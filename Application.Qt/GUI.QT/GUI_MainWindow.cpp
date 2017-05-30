#include "stdafx.h"
#include "GUI_MainWindow.h"
#include "FindBlockWidget.h"
#include "GUI_ChangePassword.h"
#include "GUI_UserInfo.h"
#include "GUI_AddBookWidget.h"
#include "GUI_ShowBooks.h"
#include "GUI_ShowMyBooks.h"

GUI_MainWindow::GUI_MainWindow(User u, QWidget* parent)
	: QMainWindow(parent), user(u)
{
	ui.setupUi(this);

	HideAllMustHave_AddUser();

	addBookTabWidget = new GUI_AddBookWidget(ui.tabWidget);
	ui.addBookLayout->addWidget(addBookTabWidget);

	showBooksTabWidget = new GUI_ShowBooks(&user, ui.tabWidget);
	ui.booksTabLayout->addWidget(showBooksTabWidget);

	showMyBooksTabWidget = new GUI_ShowMyBooks(&user, ui.tabWidget);
	ui.myBooksLayout->addWidget(showMyBooksTabWidget);
	
	if (user.getPrivelege() < UserPriveleges::user)
	{
		ui.tabWidget->removeTab(4);
	}
	
	if (user.getPrivelege() < UserPriveleges::admin)
	{
		ui.tabWidget->removeTab(3);
		ui.tabWidget->removeTab(2);
		ui.tabWidget->removeTab(1);
	}
}

GUI_MainWindow::~GUI_MainWindow()
{
	for (auto f : filters)
	{
		delete f;
	}
}

void GUI_MainWindow::ShowAllMustHave_AddUser()
{
	ui.nameMUST_AddUser->show();
	ui.surnameMUST_AddUser->show();
	ui.passportNumMUST_AddUser->show();
	ui.loginMUST_AddUser->show();
	ui.userPrivelegesMUST_AddUser->show();
	ui.fillFieldsLabel_AddUser->show();
}

void GUI_MainWindow::HideAllMustHave_AddUser()
{
	ui.nameMUST_AddUser->hide();
	ui.surnameMUST_AddUser->hide();
	ui.passportNumMUST_AddUser->hide();
	ui.loginMUST_AddUser->hide();
	ui.userPrivelegesMUST_AddUser->hide();
	ui.fillFieldsLabel_AddUser->hide();
}

void GUI_MainWindow::ClearAll_AddUser()
{
	HideAllMustHave_AddUser();
	ui.nameText_AddUser->clear();
	ui.surnameText_AddUser->clear();
	ui.fatherNameText_AddUser->clear();
	ui.passportNumText_AddUser->clear();
	ui.loginText_AddUser->clear();
	ui.userRoleComboBox_AddUser->setCurrentIndex(1);
}

void GUI_MainWindow::ClearAllTable_User()
{
	ui.tableWidget_USER->clearContents();
	while (ui.tableWidget_USER->rowCount() > 0)
	{
		ui.tableWidget_USER->removeRow(0);
	}
	ui.tableWidget_USER->repaint();

	usersFromTable.clear();
}

void GUI_MainWindow::on_ExitAction_triggered()
{
	QApplication::exit();
}

void GUI_MainWindow::on_ChangePasswordAction_triggered()
{
	GUI_ChangePassword changePassword(&user, this);
	changePassword.exec();
}

void GUI_MainWindow::on_AboutAction_triggered()
{
	QMessageBox mbBox;
	mbBox.setText("Данное программное обеспечение было разработано AJIOB");
	mbBox.setWindowTitle("Об авторе");
	mbBox.setButtonText(QMessageBox::Ok, "Хорошо");
	mbBox.setIcon(QMessageBox::Information);
	mbBox.exec();
}

void GUI_MainWindow::on_OKButton_AddUser_clicked()
{
	ui.OKButton_AddUser->setDisabled(true);
	ui.CancelButton_AddUser->setDisabled(true);
	HideAllMustHave_AddUser();

	if (ui.nameText_AddUser->text().isEmpty() || ui.surnameText_AddUser->text().isEmpty() || ui.passportNumText_AddUser->text().isEmpty()
		|| ui.loginText_AddUser->text().isEmpty() || ui.userRoleComboBox_AddUser->currentIndex() < 0)
	{
		ShowAllMustHave_AddUser();
		ui.OKButton_AddUser->setEnabled(true);
		ui.CancelButton_AddUser->setEnabled(true);
		return;
	}

	if (ControllerQT::get().addUser(ui.nameText_AddUser->text(), ui.surnameText_AddUser->text(), ui.fatherNameText_AddUser->text(),
	                                ui.passportNumText_AddUser->text(), ui.loginText_AddUser->text(), ui.userRoleComboBox_AddUser->currentIndex()))
	{
		ClearAll_AddUser();
	}

	ui.OKButton_AddUser->setEnabled(true);
	ui.CancelButton_AddUser->setEnabled(true);
}

void GUI_MainWindow::on_searchButton_USER_clicked()
{
	ui.searchButton_USER->setDisabled(true);
	ui.searchButton_USER->repaint();
	ClearAllTable_User();
	ui.moreInfoButton_USER->setEnabled(false);

	std::multimap<QString, QString> mmap;
	for (auto f: filters)
	{
		mmap.emplace(f->getCurrentData(), f->getCurrentText());
	}

	auto users = ControllerQT::get().findUsers(mmap);
	for (auto u: users)
	{
		auto table = ui.tableWidget_USER;
		int rowNum = table->rowCount();
		table->insertRow(rowNum);

		//name
		QLabel* label = new QLabel(QString::fromStdString(u.getPersonalInfo().getSurname()), table);
		table->setCellWidget(rowNum, 0, label);

		//id
		label = new QLabel(QString::fromStdString(u.getId().toString()), table);
		table->setCellWidget(rowNum, 1, label);

		usersFromTable.push_back(u);
	}
	ui.searchButton_USER->setDisabled(false);
}

void GUI_MainWindow::on_moreInfoButton_USER_clicked()
{
	GUI_UserInfo userInfo(&usersFromTable[currentSelectedRow_USER]);
	userInfo.exec();
	QLabel* label = new QLabel(QString::fromStdString(usersFromTable[currentSelectedRow_USER].getPersonalInfo().getSurname()), ui.tableWidget_USER);
	ui.tableWidget_USER->setCellWidget(currentSelectedRow_USER, 0, label);
}

void GUI_MainWindow::on_addFilterButton_USER_clicked()
{
	FindBlockWidget* fbw = new FindBlockWidget(filters, this);
	fbw->addVariant("Идентификатор", "_id");
	fbw->addVariant("Имя", "name");
	fbw->addVariant("Фамилия", "surname");
	fbw->addVariant("Отчество", "father_name");
	fbw->addVariant("Номер паспорта", "passport_number");

	ui.listLayout_USER->addWidget(fbw);
	filters.push_back(fbw);
}

void GUI_MainWindow::on_clearFilters_USER_clicked()
{
	for (auto f : filters)
	{
		delete f;
	}

	filters.clear();
}

void GUI_MainWindow::on_tableWidget_USER_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	ui.moreInfoButton_USER->setDisabled(currentRow < 0);
	ui.deleteButton_USER->setDisabled(currentRow < 0);
	currentSelectedRow_USER = currentRow;
}

void GUI_MainWindow::on_deleteButton_USER_clicked()
{
	ui.deleteButton_USER->setEnabled(false);
	if (ControllerQT::get().deleteUser(usersFromTable[currentSelectedRow_USER]))
	{
		usersFromTable.erase(usersFromTable.begin() + currentSelectedRow_USER);
		ui.tableWidget_USER->removeRow(currentSelectedRow_USER);
	}
	ui.deleteButton_USER->setEnabled(true);
}

void GUI_MainWindow::on_tabWidget_currentChanged(int index)
{
	if (index == 4)
	{
		showMyBooksTabWidget->refillAllInfo();
	}
}

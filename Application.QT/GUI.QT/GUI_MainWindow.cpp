#include "stdafx.h"
#include "GUI_MainWindow.h"
#include "FindBlockWidget.h"

GUI_MainWindow::GUI_MainWindow(User u, QWidget* parent)
	: QMainWindow(parent), user(u)
{
	//todo: different interface, which depends of user

	ui.setupUi(this);

	HideAllMustHave_AddUser();
	ui.moreInfoButton_USER->setDisabled(true);
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

void GUI_MainWindow::on_ExitAction_triggered()
{
	QApplication::exit();
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
	ui.tableWidget_USERS->clear();

	std::multimap<QString, QString> mmap;
	for (auto f: filters)
	{
		mmap.insert(std::pair<QString, QString>(f->getCurrentData(), f->getCurrentText()));
	}

	auto users = ControllerQT::get().findUsers(mmap);
	for (auto u: users)
	{
		//ui.tableWidget_USERS->insertRow(0);
		//todo: add rows to table
	}
}

void GUI_MainWindow::on_moreInfoButton_USER_clicked()
{
	//todo
}

void GUI_MainWindow::on_addFilterButton_USER_clicked()
{
	FindBlockWidget* fbw = new FindBlockWidget(filters, this);
	fbw->addVariant("Идентификатор", "_id");
	fbw->addVariant("Имя", "name");
	fbw->addVariant("Фамилия", "surname");
	fbw->addVariant("Отчество", "father_name");
	fbw->addVariant("Номер паспорта", "passport_number");

	ui.listLayout->addWidget(fbw);
	filters.push_back(fbw);
}

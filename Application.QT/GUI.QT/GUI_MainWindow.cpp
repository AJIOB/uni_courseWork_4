#include "stdafx.h"
#include "GUI_MainWindow.h"

GUI_MainWindow::GUI_MainWindow(User u, QWidget* parent)
	: QMainWindow(parent), user(u)
{
	//todo: different interface, which depends of user

	ui.setupUi(this);

	HideAllMustHave();
}

GUI_MainWindow::~GUI_MainWindow()
{
}

void GUI_MainWindow::ShowAllMustHave()
{
	ui.nameMUST_AddUser->show();
	ui.surnameMUST_AddUser->show();
	ui.passportNumMUST_AddUser->show();
	ui.loginMUST_AddUser->show();
	ui.userPrivelegesMUST_AddUser->show();
	ui.fillFieldsLabel_AddUser->show();
}

void GUI_MainWindow::HideAllMustHave()
{
	ui.nameMUST_AddUser->hide();
	ui.surnameMUST_AddUser->hide();
	ui.passportNumMUST_AddUser->hide();
	ui.loginMUST_AddUser->hide();
	ui.userPrivelegesMUST_AddUser->hide();
	ui.fillFieldsLabel_AddUser->hide();
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
	HideAllMustHave();

	if (ui.nameText_AddUser->text().isEmpty() || ui.surnameText_AddUser->text().isEmpty() || ui.passportNumText_AddUser->text().isEmpty()
		|| ui.loginText_AddUser->text().isEmpty() || ui.userRoleComboBox_AddUser->currentIndex() < 0)
	{
		ShowAllMustHave();
		ui.OKButton_AddUser->setEnabled(true);
		ui.CancelButton_AddUser->setEnabled(true);
		return;
	}

	//todo: add user to DB

	ui.OKButton_AddUser->setEnabled(true);
	ui.CancelButton_AddUser->setEnabled(true);
}

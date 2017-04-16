#include "stdafx.h"
#include "GUI_MainWindow.h"

GUI_MainWindow::GUI_MainWindow(User u, QWidget* parent)
	: QMainWindow(parent), user(u)
{
	//todo: different interface, which depends of user

	ui.setupUi(this);
}

GUI_MainWindow::~GUI_MainWindow()
{
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

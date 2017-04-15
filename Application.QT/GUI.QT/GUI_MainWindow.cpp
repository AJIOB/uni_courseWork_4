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

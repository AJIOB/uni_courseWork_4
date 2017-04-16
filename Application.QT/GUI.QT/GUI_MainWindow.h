#pragma once

#include <QMainWindow>
#include "ui_GUI_MainWindow.h"

class User;

class GUI_MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	GUI_MainWindow(User u, QWidget* parent = Q_NULLPTR);
	~GUI_MainWindow();

private:
	Ui::GUI_MainWindow ui;
	User user;

	void ShowAllMustHave();
	void HideAllMustHave();

private slots:
	void on_ExitAction_triggered();
	void on_AboutAction_triggered();
	void on_OKButton_AddUser_clicked();
};

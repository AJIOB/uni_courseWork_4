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

private slots:
	void on_ExitAction_triggered();
};

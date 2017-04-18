#pragma once

#include <QMainWindow>
#include "ui_GUI_MainWindow.h"

class User;
class FindBlockWidget;

class GUI_MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	GUI_MainWindow(User u, QWidget* parent = Q_NULLPTR);
	~GUI_MainWindow();

private:
	Ui::GUI_MainWindow ui;
	User user;

	std::list<FindBlockWidget*> filters;

	void ShowAllMustHave_AddUser();
	void HideAllMustHave_AddUser();
	void ClearAll_AddUser();

private slots:
	//head
	void on_ExitAction_triggered();
	void on_AboutAction_triggered();

	//add user tab
	void on_OKButton_AddUser_clicked();

	//users tab
	void on_searchButton_USER_clicked();
	void on_moreInfoButton_USER_clicked();
	void on_addFilterButton_USER_clicked();
};

#pragma once

#include <QMainWindow>
#include "ui_GUI_MainWindow.h"
#include <deque>

class User;
class FindBlockWidget;
class GUI_AddBookWidget;
class GUI_ShowBooks;
class GUI_ShowMyBooks;

class GUI_MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	GUI_MainWindow(User u, QWidget* parent = Q_NULLPTR);
	~GUI_MainWindow();

private:
	GUI_AddBookWidget* addBookTabWidget;
	GUI_ShowBooks* showBooksTabWidget;
	GUI_ShowMyBooks* showMyBooksTabWidget;

	Ui::GUI_MainWindow ui;
	User user;

	std::list<FindBlockWidget*> filters;
	std::deque<User> usersFromTable;
	int currentSelectedRow_USER;

	void ShowAllMustHave_AddUser();
	void HideAllMustHave_AddUser();
	void ClearAll_AddUser();

	void ClearAllTable_User();

private slots:
	//head
	void on_ExitAction_triggered();
	void on_ChangePasswordAction_triggered();
	void on_AboutAction_triggered();

	//add user tab
	void on_OKButton_AddUser_clicked();

	//users tab
	void on_searchButton_USER_clicked();
	void on_moreInfoButton_USER_clicked();
	void on_addFilterButton_USER_clicked();
	void on_clearFilters_USER_clicked();
	void on_tableWidget_USER_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_deleteButton_USER_clicked();

	//all tabs
	void on_tabWidget_currentChanged(int index);
};

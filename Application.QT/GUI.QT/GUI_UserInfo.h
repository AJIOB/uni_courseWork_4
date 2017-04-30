#pragma once

#include <deque>

#include <QDialog>
#include "ui_GUI_UserInfo.h"

class User;

class GUI_UserInfo : public QDialog, public Ui::GUI_UserInfo
{
	Q_OBJECT

public:
	GUI_UserInfo(User* u, QWidget* parent = Q_NULLPTR);
	~GUI_UserInfo();

private:
	User* cl_user;

	std::deque<Transfer> objects;
	int currentSelectedRow;

	void enableAllFields(bool enable);
	void showAllRequred();
	void hideAllRequred();
	void fillAllUserInfo();

	void fillAllBookInfo();

	void clearAllTable();

private slots:
	void on_editInfoButton_clicked();
	void on_resetPasswordButton_clicked();
	void on_editModeButtons_accepted();
	void on_editModeButtons_rejected();
	void on_getOutBookButton_clicked();
	void on_getBackBookButton_clicked();
	void on_renewBookButton_clicked();
	void on_bookInfoTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
};

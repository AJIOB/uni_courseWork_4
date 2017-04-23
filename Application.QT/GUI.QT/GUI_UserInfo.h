#pragma once

#include <QDialog>
#include "ui_GUI_UserInfo.h"

class User;

class GUI_UserInfo : public QDialog, public Ui::GUI_UserInfo
{
	Q_OBJECT

public:
	GUI_UserInfo(User* u, QWidget *parent = Q_NULLPTR);
	~GUI_UserInfo();

private:
	User* cl_user;

	void enableAllFields(bool enable);
	void showAllRequred();
	void hideAllRequred();
	void fillAllUserInfo();

private slots:
	void on_editInfoButton_clicked();
	void on_resetPasswordButton_clicked();
	void on_editModeButtons_accepted();
	void on_editModeButtons_rejected();
};

#pragma once

#include <QDialog>
#include "ui_GUI_ChangePassword.h"

class GUI_ChangePassword : public QDialog, public Ui::GUI_ChangePassword
{
	Q_OBJECT

public:
	GUI_ChangePassword(User* u, QWidget* parent = Q_NULLPTR);
	~GUI_ChangePassword();

private:
	User* cl_user;

private slots:
	void on_buttonBox_accepted();
};

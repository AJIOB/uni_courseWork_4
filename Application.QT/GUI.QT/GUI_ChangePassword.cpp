#include "stdafx.h"
#include "GUI_ChangePassword.h"

GUI_ChangePassword::GUI_ChangePassword(User* u, QWidget* parent)
	: QDialog(parent), cl_user(u)
{
	setupUi(this);
}

GUI_ChangePassword::~GUI_ChangePassword()
{
}

void GUI_ChangePassword::on_buttonBox_accepted()
{
	if (ControllerQT::get().changePassword(cl_user, oldPasswordText->text(), newPasswordText->text(), duplicatedPasswordText->text()))
	{
		accept();
	}
}

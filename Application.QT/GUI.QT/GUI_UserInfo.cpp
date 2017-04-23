#include "stdafx.h"
#include "GUI_UserInfo.h"

GUI_UserInfo::GUI_UserInfo(User* u, QWidget *parent)
	: QDialog(parent), cl_user(u)
{
	setupUi(this);

	hideAllRequred();
	editModeButtons->hide();
	fillAllUserInfo();
}

GUI_UserInfo::~GUI_UserInfo()
{
}

void GUI_UserInfo::enableAllFields(bool enable)
{
	surnameText->setEnabled(enable);
	nameText->setEnabled(enable);
	fatherNameText->setEnabled(enable);
	passportNumText->setEnabled(enable);
	loginText->setEnabled(enable);
	userRoleComboBox->setEnabled(enable);
}

void GUI_UserInfo::showAllRequred()
{
	surnameMUST->show();
	nameMUST->show();
	passportNumMUST->show();
	loginMUST->show();
	userPrivelegesMUST->show();
}

void GUI_UserInfo::hideAllRequred()
{
	surnameMUST->hide();
	nameMUST->hide();
	passportNumMUST->hide();
	loginMUST->hide();
	userPrivelegesMUST->hide();
}

void GUI_UserInfo::fillAllUserInfo()
{
	surnameText->setText(QString(cl_user->getPersonalInfo().getSurname().c_str()));
	nameText->setText(QString(cl_user->getPersonalInfo().getName().c_str()));
	fatherNameText->setText(QString(cl_user->getPersonalInfo().getFatherName().c_str()));
	passportNumText->setText(QString(cl_user->getPersonalInfo().getPassportNumber().c_str()));
	loginText->setText(QString(cl_user->getLogin().c_str()));
	userRoleComboBox->setCurrentIndex(UPtoi(cl_user->getPrivelege()) - 1);
}

void GUI_UserInfo::on_editInfoButton_clicked()
{
	editInfoButton->setEnabled(false);
	editModeButtons->show();
	mainButtonsWidget->hide();
	enableAllFields(true);
	editInfoButton->setEnabled(true);
}

void GUI_UserInfo::on_resetPasswordButton_clicked()
{
	resetPasswordButton->setEnabled(false);
	ControllerQT::get().resetPassword(cl_user);
	resetPasswordButton->setEnabled(true);
}

void GUI_UserInfo::on_editModeButtons_accepted()
{
	if (ControllerQT::get().updateUser(cl_user, nameText->text(), surnameText->text(), fatherNameText->text(), passportNumText->text(), loginText->text(), userRoleComboBox->currentIndex()))
	{
		on_editModeButtons_rejected();
	}
	else
	{
		showAllRequred();
	}
}

void GUI_UserInfo::on_editModeButtons_rejected()
{
	enableAllFields(false);
	hideAllRequred();
	fillAllUserInfo();
	editModeButtons->hide();
	mainButtonsWidget->show();
}

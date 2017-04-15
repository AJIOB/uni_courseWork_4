#include "stdafx.h"
#include "GUI_AuthClass.h"

GUI_AuthClass::GUI_AuthClass(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);

	inputErrorText->hide();
}

GUI_AuthClass::~GUI_AuthClass()
{
}

User GUI_AuthClass::getUser() const
{
	return u;
}

void GUI_AuthClass::on_OKButton_clicked()
{
	//todo: add query to DB
	inputErrorText->show();
}

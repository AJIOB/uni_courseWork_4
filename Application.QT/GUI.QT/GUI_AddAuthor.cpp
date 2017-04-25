#include "stdafx.h"
#include "GUI_AddAuthor.h"

GUI_AddAuthor::GUI_AddAuthor(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	hideAllMust();
}

GUI_AddAuthor::~GUI_AddAuthor()
{
}

DB_ID GUI_AddAuthor::getID() const
{
	//todo
}

void GUI_AddAuthor::hideAllMust()
{
	surnameMUST->hide();
	nameMUST->hide();
}

void GUI_AddAuthor::showAllMust()
{
	surnameMUST->show();
	nameMUST->show();
}

void GUI_AddAuthor::on_buttonBox_accepted()
{
	auto res = ControllerQT::get().addAuthor(surnameText->text(), nameText->text(), fatherNameText->text());
	if (res == DB_ID())
	{
		showAllMust();
	}
}

void GUI_AddAuthor::on_buttonBox_rejected()
{
	reject();
}

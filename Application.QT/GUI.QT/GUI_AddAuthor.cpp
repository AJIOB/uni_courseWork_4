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
	return id;
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
	id = ControllerQT::get().addAuthor(surnameText->text(), nameText->text(), fatherNameText->text());
	if (id == DB_ID())
	{
		showAllMust();
	}
	else
	{
		accept();
	}
}

void GUI_AddAuthor::on_buttonBox_rejected()
{
	reject();
}

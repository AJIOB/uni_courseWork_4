#include "stdafx.h"
#include "GUI_AddAuthor.h"

GUI_AddAuthor::GUI_AddAuthor(QWidget* parent)
	: QDialog(parent)
{
	setupUi(this);

	hideAllMust();
}

GUI_AddAuthor::~GUI_AddAuthor()
{
}

Author GUI_AddAuthor::getAuthor() const
{
	return author;
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
	author = ControllerQT::get().addAuthor(surnameText->text(), nameText->text(), fatherNameText->text());
	if (author == Author())
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

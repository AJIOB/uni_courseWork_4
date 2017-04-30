#include "stdafx.h"
#include "GUI_GetOutBook.h"

GUI_GetOutBook::GUI_GetOutBook(User* user, QWidget* parent)
	: QDialog(parent), cl_user(user)
{
	setupUi(this);
}

GUI_GetOutBook::~GUI_GetOutBook()
{
}

void GUI_GetOutBook::on_buttonBox_accepted()
{
	if (ControllerQT::get().getOutBook(cl_user, IDText->text()))
	{
		accept();
	}
}

void GUI_GetOutBook::on_buttonBox_rejected()
{
	reject();
}

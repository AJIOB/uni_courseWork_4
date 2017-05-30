#include "stdafx.h"
#include "GUI_ChangeAuthors.h"
#include "GUI_AddAuthor.h"
#include "ViewAuthorWidget.h"

GUI_ChangeAuthors::GUI_ChangeAuthors(std::list<Author> authors, QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	for (auto a : authors)
	{
		createOneAuthorWidget(a);
	}
}

GUI_ChangeAuthors::~GUI_ChangeAuthors()
{
}

std::list<Author> GUI_ChangeAuthors::getAuthors() const
{
	std::list<Author> res;

	for (auto waw : cl_filters)
	{
		res.push_back(waw->getAuthor());
	}

	return res;
}

void GUI_ChangeAuthors::createOneAuthorWidget(Author a)
{
	ViewAuthorWidget* waw = new ViewAuthorWidget(a, cl_filters, this);
	listOfAuthorsLayout->addWidget(waw);
	cl_filters.push_back(waw);
}

void GUI_ChangeAuthors::on_buttonBox_accepted()
{
	accept();
}

void GUI_ChangeAuthors::on_buttonBox_rejected()
{
	reject();
}

void GUI_ChangeAuthors::on_addButton_clicked()
{
	GUI_AddAuthor window;
	if (window.exec() == QDialog::Accepted)
	{
		createOneAuthorWidget(window.getAuthor());
	}
}

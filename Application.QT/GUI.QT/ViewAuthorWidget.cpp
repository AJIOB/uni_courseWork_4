#include "stdafx.h"
#include "ViewAuthorWidget.h"

ViewAuthorWidget::ViewAuthorWidget(Author a, std::list<ViewAuthorWidget*>& removeMyselfList, QWidget *parent)
	: QWidget(parent), cl_author(a), cl_removeList(&removeMyselfList)
{
	setupUi(this);

	infoText->setText(QString::fromStdString(a.getSurname() + ", " + a.getName() + " " + a.getFatherName()));
	infoText->setCursorPosition(0);
}

ViewAuthorWidget::~ViewAuthorWidget()
{
}

Author ViewAuthorWidget::getAuthor() const
{
	return cl_author;
}

void ViewAuthorWidget::on_deleteButton_clicked()
{
	auto it = std::find(cl_removeList->begin(), cl_removeList->end(), this);
	if (it != cl_removeList->end())
		cl_removeList->erase(it);
	delete this;
}

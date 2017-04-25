#include "stdafx.h"
#include "GUI_AddBookWidget.h"
#include "GUI_AddAuthor.h"

GUI_AddBookWidget::GUI_AddBookWidget(QWidget* parent)
	: QWidget(parent)
{
	setupUi(this);

	on_ClearAllButton_clicked();
}

GUI_AddBookWidget::~GUI_AddBookWidget()
{
}

void GUI_AddBookWidget::hideAllMust()
{
	ISBNMUST->hide();
	authorMUST->hide();
	nameMUST->hide();
	yearMUST->hide();
	pagesMUST->hide();
	copiesMUST->hide();
}

void GUI_AddBookWidget::showAllMust()
{
	ISBNMUST->show();
	authorMUST->show();
	nameMUST->show();
	yearMUST->show();
	pagesMUST->show();
	copiesMUST->show();
}

void GUI_AddBookWidget::on_clearAuthorsButton_clicked()
{
	for (auto a : authors)
	{
		delete a;
	}

	authors.clear();
	ids.clear();
}

void GUI_AddBookWidget::on_addAuthorButton_clicked()
{
	GUI_AddAuthor window;
	if (window.exec() == QDialog::Accepted)
	{
		auto line = new QLineEdit(this);
		line->setEnabled(false);
		authors.push_back(line);
		authorLayout->addWidget(line);
		
		ids.push_back(window.getID());

		line->setText(window.surnameText->text() + ", " + window.nameText->text() + " " + window.fatherNameText->text());
	}
}

void GUI_AddBookWidget::on_ClearAllButton_clicked()
{
	on_clearAuthorsButton_clicked();
	hideAllMust();
	ISBNText->setText("");
	nameText->setText("");
	yearSpinBox->setValue(0);
	pagesSpinBox->setValue(0);
	copiesSpinBox->setValue(0);
}

void GUI_AddBookWidget::on_AddButton_clicked()
{
	AddButton->setDisabled(true);
	AddButton->repaint();
	ClearAllButton->setDisabled(true);
	ClearAllButton->repaint();

	std::list<Author> authorNames;

	//todo
	/*for (auto a : authors)
	{
		authorNames.push_back(a->text());
	}*/

	if (!ControllerQT::get().addBook(ISBNText->text(), authorNames, nameText->text(), yearSpinBox->value(), pagesSpinBox->value(), copiesSpinBox->value()))
	{
		showAllMust();
	}
	else
	{
		on_ClearAllButton_clicked();
	}
	
	ClearAllButton->setDisabled(false);
	AddButton->setDisabled(false);
}

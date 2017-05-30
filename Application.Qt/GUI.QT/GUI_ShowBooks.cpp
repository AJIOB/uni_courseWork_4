#include "stdafx.h"
#include "GUI_ShowBooks.h"

#include "FindBlockWidget.h"
#include "GUI_BookInfo.h"

GUI_ShowBooks::GUI_ShowBooks(const User* user, QWidget* parent)
	: QWidget(parent), cl_user(user)
{
	setupUi(this);

	if (user->getPrivelege() < UserPriveleges::admin)
	{
		deleteButton->hide();
	}

	scrollAreaWidgetContents->setLayout(listLayout);
}

GUI_ShowBooks::~GUI_ShowBooks()
{
}

void GUI_ShowBooks::ClearAllTable()
{
	tableWidget->clearContents();
	while (tableWidget->rowCount() > 0)
	{
		tableWidget->removeRow(0);
	}
	tableWidget->repaint();

	objects.clear();
}

void GUI_ShowBooks::on_searchButton_clicked()
{
	searchButton->setDisabled(true);
	searchButton->repaint();
	ClearAllTable();
	moreInfoButton->setEnabled(false);

	std::multimap<QString, QString> mmap;
	for (auto f : filters)
	{
		mmap.emplace(f->getCurrentData(), f->getCurrentText());
	}

	auto books = ControllerQT::get().findBooks(mmap);
	for (auto b : books)
	{
		int rowNum = tableWidget->rowCount();
		tableWidget->insertRow(rowNum);

		//authors
		QLabel* label = new QLabel(QString::fromStdString(b.getAuthorsAsString()), tableWidget);
		tableWidget->setCellWidget(rowNum, 0, label);

		//name
		label = new QLabel(QString::fromStdString(b.getName()), tableWidget);
		tableWidget->setCellWidget(rowNum, 1, label);

		//id
		label = new QLabel(QString::fromStdString(b.getId().toString()), tableWidget);
		tableWidget->setCellWidget(rowNum, 2, label);

		objects.push_back(b);
	}
	searchButton->setDisabled(false);
}

void GUI_ShowBooks::on_moreInfoButton_clicked()
{
	GUI_BookInfo userInfo(cl_user, &objects[currentSelectedRow]);
	userInfo.exec();
	QLabel* label = new QLabel(QString::fromStdString(objects[currentSelectedRow].getAuthorsAsString()), tableWidget);
	tableWidget->setCellWidget(currentSelectedRow, 0, label);
	label = new QLabel(QString::fromStdString(objects[currentSelectedRow].getName()), tableWidget);
	tableWidget->setCellWidget(currentSelectedRow, 1, label);
}

void GUI_ShowBooks::on_addFilterButton_clicked()
{
	FindBlockWidget* fbw = new FindBlockWidget(filters, this);
	fbw->addVariant("Идентификатор", "_id");
	fbw->addVariant("ISBN", "isbn");
	fbw->addVariant("Фамилия автора", AJIOB_Const::authorSurname);
	fbw->addVariant("Название", "name");
	fbw->addVariant("Год издания", "year");

	listLayout->addWidget(fbw);
	filters.push_back(fbw);
}

void GUI_ShowBooks::on_clearFilters_clicked()
{
	for (auto f : filters)
	{
		delete f;
	}

	filters.clear();
}

void GUI_ShowBooks::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	moreInfoButton->setDisabled(currentRow < 0);
	deleteButton->setDisabled(currentRow < 0);
	currentSelectedRow = currentRow;
}

void GUI_ShowBooks::on_deleteButton_clicked()
{
	deleteButton->setEnabled(false);
	if (ControllerQT::get().deleteBook(objects[currentSelectedRow]))
	{
		objects.erase(objects.begin() + currentSelectedRow);
		tableWidget->removeRow(currentSelectedRow);
	}
	deleteButton->setEnabled(true);
}

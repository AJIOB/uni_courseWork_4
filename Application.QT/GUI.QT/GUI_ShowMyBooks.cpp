#include "stdafx.h"
#include "GUI_ShowMyBooks.h"

GUI_ShowMyBooks::GUI_ShowMyBooks(const User* u, QWidget *parent)
	: QWidget(parent), cl_user(u)
{
	setupUi(this);
	refillAllInfo();
}

GUI_ShowMyBooks::~GUI_ShowMyBooks()
{
}

void GUI_ShowMyBooks::refillAllInfo()
{
	clearAllTable();

	//Transfer, Book
	auto results = ControllerQT::get().getAllNonClosedTransfers(cl_user);
	for (auto r : results)
	{
		int rowNum = bookInfoTable->rowCount();
		bookInfoTable->insertRow(rowNum);

		//ISBN
		QLabel* label = new QLabel(QString::fromStdString(r.second.getISBN().toString()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 0, label);

		//authors
		label = new QLabel(QString::fromStdString(r.second.getAuthorsAsString()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 1, label);

		//name
		label = new QLabel(QString::fromStdString(r.second.getName()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 2, label);

		//copy id
		label = new QLabel(QString::fromStdString(r.first.getCopyId().toString()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 3, label);

		//get out date
		label = new QLabel(QString::fromStdString(r.first.getFirstGetDate().toString()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 4, label);

		//last continue date
		label = new QLabel(QString::fromStdString(r.first.getLastContinueDate().toString()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 5, label);
	}
}

void GUI_ShowMyBooks::clearAllTable()
{
	bookInfoTable->clearContents();
	while (bookInfoTable->rowCount() > 0)
	{
		bookInfoTable->removeRow(0);
	}
	bookInfoTable->repaint();
}

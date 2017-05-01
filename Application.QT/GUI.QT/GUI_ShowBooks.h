#pragma once

#include <deque>

#include <QWidget>
#include "ui_GUI_ShowBooks.h"

class Book;

class GUI_ShowBooks : public QWidget, public Ui::GUI_ShowBooks
{
	Q_OBJECT

public:
	GUI_ShowBooks(const User* user, QWidget* parent = Q_NULLPTR);
	~GUI_ShowBooks();

private:
	std::list<FindBlockWidget*> filters;
	std::deque<Book> objects;
	int currentSelectedRow;

	const User* cl_user;

	void ClearAllTable();

private slots:
	void on_searchButton_clicked();
	void on_moreInfoButton_clicked();
	void on_addFilterButton_clicked();
	void on_clearFilters_clicked();
	void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_deleteButton_clicked();
};

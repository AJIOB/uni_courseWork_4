#pragma once

#include <QDialog>
#include "ui_GUI_BookInfo.h"

class GUI_BookInfo : public QDialog, public Ui::GUI_BookInfo
{
	Q_OBJECT

public:
	GUI_BookInfo(const User* user, Book* book, QWidget *parent = Q_NULLPTR);
	~GUI_BookInfo();

private:
	const User* cl_user;
	Book* cl_book;
	
	std::list<Transfer> transfers;
	int currentSelectedRow;

	std::list<Author> newAuthors;

	void enableAllFields(bool enable);
	void showAllRequred();
	void hideAllRequred();

	void fillAllBookCopyInfo();
	void fillAllBookInfo();

	void clearAllTable();

	void disableTable();
	void enableTable();

	static QString fromBool(const bool& b);
	BookCopy getCurrentBookCopy() const;

private slots :
	void on_editInfoButton_clicked();
	void on_editModeButtons_accepted();
	void on_editModeButtons_rejected();
	void on_getBackBookButton_clicked();
	void on_renewBookButton_clicked();
	void on_archieveBookButton_clicked();
	void on_bookInfoTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void on_editAuthorsButton_clicked();
};

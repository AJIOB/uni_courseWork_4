#include "stdafx.h"
#include "GUI_BookInfo.h"
#include "GUI_ChangeAuthors.h"

GUI_BookInfo::GUI_BookInfo(const User* user, Book* book, QWidget *parent)
	: QDialog(parent), cl_user(user), cl_book(book), currentSelectedRow(-1)
{
	setupUi(this);

	hideAllRequred();
	editModeButtons->hide();
	fillAllBookCopyInfo();
	fillAllBookInfo();

	if (user->getPrivelege() < UserPriveleges::admin)
	{
		editCopiesButtons->hide();
		editInfoButton->hide();
	}
}

GUI_BookInfo::~GUI_BookInfo()
{
}

void GUI_BookInfo::enableAllFields(bool enable)
{
	ISBNText->setReadOnly(!enable);
	nameText->setReadOnly(!enable);
	yearSpinBox->setReadOnly(!enable);
	pagesSpinBox->setReadOnly(!enable);
	copiesSpinBox->setReadOnly(!enable);
	editAuthorsButton->setEnabled(enable);
}

void GUI_BookInfo::showAllRequred()
{
	ISBNMUST->show();
	authorMUST->show();
	nameMUST->show();
	yearMUST->show();
	pagesMUST->show();
	copiesMUST->show();
}

void GUI_BookInfo::hideAllRequred()
{
	ISBNMUST->hide();
	authorMUST->hide();
	nameMUST->hide();
	yearMUST->hide();
	pagesMUST->hide();
	copiesMUST->hide();
}

void GUI_BookInfo::fillAllBookCopyInfo()
{
	clearAllTable();

	transfers = ControllerQT::get().getAllNonClosedTransfers(cl_book);
	for (auto copy : cl_book->getCopies())
	{
		int rowNum = bookInfoTable->rowCount();
		bookInfoTable->insertRow(rowNum);

		//copy id
		QLabel* label = new QLabel(QString::fromStdString(copy.getId().toString()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 0, label);

		//isArchieved
		label = new QLabel(fromBool(copy.getIsArchieved()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 1, label);

		//is getted out
		label = new QLabel(fromBool(copy.getIsGettedOut()), bookInfoTable);
		bookInfoTable->setCellWidget(rowNum, 2, label);
	}
}

void GUI_BookInfo::fillAllBookInfo()
{
	ISBNText->setText(QString::fromStdString(cl_book->getISBN().toString()));
	authorsText->setText(QString::fromStdString(cl_book->getAuthorsAsString()));
	nameText->setText(QString::fromStdString(cl_book->getName()));
	yearSpinBox->setValue(cl_book->getYear());
	pagesSpinBox->setValue(cl_book->getPageCount());
	copiesSpinBox->setValue(cl_book->getCopies().size());

	copiesSpinBox->setMinimum(cl_book->getCopies().size());

	ISBNText->setCursorPosition(0);
	authorsText->setCursorPosition(0);
	nameText->setCursorPosition(0);
}

void GUI_BookInfo::clearAllTable()
{
	bookInfoTable->clearContents();
	while (bookInfoTable->rowCount() > 0)
	{
		bookInfoTable->removeRow(0);
	}
	bookInfoTable->repaint();

	transfers.clear();
}

void GUI_BookInfo::disableTable()
{
	allTableWidget->setEnabled(false);
}

void GUI_BookInfo::enableTable()
{
	allTableWidget->setEnabled(true);
	bookInfoTable->setCurrentCell(-1, -1);
}

QString GUI_BookInfo::fromBool(const bool& b)
{
	return b ? "Да" : "Нет";
}

void GUI_BookInfo::on_editInfoButton_clicked()
{
	editInfoButton->setEnabled(false);
	editModeButtons->show();
	mainButtonsWidget->hide();
	enableAllFields(true);
	disableTable();

	newAuthors = cl_book->getAuthors();

	editInfoButton->setEnabled(true);
}

void GUI_BookInfo::on_editModeButtons_accepted()
{
	if (ControllerQT::get().updateBook(cl_book, ISBNText->text(), newAuthors, nameText->text(), yearSpinBox->value(), pagesSpinBox->value(), copiesSpinBox->value()))
	{
		on_editModeButtons_rejected();
		copiesSpinBox->setMinimum(cl_book->getCopies().size());
	}
	else
	{
		showAllRequred();
	}
}

void GUI_BookInfo::on_editModeButtons_rejected()
{
	enableAllFields(false);
	hideAllRequred();
	fillAllBookInfo();
	fillAllBookCopyInfo();
	editModeButtons->hide();
	mainButtonsWidget->show();
	
	enableTable();
}

void GUI_BookInfo::on_getBackBookButton_clicked()
{
	auto bookCopy = getCurrentBookCopy();
	auto itTransfer = std::find_if(transfers.begin(), transfers.end(), [&bookCopy](const Transfer& t) -> bool
	{
		return bookCopy.getId() == t.getCopyId();
	});

	if (ControllerQT::get().returnBook(*itTransfer, cl_book))
	{
		fillAllBookCopyInfo();
	}
	bookInfoTable->setCurrentCell(-1, -1);
}

void GUI_BookInfo::on_renewBookButton_clicked()
{
	auto bookCopy = getCurrentBookCopy();
	auto itTransfer = std::find_if(transfers.begin(), transfers.end(), [&bookCopy](const Transfer& t) -> bool
	{
		return bookCopy.getId() == t.getCopyId();
	});

	if (ControllerQT::get().renewBook(*itTransfer))
	{
		fillAllBookCopyInfo();
	}
	bookInfoTable->setCurrentCell(-1, -1);
}

void GUI_BookInfo::on_archieveBookButton_clicked()
{
	auto bookCopy = getCurrentBookCopy();
	if (ControllerQT::get().archieveBook(&bookCopy, cl_book))
	{
		fillAllBookCopyInfo();
	}
	
	bookInfoTable->setCurrentCell(-1, -1);
}

BookCopy GUI_BookInfo::getCurrentBookCopy() const
{
	auto copies = cl_book->getCopies();
	auto it = copies.begin();

	for (auto i = 0; i < currentSelectedRow; ++i)
	{
		++it;
	}

	return *it;
}

void GUI_BookInfo::on_bookInfoTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	currentSelectedRow = currentRow;

	auto bookCopy = getCurrentBookCopy();

	archieveBookButton->setDisabled(bookCopy.getIsArchieved() || bookCopy.getIsGettedOut() || currentRow < 0);
	getBackBookButton->setDisabled(bookCopy.getIsArchieved() || !bookCopy.getIsGettedOut() || currentRow < 0);
	renewBookButton->setDisabled(bookCopy.getIsArchieved() || !bookCopy.getIsGettedOut() || currentRow < 0);
}

void GUI_BookInfo::on_editAuthorsButton_clicked()
{
	GUI_ChangeAuthors gui(newAuthors, this);
	if (gui.exec() == QMessageBox::Accepted)
	{
		newAuthors = gui.getAuthors();
		authorsText->setText(QString::fromStdString(Book::getAuthorsAsString(newAuthors)));
	}
}

#include "stdafx.h"
#include "GUI_UserInfo.h"
#include "GUI_GetOutBook.h"

GUI_UserInfo::GUI_UserInfo(User* u, QWidget* parent)
	: QDialog(parent), cl_user(u)
{
	setupUi(this);

	hideAllRequred();
	editModeButtons->hide();
	fillAllUserInfo();
	fillAllBookInfo();
}

GUI_UserInfo::~GUI_UserInfo()
{
	clearAllTable();
}

void GUI_UserInfo::enableAllFields(bool enable)
{
	surnameText->setReadOnly(!enable);
	nameText->setReadOnly(!enable);
	fatherNameText->setReadOnly(!enable);
	passportNumText->setReadOnly(!enable);
	loginText->setReadOnly(!enable);
	userRoleComboBox->setEnabled(enable);
}

void GUI_UserInfo::showAllRequred()
{
	surnameMUST->show();
	nameMUST->show();
	passportNumMUST->show();
	loginMUST->show();
	userPrivelegesMUST->show();
}

void GUI_UserInfo::hideAllRequred()
{
	surnameMUST->hide();
	nameMUST->hide();
	passportNumMUST->hide();
	loginMUST->hide();
	userPrivelegesMUST->hide();
}

void GUI_UserInfo::fillAllUserInfo()
{
	surnameText->setText(QString(cl_user->getPersonalInfo().getSurname().c_str()));
	nameText->setText(QString(cl_user->getPersonalInfo().getName().c_str()));
	fatherNameText->setText(QString(cl_user->getPersonalInfo().getFatherName().c_str()));
	passportNumText->setText(QString(cl_user->getPersonalInfo().getPassportNumber().c_str()));
	loginText->setText(QString(cl_user->getLogin().c_str()));
	userRoleComboBox->setCurrentIndex(UPtoi(cl_user->getPrivelege()) - 1);

	surnameText->setCursorPosition(0);
	nameText->setCursorPosition(0);
	fatherNameText->setCursorPosition(0);
	passportNumText->setCursorPosition(0);
	loginText->setCursorPosition(0);
}

void GUI_UserInfo::fillAllBookInfo()
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

		objects.push_back(r.first);
	}
}

void GUI_UserInfo::clearAllTable()
{
	bookInfoTable->clearContents();
	while (bookInfoTable->rowCount() > 0)
	{
		bookInfoTable->removeRow(0);
	}
	bookInfoTable->repaint();

	objects.clear();
}

void GUI_UserInfo::on_editInfoButton_clicked()
{
	editInfoButton->setEnabled(false);
	editModeButtons->show();
	mainButtonsWidget->hide();
	enableAllFields(true);
	editInfoButton->setEnabled(true);
}

void GUI_UserInfo::on_resetPasswordButton_clicked()
{
	resetPasswordButton->setEnabled(false);
	ControllerQT::get().resetPassword(cl_user);
	resetPasswordButton->setEnabled(true);
}

void GUI_UserInfo::on_editModeButtons_accepted()
{
	if (ControllerQT::get().updateUser(cl_user, nameText->text(), surnameText->text(), fatherNameText->text(), passportNumText->text(), loginText->text(), userRoleComboBox->currentIndex()))
	{
		on_editModeButtons_rejected();
	}
	else
	{
		showAllRequred();
	}
}

void GUI_UserInfo::on_editModeButtons_rejected()
{
	enableAllFields(false);
	hideAllRequred();
	fillAllUserInfo();
	editModeButtons->hide();
	mainButtonsWidget->show();
}

void GUI_UserInfo::on_getOutBookButton_clicked()
{
	GUI_GetOutBook box(cl_user, this);
	if (box.exec() == QMessageBox::Accepted)
	{
		fillAllBookInfo();
	}
}

void GUI_UserInfo::on_getBackBookButton_clicked()
{
	if (ControllerQT::get().returnBook(objects[currentSelectedRow]))
	{
		objects.erase(objects.begin() + currentSelectedRow);
		bookInfoTable->removeRow(currentSelectedRow);
	}
}

void GUI_UserInfo::on_renewBookButton_clicked()
{
	if (ControllerQT::get().renewBook(objects[currentSelectedRow]))
	{
		fillAllBookInfo();
	}
}

void GUI_UserInfo::on_bookInfoTable_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	renewBookButton->setDisabled(currentRow < 0);
	getBackBookButton->setDisabled(currentRow < 0);
	currentSelectedRow = currentRow;
}

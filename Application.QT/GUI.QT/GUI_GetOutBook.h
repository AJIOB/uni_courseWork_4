#pragma once

#include <QDialog>
#include "ui_GUI_GetOutBook.h"

class GUI_GetOutBook : public QDialog, public Ui::GUI_GetOutBook
{
	Q_OBJECT

public:
	GUI_GetOutBook(User* user, QWidget* parent = Q_NULLPTR);
	~GUI_GetOutBook();

private:
	User* cl_user;

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
};

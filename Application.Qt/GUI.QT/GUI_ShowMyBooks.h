#pragma once

#include <QWidget>
#include "ui_GUI_ShowMyBooks.h"

class GUI_ShowMyBooks : public QWidget, public Ui::GUI_ShowMyBooks
{
	Q_OBJECT

public:
	GUI_ShowMyBooks(const User* u, QWidget *parent = Q_NULLPTR);
	~GUI_ShowMyBooks();

	void refillAllInfo();

private:
	const User* cl_user;

	void clearAllTable();
};

#pragma once

#include <QDialog>
#include "ui_GUI_AuthClass.h"

class GUI_AuthClass : public QDialog, public Ui::GUI_AuthClass
{
	Q_OBJECT

public:
	GUI_AuthClass(QWidget* parent = Q_NULLPTR);
	~GUI_AuthClass();

	User getUser() const;

private:
	User u;

private slots:
	void on_OKButton_clicked();
	void on_loginAsGuestButton_clicked();
};

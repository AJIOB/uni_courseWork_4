#pragma once

#include <QDialog>
#include "ui_GUI_AddAuthor.h"

class GUI_AddAuthor : public QDialog, public Ui::GUI_AddAuthor
{
	Q_OBJECT

public:
	GUI_AddAuthor(QWidget* parent = Q_NULLPTR);
	~GUI_AddAuthor();

	Author getAuthor() const;

private:
	Author author;

	void hideAllMust();
	void showAllMust();

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
};

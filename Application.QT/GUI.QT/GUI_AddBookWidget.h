#pragma once

#include <QWidget>
#include "ui_GUI_AddBookWidget.h"

class GUI_AddBookWidget : public QWidget, public Ui::GUI_AddBookWidget
{
	Q_OBJECT

public:
	GUI_AddBookWidget(QWidget* parent = Q_NULLPTR);
	~GUI_AddBookWidget();

private:
	std::list<QLineEdit*> authorLines;
	std::list<Author> authors;

	void hideAllMust();
	void showAllMust();

private slots:
	void on_clearAuthorsButton_clicked();
	void on_addAuthorButton_clicked();
	void on_ClearAllButton_clicked();
	void on_AddButton_clicked();
};

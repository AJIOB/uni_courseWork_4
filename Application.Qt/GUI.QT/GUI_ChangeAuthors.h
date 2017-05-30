#pragma once

#include <QDialog>
#include "ui_GUI_ChangeAuthors.h"

class ViewAuthorWidget;

class GUI_ChangeAuthors : public QDialog, public Ui::GUI_ChangeAuthors
{
	Q_OBJECT

public:
	GUI_ChangeAuthors(std::list<Author> authors, QWidget *parent = Q_NULLPTR);
	~GUI_ChangeAuthors();

	std::list<Author> getAuthors() const;

private:
	std::list<ViewAuthorWidget*> cl_filters;

	void createOneAuthorWidget(Author a);

private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();
	void on_addButton_clicked();
};

#pragma once

#include <QWidget>
#include "ui_ViewAuthorWidget.h"

class ViewAuthorWidget : public QWidget, public Ui::ViewAuthorWidget
{
	Q_OBJECT

public:
	ViewAuthorWidget(Author a, std::list<ViewAuthorWidget*>& removeMyselfList, QWidget *parent = Q_NULLPTR);
	~ViewAuthorWidget();

	Author getAuthor() const;

private:
	std::list<ViewAuthorWidget*>* cl_removeList;
	Author cl_author;

private slots:
	void on_deleteButton_clicked();
};

#pragma once

#include <QWidget>
#include "ui_FindBlockWidget.h"

class FindBlockWidget : public QWidget
{
	Q_OBJECT

public:
	explicit FindBlockWidget(std::list<FindBlockWidget*>& removeMyselfList, QWidget* parent = Q_NULLPTR);
	~FindBlockWidget();

	void addVariant(const QString& text, const QString& data);
	void clearVariants();
	void clear();
	void clearText();
	QString getCurrentData();
	QString getCurrentText() const;

private:
	Ui::FindBlockWidget ui;
	std::list<FindBlockWidget*>* removeList;

private slots:
	void on_deleteButton_clicked();
};

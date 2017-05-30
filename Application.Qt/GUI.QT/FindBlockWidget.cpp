#include "stdafx.h"
#include "FindBlockWidget.h"

FindBlockWidget::FindBlockWidget(std::list<FindBlockWidget*>& removeList, QWidget* parent)
	: QWidget(parent), removeList(&removeList)
{
	ui.setupUi(this);
}

FindBlockWidget::~FindBlockWidget()
{
}

void FindBlockWidget::addVariant(const QString& text, const QString& data)
{
	ui.variants->addItem(text, data);
}

void FindBlockWidget::clearVariants()
{
	ui.variants->clear();
}

void FindBlockWidget::clear()
{
	clearText();
	clearVariants();
}

void FindBlockWidget::clearText()
{
	ui.infoText->clear();
}

QString FindBlockWidget::getCurrentData()
{
	return ui.variants->currentData().toString();
}

QString FindBlockWidget::getCurrentText() const
{
	return ui.infoText->text();
}

void FindBlockWidget::on_deleteButton_clicked()
{
	auto it = std::find(removeList->begin(), removeList->end(), this);
	if (it != removeList->end())
		removeList->erase(it);
	delete this;
}

#pragma once

#include <QTableWidget>

#include "BaseHashTableWidget.h"

class HashTableWidget : public BaseHashTableWidget
{
    Q_OBJECT
public:
    HashTableWidget(QWidget *parent = nullptr);
    ~HashTableWidget() override = default;

protected slots:
    void addKeyValue() override;
    void resizeTable() override;

private slots:
    void onItemChanged(QTableWidgetItem *item);

private:
    QTableWidget *m_tableWidget = nullptr;
};


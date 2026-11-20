#include <QDebug>

#include "HashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

HashTableWidget::HashTableWidget(QWidget *parent)
    : BaseHashTableWidget(parent)
    , m_tableWidget(new QTableWidget(this))
{
    ui->verticalLayout->insertWidget(0, m_tableWidget);
    m_tableWidget->setColumnCount(2);
    m_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Key"));
    m_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));
    HashTableWidget::resizeTable();

    connect(m_tableWidget, &QTableWidget::itemChanged, this, &HashTableWidget::onItemChanged);
}

void HashTableWidget::addKeyValue()
{
    // TODO: проверка на повтор ключа
    // TODO: заменить определение строки
    int row = -1;
    while (row < 0 || !m_tableWidget->item(row, 0)->text().isEmpty())
    {
        row = rand() % m_tableWidget->rowCount();
    }

    m_tableWidget->blockSignals(true);
    m_tableWidget->item(row, 0)->setText(ui->spinBox_key->text());
    QTableWidgetItem *item = m_tableWidget->item(row, 1);
    item->setText(ui->lineEdit_value->text());
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    m_tableWidget->blockSignals(false);
}

void HashTableWidget::resizeTable()
{
    m_tableWidget->blockSignals(true);
    // TODO: resize хеш-таблицы
    int oldSize = m_tableWidget->rowCount();
    m_tableWidget->setRowCount(ui->spinBox_size->value());
    for (int i = 0; i < oldSize; ++i)
    {
        // TODO: заполнить новыми значениями из хеш-таблицы
    }
    for (int i = oldSize; i < m_tableWidget->rowCount(); ++i)
    {
        m_tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        m_tableWidget->setItem(i, 0, item);

        item = new QTableWidgetItem();
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        m_tableWidget->setItem(i, 1, item);
    }
    m_tableWidget->blockSignals(false);
}

void HashTableWidget::onItemChanged(QTableWidgetItem *item)
{
    if (item->column() != 1)
    {
        return; // Non-value item, skip
    }

    int key = m_tableWidget->item(item->row(), 0)->data(Qt::DisplayRole).toInt();
    QString value = item->data(Qt::DisplayRole).toString();
    onValueChanged(key, value);
}

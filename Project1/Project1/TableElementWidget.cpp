#include <QPalette>
#include <QColor>

#include "TableElementWidget.h"
#include "ui_TableElementWidget.h"

TableElementWidget::TableElementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableElementWidget)
{
    ui->setupUi(this);

    connect(ui->lineEdit_value, &QLineEdit::textChanged, this, &TableElementWidget::onValueChanged);
}

TableElementWidget::~TableElementWidget()
{
    delete ui;
}

int TableElementWidget::key() const
{
    return ui->lineEdit_key->text().toInt();
}

QString TableElementWidget::value() const
{
    return ui->lineEdit_value->text();
}

void TableElementWidget::setKey(int key)
{
    ui->lineEdit_key->setText(QString::number(key));
}

void TableElementWidget::setValue(const QString &value)
{
    ui->lineEdit_value->setText(value);
}

void TableElementWidget::itemIsEditable()
{
    ui->lineEdit_value->setEnabled(1);
}
void TableElementWidget::itemIsNotEditable()
{
    ui->lineEdit_key->setEnabled(0);
    ui->lineEdit_value->setEnabled(0);
}

bool TableElementWidget::isEmpty() const
{
    return ui->lineEdit_key->text().isEmpty();
}

void TableElementWidget::clear()
{
    ui->lineEdit_key->clear();
    ui->lineEdit_value->clear();

}

void TableElementWidget::onValueChanged(const QString &value)
{
    if (!isEmpty())
    {
        emit valueChanged(key(), value);
    }
}

void TableElementWidget::changeColor(const QColor& color)
{

    QPalette palette = ui->lineEdit_key->palette();
    palette.setColor(QPalette::Base, color);
    ui->lineEdit_key->setPalette(palette);
    //ui->lineEdit_value->setPalette(palette);
}

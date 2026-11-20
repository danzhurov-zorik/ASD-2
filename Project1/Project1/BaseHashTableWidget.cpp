#include "BaseHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

BaseHashTableWidget::BaseHashTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BaseHashTableWidget)
{
    ui->setupUi(this);
    connect(ui->spinBox_size, &QSpinBox::editingFinished, this, &BaseHashTableWidget::resizeTable);
    connect(ui->pushButton_add, &QPushButton::clicked, this, &BaseHashTableWidget::addKeyValue);
    connect(ui->pushButton_remove, &QPushButton::clicked, this, &BaseHashTableWidget::removeKeyValue);
    connect(ui->pushButton_find, &QPushButton::clicked, this, &BaseHashTableWidget::findKey);
    connect(ui->comboBox_function, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BaseHashTableWidget::changeFunction);
}

BaseHashTableWidget::~BaseHashTableWidget()
{
    delete ui;
}

void BaseHashTableWidget::onValueChanged(int key, const QString &value)
{
    m_hashTable.setValue(key, value);


    //value.toStdString()
    // TODO: записать новое значение в хеш-таблицу
}

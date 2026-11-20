#include <QGraphicsProxyWidget>
#include <utility>

#include "TableElementWidget.h"

#include "SceneHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

SceneHashTableWidget::SceneHashTableWidget(QWidget *parent)
    : BaseHashTableWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_view(new QGraphicsView(this))
{
    m_view->setScene(m_scene);
    ui->verticalLayout->insertWidget(0, m_view);

    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::addKeyValue()
{
    if(m_hashTable.contains(ui->spinBox_key->value())) //проверка на повтор ключа
        return;

    int row = m_hashTable.hashFunction()->hash(ui->spinBox_key->value(), ui->spinBox_size->value());

    m_hashTable.insert(ui->spinBox_key->value(), ui->lineEdit_value->text());

    int column = 0;

    if (!m_rows[row][column].widget->isEmpty())
    {
        column = m_rows[row].size();
        addBlankElement(row, column);
    }

    m_rows[row][column].widget->setKey(ui->spinBox_key->value());
    m_rows[row][column].widget->setValue(ui->lineEdit_value->text());

    m_rows[row][column].widget->itemIsEditable();
}

void SceneHashTableWidget::removeKeyValue()
{
    m_hashTable.removeKey(ui->spinBox_key->value());
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::findKey()
{
    int hash = m_hashTable.hashFunction()->hash(ui->spinBox_key->value(), m_hashTable.capacity());
    for(int i = 0; i < m_hashTable.hashTable()[hash].size(); i++)
    {
        if(m_hashTable.hashTable()[hash][i].first == ui->spinBox_key->value())
        {
            m_rows[hash][i].widget->changeColor(Qt::green);
            return;
        }
    }
}

void SceneHashTableWidget::resizeTable()
{

    int oldSize = m_rows.size();
    int newSize = ui->spinBox_size->value();

    m_hashTable.setCapacity(newSize);

    for (int i = 0; i < oldSize; ++i)
    {
        for (ElementData& data : m_rows[i])
        {
            m_scene->removeItem(data.proxy);
            data.widget->deleteLater();
        }
    }

    m_rows.clear();
    m_rows.resize(newSize);

    for (int i = 0; i < newSize; ++i)
    {
        addBlankElement(i, 0);
    }

    for (int i = 0; i < newSize; i++)
    {
        for(int j = 0; j < m_hashTable.hashTable()[i].size(); j++)
        {
            if(!m_rows[i][0].widget->isEmpty())
                addBlankElement(i, j);

            m_rows[i][j].widget->itemIsEditable();

            m_rows[i][j].widget->setKey(m_hashTable.hashTable()[i][j].first);
            m_rows[i][j].widget->setValue(m_hashTable.hashTable()[i][j].second);
        }
        // TODO: заполнить новыми значениями из хеш-таблицы
        // (добавить/удалить элементы коллизий при необходимости)
    }
}

void SceneHashTableWidget::changeFunction(int index)
{

    switch (index) {
    case 0:
        m_hashTable.setFunction(new QuadraticHash());
        break;
    case 1:
        m_hashTable.setFunction(new MultiplicationHash());
        break;
    case 2:
        m_hashTable.setFunction(new ThirdHash());
        break;
    default:
        break;
    }

    SceneHashTableWidget::resizeTable();
}



void SceneHashTableWidget::addBlankElement(int row, int column)
{
    TableElementWidget *item = new TableElementWidget();
    item->itemIsNotEditable();

    connect(item, &TableElementWidget::valueChanged, this, &SceneHashTableWidget::onValueChanged);

    QGraphicsProxyWidget* proxy = m_scene->addWidget(item);
    column = m_rows[row].size();
    int x = column * (item->width() + 50);
    int y = row * item->height();
    proxy->setX(x);
    proxy->setY(y);

    if (column)
    {
        int centerY = item->height() / 2;
        auto* line = m_scene->addLine(-50, centerY, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2 * 3, 0, centerY);
        line->setParentItem(proxy);
    }

    m_rows[row].append({item, proxy});
}

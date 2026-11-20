#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>

#include "TableElementWidget.h"

#include "BaseHashTableWidget.h"

/**
 * @brief Класс виджета хеш-таблицы, основанной на методе внешних цепочек.
 * Для его реализации элементы таблицы размещаются на сцене (QGraphicsScene).
 *
 * см. также класс `TableElementWidget`.
 */
class SceneHashTableWidget : public BaseHashTableWidget
{
public:
    SceneHashTableWidget(QWidget *parent = nullptr);

protected slots:
    void addKeyValue() override;
    void removeKeyValue() override;
    void findKey() override;
    void resizeTable() override;


    void changeFunction(int index) override;

private:
    /**
     * @brief На QGraphicsScene нельзя размещать виждеты напрямую;
     * Сцена может хранить только наследников класса QGraphicsItem.
     * Поэтому при попытке добавления виджета на сцену (см. `addElement`)
     * сцена автоматически создаст для него специальный объект-контейнер типа QGraphicsProxyWidget.
     * Данная структура нужна для сопоставления виждета элемента таблицы с его контейнером.
     */
    struct ElementData
    {
        TableElementWidget* widget = nullptr;
        QGraphicsProxyWidget* proxy = nullptr;
    };

private:
    /**
     * @brief Добавляет пустой элемент хеш-таблицы на сцену.
     * @param row индекс строки элемента.
     * @param column индекс столбца (коллизии) элемента.
     */
    void addBlankElement(int row, int column);

private:
    /**
     * @brief Сцена, на которой размещаются элементы таблицы.
     */
    QGraphicsScene *m_scene = nullptr;

    /**
     * @brief Класс, отвечающий за отображение заданной области сцены
     * (сцена может быть намного больше видимой части).
     */
    QGraphicsView *m_view = nullptr;

    QVector<QVector<ElementData>> m_rows;
};

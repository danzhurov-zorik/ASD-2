#include "HashTableWidget.h"
#include "SceneHashTableWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SceneHashTableWidget w;
    w.show();
    return a.exec();
}

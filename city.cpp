#include "city.h"


City::City(QString name, int x, int y):
    name(name), x(x), y(y)
{

}

City::~City()
{

}

void City::draw(QGraphicsScene &scene)
{
    QPen Pen;
    QString Stadt = this->name;
    Pen.setColor(Qt::red);
    Pen.setWidth(2);
    scene.addEllipse(x, y, 12, 12, Pen, QBrush(Qt::yellow, Qt::SolidPattern));

    QGraphicsTextItem* text = new QGraphicsTextItem;
    text->setPos(x, y);
    text->setPlainText(Stadt);
    scene.addItem(text);
}

QString City::getName()
{
    return name;
}

int City::getX()
{
    return x;
}

int City::getY()
{
    return y;
}


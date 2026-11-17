#include "map.h"

Map::Map()
{

}

void Map::addCity(City* stadt)
{
    staedte_Liste.append(stadt);
    qDebug() << stadt->getName() << "wurde in die Karte hinzugefügt.";
}

City* Map::findCity(const QString cityName) const
{
    for(QVector<City*>::const_iterator it = staedte_Liste.begin(); it != staedte_Liste.end(); it++)
    {
        if ((*it)->getName() == cityName)
        {
            return *it;
        }
    }

    return nullptr;
}

QVector<Street*> Map::getStreetList(const City* city) const
{
    QVector <Street*> CityStreetList;
    for(QVector<Street*>::const_iterator it = strassen_Liste.begin(); it != strassen_Liste.end(); it++)
    {
        if(city == (*it)->getStadt1() || city == (*it)->getStadt2())
        {
            CityStreetList.append(*it);
        }
    }

    return CityStreetList;
}

QVector<City*> Map::getCityList()
{
    return staedte_Liste;
}

City* Map::getOppositeCity(const Street* street, const City* city) const
{
    if (city == street->getStadt1())
    {
        return street->getStadt2();
    }

    else if (city == street->getStadt2())
    {
        return street->getStadt1();
    }

    else
    {
        return nullptr;
    }
}

double Map::getLength(const Street* street) const
{
    double x1 = street->getStadt1()->getX();
    double x2 = street->getStadt2()->getX();
    double y1 = street->getStadt1()->getY();
    double y2 = street->getStadt2()->getY();

    double x_laenge = abs(x2 - x1);
    double y_laenge = abs(y2 - y1);

    double length = sqrt(x_laenge*x_laenge + y_laenge*y_laenge);

    return length;
}

bool Map::addStreet(Street* strasse)
{
    City* gorad1 = strasse->getStadt1();
    City* gorad2 = strasse->getStadt2();

    if (findCity(gorad1->getName()) != nullptr && findCity(gorad2->getName()) != nullptr)
    {
        strassen_Liste.append(strasse);
        return true;
    }

    else
    {
        return false;
    }
}

void Map::draw(QGraphicsScene &scene)
{
    for(QVector<City*>::iterator it = staedte_Liste.begin(); it != staedte_Liste.end(); it++)
    {
        QPen Pen;
        QString gorod = (*it)->getName();
        int x = (*it)->getX();
        int y = (*it)->getY();
        Pen.setColor(Qt::red);
        Pen.setWidth(2);
        scene.addEllipse(x, y, 12, 12, Pen, QBrush(Qt::yellow, Qt::SolidPattern));

        QGraphicsTextItem* text = new QGraphicsTextItem;
        text->setPos(x, y);
        text->setPlainText(gorod);
        scene.addItem(text);
    }
}

Map::~Map()
{

}

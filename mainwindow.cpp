#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "city.h"
#include "street.h"
#include <QDebug>
#include <QString>
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
#include "dialog.h"
#include "dijkstra.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    mapio = new MapIoNrw;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stpushButton_test_clicked()
{
    QString str1 = ui->lineEdit_test->text();
    bool ok;
    int a = str1.toInt(&ok);
    QMessageBox msgBox;

    if (!ok)
    {
        QString str2 = QString("Ihr eingegebener Text: %1").arg(str1);
        qDebug() << str2;
    }
    else
    {
        qDebug() << "Ihre um 4 inkreminierte Zahl: " << a + 4;
    }

    double x = qrand()*9/RAND_MAX;
    double y = qrand()*9/RAND_MAX;
    double w = qrand()*9/RAND_MAX;
    double h = qrand()*9/RAND_MAX;

    scene.addRect(x, y, w, h, QPen(Qt::red), QBrush(Qt::SolidPattern));

    msgBox.exec();

}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionClear_Scene_triggered()
{
    scene.clear();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    QString str1 = "Netter Titel!";
    QString str2 = "Ein netter Versuch, dieses Projekt zu beschreiben!";

    msgBox.about(this, str1, str2);
}

void MainWindow::on_test_draw_city_clicked()
{
    City Kairo("Kairo", 0, 0);
    City Aachen("Aachen", 40, 10);
    Kairo.draw(scene);
    Aachen.draw(scene);
}

void MainWindow::on_TestMap_clicked()
{
    City Kairo("Kairo", 0, 0);
    City Aachen("Aachen", 20, 50);
    map.addCity(&Kairo);
    map.addCity(&Aachen);
    Kairo.draw(scene);
    Aachen.draw(scene);

}

void MainWindow::on_TestStreet_clicked()
{
    City Kairo("Kairo", 0, 0);
    City Aachen("Aachen", 20, 50);
    Street street1(&Kairo, &Aachen);
    map.addCity(&Kairo);
    map.addCity(&Aachen);
    Kairo.draw(scene);
    Aachen.draw(scene);
    street1.draw(scene);
}

void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked()==true)
    {
        ui->TestStreet->hide();
        ui->TestMap->hide();
        ui->test_draw_city->hide();
    }

    else if(ui->checkBox->isChecked()==false)
    {
        ui->TestStreet->show();
        ui->TestMap->show();
        ui->test_draw_city->show();
    }

}

void MainWindow::on_AddCity_clicked()
{
    Dialog dialog;
    int i = dialog.exec();
    qDebug() << "Der Rückgabewert: " << i;

    if (i == 1)
    {
        City* gorad = dialog.neueStadt();
        map.addCity(gorad);
        gorad->draw(scene);
    }

    else
    {
        qDebug() << "No new city has been added!";
    }
    updateCombo();
}

void MainWindow::on_FillMap_clicked()
{
    mapio->fillMap(map);
    map.draw(scene);
}

void MainWindow::on_TestAbstractMap_clicked()
{
       Map testMap;
       City *a = new City("a", 0, 0);
       City *b = new City("b", 0, 100);
       City *c = new City("c", 100, 300);
       Street *s = new Street(a, b);
       Street *s2 = new Street(b, c);


       qDebug() << "MapTest: Start Test of the Map";
       {
           qDebug() << "MapTest: adding wrong street";
           bool t1 = testMap.addStreet(s);
           if (t1) {
               qDebug() << "-Error: Street should not bee added, if cities have not been added.";
           }
       }

       {
           qDebug() << "MapTest: adding correct street";
           testMap.addCity(a);
           testMap.addCity(b);
           bool t1 = testMap.addStreet(s);
           if (!t1) {
               qDebug() << "-Error: It should be possible to add this street.";
           }
       }

       {
           qDebug() << "MapTest: findCity";
           City* city = testMap.findCity("a");
           if (city != a)
               qDebug() << "-Error: City a could not be found.";

           city = testMap.findCity("b");
           if (city != b)
               qDebug() << "-Error: City b could not be found.";

           city = testMap.findCity("c");
           if (city != nullptr)
               qDebug() << "-Error: If city could not be found 0 should be returned.";
       }

       testMap.addCity(c);
       testMap.addStreet(s2);

       {
           qDebug() << "MapTest: getOppositeCity";
           const City *city = testMap.getOppositeCity(s, a);
           if (city != b)
               qDebug() << "-Error: Opposite city should be b.";

           city = map.getOppositeCity(s, c);
           if (city != nullptr)
               qDebug() << "-Error: Opposite city for a city which is not linked by given street should be 0.";
       }

       {
           qDebug() << "MapTest: streetLength";
           double l = testMap.getLength(s2);
           double expectedLength = 223.6;
           // compare doubles with 5% tolerance
           if (l < expectedLength * 0.95 || l > expectedLength *1.05)
               qDebug() << "-Error: Street Length is not equal to the expected.";

       }

       {
           qDebug() << "MapTest: getStreetList";
           QVector<Street*> streetList1 = testMap.getStreetList(a);
           QVector<Street*> streetList2 = testMap.getStreetList(b);
           if (streetList1.size() != 1) {
               qDebug() << "-Error: One street should be found for city a.";
           }
           else if (*streetList1.begin() != s) {
                   qDebug() << "-Error: The wrong street has been found for city a.";
           }

           if (streetList2.size() != 2)
               qDebug() << "-Error: Two streets should be found for city b.";
       }

       qDebug() << "MapTest: End Test of the Map.";

}

void MainWindow::on_TestDijkstra_clicked()
{
    Map testMap;

    City *start = new City("start", 0, 0);
    City *transit = new City("transit", 50, 50);
    City *target = new City("target", 0, 100);
    testMap.addCity(start);
    testMap.addCity(transit);
    testMap.addCity(target);

    Street *testStreet1 = new Street(start, transit);
    Street *testStreet2 = new Street(transit, target);
    testMap.addStreet(testStreet1);
    testMap.addStreet(testStreet2);

    testMap.draw(scene);

    QVector<Street*> shortest_path = Dijkstra::search(testMap, start->getName(), target->getName());

    for(auto it = shortest_path.begin(); it != shortest_path.end(); it++)
    {
        (*it)->strassen_id();
    }

    for(auto it = shortest_path.begin(); it != shortest_path.end(); it++)
        {
            (*it)->drawRed(scene);
        }
}

void MainWindow::updateCombo()
{
    QVector<City*> temp = map.getCityList();

    ui->comboBox_1->clear();
    ui->comboBox_2->clear();

    for(auto it = temp.begin(); it != temp.end(); it++)
    {
        ui->comboBox_1->addItem((*it)->getName());
        ui->comboBox_2->addItem((*it)->getName());
    }
}


void MainWindow::on_find_shortestpath_clicked()
{
    QString start = ui->comboBox_1->currentText();
    QString target = ui->comboBox_2->currentText();

    if (start == target)
    {
        qDebug() << "please enter a valid destination";
        return;
    }


    QVector<Street*> shortest_path = Dijkstra::search(map, start, target);

    for(auto it = shortest_path.begin(); it != shortest_path.end(); it++)
    {
        (*it)->strassen_id();
    }

    for(auto it = shortest_path.begin(); it != shortest_path.end(); it++)
        {
            (*it)->drawRed(scene);
        }
}

void MainWindow::on_AddStreet_clicked()
{
    Dialog dialog;
    int i = dialog.exec();
    qDebug() << "Der Rückgabewert: " << i;


    if (i == 1)
    {
        QString Name1 = dialog.getgorad1Name();
        QString Name2 = dialog.getgorad2Name();

        if(map.findCity(Name1) == nullptr || map.findCity(Name2) == nullptr)
        {
            qDebug() << "please enter valid cities!";
            return;
        }

        City* gorad1 = map.findCity(Name1);
        City* gorad2 = map.findCity(Name2);

        Street* strasse = new Street(gorad1, gorad2);
        //qDebug() << "street adition succedded!";
        if(map.addStreet(strasse))
        {
            //qDebug() << "Street has been found";
            strasse->draw(scene);
        }
    }

    else
    {
        qDebug() << "No new street has been added!";
    }
}

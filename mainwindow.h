#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QComboBox>
#include "map.h"
#include "mapio.h"
#include "mapionrw.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_stpushButton_test_clicked();

    void on_actionExit_triggered();

    void on_actionClear_Scene_triggered();

    void on_actionAbout_triggered();

    void on_test_draw_city_clicked();

    void on_TestMap_clicked();

    void on_TestStreet_clicked();

    void on_checkBox_clicked();

    void on_AddCity_clicked();

    void on_FillMap_clicked();

    void on_TestAbstractMap_clicked();

    void on_TestDijkstra_clicked();

    void on_find_shortestpath_clicked();

    void on_AddStreet_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    Map map;
    MapIo* mapio;
    void updateCombo();
};

#endif // MAINWINDOW_H

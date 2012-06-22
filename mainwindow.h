#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:

    Ui::MainWindow *ui;

public slots:
    void numChanged(int num, bool vert, bool multi, bool full);
    void generation();
    void drawSlot();
    void stopdrawSlot();
    void enableon();
    void enableof();
    void load();
    void save();
    void saveresult();
signals:
    void generetePoints(int num, bool vert, bool multi, bool full);
    void loadFromFile(QString file);
    void saveToFile(QString file);
    void saveResultToFile(QString file);
    void drawSignal();
    void stopdrawSignal();
};

#endif // MAINWINDOW_H

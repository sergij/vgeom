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
    void numChanged(int num);
    void generation();
    void enableon();
    void enableof();
    void load();
    void save();
signals:
    void generetePoints(int num);
    void loadFromFile(QString file);
    void saveToFile(QString file);
};

#endif // MAINWINDOW_H

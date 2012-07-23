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
    void generetePointsMainWindowSlot(int num, bool vert, bool multi, bool full);
    void generationMainWindowSlot();
    void drawMainWindowSlot();
    void stopDrawMainWindowSlot();
    void enableToolsOnMainWindowSlot();
    void enableToolsOfMainWindowSlot();
    void loadFromFileMainWindowSlot();
    void saveToFileMainWindowSlot();
    void saveResultToFileMainWindowSlot();
signals:
    void generetePointsMainWindowSignal(int num, bool vert, bool multi, bool full);
    void loadFromFileMainWindowSignal(QString file);
    void saveToFileMainWindowSignal(QString file);
    void saveResultToFileMainWindowSignal(QString file);
    void drawMainWindowSignal();
    void stopDrawMainWindowSignal();
};

#endif // MAINWINDOW_H

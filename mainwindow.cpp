#include "mainwindow.h"
#include "generator.h"
#include <iostream>
#include <QtGui/QPalette>
#include <QtGui/QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->setCentralWidget(ui->area);

    // no points - no actions
    enableToolsOfMainWindowSlot();

    connect( ui->actionRandom, SIGNAL(triggered()), this, SLOT(generationMainWindowSlot()));
    connect(this, SIGNAL(generetePointsMainWindowSignal(int, bool, bool, bool)), this, SLOT(enableToolsOnMainWindowSlot()));


    // connect to Area slots
    connect(this, SIGNAL(generetePointsMainWindowSignal(int, bool, bool, bool)), ui->area, SLOT(generetePointsAreaSlot(int, bool, bool, bool)));
    connect(this, SIGNAL(generetePointsMainWindowSignal(int, bool, bool, bool)), ui->area, SLOT(pauseAreaSlot()));

    connect(ui->toolBar->forwardstepAction, SIGNAL(triggered()), ui->area, SLOT(forwardStepAreaSlot()));
    connect(ui->toolBar->backstepAction, SIGNAL(triggered()), ui->area, SLOT(backStepAreaSlot()));
    connect(ui->toolBar->forwardstepsAction, SIGNAL(triggered()), ui->area, SLOT(forwardStepsAreaSlot()));
    connect(ui->toolBar->backstepsAction, SIGNAL(triggered()), ui->area, SLOT(backStepsAreaSlot()));
    connect(ui->toolBar->qforwardstepsAction, SIGNAL(triggered()), ui->area, SLOT(qforwardStepsAreaSlot()));
    connect(ui->toolBar->qbackstepsAction, SIGNAL(triggered()), ui->area, SLOT(qbackStepsAreaSlot()));

    connect(ui->toolBar->pauseAction, SIGNAL(triggered()), ui->area, SLOT(pauseAreaSlot()));
    connect(ui->toolBar->stopAction, SIGNAL(triggered()), ui->area, SLOT(stopAreaSlot()));
    connect(ui->toolBar->finishAction, SIGNAL(triggered()), ui->area, SLOT(finishAreaSlot()));

    // files control
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFromFileMainWindowSlot()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveToFileMainWindowSlot()));
    connect(ui->actionSaveResult, SIGNAL(triggered()), this, SLOT(saveResultToFileMainWindowSlot()));

    // draw control
    connect(ui->actionDraw, SIGNAL(triggered()), this, SLOT(drawMainWindowSlot()));
    connect(ui->actionStopDraw, SIGNAL(triggered()), this, SLOT(stopDrawMainWindowSlot()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->area, SLOT(redoAreaSlot()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->area, SLOT(undoAreaSlot()));

    connect(this, SIGNAL(drawMainWindowSignal()), ui->area, SLOT(pauseAreaSlot()));
    connect(this, SIGNAL(drawMainWindowSignal()), ui->area, SLOT(drawAreaSlot()));
    connect(this, SIGNAL(stopDrawMainWindowSignal()), ui->area, SLOT(stopDrawAreaSlot()));

    // files control
    connect(this, SIGNAL(loadFromFileMainWindowSignal(QString)), ui->area, SLOT(loadFromFileAreaSlot(QString)));
    connect(this, SIGNAL(saveToFileMainWindowSignal(QString)), ui->area, SLOT(saveToFileAreaSlot(QString)));

    // enable tools
    connect(ui->area, SIGNAL(generationFailAreaSignal()), this, SLOT(enableToolsOfMainWindowSlot()));
    connect(this, SIGNAL(loadFromFileMainWindowSignal(QString)), this, SLOT(enableToolsOnMainWindowSlot()));
    connect(this, SIGNAL(stopDrawMainWindowSignal()), this, SLOT(enableToolsOnMainWindowSlot()));
    connect(ui->toolBar->stopAction, SIGNAL(triggered()), this, SLOT(enableToolsOfMainWindowSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generetePointsMainWindowSlot(int num, bool vert, bool multi, bool full)
{
    emit generetePointsMainWindowSignal(num, vert, multi, full);
}

void MainWindow::generationMainWindowSlot()
{
    Generator* g = new Generator(this);
    if (g->exec() == QDialog::Accepted) {
    }
    delete g;
}

void MainWindow::enableToolsOfMainWindowSlot()
{
    ui->toolBar->backstepAction->setEnabled(false);
    ui->toolBar->backstepsAction->setEnabled(false);
    ui->toolBar->forwardstepAction->setEnabled(false);
    ui->toolBar->forwardstepsAction->setEnabled(false);
    ui->toolBar->pauseAction->setEnabled(false);
    ui->toolBar->stopAction->setEnabled(false);
    ui->toolBar->finishAction->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSaveResult->setEnabled(false);
    ui->toolBar->qbackstepsAction->setEnabled(false);
    ui->toolBar->qforwardstepsAction->setEnabled(false);
    ui->actionStopDraw->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);
}

void MainWindow::enableToolsOnMainWindowSlot()
{
    ui->toolBar->backstepAction->setEnabled(true);
    ui->toolBar->backstepsAction->setEnabled(true);
    ui->toolBar->forwardstepAction->setEnabled(true);
    ui->toolBar->forwardstepsAction->setEnabled(true);
    ui->toolBar->pauseAction->setEnabled(true);
    ui->toolBar->stopAction->setEnabled(true);
    ui->toolBar->finishAction->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSaveResult->setEnabled(true);
    ui->toolBar->qbackstepsAction->setEnabled(true);
    ui->toolBar->qforwardstepsAction->setEnabled(true);
}

void MainWindow::loadFromFileMainWindowSlot()
{
    QString file = QFileDialog::getOpenFileName(0, "Select file", "", "*.txt");
    if (file != NULL) emit loadFromFileMainWindowSignal(file);
}

void MainWindow::saveToFileMainWindowSlot()
{
    QString file = QFileDialog::getSaveFileName(0, "Select file", "", "*.txt");
    if (file != NULL) emit saveToFileMainWindowSignal(file);
}


void MainWindow::saveResultToFileMainWindowSlot()
{
    QString file = QFileDialog::getSaveFileName(0, "Select file", "", "*.txt");
    if (file != NULL) emit saveResultToFileMainWindowSignal(file);
}

void MainWindow::drawMainWindowSlot() {
    ui->actionDraw->setEnabled(false);
    ui->actionStopDraw->setEnabled(true);
    ui->actionRedo->setEnabled(true);
    ui->actionUndo->setEnabled(true);
    emit drawMainWindowSignal();
}

void MainWindow::stopDrawMainWindowSlot() {
    ui->actionDraw->setEnabled(true);
    ui->actionStopDraw->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    emit stopDrawMainWindowSignal();
}


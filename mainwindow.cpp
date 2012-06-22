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

    enableof();
    ui->actionStop_Draw->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);

    connect( ui->actionRandom, SIGNAL(triggered()), this, SLOT(generation()));
    connect(this, SIGNAL(generetePoints(int, bool, bool, bool)), ui->area, SLOT(generetePoints(int, bool, bool, bool)));
    connect(this, SIGNAL(generetePoints(int, bool, bool, bool)), this, SLOT(enableon()));
    connect(ui->toolBar->forwardstepAction, SIGNAL(triggered()), ui->area, SLOT(forwardstep()));
    connect(ui->toolBar->backstepAction, SIGNAL(triggered()), ui->area, SLOT(backstep()));
    connect(ui->toolBar->forwardstepsAction, SIGNAL(triggered()), ui->area, SLOT(forwardsteps()));
    connect(ui->toolBar->backstepsAction, SIGNAL(triggered()), ui->area, SLOT(backsteps()));
    connect(ui->toolBar->qforwardstepsAction, SIGNAL(triggered()), ui->area, SLOT(qforwardsteps()));
    connect(ui->toolBar->qbackstepsAction, SIGNAL(triggered()), ui->area, SLOT(qbacksteps()));
    connect(this, SIGNAL(generetePoints(int, bool, bool, bool)), ui->area, SLOT(pause()));
    connect(ui->toolBar->pauseAction, SIGNAL(triggered()), ui->area, SLOT(pause()));
    connect(ui->toolBar->stopAction, SIGNAL(triggered()), ui->area, SLOT(stop()));
    connect(ui->toolBar->finishAction, SIGNAL(triggered()), ui->area, SLOT(finish()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSaveResult, SIGNAL(triggered()), this, SLOT(saveresult()));
    connect(ui->toolBar->stopAction, SIGNAL(triggered()), this, SLOT(enableof()));

    connect(ui->area, SIGNAL(generationfail()), this, SLOT(enableof()));

    connect(ui->actionDraw, SIGNAL(triggered()), this, SLOT(drawSlot()));
    connect(ui->actionStop_Draw, SIGNAL(triggered()), this, SLOT(stopdrawSlot()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->area, SLOT(redo()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->area, SLOT(undo()));

    connect(this, SIGNAL(drawSignal()), ui->area, SLOT(pause()));
    connect(this, SIGNAL(stopdrawSignal()), this, SLOT(enableon()));

    connect(this, SIGNAL(loadFromFile(QString)), ui->area, SLOT(load(QString)));
    connect(this, SIGNAL(saveToFile(QString)), ui->area, SLOT(save(QString)));
    connect(this, SIGNAL(loadFromFile(QString)), this, SLOT(enableon()));

    connect(this, SIGNAL(drawSignal()), ui->area, SLOT(draw()));
    connect(this, SIGNAL(stopdrawSignal()), ui->area, SLOT(stopdraw()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numChanged(int num, bool vert, bool multi, bool full)
{
    emit generetePoints(num, vert, multi, full);
}

void MainWindow::generation()
{
    Generator* g = new Generator(this);
    if (g->exec() == QDialog::Accepted) {
    }
    delete g;
}

void MainWindow::enableof()
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
}

void MainWindow::enableon()
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

void MainWindow::load()
{
    QString file = QFileDialog::getOpenFileName(0, "Select file", "", "*.txt");
    if (file != NULL) emit loadFromFile(file);
}

void MainWindow::save()
{
    QString file = QFileDialog::getSaveFileName(0, "Select file", "", "*.txt");
    if (file != NULL) emit saveToFile(file);
}


void MainWindow::saveresult()
{
    QString file = QFileDialog::getSaveFileName(0, "Select file", "", "*.txt");
    if (file != NULL) emit saveResultToFile(file);
}

void MainWindow::drawSlot() {
    ui->actionDraw->setEnabled(false);
    ui->actionStop_Draw->setEnabled(true);
    ui->actionRedo->setEnabled(true);
    ui->actionUndo->setEnabled(true);
    emit drawSignal();
}

void MainWindow::stopdrawSlot() {
    ui->actionDraw->setEnabled(true);
    ui->actionStop_Draw->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    emit stopdrawSignal();
}


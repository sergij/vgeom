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

    QPalette pal = ui->area->palette();
    pal.setColor(QPalette::Background, Qt::green);
    ui->area->setPalette(pal);

    ui->backstep->setEnabled(false);
    ui->backsteps->setEnabled(false);
    ui->forwardstep->setEnabled(false);
    ui->forwardsteps->setEnabled(false);
    ui->pause->setEnabled(false);
    connect( ui->generation, SIGNAL(clicked()), this, SLOT(generation()));
    connect(this, SIGNAL(generetePoints(int)), ui->area, SLOT(generetePoints(int)));
    connect(this, SIGNAL(generetePoints(int)), this, SLOT(enableon()));
    connect(ui->forwardstep, SIGNAL(clicked()), ui->area, SLOT(forwardstep()));
    connect(ui->backstep, SIGNAL(clicked()), ui->area, SLOT(backstep()));
    connect(ui->forwardsteps, SIGNAL(clicked()), ui->area, SLOT(forwardsteps()));
    connect(ui->backsteps, SIGNAL(clicked()), ui->area, SLOT(backsteps()));
    connect(this, SIGNAL(generetePoints(int)), ui->area, SLOT(pause()));
    connect(ui->pause, SIGNAL(clicked()), ui->area, SLOT(pause()));
    connect(ui->stop, SIGNAL(clicked()), ui->area, SLOT(stop()));
    connect(ui->finish, SIGNAL(clicked()), ui->area, SLOT(finish()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(load()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->stop, SIGNAL(clicked()), this, SLOT(enableof()));

    connect(this, SIGNAL(loadFromFile(QString)), ui->area, SLOT(load(QString)));
    connect(this, SIGNAL(saveToFile(QString)), ui->area, SLOT(save(QString)));
    connect(this, SIGNAL(loadFromFile(QString)), this, SLOT(enableon()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numChanged(int num)
{
    emit generetePoints(num);
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
    ui->backstep->setEnabled(false);
    ui->backsteps->setEnabled(false);
    ui->forwardstep->setEnabled(false);
    ui->forwardsteps->setEnabled(false);
    ui->pause->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->finish->setEnabled(false);
    ui->save->setEnabled(false);
}

void MainWindow::enableon()
{
    ui->backstep->setEnabled(true);
    ui->backsteps->setEnabled(true);
    ui->forwardstep->setEnabled(true);
    ui->forwardsteps->setEnabled(true);
    ui->pause->setEnabled(true);
    ui->stop->setEnabled(true);
    ui->finish->setEnabled(true);
    ui->save->setEnabled(true);
}

void MainWindow::load()
{
    QString file = QFileDialog::getOpenFileName(0, "Choose file", "", "*.txt");
    if (file != NULL) emit loadFromFile(file);
}

void MainWindow::save()
{
    QString file = QFileDialog::getSaveFileName(0, "Choose file", "", "*.txt");
    if (file != NULL) emit saveToFile(file);
}



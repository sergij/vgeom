#include "generator.h"
#include "ui_generator.h"

Generator::Generator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);

    ui->numberScroll->setRange (0, 50);
    ui->numberScroll->setSingleStep (1);
    ui->numberScroll->setSliderPosition (10);

    ui->numberLabel->setText(QString("10"));

    connect(ui->numberScroll, SIGNAL(valueChanged( int ) ), SLOT(numChanged( int )));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(this, SIGNAL(generatePoints(int)), parent, SLOT(numChanged( int )));
}

Generator::~Generator()
{
    delete ui;
}

void Generator::numChanged(int num)
{
    ui->numberLabel->setText(QString::number(num));
}


void Generator::generate() {
    emit generatePoints(ui->numberScroll->value());
}


#include "generator.h"
#include "ui_generator.h"

Generator::Generator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Generator)
{
    ui->setupUi(this);

    ui->numberScroll->setRange (2, 50);
    ui->numberScroll->setSingleStep (1);
    ui->numberScroll->setSliderPosition (10);

    ui->numberLabel->setText(QString("10"));

    connect(ui->numberScroll, SIGNAL(valueChanged( int ) ), SLOT(generatePointsGeneratorSlot( int )));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(generateGeneratorSlot()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(this, SIGNAL(generatePointsGeneratorSignal(int, bool, bool, bool)), parent, SLOT(generetePointsMainWindowSlot( int, bool, bool, bool )));
}

Generator::~Generator()
{
    delete ui;
}

void Generator::generatePointsGeneratorSlot(int num)
{
    ui->numberLabel->setText(QString::number(num));
}


void Generator::generateGeneratorSlot() {
    emit generatePointsGeneratorSignal(ui->numberScroll->value(), ui->vert->isChecked(), ui->multi->isChecked(), ui->full->isChecked());
}


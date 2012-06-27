#ifndef GENERATOR_H
#define GENERATOR_H

#include <QDialog>

namespace Ui {
class Generator;
}

class Generator : public QDialog
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = 0);
    ~Generator();

private:
    Ui::Generator *ui;

public slots:
    void generatePointsGeneratorSlot(int num);
    void generateGeneratorSlot();
signals:
    void generatePointsGeneratorSignal(int num, bool vert, bool multi, bool full);

};

#endif // GENERATOR_H

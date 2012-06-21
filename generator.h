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
    void numChanged(int num);
    void generate();
signals:
    void generatePoints(int num);

};

#endif // GENERATOR_H

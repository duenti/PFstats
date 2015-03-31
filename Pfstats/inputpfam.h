#ifndef INPUTPFAM_H
#define INPUTPFAM_H

#include <QDialog>

namespace Ui {
class InputPFAM;
}

class InputPFAM : public QDialog
{
    Q_OBJECT

public:
    explicit InputPFAM(QWidget *parent = 0);
    ~InputPFAM();
    QString getResult();

private slots:
    void on_btnFetch_clicked();

private:
    Ui::InputPFAM *ui;
    QString pfam;
};

#endif // INPUTPFAM_H

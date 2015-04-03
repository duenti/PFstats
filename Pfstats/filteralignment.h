#ifndef FILTERALIGNMENT_H
#define FILTERALIGNMENT_H

#include <QDialog>

namespace Ui {
class FilterAlignment;
}

class FilterAlignment : public QDialog
{
    Q_OBJECT

public:
    explicit FilterAlignment(QWidget *parent = 0);
    ~FilterAlignment();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::FilterAlignment *ui;
};

#endif // FILTERALIGNMENT_H

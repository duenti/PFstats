#include "filteralignment.h"
#include "ui_filteralignment.h"
#include <QMessageBox>

FilterAlignment::FilterAlignment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterAlignment)
{
    ui->setupUi(this);
}

FilterAlignment::~FilterAlignment()
{
    delete ui;
}

void FilterAlignment::on_buttonBox_accepted()
{
    //Validação
    bool ok;
    float minCover, minId, maxId;

    if(ui->cmbRefSeq->currentText() == "" || ui->txtMinCover->text() == "" || ui->txtMinId->text() == "" || ui->txtMaxId->text() == ""){
        QMessageBox::warning(this,"Error","All fields must be filled");
        return ;
    }

    minCover = ui->txtMinCover->text().toFloat(&ok);
    if(!ok){
        QMessageBox::warning(this,"Error","Minimum cover must be numerical");
        return;
    }
    minId = ui->txtMinId->text().toFloat(&ok);
    if(!ok){
        QMessageBox::warning(this,"Error","Minimum identy must be numerical");
        return;
    }
    maxId = ui->txtMaxId->text().toFloat(&ok);
    if(!ok){
        QMessageBox::warning(this,"Error","Maximum identy must be numerical");
        return;
    }
}

void FilterAlignment::on_buttonBox_rejected()
{
    this->close();
}

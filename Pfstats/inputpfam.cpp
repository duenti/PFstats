#include "inputpfam.h"
#include "ui_inputpfam.h"
#include <QCoreApplication>
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>

InputPFAM::InputPFAM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPFAM)
{
    ui->setupUi(this);
}

InputPFAM::~InputPFAM()
{
    delete ui;
}

void InputPFAM::on_btnFetch_clicked()
{
    //Trava o botão para não chamar o evento mais de uma vez
    ui->btnFetch->setEnabled(false);

    //Verificação de Dados
    if(ui->txtAccession->text() == ""){
        QMessageBox::warning(this,"Preencha todos os campos","Preencha todos os campos");
        return ;
    }

    //Create URL
    QString url = "http://pfam.xfam.org/family/" + ui->txtAccession->text() + "/alignment/";

    if(ui->radioButton->isChecked()) url += "seed/format?format=pfam&alnType=seed&order=";
    else url += "full/format?format=pfam&alnType=full&order=";

    if(ui->radioButton_3->isChecked()) url += "t&case=";
    else url += "a&case=";

    if(ui->radioButton_5->isChecked()) url += "l&gaps=";
    else url += "u&gaps=";

    if(ui->radioButton_7->isChecked()) url += "dashes&download=0";
    else if(ui->radioButton_8->isChecked()) url += "dots&download=0";
    else if(ui->radioButton_9->isChecked()) url += "default&download=0";
    else url += "none&download=0";

    QUrl qurl = url;
    QNetworkAccessManager manager;
    QNetworkRequest request(qurl);
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //qDebug(reply->readAll());
    pfam = reply->readAll();
    this->close();
}

QString InputPFAM::getResult(){
    return pfam;
}

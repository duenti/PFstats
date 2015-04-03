#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputpfam.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QtNetwork>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Seta Wizard como false
    wizard = false;

    //Bloqueia botões do Wizard
    changeWizardCmds(false);

    //Conecta Slots
    connect(ui->actionInput_Alignment,SIGNAL(triggered()),this,SLOT(inputAlignment_triggered()));
    connect(ui->actionFetch_From_PFAM,SIGNAL(triggered()),this,SLOT(fetchPFAM_triggered()));
    connect(ui->actionExport_Alignment,SIGNAL(triggered()),this,SLOT(exportAlignment_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeWizardCmds(bool bl){
    ui->cmdAdvance->setVisible(bl);
    ui->cmdBack->setVisible(bl);
    ui->cmdMain->setVisible(bl);
}

void MainWindow::inputAlignment_triggered(){
    //Abre arquivo para leitura
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("TEXT Files (*.txt *.pfam)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    //Limpa a textBrowser
    //ui->textBrowser->clear();

    //Add na Lista
    bool same = false;
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(fileName ==  ui->listWidget->item(i)->text()) same = true;
    }
    if(!same) ui->listWidget->addItem(fileName);

    //lê arquivo
   /*
    QTextStream in(&file);
    while (!in.atEnd()) {
         ui->textBrowser->append(in.readLine());
    }
    file.close();
*/
}

void MainWindow::fetchPFAM_triggered(){
    InputPFAM inputpfam;
    inputpfam.setModal(true);
    inputpfam.exec();
    //QMessageBox::information(this,"a",inputpfam.getResult());

    //Limpa a textBrowser
    //ui->textBrowser->clear();

    //ui->textBrowser->append(inputpfam.getResult());

}

void MainWindow::exportAlignment_triggered(){
    //Abre janela para salvar arquivo atualmente aberto
    QString filename = QFileDialog::getSaveFileName(this,tr("Export File"),"/home",tr("TEXT Files (*.txt *.pfam)"));

    //Add na Lista
    bool same = false;
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(filename ==  ui->listWidget->item(i)->text()) same = true;
    }
    if(!same) ui->listWidget->addItem(filename);

    //Salva em arquivo
    QFile f(filename);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&f);
    //out << ui->textBrowser->toPlainText();
    f.close();
}

void MainWindow::on_cmdStartWizard_clicked()
{
    //Diz que usuario esta executando wizard
    wizard = true;

    //Ativa botões do Wizard
    changeWizardCmds(true);

    //Muda para tela 1
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_cmdMain_clicked()
{
    ui->cmdMain->setEnabled(false);

    //Apaga botões do Wizard
    changeWizardCmds(false);

    //Muda para tela 0
    ui->stackedWidget->setCurrentIndex(0);

    ui->cmdMain->setEnabled(true);
}

void MainWindow::on_cmdBack_clicked()
{
    ui->cmdBack->setEnabled(false);

    int ctIx = ui->stackedWidget->currentIndex();

    if(ctIx == 1){
        //Apaga botões do Wizard
        changeWizardCmds(false);
    }
    ui->stackedWidget->setCurrentIndex(ctIx-1);

    ui->cmdBack->setEnabled(true);
}

void MainWindow::on_cmdAdvance_clicked()
{
    ui->cmdAdvance->setEnabled(false);

    int ctIx = ui->stackedWidget->currentIndex();
     ui->stackedWidget->setCurrentIndex(ctIx+1);


    ui->cmdAdvance->setEnabled(true);
}

void MainWindow::on_cmdOpen_clicked()
{
    ui->cmdOpen->setEnabled(false);

    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("TEXT Files (*.txt *.pfam)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    //Add na Lista
    bool same = false;
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(fileName ==  ui->listWidget->item(i)->text()) same = true;
    }
    if(!same) ui->listWidget->addItem(fileName);

    ui->cmdOpen->setEnabled(true);
}

void MainWindow::on_cmdFetch_clicked()
{
    ui->cmdFetch->setEnabled(false);

    //Validação de Dados
    if(ui->txtAccession->text() == ""){
        QMessageBox::warning(this,"Preencha todos os campos","Preencha todos os campos");
        return ;
    }

    //Monta URL
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

    //Faz a conexão
    QUrl qurl = url;
    QNetworkAccessManager manager;
    QNetworkRequest request(qurl);
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //qDebug(reply->readAll());
    QString pfam = reply->readAll();

    //Salvar arquivo
    if(pfam != ""){
        //Abre janela para salvar arquivo atualmente aberto
        QString filename = QFileDialog::getSaveFileName(this,tr("Export File"),"/home",tr("TEXT Files (*.txt *.pfam)"));

        //Add na Lista
        bool same = false;
        for(int i = 0; i < ui->listWidget->count(); i++){
            if(filename ==  ui->listWidget->item(i)->text()) same = true;
        }
        if(!same) ui->listWidget->addItem(filename);

        //Salva em arquivo
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&f);
        out << pfam;
        f.close();
    }

    ui->cmdFetch->setEnabled(true);
}

void MainWindow::on_cmdApplyFilter_clicked()
{
    ui->cmdApplyFilter->setEnabled(false);

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


    ui->cmdApplyFilter->setEnabled(true);
}

void MainWindow::on_cmdFetchPDB_clicked()
{
    ui->cmdFetchPDB->setEnabled(false);

    //Validação de Dados
    if(ui->txtPDBName->text() == ""){
        QMessageBox::warning(this,"Preencha todos os campos","Preencha todos os campos");
        return ;
    }

    //Montar URL
    QString url = "http://pdb.org/pdb/files/" + ui->txtPDBName->text() + ".pdb";

    //Faz a conexão
    QUrl qurl = url;
    QNetworkAccessManager manager;
    QNetworkRequest request(qurl);
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //qDebug(reply->readAll());
    QString pdb = reply->readAll();

    if(pdb==""){
        QMessageBox::warning(this,"Fetching Failed","PDB não encontrado");
        return ;
    }

    ui->txtPDBfilepath->setText(url);

    ui->cmdFetchPDB->setEnabled(true);
}

void MainWindow::on_cmdPDBfromFile_clicked()
{
    ui->cmdPDBfromFile->setEnabled(false);

    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("TEXT Files (*.txt *.pfam *.pdb)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    ui->txtPDBfilepath->setText(fileName);

    ui->cmdPDBfromFile->setEnabled(true);
}

void MainWindow::on_cmdConservation_clicked()
{
    ui->cmdConservation->setEnabled(false);

    //Validação
    if(ui->cmbRefSeq_2->currentText() == ""){
        QMessageBox::warning(this,"Error","All fields must be filled");
        return ;
    }

    bool ok;
    int offset = ui->txtOffset->text().toInt(&ok,10);
    if(!ok){
        QMessageBox::warning(this,"Error","Offset must be integer.");
        return;
    }
    if(ui->txtChain->text().length() > 1){
        QMessageBox::warning(this,"Error","Chain must be a character.");
        return;
    }

    //Calcular a conservaçao

    ui->cmdConservation->setEnabled(true);
}

void MainWindow::on_cmdMinss_clicked()
{
    ui->cmdMinss->setEnabled(false);

    //Implementar minss e gerar o grafico
    //http://www.qcustomplot.com/index.php/tutorials/settingup

    //Exemplo
    QVector<double> x(101), y(101);
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    ui->graficMinss->addGraph();
    ui->graficMinss->graph(0)->setData(x,y);
    ui->graficMinss->yAxis->setLabel("y");
    ui->graficMinss->xAxis->setLabel("x");
    ui->graficMinss->yAxis->setRange(0,1);
    ui->graficMinss->xAxis->setRange(-1,1);
    ui->graficMinss->replot();

    ui->cmdMinss->setEnabled(true);
}

void MainWindow::on_cmdGraphPath_clicked()
{
    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("Graph Files (*.txt *.pfam *.csv)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    //Add no line edit
    ui->txtGraphPath->setText(fileName);
}

void MainWindow::on_cmdCorrelation_clicked()
{
    ui->cmdCorrelation->setEnabled(false);

    //Chamar PCalc

    //Chamar Trivcomm

    //Chamar Output

    //Chamar Adherence

    //Chamar comm2seqrenumbering

    ui->cmdCorrelation->setEnabled(true);
}

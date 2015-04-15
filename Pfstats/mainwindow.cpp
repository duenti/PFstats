#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QtNetwork>
#include <sstream>

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

void MainWindow::startStacked(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::resetObjects(){
    ui->txtAccession->clear();
    ui->cmbRefSeq->setCurrentIndex(0);
    ui->txtMinCover->setValue(0.8);
    ui->txtMinId->setValue(0.15);
    ui->txtMaxId->setValue(0.8);
    ui->txtPDBName->clear();
    ui->txtPDBfilepath->clear();
    ui->cmbRefSeq_2->setCurrentIndex(0);
    ui->lstRefSeqs->clearSelection();
    ui->txtOffset->clear();
    ui->txtChain->clear();
    ui->txtNoAlignments->setValue(100);
    ui->graficMinss->clearGraphs();
    ui->txtMinScore->setValue(10);
    ui->txtMinssFraction->setValue(0.2);
    ui->txtMinDeltaFreq->setValue(0.3);
    ui->txtGraphPath->clear();
}

vector<string> MainWindow::split(string text, char sep){
    int start = 0, end = 0;
    vector<string> tokens;

    while((end = text.find(sep,start)) != string::npos){
        tokens.push_back(text.substr(start,end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));

    return tokens;
}

string MainWindow::makeNewPath(string oldPath, string fileSufix){
    string finalPath = "";
    //if(oldPath[0] == '/') finalPath += '/'; //Para linux

    //Trabalha o diretorio
    vector<string> tokens = this->split(oldPath,'/');

    for(int i = 0; i < tokens.size()-1; i++){
        finalPath += tokens[i] + "/";
    }
    //QMessageBox::information(this,"a","tokens ");

    //Trabalha o arquivo
    string file = tokens[tokens.size()-1];
    vector<string> tkFile = this->split(file,'.');

    for(int i = 0; i < tkFile.size()-1; i++){
        finalPath += tkFile[i];
    }
    //QMessageBox::information(this,"a","tokensF ");

    //Monta path final
    finalPath += "_" + fileSufix + "." + tkFile[tkFile.size()-1];

    return finalPath;
}

char MainWindow::num2aa(int n){
    if(n==1) return ('A');
    if(n==2) return ('C');
    if(n==3) return ('D');
    if(n==4) return ('E');
    if(n==5) return ('F');
    if(n==6) return ('G');
    if(n==7) return ('H');
    if(n==8) return ('I');
    if(n==9) return ('K');
    if(n==10) return ('L');
    if(n==11) return ('M');
    if(n==12) return ('N');
    if(n==13) return ('P');
    if(n==14) return ('Q');
    if(n==15) return ('R');
    if(n==16) return ('S');
    if(n==17) return ('T');
    if(n==18) return ('V');
    if(n==19) return ('W');
    if(n==20) return ('Y');
    return('-');
}

int MainWindow::GetOffsetFromSeqName(string seqname){
    bool found=false;
    string offsetstr;
    int c1=0;

    while (c1<seqname.length()){
        if(seqname[c1]=='/'){
            found=true;
            c1++;
            break;
        }
        c1++;
    }
    if (!found) return 0;
    while (c1<seqname.length()){
        if(seqname[c1]=='-') break;
        else offsetstr+=seqname[c1];
        c1++;
    }
    return(atoi(offsetstr.c_str())-1);
}

void MainWindow::alignfilter(Alignment align, float occupancy, float minId, float maxId, int refseq){
    string outputlogfilename = ui->cmbRefSeq->currentText().toStdString() + "_alignfilter.log";
    FILE *outputlog;

    outputlog=fopen(outputlogfilename.c_str(),"w+");

    fprintf(outputlog,"======================================\n");
    fprintf(outputlog,"=                                    =\n");
    fprintf(outputlog,"=     PROTEIN FAMILY STATISTICS      =\n");
    fprintf(outputlog,"=         Alignment filtering        =\n");
    fprintf(outputlog,"=                                    =\n");
    fprintf(outputlog,"======================================\n");
    fprintf(outputlog,"=                                    =\n");
    fprintf(outputlog,"= Lucas Bleicher, Richard C. Garratt =\n");
    fprintf(outputlog,"=       lbleicher@icb.ufmg.br        =\n");
    fprintf(outputlog,"=        richard@if.sc.usp.br        =\n");
    fprintf(outputlog,"=                                    =\n");
    fprintf(outputlog,"=   Bleicher, Lemke, Garratt (2011)  =\n");
    fprintf(outputlog,"=  Using amino acid correlation and  =\n");
    fprintf(outputlog,"=  community detection algorithms to =\n");
    fprintf(outputlog,"=  identify functional determinants  =\n");
    fprintf(outputlog,"=        in protein families         =\n");
    fprintf(outputlog,"=   PLoS One 6(12): e27786 (2011)    =\n");
    fprintf(outputlog,"=                                    =\n");
    fprintf(outputlog,"======================================\n");
    fprintf(outputlog,"\n\nParameters:\n   minimum occupancy: %f\n   minimum identity: %f\n   maximum identity: %f\n",occupancy,minId,maxId);

    ostringstream buffer;
    buffer << "occ" << (int)(occupancy*100) << "min" << (int)(minId*100) << "max" << (int)(maxId*100);
    string path = this->makeNewPath(ui->listWidget->currentItem()->text().toStdString(),buffer.str());

    //QMessageBox::information(this,"DEBUG",refseq);

    //Calculate
    string firstrefseq = align.sequences[refseq];
    string firstrefseqname = align.sequencenames[refseq];
    align.sequences.insert(align.sequences.begin(),firstrefseq);
    align.sequencenames.insert(align.sequencenames.begin(),firstrefseqname);

    align.AlignmentTrimming(occupancy,0);
    align.IdentityMinimum(minId,refseq);
    align.IdentityTrimming(maxId);

    printf("\nFirstRefSeqName: %s\n",firstrefseqname.c_str());
    if ((string)(align.sequencenames[0])!=firstrefseqname){
        align.sequences.insert(align.sequences.begin(),firstrefseq);
        align.sequencenames.insert(align.sequencenames.begin(),firstrefseqname);
    }

    align.setFilepath(path);
    //QMessageBox::information(this,"a",fullAlignment.getFilepath().c_str());
    align.AlignmentWrite(path);

    //Add na Lista
    bool same = false;
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(path.c_str() ==  ui->listWidget->item(i)->text()) same = true;
    }
    if(!same) ui->listWidget->addItem(path.c_str());

    alinhamentos.push_back(align);

}

void MainWindow::conservation(Alignment align, int refseq, int offset, char chain, string pdbfile){
    align.CalculateFrequencies();
    align.dGCalculation();
    align.dGWrite();
    align.FreqWrite();

    if(pdbfile != ""){
        vector<string> vecPath = split(align.getFilepath(),'.');
        string path = "";

        for(int i=0;i<vecPath.size()-1;i++){
            path += vecPath[i];
        }
        path += "_STRUCTURE.pdb";

        //printf("\n%s\n",path.c_str());

        align.writedGtoPDB(pdbfile, path,offset,chain,refseq);
    }

    QMessageBox::information(this,"Files Created","The files has been successfully created.");
}

//Passar vetor de indices ->currentIndex
void MainWindow::conservedresidues(Alignment align, vector<int> referencesequences, string outputFile, float minconservation){
    int c1, c2;
    float freq;
    vector<char> conservedaa;
    vector<int> conservedpos;
    vector<float> conservedfreq;

    align.CalculateFrequencies();

    for(c1 = 0; c1 < align.frequencies.size()-2; c1++){
        for(c2 = 1; c2 <=20; c2++){
            freq = (float)align.frequencies[c1][c2]/((float)align.sequences.size());
            if(freq >= minconservation){
                conservedaa.push_back(num2aa(c2));
                conservedpos.push_back(c1);
                conservedfreq.push_back(100*freq);
            }
        }
    }

    if(conservedaa.size() == 0){
        QMessageBox::information(this,"Conserved Residues", "No residues match the conservation minimum");
        return;
    }

    QFile file(outputFile.c_str());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out.setRealNumberNotation(QTextStream::FixedNotation);
    out.setRealNumberPrecision(1);

    out << "<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th><b>Sequence</b></th>";

    for (c1=0;c1<=conservedaa.size()-1;c1++){
        out << "<th><b>" << conservedaa[c1] << conservedpos[c1]+1 << " (" << conservedfreq[c1] <<")</b></th>";
    }
    out << "</tr>\n";
    for (c1=0;c1<=referencesequences.size()-1;c1++){
        out << "<tr><th><b>" << align.sequencenames[referencesequences[c1]].c_str();
        for (c2=0;c2<=conservedaa.size()-1;c2++){
            if(align.AlignNumbering2Sequence(referencesequences[c1]+1,conservedpos[c2]) ==0){
                out << "<th><font color=#FF0000>-</font></th>";
            }else{
                if (align.sequences[referencesequences[c1]][conservedpos[c2]]==conservedaa[c2])
                    out << "<th>" << conservedaa[c2] << align.AlignNumbering2Sequence(referencesequences[c1]+1,conservedpos[c2]) + GetOffsetFromSeqName(align.sequencenames[referencesequences[c1]]) << "</th>";
                else
                    out << "<th><font color=#FF0000>" << align.sequences[referencesequences[c1]][conservedpos[c2]] << align.AlignNumbering2Sequence(referencesequences[c1]+1,conservedpos[c2])+GetOffsetFromSeqName(align.sequencenames[referencesequences[c1]]) << "</font></th>";
            }
        }
        out << "</tr>\n";
    }
    file.close();

    QMessageBox::information(this,"Conserved Residues", "Conserved residues exported to HTML table.");
}

void MainWindow::addAlignment(string path){
    Alignment align;
    align.setFilepath(path);
    align.GetFromFile();
    alinhamentos.push_back(path);
}

bool MainWindow::checkfile(const string &name){
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

void MainWindow::changeWizardCmds(bool bl){
    ui->cmdAdvance->setEnabled(bl);
    ui->cmdBack->setEnabled(bl);
    ui->cmdMain->setEnabled(bl);
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
    //InputPFAM inputpfam;
    //inputpfam.setModal(true);
    //inputpfam.exec();
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

    //Desativa botao voltar
    ui->cmdBack->setEnabled(false);

    //Muda para tela 1
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_cmdMain_clicked()
{
    ui->cmdMain->setEnabled(false);

    //Desativa botões do Wizard
    changeWizardCmds(false);

    //Reseta campos
    resetObjects();

    //Muda para tela 0
    ui->stackedWidget->setCurrentIndex(0);

    ui->cmdMain->setEnabled(true);
}

void MainWindow::on_cmdBack_clicked()
{
    //ui->cmdBack->setEnabled(false);

    int ctIx = ui->stackedWidget->currentIndex();

    if(ctIx == 1){
        //Apaga botões do Wizard
        changeWizardCmds(false);
    }
    else if(ctIx == 2) ui->cmdBack->setEnabled(false);
    else if(ctIx == 5) ui->cmdAdvance->setEnabled(true);


    ui->stackedWidget->setCurrentIndex(ctIx-1);

    //ui->cmdBack->setEnabled(true);
}

void MainWindow::on_cmdAdvance_clicked()
{
    //ui->cmdAdvance->setEnabled(false);

    int ctIx = ui->stackedWidget->currentIndex();

    if(ctIx == 1) ui->cmdBack->setEnabled(true);
    if(ctIx == 4) ui->cmdAdvance->setEnabled(false);

    ui->stackedWidget->setCurrentIndex(ctIx+1);


    //ui->cmdAdvance->setEnabled(true);
}

void MainWindow::on_cmdOpen_clicked()
{
    ui->cmdOpen->setEnabled(false);

    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("TEXT Files (*.txt *.pfam)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->cmdOpen->setEnabled(true);
        return;
    }

    //Add na Lista
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(fileName ==  ui->listWidget->item(i)->text()){
            ui->cmdOpen->setEnabled(true);
            return;
        }
    }
    ui->listWidget->addItem(fileName);

    //Cria Alinhamento
    //addAlignment(fileName.toUtf8().constData());
    Alignment align;
    align.setFilepath(fileName.toUtf8().constData());
    align.GetFromFile();
    alinhamentos.push_back(align);

    ui->cmdOpen->setEnabled(true);
}

void MainWindow::on_cmdFetch_clicked()
{
    ui->cmdFetch->setEnabled(false);

    //Validação de Dados
    if(ui->txtAccession->text() == ""){
        QMessageBox::warning(this,"Error","You must fill all fields");
        ui->cmdFetch->setEnabled(true);
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
    if(pfam.contains("302 Found") || pfam == ""){
        QMessageBox::warning(this,"Error","PFAM File not Found");
        ui->cmdFetch->setEnabled(true);
        return ;
    }else{
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
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            ui->cmdFetch->setEnabled(true);
            return;
        }

        QTextStream out(&f);
        out << pfam;
        f.close();

        //Cria Alinhamento
        //addAlignment(fileName.toUtf8().constData());
        Alignment align;
        align.setFilepath(filename.toUtf8().constData());
        align.GetFromFile();
        alinhamentos.push_back(align);
    }

    ui->cmdFetch->setEnabled(true);
}

void MainWindow::on_cmdApplyFilter_clicked()
{
    ui->cmdApplyFilter->setEnabled(false);

    //Validação
    //bool ok;

    if(ui->cmbRefSeq->currentText() == "" || ui->txtMinCover->text() == "" || ui->txtMinId->text() == "" || ui->txtMaxId->text() == ""){
        ui->cmdApplyFilter->setEnabled(true);
        QMessageBox::warning(this,"Error","All fields must be filled");
        return ;
    }
/*
    minCover = ui->txtMinCover->text().toFloat(&ok);
    if(!ok){
        QMessageBox::warning(this,"Error","Minimum cover must be numerical");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }
    minId = ui->txtMinId->text().toFloat(&ok);
    if(!ok){
        QMessageBox::warning(this,"Error","Minimum identy must be numerical");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }
    maxId = ui->txtMaxId->text().toFloat(&ok);
    if(!ok){
        QMessageBox::warning(this,"Error","Maximum identy must be numerical");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }
    */

    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    ui->cmbRefSeq_2->setCurrentIndex(ui->cmbRefSeq->currentIndex());

    ////////////////////ALIGNFILTER////////////////////
    string inputfilename;
    float occupancy, minId, maxId;
    int refseq;

    inputfilename = ui->listWidget->currentItem()->text().toStdString();

    if(!checkfile(inputfilename)){
        QMessageBox::warning(this,"Erro","File not found");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    occupancy = ui->txtMinCover->value();
    minId = ui->txtMinId->value();
    maxId = ui->txtMaxId->value();

    Alignment fullAlignment, cutAlignment;
    fullAlignment.setFilepath(inputfilename);
    fullAlignment.GetFromFile();
    fullAlignment.CalculateFrequencies();

    refseq = ui->cmbRefSeq->currentIndex()-1;

    this->alignfilter(fullAlignment,occupancy,minId,maxId,refseq);


    ui->cmdApplyFilter->setEnabled(true);
}

void MainWindow::on_cmdFetchPDB_clicked()
{
    ui->cmdFetchPDB->setEnabled(false);

    //Validação de Dados
    if(ui->txtPDBName->text() == ""){
        QMessageBox::warning(this,"Error","You must fill all fields");
        ui->cmdFetchPDB->setEnabled(true);
        return ;
    }

    //Montar URL
    QString url = "http://www.rcsb.org/pdb/files/" + ui->txtPDBName->text() + ".pdb";
    printf("\n%s\n",url.toStdString().c_str());

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

    if(pdb.contains("302 Found") || pdb.contains("301 Moved") || pdb == ""){
        printf("\n%s",pdb.toStdString().c_str());
        QMessageBox::warning(this,"Fetching Failed","PDB not found");
        ui->cmdFetchPDB->setEnabled(true);
        return ;
    }else{
        //Abre janela para salvar arquivo atualmente aberto
        QString filename = QFileDialog::getSaveFileName(this,tr("Export File"),"/home",tr("TEXT Files (*.txt *.pdb)"));

        //Salva em arquivo
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
            ui->cmdFetch->setEnabled(true);
            return;
        }

        QTextStream out(&f);
        out << pdb;
        f.close();

        ui->txtPDBfilepath->setText(filename);
    }

    ui->cmdFetchPDB->setEnabled(true);
}

void MainWindow::on_cmdPDBfromFile_clicked()
{
    ui->cmdPDBfromFile->setEnabled(false);

    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("TEXT Files (*.txt *.pdb)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->cmdPDBfromFile->setEnabled(true);
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
        QMessageBox::warning(this,"Error","You must select a pfam input file.");
        ui->cmdConservation->setEnabled(true);
        return ;
    }

    bool ok;
    int offset = ui->txtOffset->text().toInt(&ok,10);
    if(!ok){
        QMessageBox::warning(this,"Error","Offset must be integer.");
        ui->cmdConservation->setEnabled(true);
        return;
    }
    if(ui->txtChain->text().length() > 1){
        QMessageBox::warning(this,"Error","Chain must be a character.");
        ui->cmdConservation->setEnabled(true);
        return;
    }

    //Calcular a conservaçao
    string alignfilename;
    string pdbfilename;
    char chain;
    int refseq;

    alignfilename = ui->listWidget->currentItem()->text().toStdString();
    pdbfilename = ui->txtPDBfilepath->text().toStdString();
    refseq = ui->cmbRefSeq_2->currentIndex();
    chain = ui->txtChain->text().at(0).toLatin1();

    Alignment fullAlignment;

    for(int i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            fullAlignment = alinhamentos[i];
        }
    }

    this->conservation(fullAlignment,refseq,offset,chain,pdbfilename);

    //CONSERVED RESIDUES
    vector<int> refSeqs;
    float minCons = (float)ui->txtMinConserv->value();
    QModelIndexList indexList = ui->lstRefSeqs->selectionModel()->selectedIndexes();
    for(int i = 0; i < indexList.size(); i++){
        refSeqs.push_back(indexList.at(i).row());
    }

    vector<string> vecPath = split(fullAlignment.getFilepath(),'.');
    string path = "";

    for(int i=0;i<vecPath.size()-1;i++){
        path += vecPath[i];
    }
    path += "_CONSERVEDRESIDUES.html";

    this->conservedresidues(fullAlignment,refSeqs,path,minCons);

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

void MainWindow::on_listWidget_activated(const QModelIndex &index)
{
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    vector<string> sequences;

    for(int i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            sequences = alinhamentos.at(i).getSequencesName();
            /*
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[ui->cmbRefSeq->currentIndex()-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = "" + offset;
            ui->txtOffset->setText(qoffset);
            */

            break;
        }
    }

    ui->cmbRefSeq->clear();
    ui->cmbRefSeq->addItem("");
    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("");
    ui->lstRefSeqs->clear();
    for(int i = 0; i < sequences.size(); i++){
        ui->cmbRefSeq->addItem(QString::fromStdString(sequences.at(i)));
        ui->cmbRefSeq_2->addItem(QString::fromStdString(sequences.at(i)));
        ui->lstRefSeqs->addItem(QString::fromStdString(sequences.at(i)));
    }
    ui->cmbRefSeq_2->setCurrentIndex(1);
}

void MainWindow::on_cmbRefSeq_activated(int index)
{
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    for(int i = 0; i < alinhamentos.size(); i++){
        printf("\nI = %d - SIZE = %d\n%s\n%s\n",i,alinhamentos.size(),path.c_str(),alinhamentos.at(i).getFilepath().c_str());
        if(path == alinhamentos.at(i).getFilepath()){
            //QMessageBox::information(this,"a",alinhamentos.at(i).sequencenames[index-1].c_str());
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[index-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = QString::number(offset);
            ui->txtOffset->setText(qoffset);
            break;
        }
    }
}

void MainWindow::on_cmbRefSeq_2_activated(int index)
{
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    for(int i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            //QMessageBox::information(this,"a",alinhamentos.at(i).sequencenames[index-1].c_str());
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[index-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = QString::number(offset);
            ui->txtOffset->setText(qoffset);
            break;
        }
    }
}

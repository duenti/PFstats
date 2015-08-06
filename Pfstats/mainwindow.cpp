#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QtNetwork>
#include <QString>
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
    ui->graficMinss->setVisible(false);

    //Conecta Slots
    connect(ui->actionInput_Alignment,SIGNAL(triggered()),this,SLOT(inputAlignment_triggered()));
    connect(ui->actionFetch_From_PFAM,SIGNAL(triggered()),this,SLOT(fetchPFAM_triggered()));
    connect(ui->actionExport_Alignment,SIGNAL(triggered()),this,SLOT(exportAlignment_triggered()));
    connect(ui->actionOpen_XML,SIGNAL(triggered()),this,SLOT(Open_XML_triggered()));
    connect(ui->actionAlignmentPFAM,SIGNAL(triggered()),this,SLOT(exportAlignment_PFAM()));
    connect(ui->actionAlignmentTXT,SIGNAL(triggered()),this,SLOT(exportAlignment_TXT()));
    connect(ui->actionAlignmentXML,SIGNAL(triggered()),this,SLOT(exportAlignment_XML()));
    connect(ui->actionFreqTXT,SIGNAL(triggered()),this,SLOT(exportFreqTXT()));
    connect(ui->actionFreqCSV,SIGNAL(triggered()),this,SLOT(exportFreqCSV()));
    connect(ui->actionFreqXML,SIGNAL(triggered()),this,SLOT(exportFreqXML()));
    connect(ui->actionFreqHTML,SIGNAL(triggered()),this,SLOT(exportFreqHTML()));
    connect(ui->actionFreqPercTXT,SIGNAL(triggered()),this,SLOT(exportFreqPercTXT()));
    connect(ui->actionFreqPercCSV,SIGNAL(triggered()),this,SLOT(exportFreqPercCSV()));
    connect(ui->actionFreqPercXML,SIGNAL(triggered()),this,SLOT(exportFreqPercXML()));
    connect(ui->actionFreqPercHTML,SIGNAL(triggered()),this,SLOT(exportFreqPercHTML()));
    connect(ui->actionConsResTXT,SIGNAL(triggered()),this,SLOT(exportConsResTXT()));
    connect(ui->actionConsResXML,SIGNAL(triggered()),this,SLOT(exportConsResXML()));
    connect(ui->actionConsResHTML,SIGNAL(triggered()),this,SLOT(exportConsResHTML()));
    connect(ui->actionCorrListTXT,SIGNAL(triggered()),this,SLOT(exportCorrListTXT()));
    connect(ui->actionCorrListCSV,SIGNAL(triggered()),this,SLOT(exportCorrListCSV()));
    connect(ui->actionCorrListXML,SIGNAL(triggered()),this,SLOT(exportCorrListXML()));
    connect(ui->actionCommTXT,SIGNAL(triggered()),this,SLOT(exportCommsTXT()));
    connect(ui->actionCommXML,SIGNAL(triggered()),this,SLOT(exportCommsXML()));
    connect(ui->actionCorrTablePercTXT,SIGNAL(triggered()),this,SLOT(exportCorrTablePercTXT()));
    connect(ui->actionCorrTablePercXML,SIGNAL(triggered()),this,SLOT(exportCorrTablePercXML()));
    connect(ui->actionCorrTablePercHTML,SIGNAL(triggered()),this,SLOT(exportCorrTablePercHTML()));
    connect(ui->actionCorrTableTXT,SIGNAL(triggered()),this,SLOT(exportCorrTableTXT()));
    connect(ui->actionCorrTableXML,SIGNAL(triggered()),this,SLOT(exportCorrTableXML()));
    connect(ui->actionCorrTableHTML,SIGNAL(triggered()),this,SLOT(exportCorrTableHTML()));
    connect(ui->actionAdhTXT,SIGNAL(triggered()),this,SLOT(exportAdhTXT()));
    connect(ui->actionAdhCSV,SIGNAL(triggered()),this,SLOT(exportAdhCSV()));
    connect(ui->actionAdhXML,SIGNAL(triggered()),this,SLOT(exportAdhXML()));
    connect(ui->actionAdhHTML,SIGNAL(triggered()),this,SLOT(exportAdhHTML()));
    connect(ui->actionResCommTXT,SIGNAL(triggered()),this,SLOT(exportResCommTXT()));
    connect(ui->actionResCommXML,SIGNAL(triggered()),this,SLOT(exportResCommXML()));
    connect(ui->actionResCommHTML,SIGNAL(triggered()),this,SLOT(exportResCommHTML()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startStacked(){
    ui->stackedWidget->setCurrentIndex(0);
    ui->lblHidden->setVisible(false);
}

void MainWindow::resetObjects(){
    ui->listWidget->clear();
    ui->listWidget2->clear();
    ui->txtAccession->clear();
    ui->cmbRefSeq->clear();
    ui->txtMinCover->setValue(0.8);
    ui->txtMinId->setValue(0.15);
    ui->txtMaxId->setValue(0.8);
    ui->txtPDBName->clear();
    ui->txtPDBfilepath->clear();
    ui->txtOffset->setText("0");
    ui->txtChain->setText("A");
    ui->txtMinConserv->setValue(0.8);
    ui->cmbRefSeq_2->clear();
    ui->lstRefSeqs->clear();
    ui->graficMinss->clearGraphs();
    ui->graficMinss->setVisible(false);
    ui->txtNoAlignments->setValue(100);
    ui->txtMinScore->setValue(10);
    ui->txtMinssFraction->setValue(0.2);
    ui->txtMinDeltaFreq->setValue(0.3);
    ui->txtOffset_2->setText("0");
    ui->cmbRefSeq_3->clear();
    ui->lstRefSeqs_2->clear();
    ui->checkResults1->setChecked(false);
    ui->checkResults2->setChecked(false);
    ui->checkResults3->setChecked(false);
    ui->checkResults4->setChecked(false);
    ui->checkResults5->setChecked(false);
    ui->checkResults6->setChecked(false);
    ui->checkResults7->setChecked(false);
    ui->checkResults8->setChecked(false);
    ui->checkResults9->setChecked(false);
    ui->checkResults10->setChecked(false);
    ui->lstProteinsFiltered->clear();
    ui->txtSequence->clear();
    ui->tableFreq->clearContents();
    ui->tableFreqPerc->clearContents();
    ui->tableConsRes->clear();
    ui->treeCorrelation->clear();
    ui->treeCorrelationComm->clear();
    ui->tableComm1->clear();
    ui->tableComm2->clear();
    ui->tableAdherence->clear();
    ui->tableResiduesComm->clear();

    ui->cmdNextResult->setVisible(false);
    ui->cmdBackResult->setVisible(false);
}

bool MainWindow::compareLocalWebPDB(string local, string web){
    vector<string> localVec = this->split(local,'/');
    vector<string> webVec = this->split(web,'/');

    string localfile = localVec[localVec.size()-1];
    string webfile = webVec[webVec.size()-1];

    if(localfile == webfile) return true;
    return false;
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

bool MainWindow::checkfile(const string &name){
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

void MainWindow::alignfilter(string alignPath, float occupancy, float minId, float maxId, int refseq, string refseqName, bool intermediate){
    /*
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
    buffer << "occ" << (int)(occupancy*100) << "min" << (int)(minId*100) << "max" << (int)(maxId*100);*/

    //string path = this->makeNewPath(ui->listWidget->currentItem()->text().toStdString(),buffer.str());

    //QMessageBox::information(this,"DEBUG",QString::number(refseq));

    int i = 0;
    string alignfilename = ui->listWidget->currentItem()->text().toStdString();
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    alinhamentos[i].loadFullAlignment();
    bool inter = ui->chkIntermediateFilter->isChecked();

    //Calculate
    string firstrefseq = alinhamentos[i].sequences[refseq];
    string firstrefseqname = alinhamentos[i].sequencenames[refseq];
    //printf("%s: %s\n",firstrefseq.c_str(),firstrefseqname.c_str());
    alinhamentos[i].sequences.insert(alinhamentos[i].sequences.begin(),firstrefseq);
    alinhamentos[i].sequencenames.insert(alinhamentos[i].sequencenames.begin(),firstrefseqname);
//QMessageBox::information(this,"test","1");
    alinhamentos[i].AlignmentTrimming(occupancy,0,firstrefseqname,firstrefseq,inter);
//QMessageBox::information(this,"test","2");
    alinhamentos[i].IdentityMinimum(minId,0,occupancy,firstrefseqname,firstrefseq,inter);
//QMessageBox::information(this,"test","3");
    alinhamentos[i].IdentityTrimming(maxId,occupancy,minId,0,firstrefseqname,firstrefseq);
//QMessageBox::information(this,"test","4");

    //printf("\nFirstRefSeqName: %s\n",firstrefseqname.c_str()); FILTERPARS EM VEZ DE SEQUENCES E SEQUENCESNAMES
/*
    if ((string)(alinhamentos[i].sequencenames[0])!=firstrefseqname){
        alinhamentos[i].sequences.insert(alinhamentos[i].sequences.begin(),firstrefseq);
        alinhamentos[i].sequencenames.insert(alinhamentos[i].sequencenames.begin(),firstrefseqname);
    }
*/
    vector<vector<string> > filterList = alinhamentos.at(i).getAllFilters();
    ui->listWidget2->clear();

    for(int j = 0; j < filterList.size(); j++){
        if(filterList[j][0] == "0 0 0 0") ui->listWidget2->addItem("Full Alignment");
        else ui->listWidget2->addItem(filterList[j][0].c_str());
    }

    ui->listWidget2->item(ui->listWidget2->count()-1)->setSelected(true);

    //alinhamentos[i].setFilepath(path);
    //QMessageBox::information(this,"a",fullAlignment.getFilepath().c_str());
    //alignPath.AlignmentWrite(path);
/*
    //Add na Lista
    bool same = false;
    for(int i = 0; i < ui->listWidget->count(); i++){
        if(path.c_str() ==  ui->listWidget->item(i)->text()) same = true;
    }
    if(!same) ui->listWidget->addItem(path.c_str());

    alinhamentos.push_back(alignPath);
*/
}

void MainWindow::conservation(int ai, int refseq, int offset, char chain, float minCons, string pdbfile){
    alinhamentos[ai].CalculateFrequencies();
    alinhamentos[ai].dGCalculation();
    alinhamentos[ai].dGWrite();
    alinhamentos[ai].FreqWrite();

    if(pdbfile != ""){
        vector<string> vecPath = split(alinhamentos[ai].getFilepath(),'.');
        string path = "";

        for(int i=0;i<vecPath.size()-1;i++){
            path += vecPath[i];
        }
        path += "_STRUCTURE.pdb";

        //printf("\n%s\n",path.c_str());

        alinhamentos[ai].writedGtoPDB(pdbfile, path,offset,chain,refseq);
    }

    if(ui->listWidget2->currentItem() == NULL)
        alinhamentos[ai].addParameter("conservation","Full Alignment",refseq, offset, chain, minCons);
    else
        alinhamentos[ai].addParameter("conservation", ui->listWidget2->currentItem()->text().toStdString(), refseq, offset, chain, minCons);

    QMessageBox::information(this,"Files Created","The files has been successfully created.");
}

//Passar vetor de indices ->currentIndex
void MainWindow::conservedresidues(int ai, vector<int> referencesequences, float minconservation){
    int c1, c2;
    float freq;
    vector<char> conservedaa;
    vector<int> conservedpos;
    vector<float> conservedfreq;

    alinhamentos[ai].CalculateFrequencies();

    for(c1 = 0; c1 < alinhamentos[ai].frequencies.size()-2; c1++){
        for(c2 = 1; c2 <=20; c2++){
            freq = (float)alinhamentos[ai].frequencies[c1][c2]/((float)alinhamentos[ai].sequences.size());
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
/*
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
        out << "<tr><th><b>" << alinhamentos[ai].sequencenames[referencesequences[c1]].c_str();
        for (c2=0;c2<=conservedaa.size()-1;c2++){
            if(alinhamentos[ai].AlignNumbering2Sequence(referencesequences[c1]+1,conservedpos[c2]) ==0){
                out << "<th><font color=#FF0000>-</font></th>";
            }else{
                if (alinhamentos[ai].sequences[referencesequences[c1]][conservedpos[c2]]==conservedaa[c2])
                    out << "<th>" << conservedaa[c2] << alinhamentos[ai].AlignNumbering2Sequence(referencesequences[c1]+1,conservedpos[c2]) + GetOffsetFromSeqName(alinhamentos[ai].sequencenames[referencesequences[c1]]) << "</th>";
                else
                    out << "<th><font color=#FF0000>" << alinhamentos[ai].sequences[referencesequences[c1]][conservedpos[c2]] << alinhamentos[ai].AlignNumbering2Sequence(referencesequences[c1]+1,conservedpos[c2])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[referencesequences[c1]]) << "</font></th>";
            }
        }
        out << "</tr>\n";
    }
    file.close();
*/
    QMessageBox::information(this,"Conserved Residues", "Conserved residues exported to HTML table.");
}

vector<float> MainWindow::minss(int ai, int repetitions){
    vector<float> outputVec;
    alinhamentos[ai].CalculateFrequencies();
    //outputVec = alinhamentos[ai].DTRandomElimination(repetitions,99,1,1);
    outputVec = alinhamentos[ai].ShenkinEntropy(repetitions,0.5);


    if(ui->listWidget2->currentItem() == NULL)
        alinhamentos[ai].addParameter("minss","Full Alignment",repetitions);
    else
        alinhamentos[ai].addParameter("minss", ui->listWidget2->currentItem()->text().toStdString(), repetitions);

    QMessageBox::information(this,"Minss","Minss calculated.");

    return outputVec;
}

void MainWindow::pcalc(int ai, int minlogp, float minssfraction, float mindeltafreq){
    alinhamentos[ai].CalculateFrequencies();
    alinhamentos[ai].SympvalueCalculation(minlogp,minssfraction,mindeltafreq);
    //alinhamentos[ai].printCorrGraph();

    //QMessageBox::information(this,"PCalc","Communities graph generated.");
}

void MainWindow::trivcomm(int ai){
    int maxsize;
    int biggestcommunity;
    int c1,c2;
    int found1comm,found2comm,found1commpos,found2commpos; // Communities and positions where pos1-aa1 and pos2-aa2 were found
    bool member1found=false;
    bool member2found=false;
    vector < vector <int> > posCommunities;
    vector < vector <char> > aaCommunities;
    alinhamentos[ai].clearCommunity();

    tuple<string,string,int> edge = alinhamentos[ai].getCorrelationEdge(0);
    string v1 = std::get<0>(edge);
    string v2 = std::get<1>(edge);
    int score = std::get<2>(edge);
    //printf("V1: %s, V2: %s\n",v1.c_str(),v2.c_str());
    char aa1 = v1[0];
    char aa2 = v2[0];
    int pos1, pos2;

    string temp = "";
    for(int i = 1; i < v1.length(); i++){
        temp += v1[i];
    }
    pos1 = std::atoi(temp.c_str());

    temp = "";
    for(int i = 1; i < v2.length(); i++){
        temp += v2[i];
    }
    pos2 = std::atoi(temp.c_str());

    posCommunities.push_back(vector<int>());
    aaCommunities.push_back(vector<char>());
    posCommunities[0].push_back(pos1);
    aaCommunities[0].push_back(aa1);

    if(score > 0){
        posCommunities[0].push_back(pos2);
        aaCommunities[0].push_back(aa2);
    }else{
        posCommunities.push_back(vector<int>());
        aaCommunities.push_back(vector<char>());
        posCommunities[1].push_back(pos1);
        aaCommunities[1].push_back(aa1);
    }

    for(int i = 1; i < alinhamentos[ai].getCorrelationGraphSize(); i++){
        edge = alinhamentos[ai].getCorrelationEdge(i);
        v1 = std::get<0>(edge);
        v2 = std::get<1>(edge);
        score = std::get<2>(edge);

        //printf("V1: %s, V2: %s\n",v1.c_str(),v2.c_str());

        aa1 = v1[0];
        aa2 = v2[0];
        pos1, pos2;

        string temp = "";
        for(int i = 1; i < v1.length(); i++){
            temp += v1[i];
        }
        pos1 = std::atoi(temp.c_str());

        temp = "";
        for(int i = 1; i < v2.length(); i++){
            temp += v2[i];
        }
        pos2 = std::atoi(temp.c_str());

        member1found = false;
        member2found = false;

        for(c1=0;c1<=posCommunities.size()-1;c1++){
            for (c2=0;c2<=posCommunities[c1].size()-1;c2++){
                if((pos1==posCommunities[c1][c2])&&(aa1==aaCommunities[c1][c2])){
                    member1found=true;
                    found1comm=c1;
                    found1commpos=c2;
                    break;
                }
            }
            if(member1found) break;
        }

        for(c1=0;c1<=posCommunities.size()-1;c1++){
            for (c2=0;c2<=posCommunities[c1].size()-1;c2++){
                if((pos2==posCommunities[c1][c2])&&(aa2==aaCommunities[c1][c2])){
                    member2found=true;
                    found2comm=c1;
                    found2commpos=c2;
                    break;
                }
            }
            if(member2found) break;
        }

        if((!member1found)&&(!member2found)){
            if(score>0){
                posCommunities.push_back(vector<int>());
                aaCommunities.push_back(vector<char>());
                posCommunities[posCommunities.size()-1].push_back(pos1);
                aaCommunities[posCommunities.size()-1].push_back(aa1);
                posCommunities[posCommunities.size()-1].push_back(pos2);
                aaCommunities[posCommunities.size()-1].push_back(aa2);
            }else{
                posCommunities.push_back(vector<int>());
                aaCommunities.push_back(vector<char>());
                posCommunities[posCommunities.size()-1].push_back(pos1);
                aaCommunities[posCommunities.size()-1].push_back(aa1);
                posCommunities.push_back(vector<int>());
                aaCommunities.push_back(vector<char>());
                posCommunities[posCommunities.size()-1].push_back(pos2);
                aaCommunities[posCommunities.size()-1].push_back(aa2);
            }
        }

        if((member1found)&&(!member2found)){
            if(score>0){
                aaCommunities[found1comm].push_back(aa2);
                posCommunities[found1comm].push_back(pos2);
            }else{
                posCommunities.push_back(vector<int>());
                aaCommunities.push_back(vector<char>());
                posCommunities[posCommunities.size()-1].push_back(pos2);
                aaCommunities[posCommunities.size()-1].push_back(aa2);
            }
        }

        if((member2found)&&(!member1found)){
            if(score>0){
                aaCommunities[found2comm].push_back(aa1);
                posCommunities[found2comm].push_back(pos1);
            }else{
                posCommunities.push_back(vector<int>());
                aaCommunities.push_back(vector<char>());
                posCommunities[posCommunities.size()-1].push_back(pos1);
                aaCommunities[posCommunities.size()-1].push_back(aa1);
            }
        }

        if((member2found)&&(member1found)){
            if (found2comm==found1comm)
                if (score<0){
                    //printf("\nTrivial solution not possible: %c%d and %c%d are on the same community, but have a negative score",aa1,pos1,aa2,pos2);
                    QString str = "Trivial solution not possible: " + aa1 + QString::number(pos1) + " and " + aa2 + QString::number(pos2) + " are on the same community, but have a negative score";
                    QMessageBox::warning(this,"Trivcomm",str);
                    return;
                }
            if (found2comm!=found1comm){
                if(score>0){
                    for(c1=0;c1<=aaCommunities[found2comm].size()-1;c1++){
                        aaCommunities[found1comm].push_back(aaCommunities[found2comm][c1]);
                        posCommunities[found1comm].push_back(posCommunities[found2comm][c1]);
                    }
                    aaCommunities[found2comm].clear();
                    posCommunities[found2comm].clear();
                    aaCommunities.erase(aaCommunities.begin()+found2comm);
                    posCommunities.erase(posCommunities.begin()+found2comm);
                }
            }
        }
    }

    //communitiesfile=fopen(communitiesfilename.c_str(),"w+");
    //fprintf(communitiesfile,"%d communities\n",aaCommunities.size());
    c2=1;

    while(aaCommunities.size()>0){
        maxsize=0;

        for(c1=0;c1<=aaCommunities.size()-1;c1++){
            if (aaCommunities[c1].size()>maxsize){
                maxsize=aaCommunities[c1].size();
            }
        }

        for(c1=0;c1<=aaCommunities.size()-1;c1++){
            if (aaCommunities[c1].size()==maxsize){
                biggestcommunity=c1;
                break;
            }
        }

        //fprintf(communitiesfile,"%d nodes in community %d\n",aaCommunities[biggestcommunity].size(),c2);

        vector<string> comm;
        for(c1=0;c1<=aaCommunities[biggestcommunity].size()-1;c1++){
            //fprintf(communitiesfile,"%c%d\n",aaCommunities[biggestcommunity][c1],posCommunities[biggestcommunity][c1]);
            string node = aaCommunities[biggestcommunity][c1] + QString::number(posCommunities[biggestcommunity][c1]).toStdString();
            comm.push_back(node);
        }
        alinhamentos[ai].addCommunity(comm);
        comm.clear();

        aaCommunities[biggestcommunity].clear();
        posCommunities[biggestcommunity].clear();
        aaCommunities.erase(aaCommunities.begin()+biggestcommunity);
        posCommunities.erase(posCommunities.begin()+biggestcommunity);
        c2++;
    }
    //alinhamentos[ai].printCommunity();
}

void MainWindow::output(int ai, int seqnumber, int offset){
    alinhamentos[ai].CalculateFrequencies();
    //alinhamentos[ai].GetCommunitiesFromFile(communitiesfilename);
    alinhamentos[ai].getCommunitiesFromRAM();
    //string path = alinhamentos[ai].getDir();

    //communityX.html
    if(seqnumber > 0) alinhamentos[ai].Cluster2SCMFromRAM(true,seqnumber,offset);
    else alinhamentos[ai].Cluster2SCMFromRAM(false,seqnumber,offset);
    //if(seqnumber>0) alinhamentos[ai].Cluster2SCM(communitiesfilename,path,true,seqnumber,offset,true,false);
    //else alinhamentos[ai].Cluster2SCM(communitiesfilename,path,false,seqnumber,offset,true,false);

    //alinhamentos[ai].DeltaCommunitiesCalculation();
    //alinhamentos[ai].DeltaCommunitiesOutput(path + "Deltas.html");

    //if (seqnumber>0)
    //    alinhamentos[ai].ElementRanking(path, true, seqnumber,offset);
    //else
    //    alinhamentos[ai].ElementRanking(path, false, seqnumber,offset);

    //comunityXps.html
    alinhamentos[ai].pMatrix2HTMLRAM(false,1);
    //alinhamentos[ai].pMatrix2HTML("/home/neli/teste",false,1);

    //alinhamentos[ai].Cluster2PymolScript(communitiesfilename,path,seqnumber,offset);

    //QMessageBox::information(this,"Output","Output files are generated sucessfully.");
}

void MainWindow::adherence(Alignment align, string communitiesfilename, string outputfilename){
    FILE *outputfile;
    int c1,c2;

    align.CalculateFrequencies();
    align.GetCommunitiesFromFile(communitiesfilename);

    outputfile=fopen(outputfilename.c_str(),"w+");
    fprintf(outputfile,"PROTEIN_SEQUENCE");

    for(c1=0; c1<align.Communities.size()-1;c1++)
        if(align.Communities[c1].aa.size()>1) fprintf(outputfile,"\tComm%d",c1+1);
    fprintf(outputfile,"\n");

    for(c1=0;c1<=align.sequences.size()-1;c1++){
        fprintf(outputfile,"%s",align.sequencenames[c1].c_str());

        for(c2=0;c2<=align.Communities.size()-1;c2++)
            if (align.Communities[c2].aa.size()>1) fprintf(outputfile,"\t%f",align.PSA(c1,c2));
        fprintf(outputfile,"\n");
    }

    QMessageBox::information(this,"Adherence","Adherence generated.");

}

void MainWindow::comm2seqrenumbering(Alignment align, string communitiesfilename, vector<int> seqlist, string path){
    char outputfilename[255];
    int c1,c2,c3;
    FILE *outputfile;

    align.CalculateFrequencies();
    align.GetCommunitiesFromFile(communitiesfilename);

    for(c1=0; c1<align.Communities.size()-1; c1++){
        sprintf (outputfilename,"%scomm%dnumbering.html",path.c_str(),c1+1);
        outputfile=fopen(outputfilename,"w+");

        fprintf(outputfile,"<html>\n<body>\n<table border=1>\n<center>\n<tr>\n<th><b>Sequence</b></th>");

        for (c2=0;c2<=align.Communities[c1].pos.size()-1;c2++)
            fprintf(outputfile,"<th><b>%c%d</b></th>",align.Communities[c1].aa[c2],align.Communities[c1].pos[c2]+1);
        fprintf(outputfile,"</tr>\n");

        for(c2=0;c2<=seqlist.size()-1;c2++){
            fprintf(outputfile,"<tr><th><b>%s</b></th>",align.sequencenames[seqlist[c2]].c_str());

            for (c3=0;c3<=align.Communities[c1].pos.size()-1;c3++){
                if(align.sequences[seqlist[c2]][align.Communities[c1].pos[c3]]==align.Communities[c1].aa[c3])
                    fprintf (outputfile,"<th><font color=#00FF00>%c%d</font></th>",align.Communities[c1].aa[c3],align.AlignNumbering2Sequence(seqlist[c2]+1,align.Communities[c1].pos[c3])+GetOffsetFromSeqName(align.sequencenames[seqlist[c2]]));
                else{
                    if (align.sequences[seqlist[c2]][align.Communities[c1].pos[c3]]=='-') fprintf (outputfile,"<th>-</th>");
                    else fprintf (outputfile,"<th>%c%d</th>",align.sequences[seqlist[c2]][align.Communities[c1].pos[c3]],align.AlignNumbering2Sequence(seqlist[c2]+1,align.Communities[c1].pos[c3])+GetOffsetFromSeqName(align.sequencenames[seqlist[c2]]));
                }
            }
            fprintf(outputfile,"</tr>\n");
        }
        fprintf(outputfile,"</center>\n</table>\n</body>\n</html>\n");
        fclose (outputfile);
    }

    QMessageBox::information(this,"Comm2SeqRenumbering","All statics file are generated.");
}

void MainWindow::listSequences(int ai){
    vector<string> sequences;

    //Parametros
    if(ui->listWidget2->currentItem() == NULL){
        QMessageBox::information(this,"a","OK");
        ui->lblRefSeq1->setText(" Reference Sequence: Full Alignment");
        ui->lblOccupancy->setVisible(false);
        ui->lblMaxId->setVisible(false);
        ui->lblMinId->setVisible(false);
    }else{
        string filter = ui->listWidget2->currentItem()->text().toStdString();

        if(filter == "Full Alignment"){
            ui->lblRefSeq1->setText("Reference Sequence: Full Alignment");
            ui->lblOccupancy->setVisible(false);
            ui->lblMaxId->setVisible(false);
            ui->lblMinId->setVisible(false);
        }else{
            vector<string> vecPars = split(filter,' ');
            ui->lblOccupancy->setVisible(true);
            ui->lblMaxId->setVisible(true);
            ui->lblMinId->setVisible(true);
            string occ = "Occupancy: " + vecPars[0];
            string minId = "Minimum Identity: " + vecPars[1];
            string maxId = "Maximum Identity: " + vecPars[2];
            string refSeq = "Reference Sequence: " + vecPars[3];
            ui->lblOccupancy->setText(occ.c_str());
            ui->lblMinId->setText(minId.c_str());
            ui->lblMaxId->setText(maxId.c_str());
            ui->lblRefSeq1->setText(refSeq.c_str());
        }
    }


   sequences = alinhamentos.at(ai).getSequencesName();

    for(int j = 0; j < sequences.size(); j++){
        ui->lstProteinsFiltered->addItem(QString::fromStdString(sequences[j]));
    }

}

void MainWindow::tableFreq(int ai){
    int nrows = alinhamentos[ai].getConsFreqSize();

    //Limpa tabela
    ui->tableFreq->clearContents();

    //Ajusta tamanho das colunas
    ui->tableFreq->resizeColumnsToContents();

    ui->tableFreq->verticalHeader()->setVisible(false);

    //QHeaderView *HorzHdr = ui->tableFreq->horizontalHeader();
    //HorzHdr->setStretchLastSection(true);

    //Parâmetros
    vector<string> consPars = alinhamentos[ai].getConservationParameters();

    if(consPars.size() >4){
        ui->lblFilter->setText("Filter: " + QString::fromStdString(consPars[1]));
        ui->lblRefSeq->setText("Reference Sequence: " + QString::fromStdString(consPars[2]));
        ui->lblOffset->setText("Offset: " + QString::fromStdString(consPars[3]));
        ui->lblChain->setText("Chain: " + QString::fromStdString(consPars[4]));
    }


    //Preenche a tabela
    ui->tableFreq->setRowCount(nrows);

    for(int i = 0; i < nrows; i++){
        vector<int> freqRow = alinhamentos[ai].getConsFreqRow(i);

        for(int j = 0; j < 22; j++){
            if(j == 0){
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole,i+1);

                ui->tableFreq->setItem(i,j,item);
            }else{
                //QTableWidgetItem *item = new QTableWidgetItem (tr(QString::number(freqRow[j-1]).toLatin1()),1);
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole,freqRow[j-1]);

                ui->tableFreq->setItem(i,j,item);
            }
        }
    }
}

void MainWindow::tableFreqPerc(int ai){
    int nrows = alinhamentos[ai].getConsFreqPercSize();

    //Limpa tabela
    ui->tableFreqPerc->clearContents();

    //Ajusta o tamanho das colunas
    ui->tableFreqPerc->resizeColumnsToContents();

    ui->tableFreqPerc->verticalHeader()->setVisible(false);

    vector<string> consPars = alinhamentos[ai].getConservationParameters();

    if(consPars.size() > 4){
        ui->lblFilter_2->setText("Filter: " + QString::fromStdString(consPars[1]));
        ui->lblRefSeq_2->setText("Reference Sequence: " + QString::fromStdString(consPars[2]));
        ui->lblOffset_2->setText("Offset: " + QString::fromStdString(consPars[3]));
        ui->lblChain_2->setText("Chain: " + QString::fromStdString(consPars[4]));
    }

    //Preenche a tabela
    ui->tableFreqPerc->setRowCount(nrows);

    for(int i = 0; i < nrows; i++){
        vector<float> freqPercRow = alinhamentos[ai].getConsFreqPercRow(i);

        for(int j = 0; j < 21; j++){
            if(j == 0){
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole,i+1);

                ui->tableFreqPerc->setItem(i,j,item);
            }else{
                QTableWidgetItem *item = new QTableWidgetItem();
                QString strTemp = QString::number(freqPercRow[j-1],'f',2);

                item->setData(Qt::DisplayRole,strTemp.toFloat());

                ui->tableFreqPerc->setItem(i,j,item);
            }
        }
    }
    /*
    vector<float> freqPercRow = alinhamentos[ai].getConsFreqPercRow(nrows);

    for(int j = 0; j < 21; j++){
        if(j == 0){
            QTableWidgetItem *item = new QTableWidgetItem (tr("ALL"));
            ui->tableFreqPerc->setItem(nrows,j,item);
        }else{
            QTableWidgetItem *item = new QTableWidgetItem();
            QString strTemp = QString::number(freqPercRow[j-1],'f',2);

            item->setData(Qt::DisplayRole,strTemp.toFloat());

            ui->tableFreqPerc->setItem(nrows,j,item);
        }
    }
    */
}

void MainWindow::correlationList(int ai){
    int nrows = alinhamentos[ai].getCorrGraphSize();

    //Limpa a tabela
    ui->treeCorrelation->clear();

    //Recupera parametros
    vector<string> corrPars = alinhamentos[ai].getCorrelationParameters();

    if(corrPars.size() > 4){
        ui->lblFilter_3->setText("Filter: " + QString::fromStdString(corrPars[1]));
        ui->lblMinLogP->setText("Minimum Score: " + QString::fromStdString(corrPars[2]));
        ui->lblMinss->setText("Minss Fraction: " + QString::fromStdString(corrPars[3]));
        ui->lblDeltaFreq->setText("Delta Frequence: " + QString::fromStdString(corrPars[4]));
    }

    //Preenche a tabela
    for(int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = alinhamentos[ai].getCorrGraphTuple(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelation);

        item->setText(0,std::get<0>(tupCorr).c_str());
        item->setText(1,std::get<1>(tupCorr).c_str());
        item->setText(2,QString::number(std::get<2>(tupCorr)));
    }

}

void MainWindow::communitiesList(int ai){
    int nrows = alinhamentos[ai].getCommListSize();

    //Limpa a tabela
    ui->treeCorrelationComm->clear();

    //Recupera parametros
    vector<string> corrPars = alinhamentos[ai].getCorrelationParameters();

    if(corrPars.size() > 4){
        ui->lblFilter_4->setText("Filter: " + QString::fromStdString(corrPars[1]));
        ui->lblMinLogP_2->setText("Minimum Score: " + QString::fromStdString(corrPars[2]));
        ui->lblMinss_2->setText("Minss Fraction: " + QString::fromStdString(corrPars[3]));
        ui->lblDeltaFreq_2->setText("Delta Frequence: " + QString::fromStdString(corrPars[4]));
    }

    //Preenche a tabela
    for(int i = 0; i < nrows; i++){
        vector<string> residues = alinhamentos[ai].getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelationComm);

        string text = "Comunidade " + QString::number(i).toStdString();
        item->setText(0,text.c_str());

        for(int j = 0; j < residues.size(); j++){
            item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(residues[j].c_str()))));
        }
    }
}

void MainWindow::corrTable1(int ai){
    //int ncomms = alinhamentos[ai].getNumOfUtilComms();

    //Limpa a tabela
    ui->tableComm1->clear();

    //Recupera parametros
    vector<string> corrPars = alinhamentos[ai].getCorrelationParameters();

    if(corrPars.size() > 4){
        ui->lblFilter_5->setText("Filter: " + QString::fromStdString(corrPars[1]));
        ui->lblMinLogP_3->setText("Minimum Score: " + QString::fromStdString(corrPars[2]));
        ui->lblMinss_3->setText("Minss Fraction: " + QString::fromStdString(corrPars[3]));
        ui->lblDeltaFreq_3->setText("Delta Frequence: " + QString::fromStdString(corrPars[4]));
        ui->lblComunidade->setText("Comunidade 1:");
    }

    //Monta a tabela
    vector<string> residues = alinhamentos[ai].getResiduesComm(0);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = alinhamentos[ai].getCommAll(0);

    for(int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = alinhamentos[ai].getCommXRow(0,i);
        for(int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1){
                strTemp = "X";
                item2->setText(strTemp);
            }
            else {
                strTemp = QString::number(commRow[j],'f',4);
                item2->setData(Qt::DisplayRole,strTemp.toFloat()*100);
            }
            ui->tableComm1->setItem(i,j+1,item2);
        }
    }

    //Ajusta tamanho das colunas
    ui->tableComm1->resizeColumnsToContents();
}

void MainWindow::corrTable2(int ai){
    //Limpa a Tabela
    ui->tableComm2->clear();

    //Recupera parametros
    vector<string> corrPars = alinhamentos[ai].getCorrelationParameters();

    if(corrPars.size() > 4){
        ui->lblFilter_6->setText("Filter: " + QString::fromStdString(corrPars[1]));
        ui->lblMinLogP_4->setText("Minimum Score: " + QString::fromStdString(corrPars[2]));
        ui->lblMinss_4->setText("Minss Fraction: " + QString::fromStdString(corrPars[3]));
        ui->lblDeltaFreq_4->setText("Delta Frequence: " + QString::fromStdString(corrPars[4]));
        ui->lblComunidade_2->setText("Comunidade 1:");
    }

    //Montar a Tabela
    vector<string> residues = alinhamentos[ai].getResiduesCommPs(0);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(int i = 0; i < residues.size(); i++){
        vector<int> commRow = alinhamentos[ai].getCommPsRow(0,i);

        for(int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1) item2->setText("X");
            else item2->setData(Qt::DisplayRole,commRow[j]);

            ui->tableComm2->setItem(i,j,item2);
        }
    }
    //Ajusta tamanho das colunas
    ui->tableComm2->resizeColumnsToContents();
}

void MainWindow::adh(int ai){

    int nComm = alinhamentos[ai].getNumOfUtilComms();
    int nSequences = alinhamentos[ai].sequences.size()-1;

    //alinhamentos[ai].printFrequencies();

    //Montar a Tabela
    ui->tableAdherence->horizontalHeader()->setVisible(true);
    ui->tableAdherence->setColumnCount(nComm + 1);
    ui->tableAdherence->setRowCount(nSequences);

    ui->tableAdherence->setHorizontalHeaderItem(0,new QTableWidgetItem("PROTEIN SEQUENCE"));

    for(int i = 0; i < nComm; i++){
        string temp = "Comm " + QString::number(i+1).toStdString();
        ui->tableAdherence->setHorizontalHeaderItem(i+1,new QTableWidgetItem(temp.c_str()));
    }

    //------ADHERENCE-----
    for(int i = 0; i < alinhamentos[ai].sequences.size()-1; i++){
        QTableWidgetItem *protItem = new QTableWidgetItem();
        protItem->setText(alinhamentos[ai].sequencenames[i].c_str());
        ui->tableAdherence->setItem(i,0,protItem);

        for(int j = 0; j < nComm; j++){
            if(alinhamentos[ai].Communities[j].aa.size() > 1){
                float psa = alinhamentos[ai].PSA(i,j);

                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole,psa);
                ui->tableAdherence->setItem(i,j+1,item);
            }
        }

    }
    //Ajusta tamanho das colunas
    ui->tableAdherence->resizeColumnsToContents();
}

void MainWindow::showConservedResidues(int ai){
    vector<int> refSeqs;
    vector<char> conservedaa;
    vector<int> conservedpos;
    vector<float> conservedfreq;
    float minCons = ui->txtMinConserv->value();

    //Parâmetros
    vector<string> consPars = alinhamentos[ai].getConservationParameters();

    if(consPars.size() > 4){
        ui->lblFilter_8->setText("Filter: " + QString::fromStdString(consPars[1]));
        ui->lblMinCons->setText("Minimum Conservation: " + QString::fromStdString(consPars[5]));
    }

    alinhamentos[ai].CalculateFrequencies();
/*
    QModelIndexList indexList = ui->lstRefSeqs->selectionModel()->selectedIndexes();
    for(int j = 0; j < indexList.size(); j++){
        refSeqs.push_back(indexList.at(j).row());
    }
*/
    for(int i = 0; i < alinhamentos[ai].getConsRefsSize(); i++){
        string ref1 = alinhamentos[ai].getConsref(i);

        for(int j = 0; j < ui->lstRefSeqs->count(); j++){
            string ref2 = ui->lstRefSeqs->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }


    for(int i = 0; i < alinhamentos[ai].frequencies.size()-2; i++){
        for(int j = 1; j <= 20; j++){
            float freq = alinhamentos[ai].frequencies[i][j]/((float)alinhamentos[ai].sequences.size());
            //printf("freq=%f / minCons=%f\n",freq,minCons);
            if(freq >= minCons){
                conservedaa.push_back(num2aa(j));
                conservedpos.push_back(i);
                conservedfreq.push_back(100.0*freq);
            }
        }
    }

    if(conservedaa.size() == 0){
        QMessageBox::warning(this,"Warning","No residues match the conservation minimum.");
        return;
    }

    //Cabeçalho
    ui->tableConsRes->setColumnCount(conservedaa.size());
    for(int i = 0; i < conservedaa.size(); i++){
        string textCab = conservedaa[i] + QString::number(conservedpos[i] + 1).toStdString() + " (" + QString::number(conservedfreq[i],'f',1).toStdString() + ")";
        ui->tableConsRes->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    ui->tableConsRes->setRowCount(refSeqs.size());
    for(int i = 0; i < refSeqs.size(); i++){
        ui->tableConsRes->setVerticalHeaderItem(i,new QTableWidgetItem(alinhamentos[ai].sequencenames[refSeqs[i]].c_str()));

        for(int j = 0; j < conservedaa.size(); j++){
            if(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,conservedpos[j]) == 0){
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setTextColor(QColor(255,0,0,255));
                item->setText("-");
                ui->tableConsRes->setItem(i,j,item);
            }else{
                if(alinhamentos[ai].sequences[refSeqs[i]][conservedpos[j]]==conservedaa[j]){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = conservedaa[j] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,conservedpos[j]) + GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableConsRes->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = alinhamentos[ai].sequences[refSeqs[i]][conservedpos[j]] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,conservedpos[j]) + GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                    item->setTextColor(QColor(255,0,0,255));
                    item->setText(textItem.c_str());
                    ui->tableConsRes->setItem(i,j,item);
                }
            }
        }
    }
    //Ajusta tamanho das colunas
    ui->tableConsRes->resizeColumnsToContents();
}

void MainWindow::showResiduesComm(int ai){
    vector<int> refSeqs;

    alinhamentos[ai].CalculateFrequencies();

    /*QModelIndexList indexList = ui->lstRefSeqs_2->selectionModel()->selectedIndexes();
    for(int j = 0; j < indexList.size(); j++){
        refSeqs.push_back(indexList.at(j).row());
    }*/

    for(int i = 0; i < alinhamentos[ai].getCorrRefSeqsSize(); i++){
        string ref1 = alinhamentos[ai].getCorrRefSeq(i);

        for(int j = 0; j < ui->lstRefSeqs_2->count(); j++){
            string ref2 = ui->lstRefSeqs_2->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    //Parâmetros
    ui->lblComunidade_3->setText("Comunidade 1");

    vector<string> corrPars = alinhamentos[ai].getCorrelationParameters();

    if(corrPars.size() > 4){
        ui->lblFilter_9->setText("Filter: " + QString::fromStdString(corrPars[1]));
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(alinhamentos[ai].Communities[0].pos.size());
    for(int i = 0; i < alinhamentos[ai].Communities[0].pos.size(); i++){
        string textCab = alinhamentos[ai].Communities[0].aa[i] + QString::number(alinhamentos[ai].Communities[0].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(alinhamentos[ai].sequencenames[refSeqs[i]].c_str()));

        for(int j = 0; j < alinhamentos[ai].Communities[0].pos.size(); j++){
            if(alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[0].pos[j]]==alinhamentos[ai].Communities[0].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = alinhamentos[ai].Communities[0].aa[j] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,alinhamentos[ai].Communities[0].pos[j])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[0].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[0].pos[j]] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,alinhamentos[ai].Communities[0].pos[j])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableResiduesComm->setItem(i,j,item);
                }
            }
        }
    }

    //Ajusta tamanho das colunas
    ui->tableResiduesComm->resizeColumnsToContents();
}

void MainWindow::addAlignment(string path){
    Alignment align;
    align.setFilepath(path);
    align.GetFromFile();
    alinhamentos.push_back(path);
}

void MainWindow::changeWizardCmds(bool bl){
    ui->cmdAdvance->setEnabled(bl);
    ui->cmdBack->setEnabled(bl);
    ui->cmdMain->setEnabled(bl);
    ui->cmdSaveResults->setEnabled(bl);
    ui->cmdShowResults->setEnabled(bl);
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

    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::warning(this,"Quit","This will clean all you data. Do you really want to proceed?",QMessageBox::Yes|QMessageBox::No);

    if(confirm == QMessageBox::Yes){

        ui->listWidget->setEnabled(true);
        ui->listWidget2->setEnabled(true);
        ui->cmdNextResult->setVisible(false);
        ui->cmdBackResult->setVisible(false);

        //Desativa botões do Wizard
        changeWizardCmds(false);

        //Reseta campos
        resetObjects();
        for(int i = 0; i < alinhamentos.size(); i++)
            alinhamentos[i].clear();
        alinhamentos.clear();
        alinhamentos.shrink_to_fit();

        //Muda para tela 0
        ui->stackedWidget->setCurrentIndex(0);

    }

    ui->cmdMain->setEnabled(true);
}

void MainWindow::on_cmdBack_clicked()
{
    //ui->cmdBack->setEnabled(false);
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);
    ui->cmdNextResult->setVisible(false);
    ui->cmdBackResult->setVisible(false);

    int ctIx = ui->stackedWidget->currentIndex();

    if(ctIx == 1){
        //Apaga botões do Wizard
        changeWizardCmds(false);
    }
    else if(ctIx == 2) ui->cmdBack->setEnabled(false);
    else if(ctIx == 5) ui->cmdAdvance->setEnabled(true);
    else if(ctIx == 6){
        ui->checkResults1->setChecked(false);
        ui->checkResults2->setChecked(false);
        ui->checkResults3->setChecked(false);
        ui->checkResults4->setChecked(false);
        ui->checkResults5->setChecked(false);
        ui->checkResults6->setChecked(false);
        ui->checkResults7->setChecked(false);
        ui->checkResults8->setChecked(false);
        ui->checkResults9->setChecked(false);
        ui->checkResults10->setChecked(false);

        int newctIx = stackBeforeShowResults;

        changeWizardCmds(true);

        if(newctIx == 0) changeWizardCmds(false);
        else if(newctIx == 1) ui->cmdBack->setEnabled(false);
        else if(newctIx == 5) ui->cmdAdvance->setEnabled(false);

        ui->stackedWidget->setCurrentIndex(newctIx);
        return;
    }


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

    //Salva Full Alignment
    vector<string> filterSequence;
    vector<string> filterList;
    string params = "0 0 0 0";
    filterSequence.push_back(params);
    filterList.push_back(params);

    vector<string> fullNames = align.getFullAlignment();
    for(int i = 0; i < fullNames.size(); i++){
        filterList.push_back(fullNames[i]);
    }

    vector<string> fullSequences = align.getFullSequences();
    for(int i = 0; i < fullSequences.size(); i++){
        filterSequence.push_back(fullSequences[i]);
    }

    align.addFilterSequence(filterList,filterSequence);

    //Armazena local para XML
    align.setLocalDir(fileName.toStdString());

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

    if(ui->radioButton->isChecked()) url += "seed/format?format=pfam&amp;alnType=seed&amp;order=";
    else url += "full/format?format=pfam&amp;alnType=full&amp;order=";

    if(ui->radioButton_3->isChecked()) url += "t&amp;case=";
    else url += "a&amp;case=";

    if(ui->radioButton_5->isChecked()) url += "l&amp;gaps=";
    else url += "u&amp;gaps=";

    if(ui->radioButton_7->isChecked()) url += "dashes&amp;download=0";
    else if(ui->radioButton_8->isChecked()) url += "dots&amp;download=0";
    else if(ui->radioButton_9->isChecked()) url += "default&amp;download=0";
    else url += "none&amp;download=0";

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
        align.setWebDir(url.toStdString());

        //Salva Full Alignment
        vector<string> filterSequence;
        vector<string> filterList;
        string params = "0 0 0 0";
        filterSequence.push_back(params);
        filterList.push_back(params);

        vector<string> fullNames = align.getFullAlignment();
        for(int i = 0; i < fullNames.size(); i++){
            filterList.push_back(fullNames[i]);
        }

        vector<string> fullSequences = align.getFullSequences();
        for(int i = 0; i < fullSequences.size(); i++){
            filterSequence.push_back(fullSequences[i]);
        }

        align.addFilterSequence(filterList,filterSequence);

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

    for(int i = 0; i < ui->listWidget2->count(); i++){
        string filtered = ui->listWidget2->item(i)->text().toStdString();
        vector<string> vecFilter = this->split(filtered,' ');
        //QMessageBox::information(this,"a",QString::number(filtered.size()));
        if(vecFilter.size() == 4){
            //QMessageBox::information(this,"a","ok");
            float minCov = atof(vecFilter[0].c_str());
            float minId = atof(vecFilter[1].c_str());
            float maxId = atof(vecFilter[2].c_str());
            string refSeq = vecFilter[3];
            float minCov2 = ui->txtMinCover->text().toFloat();
            float minId2 = ui->txtMinId->text().toFloat();
            float maxId2 = ui->txtMaxId->text().toFloat();
            string refSeq2 = ui->cmbRefSeq->currentText().toStdString();

            if(minCov == minCov2 && minId == minId2 && maxId == maxId2 && refSeq == refSeq2){
                QMessageBox::warning(this,"Filter applied","This filter is already saved.");
                ui->cmdApplyFilter->setEnabled(true);
                return;
            }
        }
    }

    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    ui->cmbRefSeq_2->setCurrentIndex(ui->cmbRefSeq->currentIndex());
    ui->cmbRefSeq_3->setCurrentIndex(ui->cmbRefSeq->currentIndex());

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

    Alignment fullAlignment;
    fullAlignment.setFilepath(inputfilename);
    fullAlignment.GetFromFile();
    fullAlignment.CalculateFrequencies();

    refseq = ui->cmbRefSeq->currentIndex()-1;
    string refseqName = ui->cmbRefSeq->currentText().toStdString();

    if(ui->chkIntermediateFilter->isChecked())
        this->alignfilter(fullAlignment.getFilepath(),occupancy,minId,maxId,refseq,refseqName);
    else
        this->alignfilter(fullAlignment.getFilepath(),occupancy,minId,maxId,refseq,refseqName,false);


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
    //printf("\n%s\n",url.toStdString().c_str());

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
        //printf("\n%s",pdb.toStdString().c_str());
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

        this->pdbweb = url.toStdString();
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
    this->pdbweb = "";

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
    float minCons;

    alignfilename = ui->listWidget->currentItem()->text().toStdString();
    pdbfilename = ui->txtPDBfilepath->text().toStdString();
    refseq = ui->cmbRefSeq_2->currentIndex();
    chain = ui->txtChain->text().at(0).toLatin1();
    minCons = ui->txtMinConserv->value();

    //Alignment fullAlignment;
    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            //fullAlignment = alinhamentos[i];
            break;
        }
    }

    QModelIndexList indexList = ui->lstRefSeqs->selectionModel()->selectedIndexes();
    alinhamentos[i].clearConsRefs();
    for(int j = 0; j < indexList.size(); j++){
        alinhamentos[i].addConsRef(ui->lstRefSeqs->item(indexList.at(j).row())->text().toStdString());
    }


    if(ui->txtPDBfilepath->text() != ""){
        alinhamentos[i].setLocalPDBDir(ui->txtPDBfilepath->text().toStdString());
    }

    if(this->compareLocalWebPDB(ui->txtPDBfilepath->text().toStdString(),this->pdbweb))
        alinhamentos[i].setWebPDBDir(pdbweb);

    this->conservation(i,refseq,offset,chain,minCons,pdbfilename);
/*
    //CONSERVED RESIDUES
    vector<int> refSeqs;
    float minCons = (float)ui->txtMinConserv->value();
    QModelIndexList indexList = ui->lstRefSeqs->selectionModel()->selectedIndexes();
    for(int j = 0; j < indexList.size(); j++){
        refSeqs.push_back(indexList.at(j).row());
    }
/*
    vector<string> vecPath = split(fullAlignment.getFilepath(),'.');
    string path = "";

    for(int i=0;i<vecPath.size()-1;i++){
        path += vecPath[i];
    }
    path += "_CONSERVEDRESIDUES.html";
*/
    //this->conservedresidues(i,refSeqs,minCons);

    ui->cmdConservation->setEnabled(true);

}

void MainWindow::on_cmdMinss_clicked()
{
    ui->cmdMinss->setEnabled(false);

    if(ui->listWidget->selectedItems().size() == 0){
        QMessageBox::warning(this,"Error","You must select a alignment.");
        ui->cmdMinss->setEnabled(true);
        return;
    }

    string alignfilename = ui->listWidget->currentItem()->text().toStdString();
    int i = 0;

    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            break;
        }
    }
/*
    vector<string> vecPath = split(alinhamentos[i].getFilepath(),'.');
    string path = "";

    for(int i=0;i<vecPath.size()-1;i++){
        path += vecPath[i];
    }
    path += "_MINSS.dat";
*/
    int repetitions = ui->txtNoAlignments->value();

    vector<float> minssData;
    minssData = this->minss(i,repetitions);


    printf("\n\n");
    for(int j = 0; j < minssData.size(); j++)
        printf("%f\n",minssData[j]);

    QVector<double> x(100), y(100);
    for (int j=0; j<100; ++j)
    {
      x[j] = j+1; // x goes from -1 to 1
      y[99-j] = minssData[j]; // let's plot a quadratic function
    }

    ui->graficMinss->addGraph();
    ui->graficMinss->graph(0)->setData(x,y);
    ui->graficMinss->yAxis->setLabel("y");
    ui->graficMinss->xAxis->setLabel("x");
    ui->graficMinss->yAxis->setRange(0,y[99]+0.2); //DGDT
    //ui->graficMinss->yAxis->setRange(y[99] - 50,0);
    ui->graficMinss->xAxis->setRange(1,100);
    ui->graficMinss->replot();


    ui->graficMinss->setVisible(true);
    ui->cmdMinss->setEnabled(true);
}

/*
void MainWindow::on_cmdGraphPath_clicked()
{
    ui->cmdGraphPath->setEnabled(false);
    //Abre arquivo
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export File"),"/home",tr("Graph Files (*.txt *.cmm .csv)"));

    //Salva em arquivo
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        ui->cmdGraphPath->setEnabled(true);
        return;
    }

    //Add no line edit
    ui->txtGraphPath->setText(fileName);

    ui->cmdGraphPath->setEnabled(true);
}
*/

void MainWindow::on_cmdCorrelation_clicked()
{
    ui->cmdCorrelation->setEnabled(false);

    //Validação de dados
    if(ui->listWidget->selectedItems().size() == 0){
        QMessageBox::warning(this,"Error","You must select a alignment.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    /*
    if(ui->txtGraphPath->text() == ""){
        QMessageBox::warning(this,"Error","You must select a output file.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }
    */

    //Chamar PCalc
    //string outputgraphfilename = ui->txtGraphPath->text().toStdString().c_str();
    int minlogp = ui->txtMinScore->value();
    float minssfraction = ui->txtMinssFraction->value();
    float mindeltafreq = ui->txtMinDeltaFreq->value();

    string alignfilename = ui->listWidget->currentItem()->text().toStdString();


    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(ui->listWidget2->currentItem() == NULL)
        alinhamentos[i].addParameter("correlation", "Full Alignment", minlogp, minssfraction, mindeltafreq);
    else
        alinhamentos[i].addParameter("correlation",ui->listWidget2->currentItem()->text().toStdString(),minlogp, minssfraction, mindeltafreq);

    this->pcalc(i,minlogp,minssfraction,mindeltafreq);

    //Chamar Trivcomm
    this->trivcomm(i);

    //Salvar Refs Seqs
    // get selected ids
    QModelIndexList indexList = ui->lstRefSeqs_2->selectionModel()->selectedIndexes();
    QList<int> ids;
    for(int j = 0; j < indexList.size(); j++){
        ids += indexList.at(j).row();
    }

    for(int j = 0; j < ids.size(); j++){
        //QMessageBox::information(this,"ok",QString::number(ids[j]));
        alinhamentos[i].addCorrRefSeq(ui->lstRefSeqs_2->item(ids[j])->text().toStdString());
    }


    //Chamar Output
    this->output(i,1,ui->txtOffset_2->text().toInt());

    /*
    //Chamar Adherence
    string adhout = alinhamentos[i].getDir() + "ADH.txt";
    this->adherence(alinhamentos[i],trivpath,adhout);

    //Chamar comm2seqrenumbering
    vector<int> refSeqs;

    QModelIndexList indexList = ui->lstRefSeqs_2->selectionModel()->selectedIndexes();
    for(int j = 0; j < indexList.size(); j++){
        refSeqs.push_back(indexList.at(j).row());
    }

    this->comm2seqrenumbering(alinhamentos[i],trivpath,refSeqs,alinhamentos[i].getDir());
*/

    QMessageBox::information(this,"Correlation","All correlations were calculated.");
    ui->cmdCorrelation->setEnabled(true);
}

void MainWindow::on_listWidget_activated(const QModelIndex &index)
{
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    vector<string> sequences;

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            sequences = alinhamentos.at(i).getSequencesName();
            break;
        }
    }
/*
    for(int j = 0; j < sequences.size(); j++){
        printf("%d - %s",i,sequences[i].c_str());
    }
*/

    ui->cmbRefSeq->clear();
    ui->cmbRefSeq->addItem("");
    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("");
    ui->lstRefSeqs->clear();
    ui->lstRefSeqs_2->clear();

    //printf("SIZE: %d",sequences.size());
    vector<string> fullAlign = alinhamentos[i].getFullAlignment();
    //printf("\n%d\n",fullAlign.size());
    for(int i = 0; i < fullAlign.size(); i++){
        vector<string> splitVec = this->split(fullAlign[i],'/');
        ui->cmbRefSeq->addItem(QString::fromStdString(splitVec[0]));
        ui->lstRefSeqs->addItem(QString::fromStdString(splitVec[0]));
        ui->lstRefSeqs_2->addItem(QString::fromStdString(splitVec[0]));
    }

    ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(fullAlign.size()));

    ui->listWidget2->clear();

    vector<vector<string> > filterList = alinhamentos.at(i).getAllFilters();

    for(int j = 0; j < filterList.size(); j++){
        if(filterList[j][0] == "0 0 0 0") ui->listWidget2->addItem("Full Alignment");
        else ui->listWidget2->addItem(filterList[j][0].c_str());
    }

    //ui->cmbRefSeq_2->setCurrentIndex(1);
    //ui->cmbRefSeq_3->setCurrentIndex(1);
}

void MainWindow::on_listWidget2_activated(const QModelIndex &index)
{
    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    //Analisa qual o filtro de trabalho
    string filterPars = ui->listWidget2->currentItem()->text().toStdString();

    vector<vector<string> > filterList = alinhamentos.at(i).getAllFilters();
    vector<vector<string> > filterSeq = alinhamentos.at(i).getAllSequences();

    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("");
    //ui->lstRefSeqs->clear();
    //ui->lstRefSeqs_2->clear();
    ui->lstProteinsFiltered->clear();

    if(filterPars == "Full Alignment"){
        alinhamentos[i].loadFullAlignment();
        //QMessageBox::information(this,"a","OK");
        vector<string> fullAlignment = alinhamentos.at(i).getFullAlignment();
        ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(fullAlignment.size()));
        for(int j = 0; j < fullAlignment.size(); j++){
            vector<string> splitVec = this->split(fullAlignment[j],'/');
            ui->cmbRefSeq_2->addItem(QString::fromStdString(splitVec[0]));
            ui->cmbRefSeq_3->addItem(QString::fromStdString(splitVec[0]));
            //ui->lstRefSeqs->addItem(QString::fromStdString(splitVec[0]));
            //ui->lstRefSeqs_2->addItem(QString::fromStdString(splitVec[0]));
            ui->lstProteinsFiltered->addItem(QString::fromStdString(splitVec[0]));
        }
    }else{
        for(int j = 0; j < filterList.size(); j++){
            if(filterList[j][0] == filterPars){
                alinhamentos[i].sequences.clear();
                alinhamentos[i].sequencenames.clear();
                ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(filterList[j].size()));
                for(int k = 1; k < filterList[j].size(); k++){
                    vector<string> splitVec = this->split(filterList[j][k],'/');
                    ui->cmbRefSeq_2->addItem(QString::fromStdString(splitVec[0]));
                    ui->cmbRefSeq_3->addItem(QString::fromStdString(splitVec[0]));
                    //ui->lstRefSeqs->addItem(QString::fromStdString(splitVec[0]));
                    //ui->lstRefSeqs_2->addItem(QString::fromStdString(splitVec[0]));
                    ui->lstProteinsFiltered->addItem(QString::fromStdString(splitVec[0]));
                    alinhamentos[i].sequencenames.push_back(filterList[j][k]);
                    alinhamentos[i].sequences.push_back(filterSeq[j][k]);
                }
                break;
            }
        }
    }

    alinhamentos[i].CalculateFrequencies();
    //alinhamentos[i].printFrequencies();

    ui->cmbRefSeq_2->setCurrentIndex(1);
    ui->cmbRefSeq_3->setCurrentIndex(1);

}

void MainWindow::on_cmbRefSeq_activated(int index)
{
    if(index == 0) return;

    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    ui->cmbRefSeq_2->setCurrentIndex(index);
    ui->cmbRefSeq_3->setCurrentIndex(index);

    for(int i = 0; i < alinhamentos.size(); i++){
        printf("\nI = %d - SIZE = %d\n%s\n%s\n",i,alinhamentos.size(),path.c_str(),alinhamentos.at(i).getFilepath().c_str());
        if(path == alinhamentos.at(i).getFilepath()){
            //QMessageBox::information(this,"a",alinhamentos.at(i).sequencenames[index-1].c_str());
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[index-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = QString::number(offset);
            ui->txtOffset->setText(qoffset);
            ui->txtOffset_2->setText(qoffset);
            break;
        }
    }
}

void MainWindow::on_cmbRefSeq_2_activated(int index)
{
    if(index == 0) return;

    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    ui->cmbRefSeq->setCurrentIndex(index);
    ui->cmbRefSeq_3->setCurrentIndex(index);

    for(int i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            //QMessageBox::information(this,"a",alinhamentos.at(i).sequencenames[index-1].c_str());
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[index-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = QString::number(offset);
            ui->txtOffset->setText(qoffset);
            ui->txtOffset_2->setText(qoffset);
            break;
        }
    }
}



void MainWindow::on_cmbRefSeq_3_activated(int index)
{
    if(index == 0) return;

    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    ui->cmbRefSeq->setCurrentIndex(index);
    ui->cmbRefSeq_2->setCurrentIndex(index);

    for(int i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            //QMessageBox::information(this,"a",alinhamentos.at(i).sequencenames[index-1].c_str());
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[index-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = QString::number(offset);
            ui->txtOffset->setText(qoffset);
            ui->txtOffset_2->setText(qoffset);
            break;
        }
    }
}
/*
void MainWindow::on_lstRefSeqs_itemSelectionChanged()
{
    //QModelIndexList indexes = ui->lstRefSeqs->selectionModel()->selectedIndexes();

    std::vector<int> indexList;
    foreach(QModelIndex index, indexes)
    {
        indexList.push_back(index.row());
    }

    ui->lstRefSeqs_2->clearSelection();

    for(int i=0; i < indexList.size(); i++){
        ui->lstRefSeqs_2->item(indexList[i])->setSelected(true);
    }
}
*/


void MainWindow::on_lstRefSeqs_2_itemSelectionChanged()
{
    /*
    QModelIndexList indexes = ui->lstRefSeqs_2->selectionModel()->selectedIndexes();

    std::vector<int> indexList;
    foreach(QModelIndex index, indexes)
    {
        indexList.push_back(index.row());
    }

    ui->lstRefSeqs->clearSelection();

    for(int i=0; i < indexList.size(); i++){
        ui->lstRefSeqs->item(indexList[i])->setSelected(true);
    }
    */
}

void MainWindow::on_cmdSaveResults_clicked()
{
    ui->cmdSaveResults->setEnabled(false);

    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    string alignfilename = ui->listWidget->currentItem()->text().toStdString();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    vector<string> vecPath = split(alinhamentos[i].getFilepath(),'.');
    string path = "";

    for(int i=0;i<vecPath.size()-1;i++){
        path += vecPath[i];
    }
    path += ".xml";

    alinhamentos[i].generateXML(path);

    QMessageBox::information(this,"Save Results","XML generated successfully");

    ui->cmdSaveResults->setEnabled(true);
}

void MainWindow::on_cmdShowResults_clicked()
{
    ui->cmdShowResults->setEnabled(false);
    this->resultsStackList.clear();

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select a alignment.");
        ui->cmdShowResults->setEnabled(true);
        return;
    }

    stackBeforeShowResults = ui->stackedWidget->currentIndex();

    ui->stackedWidget2->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(6);

    ui->listWidget->setEnabled(false);
    ui->listWidget2->setEnabled(false);

    string alignfilename = ui->listWidget->currentItem()->text().toStdString();
    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            //fullAlignment = alinhamentos[i];
            break;
        }
    }

    ui->lblHidden->setText(QString::number(i));

    //Verificar resultados possiveis

    //List Of Sequences after filter
    ui->checkResults1->setEnabled(true);

    //Table Of Frequence Conservation
    if(alinhamentos[i].getConsFreqSize() > 0) ui->checkResults2->setEnabled(true);
    else ui->checkResults2->setEnabled(false);

    //Table Of Percentage Conservation
    if(alinhamentos[i].getConsFreqPercSize() > 0) ui->checkResults3->setEnabled(true);
    else ui->checkResults3->setEnabled(false);

    //Conserved Residues
    if(alinhamentos[i].getConsRefsSize() > 0) ui->checkResults4->setEnabled(true);
    else ui->checkResults4->setEnabled(false);

    //Correlation and Anti-Correlation List
    if(alinhamentos[i].getCorrGraphSize() > 0) ui->checkResults5->setEnabled(true);
    else ui->checkResults5->setEnabled(false);

    //List Of Communities
    if(alinhamentos[i].getCommListSize() > 0) ui->checkResults6->setEnabled(true);
    else ui->checkResults6->setEnabled(false);

    //Correlation Tables
    if(alinhamentos[i].getNumOfUtilComms() > 0){
        ui->checkResults7->setEnabled(true);
        ui->checkResults8->setEnabled(true);
        ui->checkResults9->setEnabled(true);
    }else{
        ui->checkResults7->setEnabled(false);
        ui->checkResults8->setEnabled(false);
        ui->checkResults9->setEnabled(false);
    }

    //Residues Of Communities CONTINUAR
    if(alinhamentos[i].getCorrRefSeqsSize() > 0 && alinhamentos[i].getNumOfUtilComms() > 0) ui->checkResults10->setEnabled(true);
    else ui->checkResults10->setEnabled(false);

    ui->cmdMain->setEnabled(true);
    ui->cmdBack->setEnabled(true);
    ui->cmdAdvance->setEnabled(false);
    ui->cmdSaveResults->setEnabled(true);
}

void MainWindow::on_cmdShow_clicked()
{
    ui->cmdShow->setEnabled(false);
    ui->cmdNextResult->setVisible(true);
    ui->cmdBackResult->setVisible(true);
    this->resultsStackList.clear();

    //Validação dos Dados

    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        ui->cmdShow->setEnabled(true);
        return;
    }

    string alignfilename = ui->listWidget->currentItem()->text().toStdString();
    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            //fullAlignment = alinhamentos[i];
            break;
        }
    }

    //Resetar campos de resultado
    ui->lstProteinsFiltered->clear();
    ui->txtSequence->clear();
    ui->tableFreq->clearContents();
    ui->tableFreqPerc->clearContents();
    ui->treeCorrelation->clear();
    ui->treeCorrelationComm->clear();
    ui->tableComm1->clear();
    ui->tableComm2->clear();
    ui->tableAdherence->clear();


    //Controle do Stack2
    if(ui->checkResults1->isChecked()){ this->resultsStackList.push_back(1); this->listSequences(i); }
    if(ui->checkResults2->isChecked()){ this->resultsStackList.push_back(2); this->tableFreq(i); }
    if(ui->checkResults3->isChecked()){ this->resultsStackList.push_back(3); this->tableFreqPerc(i); }
    if(ui->checkResults4->isChecked()){ this->resultsStackList.push_back(4); this->showConservedResidues(i); }
    if(ui->checkResults5->isChecked()){ this->resultsStackList.push_back(5); this->correlationList(i); }
    if(ui->checkResults6->isChecked()){ this->resultsStackList.push_back(6); this->communitiesList(i); }
    if(ui->checkResults7->isChecked()){ this->resultsStackList.push_back(7); this->corrTable1(i); }
    if(ui->checkResults8->isChecked()){ this->resultsStackList.push_back(8); this->corrTable2(i); }
    if(ui->checkResults9->isChecked()){ this->resultsStackList.push_back(9); this->adh(i); }
    if(ui->checkResults10->isChecked()){ this->resultsStackList.push_back(10); this->showResiduesComm(i); }

    if(this->resultsStackList.size() == 0){
        QMessageBox::warning(this,"Warning","You must check at least one visualization.");
        ui->cmdShow->setEnabled(true);
        return;
    }

    int firstResult = this->resultsStackList[0];
    this->currentStackPos = 0;

    switch(firstResult){
    case 1://List of sequences after filter
        ui->stackedWidget2->setCurrentIndex(1);
        break;
    case 2://Table Of Frequence Conservation
        ui->stackedWidget2->setCurrentIndex(2);
        break;
    case 3://Table Of Frequence Conservation in Percentage
        ui->stackedWidget2->setCurrentIndex(3);
        break;
    case 4://Conserved Residues
        ui->stackedWidget2->setCurrentIndex(4);
        break;
    case 5://Correlations
        ui->stackedWidget2->setCurrentIndex(5);
        break;
    case 6://Communities List
        ui->stackedWidget2->setCurrentIndex(6);
        break;
    case 7://Correlation Tables Percentage
        ui->stackedWidget2->setCurrentIndex(7);
        //ui->lblHidden1->setText(QString::number(i)); //Salva posição do alinhamento num label escondido
        break;
    case 8://Correlation Tables Log P
        ui->stackedWidget2->setCurrentIndex(8);
        //ui->lblHidden2->setText(QString::number(i));
        break;
    case 9://Adherence
        ui->stackedWidget2->setCurrentIndex(9);
        break;
    case 10://Residues Of Communities
        ui->stackedWidget2->setCurrentIndex(10);
        break;
    default://Error
        QMessageBox::critical(this,"Error","Cant find the results.");
    }

    ui->cmdShow->setEnabled(true);
}

void MainWindow::on_lstProteinsFiltered_activated(const QModelIndex &index)
{
    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    string sequence = alinhamentos[i].getSequence(ui->lstProteinsFiltered->currentItem()->text().toStdString());

    ui->txtSequence->setText(sequence.c_str());
}

void MainWindow::on_cmdNextComm_clicked()
{
    int ai = ui->lblHidden->text().toInt();

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]);
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str());
    }

    //Verificar se comunidade existe ou resetar
    int nComm = alinhamentos[ai].getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableComm1->clear();

    //Modifica parâmetros
    temp = "Comunidade " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade->setText(temp.c_str());

    //Monta a Tabela
    vector<string> residues = alinhamentos[ai].getResiduesComm(currComm);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = alinhamentos[ai].getCommAll(currComm);

    for(int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = alinhamentos[ai].getCommXRow(currComm,i);
        for(int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1){
                strTemp = "X";
                item2->setText(strTemp);
            }else{
                strTemp = QString::number(commRow[j],'f',4);
                item2->setData(Qt::DisplayRole,strTemp.toFloat()*100);
            }
            ui->tableComm1->setItem(i,j+1,item2);
        }
    }

    //AJusta o tamanho das colunas
    ui->tableComm1->resizeColumnsToContents();
}

void MainWindow::on_cmdBackComm_clicked()
{
    int ai = ui->lblHidden->text().toInt();

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]) -1;
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str()) -1;
    }

    //Verificar se comunidade existe ou resetar
    int nComm = alinhamentos[ai].getNumOfUtilComms();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableComm1->clear();

    //Modifica parâmetros
    temp = "Comunidade " + QString::number(currComm).toStdString();
    ui->lblComunidade->setText(temp.c_str());

    //Monta a Tabela
    vector<string> residues = alinhamentos[ai].getResiduesComm(currComm-1);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = alinhamentos[ai].getCommAll(currComm-1);

    for(int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = alinhamentos[ai].getCommXRow(currComm-1,i);
        for(int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1){
                strTemp = "X";
                item2->setText(strTemp);
            }else{
                strTemp = QString::number(commRow[j],'f',4);
                item2->setData(Qt::DisplayRole,strTemp.toFloat()*100);
            }
            ui->tableComm1->setItem(i,j+1,item2);
        }
    }

    //AJusta o tamanho das colunas
    ui->tableComm1->resizeColumnsToContents();
}

void MainWindow::on_cmdNextComm_2_clicked()
{
    int ai = ui->lblHidden->text().toInt();

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade_2->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]);
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str());
    }

    //Verificar se comunidade existe ou resetar
    int nComm = alinhamentos[ai].getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableComm2->clear();

    //Modifica parâmetros
    temp = "Comunidade " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_2->setText(temp.c_str());

    //Montar a Tabela
    vector<string> residues = alinhamentos[ai].getResiduesCommPs(currComm);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(int i = 0; i < residues.size(); i++){
        vector<int> commRow = alinhamentos[ai].getCommPsRow(currComm,i);

        for(int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1) item2->setText("X");
            else item2->setData(Qt::DisplayRole,commRow[j]);

            ui->tableComm2->setItem(i,j,item2);
        }
    }

    //Ajusta tamanho das colunas
    ui->tableComm2->resizeColumnsToContents();
}

void MainWindow::on_cmdBackComm_2_clicked()
{
    int ai = ui->lblHidden->text().toInt();

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade_2->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]) -1;
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str()) -1;
    }

    //Verificar se comunidade existe ou resetar
    int nComm = alinhamentos[ai].getNumOfUtilComms();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableComm2->clear();

    //Modifica parâmetros
    temp = "Comunidade " + QString::number(currComm).toStdString();
    ui->lblComunidade_2->setText(temp.c_str());

    //Montar a Tabela
    vector<string> residues = alinhamentos[ai].getResiduesCommPs(currComm -1);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(int i = 0; i < residues.size(); i++){
        vector<int> commRow = alinhamentos[ai].getCommPsRow(currComm-1,i);

        for(int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1) item2->setText("X");
            else item2->setData(Qt::DisplayRole,commRow[j]);

            ui->tableComm2->setItem(i,j,item2);
        }
    }

    //Ajusta tamanho das colunas
    ui->tableComm2->resizeColumnsToContents();
}

void MainWindow::on_cmdNextResult_clicked()
{
    ui->cmdNextResult->setEnabled(false);

    if(this->currentStackPos + 1 >= this->resultsStackList.size()) this->currentStackPos = 0;
    else this->currentStackPos++;

    int result = this->resultsStackList[currentStackPos];
    int i = ui->lblHidden->text().toInt();

    switch(result){
    case 1://List of sequences after filter
        ui->stackedWidget2->setCurrentIndex(1);
        //this->listSequences(i);
        break;
    case 2://Table Of Frequence Conservation
        ui->stackedWidget2->setCurrentIndex(2);
        //this->tableFreq(i);
        break;
    case 3://Table Of Frequence Conservation in Percentage
        ui->stackedWidget2->setCurrentIndex(3);
        //this->tableFreqPerc(i);
        break;
    case 4://Conserved Residues
        ui->stackedWidget2->setCurrentIndex(4);
        break;
    case 5://Correlations
        ui->stackedWidget2->setCurrentIndex(5);
        //this->correlationList(i);
        break;
    case 6://Communities List
        ui->stackedWidget2->setCurrentIndex(6);
        //this->communitiesList(i);
        break;
    case 7://Correlation Tables Percentage
        ui->stackedWidget2->setCurrentIndex(7);
        //ui->lblHidden1->setText(QString::number(i)); //Salva posição do alinhamento num label escondido
        //this->corrTable1(i);
        break;
    case 8://Correlation Tables Log P
        ui->stackedWidget2->setCurrentIndex(8);
        //ui->lblHidden2->setText(QString::number(i));
        //this->corrTable2(i);
        break;
    case 9://Adherence
        ui->stackedWidget2->setCurrentIndex(9);
        //this->adh(i);
        break;
    case 10://Residues Of Communities
        ui->stackedWidget2->setCurrentIndex(10);
        break;
    default://Error
        QMessageBox::critical(this,"Error","Cant find the results.");
    }

    ui->cmdNextResult->setEnabled(true);
}

void MainWindow::on_cmdBackResult_clicked()
{
    ui->cmdBackResult->setEnabled(false);

    if(this->currentStackPos - 1 < 0) this->currentStackPos = this->resultsStackList.size()-1;
    else this->currentStackPos--;

    int result = this->resultsStackList[currentStackPos];
    int i = ui->lblHidden->text().toInt();

    switch(result){
    case 1://List of sequences after filter
        ui->stackedWidget2->setCurrentIndex(1);
        //this->listSequences(i);
        break;
    case 2://Table Of Frequence Conservation
        ui->stackedWidget2->setCurrentIndex(2);
        //this->tableFreq(i);
        break;
    case 3://Table Of Frequence Conservation in Percentage
        ui->stackedWidget2->setCurrentIndex(3);
        //this->tableFreqPerc(i);
        break;
    case 4://Conserved Residues
        ui->stackedWidget2->setCurrentIndex(4);
        break;
    case 5://Correlations
        ui->stackedWidget2->setCurrentIndex(5);
        //this->correlationList(i);
        break;
    case 6://Communities List
        ui->stackedWidget2->setCurrentIndex(6);
        //this->communitiesList(i);
        break;
    case 7://Correlation Tables Percentage
        ui->stackedWidget2->setCurrentIndex(7);
        //ui->lblHidden1->setText(QString::number(i)); //Salva posição do alinhamento num label escondido
        //this->corrTable1(i);
        break;
    case 8://Correlation Tables Log P
        ui->stackedWidget2->setCurrentIndex(8);
        //ui->lblHidden2->setText(QString::number(i));
        //this->corrTable2(i);
        break;
    case 9://Adherence
        ui->stackedWidget2->setCurrentIndex(9);
        //this->adh(i);
        break;
    case 10://Residues Of Communities
        ui->stackedWidget2->setCurrentIndex(10);
        break;
    default://Error
        QMessageBox::critical(this,"Error","Cant find the results.");
    }

    ui->cmdBackResult->setEnabled(true);
}

void MainWindow::on_cmdNextResComm_clicked()
{
    ui->cmdNextResComm->setEnabled(false);

    int ai = ui->lblHidden->text().toInt();

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade_3->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]);
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str());
    }

    //Verificar se comunidade existe ou resetar
    int nComm = alinhamentos[ai].Communities.size();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableResiduesComm->clear();

    //Modifica parâmetros
    temp = "Comunidade " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_3->setText(temp.c_str());

    vector<int> refSeqs;

    QModelIndexList indexList = ui->lstRefSeqs_2->selectionModel()->selectedIndexes();
    for(int j = 0; j < indexList.size(); j++){
        refSeqs.push_back(indexList.at(j).row());
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(alinhamentos[ai].Communities[currComm].pos.size());
    for(int i = 0; i < alinhamentos[ai].Communities[currComm].pos.size(); i++){
        string textCab = alinhamentos[ai].Communities[currComm].aa[i] + QString::number(alinhamentos[ai].Communities[currComm].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(alinhamentos[ai].sequencenames[refSeqs[i]].c_str()));

        for(int j = 0; j < alinhamentos[ai].Communities[currComm].pos.size(); j++){
            if(alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[currComm].pos[j]]==alinhamentos[ai].Communities[currComm].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = alinhamentos[ai].Communities[currComm].aa[j] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,alinhamentos[ai].Communities[currComm].pos[j])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[currComm].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[currComm].pos[j]] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,alinhamentos[ai].Communities[currComm].pos[j])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableResiduesComm->setItem(i,j,item);
                }
            }
        }
    }

    //Ajusta tamanho das colunas
    ui->tableResiduesComm->resizeColumnsToContents();

    ui->cmdNextResComm->setEnabled(true);
}

void MainWindow::on_cmdBackResComm_clicked()
{
    ui->cmdBackResComm->setEnabled(false);

    int ai = ui->lblHidden->text().toInt();

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade_3->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]) -1;
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str())-1;
    }

    //Verificar se comunidade existe ou resetar
    int nComm = alinhamentos[ai].Communities.size();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableResiduesComm->clear();

    //Modifica parâmetros
    temp = "Comunidade " + QString::number(currComm).toStdString();
    ui->lblComunidade_3->setText(temp.c_str());

    vector<int> refSeqs;

    QModelIndexList indexList = ui->lstRefSeqs_2->selectionModel()->selectedIndexes();
    for(int j = 0; j < indexList.size(); j++){
        refSeqs.push_back(indexList.at(j).row());
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(alinhamentos[ai].Communities[currComm -1].pos.size());
    for(int i = 0; i < alinhamentos[ai].Communities[currComm -1].pos.size(); i++){
        string textCab = alinhamentos[ai].Communities[currComm -1].aa[i] + QString::number(alinhamentos[ai].Communities[currComm-1].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(alinhamentos[ai].sequencenames[refSeqs[i]].c_str()));

        for(int j = 0; j < alinhamentos[ai].Communities[currComm -1].pos.size(); j++){
            if(alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[currComm-1].pos[j]]==alinhamentos[ai].Communities[currComm-1].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = alinhamentos[ai].Communities[currComm-1].aa[j] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,alinhamentos[ai].Communities[currComm-1].pos[j])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[currComm-1].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = alinhamentos[ai].sequences[refSeqs[i]][alinhamentos[ai].Communities[currComm-1].pos[j]] + QString::number(alinhamentos[ai].AlignNumbering2Sequence(refSeqs[i]+1,alinhamentos[ai].Communities[currComm-1].pos[j])+GetOffsetFromSeqName(alinhamentos[ai].sequencenames[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableResiduesComm->setItem(i,j,item);
                }
            }
        }
    }

    //Ajusta tamanho das colunas
    ui->tableResiduesComm->resizeColumnsToContents();

    ui->cmdBackResComm->setEnabled(true);
}

void MainWindow::Open_XML_triggered(){
    QXmlStreamReader reader;

    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("XML Files (*.xml)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    reader.setDevice(&file);

    Alignment align;
    align.setFilepath(fileName.toStdString());
    align.setLocalDir(fileName.toStdString());
    //NO FINAL INSERIR NO ALINHAMENTOS E NA LISTWIDGET

    //QMessageBox::information(this,"ok","ok");

    reader.readNext();

    while(!reader.atEnd()){
        //<FILE>
        if(reader.isStartElement() && reader.name() == "file"){
            while(!reader.atEnd()){
                reader.readNext();

                if(reader.isStartElement()){
                    if(reader.name() == "local")
                        align.setLocalDir(reader.readElementText().toStdString());
                    else if( reader.name() == "web")
                        align.setWebDir(reader.readElementText().toStdString());
                    else if(reader.name() == "pdb")
                        align.setLocalPDBDir(reader.readElementText().toStdString());
                    else{
                        QMessageBox::critical(this,"ERROR","Error parsing this XML file. It may be corrupted");
                        //LIBERAR DA MEMORIA E DELETAR O NOVO ALINHAMENTO
                        return;
                    }
                }else if(reader.isEndElement() && reader.name() == "file"){
                    break;
                }
            }
        }

        //FILTER
        if(reader.isStartElement() && reader.name() == "filters"){
            while(!reader.atEnd()){
                reader.readNext();

                if(reader.isStartElement() && reader.name() == "filter"){
                    string occ = reader.attributes().value("occ").toString().toStdString();
                    string minid = reader.attributes().value("minid").toString().toStdString();
                    string maxid = reader.attributes().value("maxid").toString().toStdString();
                    string refSeq = reader.attributes().value("refseq").toString().toStdString();
                    string parameters = occ + " " + minid + " " + maxid + " " + refSeq;
                    vector<string> namesVec;
                    vector<string> sequencesVec;
                    namesVec.push_back(parameters);
                    sequencesVec.push_back(parameters);

                    while(!reader.atEnd()){
                        reader.readNext();

                        if(reader.isStartElement()){
                            if(reader.name() == "entry"){
                                string offset = reader.attributes().value("offset").toString().toStdString();
                                string protName = reader.attributes().value("name").toString().toStdString();
                                string pfamName = protName + "/" + offset;
                                string sequence = reader.readElementText().toStdString();
                                namesVec.push_back(pfamName);
                                sequencesVec.push_back(sequence);
                            }
                        }else if(reader.isEndElement() && reader.name() == "filter"){
                            align.addFilterSequence(namesVec,sequencesVec);

                            //for(int i = 0; i < namesVec.size(); i++)
                                //printf("%d - %s\n",i,namesVec[i].c_str());

                            namesVec.clear();
                            sequencesVec.clear();

                            break;
                        }
                    }
                }else if(reader.isEndElement() && reader.name() == "filters")
                    break;
            }
        }

        //CONSERVATION
        vector<float> dg;
        if(reader.isStartElement() && reader.name() == "conservation"){
            while(!reader.atEnd()){
                reader.readNext();

                if(reader.isStartElement()){
                    if(reader.name() == "parameters"){
                        string filter;
                        int refseq;
                        int offset;
                        char chain;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "parameters"){
                                align.addParameter("conservation",filter,refseq,offset,chain,0);
                                break;
                            }
                            else if(reader.isStartElement()){
                                if(reader.name() == "filter"){
                                    filter = reader.readElementText().toStdString();
                                }else if(reader.name() == "refseq"){
                                    refseq = reader.readElementText().toInt();
                                }else if(reader.name() == "offset"){
                                    offset = reader.readElementText().toInt();
                                }else if(reader.name() == "chain"){
                                    chain = reader.readElementText().toStdString()[0];
                                }
                            }

                        }

                    }else if(reader.name() == "positions"){
                        vector<int> freq;
                        vector<float> freqPerc;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "positions"){
                                break;
                            }
                            else if(reader.isStartElement() && reader.name() == "pos"){
                               while(!reader.atEnd()){
                                   reader.readNext();

                                   if(reader.isEndElement() && reader.name() == "pos"){
                                       align.addConsFreqRow(freq);
                                       align.addConsFreqPercRow(freqPerc);
                                       freq.clear();
                                       freqPerc.clear();
                                       break;
                                   }
                                   else if(reader.isStartElement()){
                                       if(reader.name() == "deltaG")
                                           dg.push_back(reader.readElementText().toFloat());
                                       else if(reader.name() == "frequence")
                                           freq.push_back(reader.readElementText().toInt());
                                       else if(reader.name() == "percent")
                                           freqPerc.push_back(reader.readElementText().toFloat());
                                   }
                               }
                            }
                        }
                    }else if(reader.name() == "references"){
                        string prot;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "references"){
                                 break;
                            }else if(reader.isStartElement() && reader.name() == "protein"){
                                prot = reader.readElementText().toStdString();
                                align.addConsRef(prot);
                            }
                        }
                    }
                }else if(reader.isEndElement() && reader.name() == "conservation"){
                    align.setConsDG(dg);
                    //align.printConsFreq();
                    //align.printConsFreqPerc();
                    break;
                }
            }
        }

        //MINSS
        if(reader.isStartElement() && reader.name() == "minss"){
            vector<float> minss;
            while(!reader.atEnd()){
                reader.readNext();

                if(reader.isStartElement()){
                    if(reader.name() == "parameters"){
                        string filter;
                        int rep;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "parameters"){
                                align.addParameter("minss",filter,rep);
                                break;
                            }
                            else if(reader.isStartElement()){
                                if(reader.name() == "filter")
                                    filter = reader.readElementText().toStdString();
                                else if(reader.name() == "repetitions")
                                    rep = reader.readElementText().toInt();
                            }
                        }
                    }else if(reader.name() == "data"){
                        minss.push_back(reader.readElementText().toFloat());
                    }
                }else if(reader.isEndElement() && reader.name() == "minss"){
                    align.setMinssVector(minss);
                    break;
                }
            }
        }

        //CORRELATION
        if(reader.isStartElement() && reader.name() == "correlation"){


            while(!reader.atEnd()){
                reader.readNext();

                if(reader.isStartElement()){
                    if(reader.name() == "parameters"){
                        string filter;
                        int minlogp;
                        float minss;
                        float deltafreq;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "parameters"){
                                align.addParameter("correlation",filter,minlogp,minss,deltafreq);
                                break;
                            }else if(reader.isStartElement()){
                                if(reader.name() == "filter")
                                    filter = reader.readElementText().toStdString();
                                else if(reader.name() == "minlog")
                                    minlogp = reader.readElementText().toInt();
                                else if(reader.name() == "minss")
                                    minss = reader.readElementText().toFloat();
                                else if(reader.name() == "deltafreq")
                                    deltafreq = reader.readElementText().toFloat();
                            }
                        }
                    }else if(reader.name() == "corrgraph"){
                        string v1;
                        string v2;
                        int e;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "corrgraph"){
                                //align.printCorrGraph();
                                break;
                            }else if(reader.isStartElement()){
                                if(reader.name() == "edge"){
                                    v1 = reader.attributes().value("v1").toString().toStdString();
                                    v2 = reader.attributes().value("v2").toString().toStdString();
                                    e = reader.readElementText().toInt();

                                    //printf("V1: %s, V2: %s, E: %d\n",v1.c_str(),v2.c_str(),e);

                                    align.addCorrGraphEdge(v1,v2,e);
                                }
                            }
                        }
                    }else if(reader.name() == "communities"){
                        vector<string> comm;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "communities"){
                                //align.printCommunity();
                                break;
                            }else if(reader.isStartElement()){
                                if(reader.name() == "community"){
                                    comm.clear();
                                    string node;

                                    while(!reader.atEnd()){
                                        reader.readNext();

                                        if(reader.isStartElement() && reader.name() == "node"){
                                            node = reader.readElementText().toStdString();
                                            comm.push_back(node);
                                        }else if(reader.isEndElement() && reader.name() == "community"){
                                            align.addCommunity(comm);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }else if(reader.name() == "references"){
                        string prot;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "references"){
                                //align.printCorrRefSeqs();
                                break;
                            }else if(reader.isStartElement() && reader.name() == "protein"){
                                prot = reader.readElementText().toStdString();
                                align.addCorrRefSeq(prot);
                            }
                        }
                    }else if(reader.name() == "output"){
                        vector<string> residues;
                        vector<string> residuesPs;

                        while(!reader.atEnd()){
                            reader.readNext();

                            if(reader.isEndElement() && reader.name() == "output"){
                                //align.printResiduesComm();
                                //align.printResiduesCommPs();
                                break;
                            }else if(reader.isStartElement()){
                                if(reader.name() == "community"){
                                    vector<float> resAll;
                                    vector<vector<float> > commX;
                                    residues.clear();

                                    while(!reader.atEnd()){
                                        reader.readNext();

                                        if(reader.isEndElement() && reader.name() == "community"){
                                            align.addResiduesComm(residues);
                                            align.addCommXAll(resAll);
                                            align.addCommX(commX);
                                            break;
                                        }else if(reader.isStartElement() && reader.name() == "column"){
                                            string res = reader.readElementText().toStdString();
                                            if(res != "ALL") residues.push_back(res);
                                        }else if(reader.isStartElement() && reader.name() == "row"){
                                            vector<float> values;

                                            resAll.push_back(reader.attributes().at(1).value().toFloat());

                                            for(int i = 2; i < reader.attributes().size(); i++){
                                                values.push_back(reader.attributes().at(i).value().toFloat()/100);
                                            }

                                            commX.push_back(values);
                                        }
                                    }
                                }else if(reader.name() == "logP"){
                                    vector<vector<int> > commXPs;
                                    residuesPs.clear();

                                    while(!reader.atEnd()){
                                        reader.readNext();

                                        if(reader.isEndElement() && reader.name() == "logP"){
                                            align.addResiduesCommPs(residuesPs);
                                            align.addCommXps(commXPs);
                                            break;
                                        }else if(reader.isStartElement() && reader.name() == "column")
                                            residuesPs.push_back(reader.readElementText().toStdString());
                                        else if(reader.isStartElement() && reader.name() == "row"){
                                            vector<int> values;

                                            for(int i = 1; i < reader.attributes().size(); i++){
                                                values.push_back(reader.attributes().at(i).value().toInt());
                                            }

                                            commXPs.push_back(values);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        reader.readNext();
    }

    //QMessageBox::information(this,"a","ACABOU");
    align.updateFullAlignment();
    align.getCommunitiesFromRAM();
    //align.CalculateFrequencies();
    align.printFrequencies();
    ui->listWidget->addItem(fileName);
    alinhamentos.push_back(align);

    if(ui->stackedWidget->currentIndex() == 0){
        //Ativa botões do Wizard
        changeWizardCmds(true);

        //Desativa botao voltar
        ui->cmdBack->setEnabled(false);

        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_cmdRemoveFilter_clicked()
{

    if(ui->listWidget2->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a filter to remove.");
        return;
    }
    string filter = ui->listWidget2->currentItem()->text().toStdString();

    if(filter == "Full Alignment"){
        QMessageBox::warning(this,"Error","You cant remove full alignment.");
        return;
    }

    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    int pos = ui->listWidget2->currentIndex().row();
    alinhamentos[i].removeFilterItem(pos);
    delete ui->listWidget2->item(pos);
}

void MainWindow::on_cmdRemoveAlignment_clicked()
{
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to remove.");
        return;
    }

    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            //alinhamentos[i].clear();
            //alinhamentos[i].shrink_to_fit();
            break;
        }
    }

    alinhamentos.erase(alinhamentos.begin() + i);
    delete ui->listWidget->item(i);
    ui->listWidget2->clear();
}

void MainWindow::exportAlignment_PFAM(){
    string filter;

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to remove.");
        return;
    }

    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(ui->listWidget2->currentItem() == NULL)
        filter = "Full Alignment";
    else
        filter = ui->listWidget2->currentItem()->text().toStdString();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt *.pfam *.xml)"));

    alinhamentos[i].exportAlignment(filename,filter,0);

}

void MainWindow::exportAlignment_TXT(){
    string filter;

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to remove.");
        return;
    }

    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(ui->listWidget2->currentItem() == NULL)
        filter = "Full Alignment";
    else
        filter = ui->listWidget2->currentItem()->text().toStdString();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt *.pfam)"));

    alinhamentos[i].exportAlignment(filename,filter,1);

}

void MainWindow::exportAlignment_XML(){
    string filter;

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(ui->listWidget2->currentItem() == NULL)
        filter = "Full Alignment";
    else
        filter = ui->listWidget2->currentItem()->text().toStdString();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportAlignment(filename,filter,2);

}

void MainWindow::exportFreqTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportFreq(filename,0);
}

void MainWindow::exportFreqCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("CSV Files (*.txt *.csv)"));

    alinhamentos[i].exportFreq(filename,1);
}

void MainWindow::exportFreqXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportFreq(filename,2);
}

void MainWindow::exportFreqHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    alinhamentos[i].exportFreq(filename,3);

}

void MainWindow::exportFreqPercTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportFreq(filename,0,true);
}

void MainWindow::exportFreqPercCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt *.csv)"));

    alinhamentos[i].exportFreq(filename,1,true);
}

void MainWindow::exportFreqPercXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportFreq(filename,2,true);
}

void MainWindow::exportFreqPercHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    alinhamentos[i].exportFreq(filename,3,true);
}

void MainWindow::exportConsResTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    if(alinhamentos[i].getConsRefsSize() == 0){
        QMessageBox::warning(this,"Warning","You didnt set some referesence sequences to visualize.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    vector<int> refSeqs;
    for(int i2 = 0; i2 < alinhamentos[i].getConsRefsSize(); i2++){
        string ref1 = alinhamentos[i].getConsref(i2);
        printf("%s\n",ref1.c_str());
        for(int j = 0; j < ui->lstRefSeqs->count(); j++){
            string ref2 = ui->lstRefSeqs->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    //QMessageBox::information(this,"",QString::number(refSeqs.size()));

    alinhamentos[i].exportConsRes(filename,0,ui->txtMinConserv->value(),refSeqs);
}

void MainWindow::exportConsResXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    if(alinhamentos[i].getConsRefsSize() == 0){
        QMessageBox::warning(this,"Warning","You didnt set some referesence sequences to visualize.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    vector<int> refSeqs;
    for(int i2 = 0; i2 < alinhamentos[i].getConsRefsSize(); i2++){
        string ref1 = alinhamentos[i].getConsref(i2);
        printf("%s\n",ref1.c_str());
        for(int j = 0; j < ui->lstRefSeqs->count(); j++){
            string ref2 = ui->lstRefSeqs->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    //QMessageBox::information(this,"",QString::number(refSeqs.size()));

    alinhamentos[i].exportConsRes(filename,1,ui->txtMinConserv->value(),refSeqs);
}

void MainWindow::exportConsResHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    if(alinhamentos[i].getConsRefsSize() == 0){
        QMessageBox::warning(this,"Warning","You didnt set some referesence sequences to visualize.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    vector<int> refSeqs;
    for(int i2 = 0; i2 < alinhamentos[i].getConsRefsSize(); i2++){
        string ref1 = alinhamentos[i].getConsref(i2);
        printf("%s\n",ref1.c_str());
        for(int j = 0; j < ui->lstRefSeqs->count(); j++){
            string ref2 = ui->lstRefSeqs->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    //QMessageBox::information(this,"",QString::number(refSeqs.size()));

    alinhamentos[i].exportConsRes(filename,2,ui->txtMinConserv->value(),refSeqs);
}

void MainWindow::exportCorrListTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportCorrGraph(filename,0);
}

void MainWindow::exportCorrListCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt *.csv)"));

    alinhamentos[i].exportCorrGraph(filename,1);
}

void MainWindow::exportCorrListXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportCorrGraph(filename,2);
}

void MainWindow::exportCommsTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportCommList(filename,0);
}

void MainWindow::exportCommsXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportCommList(filename,1);
}

void MainWindow::exportCorrTablePercTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportCorrTable(filename,0);
}

void MainWindow::exportCorrTablePercXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportCorrTable(filename,1);
}

void MainWindow::exportCorrTablePercHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    alinhamentos[i].exportCorrTable(filename,2);
}

void MainWindow::exportCorrTableTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportCorrTable(filename,0,false);
}

void MainWindow::exportCorrTableXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportCorrTable(filename,1,false);
}

void MainWindow::exportCorrTableHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    alinhamentos[i].exportCorrTable(filename,2,false);
}

void MainWindow::exportAdhTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportAdh(filename,0);
}

void MainWindow::exportAdhCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.csv)"));

    alinhamentos[i].exportAdh(filename,1);
}

void MainWindow::exportAdhXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    alinhamentos[i].exportAdh(filename,2);
}

void MainWindow::exportAdhHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    alinhamentos[i].exportAdh(filename,3);
}

void MainWindow::exportResCommTXT(){
    vector<int> refSeqs;

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    alinhamentos[i].CalculateFrequencies();


    for(int i1 = 0; i1 < alinhamentos[i].getCorrRefSeqsSize(); i1++){
        string ref1 = alinhamentos[i].getCorrRefSeq(i1);

        for(int j = 0; j < ui->lstRefSeqs_2->count(); j++){
            string ref2 = ui->lstRefSeqs_2->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("TEXT Files (*.txt)"));

    alinhamentos[i].exportResComm(filename,0,refSeqs);
}

void MainWindow::exportResCommXML(){
    vector<int> refSeqs;

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    alinhamentos[i].CalculateFrequencies();


    for(int i1 = 0; i1 < alinhamentos[i].getCorrRefSeqsSize(); i1++){
        string ref1 = alinhamentos[i].getCorrRefSeq(i1);

        for(int j = 0; j < ui->lstRefSeqs_2->count(); j++){
            string ref2 = ui->lstRefSeqs_2->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("XML Files (*.xml)"));

    //CONTINUAR, BUG-CRASH
    alinhamentos[i].exportResComm(filename,1,refSeqs);
}

void MainWindow::exportResCommHTML(){
    vector<int> refSeqs;

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    string align = ui->listWidget->currentItem()->text().toUtf8().constData();

    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(align == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    if(alinhamentos[i].getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    alinhamentos[i].CalculateFrequencies();


    for(int i1 = 0; i1 < alinhamentos[i].getCorrRefSeqsSize(); i1++){
        string ref1 = alinhamentos[i].getCorrRefSeq(i1);

        for(int j = 0; j < ui->lstRefSeqs_2->count(); j++){
            string ref2 = ui->lstRefSeqs_2->item(j)->text().toStdString();
            if(ref1 == ref2){
                refSeqs.push_back(j);
                break;
            }
        }
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),"/home",QObject::tr("HTML Files (*.html)"));

    alinhamentos[i].exportResComm(filename,2,refSeqs);
}

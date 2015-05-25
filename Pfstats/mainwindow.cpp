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
    ui->graficMinss->setVisible(false);

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
    ui->cmbRefSeq_3->setCurrentIndex(0);
    //ui->lstRefSeqs->clear();
    ui->lstRefSeqs_2->clear();
    ui->txtOffset->clear();
    ui->txtOffset_2->clear();
    ui->txtChain->clear();
    ui->txtNoAlignments->setValue(100);
    ui->graficMinss->clearGraphs();
    ui->txtMinScore->setValue(10);
    ui->txtMinssFraction->setValue(0.2);
    ui->txtMinDeltaFreq->setValue(0.3);
    ui->txtGraphPath->clear();
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

void MainWindow::alignfilter(string alignPath, float occupancy, float minId, float maxId, int refseq, string refseqName){
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
    //string path = this->makeNewPath(ui->listWidget->currentItem()->text().toStdString(),buffer.str());

    //QMessageBox::information(this,"DEBUG",refseq);

    int i = 0;
    string alignfilename = ui->listWidget->currentItem()->text().toStdString();
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            break;
        }
    }

    alinhamentos[i].loadFullAlignment();

    //Calculate
    string firstrefseq = alinhamentos[i].sequences[refseq];
    string firstrefseqname = alinhamentos[i].sequencenames[refseq];
    //printf("%s: %s\n",firstrefseq.c_str(),firstrefseqname.c_str());
    alinhamentos[i].sequences.insert(alinhamentos[i].sequences.begin(),firstrefseq);
    alinhamentos[i].sequencenames.insert(alinhamentos[i].sequencenames.begin(),firstrefseqname);
//QMessageBox::information(this,"test","1");
    alinhamentos[i].AlignmentTrimming(occupancy,0,refseqName);
//QMessageBox::information(this,"test","2");
    alinhamentos[i].IdentityMinimum(minId,0,occupancy,refseqName);
//QMessageBox::information(this,"test","3");
    alinhamentos[i].IdentityTrimming(maxId,occupancy,minId,0,refseqName);
//QMessageBox::information(this,"test","4");

    printf("\nFirstRefSeqName: %s\n",firstrefseqname.c_str());
    if ((string)(alinhamentos[i].sequencenames[0])!=firstrefseqname){
        alinhamentos[i].sequences.insert(alinhamentos[i].sequences.begin(),firstrefseq);
        alinhamentos[i].sequencenames.insert(alinhamentos[i].sequencenames.begin(),firstrefseqname);
    }

    vector<vector<string> > filterList = alinhamentos.at(i).getAllFilters();
    ui->listWidget2->clear();
    ui->listWidget2->addItem("Full Alignment");

    for(int j = 0; j < filterList.size(); j++){
        ui->listWidget2->addItem(filterList[j][0].c_str());
    }

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

void MainWindow::conservation(int ai, int refseq, int offset, char chain, string pdbfile){
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
        alinhamentos[ai].addParameter("conservation","Full Alignment",refseq, offset, chain, pdbfile);
    else
        alinhamentos[ai].addParameter("conservation", ui->listWidget2->currentItem()->text().toStdString(), refseq, offset, chain, pdbfile);

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
    outputVec = alinhamentos[ai].DTRandomElimination(repetitions,99,1,1);

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

    QMessageBox::information(this,"PCalc","Communities graph generated.");
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

    QMessageBox::information(this,"Output","Output files are generated sucessfully.");
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

    //Salva Full Alignment
    //vector<string> filterSequence;
    //vector<string> filterList;



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
        align.setWebDir(url.toStdString());
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

    this->alignfilter(fullAlignment.getFilepath(),occupancy,minId,maxId,refseq,refseqName);


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

    alignfilename = ui->listWidget->currentItem()->text().toStdString();
    pdbfilename = ui->txtPDBfilepath->text().toStdString();
    refseq = ui->cmbRefSeq_2->currentIndex();
    chain = ui->txtChain->text().at(0).toLatin1();

    //Alignment fullAlignment;
    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(alignfilename == alinhamentos.at(i).getFilepath()){
            //fullAlignment = alinhamentos[i];
            break;
        }
    }

    if(ui->txtPDBfilepath->text() != ""){
        alinhamentos[i].setLocalPDBDir(ui->txtPDBfilepath->text().toStdString());
    }

    if(this->compareLocalWebPDB(ui->txtPDBfilepath->text().toStdString(),this->pdbweb))
        alinhamentos[i].setWebPDBDir(pdbweb);

    this->conservation(i,refseq,offset,chain,pdbfilename);
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

    for(int j = 0; j < minssData.size(); j++)
        printf("%f\n",minssData[j]);
    //http://www.qcustomplot.com/index.php/tutorials/settingup

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
    ui->graficMinss->yAxis->setRange(0,y[0]+0.04);
    ui->graficMinss->xAxis->setRange(1,100);
    ui->graficMinss->replot();


    ui->graficMinss->setVisible(true);
    ui->cmdMinss->setEnabled(true);
}

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
    ui->cmdCorrelation->setEnabled(true);
}

void MainWindow::on_listWidget_activated(const QModelIndex &index)
{
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    vector<string> sequences;
/*
    for(int i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            sequences = alinhamentos.at(i).getSequencesName();
            /*
            alinhamentos.at(i).setRefSeqName(alinhamentos.at(i).sequencenames[ui->cmbRefSeq->currentIndex()-1]);
            int offset = alinhamentos.at(i).getRefSeqOffset();
            QString qoffset = "" + offset;
            ui->txtOffset->setText(qoffset);
            *//*

            break;
        }
    }
*/
    int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            sequences = alinhamentos.at(i).getSequencesName();
            break;
        }
    }

    ui->cmbRefSeq->clear();
    ui->cmbRefSeq->addItem("");
    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("");
    //ui->lstRefSeqs->clear();
    ui->lstRefSeqs_2->clear();

    for(int i = 0; i < sequences.size(); i++){
        ui->cmbRefSeq->addItem(QString::fromStdString(sequences.at(i)));
        //ui->cmbRefSeq_2->addItem(QString::fromStdString(sequences.at(i)));
        //ui->cmbRefSeq_3->addItem(QString::fromStdString(sequences.at(i)));
        //ui->lstRefSeqs->addItem(QString::fromStdString(sequences.at(i)));
        //ui->lstRefSeqs_2->addItem(QString::fromStdString(sequences.at(i)));
    }

    ui->listWidget2->clear();
    ui->listWidget2->addItem("Full Alignment");

    vector<vector<string> > filterList = alinhamentos.at(i).getAllFilters();

    for(int j = 0; j < filterList.size(); j++){
        ui->listWidget2->addItem(filterList[j][0].c_str());
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
    ui->lstRefSeqs_2->clear();

    if(filterPars == "Full Alignment"){
        alinhamentos[i].loadFullAlignment();
        vector<string> fullAlignment = alinhamentos.at(i).getFullAlignment();
        for(int j = 0; j < fullAlignment.size(); j++){
            vector<string> splitVec = this->split(fullAlignment[j],'/');
            ui->cmbRefSeq_2->addItem(QString::fromStdString(splitVec[0]));
            ui->cmbRefSeq_3->addItem(QString::fromStdString(splitVec[0]));
            //ui->lstRefSeqs->addItem(QString::fromStdString(splitVec[0]));
            ui->lstRefSeqs_2->addItem(QString::fromStdString(splitVec[0]));
        }
    }else{
        for(int j = 0; j < filterList.size(); j++){
            if(filterList[j][0] == filterPars){
                alinhamentos[i].sequences.clear();
                alinhamentos[i].sequencenames.clear();
                for(int k = 1; k < filterList[j].size(); k++){
                    vector<string> splitVec = this->split(filterList[j][k],'/');
                    ui->cmbRefSeq_2->addItem(QString::fromStdString(splitVec[0]));
                    ui->cmbRefSeq_3->addItem(QString::fromStdString(splitVec[0]));
                    //ui->lstRefSeqs->addItem(QString::fromStdString(splitVec[0]));
                    ui->lstRefSeqs_2->addItem(QString::fromStdString(splitVec[0]));
                    alinhamentos[i].sequencenames.push_back(filterList[j][k]);
                    alinhamentos[i].sequences.push_back(filterSeq[j][k]);
                }
                break;
            }
        }
    }

    ui->cmbRefSeq_2->setCurrentIndex(1);
    ui->cmbRefSeq_3->setCurrentIndex(1);

}

void MainWindow::on_cmbRefSeq_activated(int index)
{
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

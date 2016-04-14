#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QtNetwork>
#include <QString>
#include "qcustomplot.h"
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMainWindow::showFullScreen();

    currentAlign = nullptr;

    libpath = ""; //NO windows começar com dir raiz
    //libpath = "/usr/share/pflibs/"; //No linux vai estar neste diretorio

    this->loadConfigurationFile();

    ui->menuBar->setNativeMenuBar(false);

    //Seta Wizard como false
    wizard = false;

    //Bloqueia botões do Wizard
    changeWizardCmds(false);
    ui->graficMinss->setVisible(false);

    //Configura label do grafico Minss
    minssLabel = new QCPItemText(ui->graficMinss);

    //Conecta Slots
    connect(ui->actionOpen_XML,SIGNAL(triggered()),this,SLOT(Open_XML_triggered()));
    connect(ui->actionAlignmentPFAM,SIGNAL(triggered()),this,SLOT(exportAlignment_PFAM()));
    connect(ui->actionAlignmentTXT,SIGNAL(triggered()),this,SLOT(exportAlignment_TXT()));
    connect(ui->actionAlignmentXML,SIGNAL(triggered()),this,SLOT(exportAlignment_XML()));
    connect(ui->actionRefSeqTXT,SIGNAL(triggered()),this,SLOT(exportRefSeqTXT()));
    connect(ui->actionRefSeqXML,SIGNAL(triggered()),this,SLOT(exportRefSeqXML()));
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
    connect(ui->actionStart_Wizard,SIGNAL(triggered()),this,SLOT(startWizard()));
    connect(ui->actionFilter_Alignment,SIGNAL(triggered()),this,SLOT(changetoFilterStack()));
    connect(ui->actionReference_Sequences,SIGNAL(triggered()),this,SLOT(changeToRefSeqs()));
    connect(ui->actionLoadPDB,SIGNAL(triggered()),this,SLOT(changeToLoadPDBs()));
    connect(ui->actionConservation,SIGNAL(triggered()),this,SLOT(changeToConservationStack()));
    connect(ui->actionMinss,SIGNAL(triggered()),this,SLOT(changetoMinssStack()));
    connect(ui->actionCorrelation,SIGNAL(triggered()),this,SLOT(changetoCorrelationStack()));
    connect(ui->actionUniprotLooking,SIGNAL(triggered()),this,SLOT(changeToUniprotLookingTool()));
    connect(ui->actionSave_Results,SIGNAL(triggered()),this,SLOT(saveResults()));
    connect(ui->actionClose_Alignment,SIGNAL(triggered()),this,SLOT(closeAlignment()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(ui->actionLookProtTXT,SIGNAL(triggered()),this,SLOT(exportLookProtTXT()));
    connect(ui->actionLookProtCSV,SIGNAL(triggered()),this,SLOT(exportLookProtCSV()));
    connect(ui->actionLookProtXML,SIGNAL(triggered()),this,SLOT(exportLookProtXML()));
    connect(ui->actionLookProtHTML,SIGNAL(triggered()),this,SLOT(exportLookProtHTML()));
    connect(ui->actionLookCommtTXT,SIGNAL(triggered()),this,SLOT(exportLookCommTXT()));
    connect(ui->actionLookCommCSV,SIGNAL(triggered()),this,SLOT(exportLookCommCSV()));
    connect(ui->actionLookCommXML,SIGNAL(triggered()),this,SLOT(exportLookCommXML()));
    connect(ui->actionLookCommHTML,SIGNAL(triggered()),this,SLOT(exportLookCommHTML()));
    connect(ui->actionCreate_Communitie,SIGNAL(triggered()),this,SLOT(changeToCreateCommunity()));
    connect(ui->actionList_Of_Sequences,SIGNAL(triggered()),this,SLOT(changeToListOfSequences()));
    connect(ui->actionIn_Frequence,SIGNAL(triggered()),this,SLOT(changeToConservationFrequence()));
    connect(ui->actionIn_Percentage,SIGNAL(triggered()),this,SLOT(changeToConservationPercentage()));
    connect(ui->actionConserved_Residues,SIGNAL(triggered()),this,SLOT(changeToConservedResidues()));
    connect(ui->actionCorrelation_List,SIGNAL(triggered()),this,SLOT(changetoCorrelationList()));
    connect(ui->actionCommunities_List,SIGNAL(triggered()),this,SLOT(changeToCommunitiesList()));
    connect(ui->actionIn_Percentage_2,SIGNAL(triggered()),this,SLOT(changeToCorrelationInPerc()));
    connect(ui->actionIn_Log_P,SIGNAL(triggered()),this,SLOT(changeToCorrelationInLogP()));
    connect(ui->actionAdherence_Matrix,SIGNAL(triggered()),SLOT(changeToAdherenceMatrix()));
    connect(ui->actionResidues_Of_Communities,SIGNAL(triggered()),SLOT(changeToResiduesOfCommunities()));
    connect(ui->actionGrouped_By_Proteins,SIGNAL(triggered()),this,SLOT(changeToULGroupedByProteins()));
    connect(ui->actionGrouped_By_Communities,SIGNAL(triggered()),this,SLOT(changeToULGroupedByComms()));
    connect(ui->actionCorrelation_Graph,SIGNAL(triggered()),this,SLOT(changeToCorrelationGraph()));
    connect(ui->actionCommunities_Graphs,SIGNAL(triggered()),this,SLOT(changeToCommunitiesGraphs()));
    connect(ui->actionCorrelationBetweenCommunities,SIGNAL(triggered()),this,SLOT(changeToCorrelationBetweenComms()));
    connect(ui->actionStrutucture_Conserved_Residues_Visualization,SIGNAL(triggered()),SLOT(changeToPDBVisualization()));
    connect(ui->actionStructure_Communities_Visualization,SIGNAL(triggered()),SLOT(changeToPDBVisualization2()));
    connect(ui->actionFull_Alignment,SIGNAL(triggered()),this,SLOT(changeToFullAlignment()));
    connect(ui->actionSet_Libraries_Path,SIGNAL(triggered()),this,SLOT(setLibPath()));
    connect(ui->actionAlphabet_Reduction,SIGNAL(triggered()),this,SLOT(changeToAlphabetReduction()));
    connect(ui->graficMinss,SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)),this,SLOT(graphClicked(QCPAbstractPlottable*,QMouseEvent*)));

    string filepath = libpath + "taxons.txt";
    printf("%s",filepath.c_str());
    QFile file (filepath.c_str());
    if(!file.open(QIODevice::ReadOnly)) {
        //SE NÃO ENCONTRAR O ARQUIVO PUXAR POR WEBSERVICE
        return;
    }

    QTextStream in(&file);

    QStringList taxlist;
    while(!in.atEnd()) {
        QString line = in.readLine();
        taxlist.append(line);
        //printf("%s\n",line.toStdString().c_str());
    }

    taxonsCompleter = new QCompleter(taxlist,this);
    taxonsCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtTaxons->setCompleter(taxonsCompleter);


    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadConfigurationFile(){
    QFileInfo checkFile(CONFIG);

    if(checkFile.exists() && checkFile.isFile()){
        //LER
        QFile file(CONFIG);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(0, "error","Unable to read configuration file");
            return;
        }

        QTextStream in(&file);

        libpath = in.readLine().toStdString();

        file.close();
    }
}

bool MainWindow::isFloat( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

void MainWindow::startStacked(){
    ui->stackedWidget->setCurrentIndex(STACK_MAIN);
    ui->lblHidden->setVisible(false);
}

//Reset UI Objects
void MainWindow::resetObjects(){
    //MAIN WINDOW
    ui->listWidget->clear();
    ui->listWidget2->clear();
    //GET ALIGNMENT
    ui->txtAccession->clear();
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(true);
    ui->radioButton_5->setChecked(false);
    ui->radioButton_6->setChecked(true);
    ui->radioButton_7->setChecked(true);
    ui->radioButton_8->setChecked(false);
    ui->radioButton_9->setChecked(false);
    ui->radioButton_10->setChecked(false);
    ui->cmbFetchFormat->setCurrentIndex(0);
    ui->chkDownloadAlignment->setChecked(false);
    //FILTER
    ui->cmbRefSeq->clear();
    ui->txtTaxons->clear();
    ui->txtMinCover->setValue(0.8);
    ui->txtMinId->setValue(0.15);
    ui->txtMaxId->setValue(0.8);
    //REFSEQS
    ui->cmbFilterRefseq->setCurrentIndex(0);
    ui->txtFilterRefSeq->clear();
    ui->lstRefSeqs->clear();
    ui->lstRefSeqSelected->clear();
    //PDB
    ui->txtChainPDB->clear();
    ui->txtFilePathPDB->clear();
    ui->txtPdbId->clear();
    ui->lstRecommendedPDBs->clear();
    ui->lstPDBsInMemory->clear();
    ui->chkDownloadPDB->setChecked(false);
    ui->txtPDBFrom->setValue(0);
    ui->txtPDBTo->setValue(0);
    ui->cmbRefSeq_4->clear();
    //CONSERVATION
    ui->txtPDBName->clear();
    ui->lstRecomendedPDBs->clear();
    ui->txtOffset->setText("0");
    ui->txtChain->setText("A");
    ui->txtMinConserv->setValue(0.8);
    ui->cmbRefSeq_2->clear();
    //MINSS
    ui->graficMinss->clearGraphs();
    ui->graficMinss->setVisible(false);
    ui->txtNoAlignments->setValue(100);
    //CORRELATION
    ui->chkRemoveContactResidues->setChecked(false);
    ui->txtAtomDistance->setValue(4.5);
    ui->txtAtomDistance->setEnabled(false);
    ui->txtPDBName_2->clear();
    ui->txtPDBName_2->setEnabled(false);
    ui->txtChain_2->setText("A");
    ui->txtChain_2->setEnabled(false);
    ui->lstPDBsLoaded_2->clear();
    ui->lstPDBsLoaded_2->setEnabled(false);
    ui->chkCommVisualization->setChecked(false);
    ui->txtMinScore->setValue(10);
    ui->txtMinssFraction->clear();
    ui->txtMinDeltaFreq->setValue(0.3);
    ui->txtOffset_2->setText("0");
    ui->cmbRefSeq_3->clear();
    //RESULTS
    //MAIN RESULT PAGE
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
    ui->checkResults11->setChecked(false);
    ui->checkResults12->setChecked(false);
    ui->lblHidden->setText(0);
    //LIST SEQUENCES
    ui->lstProteinsFiltered->clear();
    ui->txtSequence->clear();
    ui->lblRefSeq->setText("Reference Sequence:");
    ui->lblTaxon->setText("Taxon:");
    ui->lblMinId->setText("Minimum Identity: ");
    ui->lblOccupancy->setText("Occupancy: ");
    ui->lblMaxId->setText("Maximum Identity: ");
    //FREQ CONSERVATION
    ui->lblFilter->setText("Filter: ");
    ui->lblRefSeq->setText("Reference Sequence: ");
    ui->lblOffset->setText("Offset: ");
    ui->lblMinimumCons->setText("Minimum Conservation: ");
    ui->tableFreq->clearContents();
    //PERC CONSERVATION
    ui->lblFilter_2->setText("Filter: ");
    ui->lblRefSeq_2->setText("Reference Sequence: ");
    ui->lblOffset_2->setText("Offset: ");
    ui->lblMinimumCons_2->setText("Minimum Conservation: ");
    ui->tableFreqPerc->clearContents();
    //CONSERVED RESIDUES
    ui->lblFilter_8->setText("Filter: ");
    ui->lblMinCons->setText("Minimum Conservation: ");
    ui->tableConsRes->clear();
    //CORRELATION LIST
    ui->lblFilter_3->setText("Filter: ");
    ui->lblMinLogP->setText("Minimum Score: ");
    ui->lblMinss->setText("Minss Fraction: ");
    ui->lblDeltaFreq->setText("Delta Frequence: ");
    ui->treeCorrelation->clear();
    //LIST OF COMMUNITIES
    ui->lblFilter_4->setText("Filter: ");
    ui->lblMinLogP_2->setText("Minimum Score: ");
    ui->lblMinss_2->setText("Minss Fraction: ");
    ui->lblDeltaFreq_2->setText("Delta Frequence: ");
    ui->treeCorrelationComm->clear();
    //CORRELATION TABLES %
    ui->lblFilter_5->setText("Filter: ");
    ui->lblComunidade->setText("Communitie: ");
    ui->lblMinLogP_3->setText("Minimum Score: ");
    ui->lblMinss_3->setText("Minss Fraction: ");
    ui->lblDeltaFreq_3->setText("Delta Frequence: ");
    ui->tableComm1->clear();
    //CORRELATION TABLES LOG P
    ui->lblFilter_6->setText("Filter: ");
    ui->lblComunidade_2->setText("Communitie: ");
    ui->lblMinLogP_4->setText("Minimum Score: ");
    ui->lblMinss_4->setText("Minss Fraction: ");
    ui->lblDeltaFreq_4->setText("Delta Frequence: ");
    ui->tableComm2->clear();
    //ADHERENCE
    ui->lblFilter_7->setText("Filter: ");
    ui->tableAdherence->clear();
    //RESIDUES OF COMMUNITIE
    ui->lblFilter_9->setText("Filter: ");
    ui->lblComunidade_3->setText("Communitie: ");
    ui->tableResiduesComm->clear();
    //RESULTS UNIPROT 1
    ui->lstProteinsMined->clear();
    ui->tableProteinsMined1->clearContents();
    //RESULTS UNIPROT 2
    ui->treeMinerComms->clear();
    ui->tableProteinsMined2->clearContents();
    //COMM GRAPHS
    ui->lblComunidade_4->setText("Communitie ");
    //CORRELATION BETWEEN COMMS GRAPH
    ui->txtGraphCutoff->setText("1.5");
    //Uniprot Looking Tool
    ui->chkConserveds->setChecked(false);
    ui->chkComm->setChecked(false);
    ui->cmbLookingFilter->setCurrentIndex(0);
    ui->txtLookingFilter->clear();
    ui->txtLookingFilter->setEnabled(false);
    ui->lstLookingRefs->clear();
    //Manage Communities
    ui->cmbComm->clear();
    ui->lstManageComms->clear();
    //Alphabet Reduction
    ui->cmbAlphabetList->setCurrentIndex(0);
    ui->lblAlphabetName->setText("Name: ");
    ui->lblAlphabetChanges->setText("Changes: ");
    ui->radioAlphabetCurrent->setChecked(false);
    ui->radioAlphabetNew->setChecked(true);

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
    unsigned int c1=0;

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

void MainWindow::alignfilter(float occupancy, float minId, float maxId, int refseq, bool filter1, bool filter2, bool filter3, bool taxfilter){
    QString msg = "The filters were successfully applied\n";
    int seqSize;
    int seqCut;

    //Calculate
    string firstrefseq = currentFilter->sequences[refseq];
    string firstrefseqname = currentFilter->sequencenames[refseq];
    string taxon = ui->txtTaxons->text().toStdString();
    string alphabet = currentFilter->getAlphabet();
    string name = ui->txtFilterName->text().toStdString();
    int type = ui->cmbFilterMethod->currentIndex();
    //printf("%s: %s\n",firstrefseq.c_str(),firstrefseqname.c_str());
    vector<string> sequences = currentFilter->sequences;
    vector<string> sequencenames = currentFilter->sequencenames;

    sequences.insert(sequences.begin(),firstrefseq);
    sequencenames.insert(sequencenames.begin(),firstrefseqname);
    currentAlign->addSequences(sequences,sequencenames);

    seqSize = currentAlign->sequences.size();
    msg += "Full Alignment: " + QString::number(seqSize) + ".\n\n";
    //currentAlign->AlignmentTrimming(occupancy,0,firstrefseqname,firstrefseq,inter);

    if(taxfilter){
        currentAlign->taxonTrimming(taxon,firstrefseqname,firstrefseq);

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Taxons filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filter1){
        //if(method == 0) currentAlign->hmmCoverageTrimmimg(taxon,occupancy,alphabet,inter);
        currentAlign->AlignmentTrimming(occupancy,0,firstrefseq,firstrefseqname,true);

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Minimum coverage filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filter2){
        currentAlign->IdentityMinimum(minId,0);

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Minimum identity filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filter3){
        currentAlign->IdentityTrimming(maxId);

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Maximum identity filter removed " + QString::number(seqCut) + " sequences.\n\n";
    }

    msg += "Remaining sequences: " + QString::number(seqSize) + ".";

    Filter *filter = new Filter(name,alphabet,type);
    filter->setRefSeq(firstrefseqname);
    filter->setTaxon(taxon);
    filter->setMinOcc(occupancy);
    filter->setMinId(minId);
    filter->setMaxId(maxId);
    filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
    filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

    currentAlign->addFilter(filter);

    ui->listWidget2->addItem(name.c_str());

    ui->listWidget2->item(ui->listWidget2->count()-1)->setSelected(true);
    emit ui->listWidget2->activated(ui->listWidget2->currentIndex());

    QMessageBox::information(this,"Alignment filters",msg);
}

void MainWindow::alignfilter(float occupancy, float maxId, bool filterOcc, bool filterMaxId, bool filterTaxon){
    QString msg = "The filters were successfully applied\n";
    int seqSize;
    int seqCut;

    currentFilter->CalculateFrequencies();

    string taxon = ui->txtTaxons->text().toStdString();
    string alphabet = currentFilter->getAlphabet();
    string name = ui->txtFilterName->text().toStdString();
    int type = ui->cmbFilterMethod->currentIndex();

    vector<string> sequences = currentFilter->sequences;
    vector<string> sequencenames = currentFilter->sequencenames;

    currentAlign->addSequences(sequences,sequencenames);
    currentAlign->defineHMMpositions();

    seqSize = currentAlign->sequences.size();
    msg += "Full Alignment: " + QString::number(seqSize) + ".\n\n";

    if(filterTaxon){
        currentAlign->taxonTrimming(taxon,"0","");

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Taxons filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filterOcc){
        currentAlign->hmmCoverageTrimmimg(occupancy);

        if(currentAlign->sequences.size() == 0){
            QMessageBox::warning(this,"Filter","Your parameters filtered all sequences of the alignment.");
            return;
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Minimum coverage filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filterMaxId){
        currentAlign->IdentityTrimming(maxId);

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Maximum identity filter removed " + QString::number(seqCut) + " sequences.\n\n";
    }

    msg += "Remaining sequences: " + QString::number(seqSize) + ".";

    currentAlign->convertLowerDots();

    currentAlign->dots2dashs();

    Filter *filter = new Filter(name,alphabet,type);
    filter->setTaxon(taxon);
    filter->setMinOcc(occupancy);
    filter->setMaxId(maxId);
    filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());

    currentAlign->addFilter(filter);

    ui->listWidget2->addItem(name.c_str());

    ui->listWidget2->item(ui->listWidget2->count()-1)->setSelected(true);
    emit ui->listWidget2->activated(ui->listWidget2->currentIndex());

    QMessageBox::information(this,"Alignment filters",msg);
}

void MainWindow::applyHenikoffFilter(){
    //IMPLEMENTAR
}

void MainWindow::conservation(int refseq, int offset, char chain, float minCons, string pdbid){
    currentFilter->CalculateFrequencies();
    currentFilter->dGCalculation();
    currentFilter->dGWrite();
    currentFilter->FreqWrite();

    string path = "";

    if(pdbid != ""){
        Pdb* pdb = NULL;
        for(unsigned int i = 0; i < pdbs.size(); i++){
            if(pdbid == pdbs[i]->getId()){
                pdb = pdbs[i];
                break;
            }
        }

        if(pdb == NULL){
            QMessageBox::warning(this,"Warning","This is not a valid loaded structure.");
            ui->cmdConservation->setEnabled(true);
            return;
        }

        QString filename = QFileDialog::getSaveFileName(this,tr("Save conservation structure file"),"",tr("TEXT Files (*.pdb)"));
        path = filename.toStdString();

        //pdb->printSeqNumbers();
        vector<float> consvec = currentFilter->createConservationVector(refseq);
        pdb->exportStructure(filename,consvec,chain);

        currentFilter->setConsPDBPath(path);

    }

    currentFilter->setConsMin(minCons);
    currentFilter->setConsOffset(offset);
    currentFilter->setConsPDB(pdbid);
    currentFilter->setConsRefseq(refseq);

    if(pdbid != "") QMessageBox::information(this,"Conservation","Conservation has been calculated and the structure file has been successfully created at the above path:\n\n" + QString::fromStdString(path));
    else QMessageBox::information(this,"Conservation","Conservation has been calculated.");
}

vector<float> MainWindow::minss(int repetitions){
    vector<float> outputVec;
    currentFilter->CalculateFrequencies();
    //outputVec = currentAlign->DTRandomElimination(repetitions,99,1,1);
    outputVec = currentFilter->ShannonEntropy(repetitions);

    QMessageBox::information(this,"Minss","Minss calculated.");

    return outputVec;
}

void MainWindow::pcalc(int minlogp, float minssfraction, float mindeltafreq){
    currentFilter->CalculateFrequencies();
    currentFilter->SympvalueCalculation(minlogp,minssfraction,mindeltafreq);
}

void MainWindow::trivcomm(){
    unsigned int maxsize;
    unsigned int biggestcommunity;
    unsigned int c1,c2;
    int found1comm,found2comm; // Communities and positions where pos1-aa1 and pos2-aa2 were found
    bool member1found=false;
    bool member2found=false;
    vector < vector <int> > posCommunities;
    vector < vector <char> > aaCommunities;
    currentFilter->clearCommunity();

    tuple<string,string,int> edge = currentFilter->getCorrelationEdge(0);
    string v1 = std::get<0>(edge);
    string v2 = std::get<1>(edge);
    int score = std::get<2>(edge);
    //printf("V1: %s, V2: %s\n",v1.c_str(),v2.c_str());
    char aa1 = v1[0];
    char aa2 = v2[0];
    int pos1, pos2;

    string temp = "";
    for(unsigned int i = 1; i < v1.length(); i++){
        temp += v1[i];
    }
    pos1 = std::atoi(temp.c_str());

    temp = "";
    for(unsigned int i = 1; i < v2.length(); i++){
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

    for(unsigned int i = 1; i < currentFilter->getCorrelationGraphSize(); i++){
        edge = currentFilter->getCorrelationEdge(i);
        v1 = std::get<0>(edge);
        v2 = std::get<1>(edge);
        score = std::get<2>(edge);
        //printf("V1: %s, V2: %s\n",v1.c_str(),v2.c_str());

        aa1 = v1[0];
        aa2 = v2[0];

        string temp = "";
        for(unsigned int i = 1; i < v1.length(); i++){
            temp += v1[i];
        }
        pos1 = std::atoi(temp.c_str());

        temp = "";
        for(unsigned int i = 1; i < v2.length(); i++){
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
        currentFilter->addCommunity(comm);
        comm.clear();

        aaCommunities[biggestcommunity].clear();
        posCommunities[biggestcommunity].clear();
        aaCommunities.erase(aaCommunities.begin()+biggestcommunity);
        posCommunities.erase(posCommunities.begin()+biggestcommunity);
        c2++;
    }
    //currentAlign->printCommunity();
}

void MainWindow::output(int seqnumber, int offset){
    currentFilter->CalculateFrequencies();
    currentFilter->getCommunitiesFromRAM();

    //communityX.html
    if(seqnumber > 0) currentFilter->Cluster2SCMFromRAM(true,seqnumber,offset);
    else currentFilter->Cluster2SCMFromRAM(false,seqnumber,offset);
    //if(seqnumber>0) currentAlign->Cluster2SCM(communitiesfilename,path,true,seqnumber,offset,true,false);
    //else currentAlign->Cluster2SCM(communitiesfilename,path,false,seqnumber,offset,true,false);

    currentFilter->DeltaCommunitiesCalculation();
    //currentAlign->DeltaCommunitiesOutput(path + "Deltas.html");

    //if (seqnumber>0)
    //    currentAlign->ElementRanking(path, true, seqnumber,offset);
    //else
    //    currentAlign->ElementRanking(path, false, seqnumber,offset);

    //comunityXps.html
    currentFilter->pMatrix2HTMLRAM(false,1);
    //currentAlign->pMatrix2HTML("/home/neli/teste",false,1);

    //currentAlign->Cluster2PymolScript(communitiesfilename,path,seqnumber,offset);
}

void MainWindow::listSequences(){
    vector<string> sequences;

    //Parametros
    if(ui->listWidget2->currentItem() == NULL){
        ui->lblRefSeq1->setText(" Reference Sequence: Full Alignment");
        ui->lblTaxon->setVisible(false);
        ui->lblOccupancy->setVisible(false);
        ui->lblMaxId->setVisible(false);
        ui->lblMinId->setVisible(false);
    }else{
        if(currentFilter->getType() == 9){
            ui->lblRefSeq1->setText("Reference Sequence: Full Alignment");
            ui->lblTaxon->setVisible(false);
            ui->lblOccupancy->setVisible(false);
            ui->lblMaxId->setVisible(false);
            ui->lblMinId->setVisible(false);
        }else{
            if(currentFilter->getMinOcc() == 0) ui->lblOccupancy->setVisible(false);
            else{
                string occ = "Occupancy: " + to_string(currentFilter->getMinOcc());
                ui->lblOccupancy->setVisible(true);
                ui->lblOccupancy->setText(occ.c_str());
            }

            if(currentFilter->getMinId() == 0) ui->lblMinId->setVisible(false);
            else{
                string minId = "Minimum Identity: " + to_string(currentFilter->getMinId());
                ui->lblMinId->setVisible(true);
                ui->lblMinId->setText(minId.c_str());
            }

            if(currentFilter->getMaxId() == 0) ui->lblMaxId->setVisible(false);
            else{
                string maxId = "Maximum Identity: " + to_string(currentFilter->getMaxId());
                ui->lblMaxId->setVisible(true);
                ui->lblMaxId->setText(maxId.c_str());
            }

            if(currentFilter->getTaxon() == "") ui->lblTaxon->setVisible(false);
            else{
                string taxon = "Taxon: " + currentFilter->getTaxon();
                ui->lblTaxon->setVisible(true);
                ui->lblTaxon->setText(taxon.c_str());
            }

            if(currentFilter->getRefSeq() == "") ui->lblRefSeq1->setVisible(false);
            else{
                string refseq = "Reference Sequence: " + currentFilter->getRefSeq();
                ui->lblRefSeq1->setVisible(true);
                ui->lblRefSeq1->setText(refseq.c_str());
            }
        }
    }

    for(unsigned int j = 0; j < currentFilter->sequencenames.size(); j++){
        ui->lstProteinsFiltered->addItem(QString::fromStdString(currentFilter->sequencenames[j]));
    }

}

void MainWindow::tableFreq(){
    unsigned int nrows = currentFilter->getConsFreqSize();

    //Limpa tabela
    ui->tableFreq->clearContents();

    //Ajusta tamanho das colunas
    ui->tableFreq->resizeColumnsToContents();

    ui->tableFreq->verticalHeader()->setVisible(false);

    //QHeaderView *HorzHdr = ui->tableFreq->horizontalHeader();
    //HorzHdr->setStretchLastSection(true);

    //Parâmetros
    ui->lblFilter->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblRefSeq->setText("Reference Sequence: " + QString::fromStdString(currentFilter->getRefSeq()));
    ui->lblOffset->setText("Offset: " + QString::fromStdString(to_string(currentFilter->getConsOffset())));
    ui->lblMinimumCons->setText("Minimum Conservation: " + QString::fromStdString(to_string(currentFilter->getConsMin())));

    if(currentFilter->getRefSeq() == "") ui->lblRefSeq->setVisible(false);
    else ui->lblRefSeq->setVisible(true);

    //Preenche a tabela
    ui->tableFreq->setRowCount(nrows);

    for(unsigned int i = 0; i < nrows-1; i++){
        vector<int> freqRow = currentFilter->getConsFreqRow(i);

        for(unsigned int j = 0; j < 22; j++){
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
    vector<int> freqRow = currentFilter->getConsFreqRow(nrows-1);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole,"TOTAL");
    ui->tableFreq->setItem(nrows-1,0,item);
    for(unsigned int i = 0; i < 21; i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole,freqRow[i]);

        ui->tableFreq->setItem(nrows-1,i+1,item);
    }
}

void MainWindow::tableFreqPerc(){
    unsigned int nrows = currentFilter->getConsFreqPercSize();

    //Limpa tabela
    ui->tableFreqPerc->clearContents();

    //Ajusta o tamanho das colunas
    ui->tableFreqPerc->resizeColumnsToContents();

    ui->tableFreqPerc->verticalHeader()->setVisible(false);

    ui->lblFilter_2->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblRefSeq_2->setText("Reference Sequence: " + QString::fromStdString(currentFilter->getRefSeq()));
    ui->lblOffset_2->setText("Offset: " + QString::fromStdString(to_string(currentFilter->getConsOffset())));
    ui->lblMinimumCons_2->setText("Minimum Conservation: " + QString::fromStdString(to_string(currentFilter->getConsMin()).c_str()));

    if(currentFilter->getRefSeq() == "") ui->lblRefSeq_2->setVisible(false);
    else ui->lblRefSeq_2->setVisible(true);

    //Preenche a tabela
    ui->tableFreqPerc->setRowCount(nrows);

    for(unsigned int i = 0; i < nrows; i++){
        vector<float> freqPercRow = currentFilter->getConsFreqPercRow(i);

        for(unsigned int j = 0; j < 21; j++){
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
}

void MainWindow::correlationList(){
    unsigned int nrows = currentFilter->getCorrGraphSize();

    //Limpa a tabela
    ui->treeCorrelation->clear();

    //Recupera parametros
    ui->lblFilter_3->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblMinLogP->setText("Minimum Score: " + QString::fromStdString(to_string(currentFilter->getCorrMinScore())));
    ui->lblMinss->setText("Minss Fraction: " + QString::fromStdString(to_string(currentFilter->getCorrMinssFraction())));
    ui->lblDeltaFreq->setText("Delta Frequence: " + QString::fromStdString(to_string(currentFilter->getCorrMinDelta())));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = currentFilter->getCorrGraphTuple(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelation);

        item->setText(0,std::get<0>(tupCorr).c_str());
        item->setText(1,std::get<1>(tupCorr).c_str());
        item->setText(2,QString::number(std::get<2>(tupCorr)));
    }

}

void MainWindow::createCorrelationJSON(){
    unsigned int nrows = currentFilter->getCorrGraphSize();
    string pathJSON = libpath + "abor/in1.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    out << "{\n\t\"nodes\": {\n";
    set<string> nodes = currentFilter->getCorrelationNodes();
    unsigned int count = 0;

    for(set<string>::iterator it = nodes.begin(); it != nodes.end(); it++){
        count++;

        out << ("\t\t\"" + *it + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"" + *it + "\"\n").c_str();

        if(count < nodes.size()) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";

    for(set<string>::iterator it = nodes.begin(); it != nodes.end(); it++){
        if(it != nodes.begin()) out << ",\n";
        out << ("\t\t\"" + *it + "\": {\n").c_str();

        count = 0;
        for(unsigned int j = 0; j < nrows; j++){
            tuple<string,string,int> tupCorr = currentFilter->getCorrGraphTuple(j);

            if(std::get<0>(tupCorr) == *it){
                if(count > 0) out << ",\n";
                count++;

                out << ("\t\t\t\"" + std::get<1>(tupCorr) + "\": {\n").c_str();
                out << ("\t\t\t\t\"value\": " + std::to_string(std::get<2>(tupCorr)) + "\n").c_str();

                out << "\t\t\t\t}";
                //out << "\t\t\t}\n";
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";


    string path = libpath + "abor/index.html";
    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;
    ui->webCorrGraph->load(QUrl(localUrl.c_str()));
}

void MainWindow::on_cmdHideShowAntiCorr_clicked()
{
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(ui->cmdHideShowAntiCorr->text() == "Hide Anti-Correlations"){
        ui->cmdHideShowAntiCorr->setText("Show Anti-Correlations");
    }else{
        ui->cmdHideShowAntiCorr->setText("Hide Anti-Correlations");
    }


    unsigned int nrows = currentFilter->getCorrGraphSize();
    string path = libpath + "abor/in1.json";
    QFile fileJSON(path.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    out << "{\n\t\"nodes\": {\n";

    set<string> nodes;
    if(ui->cmdHideShowAntiCorr->text() == "Show Anti-Correlations")
        nodes = currentFilter->getPositiveCorrelationNodes();
    else
        nodes = currentFilter->getCorrelationNodes();

    unsigned int count = 0;

    for(set<string>::iterator it = nodes.begin(); it != nodes.end(); it++){
        count++;

        out << ("\t\t\"" + *it + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"" + *it + "\"\n").c_str();

        if(count < nodes.size()) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";

    for(set<string>::iterator it = nodes.begin(); it != nodes.end(); it++){
        if(it != nodes.begin()) out << ",\n";
        out << ("\t\t\"" + *it + "\": {\n").c_str();

        count = 0;
        for(unsigned int j = 0; j < nrows; j++){
            tuple<string,string,int> tupCorr = currentFilter->getCorrGraphTuple(j);

            if(ui->cmdHideShowAntiCorr->text() == "Show Anti-Correlations"){
                if(std::get<0>(tupCorr) == *it && std::get<2>(tupCorr) > 0){
                    if(count > 0) out << ",\n";
                    count++;

                    out << ("\t\t\t\"" + std::get<1>(tupCorr) + "\": {\n").c_str();
                    out << ("\t\t\t\t\"value\": " + std::to_string(std::get<2>(tupCorr)) + "\n").c_str();

                    out << "\t\t\t\t}";
                    //out << "\t\t\t}\n";
                }
            }else{
                if(std::get<0>(tupCorr) == *it){
                    if(count > 0) out << ",\n";
                    count++;

                    out << ("\t\t\t\"" + std::get<1>(tupCorr) + "\": {\n").c_str();
                    out << ("\t\t\t\t\"value\": " + std::to_string(std::get<2>(tupCorr)) + "\n").c_str();

                    out << "\t\t\t\t}";
                    //out << "\t\t\t}\n";
                }
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";

    ui->webCorrGraph->reload();//load(QUrl(localUrl.c_str()));
}

void MainWindow::communitiesGraphs(){
    string pathJSON = libpath + "abor/in2.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    ui->lblComunidade_4->setText("Communitie 1");

    vector<string> nodes = currentFilter->getCommunitie(0);
    vector<tuple<string,string,int> > graph = currentFilter->getEdgesByComm(0);

    out << "{\n\t\"nodes\": {\n";
    for(unsigned int i = 0; i < nodes.size(); i++){
        out << ("\t\t\"" + nodes[i] + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"" + nodes[i] + "\"\n").c_str();

        if(i+1 < nodes.size()) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";
    for(unsigned int i = 0; i < nodes.size(); i++){
        if(i != 0) out << ",\n";
        out << ("\t\t\"" + nodes[i] + "\": {\n").c_str();

        int count = 0;
        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,int> tupCorr = graph[j];

            if(std::get<0>(tupCorr) == nodes[i] && std::get<2>(tupCorr) > 0){
                if(count > 0) out << ",\n";
                count++;

                out << ("\t\t\t\"" + std::get<1>(tupCorr) + "\": {\n").c_str();
                out << ("\t\t\t\t\"value\": " + std::to_string(std::get<2>(tupCorr)) + "\n").c_str();

                out << "\t\t\t\t}";
                //out << "\t\t\t}\n";
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";

    fileJSON.close();

    string path = libpath + "abor/index2.html";
    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;
    ui->webCommGraphs->load(QUrl(localUrl.c_str()));
}

void MainWindow::corrBetweenComms(){
    string pathJSON = libpath + "abor/in3.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    unsigned int nDeltas = currentFilter->getNumOfUtilComms();

    out << "{\n\t\"nodes\": {\n";
    for(unsigned int i = 0; i < nDeltas; i++){
        out << ("\t\t\"C" + std::to_string(i+1) + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"C" + std::to_string(i+1) + "\"\n").c_str();

        if(i+1 < nDeltas) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";
    vector<tuple<string,string,float> > graph = currentFilter->getDeltasEdges(0.5);
    for(unsigned int i = 0; i < nDeltas; i++){
        string comm = "C" + std::to_string(i+1);

        if(i != 0) out << ",\n";
        out << ("\t\t\"" + comm + "\": {\n").c_str();

        int count = 0;
        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,float> edge = graph[j];


            if(std::get<0>(edge) == comm){
                string comm2 = std::get<1>(edge);
                float weight = std::get<2>(edge);

                if(count > 0) out << ",\n";
                count++;

                string unformatedValue = std::to_string(weight);
                string formated = "";

                for(unsigned int k = 0; k < unformatedValue.size(); k++){
                    if(unformatedValue[k] == ','){
                        formated += '.';
                        formated += unformatedValue[k+1];
                        formated += unformatedValue[k+2];
                        break;
                    }else
                        formated += unformatedValue[k];
                }

                out << ("\t\t\t\"" + comm2 + "\": {\n").c_str();
                out << ("\t\t\t\t\"value\": " + formated + "\n").c_str();
                out << "\t\t\t\t}";
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";

    string path = libpath + "abor/index3.html";
    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;
    ui->webCorrComm->load(QUrl(localUrl.c_str()));
}

void MainWindow::on_cmdCorrCommCutoff_clicked()
{
    ui->cmdCorrCommCutoff->setEnabled(false);

    //Validaçao
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(ui->txtGraphCutoff->text() == ""){
        QMessageBox::warning(this,"Error","You must set a cutoff value.");
        ui->cmdCorrCommCutoff->setEnabled(true);
        return;
    }

    if(!isFloat(ui->txtGraphCutoff->text().toStdString())){
        QMessageBox::warning(this,"Error","You must set a numeric value for cutoff.");
        ui->cmdCorrCommCutoff->setEnabled(true);
        return;
    }

    float cutoff = ui->txtGraphCutoff->text().toFloat();
    string pathJSON = libpath + "abor/in3.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    unsigned int nDeltas = currentFilter->getNumOfUtilComms();

    out << "{\n\t\"nodes\": {\n";
    for(unsigned int i = 0; i < nDeltas; i++){
        out << ("\t\t\"C" + std::to_string(i+1) + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"C" + std::to_string(i+1) + "\"\n").c_str();

        if(i+1 < nDeltas) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";
    vector<tuple<string,string,float> > graph = currentFilter->getDeltasEdges(cutoff);
    for(unsigned int i = 0; i < nDeltas; i++){
        string comm = "C" + std::to_string(i+1);

        if(i != 0) out << ",\n";
        out << ("\t\t\"" + comm + "\": {\n").c_str();

        int count = 0;
        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,float> edge = graph[j];


            if(std::get<0>(edge) == comm){
                string comm2 = std::get<1>(edge);
                float weight = std::get<2>(edge);

                if(count > 0) out << ",\n";
                count++;

                string unformatedValue = std::to_string(weight);
                string formated = "";

                for(unsigned int k = 0; k < unformatedValue.size(); k++){
                    if(unformatedValue[k] == ','){
                        formated += '.';
                        formated += unformatedValue[k+1];
                        formated += unformatedValue[k+2];
                        break;
                    }else
                        formated += unformatedValue[k];
                }

                out << ("\t\t\t\"" + comm2 + "\": {\n").c_str();
                out << ("\t\t\t\t\"value\": " + formated + "\n").c_str();
                out << "\t\t\t\t}";
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";

    ui->webCorrComm->reload();

    ui->cmdCorrCommCutoff->setEnabled(true);
}

string MainWindow::makeVisPDBHTML(string pdb){
    string html = "";
    html += "<!DOCTYPE html>\n";
    html += "<html>\n";
    html += "<head>\n";
    html += "<title>Structure colored by conservation</title>\n";
    html += "<script src=3Dmol.js></script>\n";
    html += "<script src=3Dmol/3dmol.js></script>\n";
    html += "<script src=3Dmol/colors.js></script>\n";
    html += "<script src=3Dmol/glmodel.js></script>\n";
    html += "<script src=3Dmol/glviewer.js></script>\n";
    html += "<script src=3Dmol/gradients.js></script>\n";
    html += "<style>head,body{margin:0;border:0;padding:0;max-height:100vh}</style>\n";
    html += "<script>$3Dmol.syncSurface=true;var glviewer=null;var labels=[];var m=null;var posLobe=null;var negLobe=null;var m2=null;var atoms=null;var moldata=\"\";var l=null;var modelgroup=null;var receptorModel=null;var ligandModel=null;var molObj=null;var lastsurfstyle=true;var voldata=null;var toggleSurfTrans=function(b){var a=!!(lastsurfstyle)?0.75:1;glviewer.setSurfaceMaterialStyle(b,{opacity:a});glviewer.render();lastsurfstyle=!(lastsurfstyle)};var addLabels=function(){var d=glviewer.getModel().selectedAtoms({atom:\"CA\"});if(labels.length==0){for(var c in d){var e=d[c];var b=glviewer.addLabel(e.resn+\" \"+e.resi,{inFront:true,fontSize:12,position:{x:e.x,y:e.y,z:e.z}});e.label=b;labels.push(e)}}else{glviewer.removeAllLabels();labels=[]}};var atomcallback=function(b,c){if(b.clickLabel===undefined||!b.clickLabel instanceof $3Dmol.Label){b.clickLabel=c.addLabel(b.elem+b.serial,{fontSize:14,position:{x:b.x,y:b.y,z:b.z}});b.clicked=true}else{if(b.clicked){var a={fontSize:b.clickLabel.fontSize,position:b.clickLabel.position,backgroundColor:{r:100,g:0,b:255,a:0.8}};c.setLabelStyle(b.clickLabel,a);b.clicked=!b.clicked}else{c.removeLabel(b.clickLabel);b.clickLabel=undefined;b.clicked=false}}};var shapecallback=function(b,c){if(b.clickLabel===undefined||!b.clickLabel instanceof $3Dmol.Label){b.clickLabel=c.addLabel(\"Shape \"+b.id,{fontSize:14,position:{x:b.position.x,y:b.position.y,z:b.position.z}});b.clicked=true}else{if(b.clicked){var a=b.clickLabel.stylespec;a.backgroundColor={r:100,g:0,b:255,a:0.8};c.setLabelStyle(b.clickLabel,a);b.clicked=!b.clicked}else{c.removeLabel(b.clickLabel);b.clickLabel=undefined;b.clicked=false}}};$(document).ready(function(){});function upload(a){var c=glviewer=$3Dmol.createViewer(\"gldiv\",{defaultcolors:$3Dmol.rasmolElementColors});glviewer.setBackgroundColor(16777215);glviewer.addModel(a,\"pdb\");var b=new $3Dmol.Gradient.Sinebow($3Dmol.getPropertyRange(glviewer.selectedAtoms(),\"b\"));glviewer.setStyle({},{stick:{colorscheme:{prop:\"b\",gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render();console.log(glviewer);glviewer.zoomTo();glviewer.render()}</script>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "<div id=gldiv style=width:100%;position:relative;height:80vh;margin:0;padding:0;border:0></div>\n";
    html += "<hr style=margin:0><br>\n";
    html += "<form>\n";
    html += "<input type=button value=Stick onclick=\"glviewer.setStyle({},{stick:{colorscheme:{prop:'b',gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render()\"></input>\n";
    html += "<input type=button value=Line onclick=\"glviewer.setStyle({},{line:{colorscheme:{prop:'b',gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render()\"></input>\n";
    html += "<input type=button value=Cross onclick=\"glviewer.setStyle({},{cross:{colorscheme:{prop:'b',gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render()\"></input>\n";
    html += "<input type=button value=Sphere onclick=\"glviewer.setStyle({},{sphere:{colorscheme:{prop:'b',gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render()\"></input>\n";
    html += "<input type=button value=Cartoon onclick=\"glviewer.setStyle({hetflag:false},{cartoon:{colorscheme:{prop:'b',gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render()\"></input>\n";
    html += "<input type=button value=Trace onclick=\"glviewer.setStyle({},{cartoon:{style:'trace',thickness:0.3,colorscheme:{prop:'b',gradient:new $3Dmol.Gradient.Sinebow(0,150)}}});glviewer.render()\"></input>\n";
    html += "<input type=button value=\"Alpha C's\" onclick=addLabels(glviewer);glviewer.render()></input>\n";
    html += "<br>\n";
    html += "<input type=button value=Centralize onclick=glviewer.zoomTo()></input>\n";
    html += "<br>\n";
    html += "</form>\n";
    html += "<br>\n";
    html += "<script type=text/javascript>contents=\"" + pdb + "\";upload(contents);</script>\n";
    html += "</body>\n";
    html += "</html>";

    return html;
}

void MainWindow::consVisualization(){
    string path = libpath + "3Dmol/index.html";
    QFile indexHTML(path.c_str());
    indexHTML.open(QIODevice::WriteOnly);
    QTextStream out(&indexHTML);
    QFile pdbPath(currentFilter->getConsPDBPath().c_str());
    pdbPath.open(QIODevice::ReadOnly);
    string pdb = "";

    while(!pdbPath.atEnd()){
        string line = pdbPath.readLine().data();
        string newline = "";

        //Invert b-factor values
        if(line.substr(0,4) == "ATOM"){
            string temp = line.substr(60,6);
            string strbfactor = "";

            for(unsigned int i = 0; i < temp.size(); i++){
                if(temp[i] == '.') strbfactor += ',';
                else if(temp[i] != ' ') strbfactor += temp[i];
            }

            float bfactor = 100 - atof(strbfactor.c_str());
            if(bfactor < 0) bfactor = bfactor * -1;

            stringstream stream;
            stream << fixed << setprecision(2) << bfactor;
            temp = stream.str();

            newline += line.substr(0,60);

            switch(temp.size()){
            case 4:
            {
                newline += "  " + temp;
                break;
            }
            case 5:
            {
                newline += " " + temp;
                break;
            }
            case 6:
            {
                newline += temp;
                break;
            }
            }

            newline += line.substr(66);

            pdb += newline.substr(0,newline.length()-1) + "\\n";
        }else
            pdb += line.substr(0,line.length()-1) + "\\n";
    }

    string html = this->makeVisPDBHTML(pdb);

    //printf("PDB:\n%s",pdb.c_str());


    out << html.c_str();

    indexHTML.close();
    pdbPath.close();

    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;
    ui->webConservedPDB->load(QUrl(localUrl.c_str()));

}

void MainWindow::commVisualization(){
    string path = libpath + "3Dmol/index4.html";
    QFile indexHTML(path.c_str());
    indexHTML.open(QIODevice::WriteOnly);
    QTextStream out(&indexHTML);
    QFile pdbPath(currentFilter->getCommPDBPath().c_str());
    pdbPath.open(QIODevice::ReadOnly);
    string pdb = "";

    while(!pdbPath.atEnd()){
        string line = pdbPath.readLine().data();
        string newline = "";

        //Invert B-Factors values
        if(line.substr(0,4) == "ATOM"){
            string temp = line.substr(60,6);
            string strbfactor = "";

            for(unsigned int i = 0; i < temp.size(); i++){
                if(temp[i] == '.') strbfactor += ',';
                else if(temp[i] != ' ') strbfactor += temp[i];
            }

            float bfactor = 100 - atof(strbfactor.c_str());
            if(bfactor < 0) bfactor = bfactor * -1;

            stringstream stream;
            stream << fixed << setprecision(2) << bfactor;
            temp = stream.str();

            newline += line.substr(0,60);

            switch(temp.size()){
            case 4:
            {
                newline += "  " + temp;
                break;
            }
            case 5:
            {
                newline += " " + temp;
                break;
            }
            case 6:
            {
                newline += temp;
                break;
            }
            }

            newline += line.substr(66);

            pdb += newline.substr(0,newline.length()-1) + "\\n";
        }else
            pdb += line.substr(0,line.length()-1) + "\\n";
    }

    string html = this->makeVisPDBHTML(pdb);

    //printf("PDB:\n%s",pdb.c_str());


    out << html.c_str();

    indexHTML.close();
    pdbPath.close();

    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;
    ui->webCommunitiesPDB->load(QUrl(localUrl.c_str()));
}

void MainWindow::on_cmdNexCommGraph_clicked()
{
    ui->cmdNexCommGraph->setEnabled(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade_4->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]);
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str());
    }

    //Verificar se comunidade existe ou resetar
    int nComm = currentFilter->getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_4->setText(temp.c_str());

    string pathJSON = libpath + "abor/in2.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    vector<string> nodes = currentFilter->getCommunitie(currComm);
    vector<tuple<string,string,int> > graph = currentFilter->getEdgesByComm(currComm);

    out << "{\n\t\"nodes\": {\n";
    for(unsigned int i = 0; i < nodes.size(); i++){
        out << ("\t\t\"" + nodes[i] + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"" + nodes[i] + "\"\n").c_str();

        if(i+1 < nodes.size()) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";
    for(unsigned int i = 0; i < nodes.size(); i++){
        if(i != 0) out << ",\n";
        out << ("\t\t\"" + nodes[i] + "\": {\n").c_str();

        int count = 0;
        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,int> tupCorr = graph[j];

            if(std::get<0>(tupCorr) == nodes[i] && std::get<2>(tupCorr) > 0){
                if(count > 0) out << ",\n";
                count++;

                out << ("\t\t\t\"" + std::get<1>(tupCorr) + "\": {\n").c_str();
                out << ("\t\t\t\t\"value\": " + std::to_string(std::get<2>(tupCorr)) + "\n").c_str();

                out << "\t\t\t\t}";
                //out << "\t\t\t}\n";
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";

    fileJSON.close();

    ui->webCommGraphs->reload();

    ui->cmdNexCommGraph->setEnabled(true);
}

void MainWindow::on_cmdBackCommGraph_clicked()
{
    ui->cmdBackCommGraph->setEnabled(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    //Recuperar a Comunidade Atual
    vector<string> vecSplit = split(ui->lblComunidade_4->text().toStdString(),' ');
    string temp = vecSplit[1];
    int currComm;

    if(temp.length() == 2) currComm = atoi(&temp[0]) -1;
    else{
        temp = temp[0] + temp[1];
        currComm = atoi(temp.c_str())-1;
    }

    //Verificar se comunidade existe ou resetar
    int nComm = currentFilter->getNumOfUtilComms()-1;
    if(currComm == 0 ) currComm = nComm;

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm).toStdString();
    ui->lblComunidade_4->setText(temp.c_str());

    string pathJSON = libpath + "abor/in2.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    vector<string> nodes = currentFilter->getCommunitie(currComm);
    vector<tuple<string,string,int> > graph = currentFilter->getEdgesByComm(currComm);

    out << "{\n\t\"nodes\": {\n";
    for(unsigned int i = 0; i < nodes.size(); i++){
        out << ("\t\t\"" + nodes[i] + "\": {\n").c_str();
        out << ("\t\t\t\"alignName\": \"" + nodes[i] + "\"\n").c_str();

        if(i+1 < nodes.size()) out << "\t\t\t},\n";
        else out << "\t\t}\n\t},\n";
    }

    out << "\t\"edges\":{\n";
    for(unsigned int i = 0; i < nodes.size(); i++){
        if(i != 0) out << ",\n";
        out << ("\t\t\"" + nodes[i] + "\": {\n").c_str();

        int count = 0;
        for(unsigned int j = 0; j < graph.size(); j++){
            tuple<string,string,int> tupCorr = graph[j];

            if(std::get<0>(tupCorr) == nodes[i] && std::get<2>(tupCorr) > 0){
                if(count > 0) out << ",\n";
                count++;

                out << ("\t\t\t\"" + std::get<1>(tupCorr) + "\": {\n").c_str();
                out << ("\t\t\t\t\"value\": " + std::to_string(std::get<2>(tupCorr)) + "\n").c_str();

                out << "\t\t\t\t}";
                //out << "\t\t\t}\n";
            }
        }
        out << "\n\t\t}";
    }
    out << "\t},\n\"_\": \"zebra finch bk42w74 syllable transition graph\"\n}";

    fileJSON.close();

    ui->webCommGraphs->reload();

    ui->cmdBackCommGraph->setEnabled(true);
}

void MainWindow::communitiesList(){
    unsigned int nrows = currentFilter->getCommListSize();

    //Limpa a tabela
    ui->treeCorrelationComm->clear();

    //Recupera parametros
    ui->lblFilter_4->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblMinLogP_2->setText("Minimum Score: " + QString::fromStdString(to_string(currentFilter->getCorrMinScore()).c_str()));
    ui->lblMinss_2->setText("Minss Fraction: " + QString::fromStdString(to_string(currentFilter->getCorrMinssFraction()).c_str()));
    ui->lblDeltaFreq_2->setText("Delta Frequence: " + QString::fromStdString(to_string(currentFilter->getCorrMinDelta()).c_str()));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        vector<string> residues = currentFilter->getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelationComm);

        string text = "Community " + QString::number(i+1).toStdString();
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < residues.size(); j++){
            item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(residues[j].c_str()))));
        }
    }
}

void MainWindow::corrTable1(){
    //int ncomms = currentAlign->getNumOfUtilComms();

    //Limpa a tabela
    ui->tableComm1->clear();

    //Recupera parametros
    ui->lblFilter_5->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblMinLogP_3->setText("Minimum Score: " + QString::fromStdString(to_string(currentFilter->getCorrMinScore()).c_str()));
    ui->lblMinss_3->setText("Minss Fraction: " + QString::fromStdString(to_string(currentFilter->getCorrMinssFraction()).c_str()));
    ui->lblDeltaFreq_3->setText("Delta Frequence: " + QString::fromStdString(to_string(currentFilter->getCorrMinDelta()).c_str()));
    ui->lblComunidade->setText("Community 1:");

    //Monta a tabela
    vector<string> residues = currentFilter->getResiduesComm(0);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = currentFilter->getCommAll(0);

    for(unsigned int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = currentFilter->getCommXRow(0,i);
        for(unsigned int j = 0; j < commRow.size(); j++){
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

void MainWindow::corrTable2(){
    //Limpa a Tabela
    ui->tableComm2->clear();

    //Recupera parametros
    ui->lblFilter_6->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblMinLogP_4->setText("Minimum Score: " + QString::fromStdString(to_string(currentFilter->getCorrMinScore()).c_str()));
    ui->lblMinss_4->setText("Minss Fraction: " + QString::fromStdString(to_string(currentFilter->getCorrMinScore()).c_str()));
    ui->lblDeltaFreq_4->setText("Delta Frequence: " + QString::fromStdString(to_string(currentFilter->getCorrMinDelta()).c_str()));
    ui->lblComunidade_2->setText("Community 1:");

    //Montar a Tabela
    vector<string> residues = currentFilter->getResiduesCommPs(0);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(unsigned int i = 0; i < residues.size(); i++){
        vector<int> commRow = currentFilter->getCommPsRow(0,i);

        for(unsigned int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1) item2->setText("X");
            else item2->setData(Qt::DisplayRole,commRow[j]);

            ui->tableComm2->setItem(i,j,item2);
        }
    }
    //Ajusta tamanho das colunas
    ui->tableComm2->resizeColumnsToContents();
}

void MainWindow::adh(){
    ui->lblFilter_7->setText(currentFilter->getName().c_str());

    unsigned int nComm = currentFilter->getNumOfUtilComms();
    unsigned int nSequences = currentFilter->sequences.size()-1;
    currentFilter->CalculateFrequencies();

    //currentAlign->printFrequencies();

    //Montar a Tabela
    ui->tableAdherence->horizontalHeader()->setVisible(true);
    ui->tableAdherence->setColumnCount(nComm + 1);
    ui->tableAdherence->setRowCount(nSequences);

    ui->tableAdherence->setHorizontalHeaderItem(0,new QTableWidgetItem("PROTEIN SEQUENCE"));

    for(unsigned int i = 0; i < nComm; i++){
        string temp = "Comm " + QString::number(i+1).toStdString();
        ui->tableAdherence->setHorizontalHeaderItem(i+1,new QTableWidgetItem(temp.c_str()));
    }

    //------ADHERENCE-----
    for(unsigned int i = 0; i < currentFilter->sequences.size()-1; i++){
        QTableWidgetItem *protItem = new QTableWidgetItem();
        protItem->setText(currentFilter->sequencenames[i].c_str());
        ui->tableAdherence->setItem(i,0,protItem);

        for(unsigned int j = 0; j < nComm; j++){

            if(currentFilter->Communities[j].aa.size() > 1){
                float psa = currentFilter->PSA(i,j);

                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole,psa);
                ui->tableAdherence->setItem(i,j+1,item);
            }
        }

    }
    //Ajusta tamanho das colunas
    ui->tableAdherence->resizeColumnsToContents();
}

void MainWindow::showConservedResidues(){
    vector<int> refSeqs;
    vector<char> conservedaa;
    vector<int> conservedpos;
    vector<float> conservedfreq;
    float minCons = currentFilter->getConsMin();

    //Parâmetros
    ui->lblFilter_8->setText("Filter: " + QString::fromStdString(currentFilter->getName()));
    ui->lblMinCons->setText("Minimum Conservation: " + QString::fromStdString(to_string(currentFilter->getConsMin())));


    currentFilter->CalculateFrequencies();

    for(unsigned int i = 0; i < currentFilter->getRefSeqsSize(); i++){
        string ref1 = currentFilter->getRefSeq(i);
        refSeqs.push_back(currentAlign->seqname2seqint2(ref1));
    }

    for(unsigned int i = 0; i < currentFilter->frequencies.size()-2; i++){
        for(unsigned int j = 1; j <= 20; j++){
            float freq = currentFilter->frequencies[i][j]/((float)currentFilter->sequences.size());
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
    for(unsigned int i = 0; i < conservedaa.size(); i++){
        string textCab = conservedaa[i] + QString::number(conservedpos[i] + 1).toStdString() + " (" + QString::number(conservedfreq[i],'f',1).toStdString() + ")";
        ui->tableConsRes->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    ui->tableConsRes->setRowCount(refSeqs.size());
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableConsRes->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < conservedaa.size(); j++){
            if(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,conservedpos[j],fullSequences) == 0){
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setTextColor(QColor(255,0,0,255));
                item->setText("-");
                ui->tableConsRes->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][conservedpos[j]]==conservedaa[j]){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = conservedaa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,conservedpos[j],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableConsRes->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][conservedpos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,conservedpos[j],fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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

void MainWindow::showResiduesComm(){
    vector<int> refSeqs;

    currentFilter->CalculateFrequencies();

    for(unsigned int i = 0; i < currentFilter->getRefSeqsSize(); i++){
        string ref1 = currentFilter->getRefSeq(i);

        refSeqs.push_back(currentAlign->seqname2seqint2(ref1));
    }

    //Parâmetros
    ui->lblComunidade_3->setText("Comumunity 1");

    ui->lblFilter_9->setText("Filter: " + QString::fromStdString(currentFilter->getName()));

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(currentFilter->Communities[0].pos.size());
    for(unsigned int i = 0; i < currentFilter->Communities[0].pos.size(); i++){
        string textCab = currentFilter->Communities[0].aa[i] + QString::number(currentFilter->Communities[0].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < currentFilter->Communities[0].pos.size(); j++){
            if(fullSequences[refSeqs[i]][currentFilter->Communities[0].pos[j]]==currentFilter->Communities[0].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = currentFilter->Communities[0].aa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentFilter->Communities[0].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][currentFilter->Communities[0].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][currentFilter->Communities[0].pos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentFilter->Communities[0].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableResiduesComm->setItem(i,j,item);
                }
            }
        }
    }

    //Ajusta tamanho das colunas
    ui->tableResiduesComm->resizeColumnsToContents();
}

void MainWindow::showUniprotGroupByProteins(){

    ui->lstProteinsMined->clear();
    for(unsigned int i = 0; i < currentFilter->getUniprotMinedSize(); i++){
        string prot = currentFilter->getUniprotEntryName(i) + " [" + to_string(currentFilter->getUniprotEntryNofFeatures(i)) + "]";
        ui->lstProteinsMined->addItem(prot.c_str());
    }
}

void MainWindow::showUniprotGroupByComms(){
    unsigned int nrows = currentFilter->getCommListSize();

    ui->treeMinerComms->clear();

    for(unsigned int i = 0; i < nrows; i++){
        vector<string> residues = currentFilter->getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeMinerComms);

        string text = "Comm " + QString::number(i+1).toStdString();
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < residues.size(); j++){
            int nOfResidues = currentFilter->getResidueFeaturesByCommCount(residues[j]);
            string child = residues[j] + " [" + to_string(nOfResidues) + "]";
            item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(child.c_str()))));
        }
    }

    //CONS RES
    float minCons = currentFilter->getConsMin();
    vector<string> consRes = currentFilter->getConsRes(minCons);
    if(consRes.size() > 0){
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeMinerComms);

        string text = "Conservation";
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < consRes.size(); j++){
            int nOfResidues = currentFilter->getResidueFeaturesByCommCount(consRes[j]);
            string child = consRes[j] + " [" + to_string(nOfResidues) + "]";
            item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(child.c_str()))));
        }
    }
}

vector<float> MainWindow::generateAMCL(int alfabetIndex){
    int alignCoulumnsSize = currentFilter->sequences[0].size();
    int countMatrix[alignCoulumnsSize][21] = {0};//21 is the total size without gaps
    vector<float> maxValues;

    switch(alfabetIndex){
    case 0:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'A') countMatrix[j][0] ++;
                else if(c == 'C') countMatrix[j][1] ++;
                else if(c == 'D') countMatrix[j][2] ++;
                else if(c == 'E') countMatrix[j][3] ++;
                else if(c == 'F') countMatrix[j][4] ++;
                else if(c == 'G') countMatrix[j][5] ++;
                else if(c == 'H') countMatrix[j][6] ++;
                else if(c == 'I') countMatrix[j][7] ++;
                else if(c == 'K') countMatrix[j][8] ++;
                else if(c == 'L') countMatrix[j][9] ++;
                else if(c == 'M') countMatrix[j][10] ++;
                else if(c == 'N') countMatrix[j][11] ++;
                else if(c == 'P') countMatrix[j][12] ++;
                else if(c == 'Q') countMatrix[j][13] ++;
                else if(c == 'R') countMatrix[j][14] ++;
                else if(c == 'S') countMatrix[j][15] ++;
                else if(c == 'T') countMatrix[j][16] ++;
                else if(c == 'V') countMatrix[j][17] ++;
                else if(c == 'W') countMatrix[j][18] ++;
                else if(c == 'Y') countMatrix[j][19] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 1:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'A' || c == 'G' || c == 'T' || c == 'S' || c == 'N' || c == 'Q' || c == 'D' || c == 'E' || c == 'H' || c == 'R' || c == 'K' || c == 'P')
                    countMatrix[j][0] ++;
                else if(c == 'C' || c == 'M' || c == 'F' || c == 'I' || c == 'L' || c == 'V' || c == 'W' || c == 'Y')
                    countMatrix[j][1] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 2:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'I' || c == 'V' || c == 'L')
                    countMatrix[j][0] ++;
                else if(c == 'F' || c == 'Y' || c == 'W' || c == 'H')
                    countMatrix[j][1] ++;
                else if(c == 'K' || c == 'R' || c == 'D' || c == 'E')
                    countMatrix[j][2] ++;
                else if(c == 'G' || c == 'A' || c == 'C' || c == 'S')
                    countMatrix[j][3] ++;
                else if(c == 'T' || c == 'M' || c == 'Q' || c == 'N' || c == 'P')
                    countMatrix[j][4] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 3:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'I' || c == 'V' || c == 'L')
                    countMatrix[j][0] ++;
                else if(c == 'F' || c == 'Y' || c == 'W' || c == 'H')
                    countMatrix[j][1] ++;
                else if(c == 'K' || c == 'R')
                    countMatrix[j][2] ++;
                else if(c == 'D' || c == 'E')
                    countMatrix[j][3] ++;
                else if(c == 'G' || c == 'A' || c == 'C' || c == 'S')
                    countMatrix[j][4] ++;
                else if(c == 'T' || c == 'M' || c == 'Q' || c == 'N' || c == 'P')
                    countMatrix[j][5] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 4:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'I' || c == 'V' || c == 'L' || c == 'F' || c == 'C' || c == 'M' || c == 'A' || c == 'W')
                    countMatrix[j][0] ++;
                else if(c == 'G' || c == 'T' || c == 'S' || c == 'Y' || c == 'P' || c == 'M')
                    countMatrix[j][1] ++;
                else if(c == 'D' || c == 'N' || c == 'E' || c == 'Q' || c == 'K' || c == 'R')
                    countMatrix[j][2] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 5:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'G' || c == 'A' || c == 'S')
                    countMatrix[j][0] ++;
                else if(c == 'C' || c == 'D' || c == 'P' || c == 'N' || c == 'T')
                    countMatrix[j][1] ++;
                else if(c == 'E' || c == 'V' || c == 'Q' || c == 'H')
                    countMatrix[j][2] ++;
                else if(c == 'M' || c == 'I' || c == 'L' || c == 'K' || c == 'R')
                    countMatrix[j][3] ++;
                else if(c == 'F' || c == 'Y' || c == 'W')
                    countMatrix[j][4] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 6:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'A' || c == 'V' || c == 'I' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'G') countMatrix[j][1] ++;
                else if(c == 'P') countMatrix[j][2] ++;
                else if(c == 'F') countMatrix[j][3] ++;
                else if(c == 'W') countMatrix[j][4] ++;
                else if(c == 'Y') countMatrix[j][5] ++;
                else if(c == 'D' || c == 'E') countMatrix[j][6] ++;
                else if(c == 'H' || c == 'K' || c == 'R') countMatrix[j][7] ++;
                else if(c == 'T' || c == 'S') countMatrix[j][8] ++;
                else if(c == 'C' || c == 'M') countMatrix[j][9] ++;
                else if(c == 'Q' || c == 'N') countMatrix[j][10] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 7:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'M' || c == 'V' || c == 'I' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'A') countMatrix[j][1] ++;
                else if(c == 'G') countMatrix[j][2] ++;
                else if(c == 'P') countMatrix[j][3] ++;
                else if(c == 'F' || c == 'Y') countMatrix[j][4] ++;
                else if(c == 'W') countMatrix[j][5] ++;
                else if(c == 'E') countMatrix[j][6] ++;
                else if(c == 'D') countMatrix[j][7] ++;
                else if(c == 'K' || c == 'R') countMatrix[j][8] ++;
                else if(c == 'T') countMatrix[j][9] ++;
                else if(c == 'S') countMatrix[j][10] ++;
                else if(c == 'C') countMatrix[j][11] ++;
                else if(c == 'Q') countMatrix[j][12] ++;
                else if(c == 'N') countMatrix[j][13] ++;
                else if(c == 'H') countMatrix[j][14] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 8:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'M' || c == 'V' || c == 'I' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'A') countMatrix[j][1] ++;
                else if(c == 'G') countMatrix[j][2] ++;
                else if(c == 'P') countMatrix[j][3] ++;
                else if(c == 'F' || c == 'Y' || c == 'W') countMatrix[j][4] ++;
                else if(c == 'E' || c == 'D' || c == 'N' || c == 'Q') countMatrix[j][5] ++;
                else if(c == 'K' || c == 'R') countMatrix[j][6] ++;
                else if(c == 'T' || c == 'S') countMatrix[j][7] ++;
                else if(c == 'C') countMatrix[j][8] ++;
                else if(c == 'H') countMatrix[j][9] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 9:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'C' || c == 'M' || c == 'V' || c == 'I' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'A' || c == 'G') countMatrix[j][1] ++;
                else if(c == 'P') countMatrix[j][2] ++;
                else if(c == 'F' || c == 'Y' || c == 'W') countMatrix[j][3] ++;
                else if(c == 'E' || c == 'D' || c == 'N' || c == 'Q') countMatrix[j][4] ++;
                else if(c == 'K' || c == 'R') countMatrix[j][5] ++;
                else if(c == 'T' || c == 'S') countMatrix[j][6] ++;
                else if(c == 'H') countMatrix[j][7] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 10:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'C' || c == 'M' || c == 'V' || c == 'I' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'P' || c == 'T' || c == 'S' || c == 'A' || c == 'G') countMatrix[j][1] ++;
                else if(c == 'F' || c == 'Y' || c == 'W') countMatrix[j][2] ++;
                else if(c == 'H' || c == 'R' || c == 'K' || c == 'E' || c == 'D' || c == 'N' || c == 'Q') countMatrix[j][3] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 11:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'W' || c == 'Y' || c == 'F' || c == 'P' || c == 'T' || c == 'S' || c == 'G' || c == 'A' || c == 'C' || c == 'M' || c == 'V' || c == 'I' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'E' || c == 'D' || c == 'N' || c == 'Q' || c == 'K' || c == 'R' || c == 'H') countMatrix[j][1] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 12:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    countMatrix[j][0] ++;
                else if(c == 'A' || c == 'T' || c == 'H')
                    countMatrix[j][1] ++;
                else if(c == 'G' || c == 'P')
                    countMatrix[j][2] ++;
                else if(c == 'D' || c == 'E')
                    countMatrix[j][3] ++;
                else if(c == 'S' || c == 'N' || c == 'Q' || c == 'R' || c == 'K')
                    countMatrix[j][4] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 13:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    countMatrix[j][0] ++;
                else if(c == 'L' || c == 'V' || c == 'W' || c == 'Y')
                    countMatrix[j][1] ++;
                else if(c == 'A' || c == 'T' || c == 'G' || c == 'S')
                    countMatrix[j][2] ++;
                else if(c == 'N' || c == 'Q' || c == 'D' || c == 'E')
                    countMatrix[j][3] ++;
                else if(c == 'H' || c == 'P' || c == 'R' || c == 'K')
                    countMatrix[j][4] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 14:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    countMatrix[j][0] ++;
                else if(c == 'G' || c == 'P' || c == 'R' || c == 'A' || c == 'T' || c == 'H')
                    countMatrix[j][1] ++;
                else if(c == 'K' || c == 'Q' || c == 'N' || c == 'S' || c == 'D' || c == 'E')
                    countMatrix[j][2] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 15:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    countMatrix[j][0] ++;
                else if(c == 'A' || c == 'T' || c == 'H' || c == 'G' || c == 'P' || c == 'R' || c == 'D' || c == 'E' || c == 'N' || c == 'S' || c == 'Q' || c == 'K')
                    countMatrix[j][1] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 16:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'M' || c == 'L') countMatrix[j][0] ++;
                else if(c == 'C') countMatrix[j][1] ++;
                else if(c == 'I' || c == 'V') countMatrix[j][2] ++;
                else if(c == 'P') countMatrix[j][3] ++;
                else if(c == 'F' || c == 'Y' || c == 'W') countMatrix[j][4] ++;
                else if(c == 'E' || c == 'D' || c == 'Q') countMatrix[j][5] ++;
                else if(c == 'K' || c == 'R') countMatrix[j][6] ++;
                else if(c == 'A' || c == 'T' || c == 'S') countMatrix[j][7] ++;
                else if(c == 'G') countMatrix[j][8] ++;
                else if(c == 'N' || c == 'H') countMatrix[j][9] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 17:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'Y' || c == 'C' || c == 'W' || c == 'F')
                    countMatrix[j][0] ++;
                else if(c == 'L' || c == 'V' || c == 'M' || c == 'I')
                    countMatrix[j][1] ++;
                else if(c == 'G')
                    countMatrix[j][2] ++;
                else if(c == 'P' || c == 'A' || c == 'T' || c == 'S')
                    countMatrix[j][3] ++;
                else if(c == 'H' || c == 'N' || c == 'Q' || c == 'E' || c == 'D' || c == 'R' || c == 'K')
                    countMatrix[j][4] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 18:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'C' || c == 'F' || c == 'Y' || c == 'W') countMatrix[j][0] ++;
                else if(c == 'P' || c == 'T' || c == 'S' || c == 'A' || c == 'G') countMatrix[j][1] ++;
                else if(c == 'M' || c == 'L' || c == 'I' || c == 'V') countMatrix[j][2] ++;
                else if(c == 'H' || c == 'R' || c == 'K' || c == 'E' || c == 'D' || c == 'N' || c == 'Q') countMatrix[j][3] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    case 19:
    {
        for(int j = 0; j < alignCoulumnsSize; j++){
            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                char c = toupper(currentFilter->sequences[i][j]);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    countMatrix[j][0] ++;
                else if(c == 'G' || c == 'P' || c == 'S' || c == 'A' || c == 'T')
                    countMatrix[j][1] ++;
                else if(c == 'K' || c == 'Q' || c == 'N' || c == 'H' || c == 'D' || c == 'E' || c == 'R')
                    countMatrix[j][2] ++;
                if(c != '-') countMatrix[j][20] ++;
            }
        }
        break;
    }
    }

    for(int i = 0; i < alignCoulumnsSize; i++){
        //Desconsiderar sequências com mais de 95% de gap
        if(countMatrix[i][20] < currentFilter->sequences.size()*0.05) maxValues.push_back(0);
        else{
            float maxFreq = (float)*max_element(countMatrix[i],countMatrix[i]+20)/(float)countMatrix[i][20];
            maxValues.push_back(maxFreq);
            //printf("%d/%d = %f\n",*max_element(countMatrix[i],countMatrix[i]+20),countMatrix[i][20],maxFreq);
        }
    }

    return maxValues;
}

void MainWindow::showFullAlignment(int colorIndex, int columnsIndex){
    unsigned int nrows = currentFilter->sequences.size();

    if(currentFilter->getAlphabet() == "T20"){
        ui->cmbAlphabetColor->setEnabled(true);
    }else{
        ui->cmbAlphabetColor->setCurrentText(currentFilter->getAlphabet().c_str());
        colorIndex = ui->cmbAlphabetColor->currentIndex();
        ui->cmbAlphabetColor->setEnabled(false);
    }

    ui->tableFullAlignment->clear();
    ui->tableFullAlignment->setColumnCount(currentFilter->sequences[0].size());
    ui->tableFullAlignment->setRowCount(nrows);

    QProgressDialog progress("Calculating...", "Abort", 0,nrows+10);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    vector<float> colorFreq = this->generateAMCL(colorIndex);

    for(unsigned int i = 0; i < currentFilter->sequences[0].size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i+1));
        item->setTextAlignment(Qt::AlignCenter);
        QFont font;

        if(colorFreq[i] > 0.98){
            font.setBold(true);

            ui->tableFullAlignment->showColumn(i);

        }else if(colorFreq[i] > 0.75){
            font.setUnderline(true);

            if(columnsIndex == 1) ui->tableFullAlignment->hideColumn(i);
            else ui->tableFullAlignment->showColumn(i);

        }else if(colorFreq[i] < 0.20){
            font.setItalic(true);

            if(columnsIndex == 0) ui->tableFullAlignment->showColumn(i);
            else ui->tableFullAlignment->hideColumn(i);
        }else{
            if(columnsIndex == 1 || columnsIndex == 2) ui->tableFullAlignment->hideColumn(i);
            else ui->tableFullAlignment->showColumn(i);
        }

        item->setFont(font);

        ui->tableFullAlignment->setHorizontalHeaderItem(i,item);
    }

    for(unsigned int i = 0; i < nrows; i++){
        if(progress.wasCanceled()) break;
        progress.setValue(i);

        QTableWidgetItem *item = new QTableWidgetItem(currentFilter->sequencenames[i].c_str());
        ui->tableFullAlignment->setVerticalHeaderItem(i,item);

        switch(colorIndex){
        case 0:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'A') item2->setBackgroundColor(QColor(102,0,0));
                else if(c == 'G') item2->setBackgroundColor(QColor(153,0,0));
                else if(c == 'I') item2->setBackgroundColor(QColor(204,0,0));
                else if(c == 'L') item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'P') item2->setBackgroundColor(QColor(255,102,102));
                else if(c == 'V') item2->setBackgroundColor(QColor(255,153,153));
                else if(c == 'F') item2->setBackgroundColor(QColor(51,102,0));
                else if(c == 'W') item2->setBackgroundColor(QColor(201,204,0));
                else if(c == 'Y') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'D') item2->setBackgroundColor(QColor(255,128,0));
                else if(c == 'E') item2->setBackgroundColor(QColor(255,178,102));
                else if(c == 'R') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'H') item2->setBackgroundColor(QColor(153,153,255));
                else if(c == 'K') item2->setBackgroundColor(QColor(51,153,255));
                else if(c == 'S') item2->setBackgroundColor(QColor(204,0,204));
                else if(c == 'T') item2->setBackgroundColor(QColor(255,0,255));
                else if(c == 'C') item2->setBackgroundColor(QColor(204,204,0));
                else if(c == 'M') item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'N') item2->setBackgroundColor(QColor(51,0,102));
                else if(c == 'Q') item2->setBackgroundColor(QColor(0,51,102));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 1:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'A' || c == 'G' || c == 'T' || c == 'S' || c == 'N' || c == 'Q' || c == 'D' || c == 'E' || c == 'H' || c == 'R' || c == 'K' || c == 'P')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'C' || c == 'M' || c == 'F' || c == 'I' || c == 'L' || c == 'V' || c == 'W' || c == 'Y')
                    item2->setBackgroundColor(QColor(0,0,255));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 2:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'I' || c == 'V' || c == 'L')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'F' || c == 'Y' || c == 'W' || c == 'H')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'K' || c == 'R' || c == 'D' || c == 'E')
                    item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'G' || c == 'A' || c == 'C' || c == 'S')
                    item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'T' || c == 'M' || c == 'Q' || c == 'N' || c == 'P')
                    item2->setBackgroundColor(QColor(128,128,128));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 3:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'I' || c == 'V' || c == 'L')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'F' || c == 'Y' || c == 'W' || c == 'H')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'K' || c == 'R')
                    item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'D' || c == 'E')
                    item2->setBackgroundColor(QColor(255,128,0));
                else if(c == 'G' || c == 'A' || c == 'C' || c == 'S')
                    item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'T' || c == 'M' || c == 'Q' || c == 'N' || c == 'P')
                    item2->setBackgroundColor(QColor(128,128,128));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 4:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'I' || c == 'V' || c == 'L' || c == 'F' || c == 'C' || c == 'M' || c == 'A' || c == 'W')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'G' || c == 'T' || c == 'S' || c == 'Y' || c == 'P' || c == 'M')
                    item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'D' || c == 'N' || c == 'E' || c == 'Q' || c == 'K' || c == 'R')
                    item2->setBackgroundColor(QColor(0,0,255));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 5:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'G' || c == 'A' || c == 'S')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'C' || c == 'D' || c == 'P' || c == 'N' || c == 'T')
                    item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'E' || c == 'V' || c == 'Q' || c == 'H')
                    item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'M' || c == 'I' || c == 'L' || c == 'K' || c == 'R')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'F' || c == 'Y' || c == 'W')
                    item2->setBackgroundColor(QColor(255,128,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 6:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'A' || c == 'V' || c == 'I' || c == 'L') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'G') item2->setBackgroundColor(QColor(0,255,255));
                else if(c == 'P') item2->setBackgroundColor(QColor(0,102,102));
                else if(c == 'F') item2->setBackgroundColor(QColor(255,0,255));
                else if(c == 'W') item2->setBackgroundColor(QColor(255,0,127));
                else if(c == 'Y') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'D' || c == 'E') item2->setBackgroundColor(QColor(255,128,0));
                else if(c == 'H' || c == 'K' || c == 'R') item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'T' || c == 'S') item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'C' || c == 'M') item2->setBackgroundColor(QColor(102,51,0));
                else if(c == 'Q' || c == 'N') item2->setBackgroundColor(QColor(255,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 7:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'M' || c == 'V' || c == 'I' || c == 'L') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'A') item2->setBackgroundColor(QColor(102,102,0));
                else if(c == 'G') item2->setBackgroundColor(QColor(255,0,255));
                else if(c == 'P') item2->setBackgroundColor(QColor(0,102,102));
                else if(c == 'F' || c == 'Y') item2->setBackgroundColor(QColor(0,255,255));
                else if(c == 'W') item2->setBackgroundColor(QColor(102,0,51));
                else if(c == 'E') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'D') item2->setBackgroundColor(QColor(255,128,0));
                else if(c == 'K' || c == 'R') item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'T') item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'S') item2->setBackgroundColor(QColor(0,102,0));
                else if(c == 'C') item2->setBackgroundColor(QColor(102,51,0));
                else if(c == 'Q') item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'N') item2->setBackgroundColor(QColor(102,0,102));
                else if(c == 'H') item2->setBackgroundColor(QColor(255,0,127));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 8:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'M' || c == 'V' || c == 'I' || c == 'L') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'A') item2->setBackgroundColor(QColor(102,102,0));
                else if(c == 'G') item2->setBackgroundColor(QColor(255,0,255));
                else if(c == 'P') item2->setBackgroundColor(QColor(0,102,102));
                else if(c == 'F' || c == 'Y' || c == 'W') item2->setBackgroundColor(QColor(0,255,255));
                else if(c == 'E' || c == 'D' || c == 'N' || c == 'Q') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'K' || c == 'R') item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'T' || c == 'S') item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'C') item2->setBackgroundColor(QColor(102,51,0));
                else if(c == 'H') item2->setBackgroundColor(QColor(255,0,127));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 9:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'C' || c == 'M' || c == 'V' || c == 'I' || c == 'L') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'A' || c == 'G') item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'P') item2->setBackgroundColor(QColor(0,102,102));
                else if(c == 'F' || c == 'Y' || c == 'W') item2->setBackgroundColor(QColor(0,255,255));
                else if(c == 'E' || c == 'D' || c == 'N' || c == 'Q') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'K' || c == 'R') item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'T' || c == 'S') item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'H') item2->setBackgroundColor(QColor(255,0,127));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 10:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'C' || c == 'M' || c == 'V' || c == 'I' || c == 'L') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'P' || c == 'T' || c == 'S' || c == 'A' || c == 'G') item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'F' || c == 'Y' || c == 'W') item2->setBackgroundColor(QColor(0,255,255));
                else if(c == 'H' || c == 'R' || c == 'K' || c == 'E' || c == 'D' || c == 'N' || c == 'Q') item2->setBackgroundColor(QColor(0,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 11:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'W' || c == 'Y' || c == 'F' || c == 'P' || c == 'T' || c == 'S' || c == 'G' || c == 'A' || c == 'C' || c == 'M' || c == 'V' || c == 'I' || c == 'L') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'E' || c == 'D' || c == 'N' || c == 'Q' || c == 'K' || c == 'R' || c == 'H') item2->setBackgroundColor(QColor(255,0,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 12:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'A' || c == 'T' || c == 'H')
                    item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'G' || c == 'P')
                    item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'D' || c == 'E')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'S' || c == 'N' || c == 'Q' || c == 'R' || c == 'K')
                    item2->setBackgroundColor(QColor(255,128,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 13:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'L' || c == 'V' || c == 'W' || c == 'Y')
                    item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'A' || c == 'T' || c == 'G' || c == 'S')
                    item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'N' || c == 'Q' || c == 'D' || c == 'E')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'H' || c == 'P' || c == 'R' || c == 'K')
                    item2->setBackgroundColor(QColor(255,128,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 14:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'G' || c == 'P' || c == 'R' || c == 'A' || c == 'T' || c == 'H')
                    item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'K' || c == 'Q' || c == 'N' || c == 'S' || c == 'D' || c == 'E')
                    item2->setBackgroundColor(QColor(0,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 15:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'A' || c == 'T' || c == 'H' || c == 'G' || c == 'P' || c == 'R' || c == 'D' || c == 'E' || c == 'N' || c == 'S' || c == 'Q' || c == 'K')
                    item2->setBackgroundColor(QColor(255,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 16:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'M' || c == 'L') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'C') item2->setBackgroundColor(QColor(255,0,127));
                else if(c == 'I' || c == 'V') item2->setBackgroundColor(QColor(0,255,255));
                else if(c == 'P') item2->setBackgroundColor(QColor(0,102,102));
                else if(c == 'F' || c == 'Y' || c == 'W') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'E' || c == 'D' || c == 'Q') item2->setBackgroundColor(QColor(255,255,0));
                else if(c == 'K' || c == 'R') item2->setBackgroundColor(QColor(255,0,255));
                else if(c == 'A' || c == 'T' || c == 'S') item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'G') item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'N' || c == 'H') item2->setBackgroundColor(QColor(255,128,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 17:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'Y' || c == 'C' || c == 'W' || c == 'F')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'L' || c == 'V' || c == 'M' || c == 'I')
                    item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'G')
                    item2->setBackgroundColor(QColor(128,128,128));
                else if(c == 'P' || c == 'A' || c == 'T' || c == 'S')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'H' || c == 'N' || c == 'Q' || c == 'E' || c == 'D' || c == 'R' || c == 'K')
                    item2->setBackgroundColor(QColor(255,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 18:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'C' || c == 'F' || c == 'Y' || c == 'W') item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'P' || c == 'T' || c == 'S' || c == 'A' || c == 'G') item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'M' || c == 'L' || c == 'I' || c == 'V') item2->setBackgroundColor(QColor(0,255,0));
                else if(c == 'H' || c == 'R' || c == 'K' || c == 'E' || c == 'D' || c == 'N' || c == 'Q') item2->setBackgroundColor(QColor(255,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        case 19:
        {
            for(unsigned int j = 0; j < currentFilter->sequences[i].size(); j++){
                char c = toupper(currentFilter->sequences[i][j]);
                string aa(1,c);
                QTableWidgetItem *item2 = new QTableWidgetItem(aa.c_str());
                item2->setTextAlignment(Qt::AlignCenter);

                if(c == 'Y' || c == 'W' || c == 'V' || c == 'L' || c == 'I' || c == 'C' || c == 'M' || c == 'F')
                    item2->setBackgroundColor(QColor(0,0,255));
                else if(c == 'G' || c == 'P' || c == 'S' || c == 'A' || c == 'T')
                    item2->setBackgroundColor(QColor(255,0,0));
                else if(c == 'K' || c == 'Q' || c == 'N' || c == 'H' || c == 'D' || c == 'E' || c == 'R')
                    item2->setBackgroundColor(QColor(255,255,0));

                ui->tableFullAlignment->setItem(i,j,item2);

            }
            break;
        }
        }
    }

    progress.close();

    //Ajusta tamanho das colunas
    ui->tableFullAlignment->resizeColumnsToContents();
    ui->tableFullAlignment->resizeRowsToContents();
}

void MainWindow::addAlignment(string path){
    Alignment align;
    align.setFilepath(path);
    align.GetFromFile();
    alinhamentos.push_back(path);
}

void MainWindow::changeWizardCmds(bool bl){
    ui->cmdAdvance->setVisible(bl);
    ui->cmdBack->setVisible(bl);
    ui->cmdMain->setVisible(bl);
    ui->cmdSaveResults->setVisible(bl);
}

void MainWindow::on_cmdStartWizard_clicked()
{
    this->startWizard();
}

void MainWindow::on_cmdMain_clicked()
{
    ui->cmdMain->setEnabled(false);

    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::warning(this,"Quit","This will clean all you data. Do you really want to proceed?",QMessageBox::Yes|QMessageBox::No);

    if(confirm == QMessageBox::Yes){
        //Desativa botões do Wizard
        changeWizardCmds(false);

        //Reseta campos
        resetObjects();
        for(unsigned int i = 0; i < alinhamentos.size(); i++)
            alinhamentos[i].clear();
        alinhamentos.clear();
        alinhamentos.shrink_to_fit();
        pdbs.clear();
        pdbs.shrink_to_fit();
        currentAlign = NULL;
        currentFilter = NULL;
        currentPDBContent = "";
        pdbweb = "";

        //Muda para tela 0
        ui->stackedWidget->setCurrentIndex(STACK_MAIN);

    }

    ui->cmdMain->setEnabled(true);
}

void MainWindow::on_cmdBack_clicked()
{
    //ui->cmdBack->setEnabled(false);
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    int ctIx = ui->stackedWidget->currentIndex();

    switch(ctIx){
    case STACK_MAIN:
    {
        return;
        break;
    }
    case STACK_ALIGNMENT:
    {
        ui->stackedWidget->setCurrentIndex(STACK_MAIN);

        //Apaga botões do Wizard
        changeWizardCmds(false);
        break;
    }
    case STACK_FILTER:
    {
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        ui->cmdBack->setEnabled(false);
        ui->cmdAdvance->setEnabled(true);
        break;
    }
    case STACK_REFSEQS:
    {
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_FILTER);
        break;
    }
    case STACK_PDB:
    {
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
        break;
    }
    case STACK_CONSERVATION:
    {
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_PDB);
        break;
    }
    case STACK_MINSS:
    {
        if(pdbs.size() == 0){
            ui->chkGenerateConsPDB->setChecked(false);
            emit ui->chkGenerateConsPDB->clicked(false);
        }
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
        break;
    }
    case STACK_CORRELATION:
    {
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_MINSS);
        break;
    }
    default:
    {
        changeWizardCmds(true);
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        break;
    }
    }
    //ui->cmdBack->setEnabled(true);
}

void MainWindow::on_cmdAdvance_clicked()
{
    //ui->cmdAdvance->setEnabled(false);

    int ctIx = ui->stackedWidget->currentIndex();

    switch(ctIx){
    case STACK_MAIN:
    {
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        break;
    }
    case STACK_ALIGNMENT:
    {
        if(ui->listWidget->count() == 0){
            QMessageBox::warning(this,"Warning","You must fetch an alignment before goes on.");
            return;
        }

        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_FILTER);
        break;
    }
    case STACK_FILTER:
    {
        if(ui->listWidget2->count() < 2){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Warning",
                                            "You are leaving this page without running any filter. Is that correct?",
                                            QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::No){
                return;
            }
        }

        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
        break;
    }
    case STACK_REFSEQS:
    {
        if(currentFilter->getRefSeqsSize() == 0){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Warning",
                                            "You are leaving this page without setting any reference sequence. Is that correct?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes){
                ui->cmdBack->setEnabled(true);
                ui->cmdAdvance->setEnabled(true);
                ui->stackedWidget->setCurrentIndex(STACK_PDB);
            }
            else
                return;
        }else{
            ui->cmdBack->setEnabled(true);
            ui->cmdAdvance->setEnabled(true);
            ui->stackedWidget->setCurrentIndex(STACK_PDB);
        }
        break;
    }
    case STACK_PDB:
    {
        if(pdbs.size() == 0){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Warning",
                                            "You are leaving this page without any structure loaded. Is that correct?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes){
                ui->chkGenerateConsPDB->setChecked(false);
                emit ui->chkGenerateConsPDB->clicked(false);
                ui->cmdBack->setEnabled(true);
                ui->cmdAdvance->setEnabled(true);
                ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
            }else return;
        }else{
            ui->cmdBack->setEnabled(true);
            ui->cmdAdvance->setEnabled(true);
            ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
        }
        break;
    }
    case STACK_CONSERVATION:
    {
        if(currentFilter->getConsFreqSize() == 0){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Warning",
                                            "You are leaving this page without running the conservation method. Is that correct?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::No) return;
        }

        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_MINSS);
        break;
    }
    case STACK_MINSS:
    {
        if(currentFilter->getMinssVectorSize() == 0){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Warning",
                                            "You are leaving this page without generating the minss chart. Is that correct?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::No) return;
        }

        if(pdbs.size() == 0){
            ui->chkRemoveContactResidues->setChecked(false);
            emit ui->chkRemoveContactResidues->clicked(false);
        }

        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        ui->cmdAdvance->setEnabled(false);
        ui->cmdBack->setEnabled(true);
        break;
    }
    default:
    {
        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        changeWizardCmds(true);
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
    }
    }
}

void MainWindow::on_cmdOpen_clicked()
{
    ui->cmdOpen->setEnabled(false);

    //Abre arquivo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("TEXT Files (*.txt *.pfam *.sto *.stockholm)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->cmdOpen->setEnabled(true);
        return;
    }

    QProgressDialog progress("Loading the alignment...","Cancel",0,0,this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    //Cria Alinhamento
    Alignment align;
    align.setFilepath(fileName.toUtf8().constData());
    bool a = align.GetFromFile();
    if(!a){
        ui->cmdOpen->setEnabled(true);
        QMessageBox::warning(this,"Warning","Ivalid input format.");
        return;
    }

    if(progress.wasCanceled()){
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

    //Configura para alinhamento carregado por arquivo
    align.setType(0);

    int kind = align.getKindOfAlignment();

    if(kind == 1){
        ui->cmbFilterMethod->setCurrentIndex(0);
        emit ui->cmbFilterMethod->activated(0);
    }else{
        ui->cmbFilterMethod->setCurrentIndex(1);
        emit ui->cmbFilterMethod->activated(1);
    }

    alinhamentos.push_back(align);

    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    emit ui->listWidget->activated(ui->listWidget->currentIndex());

    progress.close();

    QString msg = "Alignment loaded with " + QString::number(align.sequences.size()) + " sequences.";
    QMessageBox::information(this,"Alignment loaded",msg);

    ui->cmdOpen->setEnabled(true);
}

void MainWindow::on_cmdFetch_clicked()
{
    ui->cmdFetch->setEnabled(false);
    QString filename;
    Alignment align;

    //Validação de Dados
    if(ui->txtAccession->text() == ""){
        QMessageBox::warning(this,"Error","You must fill all fields");
        ui->cmdFetch->setText("Fetch");
        ui->cmdFetch->setEnabled(true);
        return ;
    }

    if(ui->chkDownloadAlignment->isChecked()){
        QString finalName;
        if(ui->cmbFetchFormat->currentIndex() == 0) finalName = ui->txtAccession->text() + ".sto";
        else finalName = ui->txtAccession->text() + ".pfam";
        filename = QFileDialog::getSaveFileName(this,tr("Export File"),finalName,tr("TEXT Files (*.pfam *.txt *.sto *.stockholm)"));

        if(filename == ""){
            ui->cmdFetch->setText("Fetch");
            ui->cmdFetch->setEnabled(true);
            return;
        }
    }

    QProgressDialog progress("Downloading the alignment...","Cancel",0,0,this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    //Monta URL
    QString url = "http://pfam.xfam.org/family/" + ui->txtAccession->text() + "/alignment/";
    QString format = "";

    if(ui->cmbFetchFormat->currentIndex() == 0) format = "stockholm";
    else format = "pfam";

    if(ui->radioButton->isChecked()) url += "seed/format?format=" + format + "&amp;alnType=seed&amp;order=";
    else url += "full/format?format=" + format + "&amp;alnType=full&amp;order=";

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

    if(progress.wasCanceled()){
        ui->cmdFetch->setEnabled(true);
    }
    //Salvar arquivo
    if(pfam.contains("302 Found") || pfam.contains("500 Internal Server Error") || pfam == ""){
        progress.close();
        QMessageBox::warning(this,"Error","PFAM File not Found");
        ui->cmdFetch->setText("Fetch");
        ui->cmdFetch->setEnabled(true);
        return ;
    }else{
        if(ui->chkDownloadAlignment->isChecked()){
            //Salva em arquivo
            if(filename.toStdString().find('.') == std::string::npos){ //contains
                if(ui->cmbFetchFormat->currentIndex() == 0) filename += ".sto";
                else filename += ".pfam";
            }

            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                ui->cmdFetch->setEnabled(true);
                return;
            }

            //Add na Lista
            bool same = false;
            for(int i = 0; i < ui->listWidget->count(); i++){
                if(filename ==  ui->listWidget->item(i)->text()) same = true;
            }
            if(!same) ui->listWidget->addItem(filename);

            QTextStream out(&f);
            out << pfam;
            f.close();

            align.setFilepath(filename.toUtf8().constData());
        }else{
            //Add na Lista
            bool same = false;
            for(int i = 0; i < ui->listWidget->count(); i++){
                if(ui->txtAccession->text() ==  ui->listWidget->item(i)->text()) same = true;
            }
            if(!same){
                ui->listWidget->addItem(ui->txtAccession->text());
                align.setFilepath(ui->txtAccession->text().toStdString());
            }
        }

        //Cria Alinhamento
        //addAlignment(fileName.toUtf8().constData());
        if(!align.getFromStd(pfam.toStdString())){
            progress.close();
            delete ui->listWidget->item(ui->listWidget->count()-1);
            ui->cmdFetch->setText("Fetch");
            ui->cmdFetch->setEnabled(true);
            return;
        }

        //Configura para alinhamento carregado pela web
        align.setType(1);

        if(ui->radioButton_8->isChecked() || ui->radioButton_9->isChecked()){
            ui->cmbFilterMethod->setCurrentIndex(0);
            emit ui->cmbFilterMethod->activated(0);
        }else{
            ui->cmbFilterMethod->setCurrentIndex(1);
            emit ui->cmbFilterMethod->activated(1);
        }

        alinhamentos.push_back(align);

        progress.close();

        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        emit ui->listWidget->activated(ui->listWidget->currentIndex());

        QString msg = "Alignment loaded with " + QString::number(align.sequences.size()) + " sequences.";
        QMessageBox::information(this,"Alignment loaded",msg);
    }

    ui->cmdFetch->setText("Fetch");
    ui->cmdFetch->setEnabled(true);
}

void MainWindow::on_cmdApplyFilter_clicked()
{
    ui->cmdApplyFilter->setEnabled(false);

    //VALIDATIONS
    //Select an alignment
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    //Filter name cant be blank
    if(ui->txtFilterName->text() == ""){
        QMessageBox::warning(this,"Validation problem","You must set a filter name.");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    //Filter names must be different
    for(unsigned int i = 0; i < ui->listWidget2->count(); i++){
        if(ui->txtFilterName->text() == ui->listWidget2->currentItem()->text()){
            QMessageBox::warning(this,"Validation p'roblem","There is already a filter with this name. Pleasy change the name and try again.");
            ui->cmdApplyFilter->setEnabled(true);
            return;
        }
    }

    //Validations for ref seq filter
    if(ui->cmbFilterMethod->currentIndex() == 1){
        //Ref seq cant be blank
        if(ui->cmbRefSeq->currentText() == ""){
            QMessageBox::warning(this,"Filter error","You must fill reference sequence when using the Refseq Method");
            ui->cmdApplyFilter->setEnabled(true);
            return;
        }

        //Validate the reference sequence
        bool exists = false;
        for(int i = 0; i < ui->cmbRefSeq->count(); i++){
            if(ui->cmbRefSeq->currentText() == ui->cmbRefSeq->itemText(i)){
                exists = true;
                break;
            }
        }
        if(!exists){
            QMessageBox::warning(this,"Unknown protein","Choose one of the proteins in the family to be the reference sequence");
            ui->cmdApplyFilter->setEnabled(true);
            return;
        }
    }

    if(ui->chkApplyTaxonFilter->isChecked() && ui->chkApplyTaxonFilter->isEnabled() && ui->txtTaxons->text() == ""){
        QMessageBox::warning(this,"Error","If you're going to filter by taxons, you must inform the taxon.");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    if(currentFilter->getType() != 9){
        QMessageBox::StandardButton confirm;
        confirm = QMessageBox::warning(this,"Filter","This alignment is already filtered. DO you really want apply sub-filters?",QMessageBox::Yes|QMessageBox::No);

        if(confirm == QMessageBox::No){
            ui->cmdApplyFilter->setEnabled(true);
            return;
        }
    }

    ui->cmbRefSeq_2->setCurrentIndex(ui->cmbRefSeq->currentIndex());
    ui->cmbRefSeq_2->activated(ui->cmbRefSeq_2->currentText());
    ui->cmbRefSeq_3->setCurrentIndex(ui->cmbRefSeq->currentIndex());
    ui->cmbRefSeq_4->setCurrentIndex(ui->cmbRefSeq->currentIndex());
    ui->cmbRefSeq_4->activated(ui->cmbRefSeq_4->currentText());

    ////////////////////ALIGNFILTER////////////////////
    float occupancy, minId, maxId;
    int refseq;

    occupancy = ui->txtMinCover->value();
    minId = ui->txtMinId->value();
    maxId = ui->txtMaxId->value();

    currentFilter->CalculateFrequencies();

    refseq = ui->cmbRefSeq->currentIndex()-1;

    int method = ui->cmbFilterMethod->currentIndex();

    if(method == 0)
        this->alignfilter(occupancy,maxId,ui->chkApplyMinCover->isChecked(),ui->chkApplyMaxId->isChecked(),ui->chkApplyTaxonFilter->isChecked());
    else if(method == 1)
        this->alignfilter(occupancy,minId,maxId,refseq,ui->chkApplyMinCover->isChecked(),ui->chkApplyMinId->isChecked(),ui->chkApplyMaxId->isChecked(),ui->chkApplyTaxonFilter->isChecked());
    //else if method == 2 chamar henikoff henikoff

    ui->listWidget2->setCurrentRow(ui->listWidget2->count()-1);
    emit ui->listWidget2->activated(ui->listWidget2->currentIndex());

    ui->cmdApplyFilter->setEnabled(true);
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
    if(ui->chkGenerateConsPDB->isChecked() && ui->txtPDBName->text() == ""){
        QMessageBox::warning(this,"Error","You checked to generate structure visualization, but didnt inform any PDB file.");
        ui->cmdConservation->setEnabled(true);
        return;
    }

    //Calcular a conservaçao
    string alignfilename;
    string pdbfilename = "";
    char chain;
    int refseq;
    float minCons;

    if(ui->chkGenerateConsPDB->isChecked())
        pdbfilename = ui->txtPDBName->text().toStdString();

    alignfilename = ui->listWidget->currentItem()->text().toStdString();
    refseq = ui->cmbRefSeq_2->currentIndex();
    chain = ui->txtChain->text().at(0).toLatin1();
    minCons = ui->txtMinConserv->value();
    offset = ui->txtOffset->text().toInt();

    this->conservation(refseq,offset,chain,minCons,pdbfilename);

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

    int repetitions = ui->txtNoAlignments->value();

    vector<float> minssData;
    minssData = this->minss(repetitions);

    QVector<double> x(100), y(100);
    for (int j=0; j<100; ++j)
    {
      x[j] = j+1; // x goes from -1 to 1
      y[99-j] = minssData[j]; // let's plot a quadratic function
    }

    ui->graficMinss->addGraph();
    ui->graficMinss->graph(0)->setData(x,y);
    ui->graficMinss->yAxis->setLabel("Shannon entropy value for each SA");
    ui->graficMinss->xAxis->setLabel("Size of minimum sub-alignment(SA)");
    ui->graficMinss->yAxis->setRange(y[0]-0.15,y[99]+0.15); //DGDT
    //ui->graficMinss->yAxis->setRange(y[99] - 50,0);
    ui->graficMinss->xAxis->setRange(1,100);
    ui->graficMinss->replot();


    ui->graficMinss->setVisible(true);
    ui->cmdMinss->setEnabled(true);
}

void MainWindow::on_cmdCorrelation_clicked()
{
    ui->cmdCorrelation->setEnabled(false);
    string msg = "";
    char chain = ui->txtChain_2->text()[0].toLatin1();

    //Validação de dados
    if(ui->listWidget->selectedItems().size() == 0){
        QMessageBox::warning(this,"Error","You must select a alignment.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    if(ui->txtMinssFraction->text() == ""){
        QMessageBox::warning(this,"Error","You must set a minss fraction value to run correlation.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    if(!isFloat(ui->txtMinssFraction->text().toStdString())){
        QMessageBox::warning(this,"Parse Error","Minss fraction must be a float number.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }
    float minssfraction = ui->txtMinssFraction->text().toFloat();
    if(minssfraction < 0.05 || minssfraction > 0.9){
        QMessageBox::warning(this,"Error","Minss fraction must be in the 0.05 - 0.9 interval.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    vector<tuple<string, string> > contactResidues;

    //Contact Filters
    if(ui->chkRemoveContactResidues->isChecked()){
       if(ui->txtPDBName_2->text() == ""){
           QMessageBox::warning(this,"Warning","You must choose a PDB loaded to apply the contact filter");
           ui->cmdCorrelation->setEnabled(true);
           return;
       }

       Pdb* pdb = NULL;
       for(unsigned int i = 0; i < pdbs.size(); i++){
           if(ui->txtPDBName_2->text().toStdString() == pdbs[i]->getId()){
               pdb = pdbs[i];
               break;
           }
       }

       if(pdb == NULL){
           QMessageBox::warning(this,"Warning","This is not a valid loaded structure.");
           ui->cmdConservation->setEnabled(true);
           return;
       }

       contactResidues = pdb->getResiduesInContact(ui->txtAtomDistance->value(),chain);
    }

    //Chamar PCalc
    //string outputgraphfilename = ui->txtGraphPath->text().toStdString().c_str();
    int minlogp = ui->txtMinScore->value();
    float mindeltafreq = ui->txtMinDeltaFreq->value();
    int offset = ui->txtOffset_2->text().toInt();
    int refseq = ui->cmbRefSeq_3->currentIndex();
    string pdbid = "";

    //USA ALINHAMENTO TODO EM MAIUSCULAS
    currentFilter->alignment2UpperCase();

    currentFilter->setCorrMinScore(minlogp);
    currentFilter->setCorrMinDelta(mindeltafreq);
    currentFilter->setCorrMinssFraction(minssfraction);
    currentFilter->setCorrOffset(offset);
    currentFilter->setCorrRefSeq(refseq);

    this->pcalc(minlogp,minssfraction,mindeltafreq);

    //Aplica filtro
    if(contactResidues.size() > 0){
        vector<string> filtered = currentFilter->filterCorrGraph(contactResidues,refseq);

        if(filtered.size() > 0){
            msg += "The pairs above were removed in the filtered:\n\n";
            for(unsigned int i = 0; i < filtered.size(); i++){
                msg += filtered[i] + " ";
            }
            msg += "\n\n";
        }else msg += "None correlation pair were removed in the filter.\n\n";

    }

    //Chamar Trivcomm
    this->trivcomm();

    //Chamar Output
    this->output(1,offset);

    //Gerar Visualizações
    if(ui->chkCommVisualization->isChecked()){
        if(ui->txtPDBName_2->text() == ""){
            QMessageBox::warning(this,"Warning","To generate communities visualization, you must set a PDB id");
            ui->cmdCorrelation->setEnabled(true);
            return;
        }

        Pdb* pdb = NULL;
        pdbid = ui->txtPDBName_2->text().toStdString();
        for(unsigned int i = 0; i < pdbs.size(); i++){
            if(pdbid == pdbs[i]->getId()){
                pdb = pdbs[i];
                break;
            }
        }

        if(pdb == NULL){
            QMessageBox::warning(this,"Warning","PDB not found. Maybe it hasn't been loaded.");
            ui->cmdCorrelation->setEnabled(true);
            return;
        }

        QString filename = QFileDialog::getSaveFileName(this,tr("Save correlation structure file"),"",tr("TEXT Files (*.pdb)"));
        vector<float> commvec = currentFilter->createCommuntitiesVector(refseq);
        pdb->exportStructure(filename,commvec,chain);
        currentFilter->setCommPDBPath(filename.toStdString());
    }

    currentFilter->setCorrPDB(pdbid);

    msg += "All correlations were calculated.";

    QMessageBox::information(this,"Correlation",msg.c_str());
    ui->cmdCorrelation->setEnabled(true);
}

void MainWindow::updateResultsViews(){
    switch(ui->stackedWidget2->currentIndex()){
    case STACK_RESULT_SEQLIST:
    {
        //Resetar campos de resultado
        ui->lstProteinsFiltered->clear();
        ui->txtSequence->clear();

        this->listSequences();

        break;
    }
    case STACK_RESULT_CONSFREQ:
    {
        if(currentFilter->getConsFreqSize() == 0){
            QMessageBox::warning(this,"Warning","You must run conservation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableFreq->clearContents();

        this->tableFreq();

        break;
    }
    case STACK_RESULT_FREQPERC:
    {
        if(currentFilter->getConsFreqPercSize() == 0){
            QMessageBox::warning(this,"Warning","You must run conservation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableFreqPerc->clearContents();

        this->tableFreqPerc();

        break;
    }
    case STACK_RESULT_CONSRES:
    {
        if(currentFilter->getRefSeqsSize() == 0){
            QMessageBox::warning(this,"Warning","You must select some reference sequences.");
            ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
            return;
        }

        if(currentFilter->getConsFreqPercSize() == 0){
            QMessageBox::warning(this,"Warning","You must run conservation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableConsRes->clear();

        this->showConservedResidues();

        break;
    }
    case STACK_RESULT_CORRLIST:
    {
        if(currentFilter->getCorrGraphSize() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        //Resetar campos de resultado
        ui->treeCorrelation->clear();

        this->correlationList();

        break;
    }
    case STACK_RESULT_COMMLIST:
    {
        if(currentFilter->getCommListSize() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        //Resetar campos de resultado
        ui->treeCorrelationComm->clear();

        this->communitiesList();

        break;
    }
    case STACK_RESULT_CORRPERC:
    {
        if(currentFilter->getNumOfUtilComms() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableComm1->clear();

        this->corrTable1();

        break;
    }
    case STACK_RESULT_CORRLOG:
    {
        if(currentFilter->getNumOfUtilComms() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableComm2->clear();

        this->corrTable2();

        break;
    }
    case STACK_RESULT_ADHERENCE:
    {
        if(currentFilter->getNumOfUtilComms() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableAdherence->clear();

        this->adh();

        break;
    }
    case STACK_RESULT_RESCOMM:
    {
        if(currentFilter->getRefSeqsSize() == 0){
            QMessageBox::warning(this,"Warning","You must have some reference sequences selected.");
            ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
            return;
        }

        if(currentFilter->getNumOfUtilComms() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        //Resetar campos de resultado
        ui->tableResiduesComm->clear();

        this->showResiduesComm();

        break;
    }
    case STACK_RESULT_UNIPROT_PROTEINS:
    {
        if(currentFilter->getUniprotMinedSize() == 0){
            QMessageBox::warning(this,"Warning","You must run Uniprot Looking Tool.");
            ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
            return;
        }

        //Resetar campos de resultado
        ui->lstProteinsMined->clear();
        ui->tableProteinsMined1->clearContents();

        this->showUniprotGroupByProteins();

        break;
    }
    case STACK_RESULT_UNIPROT_COMMS:
    {
        if(currentFilter->getUniprotMinedSize() == 0){
            QMessageBox::warning(this,"Warning","You must run Uniprot Looking Tool.");
            ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
            return;
        }

        //Resetar campos de resultado
        ui->treeMinerComms->clear();
        ui->tableProteinsMined2->clearContents();

        this->showUniprotGroupByComms();

        break;
    }
    case STACK_RESULT_CONSPDB:
    {
        if(currentFilter->getConsPDBPath() == ""){
            QMessageBox::warning(this,"Warning","You must run conservation with a PDB for this alignment.");
            ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
            return;
        }

        this->consVisualization();

        break;
    }
    case STACK_RESULT_COMMPDB:
    {
        if(currentFilter->getCommPDBPath() == ""){
            QMessageBox::warning(this,"Warning","You must run correlation with a PDB for this alignment.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->commVisualization();

        break;
    }
    case STACK_RESULT_CORRGRAPH:
    {
        if(currentFilter->getCorrGraphSize() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->createCorrelationJSON();

        break;
    }
    case STACK_RESULT_COMMGRAPH:
    {
        if(currentFilter->getCorrGraphSize() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->communitiesGraphs();

        break;
    }
    case STACK_RESULT_DELTAGRAPH:
    {
        if(currentFilter->getDeltasSize() == 0){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->corrBetweenComms();

        break;
    }
    case STACK_RESULT_FULLALIGN:
    {
        ui->tableFullAlignment->clear();

        this->showFullAlignment(ui->cmbAlphabetColor->currentIndex(), ui->cmbViewColumns->currentIndex());

        break;
    }
    }
}

void MainWindow::on_listWidget_activated(const QModelIndex &index)
{
    QProgressDialog progress("Loading the alignment...","Cancel",0,0,this);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    string path = index.data().toString().toStdString();
    vector<string> sequences;

    unsigned int i = 0;
    for(i = 0; i < alinhamentos.size(); i++){
        if(path == alinhamentos.at(i).getFilepath()){
            sequences = alinhamentos.at(i).getSequencesName();
            currentAlign = &alinhamentos[i];
            break;
        }
    }

    ui->cmbRefSeq->clear();
    ui->cmbRefSeq->addItem("");
    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("");
    ui->cmbRefSeq_4->clear();
    ui->cmbRefSeq_4->addItem("");
    ui->lstRefSeqs->clear();
    ui->lstRefSeqSelected->clear();
    ui->lstLookingRefs->clear();
    ui->cmbComm->clear();
    ui->lstManageComms->clear();
    ui->graficMinss->setVisible(false);

    //printf("SIZE: %d",sequences.size());
    vector<string> fullAlign = currentAlign->getFullAlignment();
    currentFilter = currentAlign->getFullFilter();
    //printf("\n%d\n",fullAlign.size());
    for(unsigned int i1 = 0; i1 < fullAlign.size(); i1++){
        vector<string> splitVec = this->split(fullAlign[i1],'/');
        ui->cmbRefSeq->addItem(QString::fromStdString(splitVec[0]));
        //ui->lstRefSeqs->addItem(QString::fromStdString(splitVec[0]));
        ui->lstLookingRefs->addItem(QString::fromStdString(splitVec[0]));

        string prot = splitVec[0];
        bool contains = false;

        for(unsigned int j = 0; j < currentFilter->getRefSeqsSize(); j++){
            string ref1 = currentFilter->getRefSeq(j);
            if(splitVec[0] == ref1){
                contains = true;
                break;
            }
        }

        if(contains){
            ui->lstRefSeqSelected->addItem(prot.c_str());
        }else{
            ui->lstRefSeqs->addItem(prot.c_str());
        }
    }

    if(ui->stackedWidget->currentIndex() == STACK_MANAGE_COMMS){
        ui->cmbComm->clear();
        unsigned int nOfComms = currentFilter->getCommListSize();

        for(unsigned int j = 1; j <= nOfComms; j++)
            ui->cmbComm->addItem(QString::number(j));
    }else if(ui->stackedWidget->currentIndex() == STACK_RESULTS){
        this->updateResultsViews();
    }

    ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(fullAlign.size()));

    ui->listWidget2->clear();

    vector<Filter*> filters = currentAlign->getFilters();

    for(unsigned int j = 0; j < filters.size(); j++){
        Filter* filter = filters[j];
        ui->listWidget2->addItem(filter->getName().c_str());
    }

    ui->listWidget2->setCurrentRow(ui->listWidget2->count()-1);

    emit ui->listWidget2->activated(ui->listWidget2->currentIndex());

    progress.close();

    //ui->cmbRefSeq_2->setCurrentIndex(1);
    //ui->cmbRefSeq_3->setCurrentIndex(1);
}

void MainWindow::on_cmbRefSeq_activated(int index)
{
    if(index == 0) return;

    ui->cmbRefSeq_2->setCurrentIndex(index);
    ui->cmbRefSeq_2->activated(ui->cmbRefSeq_2->currentText());
    ui->cmbRefSeq_3->setCurrentIndex(index);
    ui->cmbRefSeq_4->setCurrentIndex(index);
    ui->cmbRefSeq_4->activated(ui->cmbRefSeq_4->currentText());

    //QMessageBox::information(this,"a",currentAlign->sequencenames[index-1].c_str());
    currentFilter->setRefSeqName(currentFilter->sequencenames[index-1]);
    int offset = currentFilter->getRefSeqOffset();
    QString qoffset = QString::number(offset);
    ui->txtOffset->setText(qoffset);
    ui->txtOffset_2->setText(qoffset);
}

void MainWindow::on_cmbRefSeq_2_activated(int index)
{
    //TAMBEM TEM EVENTO ACTIVATED COM PARAMETRO STRING
    if(index == 0) return;

    ui->cmbRefSeq->setCurrentIndex(index);
    ui->cmbRefSeq_3->setCurrentIndex(index);

    //QMessageBox::information(this,"a",currentAlign->sequencenames[index-1].c_str());
    currentFilter->setRefSeqName(currentFilter->sequencenames[index-1]);
    int offset = currentFilter->getRefSeqOffset();
    QString qoffset = QString::number(offset);
    ui->txtOffset->setText(qoffset);
    ui->txtOffset_2->setText(qoffset);
}



void MainWindow::on_cmbRefSeq_3_activated(int index)
{
    if(index == 0) return;

    string path = ui->listWidget->currentItem()->text().toUtf8().constData();
    ui->cmbRefSeq->setCurrentIndex(index);
    ui->cmbRefSeq_2->setCurrentIndex(index);
    ui->cmbRefSeq_2->activated(ui->cmbRefSeq_2->currentText());

    //QMessageBox::information(this,"a",currentAlign->sequencenames[index-1].c_str());
    currentFilter->setRefSeqName(currentFilter->sequencenames[index-1]);
    int offset = currentFilter->getRefSeqOffset();
    QString qoffset = QString::number(offset);
    ui->txtOffset->setText(qoffset);
    ui->txtOffset_2->setText(qoffset);
}

void MainWindow::on_cmdSaveResults_clicked()
{
    this->saveResults();
}

void MainWindow::on_lstProteinsFiltered_activated(const QModelIndex &index)
{
    string sequence = currentFilter->getSequence(index.data().toString().toStdString());

    ui->txtSequence->setText(sequence.c_str());
}

void MainWindow::on_cmdNextComm_clicked()
{
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
    int nComm = currentFilter->getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableComm1->clear();

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade->setText(temp.c_str());

    //Monta a Tabela
    vector<string> residues = currentFilter->getResiduesComm(currComm);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = currentFilter->getCommAll(currComm);

    for(unsigned int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = currentFilter->getCommXRow(currComm,i);
        for(unsigned int j = 0; j < commRow.size(); j++){
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
    int nComm = currentFilter->getNumOfUtilComms();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableComm1->clear();

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm).toStdString();
    ui->lblComunidade->setText(temp.c_str());

    //Monta a Tabela
    vector<string> residues = currentFilter->getResiduesComm(currComm-1);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = currentFilter->getCommAll(currComm-1);

    for(unsigned int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = currentFilter->getCommXRow(currComm-1,i);
        for(unsigned int j = 0; j < commRow.size(); j++){
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
    int nComm = currentFilter->getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableComm2->clear();

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_2->setText(temp.c_str());

    //Montar a Tabela
    vector<string> residues = currentFilter->getResiduesCommPs(currComm);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(unsigned int i = 0; i < residues.size(); i++){
        vector<int> commRow = currentFilter->getCommPsRow(currComm,i);

        for(unsigned int j = 0; j < commRow.size(); j++){
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
    int nComm = currentFilter->getNumOfUtilComms();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableComm2->clear();

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm).toStdString();
    ui->lblComunidade_2->setText(temp.c_str());

    //Montar a Tabela
    vector<string> residues = currentFilter->getResiduesCommPs(currComm -1);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(unsigned int i = 0; i < residues.size(); i++){
        vector<int> commRow = currentFilter->getCommPsRow(currComm-1,i);

        for(unsigned int j = 0; j < commRow.size(); j++){
            QTableWidgetItem *item2 = new QTableWidgetItem();

            if(commRow[j] == -1) item2->setText("X");
            else item2->setData(Qt::DisplayRole,commRow[j]);

            ui->tableComm2->setItem(i,j,item2);
        }
    }

    //Ajusta tamanho das colunas
    ui->tableComm2->resizeColumnsToContents();
}

void MainWindow::on_cmdNextResComm_clicked()
{
    ui->cmdNextResComm->setEnabled(false);

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
    int nComm = currentFilter->Communities.size();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableResiduesComm->clear();

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_3->setText(temp.c_str());

    vector<int> refSeqs;

    for(unsigned int j = 0; j < currentFilter->getRefSeqsSize(); j++){
        refSeqs.push_back(currentAlign->seqname2seqint2(currentFilter->getRefSeq(j)));
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(currentFilter->Communities[currComm].pos.size());
    for(unsigned int i = 0; i < currentFilter->Communities[currComm].pos.size(); i++){
        string textCab = currentFilter->Communities[currComm].aa[i] + QString::number(currentFilter->Communities[currComm].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < currentFilter->Communities[currComm].pos.size(); j++){
            if(fullSequences[refSeqs[i]][currentFilter->Communities[currComm].pos[j]]==currentFilter->Communities[currComm].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = currentFilter->Communities[currComm].aa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentFilter->Communities[currComm].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][currentFilter->Communities[currComm].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][currentFilter->Communities[currComm].pos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentFilter->Communities[currComm].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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
    int nComm = currentFilter->Communities.size();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableResiduesComm->clear();

    //Modifica parâmetros
    temp = "Community " + QString::number(currComm).toStdString();
    ui->lblComunidade_3->setText(temp.c_str());

    vector<int> refSeqs;

    for(unsigned int j = 0; j < currentFilter->getRefSeqsSize(); j++){
        refSeqs.push_back(currentAlign->seqname2seqint2(currentFilter->getRefSeq(j)));
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(currentFilter->Communities[currComm -1].pos.size());
    for(unsigned int i = 0; i < currentFilter->Communities[currComm -1].pos.size(); i++){
        string textCab = currentFilter->Communities[currComm -1].aa[i] + QString::number(currentFilter->Communities[currComm-1].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < currentFilter->Communities[currComm -1].pos.size(); j++){
            if(fullSequences[refSeqs[i]][currentFilter->Communities[currComm-1].pos[j]]==currentFilter->Communities[currComm-1].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = currentFilter->Communities[currComm-1].aa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentFilter->Communities[currComm-1].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][currentFilter->Communities[currComm-1].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][currentFilter->Communities[currComm-1].pos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentFilter->Communities[currComm-1].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("XML Files (*.xml)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    reader.setDevice(&file);

    int currentFilterCode = -1;
    Alignment align;
    align.setFilepath(fileName.toStdString());


    while(!reader.atEnd()){
        reader.readNext();
        //FILTER
        if(reader.isStartElement() && reader.name() == "filters"){
            while(!reader.atEnd()){
                reader.readNext();
                if(reader.isStartElement() && reader.name() == "filter"){
                    string name = reader.attributes().value("name").toString().toStdString();
                    string strType = reader.attributes().value("type").toString().toStdString();
                    string taxon = reader.attributes().value("taxon").toString().toStdString();
                    float occ = reader.attributes().value("occ").toFloat();
                    float minid = reader.attributes().value("minid").toFloat();
                    float maxid = reader.attributes().value("maxid").toFloat();
                    string refseq = reader.attributes().value("refseq").toString().toStdString();
                    string alphabet = reader.attributes().value("alphabet").toString().toStdString();
                    int type = 9;

                    if(strType == "Full Alignment"){
                        if(alphabet == "T20") type = 9;
                        else type = 8;
                    }else if(strType == "HMM") type = 0;
                    else if(strType == "Refseq") type = 1;
                    else if(strType == "Henikof") type = 2;

                    Filter* filter = new Filter(name,alphabet,type);
                    filter->setTaxon(taxon);
                    filter->setMinOcc(occ);
                    filter->setMinId(minid);
                    filter->setMaxId(maxid);
                    filter->setRefSeq(refseq);
                    vector<string> names;
                    vector<string> seqs;
                    currentFilterCode++;

                    while(!reader.atEnd()){
                        reader.readNext();

                        if(reader.isStartElement()){
                            if(reader.name() == "seqlist"){
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement()){
                                        if(reader.name() == "sequence"){
                                            string seqName = reader.attributes().value("name").toString().toStdString();
                                            string seq = reader.readElementText().toStdString();
                                            names.push_back(seqName);
                                            seqs.push_back(seq);
                                        }
                                    }else if(reader.isEndElement() && reader.name() == "seqlist"){
                                        filter->addSequences(names,seqs);
                                        //align.addFilter(filter);

                                        break;
                                    }
                                }
                            }else if(reader.name() == "references"){
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "sequence"){
                                        string refseq = reader.readElementText().toStdString();
                                        filter->addRefSeq(refseq);
                                    }else if(reader.isEndElement() && reader.name() == "references")
                                        break;
                                }
                            }else if(reader.name() == "conservation"){
                                vector<float> dg;
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "parameters"){
                                        while(!reader.atEnd()){
                                            reader.readNext();

                                            if(reader.isStartElement()){
                                                if(reader.name() == "pdb"){
                                                    string pdb = reader.readElementText().toStdString();
                                                    filter->setConsPDB(pdb);
                                                }else if(reader.name() == "offset"){
                                                    int offset = reader.readElementText().toInt();
                                                    filter->setConsOffset(offset);
                                                }else if(reader.name() == "minimum"){
                                                    float min = reader.readElementText().toFloat();
                                                    filter->setConsMin(min);
                                                }else if(reader.name() == "refseq"){
                                                    int ref = reader.readElementText().toInt();
                                                    filter->setConsRefseq(ref);
                                                }
                                            }else if(reader.isEndElement() && reader.name() == "parameters"){
                                                break;
                                            }
                                        }
                                    }else if(reader.isStartElement() && reader.name() == "positions"){
                                        vector<int> freq;
                                        vector<float> freqperc;

                                        while(!reader.atEnd()){
                                            reader.readNext();

                                            if(reader.isStartElement() && reader.name() == "pos"){
                                                while(!reader.atEnd()){
                                                    reader.readNext();

                                                    if(reader.isStartElement()){
                                                        if(reader.name() == "deltaG")
                                                            dg.push_back(reader.readElementText().toFloat());
                                                        else if(reader.name() == "frequence")
                                                            freq.push_back(reader.readElementText().toInt());
                                                        else if(reader.name() == "percent")
                                                            freqperc.push_back(reader.readElementText().toFloat());
                                                    }else if(reader.isEndElement() && reader.name() == "pos"){
                                                        filter->addConsFreqRow(freq);
                                                        filter->addConsFreqPercRow(freqperc);
                                                        freq.clear();
                                                        freqperc.clear();
                                                        break;
                                                    }
                                                }
                                            }else if(reader.isEndElement() && reader.name() == "positions")
                                                break;
                                        }
                                    }else if(reader.isEndElement() && reader.name() == "conservation"){
                                        filter->setConsDG(dg);
                                        //filter->printConsFreq();
                                        //printf("\n\n");
                                        //filter->printConsFreqPerc();
                                        break;
                                    }
                                }
                            }else if(reader.isStartElement() && reader.name() == "minss"){
                                vector<float> minss;

                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "data"){
                                        minss.push_back(reader.readElementText().toFloat());
                                    }else if(reader.isEndElement() && reader.name() == "minss"){
                                        filter->setMinss(minss);
                                        break;
                                    }
                                }
                            }else if(reader.isStartElement() && reader.name() == "correlation"){
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement()){
                                        if(reader.name() == "parameters"){
                                            while(!reader.atEnd()){
                                                reader.readNext();

                                                if(reader.isStartElement()){
                                                    if(reader.name() == "pdb"){
                                                        string pdb = reader.readElementText().toStdString();
                                                        filter->setCorrPDB(pdb);
                                                    }else if(reader.name() == "offset"){
                                                        int offset = reader.readElementText().toInt();
                                                        filter->setCorrOffset(offset);
                                                    }else if(reader.name() == "min_score"){
                                                        float score = reader.readElementText().toFloat();
                                                        filter->setCorrMinScore(score);
                                                    }else if(reader.name() == "minss"){
                                                        float minss = reader.readElementText().toFloat();
                                                        filter->setCorrMinssFraction(minss);
                                                    }else if(reader.name() == "min_delta"){
                                                        float delta = reader.readElementText().toFloat();
                                                        filter->setCorrMinDelta(delta);
                                                    }else if(reader.name() == "refseq"){
                                                        int refseq = reader.readElementText().toInt();
                                                        filter->setCorrRefSeq(refseq);
                                                    }
                                                }else if(reader.isEndElement() && reader.name() == "parameters")
                                                    break;
                                            }
                                        }else if(reader.name() == "graph"){
                                            while(!reader.atEnd()){
                                                reader.readNext();

                                                if(reader.isStartElement() && reader.name() == "edge"){
                                                    string v1 = reader.attributes().value("v1").toString().toStdString();
                                                    string v2 = reader.attributes().value("v2").toString().toStdString();
                                                    int score = reader.readElementText().toInt();

                                                    filter->addCorrEdge(v1,v2,score);
                                                }else if(reader.isEndElement() && reader.name() == "graph")
                                                    break;
                                            }
                                        }else if(reader.name() == "communities"){
                                            vector<string> comms;

                                            while(!reader.atEnd()){
                                                reader.readNext();

                                                if(reader.isStartElement() && reader.name() == "community"){
                                                    comms.clear();
                                                    string node;

                                                    while(!reader.atEnd()){
                                                        reader.readNext();

                                                        if(reader.isStartElement() && reader.name() == "node"){
                                                            node = reader.readElementText().toStdString();
                                                            comms.push_back(node);
                                                        }else if(reader.isEndElement() && reader.name() == "community"){
                                                            filter->addCommunity(comms);
                                                            break;
                                                        }
                                                    }
                                                }else if(reader.isEndElement() && reader.name() == "communities")
                                                    break;
                                            }
                                        }else if(reader.name() == "output"){
                                            vector<string> residues;
                                            vector<string> residuesPs;

                                            while(!reader.atEnd()){
                                                reader.readNext();

                                                if(reader.isStartElement()){
                                                    if(reader.name() == "community"){
                                                        vector<float> resAll;
                                                        vector<vector<float> > commX;
                                                        residues.clear();

                                                        while(!reader.atEnd()){
                                                            reader.readNext();

                                                            if(reader.isStartElement() && reader.name() == "column"){
                                                                string res = reader.readElementText().toStdString();
                                                                if(res != "ALL") residues.push_back(res);
                                                            }else if(reader.isStartElement() && reader.name() == "row"){
                                                                vector<float> values;

                                                                resAll.push_back(reader.attributes().at(1).value().toFloat());

                                                                for(unsigned int i = 2; i < reader.attributes().size(); i++){
                                                                    values.push_back(reader.attributes().at(i).value().toFloat()/100);
                                                                }

                                                                commX.push_back(values);
                                                            }else if(reader.isEndElement() && reader.name() == "community"){
                                                                filter->addResiduesComm(residues);
                                                                filter->addCommXAll(resAll);
                                                                filter->addCommX(commX);
                                                                break;
                                                            }
                                                        }
                                                    }else if(reader.name() == "logP"){
                                                        vector<vector<int> > commXPs;
                                                        residuesPs.clear();

                                                        while(!reader.atEnd()){
                                                            reader.readNext();

                                                            if(reader.isStartElement() && reader.name() == "column"){
                                                                residuesPs.push_back(reader.readElementText().toStdString());
                                                            }else if(reader.isStartElement() && reader.name() == "row"){
                                                                vector<int> values;

                                                                for(unsigned int i = 1; i < reader.attributes().size(); i++){
                                                                    values.push_back(reader.attributes().at(i).value().toInt());
                                                                }

                                                                commXPs.push_back(values);
                                                            }else if(reader.isEndElement() && reader.name() == "logP"){
                                                                filter->addResiduesCommPs(residuesPs);
                                                                filter->addCommXPs(commXPs);
                                                                break;
                                                            }
                                                        }
                                                    }
                                                }else if(reader.isEndElement() && reader.name() == "output")
                                                    break;
                                            }
                                        }else if(reader.name() == "deltas"){
                                            while(!reader.atEnd()){
                                                reader.readNext();

                                                if(reader.isStartElement() && reader.name() == "row"){
                                                    vector<float> deltaLines;

                                                    for(unsigned int i = 0; i < reader.attributes().size(); i++)
                                                        deltaLines.push_back(reader.attributes().at(i).value().toFloat());

                                                    filter->addDeltaLine(deltaLines);
                                                }else if(reader.isEndElement() && reader.name() == "deltas"){
                                                    break;
                                                }
                                            }
                                        }
                                    }else if(reader.isEndElement() && reader.name() == "correlation")
                                        break;
                                }
                            }//ELSE PRA CONTINUAR UNIPROT LOOK
                        }else if(reader.isEndElement() && reader.name() == "filter"){
                            align.addFilter(filter);

                            break;
                        }
                    }
                }
            }
        }else if(reader.isEndElement() && reader.name() == "filters")
            break;
    }

    if(align.countFilters() == 0){
        QMessageBox::warning(this,"Warning","Invalid input file. The data may be corrupted");
        return;
    }

    align.updateFiltersData();
    ui->listWidget->addItem(fileName);
    alinhamentos.push_back(align);

    if(ui->stackedWidget->currentIndex() == STACK_MAIN){
        //Desativa botões do Wizard
        changeWizardCmds(false);
        wizard = false;

        //Desativa botao voltar
        ui->cmdBack->setEnabled(false);

        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
    }

    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    emit ui->listWidget->activated(ui->listWidget->currentIndex());

    QString msg = "Alignment loaded with " + QString::number(currentFilter->sequences.size()) + " sequences.";
    QMessageBox::information(this,"Alignment loaded",msg);
}

void MainWindow::on_cmdRemoveFilter_clicked()
{

    if(ui->listWidget2->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a filter to remove.");
        return;
    }

    if(currentFilter->getType() == 9){
        QMessageBox::warning(this,"Error","You cant remove full alignment.");
        return;
    }

    int pos = ui->listWidget2->currentIndex().row();
    currentAlign->removeFilter(ui->listWidget2->currentItem()->text().toStdString());
    delete ui->listWidget2->item(pos);
    ui->listWidget2->setCurrentRow(0);
    emit ui->listWidget2->activated(ui->listWidget2->currentIndex());
}

void MainWindow::on_cmdRemoveAlignment_clicked()
{
    this->closeAlignment();
}

void MainWindow::exportAlignment_PFAM(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("alignment.pfam"),QObject::tr("TEXT Files (*.txt *.pfam)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFilteredAlignment(filename,0);
}

void MainWindow::exportAlignment_TXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("alignment.txt"),QObject::tr("TEXT Files (*.txt *.pfam *.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFilteredAlignment(filename,1);
}

void MainWindow::exportAlignment_XML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("alignment.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFilteredAlignment(filename,2);
}

void MainWindow::exportRefSeqTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","There's no reference sequence loaded.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("reference_sequences.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportRefs(filename,0);
}

void MainWindow::exportRefSeqXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","There's no reference sequence loaded.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("reference_sequences.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportRefs(filename,1);
}

void MainWindow::exportFreqTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,0);
}

void MainWindow::exportFreqCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences.csv"),QObject::tr("TEXT Files (*.csv)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,1);
}

void MainWindow::exportFreqXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,2);
}

void MainWindow::exportFreqHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,3);
}

void MainWindow::exportFreqPercTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences_perc.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,0,true);
}

void MainWindow::exportFreqPercCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences_perc.csv"),QObject::tr("TEXT Files (*.csv)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,1,true);
}

void MainWindow::exportFreqPercXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences_perc.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,2,true);
}

void MainWindow::exportFreqPercHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("frequences_perc.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportFreq(filename,3,true);
}

void MainWindow::exportConsResTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","You didnt set some reference sequences to visualize.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("conserved_residues.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    vector<int> refSeqs;
    for(unsigned int i2 = 0; i2 < currentFilter->getRefSeqsSize(); i2++){
        string ref1 = currentFilter->getRefSeq(i2);
        //printf("%s\n",ref1.c_str());
        refSeqs.push_back(currentAlign->seqname2seqint2(ref1));
    }

    currentFilter->exportConsRes(filename,0,ui->txtMinConserv->value(),refSeqs,fullAlignment,fullSequences);
}

void MainWindow::exportConsResXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","You didnt set some reference sequences to visualize.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("conserved_residues.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    vector<int> refSeqs;
    for(unsigned int i2 = 0; i2 < currentFilter->getRefSeqsSize(); i2++){
        string ref1 = currentFilter->getRefSeq(i2);
        //printf("%s\n",ref1.c_str());
        refSeqs.push_back(currentAlign->seqname2seqint2(ref1));
    }

    currentFilter->exportConsRes(filename,1,ui->txtMinConserv->value(),refSeqs,fullAlignment,fullSequences);
}

void MainWindow::exportConsResHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation before export results");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","You didnt set some reference sequences to visualize.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("conserved_residues.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    vector<int> refSeqs;
    for(unsigned int i2 = 0; i2 < currentFilter->getRefSeqsSize(); i2++){
        string ref1 = currentFilter->getRefSeq(i2);
        //printf("%s\n",ref1.c_str());
        refSeqs.push_back(currentAlign->seqname2seqint2(ref1));
    }

    currentFilter->exportConsRes(filename,2,ui->txtMinConserv->value(),refSeqs,fullAlignment,fullSequences);
}

void MainWindow::exportCorrListTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation_list.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrGraph(filename,0);
}

void MainWindow::exportCorrListCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation_list.csv"),QObject::tr("TEXT Files (*.csv)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrGraph(filename,1);
}

void MainWindow::exportCorrListXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation_list.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrGraph(filename,2);
}

void MainWindow::exportCommsTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("communities.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCommList(filename,0);
}

void MainWindow::exportCommsXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("communities.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCommList(filename,1);
}

void MainWindow::exportCorrTablePercTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrTable(filename,0);
}

void MainWindow::exportCorrTablePercXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrTable(filename,1);
}

void MainWindow::exportCorrTablePercHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrTable(filename,2);
}

void MainWindow::exportCorrTableTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrTable(filename,0,false);
}

void MainWindow::exportCorrTableXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrTable(filename,1,false);
}

void MainWindow::exportCorrTableHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportCorrTable(filename,2,false);
}

void MainWindow::exportAdhTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportAdh(filename,0);
}

void MainWindow::exportAdhCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.csv"),QObject::tr("TEXT Files (*.csv)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportAdh(filename,1);
}

void MainWindow::exportAdhXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportAdh(filename,2);
}

void MainWindow::exportAdhHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportAdh(filename,3);
}

void MainWindow::exportResCommTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    currentFilter->CalculateFrequencies();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("residues_communities.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportResComm(filename,0,fullAlignment,fullSequences);
}

void MainWindow::exportResCommXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    currentFilter->CalculateFrequencies();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("residues_communities.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportResComm(filename,1,fullAlignment,fullSequences);
}

void MainWindow::exportResCommHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation before export this result");
        return;
    }

    currentFilter->CalculateFrequencies();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("residues_communities.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentFilter->exportResComm(filename,2,fullAlignment,fullSequences);
}

void MainWindow::startWizard(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    //Diz que usuario esta executando wizard
    wizard = true;

    //Ativa botões do Wizard
    changeWizardCmds(true);

    //Desativa botao voltar
    ui->cmdBack->setEnabled(false);

    //Muda para tela 1
    ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
}

void MainWindow::changetoFilterStack(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_FILTER);
}

void MainWindow::changeToRefSeqs(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
}

void MainWindow::changeToLoadPDBs(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_PDB);
}

void MainWindow::changeToConservationStack(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;

    this->changeWizardCmds(false);

    if(pdbs.size() == 0){
        ui->chkGenerateConsPDB->setChecked(false);
        emit ui->chkGenerateConsPDB->clicked(false);
    }

    ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
}

void MainWindow::changetoMinssStack(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_MINSS);
}

void MainWindow::changetoCorrelationStack(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;

    this->changeWizardCmds(false);

    if(pdbs.size() == 0){
        ui->chkRemoveContactResidues->setChecked(false);
        emit ui->chkRemoveContactResidues->clicked(false);
    }

    ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
}

void MainWindow::changeToUniprotLookingTool(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select a alignment.");
        return;
    }

    if(currentFilter->getConsFreqSize() > 0){
        ui->chkConserveds->setCheckable(true);
        ui->chkConserveds->setChecked(true);
    }else ui->chkConserveds->setCheckable(false);

    if(currentFilter->getCommListSize() > 0){
        ui->chkComm->setCheckable(true);
        ui->chkComm->setChecked(true);
    }else ui->chkComm->setCheckable(false);

    if(currentFilter->getConsFreqSize() == 0 && currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run at least Conservation or Correlation programs before use this.");
        return;
    }

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
}

void MainWindow::graphClicked(QCPAbstractPlottable *plot, QMouseEvent *mouse){
    float xValue = plot->keyAxis()->pixelToCoord(mouse->pos().x());
    float yValue = ui->graficMinss->yAxis->pixelToCoord(mouse->pos().y());
    vector<string> temp = this->split(ui->lblNseq->text().toStdString(),' ');
    string strNSeq = temp[temp.size() -1];
    int nSeq = stoi(strNSeq);
    float minssFrac = xValue/100;
    float seqs = nSeq*minssFrac;
    nSeq = (int)seqs;

    minssLabel->setText(QString::number(nSeq) + " sequences (" + QString::number(minssFrac,'f',2) + ")");
    minssLabel->position->setCoords(xValue,yValue);
    ui->txtMinssFraction->setText(QString::number(minssFrac,'f',2));
    ui->graficMinss->addItem(minssLabel);

    //QMessageBox::information(this,"a",QString::number(nSeq));
}

void MainWindow::saveResults(){
    ui->cmdSaveResults->setEnabled(false);

    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    vector<string> vecPath = split(currentAlign->getFilepath(),'.');
    string path = "";

    if(vecPath.size() == 1){
        path = vecPath[0] + ".xml";
    }else{
        for(unsigned int i=0;i<vecPath.size()-1;i++){
            path += vecPath[i];
        }
        path += ".xml";
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Saving results file"),path.c_str(),QObject::tr("XML Files (*.xml)"));

    currentAlign->generateXML(filename.toStdString());

    string msg = "XML file was generated in the above path:\n\n" + filename.toStdString();
    QMessageBox::information(this,"Save Results",msg.c_str());

    ui->cmdSaveResults->setEnabled(true);
}

void MainWindow::closeAlignment(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to remove.");
        return;
    }

    //Acha qual alinhamento está trabalhando
    string path = ui->listWidget->currentItem()->text().toUtf8().constData();

    unsigned int i = 0;
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
    ui->stackedWidget->setCurrentIndex(STACK_MAIN);
}

void MainWindow::showAbout(){
    About* about = new About(this);

    about->show();
}


void MainWindow::on_cmdLook_clicked()
{
    ui->cmdLook->setEnabled(false);

    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment.");
        return;
    }

    if(!ui->chkConserveds->isChecked() && !ui->chkComm->isChecked()){
        QMessageBox::warning(this,"Error","You must select at least one kind of targets.");
        return;
    }

    if(ui->lstLookingRefs->selectedItems().size() == 0){
        QMessageBox::warning(this,"Error","You must select at least one protein of the list.");
        return;
    }

    vector<string> proteins;
    vector<int> idproteins;
    for(int j = 0; j < ui->lstLookingRefs->count(); j++){
        if(ui->lstLookingRefs->item(j)->isSelected()){
            proteins.push_back(ui->lstLookingRefs->item(j)->text().toStdString());
            idproteins.push_back(j);
        }
    }

    float minCons = currentFilter->getConsMin();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    currentFilter->uniprotLook(ui->chkConserveds->isChecked(),ui->chkComm->isChecked(),proteins,idproteins,minCons,fullAlignment,fullSequences);

    ui->cmdLook->setEnabled(true);
}

void MainWindow::on_cmdLookNone_clicked()
{
    ui->lstLookingRefs->clearSelection();
}

void MainWindow::on_cmdLookAll_clicked()
{
    ui->lstLookingRefs->selectAll();
}

void MainWindow::on_lstProteinsMined_activated(const QModelIndex &index)
{
    ui->tableProteinsMined1->clearContents();
    string name = index.data().toString().split(' ')[0].toStdString();

    //Acha a entrada uniprot selecionada
    unsigned int j = 0;
    for(j = 0; j < currentFilter->getUniprotMinedSize(); j++){
        if(currentFilter->getUniprotEntryName(j) == name){
            break;
        }
    }

    string function = "Function: " + currentFilter->getUniprotFunction(j);
    ui->lblUniprotFunction->setText(function.c_str());
    ui->lblUniprotFunction->setWordWrap(true);

    ui->tableProteinsMined1->setRowCount(currentFilter->getUniprotEntryNofFeatures(j));
    for(unsigned int k = 0; k < currentFilter->getUniprotEntryNofFeatures(j); k++){
        Feature *f = currentFilter->getUniprotFeature(j,k);

        printf("\nRES: %s\nAGREG:%d\n",f->getResidueColigated().c_str(),f->getAgregate());

        if(f->getResidueColigated() != "" && f->getAgregate() != -1){
            QTableWidgetItem *itemA = new QTableWidgetItem();
            itemA->setText(f->getAlignResidue().c_str());
            ui->tableProteinsMined1->setItem(k,0,itemA);

            QTableWidgetItem *item = new QTableWidgetItem();
            if(f->getAlignResidue()[0] != f->getResidueColigated()[0])
                item->setTextColor(QColor(255,0,0));
            item->setText(f->getResidueColigated().c_str());
            ui->tableProteinsMined1->setItem(k,1,item);

            QTableWidgetItem *item2 = new QTableWidgetItem();
            if(f->getAgregate() == 0) item2->setText("CONS");
            else item2->setText(QString::number(f->getAgregate()));
            ui->tableProteinsMined1->setItem(k,2,item2);

            QTableWidgetItem *item3 = new QTableWidgetItem();
            item3->setText(f->getType().c_str());
            ui->tableProteinsMined1->setItem(k,3,item3);

            QTableWidgetItem *item4 = new QTableWidgetItem();
            item4->setText(f->getDescription().c_str());
            ui->tableProteinsMined1->setItem(k,4,item4);

            if(f->getPosition() != -1){
                QTableWidgetItem *item5 = new QTableWidgetItem();
                item5->setText(QString::number(f->getPosition()));
                ui->tableProteinsMined1->setItem(k,5,item5);
            }

            if(f->getBegin() != -1){
                QTableWidgetItem *item6 = new QTableWidgetItem();
                item6->setText(QString::number(f->getBegin()));
                ui->tableProteinsMined1->setItem(k,6,item6);
            }

            if(f->getEnd() != -1){
                QTableWidgetItem *item7 = new QTableWidgetItem();
                item7->setText(QString::number(f->getEnd()));
                ui->tableProteinsMined1->setItem(k,7,item7);
            }
        }
    }
    //Ajusta tamanho das colunas
    ui->tableProteinsMined1->resizeColumnsToContents();
}

void MainWindow::on_treeMinerComms_clicked(const QModelIndex &index)
{
    ui->tableProteinsMined2->clearContents();

    QString item = index.data().toString().split(' ')[0];

    if(!item.startsWith("Comm") && !item.startsWith("Conservation")){
        vector<Uniprot*> features = currentFilter->getAllResidueFeatures(item.toStdString());

        ui->tableProteinsMined2->setRowCount(features.size());
        for(unsigned int j = 0; j < features.size(); j++){
            QTableWidgetItem *itemName = new QTableWidgetItem();
            itemName->setText(features[j]->getName().c_str());
            ui->tableProteinsMined2->setItem(j,0,itemName);

            Feature *f = features[j]->getFeature(0);

            QTableWidgetItem *item1 = new QTableWidgetItem();
            if(index.data().toString().toStdString()[0] != f->getResidueColigated()[0])
                item1->setTextColor(QColor(255,0,0));
            item1->setText(f->getResidueColigated().c_str());
            ui->tableProteinsMined2->setItem(j,1,item1);

            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setText(f->getType().c_str());
            ui->tableProteinsMined2->setItem(j,2,item2);

            QTableWidgetItem *item3 = new QTableWidgetItem();
            item3->setText(f->getDescription().c_str());
            ui->tableProteinsMined2->setItem(j,3,item3);

            if(f->getPosition() != -1){
                QTableWidgetItem *item4 = new QTableWidgetItem();
                item4->setText(QString::number(f->getPosition()));
                ui->tableProteinsMined2->setItem(j,4,item4);
            }

            if(f->getBegin() != -1){
                QTableWidgetItem *item5 = new QTableWidgetItem();
                item5->setText(QString::number(f->getBegin()));
                ui->tableProteinsMined2->setItem(j,5,item5);

                QTableWidgetItem *item6 = new QTableWidgetItem();
                item6->setText(QString::number(f->getEnd()));
                ui->tableProteinsMined2->setItem(j,6,item6);
            }

            if(f->getOriginal() != ""){
                QTableWidgetItem *item7 = new QTableWidgetItem();
                item7->setText(f->getOriginal().c_str());
                ui->tableProteinsMined2->setItem(j,7,item7);

                QTableWidgetItem *item8 = new QTableWidgetItem();
                item8->setText(f->getVariation().c_str());
                ui->tableProteinsMined2->setItem(j,8,item8);
            }
        }
    }

    //Ajusta tamanho das colunas
    ui->tableProteinsMined2->resizeColumnsToContents();
}

void MainWindow::exportLookProtTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);


    currentFilter->exportLookProt(filename,0);
}

void MainWindow::exportLookProtCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);


    currentFilter->exportLookProt(filename,1);
}

void MainWindow::exportLookProtXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);


    currentFilter->exportLookProt(filename,2);
}

void MainWindow::exportLookProtHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);


    currentFilter->exportLookProt(filename,3);
}

void MainWindow::exportLookCommTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentFilter->exportLookComm(filename,0);
}

void MainWindow::exportLookCommCSV(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentFilter->exportLookComm(filename,1);
}

void MainWindow::exportLookCommXML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentFilter->exportLookComm(filename,2);
}

void MainWindow::exportLookCommHTML(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Error","You must select an filter to export");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Looking Tool to export this results.");
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentFilter->exportLookComm(filename,3);
}

void MainWindow::changeToCreateCommunity(){
    ui->listWidget->setEnabled(true);
    ui->listWidget2->setEnabled(true);

    wizard = false;
    ui->cmbComm->clear();
    ui->lstManageComms->clear();

    this->changeWizardCmds(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        return;
    }

    unsigned int nOfComms = currentFilter->getCommListSize();

    for(unsigned int j = 1; j <= nOfComms; j++)
        ui->cmbComm->addItem(QString::number(j));

    ui->stackedWidget->setCurrentIndex(STACK_MANAGE_COMMS);
}


void MainWindow::on_cmbComm_currentIndexChanged(int index)
{
    vector<string> comms = currentFilter->getCommunitie(index);

    ui->lstManageComms->clear();

    for(unsigned int j = 0; j < comms.size(); j++){
        ui->lstManageComms->addItem(comms[j].c_str());
    }
}

bool MainWindow::isaa(char c){
    if((c=='A')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')||(c=='I')||(c=='K')||(c=='L')||
       (c=='M')||(c=='N')||(c=='P')||(c=='Q')||(c=='R')||(c=='S')||(c=='T')||(c=='V')||(c=='W')||(c=='Y')||
       (c=='a')||(c=='c')||(c=='d')||(c=='e')||(c=='f')||(c=='g')||(c=='h')||(c=='i')||(c=='k')||(c=='l')||
       (c=='m')||(c=='n')||(c=='p')||(c=='q')||(c=='r')||(c=='s')||(c=='t')||(c=='v')||(c=='w')||(c=='y'))
            return (true);
    else return false;
}

bool MainWindow::isInt(string v){
    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i] != '0' && v[i] != '1' && v[i] != '2' && v[i] != '3' && v[i] != '4' && v[i] != '5' && v[i] != '6' && v[i] != '7' && v[i] != '8' && v[i] != '9' )
            return false;
    }
    return true;
}

void MainWindow::on_cmdAddResComm_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Adding residue to community"),
                                         tr("Type the new amino acid/position pair (Ex: G124, A32):"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()){
        QChar aa = text.at(0);
        string pos = text.toStdString().substr(1);

        if(!this->isaa(aa.toLatin1())){
            QMessageBox::warning(this,"Warning","Invalid pair amino acid/position.");
            return;
        }

        if(!this->isInt(pos)){
            QMessageBox::warning(this,"Warning","Invalid pair amino acid/position.");
            return;
        }

    }

    int nc = ui->cmbComm->currentIndex();

    currentFilter->addItemToCommunity(text.toStdString(),nc);

    //Atualizar campo
    vector<string> comms = currentFilter->getCommunitie(nc);

    ui->lstManageComms->clear();

    for(unsigned int j = 0; j < comms.size(); j++){
        ui->lstManageComms->addItem(comms[j].c_str());
    }
}

void MainWindow::on_cmdDelResComm_clicked()
{
    if(ui->lstManageComms->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must selec a residue to remove.");
        return;
    }

    int residueIndex = ui->lstManageComms->currentIndex().row();
    int nc = ui->cmbComm->currentIndex();

    currentFilter->removeItemOfCommunity(nc,residueIndex);

    //Atualizar campo
    vector<string> comms = currentFilter->getCommunitie(nc);

    ui->lstManageComms->clear();

    for(unsigned int j = 0; j < comms.size(); j++){
        ui->lstManageComms->addItem(comms[j].c_str());
    }
}

void MainWindow::on_cmdNewComm_clicked()
{
    vector<string> newComm;
    currentFilter->addCommunity(newComm);

    //Atualizar campos
    int nOfComms = currentFilter->getCommListSize();

    ui->cmbComm->addItem(QString::number(nOfComms));

    ui->cmbComm->setCurrentIndex(nOfComms-1);
}

void MainWindow::changeToListOfSequences(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        return;
    }

    //Resetar campos de resultado
    ui->lstProteinsFiltered->clear();
    ui->txtSequence->clear();

    this->listSequences();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_SEQLIST);
}

void MainWindow::changeToConservationFrequence(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        return;
    }

    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation method.");
        return;
    }

    //Resetar campos de resultado
    ui->tableFreq->clearContents();

    this->tableFreq();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CONSFREQ);
}

void MainWindow::changeToConservationPercentage(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Error","You must select an alignment");
        return;
    }

    if(currentFilter->getConsFreqPercSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation method.");
        return;
    }

    //Resetar campos de resultado
    ui->tableFreqPerc->clearContents();

    this->tableFreqPerc();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_FREQPERC);
}

void MainWindow::changeToConservedResidues(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","You must select some reference sequences.");
        return;
    }

    //Resetar campos de resultado
    ui->tableConsRes->clear();

    this->showConservedResidues();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CONSRES);
}

void MainWindow::changetoCorrelationList(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getCorrGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    //Resetar campos de resultado
    ui->treeCorrelation->clear();

    this->correlationList();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRLIST);
}

void MainWindow::changeToCorrelationGraph(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getCorrGraphSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    createCorrelationJSON();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRGRAPH);
}

void MainWindow::changeToCommunitiesGraphs(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    this->communitiesGraphs();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_COMMGRAPH);
}

void MainWindow::changeToCorrelationBetweenComms(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getDeltasSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    this->corrBetweenComms();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_DELTAGRAPH);

}

void MainWindow::changeToPDBVisualization(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getConsPDBPath() == ""){
        QMessageBox::warning(this,"Warning","You must run conservation method and send a PDB file.");
        return;
    }

    this->consVisualization();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CONSPDB);
}

void MainWindow::changeToPDBVisualization2(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getCommPDBPath() == ""){
        QMessageBox::warning(this,"Warning","You must run correlation method and send a PDB file.");
        return;
    }

    this->commVisualization();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_COMMPDB);
}

void MainWindow::changeToAlphabetReduction(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    emit ui->cmbAlphabetList->currentIndexChanged(0);
    ui->stackedWidget->setCurrentIndex(STACK_ALPHABET);
}

void MainWindow::changeToCommunitiesList(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    //Resetar campos de resultado
    ui->treeCorrelationComm->clear();

    this->communitiesList();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_COMMLIST);
}

void MainWindow::changeToCorrelationInPerc(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    //Resetar campos de resultado
    ui->tableComm1->clear();

    this->corrTable1();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRPERC);
}

void MainWindow::changeToCorrelationInLogP(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    //Resetar campos de resultado
    ui->tableComm2->clear();

    this->corrTable2();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRLOG);
}

void MainWindow::changeToAdherenceMatrix(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        return;
    }

    //Resetar campos de resultado
    ui->tableAdherence->clear();

    this->adh();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_ADHERENCE);
}

void MainWindow::changeToResiduesOfCommunities(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getRefSeqsSize() == 0 || currentFilter->getNumOfUtilComms() == 0){
        QMessageBox::warning(this,"Warning","You must have some reference sequences.");
        return;
    }

    //Resetar campos de resultado
    ui->tableResiduesComm->clear();

    this->showResiduesComm();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_RESCOMM);
}

void MainWindow::changeToULGroupedByProteins(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You must run Uniprot Looking Tool.");
        return;
    }

    //Resetar campos de resultado
    ui->lstProteinsMined->clear();
    ui->tableProteinsMined1->clearContents();

    this->showUniprotGroupByProteins();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_UNIPROT_PROTEINS);
}

void MainWindow::changeToULGroupedByComms(){
    //ui->cmdNextResult->setVisible(false);
    //ui->cmdBackResult->setVisible(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    if(currentFilter->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You must run Uniprot Looking Tool.");
        return;
    }

    //Resetar campos de resultado
    ui->treeMinerComms->clear();
    ui->tableProteinsMined2->clearContents();

    this->showUniprotGroupByComms();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_UNIPROT_COMMS);
}

void MainWindow::changeToFullAlignment(){
    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        return;
    }

    ui->tableFullAlignment->clear();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_FULLALIGN);

    this->showFullAlignment(ui->cmbAlphabetColor->currentIndex(), ui->cmbViewColumns->currentIndex());
}

void MainWindow::on_cmdAddFileRefSeq_clicked()
{
    ui->cmdAddFileRefSeq->setEnabled(false);

    int total = 0;
    int selecteds = 0;

    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Export File"),"",QObject::tr("TEXT Files (*.txt)"));

    if(filename == NULL){
        ui->cmdAddFileRefSeq->setEnabled(true);
        return;
    }

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Warning","File not found.");
        ui->cmdAddFileRefSeq->setEnabled(true);
        return;
    }

    QTextStream in(&file);

    QString prot = in.readLine();
    while (!prot.isNull())
    {
        total++;
        //printf("%s\n",prot.toStdString().c_str());

        for(int i = 0; i < ui->lstRefSeqs->count(); i++){
            if(prot == ui->lstRefSeqs->item(i)->text()){
                delete ui->lstRefSeqs->item(i);
                ui->lstRefSeqSelected->addItem(prot);
                selecteds++;
                break;
            }
        }
        prot = in.readLine();
    }

    string msge = QString::number(selecteds).toStdString() + " of " + QString::number(total).toStdString() + " sequences have been found and selected.";
    QMessageBox::information(this,"Upload Reference Sequences",msge.c_str());

    file.close();

    ui->cmdAddFileRefSeq->setEnabled(true);
}

void MainWindow::on_cmdAddAllRefSeq_clicked()
{
    ui->cmdAddAllRefSeq->setEnabled(false);
    for(int i = 0; i < ui->lstRefSeqs->count(); i++){
        QString prot = ui->lstRefSeqs->item(i)->text();
        ui->lstRefSeqSelected->addItem(prot);
    }
    ui->lstRefSeqs->clear();
    ui->cmdAddAllRefSeq->setEnabled(true);
}

void MainWindow::on_cmdRemoveAllRefSeq_clicked()
{
    ui->cmdRemoveAllRefSeq->setEnabled(false);
    for(int i = 0; i < ui->lstRefSeqSelected->count(); i++){
        QString prot = ui->lstRefSeqSelected->item(i)->text();
        ui->lstRefSeqs->addItem(prot);
    }
    ui->lstRefSeqSelected->clear();
    ui->cmdRemoveAllRefSeq->setEnabled(true);
}

void MainWindow::on_cmdAddOneRefSeq_clicked()
{
    ui->cmdAddOneRefSeq->setEnabled(false);

    if(ui->lstRefSeqs->currentItem() == NULL){
        ui->cmdAddOneRefSeq->setEnabled(true);
        return;
    }

    QString item = ui->lstRefSeqs->currentItem()->text();
    delete ui->lstRefSeqs->currentItem();
    ui->lstRefSeqSelected->addItem(item);
    ui->cmdAddOneRefSeq->setEnabled(true);
}

void MainWindow::on_cmdRemoveOneRefSeq_clicked()
{
    ui->cmdRemoveOneRefSeq->setEnabled(false);

    if(ui->lstRefSeqSelected->currentItem() == NULL){
        ui->cmdRemoveOneRefSeq->setEnabled(true);
        return;
    }

    QString item = ui->lstRefSeqSelected->currentItem()->text();
    delete ui->lstRefSeqSelected->currentItem();
    ui->lstRefSeqs->addItem(item);
    ui->cmdRemoveOneRefSeq->setEnabled(true);
}

void MainWindow::on_cmdSaveRefSeqs_clicked()
{
    ui->cmdSaveRefSeqs->setEnabled(false);

    //Validação
    if(!ui->listWidget->currentItem()){
        QMessageBox::warning(this,"Warning","You must select an alignment");
        ui->cmdSaveRefSeqs->setEnabled(true);
        return;
    }

    currentFilter->clearRefSeq();

    for(int j = 0; j < ui->lstRefSeqSelected->count(); j++){
        //printf("5891:Refseq - %s\n",ui->lstRefSeqSelected->item(j)->text().toStdString().c_str());
        currentFilter->addRefSeq(ui->lstRefSeqSelected->item(j)->text().toStdString());
    }
    QMessageBox::information(this,"Reference sequences","The reference sequences are stored.");

    ui->cmdSaveRefSeqs->setEnabled(true);
}

void MainWindow::on_cmdUpdateComms_clicked()
{
    //Chamar Output
    this->output(1,currentFilter->getRefSeqOffset());

    QMessageBox::information(this,"Update Communities","The communtities have been updated.");
}

void MainWindow::on_txtMinssFraction_editingFinished()
{
    string minssFraction = ui->txtMinssFraction->text().toStdString();
    string newMinss = "";

    for(unsigned int i = 0; i < minssFraction.size(); i++){
        if(minssFraction[i] == ',') newMinss += '.';
        else newMinss += minssFraction[i];
    }

    ui->txtMinssFraction->setText(newMinss.c_str());
}

void MainWindow::on_txtGraphCutoff_editingFinished()
{
    string cutoff = ui->txtGraphCutoff->text().toStdString();
    string newCutoff = "";

    for(unsigned int i = 0; i < cutoff.size(); i++){
        if(cutoff[i] == ',') newCutoff += '.';
        else newCutoff += cutoff[i];
    }

    ui->txtGraphCutoff->setText(newCutoff.c_str());
}

void MainWindow::setLibPath(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(libpath.c_str());
    dialog.setOption(QFileDialog::ShowDirsOnly);

    string temp = dialog.getExistingDirectory().toStdString() + "/";

    if(temp == "/") return;

    libpath = temp;

    QFile file(CONFIG);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    out << libpath.c_str();

    file.close();

    string msg = "The libraries directory is set.\n" + libpath;
    QMessageBox::information(this,"Setting lib path",msg.c_str());
}

void MainWindow::on_chkApplyTaxonFilter_clicked(bool checked)
{
    ui->label_78->setEnabled(checked);
    ui->txtTaxons->setEnabled(checked);

    if(checked || ui->chkApplyMaxId->isChecked() || ui->chkApplyMinId->isChecked() || ui->chkApplyMinCover->isChecked()){
        ui->cmdApplyFilter->setChecked(true);
    }else{
        ui->cmdApplyFilter->setChecked(false);
    }
}


void MainWindow::on_chkApplyMinCover_clicked(bool checked)
{
    ui->label_11->setEnabled(checked);
    ui->txtMinCover->setEnabled(checked);

    if(checked || ui->chkApplyMinId->isChecked() || ui->chkApplyMaxId->isChecked() || ui->chkApplyTaxonFilter->isChecked()){
        ui->cmdApplyFilter->setEnabled(true);
    }else{
        ui->cmdApplyFilter->setEnabled(false);
    }
}

void MainWindow::on_chkApplyMinId_clicked(bool checked)
{
    ui->label_12->setEnabled(checked);
    ui->txtMinId->setEnabled(checked);

    if(checked || ui->chkApplyMinCover->isChecked() || ui->chkApplyMaxId->isChecked() || ui->chkApplyTaxonFilter->isChecked()){
        ui->cmdApplyFilter->setEnabled(true);
    }else{
        ui->cmdApplyFilter->setEnabled(false);
    }
}


void MainWindow::on_chkApplyMaxId_clicked(bool checked)
{
    ui->label_13->setEnabled(checked);
    ui->txtMaxId->setEnabled(checked);

    if(checked || ui->chkApplyMinCover->isChecked() || ui->chkApplyMinId->isChecked() || ui->chkApplyTaxonFilter->isChecked()){
        ui->cmdApplyFilter->setEnabled(true);
    }else{
        ui->cmdApplyFilter->setEnabled(false);
    }
}

void MainWindow::on_cmbAlphabetList_currentIndexChanged(int index)
{
    switch(index){
    case 0:
    {
        ui->lblAlphabetName->setText("Name: Complete Alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nNone");
        break;
    }
    case 1:
    {
        ui->lblAlphabetName->setText("Name: Two Letters Alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nAGTSNQDEHRKP => P: Hydrophilic\nCMFILVWY =>H: Hydrophobic");
        break;
    }
    case 2:
    {
        ui->lblAlphabetName->setText("Name: Five letters alphabet: Chemical / structural properties");
        ui->lblAlphabetChanges->setText("Changes:\nIVL   => I: Aliphatic\nFYWH  => F: Aromatic\nKRDE  => K: Charged\nGACS  => G: Tiny\nTMQNP => T: Diverse");
        break;
    }
    case 3:
    {
        ui->lblAlphabetName->setText("Name: Six letters alphabet: Chemical / structural properties #2");
        ui->lblAlphabetChanges->setText("Changes:\nIVL   =>I: Aliphatic\nFYWH  => F: Aromatic\nKR    => K: Pos. charged\nDE    => D: Neg. charged\nGACS  => G: Tiny\nTMQNP => T: Diverse");
        break;
    }
    case 4:
    {
        ui->lblAlphabetName->setText("Name: 3 IMGT amino acid hydropathy alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nIVLFCMAW => I: Hydrophilic\nGTSYPM => G: Neutral\nDNEQKR =>D: Hydrophobic");
        break;
    }
    case 5:
    {
        ui->lblAlphabetName->setText("Name: 5 IMGT amino acid volume alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nGAS   => G: 60-90\nCDPNT => C: 108-117\nEVQH  => E: 138-154\nMILKR => M: 162-174\nFYW   => F: 189-228");
        break;
    }
    case 6:
    {
        ui->lblAlphabetName->setText("Name: 11 IMGT amino acid chemical characteristics alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nAVIL => A: Aliphatic\nF    => F: Phenylalanine\nCM   => C: Sulfur\nG    => G: Glycine\nST   => S: Hydroxyl\nW    => W: Tryptophan\nY    => Y: Tyrosine\nP    => P: Proline\nDE   => D: Acidic\nNQ   => N: Amide\nHKR  => H: Basic");
        break;
    }
    case 7:
    {
        ui->lblAlphabetName->setText("Name: Murphy et al, 2000; 15 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nL: Large hydrophobic\nC    => C\nA    => A\nG    => G\nS    => S\nT    => T\nP    => P\nFY   => F: Hydrophobic/aromatic sidechains\nW    => W\nE    => E\nD    => D\nN    => N\nQ    => Q\nKR   => K: Long-chain positively charged\nH    => H");
        break;
    }
    case 8:
    {
        ui->lblAlphabetName->setText("Name: Murphy et al, 2000; 10 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nLVIM => L: Large hydrophobic\nC    => C\nA    => A\nG    => G\nST   => S: Polar\nP    => P\nFYW  => F:Hydrophobic/aromatic sidechains\nEDNQ => E: Charged / polar\nKR   => K: Long-chain positively charged\nH    =>H");
        break;
    }
    case 9:
    {
        ui->lblAlphabetName->setText("Name: Murphy et al, 2000; 8 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nLVIMC => L: Hydrophobic\nAG    => A\nST    => S: Polar\nP     => P\nFYW   => F: Hydrophobic/aromatic sidechains\nEDNQ  => E\nKR    => K: Long-chain positively charged\nH     => H");
        break;
    }
    case 10:
    {
        ui->lblAlphabetName->setText("Name: Murphy et al, 2000; 4 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nLVIMC   => L: Hydrophobic\nAGSTP   => A\nFYW     => F: Hydrophobic/aromatic sidechains\nEDNQKRH =>E");
        break;
    }
    case 11:
    {
        ui->lblAlphabetName->setText("Name: Murphy et al, 2000; 2 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nLVIMCAGSTPFYW => P: Hydrophobic\nEDNQKRH       => E: Hydrophilic");
        break;
    }
    case 12:
    {
        ui->lblAlphabetName->setText("Name: Wang & Wang, 1999; 5 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCMFILVWY => I\nATH      => A\nGP       => G\nDE       => E\nSNQRK    => K");
        break;
    }
    case 13:
    {
        ui->lblAlphabetName->setText("Name: Wang & Wang, 1999; 5 letters variant alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCMFI => I\nLVWY => L\nATGS => A\nNQDE => E\nHPRK => K");
        break;
    }
    case 14:
    {
        ui->lblAlphabetName->setText("Name: Wang & Wang, 1999; 3 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCMFILVWY => I\nATHGPR   => A\nDESNQK   => E");
        break;
    }
    case 15:
    {
        ui->lblAlphabetName->setText("Name: Wang & Wang, 1999; 2 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCMFILVWY     => I\nATHGPRDESNQK => A");
        break;
    }
    case 16:
    {
        ui->lblAlphabetName->setText("Name: Li et al, 2003; 10 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nC   => C\nFYW => Y\nML  => L\nIV  => V\nG   => G\nP   => P\nATS => S\nNH  => N\nQED => E\nRK  => K");
        break;
    }
    case 17:
    {
        ui->lblAlphabetName->setText("Name: Li et al, 2003; 5 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCFYW    => Y\nMLIV    => I\nG       => G\nPATS    => S\nNHQEDRK => E");
        break;
    }
    case 18:
    {
        ui->lblAlphabetName->setText("Name: Li et al, 2003; 4 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCFYW    => Y\nMLIV    => I\nGPATS   => S\nNHQEDRK => E");
        break;
    }
    case 19:
    {
        ui->lblAlphabetName->setText("Name: Li et al, 2003; 3 letters alphabet");
        ui->lblAlphabetChanges->setText("Changes:\nCFYWMLIV => I\nGPATS    => S\nNHQEDRK  => E");
        break;
    }
    }
}

void MainWindow::on_radioAlphabetCurrent_clicked(bool checked)
{
    if(checked){
        ui->radioAlphabetCurrent->setChecked(true);
        ui->radioAlphabetNew->setChecked(false);
    }
}

void MainWindow::on_radioAlphabetNew_clicked(bool checked)
{
    if(checked){
        ui->radioAlphabetCurrent->setChecked(false);
        ui->radioAlphabetNew->setChecked(true);
    }
}

void MainWindow::on_cmdApplyAlphabetReduction_clicked()
{
    ui->cmdApplyAlphabetReduction->setEnabled(false);

    vector<string> oldChars;
    vector<char> newChars;
    int alphabet = ui->cmbAlphabetList->currentIndex();
    bool newFilter;
    string type;
    string alignname = "";

    if(ui->radioAlphabetNew->isChecked()) newFilter = true;
    else newFilter = false;


    //Validation
    if(currentFilter->getAlphabet() != "T20"){
        QMessageBox::warning(this,"Warning","You cannot reduce an alphabet from a already reduced alignment. Please choose a T20 filter");
        ui->cmdApplyAlphabetReduction->setEnabled(true);
        return;
    }

    if(newFilter){
        bool ok;
        QString text = QInputDialog::getText(this, tr("Name the new alignment"),
                                             tr("Alignment name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty()){
            for(unsigned int i = 0; i < ui->listWidget2->count(); i++){
                if(ui->listWidget2->item(i)->text() == text){
                    QMessageBox::warning(this,"Warning","There's already an alignment with that name.");
                    ui->cmdApplyAlphabetReduction->setEnabled(true);
                    return;
                }
            }

            alignname = text.toStdString();
        }else if(ok && text.isEmpty()){
            QMessageBox::warning(this,"Warning","You must set a name for the new alignment.");
            ui->cmdApplyAlphabetReduction->setEnabled(true);
            return;
        }
    }

    switch(alphabet){
    case 0:
    {
        //CUSTOM
        break;
    }
    case 1:
    {
        type = "T2";
        oldChars.push_back("AGTSNQDEHRKP");
        newChars.push_back('P');
        oldChars.push_back("CMFILVWY");
        newChars.push_back('Y');

        break;
    }
    case 2:
    {
        type = "T5";
        oldChars.push_back("IVL");
        newChars.push_back('I');
        oldChars.push_back("FYWH");
        newChars.push_back('F');
        oldChars.push_back("KRDE");
        newChars.push_back('K');
        oldChars.push_back("GACS");
        newChars.push_back('G');
        oldChars.push_back("TMQNP");
        newChars.push_back('T');

        break;
    }
    case 3:
    {
        type = "T6";
        oldChars.push_back("IVL");
        newChars.push_back('I');
        oldChars.push_back("FYWH");
        newChars.push_back('F');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("DE");
        newChars.push_back('D');
        oldChars.push_back("GACS");
        newChars.push_back('G');
        oldChars.push_back("TMQNP");
        newChars.push_back('T');

        break;
    }
    case 4:
    {
        type = "3IMG";
        oldChars.push_back("IVLFCMAW");
        newChars.push_back('I');
        oldChars.push_back("GTSYPM");
        newChars.push_back('G');
        oldChars.push_back("DNEQKR");
        newChars.push_back('D');

        break;
    }
    case 5:
    {
        type = "5IMG";
        oldChars.push_back("GAS");
        newChars.push_back('G');
        oldChars.push_back("CDPNT");
        newChars.push_back('C');
        oldChars.push_back("EVQH");
        newChars.push_back('E');
        oldChars.push_back("MILKR");
        newChars.push_back('M');
        oldChars.push_back("FYW");
        newChars.push_back('F');

        break;
    }
    case 6:
    {
        type = "11IMG";
        oldChars.push_back("AVIL");
        newChars.push_back('A');
        oldChars.push_back("F");
        newChars.push_back('F');
        oldChars.push_back("CM");
        newChars.push_back('C');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("ST");
        newChars.push_back('S');
        oldChars.push_back("W");
        newChars.push_back('W');
        oldChars.push_back("Y");
        newChars.push_back('Y');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("DE");
        newChars.push_back('D');
        oldChars.push_back("NQ");
        newChars.push_back('N');
        oldChars.push_back("HKR");
        newChars.push_back('H');
        break;
    }
    case 7:
    {
        type = "Murphy15";
        oldChars.push_back("LVIM");
        newChars.push_back('L');
        oldChars.push_back("C");
        newChars.push_back('C');
        oldChars.push_back("A");
        newChars.push_back('A');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("S");
        newChars.push_back('S');
        oldChars.push_back("T");
        newChars.push_back('T');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("FY");
        newChars.push_back('F');
        oldChars.push_back("W");
        newChars.push_back('W');
        oldChars.push_back("E");
        newChars.push_back('E');
        oldChars.push_back("D");
        newChars.push_back('D');
        oldChars.push_back("N");
        newChars.push_back('N');
        oldChars.push_back("Q");
        newChars.push_back('Q');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("H");
        newChars.push_back('H');

        break;
    }
    case 8:
    {
        type = "Murphy10";
        oldChars.push_back("LVIM");
        newChars.push_back('L');
        oldChars.push_back("C");
        newChars.push_back('C');
        oldChars.push_back("A");
        newChars.push_back('A');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("ST");
        newChars.push_back('S');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("FYW");
        newChars.push_back('F');
        oldChars.push_back("EDNQ");
        newChars.push_back('E');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("H");
        newChars.push_back('H');

        break;
    }
    case 9:
    {
        type = "Murphy8";
        oldChars.push_back("LVIMC");
        newChars.push_back('L');
        oldChars.push_back("AG");
        newChars.push_back('A');
        oldChars.push_back("ST");
        newChars.push_back('S');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("FYW");
        newChars.push_back('F');
        oldChars.push_back("EDNQ");
        newChars.push_back('E');
        oldChars.push_back("KR");
        newChars.push_back('K');
        oldChars.push_back("H");
        newChars.push_back('H');

        break;
    }
    case 10:
    {
        type = "Murphy4";
        oldChars.push_back("LVIMC");
        newChars.push_back('L');
        oldChars.push_back("AGSTP");
        newChars.push_back('A');
        oldChars.push_back("FYW");
        newChars.push_back('F');
        oldChars.push_back("EDNQKRH");
        newChars.push_back('E');

        break;
    }
    case 11:
    {
        type = "Murphy2";
        oldChars.push_back("LVIMCAGSTPFYW");
        newChars.push_back('P');
        oldChars.push_back("EDNQKRH");
        newChars.push_back('E');

        break;
    }
    case 12:
    {
        type = "Wang5";
        oldChars.push_back("CMFILVWY");
        newChars.push_back('I');
        oldChars.push_back("ATH");
        newChars.push_back('A');
        oldChars.push_back("GP");
        newChars.push_back('G');
        oldChars.push_back("DE");
        newChars.push_back('E');
        oldChars.push_back("SNQRK");
        newChars.push_back('K');

        break;
    }
    case 13:
    {
        type = "Wang5v";
        oldChars.push_back("CMFI");
        newChars.push_back('I');
        oldChars.push_back("LVWY");
        newChars.push_back('L');
        oldChars.push_back("ATGS");
        newChars.push_back('A');
        oldChars.push_back("NQDE");
        newChars.push_back('E');
        oldChars.push_back("HPRK");
        newChars.push_back('K');

        break;
    }
    case 14:
    {
        type = "Wang3";
        oldChars.push_back("CMFILVWY");
        newChars.push_back('I');
        oldChars.push_back("ATHGPR");
        newChars.push_back('A');
        oldChars.push_back("DESNQK");
        newChars.push_back('E');

        break;
    }
    case 15:
    {
        type = "Wang2";
        oldChars.push_back("CMFILVWY");
        newChars.push_back('I');
        oldChars.push_back("ATHGPRDESNQK");
        newChars.push_back('A');

        break;
    }
    case 16:
    {
        type = "Li10";
        oldChars.push_back("C");
        newChars.push_back('C');
        oldChars.push_back("FYW");
        newChars.push_back('Y');
        oldChars.push_back("ML");
        newChars.push_back('L');
        oldChars.push_back("IV");
        newChars.push_back('V');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("P");
        newChars.push_back('P');
        oldChars.push_back("ATS");
        newChars.push_back('S');
        oldChars.push_back("NH");
        newChars.push_back('N');
        oldChars.push_back("QED");
        newChars.push_back('E');
        oldChars.push_back("RK");
        newChars.push_back('K');

        break;
    }
    case 17:
    {
        type = "Li5";
        oldChars.push_back("CFYW");
        newChars.push_back('Y');
        oldChars.push_back("MLIV");
        newChars.push_back('I');
        oldChars.push_back("G");
        newChars.push_back('G');
        oldChars.push_back("PATS");
        newChars.push_back('S');
        oldChars.push_back("NHQEDRK");
        newChars.push_back('N');

        break;
    }
    case 18:
    {
        type = "Li4";
        oldChars.push_back("CFYW");
        newChars.push_back('Y');
        oldChars.push_back("MLIV");
        newChars.push_back('I');
        oldChars.push_back("GPATS");
        newChars.push_back('S');
        oldChars.push_back("NHQEDRK");
        newChars.push_back('E');

        break;
    }
    case 19:
    {
        type = "Li3";
        oldChars.push_back("CFYWMLIV");
        newChars.push_back('I');
        oldChars.push_back("GPATS");
        newChars.push_back('S');
        oldChars.push_back("NHQEDRK");
        newChars.push_back('E');

        break;
    }
    }

    if(newFilter){
        Filter* filter = new Filter();
        filter->setName(alignname);
        filter->setAlphabet(type);
        if(currentFilter->getType() == 9) filter->setType(8);
        else filter->setType(currentFilter->getType());
        filter->setMaxId(currentFilter->getMaxId());
        filter->setMinId(currentFilter->getMinId());
        filter->setMinOcc(currentFilter->getMinOcc());
        filter->setRefSeq(currentFilter->getRefSeq());
        filter->setTaxon(currentFilter->getTaxon());
        filter->addSequences(currentAlign->sequencenames,currentAlign->sequences);

        filter->applyAlphabetReduction(oldChars,newChars);

        currentAlign->addFilter(filter);

        ui->listWidget2->addItem(alignname.c_str());
        ui->listWidget2->setCurrentRow(ui->listWidget2->count()-1);
        emit ui->listWidget2->activated(ui->listWidget2->currentIndex());
    }else{
        currentFilter->applyAlphabetReduction(oldChars,newChars);
        currentFilter->setAlphabet(type);
        currentFilter->addSequences(currentAlign->sequencenames,currentAlign->sequences);
    }

    string msg = "The sequence alphabet was reduced using the " + type + " method.";
    QMessageBox::information(this,"Alhabet Reduced",msg.c_str());

    ui->cmdApplyAlphabetReduction->setEnabled(true);
}

void MainWindow::on_cmbRefSeq_2_activated(const QString &arg1)
{
    //Atualizar Recommended PDBS
    ui->lstRecomendedPDBs->clear();

    for(unsigned int i = 0; i < pdbs.size(); i++){
        Pdb* pdb = pdbs[i];

        if(pdb->getRefseq() == arg1.toStdString())
            ui->lstRecomendedPDBs->addItem(pdb->getId().c_str());
    }
}

void MainWindow::on_lstRecomendedPDBs_itemActivated(QListWidgetItem *item)
{
    string strpdb = item->text().toStdString();
    ui->txtPDBName->setText(strpdb.c_str());

    for(unsigned int i = 0; i < pdbs.size(); i++){
        Pdb* pdb = pdbs[i];
        if(pdb->getId() == strpdb){
            string chain = std::string(1,pdb->getRefseq_chain());
            ui->txtChain->setText(QString::fromStdString(chain));
            break;
        }
    }
}

void MainWindow::on_chkRemoveContactResidues_clicked(bool checked)
{

    if(checked){
        ui->txtAtomDistance->setEnabled(true);
        ui->txtPDBName_2->setEnabled(true);
        ui->txtChain_2->setEnabled(true);
        ui->lstPDBsLoaded_2->setEnabled(true);
    }else{
        ui->txtAtomDistance->setEnabled(false);
        if(ui->chkCommVisualization->isChecked()){
            ui->txtPDBName_2->setEnabled(true);
            ui->txtChain_2->setEnabled(true);
            ui->lstPDBsLoaded_2->setEnabled(true);
        }else{
            ui->txtPDBName_2->setEnabled(false);
            ui->txtChain_2->setEnabled(false);
            ui->lstPDBsLoaded_2->setEnabled(false);
        }
    }
}

void MainWindow::on_cmbRefSeq_3_activated(const QString &arg1)
{
    //Atualizar Recommended PDBS
    ui->lstPDBsLoaded_2->clear();

    for(unsigned int i = 0; i < pdbs.size(); i++){
        Pdb* pdb = pdbs[i];

        if(pdb->getRefseq() == arg1.toStdString())
            ui->lstPDBsLoaded_2->addItem(pdb->getId().c_str());
    }
}

void MainWindow::on_lstPDBsLoaded_2_itemActivated(QListWidgetItem *item)
{
    string strpdb = item->text().toStdString();
    ui->txtPDBName_2->setText(strpdb.c_str());

    for(unsigned int i = 0; i < pdbs.size(); i++){
        Pdb* pdb = pdbs[i];
        if(pdb->getId() == strpdb){
            string chain = std::string(1,pdb->getRefseq_chain());
            ui->txtChain_2->setText(QString::fromStdString(chain));
            break;
        }
    }
}

void MainWindow::on_cmbRefSeq_4_activated(const QString &arg1)
{
    //Atualizar Recommended PDBS
    ui->lstRecommendedPDBs->clear();

    vector<string> pdbs = currentAlign->getRecommendsPDBs(arg1.toStdString());

    for(unsigned int j = 0; j < pdbs.size(); j++){
        ui->lstRecommendedPDBs->addItem(pdbs[j].c_str());
    }

    int index = ui->cmbRefSeq_4->currentIndex();
    ui->cmbRefSeq_2->setCurrentIndex(index);
    emit ui->cmbRefSeq_2->activated(index);
}

void MainWindow::on_lstRecommendedPDBs_itemActivated(QListWidgetItem *item)
{
    string pdbchain = item->text().toStdString();
    string pdb = split(pdbchain,' ')[0];
    char chain = pdbchain[pdbchain.size()-2];
    string strchain = std::string(1,chain);

    ui->txtChainPDB->setText(strchain.c_str());
    ui->txtPdbId->setText(pdb.c_str());

    string interval = currentAlign->getPDBInterval(pdb);

    vector<string> intervals = split(interval,'-');

    ui->txtPDBFrom->setValue(stoi(intervals[0].c_str()));
    ui->txtPDBTo->setValue(stoi(intervals[1].c_str()));
}

void MainWindow::on_cmdPDBFile_clicked()
{
    ui->cmdPDBFile->setEnabled(false);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("TEXT Files (*.txt *.pdb)"));
    ui->txtFilePathPDB->setText(fileName);
    ui->txtPdbId->clear();

    ui->cmdPDBFile->setEnabled(true);
}

void MainWindow::on_cmdPDBFetch_clicked()
{
    ui->cmdPDBFetch->setEnabled(false);

    //Validação
    if(ui->txtPdbId->text() == ""){
        QMessageBox::warning(this,"Error","You must fill PDB name");
        ui->cmdPDBFetch->setEnabled(true);
        return;
    }

    //Montar URL
    QString url = "http://files.rcsb.org/view/" + ui->txtPdbId->text() + ".pdb";

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
        ui->cmdPDBFetch->setEnabled(true);
        return ;
    }else{
        if(ui->chkDownloadPDB->isChecked()){
            QString finalName = ui->txtPdbId->text() + ".pdb";
            QString filename = QFileDialog::getSaveFileName(this,tr("Export File"),finalName,tr("TEXT Files (*.pdb)"));

            if(filename == ""){
                ui->cmdPDBFetch->setEnabled(true);
                return;
            }

            vector<string> tempFN = split(filename.toStdString(),'.');
            if(tempFN[tempFN.size()-1] != "pdb" && tempFN[tempFN.size()-1] != "PDB")
                filename += ".pdb";

            //Salva em arquivo
            QFile f(filename);
            if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
                ui->cmdPDBFetch->setEnabled(true);
                return;
            }

            QTextStream out(&f);
            out << pdb;
            f.close();

            ui->txtFilePathPDB->setText(filename);
        }else{
            ui->txtFilePathPDB->clear();
        }

        currentPDBContent = pdb.toStdString();
        this->pdbweb = url.toStdString();
    }

    QMessageBox::StandardButton mbox;
    mbox = QMessageBox::question(this, "Load 3D Structure", "Your PDB file has been found on the rcsb.org. Do you want to load it now?",
                                QMessageBox::Yes|QMessageBox::No);
    if (mbox == QMessageBox::Yes) {
        ui->cmdLoadPDB->clicked();
    }

    ui->cmdPDBFetch->setEnabled(true);
}

void MainWindow::on_cmdLoadPDB_clicked()
{
    ui->cmdLoadPDB->setEnabled(false);
    Pdb* pdb = NULL;
    int intervalFrom = ui->txtPDBFrom->value();
    int intervalTo = ui->txtPDBTo->value();
    string refseq = ui->cmbRefSeq_4->currentText().toStdString();

    //Validação
    if(refseq == " "){
        QMessageBox::warning(this,"Warning","You must set a reference sequence for this structure.");
        ui->cmdLoadPDB->setEnabled(true);
        return;
    }

    if(intervalFrom >= intervalTo){
        QMessageBox::warning(this,"Warning","The second value of intervals must be higher than first.");
        ui->cmdLoadPDB->setEnabled(true);
        return;
    }

    if(ui->txtPdbId->text() != ""){
        //Já está na memoria
        if(currentPDBContent == ""){
            QMessageBox::warning(this,"Warning","You must fetch your PDB before load.");
            ui->cmdLoadPDB->setEnabled(true);
            return;
        }
        pdb = new Pdb(currentPDBContent);
    }else if(ui->txtFilePathPDB->text() != ""){
        QString filepath = ui->txtFilePathPDB->text();
        pdb = new Pdb(filepath);
    }

    if(pdb != NULL){
        string pdbname = pdb->getId();
        char chain = ui->txtChainPDB->text().toStdString()[0];

        pdb->setRefseq(refseq);
        pdb->setRefseq_chain(chain);
        pdb->setIntervals(intervalFrom,intervalTo);
        //pdb->setResiduesSeqNumber(chain);


        //Verify if pdb and sequence align
        string currseq = currentFilter->getNoGAPSequence(ui->cmbRefSeq_3->currentIndex()-1);
        string pdbseq = pdb->getPDBSequence(chain);
        int score = pdb->setResiduesSeqNumber(currseq,chain);

        ui->lstPDBsInMemory->addItem(pdbname.c_str());

        pdbs.push_back(pdb);

        //Emit
        emit ui->cmbRefSeq_2->activated(ui->cmbRefSeq_2->currentText());
        emit ui->cmbRefSeq_3->activated(ui->cmbRefSeq_3->currentText());

        string msg = "The structure file has been load and aligned with the reference sequence scoring " + to_string(score) + "/" + to_string(currseq.length() + pdbseq.length()) + ".";

        QMessageBox::information(this,"Structure loaded",msg.c_str());
    }

    ui->cmdLoadPDB->setEnabled(true);
}

void MainWindow::on_chkGenerateConsPDB_clicked(bool checked)
{
    ui->txtPDBName->setEnabled(checked);
    ui->txtChain->setEnabled(checked);
    ui->lstRecomendedPDBs->setEnabled(checked);
}

void MainWindow::on_chkCommVisualization_clicked(bool checked)
{
    if(checked){
        ui->txtPDBName_2->setEnabled(true);
        ui->txtChain_2->setEnabled(true);
        ui->lstPDBsLoaded_2->setEnabled(true);
        if(ui->chkRemoveContactResidues->isChecked())
            ui->txtAtomDistance->setEnabled(true);
        else
            ui->txtAtomDistance->setEnabled(false);
    }else{
        if(ui->chkRemoveContactResidues->isChecked()){
            ui->txtPDBName_2->setEnabled(true);
            ui->txtChain_2->setEnabled(true);
            ui->lstPDBsLoaded_2->setEnabled(true);
            ui->txtAtomDistance->setEnabled(true);
        }else{
            ui->txtPDBName_2->setEnabled(false);
            ui->txtChain_2->setEnabled(false);
            ui->lstPDBsLoaded_2->setEnabled(false);
            ui->txtAtomDistance->setEnabled(false);
        }
    }
}


void MainWindow::on_cmbFilterRefseq_activated(int index)
{
    switch(index){
    case 0:
    {
        ui->txtFilterRefSeq->setEnabled(false);
        break;
    }
    case 1:
    {
        ui->txtFilterRefSeq->setEnabled(true);
        QStringList strCompleter;
        strCompleter.append("1");
        strCompleter.append("2");
        strCompleter.append("3");
        strCompleter.append("4");
        strCompleter.append("5");
        QCompleter* completer = new QCompleter(strCompleter);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        ui->txtFilterRefSeq->setCompleter(completer);
        break;
    }
    case 2:
    {
        ui->txtFilterRefSeq->setEnabled(true);
        ui->txtFilterRefSeq->setCompleter(taxonsCompleter);
        break;
    }
    }
}

void MainWindow::on_cmdFilterRefSeqs_clicked()
{
    ui->cmdFilterRefSeqs->setEnabled(false);

    string url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/pfam/";
    string post_content = "";

    switch(ui->cmbFilterRefseq->currentIndex()){
    case 0:
    {
        url += "haspdb";

        break;
    }
    case 1:
    {
        QString strScore = ui->txtFilterRefSeq->text();
        bool ok;
        int score = strScore.toInt(&ok);

        //Validação
        if(!ok){
            QMessageBox::warning(this,"Error","The annotation score value must be numeric");
            ui->cmdFilterRefSeqs->setEnabled(true);
            return;
        }else{
            if(score < 1 || score > 5){
                QMessageBox::warning(this,"Error","The annotation score must be a value between 1 and 5");
                ui->cmdFilterRefSeqs->setEnabled(true);
                return;
            }
        }

        url += "annotation-filter/" + strScore.toStdString();

        break;
    }
    case 2:
    {
        //Validação
        if(ui->txtFilterRefSeq->text() == ""){
            QMessageBox::warning(this,"Error","You must inform what taxon to filter.");
            ui->cmdFilterRefSeqs->setEnabled(true);
            return;
        }

        url += "taxon-filter/" + ui->txtFilterRefSeq->text().toStdString();

        break;
    }
    }

    for(int i = 0; i < ui->lstRefSeqs->count(); i++){
        string seqname = ui->lstRefSeqs->item(i)->text().toStdString();
        post_content += seqname + "\n";
    }

    QByteArray const data = QString::fromStdString(post_content).toUtf8();

    QNetworkRequest request(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("text/plain; charset=utf-8"));
    QNetworkAccessManager manager;
    QNetworkReply *response(manager.post(request,data));
    //QNetworkReply* response(manager.get(request));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString result = response->readAll();

    vector<string> filtered = this->split(result.toStdString(),'\n');

    int count = 0;
    if(ui->cmbFilterRefseq->currentIndex() == 0){
        for(unsigned int i = 0; i < filtered.size(); i++){
            string protname = this->split(filtered[i],'\t')[0];
            printf("%s\n",protname.c_str());
            for(int j = 0; j < ui->lstRefSeqs->count(); j++){
                if(protname == ui->lstRefSeqs->item(j)->text().toStdString()){
                    ui->lstRefSeqSelected->addItem(protname.c_str());
                    delete ui->lstRefSeqs->item(j);
                    if(j > 0) j--;
                    count ++;
                    break;
                }
            }
        }
    }else{
        for(unsigned int i = 0; i < filtered.size(); i++){
            for(int j = 0; j < ui->lstRefSeqs->count(); j++){
                if(filtered[i] == ui->lstRefSeqs->item(j)->text().toStdString()){
                    ui->lstRefSeqSelected->addItem(filtered[i].c_str());
                    delete ui->lstRefSeqs->item(j);
                    if(j > 0) j--;
                    count ++;
                    break;
                }
            }
        }
    }

    string msg = std::to_string(count) + " sequences were selected.";
    QMessageBox::information(this,"Sequences selected",msg.c_str());

    ui->cmdFilterRefSeqs->setEnabled(true);
}

void MainWindow::on_cmbLookingFilter_activated(int index)
{
    switch(index){
    case 0:
    {
        ui->txtLookingFilter->setEnabled(false);
        break;
    }
    case 1:
    {
        ui->txtLookingFilter->setEnabled(true);
        QStringList strCompleter;
        strCompleter.append("1");
        strCompleter.append("2");
        strCompleter.append("3");
        strCompleter.append("4");
        strCompleter.append("5");
        QCompleter* completer = new QCompleter(strCompleter);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        ui->txtLookingFilter->setCompleter(completer);
        break;
    }
    case 2:
    {
        ui->txtFilterRefSeq->setEnabled(true);
        ui->txtFilterRefSeq->setCompleter(taxonsCompleter);
        break;
    }
    }
}


void MainWindow::on_cmdLookingFilter_clicked()
{
    ui->cmdLookingFilter->setEnabled(false);

    string url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/pfam/";
    string post_content = "";

    switch(ui->cmbLookingFilter->currentIndex()){
    case 0:
    {
        url += "haspdb";

        break;
    }
    case 1:
    {
        QString strScore = ui->txtLookingFilter->text();
        bool ok;
        int score = strScore.toInt(&ok);

        //Validação
        if(!ok){
            QMessageBox::warning(this,"Error","The annotation score value must be numeric");
            ui->cmdLookingFilter->setEnabled(true);
            return;
        }else{
            if(score < 1 || score > 5){
                QMessageBox::warning(this,"Error","The annotation score must be a value between 1 and 5");
                ui->cmdLookingFilter->setEnabled(true);
                return;
            }
        }

        url += "annotation-filter/" + strScore.toStdString();

        break;
    }
    case 2:
    {
        //Validação
        if(ui->txtLookingFilter->text() == ""){
            QMessageBox::warning(this,"Error","You must inform what taxon to filter.");
            ui->cmdLookingFilter->setEnabled(true);
            return;
        }

        url += "taxon-filter/" + ui->txtLookingFilter->text().toStdString();

        break;
    }
    }

    for(int i = 0; i < ui->lstLookingRefs->count(); i++){
        string seqname = ui->lstLookingRefs->item(i)->text().toStdString();
        post_content += seqname + "\n";
    }

    QByteArray const data = QString::fromStdString(post_content).toUtf8();
    QNetworkRequest request(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("text/plain; charset=utf-8"));
    QNetworkAccessManager manager;
    QNetworkReply *response(manager.post(request,data));
    //QNetworkReply* response(manager.get(request));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString result = response->readAll();

    vector<string> filtered = this->split(result.toStdString(),'\n');

    int count = 0;
    if(ui->cmbLookingFilter->currentIndex() == 0){
        for(unsigned int i = 0; i < filtered.size(); i++){
            string protname = this->split(filtered[i],'\t')[0];
            //printf("%s\n",protname.c_str());
            for(int j = 0; j < ui->lstLookingRefs->count(); j++){
                if(protname == ui->lstLookingRefs->item(j)->text().toStdString()){
                    //ui->lstRefSeqSelected->addItem(protname.c_str());
                    ui->lstLookingRefs->item(j)->setSelected(true);
                    count ++;
                    break;
                }
            }
        }
    }else{
        for(unsigned int i = 0; i < filtered.size(); i++){
            for(int j = 0; j < ui->lstLookingRefs->count(); j++){
                if(filtered[i] == ui->lstLookingRefs->item(j)->text().toStdString()){
                    //ui->lstRefSeqSelected->addItem(filtered[i].c_str());
                    ui->lstLookingRefs->item(j)->setSelected(true);
                    count ++;
                    break;
                }
            }
        }
    }

    string msg = std::to_string(count) + " sequences were selected.";
    QMessageBox::information(this,"Sequences selected",msg.c_str());

    ui->cmdLookingFilter->setEnabled(true);
}

string MainWindow::findCurrentAlphabet(){
    set<char> singleResidues;

    for(unsigned int i = 0; i < currentAlign->sequences.size(); i++){
        for(unsigned int j = 0; j < currentAlign->sequences[i].size(); j++){
            singleResidues.insert(currentAlign->sequences[i][j]);
        }
    }

    bool a = (singleResidues.find('A') != singleResidues.end()) || (singleResidues.find('a') != singleResidues.end());
    bool g = (singleResidues.find('G') != singleResidues.end()) || (singleResidues.find('g') != singleResidues.end());
    bool i = (singleResidues.find('I') != singleResidues.end()) || (singleResidues.find('i') != singleResidues.end());
    bool l = (singleResidues.find('L') != singleResidues.end()) || (singleResidues.find('l') != singleResidues.end());
    bool p = (singleResidues.find('P') != singleResidues.end()) || (singleResidues.find('p') != singleResidues.end());
    bool v = (singleResidues.find('V') != singleResidues.end()) || (singleResidues.find('v') != singleResidues.end());
    bool f = (singleResidues.find('F') != singleResidues.end()) || (singleResidues.find('f') != singleResidues.end());
    bool w = (singleResidues.find('W') != singleResidues.end()) || (singleResidues.find('w') != singleResidues.end());
    bool y = (singleResidues.find('Y') != singleResidues.end()) || (singleResidues.find('y') != singleResidues.end());
    bool d = (singleResidues.find('D') != singleResidues.end()) || (singleResidues.find('d') != singleResidues.end());
    bool e = (singleResidues.find('E') != singleResidues.end()) || (singleResidues.find('e') != singleResidues.end());
    bool r = (singleResidues.find('R') != singleResidues.end()) || (singleResidues.find('r') != singleResidues.end());
    bool h = (singleResidues.find('H') != singleResidues.end()) || (singleResidues.find('h') != singleResidues.end());
    bool k = (singleResidues.find('K') != singleResidues.end()) || (singleResidues.find('k') != singleResidues.end());
    bool s = (singleResidues.find('S') != singleResidues.end()) || (singleResidues.find('s') != singleResidues.end());
    bool t = (singleResidues.find('T') != singleResidues.end()) || (singleResidues.find('t') != singleResidues.end());
    bool c = (singleResidues.find('C') != singleResidues.end()) || (singleResidues.find('c') != singleResidues.end());
    bool m = (singleResidues.find('M') != singleResidues.end()) || (singleResidues.find('m') != singleResidues.end());
    bool n = (singleResidues.find('N') != singleResidues.end()) || (singleResidues.find('n') != singleResidues.end());
    bool q = (singleResidues.find('G') != singleResidues.end()) || (singleResidues.find('g') != singleResidues.end());

    //Smpre um caracter a mais pq do GAP
    switch(singleResidues.size()){
    case 3:
    {
        //T2(P,Y), Murphy2(P,E), Wang2(I,A)
        if(p){
            if(y) return "T2";
            if(e) return "Murphy2";
        }else if(i && a) return "Wang2";
    }
    case 4:
    {
        //3IMG(I,G,D), Wang3(I,A,E), Li3(I,S,E)
        if(i){
            if(e){
                if(a) return "Wang3";
                if(s) return "Li3";
            }else if(g && d) return "3IMG";
        }
    }
    case 5:
    {
        //Murphy4(LAFE), Li4(YISE)
        if(e){
            if(l && a && f) return "Murphy4";
            if(y && i && s) return "Li4";
        }
    }
    case 6:
    {
        //T5(IFKGT), 5IMG(GCEMF), Wang5(IAGEK), Wang5v(ILAEK), Li5(YIGSN)
        if(i && f && k && g && t) return "T5";
        if(g && c && e && m && f) return "5IMG";
        if(i && a && g && e && k) return "Wang5";
        if(i && l && a && e && k) return "Wang5v";
        if(y && i && g && s && n) return "Li5";
    }
    case 7:
    {
        //T6
        if(i && f && k && d && g && t)
            return "T6";
    }
    case 9:
    {
        //Murphy8
        if(l && a && s && p && f && e && k && h)
            return "Murphy8";
    }
    case 11:
    {
        //Murphy10(LCAGSPFEKH), Li10(CYLVGPSNEK)
        if(l && c && g && s && p && e && k){
            if(a && f && h) return "Murphy10";
            if(y && v && n) return "Li10";
        }

    }
    case 12:
    {
        //11IMG
        if(a && f && c && g && s && w && y && p && d && n && h)
            return "11IMG";
    }
    case 16:
    {
        //Murphy15
        if(l && c && a && g && s && t && p && f && w && e && d && n && q && k && h)
            return "Murphy15";
    }
    }

    return "T20";
}

void MainWindow::on_cmdApplyViewAlignment_clicked()
{
    this->showFullAlignment(ui->cmbAlphabetColor->currentIndex(), ui->cmbViewColumns->currentIndex());
}

void MainWindow::on_cmbFilterMethod_activated(int index)
{
    if(index == 0){
        ui->label_10->setEnabled(false);
        ui->cmbRefSeq->setCurrentText("");
        ui->cmbRefSeq->setEnabled(false);
        ui->chkApplyTaxonFilter->setEnabled(true);
        emit ui->chkApplyTaxonFilter->clicked(ui->chkApplyTaxonFilter->isChecked());
        ui->chkApplyMinCover->setEnabled(true);
        ui->chkApplyMinCover->setChecked(true);
        emit ui->chkApplyMinCover->clicked(true);
        ui->chkApplyMinId->setEnabled(false);
        ui->chkApplyMinId->setChecked(false);
        emit ui->chkApplyMinId->clicked(false);
        ui->chkApplyMaxId->setEnabled(true);
        ui->chkApplyMaxId->setChecked(true);
        emit ui->chkApplyMaxId->clicked(true);

    }else if(index == 1){
        ui->label_10->setEnabled(true);
        ui->cmbRefSeq->setEnabled(true);
        ui->chkApplyTaxonFilter->setEnabled(true);
        emit ui->chkApplyTaxonFilter->clicked(ui->chkApplyTaxonFilter->isChecked());
        ui->chkApplyMinCover->setEnabled(true);
        ui->chkApplyMinCover->setChecked(true);
        emit ui->chkApplyMinCover->clicked(true);
        ui->chkApplyMinId->setEnabled(true);
        emit ui->chkApplyMinId->clicked(true);
        ui->chkApplyMaxId->setEnabled(true);
        ui->chkApplyMaxId->setChecked(true);
        emit ui->chkApplyMaxId->clicked(true);

    }else if(index == 2){
        ui->label_10->setEnabled(false);
        ui->cmbRefSeq->setCurrentText("");
        ui->cmbRefSeq->setEnabled(false);
        ui->chkApplyTaxonFilter->setEnabled(false);
        ui->chkApplyTaxonFilter->setChecked(false);
        emit ui->chkApplyTaxonFilter->clicked(false);
        ui->chkApplyMinCover->setEnabled(false);
        ui->chkApplyMinCover->setChecked(false);
        emit ui->chkApplyMinCover->clicked(false);
        ui->chkApplyMinId->setEnabled(false);
        ui->chkApplyMinId->setChecked(false);
        emit ui->chkApplyMinId->clicked(false);
        ui->chkApplyMaxId->setEnabled(false);
        ui->chkApplyMaxId->setChecked(false);
        emit ui->chkApplyMaxId->clicked(false);
        ui->cmdApplyFilter->setEnabled(true);
    }
}

void MainWindow::on_listWidget2_itemActivated(QListWidgetItem *item)
{
    //Recupera e atualiza o filtro atual
    Filter *filter = currentAlign->getFilterByName(item->text().toStdString());
    currentFilter = filter;

    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("");
    ui->cmbRefSeq_4->clear();
    ui->cmbRefSeq_4->addItem("");
    ui->lstProteinsFiltered->clear();
    ui->lstLookingRefs->clear();
    ui->cmbComm->clear();
    ui->lstManageComms->clear();

    ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(filter->getSequencesCount()));

    for(unsigned int i = 0; i < filter->getSequencesCount(); i++){
        string proteinName = this->split(filter->getSequenceName(i),'/')[0];

        ui->cmbRefSeq_2->addItem(proteinName.c_str());
        ui->cmbRefSeq_3->addItem(proteinName.c_str());
        ui->cmbRefSeq_4->addItem(proteinName.c_str());
        ui->lstProteinsFiltered->addItem(proteinName.c_str());
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    for(unsigned int i = 0; i < fullAlignment.size(); i++){
        vector<string> splitVec = this->split(fullAlignment[i],'/');
        ui->lstLookingRefs->addItem(QString::fromStdString(splitVec[0]));
    }

    if(ui->stackedWidget->currentIndex() == STACK_MANAGE_COMMS){
        unsigned int nOfComms = currentFilter->getCommListSize();
        ui->cmbComm->clear();

        for(unsigned int j = 1; j <= nOfComms; j++)
            ui->cmbComm->addItem(QString::number(j));
    }else if(ui->stackedWidget->currentIndex() == STACK_RESULTS){
        this->updateResultsViews();
    }

    currentFilter->CalculateFrequencies();

    ui->cmbRefSeq_2->setCurrentIndex(1);
    ui->cmbRefSeq_2->activated(ui->cmbRefSeq_2->currentText());
    ui->cmbRefSeq_3->setCurrentIndex(1);
    ui->cmbRefSeq_4->setCurrentIndex(1);
    ui->cmbRefSeq_4->activated(ui->cmbRefSeq_4->currentText());
}

string MainWindow::getDirectory(string path){
    vector<string> splittedPath = this->split(path,'/');
    string directory = "";

    for(unsigned int i = 0; i < splittedPath.size()-1; i++){
        directory += splittedPath[i] + "/";
    }

    return directory;
}

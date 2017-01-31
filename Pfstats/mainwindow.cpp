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

    //QMainWindow::showFullScreen();
    ui->listWidget2->resizeColumnToContents(0);

    currentAlign = nullptr;
    currentFilter = nullptr;
    currentNetwork = nullptr;

    libpath = "pflibs/"; //NO windows começar com dir raiz
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

    //Seta número de cores na tela do minss
    unsigned cores = omp_get_num_procs();
    ui->intNumOfCores->setValue(cores);

    //Configura actions
    ui->listWidget->addAction(ui->actionNewAlignment);
    ui->listWidget->addAction(ui->actionRemoveAlignment);
    ui->listWidget2->addAction(ui->actionNewFilter);
    ui->listWidget2->addAction(ui->actionRenameFilter);
    ui->listWidget2->addAction(ui->actionRemoveFilter);
    ui->listWidget2->addAction(ui->actionDuplicateFilter);

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
    connect(ui->actionOpenAlignment,SIGNAL(triggered()),this,SLOT(changeToOpenAlignment()));
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
    connect(ui->actionTaxonomic_View,SIGNAL(triggered()),this,SLOT(changeToTaxonomicView()));
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
    connect(ui->actionCommunitiesNetwork,SIGNAL(triggered()),this,SLOT(changeToCorrelationBetweenComms()));
    connect(ui->actionStrutucture_Conserved_Residues_Visualization,SIGNAL(triggered()),SLOT(changeToPDBVisualization()));
    connect(ui->actionStructure_Communities_Visualization,SIGNAL(triggered()),SLOT(changeToPDBVisualization2()));
    connect(ui->actionFull_Alignment,SIGNAL(triggered()),this,SLOT(changeToFullAlignment()));
    connect(ui->actionSet_Libraries_Path,SIGNAL(triggered()),this,SLOT(setLibPath()));
    connect(ui->actionAlphabet_Reduction,SIGNAL(triggered()),this,SLOT(changeToAlphabetReduction()));
    connect(ui->actionGenerate_Sub_Alignment,SIGNAL(triggered()),this,SLOT(changeToGenSubAlignments()));
    connect(ui->actionAdd_Sequences,SIGNAL(triggered()),this,SLOT(changeToAddSequence()));
    connect(ui->graficMinss,SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)),this,SLOT(graphClicked(QCPAbstractPlottable*,QMouseEvent*)));
    connect(ui->actionNewAlignment,SIGNAL(triggered()),this,SLOT(changeToOpenAlignment()));
    connect(ui->actionRemoveAlignment,SIGNAL(triggered()),this,SLOT(closeAlignment()));
    connect(ui->actionNewFilter,SIGNAL(triggered()),this,SLOT(changetoFilterStack()));
    connect(ui->actionMutation_Analysis,SIGNAL(triggered()),this,SLOT(changeToMutationAnalysis()));
    connect(ui->actionRenameFilter,SIGNAL(triggered()),this,SLOT(renameFilter()));
    connect(ui->actionRemoveFilter,SIGNAL(triggered()),this,SLOT(removeFilter()));
    connect(ui->actionDuplicateFilter,SIGNAL(triggered()),this,SLOT(duplicateFilter()));

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
    ui->radioButton_11->setChecked(false);
    ui->radioButton_12->setChecked(false);
    ui->cmbFetchFormat->setCurrentIndex(0);
    ui->chkDownloadAlignment->setChecked(false);
    //FILTER
    ui->cmbRefSeq->clear();
    ui->txtTaxons->clear();
    ui->txtMinCover->setValue(0.8);
    ui->txtMinId->setValue(0.15);
    ui->txtMaxId->setValue(0.8);
    //REFSEQS
    ui->txtSecRefSeqs->clear();
    ui->txtSelectedSecRefseqs->clear();
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
    ui->cmbRefSeq_4->clear();
    //CONSERVATION
    ui->txtPDBName->clear();
    ui->lstRecomendedPDBs->clear();
    ui->txtChain->setText("A");
    ui->txtAlpha->setValue(1);
    ui->txtBeta->setValue(1);
    ui->floatMinCons->setValue(0.8);
    //MINSS
    ui->graficMinss->clearGraphs();
    ui->graficMinss->setVisible(false);
    ui->txtNoAlignments->setValue(100);
    //CORRELATION
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
    ui->txtSequenceNoGaps->clear();
    ui->lblRefSeq1->setText("Reference Sequence:");
    ui->lblTaxon->setText("Taxon:");
    ui->lblMinId->setText("Minimum Identity: ");
    ui->lblOccupancy->setText("Occupancy: ");
    ui->lblMaxId->setText("Maximum Identity: ");
    //FREQ CONSERVATION
    ui->tableFreq->clearContents();
    //PERC CONSERVATION
    ui->tableFreqPerc->clearContents();
    //CONSERVED RESIDUES
    ui->lblMinCons->setText("Minimum Conservation: ");
    ui->tableConsRes->clear();
    //CORRELATION LIST
    ui->lblMinLogP->setText("Minimum Score: ");
    ui->lblMinss->setText("Minss Fraction: ");
    ui->lblDeltaFreq->setText("Delta Frequence: ");
    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("Alignment");
    ui->cmbRefPdb_2->clear();
    ui->treeCorrelation->clear();
    //LIST OF COMMUNITIES
    ui->lblMinLogP_2->setText("Minimum Score: ");
    ui->lblMinss_2->setText("Minss Fraction: ");
    ui->lblDeltaFreq_2->setText("Delta Frequence: ");
    ui->treeCorrelationComm->clear();
    ui->cmbRefSeq_3->clear();
    ui->cmbRefPdb_3->clear();
    //CORRELATION TABLES %
    ui->lblComunidade->setText("Community: ");
    ui->lblMinLogP_3->setText("Minimum Score: ");
    ui->lblMinss_3->setText("MRsA Fraction: ");
    ui->lblDeltaFreq_3->setText("Delta Frequence: ");
    ui->tableComm1->clear();
    //CORRELATION TABLES LOG P
    ui->lblComunidade_2->setText("Community: ");
    ui->lblMinLogP_4->setText("Minimum Score: ");
    ui->lblMinss_4->setText("MRsA Fraction: ");
    ui->lblDeltaFreq_4->setText("Delta Frequence: ");
    ui->tableComm2->clear();
    //ADHERENCE
    ui->tableAdherence->clear();
    //RESIDUES OF COMMUNITIE
    ui->lblComunidade_3->setText("Community: ");
    ui->tableResiduesComm->clear();
    //RESULTS UNIPROT 1
    ui->lstProteinsMined->clear();
    ui->tableProteinsMined1->clearContents();
    //RESULTS UNIPROT 2
    ui->treeMinerComms->clear();
    ui->tableProteinsMined2->clearContents();
    //COMM GRAPHS
    ui->lblComunidade_4->setText("Community: ");
    //CORRELATION BETWEEN COMMS GRAPH
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

bool MainWindow::alignfilter(float occupancy, float minId, float maxId, int refseq, bool filter1, bool filter2, bool filter3, bool taxfilter){
    QString msg = "The filters were successfully applied\n";
    int seqSize;
    int seqCut;
    bool intermediate = ui->chkIntermediate->isChecked();

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
    string namePars = "";

    if(taxfilter){
        if(!currentAlign->taxonTrimming(taxon,firstrefseqname,firstrefseq)) return false;

        if(intermediate){
            namePars += taxon;
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setRefSeq(firstrefseqname);
            filter->setTaxon(taxon);
            filter->setMinOcc(0);
            filter->setMinId(0);
            filter->setMaxId(0);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Taxons filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filter1){
        //if(method == 0) currentAlign->hmmCoverageTrimmimg(taxon,occupancy,alphabet,inter);
        if(!currentAlign->AlignmentTrimming(occupancy,0,firstrefseq,firstrefseqname,true)) return false;

        if(intermediate){
            if(namePars.size() > 0) namePars += "," + QString::number(occupancy,'f',2).toStdString();
            else namePars += QString::number(occupancy,'f',2).toStdString();
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setRefSeq(firstrefseqname);
            filter->setTaxon(taxon);
            filter->setMinOcc(occupancy);
            filter->setMinId(0);
            filter->setMaxId(0);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Minimum coverage filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filter2){
        if(!currentAlign->IdentityMinimum(minId,0)) return false;

        if(intermediate){
            if(namePars.size() > 0) namePars += "," + QString::number(minId,'f',2).toStdString();
            else namePars += QString::number(minId,'f',2).toStdString();
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setRefSeq(firstrefseqname);
            filter->setTaxon(taxon);
            filter->setMinOcc(occupancy);
            filter->setMinId(minId);
            filter->setMaxId(0);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Minimum identity filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filter3){
        if(!currentAlign->IdentityTrimming(maxId)) return false;

        if(intermediate){
            if(namePars.size() > 0) namePars += "," + QString::number(maxId,'f',2).toStdString();
            else namePars += QString::number(maxId,'f',2).toStdString();
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setRefSeq(firstrefseqname);
            filter->setTaxon(taxon);
            filter->setMinOcc(occupancy);
            filter->setMinId(minId);
            filter->setMaxId(maxId);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Maximum identity filter removed " + QString::number(seqCut) + " sequences.\n\n";
    }

    msg += "Remaining sequences: " + QString::number(seqSize) + ".";

    if(!intermediate){
        Filter *filter = new Filter(name,alphabet,type);
        filter->setRefSeq(firstrefseqname);
        filter->setTaxon(taxon);
        if(filter1) filter->setMinOcc(occupancy);
        if(filter2) filter->setMinId(minId);
        if(filter3) filter->setMaxId(maxId);
        filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
        filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
        treeItem->setText(0,name.c_str());
        filter->setQtreeWidgetItem(treeItem);

        currentAlign->addFilter(filter);
        //ui->listWidget2->addItem(name.c_str());
    }

    ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
    //ui->listWidget2->item(ui->listWidget2->count()-1)->setSelected(true);
    //emit ui->listWidget2->activated(ui->listWidget2->currentIndex());

    QMessageBox::information(this,"Alignment filters",msg);

    return true;
}

bool MainWindow::alignfilter(float occupancy, float maxId, bool filterOcc, bool filterMaxId, bool filterTaxon){
    QString msg = "The filters were successfully applied\n";
    int seqSize;
    int seqCut;
    bool intermediate = ui->chkIntermediate->isChecked();

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

    string namePars = "";

    if(filterTaxon){
        if(!currentAlign->taxonTrimming(taxon,"0","")) return false;

        if(intermediate){
            namePars += taxon;
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setTaxon(taxon);
            filter->setMinOcc(0);
            filter->setMaxId(0);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Taxons filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filterOcc){
        if(!currentAlign->hmmCoverageTrimmimg(occupancy)){
            if(currentAlign->sequences.size() == 0){
                QMessageBox::warning(this,"Filter","Your parameters filtered all sequences of the alignment.");
            }
            return false;
        }

        if(intermediate){
            if(namePars.size() > 0) namePars += "," + QString::number(occupancy,'f',2).toStdString();
            else namePars += QString::number(occupancy,'f',2).toStdString();
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setTaxon(taxon);
            filter->setMinOcc(occupancy);
            filter->setMaxId(0);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Minimum coverage filter removed " + QString::number(seqCut) + " sequences.\n";
    }

    if(filterMaxId){
        if(!currentAlign->IdentityTrimming(maxId)) return false;

        if(intermediate){
            if(namePars.size() > 0) namePars += "," + QString::number(maxId,'f',2).toStdString();
            else namePars += QString::number(maxId,'f',2).toStdString();
            string newName = name + "(" + namePars + ")";
            Filter *filter = new Filter(newName,alphabet,type);
            filter->setTaxon(taxon);
            filter->setMinOcc(occupancy);
            filter->setMaxId(maxId);
            filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
            filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
            treeItem->setText(0,newName.c_str());
            filter->setQtreeWidgetItem(treeItem);

            currentAlign->addFilter(filter);
            //ui->listWidget2->addItem(newName.c_str());
        }

        seqCut = seqSize - currentAlign->sequences.size();
        seqSize = currentAlign->sequences.size();
        msg += "Maximum identity filter removed " + QString::number(seqCut) + " sequences.\n\n";
    }

    msg += "Remaining sequences: " + QString::number(seqSize) + ".";

    currentAlign->convertLowerDots();

    //currentAlign->dots2dashs();

    if(!intermediate){
        Filter *filter = new Filter(name,alphabet,type);
        filter->setTaxon(taxon);
        if(filterOcc) filter->setMinOcc(occupancy);
        if(filterMaxId) filter->setMaxId(maxId);
        filter->addSequences(currentAlign->getSequencesName(),currentAlign->getSequences());
        filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
        treeItem->setText(0,name.c_str());
        filter->setQtreeWidgetItem(treeItem);

        currentAlign->addFilter(filter);
        //ui->listWidget2->addItem(name.c_str());
    }

    ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
    //ui->listWidget2->item(ui->listWidget2->count()-1)->setSelected(true);
    //emit ui->listWidget2->activated(ui->listWidget2->currentIndex());

    QMessageBox::information(this,"Alignment filters",msg);

    return false;
}

bool MainWindow::applyHenikoffFilter(){
    currentAlign->convertLowerDots();
    if(!currentFilter->henikoffWeights()) return false;

    QMessageBox::information(this,"Alignment filters","The sequences were weighed correctly.");
    return true;
}

void MainWindow::conservation(char chain, float minCons, string pdbid){
    float alpha = ui->txtAlpha->value();
    float beta = ui->txtBeta->value();
    currentFilter->CalculateFrequencies();
    if(currentFilter->getWeightsSize() == 0) currentFilter->dGCalculation();
    else currentFilter->dGCalculation(alpha,beta);
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

        string pdbfilename = pdbid + "_CONS.pdb";
        QString filename = QFileDialog::getSaveFileName(this,tr("Save conservation structure file"),pdbfilename.c_str(),tr("TEXT Files (*.pdb)"));
        path = filename.toStdString();

        //pdb->printSeqNumbers();
        //vector<float> consvec = currentFilter->createConservationVector(refseq);
        vector<tuple<int,float> > consvec = currentFilter->createConservationVectorDG(pdb->getRefSeqId());
        pdb->exportStructure(filename,consvec,chain);

        currentFilter->setConsPDBPath(path);

    }

    currentFilter->setConsMin(minCons);
    currentFilter->setConsPDB(pdbid);

    if(pdbid != "") QMessageBox::information(this,"Conservation","Conservation has been calculated and the structure file has been successfully created at the above path:\n\n" + QString::fromStdString(path));
    else QMessageBox::information(this,"Conservation","Conservation has been calculated.");
}

vector<float> MainWindow::minss(int repetitions, int cores){
    vector<float> outputVec;
    currentFilter->CalculateFrequencies();
    //outputVec = currentAlign->DTRandomElimination(repetitions,99,1,1);
    outputVec = currentFilter->ShannonEntropy(repetitions,cores);

    return outputVec;
}

void MainWindow::pcalc(Network *net, int minlogp, float minssfraction, float mindeltafreq){
    net->CalculateFrequencies();

    if(currentFilter->getWeightsSize() == 0)
        net->SympvalueCalculation(minlogp,minssfraction,mindeltafreq);
    else
        net->henikoffpvalueCalculation(minlogp,minssfraction,mindeltafreq,currentFilter->getWeights());
}

void MainWindow::dfsUtil(Network *net, string node, int id){
    visited[node] = true;
    net->addToCommunity(node,id);

    set<string> adj = adjMap[node];
    for(string no : adj){
        if(!visited[no])
            dfsUtil(net,no,id);
    }
}

bool MainWindow::trivcomm(Network *net){
    adjMap.clear();
    visited.clear();
    net->clearCommunity();

    //create adjMap
    set<string> nodes = net->getCorrelationNodes();
    for(string no : nodes){
        set<string> blank;
        adjMap[no] = blank;
        visited[no] = false;
    }

    for(unsigned int i = 0; i < net->getCorrelationGraphSize(); i++){
        tuple<string,string,int> edge = net->getCorrelationEdge(i);
        int score = std::get<2>(edge);

        //Only positive edges are considered
        if(score > 0){
            string v1 = std::get<0>(edge);
            string v2 = std::get<1>(edge);
            adjMap[v1].insert(v2);
            adjMap[v2].insert(v1);
        }
    }

    //Percorre cada no e seu vetor de adjacencias
    int count = 0;
    for(string no : nodes){
        if(visited[no] == false){
            vector<string> comm;
            net->addCommunity(comm);

            this->dfsUtil(net,no,count);


            count++;//cout "\n";
        }
    }

    //Limpa os mapas
    adjMap.clear();
    visited.clear();

    //Ordena comunidades
    net->sortCommunitiesVector();

    if(net->getCommListSize() == 0) return false;

    return true;
}

/*//OLD
bool MainWindow::trivcomm(){
    unsigned int maxsize;
    unsigned int biggestcommunity;
    unsigned int c1,c2;
    int found1comm,found2comm; // Communities and positions where pos1-aa1 and pos2-aa2 were found
    bool member1found=false;
    bool member2found=false;
    vector < vector <int> > posCommunities;
    vector < vector <char> > aaCommunities;
    currentFilter->clearCommunity();

    if(currentFilter->getCorrelationGraphSize() == 0){
        QMessageBox::warning(this,"There's no correlation","None correlation was found.");
        return false;
    }

    tuple<string,string,int> edge = currentFilter->getCorrelationEdge(0);
    string v1 = std::get<0>(edge);
    string v2 = std::get<1>(edge);
    int score = std::get<2>(edge);
    int steps = v1.length() + v2.length() + currentFilter->getCorrelationGraphSize() + 30;
    int step = 0;
    //printf("V1: %s, V2: %s\n",v1.c_str(),v2.c_str());
    char aa1 = v1[0];
    char aa2 = v2[0];
    int pos1, pos2;

    QProgressDialog progress("Decomposing the network...(2/6)", "Abort", 0,steps);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );

    string temp = "";
    for(unsigned int i = 1; i < v1.length(); i++){
        step++;
        progress.setValue(step);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return false;
        temp += v1[i];
    }
    pos1 = std::atoi(temp.c_str());

    temp = "";
    for(unsigned int i = 1; i < v2.length(); i++){
        step++;
        progress.setValue(step);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return false;
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
        step++;
        progress.setValue(step);
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return false;

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
            QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
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
            QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
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
                    printf("\nTrivial solution not possible: %c%d and %c%d are on the same community, but have a negative score",aa1,pos1,aa2,pos2);
                    QString str = "Trivial solution not possible: " + aa1 + QString::number(pos1) + " and " + aa2 + QString::number(pos2) + " are on the same community, but have a negative score";
                    QMessageBox::warning(this,"Trivcomm",str);
                    return false;
                }
            if (found2comm!=found1comm){
                if(score>0){
                    for(c1=0;c1<=aaCommunities[found2comm].size()-1;c1++){
                        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
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
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        if(progress.wasCanceled()) return false;
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

    return true;

    progress.close();
    //currentAlign->printCommunity();
}
*/


void MainWindow::output(){
    currentNetwork->getCommunitiesFromRAM();


    currentNetwork->Cluster2SCMFromRAM(false,0,0);

    currentNetwork->DeltaCommunitiesCalculation();
    currentNetwork->pMatrix2HTMLRAM(false,1);
}

void MainWindow::listSequences(){
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
    unsigned int nrows = currentNetwork->getGraphSize();

    //Limpa a tabela
    ui->treeCorrelation->clear();

    //Recupera parametros
    ui->lblMinLogP->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore())));
    ui->lblMinss->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction())));
    ui->lblDeltaFreq->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta())));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = currentNetwork->getGraphTuple(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelation);

        item->setText(0,std::get<0>(tupCorr).c_str());
        item->setText(1,std::get<1>(tupCorr).c_str());
        item->setText(2,QString::number(std::get<2>(tupCorr)));
    }
}

void MainWindow::on_cmdUpdateGraphNumbering_clicked()
{
    ui->cmdUpdateGraphNumbering->setEnabled(false);

    unsigned int nrows = currentNetwork->getGraphSize();

    //Limpa a tabela
    ui->treeCorrelation->clear();

    //Recupera parametros
    ui->lblMinLogP->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore())));
    ui->lblMinss->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction())));
    ui->lblDeltaFreq->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta())));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = currentNetwork->getGraphTuple(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelation);
        string res1 = std::get<0>(tupCorr).c_str();
        string res2 = std::get<1>(tupCorr).c_str();
        char aa1 = res1[0];
        char aa2 = res2[0];
        int pos1 = atoi(res1.substr(1).c_str());
        int pos2 = atoi(res2.substr(1).c_str());
        QString newAA1;
        QString newAA2;

        if(ui->cmbRefSeq_2->currentIndex() == 0){
            newAA1 = aa1 + QString::number(pos1);
            newAA2 = aa2 + QString::number(pos2);
        }else{
            int newPos1 = currentFilter->AlignNumbering2Sequence2(ui->cmbRefSeq_2->currentIndex(),pos1-1,currentAlign->getFullSequences());
            int newPos2 = currentFilter->AlignNumbering2Sequence2(ui->cmbRefSeq_2->currentIndex(),pos2-1,currentAlign->getFullSequences());
            if(newPos1 == 0) newAA1 = "-";
            else{
                newPos1 += GetOffsetFromSeqName(ui->cmbRefSeq_2->currentText().toStdString());
                newAA1 = aa1 + QString::number(newPos1);
            }
            if(newPos2 == 0) newAA2 = "-";
            else{
                newPos2 += GetOffsetFromSeqName(ui->cmbRefSeq_2->currentText().toStdString());
                newAA2 = aa2 + QString::number(newPos2);
            }
        }

        item->setText(0,newAA1);
        item->setText(1,newAA2);
        item->setText(2,QString::number(std::get<2>(tupCorr)));
    }

    ui->cmdUpdateGraphNumbering->setEnabled(true);
}

void MainWindow::on_cmdUpdateGraphPdbNumbering_clicked()
{
    ui->cmdUpdateGraphPdbNumbering->setEnabled(false);

    //Validaçao
    if(!ui->cmbRefPdb_2->isEnabled()){
        ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
        return;
    }
    if(ui->cmbRefPdb_2->currentText() == ""){
        QMessageBox::warning(this,"Warning","You must inform a pdb file");
        if(pdbs.size() == 0) ui->stackedWidget->setCurrentIndex(STACK_PDB);
        ui->cmbRefPdb_2->setFocus();
        ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
        return;
    }
    Pdb* pdb = NULL;
    string pdbid = ui->cmbRefPdb_2->currentText().toStdString();
    for(unsigned int i = 0; i < pdbs.size(); i++){
        if(pdbid == pdbs[i]->getId()){
            pdb = pdbs[i];
            break;
        }
    }

    if(pdb == NULL){
        QMessageBox::warning(this,"Warning","PDB not found. Maybe it hasn't been loaded.");
        ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
        return;
    }

    unsigned int nrows = currentNetwork->getGraphSize();

    //Limpa a tabela
    ui->treeCorrelation->clear();

    //Recupera parametros
    ui->lblMinLogP->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore())));
    ui->lblMinss->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction())));
    ui->lblDeltaFreq->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta())));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = currentNetwork->getGraphTuple(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelation);
        string res1 = std::get<0>(tupCorr).c_str();
        string res2 = std::get<1>(tupCorr).c_str();
        char aa1 = res1[0];
        char aa2 = res2[0];
        int pos1 = atoi(res1.substr(1).c_str());
        int pos2 = atoi(res2.substr(1).c_str());
        string newAA1 = "";
        string newAA2 = "";

        for(unsigned int j = 0; j < pdb->countResidues(); j++){
            PdbResidues* residue = pdb->getResidue(j);
            if(residue->getAlignPos() == pos1)
                newAA1 = aa1 + to_string(residue->getResidueNumber());
            else if(residue->getAlignPos() == pos2)
                newAA2 = aa2 + to_string(residue->getResidueNumber());

            if(newAA1 != "" && newAA2 != "")
                break;
        }

        item->setText(0,newAA1.c_str());
        item->setText(1,newAA2.c_str());
        item->setText(2,QString::number(std::get<2>(tupCorr)));

        ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
    }
    ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
}


void MainWindow::createCorrelationJSON(){
    unsigned int nrows = currentNetwork->getGraphSize();
    string pathJSON = libpath + "visjs/examples/network/in.js";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);
    map<string,int> nodes = currentNetwork->getNodesHubs();
    map<string,int> dic;

    //Options
    out << "var options = {\n";
    out << "physics: {\n";
    out << "barnesHut: {\n";
    out << "gravitationalConstant: -36,\n";
    out << "centralGravity: 0.005,\n";
    out << "springLength: 230,\n";
    out << "springConstant: 0.18\n";
    out << "},\n";
    out << "maxVelocity: 146,\n";
    out << "solver: 'forceAtlas2Based',\n";
    out << "timestep: 0.35,\n";
    out << "stabilization: {\n";
    out << "enabled:true,\n";
    out << "iterations:2000,\n";
    out << "updateInterval:25\n";
    out << "}\n";
    out << "},\n";
    out << "interaction:{hover:true},\n";
    out << "edges:{smooth: false}\n";
    out << "};\n\n";


    out << "var nodes = [\n";
    unsigned int count = 1;

    for(map<string,int>::iterator it = nodes.begin(); it != nodes.end(); it++){
        if(it!= nodes.begin()){
            out << ",\n";
        }
        out << "{id: " + QString::number(count) + ", label: '" + QString::fromStdString(it->first) + "', value: " + QString::number(it->second) + "}";
        dic[it->first] = count;
        count++;
    }
    out << "];\n\n";


    out << "var edges = [\n";
    for(unsigned int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = currentNetwork->getGraphTuple(i);
        string n1 = get<0>(tupCorr);
        int id1 = dic[n1];
        string n2 = get<1>(tupCorr);
        int id2 = dic[n2];
        int weight = get<2>(tupCorr);
        string color = "red";

        if(weight > 0) color = "green";

        out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + "},\n";
    }
    out << "];\n";


    //CSS
    string pathCSS = libpath + "visjs/examples/network/mynetwork.css";
    QFile fileCSS(pathCSS.c_str());
    fileCSS.open(QIODevice::WriteOnly);
    QTextStream out2(&fileCSS);

    out2 << "html{\n";
    out2 << "width: 99%;\n";
    out2 << "height: 99%;\n";
    out2 << "}\n";
    out2 << "html, body, #mynetwork {\n";
    out2 << "min-height: 99% !important;\n";
    out2 << "height: 99%;\n";
    out2 << "min-width: 99% !important;\n";
    out2 << "width: 99%;\n";
    out2 << "}\n";
    out2 << "#mynetwork {\n";
    out2 << "border: 1px solid lightgray;\n}";


    string path = libpath + "visjs/examples/network/index.html";
    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;

    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
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

    unsigned int nrows = currentNetwork->getGraphSize();
    string path = libpath + "visjs/examples/network/in.js";
    QFile fileJSON(path.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);
    map<string,int> nodes;
    map<string,int> dic;

    if(ui->cmdHideShowAntiCorr->text() == "Show Anti-Correlations")
        nodes = currentNetwork->getPositiveNodeHubs();
    else
        nodes = currentNetwork->getNodesHubs();

    //Options
    out << "var options = {\n";
    out << "physics: {\n";
    out << "barnesHut: {\n";
    out << "gravitationalConstant: -36,\n";
    out << "centralGravity: 0.005,\n";
    out << "springLength: 230,\n";
    out << "springConstant: 0.18\n";
    out << "},\n";
    out << "maxVelocity: 146,\n";
    out << "solver: 'forceAtlas2Based',\n";
    out << "timestep: 0.35,\n";
    out << "stabilization: {\n";
    out << "enabled:true,\n";
    out << "iterations:2000,\n";
    out << "updateInterval:25\n";
    out << "}\n";
    out << "},\n";
    out << "interaction:{hover:true},\n";
    out << "edges:{smooth: false}\n";
    out << "};\n\n";

    out << "var nodes = [\n";
    unsigned int count = 1;

    for(map<string,int>::iterator it = nodes.begin(); it != nodes.end(); it++){
        if(it!= nodes.begin()){
            out << ",\n";
        }
        out << "{id: " + QString::number(count) + ", label: '" + QString::fromStdString(it->first) + "', value: " + QString::number(it->second) + "}";
        dic[it->first] = count;
        count++;
    }
    out << "];\n\n";

    out << "var edges = [\n";
    for(unsigned int i = 0; i < nrows; i++){
        tuple<string,string,int> tupCorr = currentNetwork->getGraphTuple(i);
        string n1 = get<0>(tupCorr);
        int id1 = dic[n1];
        string n2 = get<1>(tupCorr);
        int id2 = dic[n2];
        int weight = get<2>(tupCorr);

        if(ui->cmdHideShowAntiCorr->text() == "Show Anti-Correlations"){
            if(weight > 0){
                out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'green'}, title: " + QString::number(weight) + "},\n";
            }
        }else{
            string color = "red";
            if(weight > 0) color = "green";

            out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + "},\n";
        }
    }

    out << "];\n";

    //CSS
    string pathCSS = libpath + "visjs/examples/network/mynetwork.css";
    QFile fileCSS(pathCSS.c_str());
    fileCSS.open(QIODevice::WriteOnly);
    QTextStream out2(&fileCSS);

    out2 << "#mynetwork {\n";
    out2 << "width: " + QString::number(ui->webCorrGraph->width()) + "px;\n";
    out2 << "height: " + QString::number(ui->webCorrGraph->height()) + "px;\n";
    out2 << "border: 1px solid lightgray;\n}";

    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
    ui->webCorrGraph->reload();//load(QUrl(localUrl.c_str()));
}

void MainWindow::communitiesGraphs(){
    /*
    string pathJSON = libpath + "abor/in2.json";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);

    ui->lblComunidade_4->setText("Community: 1");

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
    */
}

void MainWindow::corrBetweenComms(){
    string pathJSON = libpath + "visjs/examples/network/in2.js";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);
    map<string,int> dic;

    //Options
    out << "var options = {\n";
    out << "physics: {\n";
    out << "barnesHut: {\n";
    out << "gravitationalConstant: -36,\n";
    out << "centralGravity: 0.005,\n";
    out << "springLength: 230,\n";
    out << "springConstant: 0.18\n";
    out << "},\n";
    out << "maxVelocity: 146,\n";
    out << "solver: 'forceAtlas2Based',\n";
    out << "timestep: 0.35,\n";
    out << "stabilization: {\n";
    out << "enabled:true,\n";
    out << "iterations:2000,\n";
    out << "updateInterval:25\n";
    out << "}\n";
    out << "},\n";
    out << "interaction:{hover:true},\n";
    out << "edges:{smooth: false}\n";
    out << "};\n\n";

    vector<tuple<string,string,float> > graph = currentNetwork->getDeltasEdges(0);
    set<string> nameset;
    for(unsigned int i = 0; i < graph.size(); i++){
        tuple<string,string,int> tupCorr = graph[i];
        string n1 = get<0>(tupCorr);
        string n2 = get<1>(tupCorr);
        nameset.insert(n1);
        nameset.insert(n2);
    }

    vector<string> commList;
    copy(nameset.begin(), nameset.end(), std::back_inserter(commList));

    if(commList.size() == 0){
        QWebSettings *websettings = QWebSettings::globalSettings();
        websettings->clearMemoryCaches();
        ui->webCorrComm->setHtml("");
        return;
    }

    out << "var nodes = [\n";
    for(unsigned int i = 0; i < commList.size(); i++){
        if(i != 0){
            out << ",\n";
        }

        if(commList[i].substr(0,2) == "Co")
            out << "{id: " + QString::number(i+1) + ", label: '" + commList[i].c_str() + "', color:{background:'#7fffa1'}}";
        else
            out << "{id: " + QString::number(i+1) + ", label: '" + commList[i].c_str() + "', color:{background:'#ffffff'}}";

        dic[commList[i]] = i+1;
    }
    out << "];\n\n";


    out << "var edges = [\n";
    for(unsigned int i = 0; i < graph.size(); i++){
        tuple<string,string,int> tupCorr = graph[i];
        string n1 = get<0>(tupCorr);
        int id1 = dic[n1];
        string n2 = get<1>(tupCorr);
        int id2 = dic[n2];
        int weight = get<2>(tupCorr);
        string color = "red";

        if(weight > 0) color = "green";

        out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + "},\n";
    }
    out << "];\n";


    //CSS
    string pathCSS = libpath + "visjs/examples/network/mynetwork.css";
    QFile fileCSS(pathCSS.c_str());
    fileCSS.open(QIODevice::WriteOnly);
    QTextStream out2(&fileCSS);

    out2 << "html{\n";
    out2 << "width: 99%;\n";
    out2 << "height: 99%;\n";
    out2 << "}\n";
    out2 << "html, body, #mynetwork {\n";
    out2 << "min-height: 99% !important;\n";
    out2 << "height: 99%;\n";
    out2 << "min-width: 99% !important;\n";
    out2 << "width: 99%;\n";
    out2 << "}\n";
    out2 << "#mynetwork {\n";
    out2 << "border: 1px solid lightgray;\n}";


    string path = libpath + "visjs/examples/network/index2.html";
    QFile file(path.c_str());
    file.open(QIODevice::ReadOnly);
    QFileInfo info(file);
    string absPath = info.absoluteFilePath().toStdString();
    string localUrl = "file:///" + absPath;

    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
    ui->webCorrComm->load(QUrl(localUrl.c_str()));
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
    QFile pdbPath(currentNetwork->getCommPDBPath().c_str());
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
    /*
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
    temp = "Community: " + QString::number(currComm + 1).toStdString();
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
    */
}

void MainWindow::on_cmdBackCommGraph_clicked()
{
    /*
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
    temp = "Community: " + QString::number(currComm).toStdString();
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
    */
}

void MainWindow::communitiesList(){
    unsigned int nrows = currentNetwork->getCommListSize();

    //Limpa a tabela
    ui->treeCorrelationComm->clear();

    //Recupera parametros
    ui->lblMinLogP_2->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore()).c_str()));
    ui->lblMinss_2->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction()).c_str()));
    ui->lblDeltaFreq_2->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta()).c_str()));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        vector<string> residues = currentNetwork->getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelationComm);

        string text = "Community " + QString::number(i+1).toStdString() + " [" + QString::number(residues.size()).toStdString() + "]";
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < residues.size(); j++){
            item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(residues[j].c_str()))));
        }
    }
}

void MainWindow::on_cmdUpdateGraphNumbering2_clicked()
{
    ui->cmdUpdateGraphNumbering2->setEnabled(false);

    unsigned int nrows = currentNetwork->getCommListSize();

    vector<int> expandeds;
    //Pega os itens ja expandidos
    for(unsigned int i = 0; i < nrows; i++){
        bool expanded = ui->treeCorrelationComm->isExpanded(ui->treeCorrelationComm->model()->index(i,0));
        if(expanded) expandeds.push_back(i);
    }

    //Limpa a tabela
    ui->treeCorrelationComm->clear();

    //Recupera parametros
    ui->lblMinLogP_2->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore()).c_str()));
    ui->lblMinss_2->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction()).c_str()));
    ui->lblDeltaFreq_2->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta()).c_str()));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        vector<string> residues = currentNetwork->getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelationComm);

        string text = "Community " + QString::number(i+1).toStdString() + " [" + QString::number(residues.size()).toStdString() + "]";
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < residues.size(); j++){
            string res = residues[j];
            char aa = res[0];
            int pos = atoi(res.substr(1).c_str());
            QString newAA;

            if(ui->cmbRefSeq_3->currentIndex() == 0)
                newAA = res.c_str();
            else{
                int newPos = currentFilter->AlignNumbering2Sequence2(ui->cmbRefSeq_3->currentIndex(),pos-1,currentAlign->getFullSequences());
                if(newPos == 0) newAA = "-";
                else{
                    newPos += GetOffsetFromSeqName(ui->cmbRefSeq_3->currentText().toStdString());
                    newAA = aa + QString::number(newPos);
                }
            }

            item->addChild(new QTreeWidgetItem(QStringList(newAA)));
        }
    }

    //Retorna expandidos
    for(unsigned int i = 0; i < expandeds.size(); i++){
        ui->treeCorrelationComm->setExpanded(ui->treeCorrelationComm->model()->index(expandeds[i],0),true);
    }

    ui->cmdUpdateGraphNumbering2->setEnabled(true);
}

void MainWindow::on_cmdUpdateGraphPdbNumbering_2_clicked()
{
    ui->cmdUpdateGraphNumbering2->setEnabled(false);

    //Validaçao
    if(!ui->cmbRefPdb_3->isEnabled()){
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(true);
        return;
    }
    if(ui->cmbRefPdb_3->currentText() == ""){
        QMessageBox::warning(this,"Warning","You must inform a pdb file");
        if(pdbs.size() == 0) ui->stackedWidget->setCurrentIndex(STACK_PDB);
        ui->cmbRefPdb_3->setFocus();
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(true);
        return;
    }
    Pdb* pdb = NULL;
    string pdbid = ui->cmbRefPdb_3->currentText().toStdString();
    for(unsigned int i = 0; i < pdbs.size(); i++){
        if(pdbid == pdbs[i]->getId()){
            pdb = pdbs[i];
            break;
        }
    }

    if(pdb == NULL){
        QMessageBox::warning(this,"Warning","PDB not found. Maybe it hasn't been loaded.");
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(true);
        return;
    }

    unsigned int nrows = currentNetwork->getCommListSize();

    vector<int> expandeds;
    //Pega os itens ja expandidos
    for(unsigned int i = 0; i < nrows; i++){
        bool expanded = ui->treeCorrelationComm->isExpanded(ui->treeCorrelationComm->model()->index(i,0));
        if(expanded) expandeds.push_back(i);
    }

    //Limpa a tabela
    ui->treeCorrelationComm->clear();

    //Recupera parametros
    ui->lblMinLogP_2->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore()).c_str()));
    ui->lblMinss_2->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction()).c_str()));
    ui->lblDeltaFreq_2->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta()).c_str()));

    //Preenche a tabela
    for(unsigned int i = 0; i < nrows; i++){
        vector<string> residues = currentNetwork->getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCorrelationComm);

        string text = "Community " + QString::number(i+1).toStdString() + " [" + QString::number(residues.size()).toStdString() + "]";
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < residues.size(); j++){
            string res = residues[j];
            char aa = res[0];
            int pos = atoi(res.substr(1).c_str());
            string newAA;

            for(unsigned int j = 0; j < pdb->countResidues(); j++){
                PdbResidues* residue = pdb->getResidue(j);
                if(residue->getAlignPos() == pos){
                    newAA = aa + to_string(residue->getResidueNumber());
                    break;
                }

            }

            item->addChild(new QTreeWidgetItem(QStringList(newAA.c_str())));
        }
    }

    //Retorna expandidos
    for(unsigned int i = 0; i < expandeds.size(); i++){
        ui->treeCorrelationComm->setExpanded(ui->treeCorrelationComm->model()->index(expandeds[i],0),true);
    }

    ui->cmdUpdateGraphNumbering2->setEnabled(true);
}

void MainWindow::corrTable1(){
    //int ncomms = currentAlign->getNumOfUtilComms();

    //Limpa a tabela
    ui->tableComm1->clear();

    //Recupera parametros
    ui->lblMinLogP_3->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore()).c_str()));
    ui->lblMinss_3->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinssFraction()).c_str()));
    ui->lblDeltaFreq_3->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta()).c_str()));
    ui->lblComunidade->setText("Community: 1");

    //Monta a tabela
    vector<string> residues = currentNetwork->getResiduesComm(0);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = currentNetwork->getCommAll(0);

    for(unsigned int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = currentNetwork->getCommXRow(0,i);
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
    ui->lblMinLogP_4->setText("Minimum Score: " + QString::fromStdString(to_string(currentNetwork->getMinScore()).c_str()));
    ui->lblMinss_4->setText("MRsA Fraction: " + QString::fromStdString(to_string(currentNetwork->getMinScore()).c_str()));
    ui->lblDeltaFreq_4->setText("Delta Frequence: " + QString::fromStdString(to_string(currentNetwork->getMinDelta()).c_str()));
    ui->lblComunidade_2->setText("Community: 1");

    //Montar a Tabela
    vector<string> residues = currentNetwork->getResiduesCommPs(0);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(unsigned int i = 0; i < residues.size(); i++){
        vector<int> commRow = currentNetwork->getCommPsRow(0,i);

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
    QProgressDialog progress("Calculating adherence for each community", "Abort", 0,currentFilter->sequences.size()+currentNetwork->getNumOfUtilComms());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    unsigned int nComm = currentNetwork->getNumOfUtilComms();
    unsigned int nSequences = currentFilter->sequences.size()-1;

    //Montar a Tabela
    ui->tableAdherence->horizontalHeader()->setVisible(true);
    ui->tableAdherence->setColumnCount(nComm + 1);
    ui->tableAdherence->setRowCount(nSequences);

    ui->tableAdherence->setHorizontalHeaderItem(0,new QTableWidgetItem("PROTEIN SEQUENCE"));

    for(unsigned int i = 0; i < nComm; i++){
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        progress.setValue(i);
        if(progress.wasCanceled()){
            ui->tableAdherence->clear();
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }
        string temp = "Comm " + QString::number(i+1).toStdString();
        ui->tableAdherence->setHorizontalHeaderItem(i+1,new QTableWidgetItem(temp.c_str()));
    }

    //------ADHERENCE-----
    for(unsigned int i = 0; i < currentFilter->sequences.size()-1; i++){
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        progress.setValue(i+nComm);
        if(progress.wasCanceled()){
            ui->tableAdherence->clear();
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }
        QTableWidgetItem *protItem = new QTableWidgetItem();
        protItem->setText(currentFilter->sequencenames[i].c_str());
        ui->tableAdherence->setItem(i,0,protItem);

        for(unsigned int j = 0; j < nComm; j++){

            if(currentNetwork->Communities[j].aa.size() > 1){
                float psa = currentNetwork->PSA(i,j);

                QTableWidgetItem *item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole,psa);
                ui->tableAdherence->setItem(i,j+1,item);
            }
        }

    }
    //Ajusta tamanho das colunas
    ui->tableAdherence->resizeColumnsToContents();
    progress.close();
}

void MainWindow::showConservedResidues(){
    vector<int> refSeqs;
    vector<string> conservedaa = currentFilter->getConsRes();
    vector<float> dgs = currentFilter->getConservedDGs();

    //Parâmetros
    ui->lblMinCons->setText("Minimum Conservation: " + QString::fromStdString(to_string(currentFilter->getConsMin())));

    for(unsigned int i = 0; i < currentFilter->getRefSeqsSize(); i++){
        string ref1 = currentFilter->getRefSeq(i);
        refSeqs.push_back(currentAlign->seqname2seqint3(ref1));
    }

    if(conservedaa.size() == 0){
        QMessageBox::warning(this,"Warning","No residues match the conservation minimum.");
        return;
    }

    //Cabeçalho
    ui->tableConsRes->setColumnCount(conservedaa.size());
    for(unsigned int i = 0; i < conservedaa.size(); i++){
        string textCab = conservedaa[i] + " (" + QString::number(dgs[i],'f',2).toStdString() + ")";
        ui->tableConsRes->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    ui->tableConsRes->setRowCount(refSeqs.size());
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableConsRes->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < conservedaa.size(); j++){
            string res = conservedaa[j];
            char aa = res[0];
            int pos = stoi(res.substr(1))-1;
            if(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,pos,fullSequences) == 0){
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setTextColor(QColor(255,0,0,255));
                item->setText("-");
                ui->tableConsRes->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][pos]==aa){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = aa + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,pos,fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                    item->setText(textItem.c_str());
                    ui->tableConsRes->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][pos] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,pos,fullSequences) + GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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

    if(currentFilter->frequencies.size() == 0)
        currentFilter->CalculateFrequencies();

    for(unsigned int i = 0; i < currentFilter->getRefSeqsSize(); i++){
        string ref1 = currentFilter->getRefSeq(i);

        refSeqs.push_back(currentAlign->seqname2seqint3(ref1));
    }

    //Parâmetros
    ui->lblComunidade_3->setText("Community: 1");

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(currentNetwork->Communities[0].pos.size());
    for(unsigned int i = 0; i < currentNetwork->Communities[0].pos.size(); i++){
        string textCab = currentNetwork->Communities[0].aa[i] + QString::number(currentNetwork->Communities[0].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < currentNetwork->Communities[0].pos.size(); j++){
            if(fullSequences[refSeqs[i]][currentNetwork->Communities[0].pos[j]]==currentNetwork->Communities[0].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = currentNetwork->Communities[0].aa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentNetwork->Communities[0].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][currentNetwork->Communities[0].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][currentNetwork->Communities[0].pos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentNetwork->Communities[0].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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
    for(unsigned int i = 0; i < currentNetwork->getUniprotMinedSize(); i++){
        if(currentNetwork->getUniprotEntryNofFeatures(i) > 0){
            string prot = currentNetwork->getUniprotEntryName(i) + " [" + to_string(currentNetwork->getUniprotEntryNofFeatures(i)) + "]";
            ui->lstProteinsMined->addItem(prot.c_str());
        }
    }
}

void MainWindow::showUniprotGroupByComms(){
    unsigned int nrows = currentNetwork->getCommListSize();

    ui->treeMinerComms->clear();

    for(unsigned int i = 0; i < nrows; i++){
        vector<string> residues = currentNetwork->getCommunitie(i);
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeMinerComms);

        string text = "Comm " + QString::number(i+1).toStdString();
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < residues.size(); j++){
            int nOfResidues = currentNetwork->getResidueFeaturesByCommCount(residues[j]);
            if(nOfResidues > 0){
                string child = residues[j] + " [" + to_string(nOfResidues) + "]";
                item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(child.c_str()))));
            }
        }
    }

    //CONS RES
    vector<string> consRes = currentFilter->getConsRes();
    if(consRes.size() > 0){
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeMinerComms);

        string text = "Conservation";
        item->setText(0,text.c_str());

        for(unsigned int j = 0; j < consRes.size(); j++){
            int nOfResidues = currentNetwork->getResidueFeaturesByCommCount(consRes[j]);
            if(nOfResidues > 0){
                string child = consRes[j] + " [" + to_string(nOfResidues) + "]";
                item->addChild(new QTreeWidgetItem(QStringList(QObject::tr(child.c_str()))));
            }
        }
    }
}

vector<float> MainWindow::generateAMCL(int alfabetIndex){
    int alignCoulumnsSize = currentFilter->sequences[0].size();
    int countMatrix[alignCoulumnsSize][22];//21 is the total size without gaps /22 is size of gaps
    memset(countMatrix,0,sizeof(countMatrix));
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
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
                else if (c== '.' || c == '-') countMatrix[j][21]++;
            }
        }
        break;
    }
    }

    //CONTINUAR
    //Frequence of most conserved residues between the non-gaps * frequence of non-gaps between all positions
    for(int i = 0; i < alignCoulumnsSize; i++){
        float resFreq = (float)*max_element(countMatrix[i],countMatrix[i]+20)/(float)countMatrix[i][20];
        float gapFreq = 1 - (float) countMatrix[i][21]/(float) currentFilter->sequences.size();

        maxValues.push_back(resFreq*gapFreq);
        //printf("%d/%d = %f\n",*max_element(countMatrix[i],countMatrix[i]+20),countMatrix[i][20],maxFreq);
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

        }else if(colorFreq[i] > 0.8){
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

    //Ajusta tamanho das colunas
    ui->tableFullAlignment->resizeColumnsToContents();
    ui->tableFullAlignment->resizeRowsToContents();
    progress.close();
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
    //Verifica qual tela está aberta e qual será a proxima tela a ser exibida
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
}

void MainWindow::on_cmdAdvance_clicked()
{
    //Verifica qual tela está aberta e qual será a proxima tela a ser exibida
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
            QMessageBox::warning(this,"Warning","You must fetch an alignment before proceeding.");
            return;
        }

        ui->cmdBack->setEnabled(true);
        ui->cmdAdvance->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(STACK_FILTER);
        break;
    }
    case STACK_FILTER:
    {
        if(ui->listWidget2->topLevelItemCount() < 2){
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
                                            "You are leaving this page without generating the MRsA chart. Is that correct?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::No) return;
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

    //Cria Alinhamento
    Alignment align;
    align.setFilepath(fileName.toUtf8().constData());
    bool a = align.GetFromFile();
    if(!a){
        ui->cmdOpen->setEnabled(true);
        QMessageBox::warning(this,"Warning","Ivalid input format.");
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
    emit ui->listWidget->activated(ui->listWidget->currentIndex());//VERIFICAR NECESSIDADE

    QString msg = "Alignment loaded with " + QString::number(align.sequences.size()) + " sequences.";
    QMessageBox::information(this,"Alignment loaded",msg);

    ui->cmdOpen->setEnabled(true);
}

void MainWindow::on_cmdFetch_clicked()
{
    ui->cmdFetch->setEnabled(false);
    QString filename;
    Alignment align;
    string pfamid = ui->txtAccession->text().toStdString();

    //Validação de Dados
    if(pfamid == ""){
        QMessageBox::warning(this,"Error","You must fill all fields");
        ui->cmdFetch->setText("Fetch");
        ui->txtAccession->setFocus();
        ui->cmdFetch->setEnabled(true);
        return ;
    }

    if(pfamid.size() > 7){
        QMessageBox::warning(this,"Error","Invalid PFAM id");
        ui->cmdFetch->setText("Fetch");
        ui->txtAccession->setFocus();
        ui->cmdFetch->setEnabled(true);
        return ;
    }else if(pfamid.size() != 7){
        int size = pfamid.size();

        if(size == 6){
            QMessageBox::warning(this,"Error","Invalid PFAM id");
            ui->cmdFetch->setText("Fetch");
            ui->txtAccession->setFocus();
            ui->cmdFetch->setEnabled(true);
            return;
        }

        for(unsigned int i = 2; i < 7-size; i++){
            pfamid = "0" + pfamid;
        }
        pfamid = "pf" + pfamid;
    }

    if(ui->chkDownloadAlignment->isChecked()){
        string finalName;
        if(ui->cmbFetchFormat->currentIndex() == 0) finalName = pfamid + ".sto";
        else finalName = pfamid + ".pfam";
        filename = QFileDialog::getSaveFileName(this,tr("Export File"),finalName.c_str(),tr("TEXT Files (*.pfam *.txt *.sto *.stockholm)"));

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
    QString url = "http://pfam.xfam.org/family/" + QString::fromStdString(pfamid) + "/alignment/";
    QString format = "";

    if(ui->cmbFetchFormat->currentIndex() == 0) format = "stockholm";
    else if(ui->cmbFetchFormat->currentIndex() == 1) format = "pfam";
    else format = "fasta";

    if(ui->radioButton->isChecked()) url += "seed/format?format=" + format + "&amp;alnType=seed&amp;order=";
    else if(ui->radioButton_2->isChecked()) url += "full/format?format=" + format + "&amp;alnType=full&amp;order=";
    else if(ui->radioButton_11->isChecked()) url += "uniprot/format?format=" + format + "&amp;alnType=uniprot   &amp;order=";
    else if(ui->radioButton_12->isChecked()) url += "ncbi/format?format=" + format + "&amp;alnType=ncbi&amp;order=";

    if(ui->radioButton_3->isChecked()) url += "t&amp;case=";
    else url += "a&amp;case=";

    if(ui->cmbAlignmentType->currentIndex() == 0) url += "u&amp;gaps=dashes&amp;download=0";
    else url += "l&amp;gaps=default&amp;download=0";

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
        QMessageBox::warning(this,"Error","PFAM File not Found. Check the PFAM id and your internet connection");
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
                if(pfamid.c_str() ==  ui->listWidget->item(i)->text()) same = true;
            }
            if(!same){
                ui->listWidget->addItem(pfamid.c_str());
                align.setFilepath(pfamid);
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

        if(ui->cmbAlignmentType->currentIndex() == 1){
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
    if(ui->txtFilterName->text() == "" && ui->cmbFilterMethod->currentIndex() != 2){
        QMessageBox::warning(this,"Validation problem","You must set a filter name.");
        ui->txtFilterName->setFocus();
        ui->cmdApplyFilter->setEnabled(true);
        return;
    }

    //Filter names must be different
    for(unsigned int i = 0; i < ui->listWidget2->topLevelItemCount(); i++){
        if(ui->txtFilterName->text() == ui->listWidget2->topLevelItem(i)->text(0) && ui->cmbFilterMethod->currentIndex() != 2){
            QMessageBox::warning(this,"Validation problem","There is already a filter with this name. Pleasy change the name and try again.");
            ui->txtFilterName->setFocus();
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

    //HMM
    if(method == 0){
        if(this->alignfilter(occupancy,maxId,ui->chkApplyMinCover->isChecked(),ui->chkApplyMaxId->isChecked(),ui->chkApplyTaxonFilter->isChecked())){
            ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
            //ui->listWidget2->setCurrentRow(ui->listWidget2->count()-1);
            //emit ui->listWidget2->activated(ui->listWidget2->currentIndex());
        }
    }else if(method == 1){//RefSeq
        if(this->alignfilter(occupancy,minId,maxId,refseq,ui->chkApplyMinCover->isChecked(),ui->chkApplyMinId->isChecked(),ui->chkApplyMaxId->isChecked(),ui->chkApplyTaxonFilter->isChecked())){
            ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
            //ui->listWidget2->setCurrentRow(ui->listWidget2->count()-1);
            //emit ui->listWidget2->activated(ui->listWidget2->currentIndex());
        }
    }else if(method == 2){//Henikoff
        if(applyHenikoffFilter()){
            ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
            //ui->listWidget2->setCurrentRow(ui->listWidget2->count()-1);
            //emit ui->listWidget2->activated(ui->listWidget2->currentIndex());
        }
    }

    ui->cmdApplyFilter->setEnabled(true);
}

void MainWindow::on_cmdConservation_clicked()
{
    ui->cmdConservation->setEnabled(false);

    string alignfilename;
    string pdbfilename = "";
    char chain;
    float minCons;

    //Validação
    if(ui->txtChain->text().length() != 1) chain = 'A';

    if(ui->chkGenerateConsPDB->isChecked() && ui->txtPDBName->text() == ""){
        QMessageBox::warning(this,"Error","You checked to generate structure visualization, but didnt inform any PDB file.");
        ui->txtPDBName->setFocus();
        ui->cmdConservation->setEnabled(true);
        return;
    }

    //Calcular a conservaçao

    if(ui->chkGenerateConsPDB->isChecked())
        pdbfilename = ui->txtPDBName->text().toStdString();

    alignfilename = ui->listWidget->currentItem()->text().toStdString();
    chain = ui->txtChain->text().at(0).toLatin1();
    minCons = ui->floatMinCons->value();

    this->conservation(chain,minCons,pdbfilename);

    ui->cmdConservation->setEnabled(true);
}

void MainWindow::on_cmdMinss_clicked()
{
    ui->cmdMinss->setEnabled(false);

    int repetitions = ui->txtNoAlignments->value();
    int cores = ui->intNumOfCores->value();
    int concurentThreadsSupported = omp_get_num_procs();

    if(cores > concurentThreadsSupported){
        QMessageBox::StandardButton mbox;
        mbox = QMessageBox::question(this, "Warning", "Running more threads than cores can slown down your computer or even crash the system. Do you want to continue?",
                                    QMessageBox::Yes|QMessageBox::No);
        if (mbox == QMessageBox::No) {
            return;
        }
    }

    vector<float> minssData;
    minssData = this->minss(repetitions,cores);

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
    if(ui->txtMinssFraction->text() == ""){
        QMessageBox::warning(this,"Error","You must set a MRsA fraction value to run correlation.");
        ui->txtMinssFraction->setFocus();
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    if(!isFloat(ui->txtMinssFraction->text().toStdString())){
        QMessageBox::warning(this,"Parse Error","MRsA fraction must be a float number.");
        ui->txtMinssFraction->setFocus();
        ui->cmdCorrelation->setEnabled(true);
        return;
    }
    float minssfraction = ui->txtMinssFraction->text().toFloat();
    if(minssfraction < 0.05 || minssfraction > 0.9){
        QMessageBox::warning(this,"Error","MRsA fraction must be in the 0.05 - 0.9 interval.");
        ui->txtMinssFraction->setFocus();
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    //string outputgraphfilename = ui->txtGraphPath->text().toStdString().c_str();
    int minlogp = ui->txtMinScore->value();
    float mindeltafreq = ui->txtMinDeltaFreq->value();
    string pdbid = "";

    //Verifica se essa network já existe neste filtro
    stringstream ss;
    ss << fixed << setprecision(2) << minssfraction;
    string strMinss = ss.str();
    ss.str(std::string());
    ss << fixed << setprecision(2) << mindeltafreq;
    string strDelta = ss.str();
    string name = to_string(minlogp) + "_" + strMinss + "_" + strDelta;
    if(currentFilter->networkExists(name)){
        QMessageBox::warning(this,"Error","A network with these parameters already exists.");
        ui->txtMinScore->setFocus();
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    //Cria nova rede
    Network *net = new Network(&currentFilter->sequences,&currentFilter->sequencenames,minlogp,minssfraction,mindeltafreq);

    //USA ALINHAMENTO TODO EM MAIUSCULAS
    net->alignment2UpperCase();

    //Chama função para calcular correlações e criar a rede
    this->pcalc(net,minlogp,minssfraction,mindeltafreq);

    //Chama funçao para decompor em comunidades
    bool ok = this->trivcomm(net);
    if(!ok){
        QMessageBox::warning(this,"Warning","No correlation was found.");
        ui->cmdCorrelation->setEnabled(true);
        return;
    }

    //Adiciona na lista de comunidades
    QTreeWidgetItem *parent = this->getFilterItem();
    QTreeWidgetItem *child = new QTreeWidgetItem();
    child->setText(0,net->getName().c_str());
    parent->addChild(child);
    currentFilter->addNetwork(net);
    currentNetwork = net;

    //Chamar Output
    this->output();

    //Comm2Align
    if(ui->chkComm2Align->isChecked())
        this->comm2Align();

    //Gerar Visualizações
    if(ui->chkCommVisualization->isChecked()){
        if(ui->txtPDBName_2->text() == ""){
            QMessageBox::warning(this,"Warning","To generate communities visualization, you must inform a PDB");
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
        QApplication::processEvents();
        string pdbfilename = ui->txtPDBName_2->text().toStdString() + "_COMMS.pdb";
        QString filename = QFileDialog::getSaveFileName(this,tr("Save correlation structure file"),pdbfilename.c_str(),tr("TEXT Files (*.pdb)"));
        vector<tuple<int,float> > commvec = currentNetwork->createCommuntitiesVector();
        pdb->exportStructure(filename,commvec,chain);
        currentNetwork->setCommPDBPath(filename.toStdString());
    }

    currentNetwork->setPDB(pdbid);

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
        //if(currentNetwork->getGraphSize() == 0){
        if(!currentNetwork){
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
        //if(currentNetwork->getCommListSize() == 0){
        if(!currentNetwork){
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
        //if(currentNetwork->getNumOfUtilComms() == 0){
        if(!currentNetwork){
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
        //if(currentNetwork->getNumOfUtilComms() == 0){
        if(!currentNetwork){
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
        //if(currentNetwork->getNumOfUtilComms() == 0){
        if(!currentNetwork){
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

        //if(currentNetwork->getNumOfUtilComms() == 0){
        if(!currentNetwork){
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
        //if(currentNetwork->getUniprotMinedSize() == 0){
        if(!currentNetwork){
            QMessageBox::warning(this,"Warning","You must run Uniprot Look-up.");
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
        //if(currentNetwork->getUniprotMinedSize() == 0){
        if(!currentNetwork){
            QMessageBox::warning(this,"Warning","You must run Uniprot Look-up.");
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
        //if(currentNetwork->getCommPDBPath() == ""){
        if(!currentNetwork){
            QMessageBox::warning(this,"Warning","You must run correlation with a PDB for this alignment.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }else if(currentNetwork->getCommPDBPath() == ""){
            QMessageBox::warning(this,"Warning","You must run correlation with a PDB for this alignment.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->commVisualization();

        break;
    }
    case STACK_RESULT_CORRGRAPH:
    {
        //if(currentNetwork->getGraphSize() == 0){
        if(!currentNetwork){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->createCorrelationJSON();

        break;
    }
    case STACK_RESULT_COMMGRAPH:
    {
        //if(currentNetwork->getGraphSize() == 0){
        if(!currentNetwork){
            QMessageBox::warning(this,"Warning","You must run correlation method.");
            ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
            return;
        }

        this->communitiesGraphs();

        break;
    }
    case STACK_RESULT_DELTAGRAPH:
    {
        //if(currentNetwork->getDeltasSize() == 0){
        if(!currentNetwork){
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
    case STACK_RESULT_TAXVIEW:{
        this->generateSunburst(currentFilter->sequencenames);
        break;
    }
    default:
    {
        //nothing
    }
    }
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if(ui->listWidget->count() == 0) return;
    if(currentRow < 0 || currentRow > ui->listWidget->count()) return;

    QProgressDialog progress("Loading the alignment...","Cancel",0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );

    string path = ui->listWidget->item(currentRow)->text().toStdString();
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
    ui->cmbRefSeq_2->addItem("Alignment");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("Alignment");
    ui->cmbRefSeq_4->clear();
    ui->cmbRefSeq_4->addItem("");
    ui->txtSecRefSeqs->clear();
    ui->txtSelectedSecRefseqs->clear();
    ui->lstRefSeqs->clear();
    ui->lstRefSeqSelected->clear();
    ui->lstLookingRefs->clear();
    ui->cmbComm->clear();
    ui->lstManageComms->clear();
    ui->graficMinss->setVisible(false);
    ui->cmbRefPdb_2->clear();
    ui->cmbRefPdb_3->clear();

    vector<string> fullAlign = currentAlign->getFullAlignment();
    currentFilter = currentAlign->getFullFilter();
    //printf("\n%d\n",fullAlign.size());
    for(unsigned int i1 = 0; i1 < fullAlign.size(); i1++){
        QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
        vector<string> splitVec = this->split(fullAlign[i1],'/');
        ui->cmbRefSeq->addItem(QString::fromStdString(splitVec[0]));
        ui->lstLookingRefs->addItem(QString::fromStdString(splitVec[0]));

        ui->lstRefSeqs->addItem(fullAlign[i1].c_str());
    }

    ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(fullAlign.size()));

    ui->listWidget2->clear();

    vector<Filter*> filters = currentAlign->getFilters();

    for(unsigned int j = 0; j < filters.size(); j++){
        Filter* filter = filters[j];
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->listWidget2);
        item->setText(0,filter->getName().c_str());
        filter->setQtreeWidgetItem(item);
        for(unsigned int k = 0; k < filter->countNetworks(); k++){
            Network *net = filter->getNetwork(k);
            QTreeWidgetItem *item2 = new QTreeWidgetItem();
            item2->setText(0,net->getName().c_str());
            item->addChild(item2);
        }
    }

    ui->listWidget2->setCurrentItem(ui->listWidget2->itemAt(0,0));

    //Está sendo chamado automáticamente pelo setCurrentItem
    //emit ui->listWidget2->currentItemChanged(ui->listWidget2->currentItem(),NULL);

    progress.close();
}

void MainWindow::on_cmbRefSeq_activated(int index)
{
    if(index == 0) return;

    ui->cmbRefSeq_4->setCurrentIndex(index);
    ui->cmbRefSeq_4->activated(ui->cmbRefSeq_4->currentText());

    //QMessageBox::information(this,"a",currentAlign->sequencenames[index-1].c_str());
    currentFilter->setRefSeqName(currentFilter->sequencenames[index-1]);
    //int offset = currentFilter->getRefSeqOffset();
}

void MainWindow::on_cmbRefSeq_2_activated(int index)
{
    ui->cmbRefSeq_3->setCurrentIndex(index);
}



void MainWindow::on_cmbRefSeq_3_activated(int index)
{
    ui->cmbRefSeq->setCurrentIndex(index);
}

void MainWindow::on_cmdSaveResults_clicked()
{
    this->saveResults();
}

void MainWindow::on_lstProteinsFiltered_itemClicked(QListWidgetItem *item)
{
    string sequence = currentFilter->getSequence(item->text().toStdString());

    ui->txtSequence->setText(sequence.c_str());

    string nogaps = currentFilter->getNoGAPSequence(item->text().toStdString());

    ui->txtSequenceNoGaps->setText(nogaps.c_str());
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
    int nComm = currentNetwork->getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableComm1->clear();

    //Modifica parâmetros
    temp = "Community: " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade->setText(temp.c_str());

    //Monta a Tabela
    vector<string> residues = currentNetwork->getResiduesComm(currComm);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));
    //ui->tableComm1->setVerticalHeaderItem(0,new QTableWidgetItem("Row1"));

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = currentNetwork->getCommAll(currComm);

    for(unsigned int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = currentNetwork->getCommXRow(currComm,i);
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
    int nComm = currentNetwork->getNumOfUtilComms();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableComm1->clear();

    //Modifica parâmetros
    temp = "Community: " + QString::number(currComm).toStdString();
    ui->lblComunidade->setText(temp.c_str());

    //Monta a Tabela
    vector<string> residues = currentNetwork->getResiduesComm(currComm-1);
    ui->tableComm1->setRowCount(residues.size());
    ui->tableComm1->setColumnCount(residues.size()+1);
    ui->tableComm1->setHorizontalHeaderItem(0,new QTableWidgetItem("All"));

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm1->setHorizontalHeaderItem(i+1, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm1->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    vector<float> corrAll = currentNetwork->getCommAll(currComm-1);

    for(unsigned int i = 0; i < residues.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString strTemp = QString::number(corrAll[i],'f',2);

        item->setData(Qt::DisplayRole,strTemp.toFloat());

        ui->tableComm1->setItem(i,0,item);

        vector<float> commRow = currentNetwork->getCommXRow(currComm-1,i);
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
    int nComm = currentNetwork->getNumOfUtilComms();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableComm2->clear();

    //Modifica parâmetros
    temp = "Community: " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_2->setText(temp.c_str());

    //Montar a Tabela
    vector<string> residues = currentNetwork->getResiduesCommPs(currComm);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(unsigned int i = 0; i < residues.size(); i++){
        vector<int> commRow = currentNetwork->getCommPsRow(currComm,i);

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
    int nComm = currentNetwork->getNumOfUtilComms();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableComm2->clear();

    //Modifica parâmetros
    temp = "Community: " + QString::number(currComm).toStdString();
    ui->lblComunidade_2->setText(temp.c_str());

    //Montar a Tabela
    vector<string> residues = currentNetwork->getResiduesCommPs(currComm -1);
    ui->tableComm2->setRowCount(residues.size());
    ui->tableComm2->setColumnCount(residues.size());

    for(unsigned int i = 0; i < residues.size(); i++){
        ui->tableComm2->setHorizontalHeaderItem(i, new QTableWidgetItem(residues[i].c_str()));
        ui->tableComm2->setVerticalHeaderItem(i,new QTableWidgetItem(residues[i].c_str()));
    }

    //Preenche a tabela
    for(unsigned int i = 0; i < residues.size(); i++){
        vector<int> commRow = currentNetwork->getCommPsRow(currComm-1,i);

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
    int nComm = currentNetwork->Communities.size();
    if(currComm == nComm ) currComm = 0;

    //Limpar tabela
    ui->tableResiduesComm->clear();

    //Modifica parâmetros
    temp = "Community: " + QString::number(currComm + 1).toStdString();
    ui->lblComunidade_3->setText(temp.c_str());

    vector<int> refSeqs;

    for(unsigned int j = 0; j < currentFilter->getRefSeqsSize(); j++){
        refSeqs.push_back(currentAlign->seqname2seqint3(currentFilter->getRefSeq(j)));
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(currentNetwork->Communities[currComm].pos.size());
    for(unsigned int i = 0; i < currentNetwork->Communities[currComm].pos.size(); i++){
        string textCab = currentNetwork->Communities[currComm].aa[i] + QString::number(currentNetwork->Communities[currComm].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < currentNetwork->Communities[currComm].pos.size(); j++){
            if(fullSequences[refSeqs[i]][currentNetwork->Communities[currComm].pos[j]]==currentNetwork->Communities[currComm].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = currentNetwork->Communities[currComm].aa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentNetwork->Communities[currComm].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][currentNetwork->Communities[currComm].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][currentNetwork->Communities[currComm].pos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentNetwork->Communities[currComm].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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
    int nComm = currentNetwork->Communities.size();
    if(currComm == 0 ) currComm = nComm;

    //Limpar tabela
    ui->tableResiduesComm->clear();

    //Modifica parâmetros
    temp = "Community: " + QString::number(currComm).toStdString();
    ui->lblComunidade_3->setText(temp.c_str());

    vector<int> refSeqs;

    for(unsigned int j = 0; j < currentFilter->getRefSeqsSize(); j++){
        refSeqs.push_back(currentAlign->seqname2seqint3(currentFilter->getRefSeq(j)));
    }

    //Cabeçalho
    ui->tableResiduesComm->setColumnCount(currentNetwork->Communities[currComm -1].pos.size());
    for(unsigned int i = 0; i < currentNetwork->Communities[currComm -1].pos.size(); i++){
        string textCab = currentNetwork->Communities[currComm -1].aa[i] + QString::number(currentNetwork->Communities[currComm-1].pos[i]+1).toStdString();
        ui->tableResiduesComm->setHorizontalHeaderItem(i,new QTableWidgetItem(textCab.c_str()));
    }

    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    ui->tableResiduesComm->setRowCount(refSeqs.size());
    for(unsigned int i = 0; i < refSeqs.size(); i++){
        ui->tableResiduesComm->setVerticalHeaderItem(i,new QTableWidgetItem(fullAlignment[refSeqs[i]].c_str()));

        for(unsigned int j = 0; j < currentNetwork->Communities[currComm -1].pos.size(); j++){
            if(fullSequences[refSeqs[i]][currentNetwork->Communities[currComm-1].pos[j]]==currentNetwork->Communities[currComm-1].aa[j]){
                QTableWidgetItem *item = new QTableWidgetItem();
                string textItem = currentNetwork->Communities[currComm-1].aa[j] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentNetwork->Communities[currComm-1].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
                item->setTextColor(QColor(0,255,0,255));
                item->setText(textItem.c_str());
                ui->tableResiduesComm->setItem(i,j,item);
            }else{
                if(fullSequences[refSeqs[i]][currentNetwork->Communities[currComm-1].pos[j]]=='-'){
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText("-");
                    ui->tableResiduesComm->setItem(i,j,item);
                }else{
                    QTableWidgetItem *item = new QTableWidgetItem();
                    string textItem = fullSequences[refSeqs[i]][currentNetwork->Communities[currComm-1].pos[j]] + QString::number(currentFilter->AlignNumbering2Sequence2(refSeqs[i]+1,currentNetwork->Communities[currComm-1].pos[j],fullSequences)+GetOffsetFromSeqName(fullAlignment[refSeqs[i]])).toStdString();
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
                            }else if(reader.isStartElement() && reader.name() == "weights"){
                                vector<float> weights;
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "value"){
                                        float value = reader.readElementText().toFloat();
                                        weights.push_back(value);
                                    }else if(reader.isEndElement() && reader.name() == "weights"){
                                        filter->setWeights(weights);
                                        break;
                                    }
                                }

                            }else if(reader.name() == "references"){
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "sequence"){
                                        string reference = reader.readElementText().toStdString();
                                        filter->addRefSeq(reference);
                                    }else if(reader.isEndElement() && reader.name() == "references"){
                                        //Atualizar no updateResults
                                        break;
                                    }
                                }
                            }else if(reader.isStartElement() && reader.name() == "conservation"){
                                while(!reader.atEnd()){
                                    reader.readNext();

                                    if(reader.isStartElement() && reader.name() == "parameters"){
                                        while(!reader.atEnd()){
                                            reader.readNext();

                                            if(reader.isStartElement()){
                                                if(reader.name() == "minimum"){
                                                    float min = reader.readElementText().toFloat();
                                                    filter->setConsMin(min);
                                                }else if(reader.name() == "alpha"){
                                                    float alpha = reader.readElementText().toFloat();
                                                    filter->setConsAlpha(alpha);
                                                }else if(reader.name() == "beta"){
                                                    float beta = reader.readElementText().toFloat();
                                                    filter->setConsBeta(beta);
                                                }
                                            }else if(reader.isEndElement() && reader.name() == "parameters"){
                                                break;
                                            }
                                        }
                                    }else if(reader.isEndElement() && reader.name() == "conservation"){

                                        filter->CalculateFrequencies();
                                        if(filter->getWeightsSize() == 0) filter->dGCalculation();
                                        else filter->dGCalculation(filter->getConsAlpha(),filter->getConsBeta());
                                        filter->dGWrite();
                                        filter->FreqWrite();

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

                                    if(reader.isStartElement() && reader.name() == "network"){
                                        Network *net = new Network(&filter->sequences,&filter->sequencenames);
                                        while(!reader.atEnd()){
                                            reader.readNext();

                                            if(reader.isStartElement()){
                                                if(reader.name() == "parameters"){
                                                    while(!reader.atEnd()){
                                                        reader.readNext();

                                                        if(reader.isStartElement()){
                                                            if(reader.name() == "min_score"){
                                                                float score = reader.readElementText().toFloat();
                                                                net->setMinScore(score);
                                                            }else if(reader.name() == "minss"){
                                                                float minss = reader.readElementText().toFloat();
                                                                net->setMinssFraction(minss);
                                                            }else if(reader.name() == "min_delta"){
                                                                float delta = reader.readElementText().toFloat();
                                                                net->setMinDelta(delta);
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

                                                            net->addCorrEdge(v1,v2,score);
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
                                                                    net->addCommunity(comms);
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
                                                                        net->addResiduesComm(residues);
                                                                        net->addCommXAll(resAll);
                                                                        net->addCommX(commX);
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
                                                                        net->addResiduesCommPs(residuesPs);
                                                                        net->addCommXPs(commXPs);
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

                                                            net->addDeltaLine(deltaLines);
                                                        }else if(reader.isEndElement() && reader.name() == "deltas"){
                                                            break;
                                                        }
                                                    }
                                                }
                                            }else if(reader.isEndElement() && reader.name() == "network"){
                                                stringstream ss;
                                                ss << fixed << setprecision(2) << net->getMinssFraction();
                                                string strMinss = ss.str();
                                                ss.str(std::string());
                                                ss << fixed << setprecision(2) << net->getMinDelta();
                                                string strDelta = ss.str();
                                                string name = to_string(net->getMinScore()) + "_" + strMinss + "_" + strDelta;
                                                net->setName(name);
                                                filter->addNetwork(net);
                                                break;
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

    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);

    if(ui->stackedWidget->currentIndex() == STACK_MAIN){
        //Desativa botões do Wizard
        changeWizardCmds(false);
        wizard = false;

        //Desativa botao voltar
        ui->cmdBack->setEnabled(false);

        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
    }else if(ui->stackedWidget->currentIndex() == STACK_RESULTS){
        this->updateResultsViews();
    }

    QString msg = "Alignment loaded with " + QString::number(currentFilter->sequences.size()) + " sequences.";
    QMessageBox::information(this,"Alignment loaded",msg);
}

void MainWindow::on_cmdRemoveFilter_clicked()
{
    if(ui->listWidget2->currentItem() == NULL){
        QMessageBox::warning(this,"Error","You must select a filter to remove.");
        return;
    }

    QString name = ui->listWidget2->currentItem()->text(0);
    if(!ui->listWidget2->currentItem()->parent()){
        //Remover um filtro
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", "Do you really want to remove the sub-alignment " + name + "?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            Filter *filter = currentAlign->getFilterByName(ui->listWidget2->currentItem()->text(0).toStdString());
            currentFilter = filter;

            if(currentFilter->getType() == 9){
                QMessageBox::warning(this,"Error","You cant remove full alignment.");
                return;
            }

            currentAlign->removeFilter(name.toStdString());
            currentFilter = NULL;
            currentNetwork = NULL;
            delete ui->listWidget2->currentItem();
            ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
        }
    }else{
        //Remover uma network
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", "Do you really want to remove the network " + name + "?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            //Network* net = currentFilter->getNetworkByName(ui->listWidget2->currentItem()->text(0).toStdString());

            currentFilter->removeNetwork(name.toStdString());
            currentNetwork = NULL;
            delete ui->listWidget2->currentItem();
            ui->listWidget2->setCurrentItem(ui->listWidget2->topLevelItem(ui->listWidget2->topLevelItemCount()-1));
        }
    }
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

    currentFilter->exportConsRes(filename,0,0.8,refSeqs,fullAlignment,fullSequences);
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

    currentFilter->exportConsRes(filename,1,0.8,refSeqs,fullAlignment,fullSequences);
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

    currentFilter->exportConsRes(filename,2,0.8,refSeqs,fullAlignment,fullSequences);
}

void MainWindow::exportCorrListTXT(){
    if(ui->listWidget->currentItem() == NULL){
        QMessageBox::warning(this,"Warning","You must select a alignment to export.");
        return;
    }

    if(currentFilter == NULL){
        QMessageBox::warning(this,"Warning","You must select an alignment to export.");
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation_list.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrGraph(filename,0);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation_list.csv"),QObject::tr("TEXT Files (*.csv)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrGraph(filename,1);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation_list.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrGraph(filename,2);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("communities.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCommList(filename,0);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("communities.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCommList(filename,1);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrTable(filename,0);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrTable(filename,1);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrTable(filename,2);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrTable(filename,0,false);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrTable(filename,1,false);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("correlation"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportCorrTable(filename,2,false);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportAdh(filename,0);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.csv"),QObject::tr("TEXT Files (*.csv)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportAdh(filename,1);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportAdh(filename,2);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("adherence.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    currentNetwork->exportAdh(filename,3);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    currentFilter->CalculateFrequencies();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("residues_communities.txt"),QObject::tr("TEXT Files (*.txt)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    vector<string> refseqs = currentFilter->getRefSeqs();
    currentNetwork->exportResComm(filename,0,fullAlignment,fullSequences,refseqs);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    currentFilter->CalculateFrequencies();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("residues_communities.xml"),QObject::tr("TEXT Files (*.xml)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    vector<string> refseqs = currentFilter->getRefSeqs();
    currentNetwork->exportResComm(filename,1,fullAlignment,fullSequences,refseqs);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    currentFilter->CalculateFrequencies();
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();

    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Export File"),exportPath.c_str() + QString("residues_communities.html"),QObject::tr("TEXT Files (*.html)"));

    if(filename == "") return;
    this->exportPath = this->getDirectory(filename.toStdString());

    vector<string> refseqs = currentFilter->getRefSeqs();
    currentNetwork->exportResComm(filename,2,fullAlignment,fullSequences,refseqs);
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

void MainWindow::changeToOpenAlignment(){
    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
}

void MainWindow::changetoFilterStack(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_FILTER);
}

void MainWindow::changeToRefSeqs(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
}

void MainWindow::changeToLoadPDBs(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_PDB);
}

void MainWindow::changeToConservationStack(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    wizard = false;

    this->changeWizardCmds(false);

    if(pdbs.size() == 0){
        ui->chkGenerateConsPDB->setChecked(false);
        emit ui->chkGenerateConsPDB->clicked(false);
    }

    if(pdbs.size() > 0) ui->chkGenerateConsPDB->setChecked(true);
    else ui->chkGenerateConsPDB->setChecked(false);

    ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
}

void MainWindow::changetoMinssStack(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    wizard = false;

    unsigned cores = omp_get_num_procs();
    ui->intNumOfCores->setValue(cores);

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_MINSS);
}

void MainWindow::changetoCorrelationStack(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
}

void MainWindow::changeToUniprotLookingTool(){
    //Validação
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(currentFilter->getConsFreqSize() > 0){
        ui->chkConserveds->setCheckable(true);
        ui->chkConserveds->setChecked(true);
    }else ui->chkConserveds->setCheckable(false);


    //if(currentNetwork->getCommListSize() > 0){
    if(!currentNetwork){
        ui->chkComm->setCheckable(true);
        ui->chkComm->setChecked(true);
    }else ui->chkComm->setCheckable(false);

    if(currentFilter->getConsFreqSize() == 0 && !currentNetwork){
        QMessageBox::warning(this,"Warning","You must run at least Conservation or Correlation programs before use this.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    wizard = false;

    this->changeWizardCmds(false);

    ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
}

void MainWindow::changeToMutationAnalysis(){
    /*DEVELOPING
    //Validação
//Validação
if(!currentFilter){
    QMessageBox::warning(this,"Warning","You must load an alignment.");
    ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
    return;
}
    if(pdbs.size() == 0){
        QMessageBox::warning(this,"Warning","You must have at least one structure file loaded.");
        ui->stackedWidget->setCurrentIndex(STACK_PDB);
        return;
    }

    wizard = false;

    this->changeWizardCmds(false);

    ui->cmbMutationRefSeq->clear();
    for(unsigned int i = 0; i < currentFilter->sequencenames.size(); i++){
        ui->cmbMutationRefSeq->addItem(currentFilter->sequencenames[i].c_str());
    }

    ui->cmbMutationStructure->clear();
    for(unsigned int i = 0; i < pdbs.size(); i++){
        Pdb* pdb = pdbs[i];

        ui->cmbMutationStructure->addItem(pdb->getId().c_str());
    }

    ui->stackedWidget->setCurrentIndex(STACK_MUTATION);
*/
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

    if(filename == ""){
        ui->cmdSaveResults->setEnabled(true);
        return;
    }

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
    emit ui->listWidget->activated(ui->listWidget->currentIndex());
}

void MainWindow::showAbout(){
    About* about = new About(this);

    about->show();
}


void MainWindow::on_cmdLook_clicked()
{
    ui->cmdLook->setEnabled(false);

    if(!ui->chkConserveds->isChecked() && !ui->chkComm->isChecked()){
        QMessageBox::warning(this,"Error","You must select at least one kind of targets.");
        ui->cmdLook->setEnabled(true);
        return;
    }

    if(ui->lstLookingRefs->selectedItems().size() == 0){
        QMessageBox::warning(this,"Error","You must select at least one protein of the list.");
        ui->cmdLook->setEnabled(true);
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
    if(minCons == 0) minCons = 0.8;
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    vector<string> fullSequences = currentAlign->getFullSequences();
    printf("%s %s",fullAlignment[0].c_str(),fullSequences[0].c_str());
    vector<string> conserved = currentFilter->getConsRes();
    currentNetwork->uniprotLook(ui->chkConserveds->isChecked(),ui->chkComm->isChecked(),proteins,idproteins,conserved,fullAlignment,fullSequences);

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

void MainWindow::on_lstProteinsMined_itemClicked(QListWidgetItem *item)
{
    ui->tableProteinsMined1->clearContents();
    string name = item->text().split(' ')[0].toStdString();
    vector<int> indexes;

    //Acha a entrada uniprot selecionada
    for(unsigned int j = 0; j < currentNetwork->getUniprotMinedSize(); j++){
        if(currentNetwork->getUniprotEntryName(j) == name){
            indexes.push_back(j);
        }
    }

    for(int j : indexes){
        string function = "Function: " + currentNetwork->getUniprotFunction(j);
        ui->lblUniprotFunction->setText(function.c_str());
        ui->lblUniprotFunction->setWordWrap(true);

        ui->tableProteinsMined1->setRowCount(currentNetwork->getUniprotEntryNofFeatures(j));
        for(unsigned int k = 0; k < currentNetwork->getUniprotEntryNofFeatures(j); k++){
            Feature *f = currentNetwork->getUniprotFeature(j,k);

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
    }
    //Ajusta tamanho das colunas
    ui->tableProteinsMined1->resizeColumnsToContents();
}

void MainWindow::on_treeMinerComms_clicked(const QModelIndex &index)
{
    ui->tableProteinsMined2->clearContents();

    QString item = index.data().toString().split(' ')[0];

    if(!item.startsWith("Comm") && !item.startsWith("Conservation")){
        vector<Uniprot*> features = currentNetwork->getAllResidueFeatures(item.toStdString());

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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookProt(filename,0);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookProt(filename,1);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookProt(filename,2);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookProt(filename,3);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }
    vector<string> conserved = currentFilter->getConsRes();

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookComm(filename,0,conserved);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }
    vector<string> conserved = currentFilter->getConsRes();

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookComm(filename,1,conserved);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }
    vector<string> conserved = currentFilter->getConsRes();

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookComm(filename,2,conserved);
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
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You may run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You may run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
        return;
    }
    vector<string> conserved = currentFilter->getConsRes();

    QString filename = QFileDialog::getExistingDirectory(this, tr("Choose a directory to save the results file"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    currentNetwork->exportLookComm(filename,3,conserved);
}

void MainWindow::changeToCreateCommunity(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    wizard = false;
    ui->cmbComm->clear();
    ui->lstManageComms->clear();

    this->changeWizardCmds(false);

    unsigned int nOfComms = currentNetwork->getCommListSize();

    //Validação
    if(nOfComms == 0){
        QMessageBox::warning(this,"Warning","You must run correlation");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    for(unsigned int j = 1; j <= nOfComms; j++)
        ui->cmbComm->addItem(QString::number(j));

    ui->stackedWidget->setCurrentIndex(STACK_MANAGE_COMMS);
}


void MainWindow::on_cmbComm_currentIndexChanged(int index)
{
    if(index >= 0){
        vector<string> comms = currentNetwork->getCommunitie(index);

        ui->lstManageComms->clear();

        for(unsigned int j = 0; j < comms.size(); j++){
            ui->lstManageComms->addItem(comms[j].c_str());
        }
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
    QChar aa = text.at(0);
    string pos = text.toStdString().substr(1);

    if (ok && !text.isEmpty()){
        if(!this->isaa(aa.toLatin1())){
            QMessageBox::warning(this,"Warning","Invalid pair amino acid/position.");
            return;
        }

        if(!this->isInt(pos)){
            QMessageBox::warning(this,"Warning","Invalid pair amino acid/position.");
            return;
        }

    }

    if(stoi(pos) > currentFilter->sequences[0].size()){
        QMessageBox::warning(this,"Warning","Invalid position");
        return;
    }

    int nc = ui->cmbComm->currentIndex();

    currentNetwork->addItemToCommunity(text.toStdString(),nc);

    //Atualizar campo
    vector<string> comms = currentNetwork->getCommunitie(nc);

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

    currentNetwork->removeItemOfCommunity(nc,residueIndex);

    //Atualizar campo
    vector<string> comms = currentNetwork->getCommunitie(nc);

    ui->lstManageComms->clear();

    for(unsigned int j = 0; j < comms.size(); j++){
        ui->lstManageComms->addItem(comms[j].c_str());
    }
}

void MainWindow::on_cmdNewComm_clicked()
{
    vector<string> newComm;
    currentNetwork->addCommunity(newComm);

    //Atualizar campos
    int nOfComms = currentNetwork->getCommListSize();

    ui->cmbComm->addItem(QString::number(nOfComms));

    ui->cmbComm->setCurrentIndex(nOfComms-1);
}

void MainWindow::changeToListOfSequences(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }

    //Resetar campos de resultado
    ui->lstProteinsFiltered->clear();
    ui->txtSequence->clear();
    ui->txtSequenceNoGaps->clear();

    this->listSequences();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_SEQLIST);
}

bool MainWindow::generateSunburst(vector<string> sequencenames){
    string url = "http://www.biocomp.icb.ufmg.br:8080/pfstats/webapi/pfam/taxondata";
    string text = "";

    if(sequencenames.size() == 0){
        for(unsigned int i = 0; i < currentFilter->sequencenames.size(); i++){
            text += split(currentFilter->sequencenames[i],'/')[0] + "\n";
        }
    }else{
        for(unsigned int i = 0; i < sequencenames.size(); i++){
            text += split(sequencenames[i],'/')[0] + "\n";
        }
    }

    QProgressDialog progress("Accessing webservice...", "Abort", 0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();
    if(progress.wasCanceled()){
        ui->cmdPDBFetch->setEnabled(true);
        return false;
    }

    QByteArray const data = QString::fromStdString(text).toUtf8();

    QNetworkRequest request(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("text/plain; charset=utf-8"));
    QNetworkAccessManager manager;
    QNetworkReply *response(manager.post(request,data));
    //QNetworkReply* response(manager.get(request));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    if(progress.wasCanceled()){
        return false;
    }
    QString html = response->readAll();

    if(html.contains("302 Found") || html.contains("error") || html == ""){
        printf("\n%s",html.toStdString().c_str());
        QMessageBox::warning(this,"Fetching Failed","Error while trying to connect the webservice");
        return false;
    }else{
        string pathcsv = libpath + "sunburst/clades.csv";
        string pathhtml = libpath + "sunburst/sunburst.html";
        QFile indexHTML(pathcsv.c_str());
        indexHTML.open(QIODevice::WriteOnly);
        QTextStream out(&indexHTML);

        out << html;

        //ATUALIZA ARQUIVO
        indexHTML.close();
        QFile file(pathhtml.c_str());
        file.open(QIODevice::ReadOnly);
        QFileInfo info(file);
        string absPath = info.absoluteFilePath().toStdString();
        string localUrl = "file:///" + absPath;
        ui->webTaxons->setUpdatesEnabled(true);
        ui->webTaxons->load(QUrl(localUrl.c_str()));
        QWebSettings *websettings = QWebSettings::globalSettings();
        //websettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
        websettings->setAttribute(QWebSettings::JavascriptEnabled,true);
        websettings->clearMemoryCaches();
        QWebFrame *frame = ui->webTaxons->page()->mainFrame();
        frame->evaluateJavaScript("displaymessage()");
    }

    progress.close();

    return true;
}

void MainWindow::changeToTaxonomicView(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }

    if(!this->generateSunburst(vector<string>())) return;
    //printf("%s",csv.c_str());

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_TAXVIEW);
}

void MainWindow::changeToConservationFrequence(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(currentFilter->getConsFreqSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
        return;
    }

    //Resetar campos de resultado
    ui->tableFreq->clearContents();

    this->tableFreq();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CONSFREQ);
}

void MainWindow::changeToConservationPercentage(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(currentFilter->getConsFreqPercSize() == 0){
        QMessageBox::warning(this,"Warning","You must run conservation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
        return;
    }

    //Resetar campos de resultado
    ui->tableFreqPerc->clearContents();

    this->tableFreqPerc();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_FREQPERC);
}

void MainWindow::changeToConservedResidues(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","You must select some reference sequences.");
        ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
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
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    //Resetar campos de resultado
    ui->treeCorrelation->clear();
    ui->cmbRefSeq_2->setCurrentIndex(0);
    ui->cmbRefPdb_2->clear();
    if(pdbs.size() == 0){
        ui->cmbRefPdb_2->setEnabled(false);
        ui->cmdUpdateGraphPdbNumbering->setEnabled(false);
    }else{
        for(unsigned int i = 0; i < pdbs.size(); i++){
            Pdb* pdb = pdbs[i];
            ui->cmbRefPdb_2->addItem(pdb->getId().c_str());
        }
        ui->cmbRefPdb_2->setEnabled(true);
        ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
    }

    this->correlationList();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRLIST);
}

void MainWindow::changeToCorrelationGraph(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    ui->cmdHideShowAntiCorr->setText("Hide Anti-Correlations");

    createCorrelationJSON();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRGRAPH);
}

void MainWindow::changeToCommunitiesGraphs(){
    /*//OLD
    //Validação
    if(currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    this->communitiesGraphs();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_COMMGRAPH);
    */
}

void MainWindow::changeToCorrelationBetweenComms(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    this->corrBetweenComms();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_DELTAGRAPH);
}

void MainWindow::changeToPDBVisualization(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(currentFilter->getConsPDBPath() == ""){
        QMessageBox::warning(this,"Warning","You must run conservation method and send a PDB file.");
        ui->stackedWidget->setCurrentIndex(STACK_CONSERVATION);
        return;
    }

    this->consVisualization();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CONSPDB);
}

void MainWindow::changeToPDBVisualization2(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getCommPDBPath() == ""){
        QMessageBox::warning(this,"Warning","You must run correlation method and send a PDB file.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    this->commVisualization();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_COMMPDB);
}

void MainWindow::changeToAlphabetReduction(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    emit ui->cmbAlphabetList->currentIndexChanged(0);
    ui->stackedWidget->setCurrentIndex(STACK_ALPHABET);
}

void MainWindow::changeToGenSubAlignments(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }

    ui->cmbSubAlignComms->clear();
    ui->txtSubAlignName->clear();
    ui->txtResiduesSubAlign->clear();

    //if(currentNetwork->getCommListSize() > 0){
    if(!currentNetwork){
        ui->cmbSubAlignComms->addItem(" ");
        for(unsigned int i = 0; i < currentNetwork->getCommListSize(); i++){
            QString txt = "Community " + QString::number(i+1);
            ui->cmbSubAlignComms->addItem(txt);
        }
    }

    ui->stackedWidget->setCurrentIndex(STACK_SUBALIGN);
}

void MainWindow::changeToAddSequence(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    ui->cmbAddSeq1->clear();
    ui->cmbAddSeq2->clear();
    ui->lstAddSeq1->clear();
    ui->lstAddSeq2->clear();

    vector<Filter*> filters = currentAlign->getFilters();
    int idFull = 0;

    for(unsigned int i = 0; i < filters.size(); i++){
        Filter* f = filters[i];

        if(f->getType() == 9) idFull = i;

        ui->cmbAddSeq1->addItem(f->getName().c_str());
        ui->cmbAddSeq2->addItem(f->getName().c_str());
    }

    ui->cmbAddSeq1->setCurrentIndex(idFull);
    emit ui->cmbAddSeq1->activated(ui->cmbAddSeq1->currentText());
    ui->cmbAddSeq2->setCurrentIndex(ui->cmbAddSeq2->count() -1);
    emit ui->cmbAddSeq2->activated(ui->cmbAddSeq2->currentText());

    ui->stackedWidget->setCurrentIndex(STACK_ADDSEQ);
}

void MainWindow::changeToCommunitiesList(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    //Resetar campos de resultado
    ui->treeCorrelationComm->clear();
    ui->cmbRefSeq_3->setCurrentIndex(0);
    ui->cmbRefPdb_3->clear();

    if(pdbs.size() == 0){
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(false);
        ui->cmbRefPdb_3->setEnabled(false);
    }else{
        for(unsigned int i = 0; i < pdbs.size(); i++){
            Pdb* pdb = pdbs[i];
            ui->cmbRefPdb_3->addItem(pdb->getId().c_str());
        }
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(true);
        ui->cmbRefPdb_3->setEnabled(true);
    }

    this->communitiesList();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_COMMLIST);
}

void MainWindow::changeToCorrelationInPerc(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    //Resetar campos de resultado
    ui->tableComm1->clear();

    this->corrTable1();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRPERC);
}

void MainWindow::changeToCorrelationInLogP(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    //Resetar campos de resultado
    ui->tableComm2->clear();

    this->corrTable2();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_CORRLOG);
}

void MainWindow::changeToAdherenceMatrix(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation method.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    //Resetar campos de resultado
    ui->tableAdherence->clear();

    this->adh();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_ADHERENCE);
}

void MainWindow::changeToResiduesOfCommunities(){
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(currentFilter->getRefSeqsSize() == 0){
        QMessageBox::warning(this,"Warning","You must have some reference sequences.");
        ui->stackedWidget->setCurrentIndex(STACK_REFSEQS);
        return;
    }

    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlatio methods.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }

    //Resetar campos de resultado
    ui->tableResiduesComm->clear();

    this->showResiduesComm();

    ui->stackedWidget->setCurrentIndex(STACK_RESULTS);
    ui->stackedWidget2->setCurrentIndex(STACK_RESULT_RESCOMM);
}

void MainWindow::changeToULGroupedByProteins(){
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You must run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
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
    //Validação
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
        return;
    }
    if(!currentNetwork){
        QMessageBox::warning(this,"Warning","You must run correlation analysis.");
        ui->stackedWidget->setCurrentIndex(STACK_CORRELATION);
        return;
    }
    if(currentNetwork->getUniprotMinedSize() == 0){
        QMessageBox::warning(this,"Warning","You must run Uniprot Look-up.");
        ui->stackedWidget->setCurrentIndex(STACK_UNIPROT);
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
    if(!currentFilter){
        QMessageBox::warning(this,"Warning","You must load an alignment.");
        ui->stackedWidget->setCurrentIndex(STACK_ALIGNMENT);
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

    this->updateRefSeqsCompleters();

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

    this->updateRefSeqsCompleters();

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

    this->updateRefSeqsCompleters();

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

    this->updateRefSeqsCompleters();

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

    this->updateRefSeqsCompleters();

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
    this->output();

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
            for(unsigned int i = 0; i < ui->listWidget2->topLevelItemCount(); i++){
                if(ui->listWidget2->topLevelItem(i)->text(0) == text){
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
        oldChars.push_back("GTSYPH");
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

    if(newFilter){//ACRESCENTAR O QTREEWIDGETITEM
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
        filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());

        filter->applyAlphabetReduction(oldChars,newChars);

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
        treeItem->setText(0,alignname.c_str());
        filter->setQtreeWidgetItem(treeItem);

        currentAlign->addFilter(filter);

        ui->listWidget2->setCurrentItem(treeItem);
    }else{
        currentFilter->applyAlphabetReduction(oldChars,newChars);
        currentFilter->setAlphabet(type);
        currentFilter->addSequences(currentAlign->sequencenames,currentAlign->sequences);
    }

    string msg = "The sequence alphabet was reduced using the " + type + " method.";
    QMessageBox::information(this,"Alhabet Reduced",msg.c_str());

    ui->cmdApplyAlphabetReduction->setEnabled(true);
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
        ui->txtPDBName_2->setEnabled(true);
        ui->txtChain_2->setEnabled(true);
        ui->lstPDBsLoaded_2->setEnabled(true);
    }else{
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
        ui->txtPdbId->setFocus();
        ui->cmdPDBFetch->setEnabled(true);
        return;
    }

    QProgressDialog progress("Accessing webservice...", "Abort", 0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

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

    if(progress.wasCanceled()){
        ui->cmdPDBFetch->setEnabled(true);
        return;
    }

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

        if(progress.wasCanceled()){
            ui->cmdPDBFetch->setEnabled(true);
            return;
        }

        currentPDBContent = pdb.toStdString();
        this->pdbweb = url.toStdString();
    }

    progress.close();

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
    string refseq = ui->cmbRefSeq_4->currentText().toStdString();

    //Validação
    if(refseq == " "){
        QMessageBox::warning(this,"Warning","You must set a reference sequence for this structure.");
        ui->cmbRefSeq_4->setFocus();
        ui->cmdLoadPDB->setEnabled(true);
        return;
    }

    if(ui->txtChainPDB->text() == ""){
        QMessageBox::warning(this,"Warning","You must set a chain for this structure.");
        ui->cmdLoadPDB->setEnabled(true);
        ui->txtChainPDB->setFocus();
        ui->txtChainPDB->setFocus();
        return;
    }

    if(ui->txtChainPDB->text().length() > 1){
        QMessageBox::warning(this,"Warning","Chain must be a one letter character");
        ui->cmdLoadPDB->setEnabled(true);
        ui->txtChainPDB->setFocus();
        ui->txtChainPDB->setFocus();
        return;
    }

    if(ui->txtPdbId->text() != ""){
        //Já está na memoria
        if(currentPDBContent == ""){
            QMessageBox::warning(this,"Warning","You must fetch your PDB before load.");
            ui->txtPdbId->setFocus();
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
        char chain = toupper(ui->txtChainPDB->text().toStdString()[0]);

        pdb->setRefseq(refseq);
        pdb->setRefseq_chain(chain);
        pdb->setRefSeqId(ui->cmbRefSeq_4->currentIndex());
        //pdb->setResiduesSeqNumber(chain);


        //Verify if pdb and sequence align
        currentFilter->convertLowerDots();
        string currseq = currentFilter->getNoGAPSequence(ui->cmbRefSeq_4->currentIndex()-1);
        string pdbseq = pdb->getPDBSequence(chain);
        int score = pdb->setResiduesSeqNumber(currseq,chain,currentFilter->sequences[ui->cmbRefSeq_4->currentIndex()-1]);

        if(score <= 0){
            QMessageBox::StandardButton mbox;
            mbox = QMessageBox::question(this, "Low alignment Score", "The alignment between your structure and reference sequence shows a very low score. It may occur because the setting of the wrong structure, reference sequence, chain or the pdb and sequence has a very divergent sizes. Do you really want to load the structure?",
                                        QMessageBox::Yes|QMessageBox::No);
            if (mbox == QMessageBox::No) {
                ui->cmdLoadPDB->setEnabled(true);
                return;
            }
        }

        ui->lstPDBsInMemory->addItem(pdbname.c_str());

        pdbs.push_back(pdb);

        ui->lstRecomendedPDBs->clear();
        ui->lstPDBsLoaded_2->clear();

        for(unsigned int i = 0; i < pdbs.size(); i++){
            Pdb* structure = pdbs[i];
            ui->lstRecomendedPDBs->addItem(structure->getId().c_str());
            ui->lstPDBsLoaded_2->addItem(structure->getId().c_str());
        }

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
    }else{        
        ui->txtPDBName_2->setEnabled(false);
        ui->txtChain_2->setEnabled(false);
        ui->lstPDBsLoaded_2->setEnabled(false);
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
        url += "haspdb/";

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
            ui->txtFilterRefSeq->setFocus();
            ui->cmdFilterRefSeqs->setEnabled(true);
            return;
        }else{
            if(score < 1 || score > 5){
                QMessageBox::warning(this,"Error","The annotation score must be a value between 1 and 5");
                ui->txtFilterRefSeq->setFocus();
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
            QMessageBox::warning(this,"Error","You must inform what taxon will generate the filtered alignment.");
            ui->txtFilterRefSeq->setFocus();
            ui->cmdFilterRefSeqs->setEnabled(true);
            return;
        }

        url += "taxon-filter/" + ui->txtFilterRefSeq->text().toStdString();

        break;
    }
    }

    QProgressDialog progress("Accessing webservice...", "Abort", 0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(int i = 0; i < ui->lstRefSeqs->count(); i++){
        if(progress.wasCanceled()){
            ui->cmdFilterRefSeqs->setEnabled(true);
            return;
        }
        string seqname = ui->lstRefSeqs->item(i)->text().toStdString();
        vector<string> temp = split(seqname,'/');
        post_content += temp[0] + "\n";
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

    if(progress.wasCanceled()){
        ui->cmdFilterRefSeqs->setEnabled(true);
        return;
    }

    if(result == ""){
        string msg = "The query returned a null content. It may be caused by one of the following cases:\n";
        msg += "-None sequence match with the search.\n";
        msg += "-You are having problems with your internet connection.\n";
        msg += "-Our servers are down. You can check it by accessing www.biocomp.icb.ufmg.br";
        QMessageBox::information(this,"Null result",msg.c_str());
        ui->cmdFilterRefSeqs->setEnabled(true);
        return;
    }

    vector<string> filtered = this->split(result.toStdString(),'\n');

    int count = 0;
    if(ui->cmbFilterRefseq->currentIndex() == 0){
        for(unsigned int i = 0; i < filtered.size(); i++){
            string protname = this->split(filtered[i],'\t')[0];
            printf("%s\n",protname.c_str());
            for(int j = 0; j < ui->lstRefSeqs->count(); j++){
                if(progress.wasCanceled()){
                    ui->cmdFilterRefSeqs->setEnabled(true);
                    return;
                }

                string protname2 = this->split(ui->lstRefSeqs->item(j)->text().toStdString(),'/')[0];
                if(protname == protname2){
                    ui->lstRefSeqSelected->addItem(ui->lstRefSeqs->item(j)->text());
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
                if(progress.wasCanceled()){
                    ui->cmdFilterRefSeqs->setEnabled(true);
                    return;
                }

                string protname2 = this->split(ui->lstRefSeqs->item(j)->text().toStdString(),'/')[0];
                if(filtered[i] == protname2){
                    ui->lstRefSeqSelected->addItem(ui->lstRefSeqs->item(j)->text());
                    delete ui->lstRefSeqs->item(j);
                    if(j > 0) j--;
                    count ++;
                    break;
                }
            }
        }
    }

    this->updateRefSeqsCompleters();

    progress.close();
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

    QProgressDialog progress("Accessing webservice...", "Abort", 0,0);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(int i = 0; i < ui->lstLookingRefs->count(); i++){
        if(progress.wasCanceled()){
            ui->cmdLookingFilter->setEnabled(true);
            return;
        }
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

    if(result == ""){
        string msg = "The query returned a null content. It may be caused by one of the following cases:\n";
        msg += "-None sequence match with the search.\n";
        msg += "-You are having problems with your internet connection.\n";
        msg += "-Our servers are down. You can check it by accessing www.biocomp.icb.ufmg.br";
        QMessageBox::information(this,"Null result",msg.c_str());
        ui->cmdLookingFilter->setEnabled(true);
        return;
    }

    vector<string> filtered = this->split(result.toStdString(),'\n');

    int count = 0;
    if(ui->cmbLookingFilter->currentIndex() == 0){
        for(unsigned int i = 0; i < filtered.size(); i++){
            if(progress.wasCanceled()){
                ui->cmdLookingFilter->setEnabled(true);
                return;
            }

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
            if(progress.wasCanceled()){
                ui->cmdLookingFilter->setEnabled(true);
                return;
            }

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

    progress.close();

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
        ui->chkIntermediate->setChecked(false);
        ui->chkIntermediate->setEnabled(true);
        ui->txtFilterName->setEnabled(true);
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
        ui->chkIntermediate->setChecked(false);
        ui->chkIntermediate->setEnabled(true);
        ui->txtFilterName->setEnabled(true);
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
        ui->chkIntermediate->setChecked(false);
        ui->chkIntermediate->setEnabled(false);
        ui->txtFilterName->setEnabled(false);
        ui->cmdApplyFilter->setEnabled(true);
    }
}

void MainWindow::on_listWidget2_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    string filtername;
    string networkname = "";

    //Verifica se o nó selecionado é um filtro ou uma rede, se for rede retorna seu filtro
    if(current == NULL) return;

    if(!current->parent()){
        filtername = current->text(0).toStdString();
    }else{
        networkname = current->text(0).toStdString();
        filtername = current->parent()->text(0).toStdString();
    }

    //Recupera e armazena o filtro
    Filter *filter = currentAlign->getFilterByName(filtername);
    currentFilter = filter;

    //Recupera e armazena a network atual
    if(networkname == "") currentNetwork = currentFilter->getNetwork(0);
    else currentNetwork = currentFilter->getNetworkByName(networkname);

    //Limpa campos de resultados
    ui->cmbRefSeq_2->clear();
    ui->cmbRefSeq_2->addItem("Alignment");
    ui->cmbRefSeq_3->clear();
    ui->cmbRefSeq_3->addItem("Alignment");
    ui->cmbRefSeq_4->clear();
    ui->cmbRefSeq_4->addItem("");
    ui->lstProteinsFiltered->clear();
    ui->lstLookingRefs->clear();
    ui->cmbComm->clear();
    ui->lstManageComms->clear();
    ui->cmbRefPdb_2->clear();
    ui->cmbRefPdb_3->clear();
    ui->lstRecomendedPDBs->clear();
    ui->lstPDBsLoaded_2->clear();

    //Label na tela do minss
    ui->lblNseq->setText("Number of sequences in the alignment: " + QString::number(filter->getSequencesCount()));


    //Add filtered sequences
    for(unsigned int i = 0; i < filter->getSequencesCount(); i++){
        string proteinName = filter->getSequenceName(i);
        ui->cmbRefSeq_4->addItem(proteinName.c_str());
        ui->lstProteinsFiltered->addItem(proteinName.c_str());
    }

    //Add Full Alignment sequences
    vector<string> fullAlignment = currentAlign->getFullAlignment();
    for(unsigned int i = 0; i < fullAlignment.size(); i++){
        vector<string> splitVec = this->split(fullAlignment[i],'/');
        ui->cmbRefSeq_2->addItem(QString::fromStdString(fullAlignment[i]));
        ui->cmbRefSeq_3->addItem(QString::fromStdString(fullAlignment[i]));
        //ui->cmbRefSeq_4->addItem(QString::fromStdString(splitVec[0]));
        ui->lstLookingRefs->addItem(QString::fromStdString(splitVec[0]));
    }

    //Add PDBS to comm and corr lists
    if(pdbs.size() == 0){
        ui->cmbRefPdb_2->setEnabled(false);
        ui->cmdUpdateGraphPdbNumbering->setEnabled(false);
        ui->cmbRefPdb_3->setEnabled(false);
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(false);
    }else{
        for(unsigned int i = 0; i < pdbs.size(); i++){
            Pdb* pdb = pdbs[i];
            ui->cmbRefPdb_2->addItem(pdb->getId().c_str());
            ui->cmbRefPdb_3->addItem(pdb->getId().c_str());
            ui->lstRecomendedPDBs->addItem(pdb->getId().c_str());
            ui->lstPDBsLoaded_2->addItem(pdb->getId().c_str());
        }
        ui->cmbRefPdb_2->setEnabled(true);
        ui->cmdUpdateGraphPdbNumbering->setEnabled(true);
        ui->cmbRefPdb_3->setEnabled(true);
        ui->cmdUpdateGraphPdbNumbering_2->setEnabled(true);
    }

    //Mudanças de filtros em páginas especificas
    if(ui->stackedWidget->currentIndex() == STACK_MANAGE_COMMS){
        unsigned int nOfComms = currentNetwork->getCommListSize();
        ui->cmbComm->clear();

        for(unsigned int j = 1; j <= nOfComms; j++)
            ui->cmbComm->addItem(QString::number(j));
    }else if(ui->stackedWidget->currentIndex() == STACK_RESULTS){
        this->updateResultsViews();
    }else if(ui->stackedWidget->currentIndex() == STACK_MUTATION){
        changeToMutationAnalysis();
    }

    //Prepara tela de conservação para usar pesos ou frequências
    if(currentFilter->getWeightsSize() == 0){
        ui->label_28->setEnabled(false);
        ui->label_31->setEnabled(false);
        ui->txtAlpha->setEnabled(false);
        ui->txtBeta->setEnabled(false);
    }else{
        ui->label_28->setEnabled(true);
        ui->label_31->setEnabled(true);
        ui->txtAlpha->setEnabled(true);
        ui->txtBeta->setEnabled(true);
    }

    ui->cmbRefSeq_2->setCurrentIndex(0);
    ui->cmbRefSeq_2->activated(ui->cmbRefSeq_2->currentText());
    ui->cmbRefSeq_3->setCurrentIndex(0);
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

void MainWindow::comm2Align(){
    int members = 0;
    QProgressDialog progress("Loading the alignment...","Cancel",0,currentNetwork->Communities.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    for(unsigned int i = 0; i < currentNetwork->Communities.size(); i++){
        progress.setValue(i);
        if(progress.wasCanceled()) return;

        string name = currentFilter->getName() + "_comm" + to_string(i+1);
        Filter* filter = new Filter(name,currentFilter->getAlphabet(),3);//ACRESCENTAR O QTREEWIDGETITEM

        for(unsigned int j = 0; j < currentNetwork->sequences->size(); j++){
            members = 0;

            for(unsigned int k = 0; k < currentNetwork->Communities[i].pos.size(); k++){
                if(currentNetwork->sequences->at(j).c_str()[currentNetwork->Communities[i].pos[k]] == currentNetwork->Communities[i].aa[k])
                    members++;
            }
            if(members == currentNetwork->Communities[i].pos.size())
                filter->addSequences(currentNetwork->sequencenames->at(j),currentNetwork->sequences->at(j));
        }

        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
        treeItem->setText(0,name.c_str());
        filter->setQtreeWidgetItem(treeItem);
        currentAlign->addFilter(filter);
        //ui->listWidget2->addItem(name.c_str());
    }

    progress.close();
}

void MainWindow::updateRefSeqsCompleters(){
    QStringList refseqs, selRefseqs;

    for(unsigned int i = 0; i < ui->lstRefSeqs->count(); i++)
        refseqs.append(ui->lstRefSeqs->item(i)->text());

    for(unsigned int i = 0; i < ui->lstRefSeqSelected->count(); i++)
        selRefseqs.append(ui->lstRefSeqSelected->item(i)->text());

    QCompleter* refseqsCompleter = new QCompleter(refseqs);
    refseqsCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    QCompleter* selRefseqsCompleter = new QCompleter(selRefseqs);
    selRefseqsCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->txtSecRefSeqs->setCompleter(refseqsCompleter);
    ui->txtSelectedSecRefseqs->setCompleter(selRefseqsCompleter);
}

void MainWindow::on_txtSecRefSeqs_editingFinished()
{
    QString text = ui->txtSecRefSeqs->text();

    for(unsigned int i = 0; i < ui->lstRefSeqs->count(); i++){
        QString item = ui->lstRefSeqs->item(i)->text();

        if(item.contains(text,Qt::CaseInsensitive)){
            ui->lstRefSeqs->item(i)->setSelected(true);
            ui->lstRefSeqs->setCurrentItem(ui->lstRefSeqs->item(i));
            ui->lstRefSeqs->setFocus();
            return;
        }
    }
}

void MainWindow::on_txtSelectedSecRefseqs_editingFinished()
{
    QString text = ui->txtSelectedSecRefseqs->text();

    for(unsigned int i = 0; i < ui->lstRefSeqSelected->count(); i++){
        QString item = ui->lstRefSeqSelected->item(i)->text();

        if(item.contains(text,Qt::CaseInsensitive)){
            ui->lstRefSeqSelected->item(i)->setSelected(true);
            ui->lstRefSeqSelected->setCurrentItem(ui->lstRefSeqSelected->item(i));
            ui->lstRefSeqSelected->setFocus();
            return;
        }
    }
}

void MainWindow::freeMem(){
    currentAlign = NULL;
    currentFilter = NULL;

    for(unsigned int i = 0; i < alinhamentos.size(); i++){
        alinhamentos[i].clear();
    }
    alinhamentos.shrink_to_fit();

}

void MainWindow::renameFilter(){
    if(ui->listWidget2->currentItem() == NULL){
        QMessageBox::warning(this,"Warning","You must select a filter to remove.");
        return;
    }

    if(!ui->listWidget2->currentItem()->parent()){
        QTreeWidgetItem *currentItem = ui->listWidget2->currentItem();

        if(currentItem->text(0) == "Full Alignment"){
            QMessageBox::warning(this,"Warning","You can't rename the Full Alignment.");
            return;
        }

        bool ok;
        QString text = QInputDialog::getText(this, tr("New filter name"),
                                             tr("Type the new filter name:"), QLineEdit::Normal,
                                             ui->listWidget2->currentItem()->text(0), &ok);
        if (ok && !text.isEmpty()){
            if(!currentAlign->verifyValidFilterName(text.toStdString())){
                QMessageBox::warning(this,"Warning","Invalid filter name.");
                return;
            }

            currentFilter->setName(text.toStdString());
            ui->listWidget2->currentItem()->setText(0,text);
        }
    }else{
        QMessageBox::warning(this,"Warning","You can't rename a network.");
        return;
    }
}

void MainWindow::removeFilter(){
    on_cmdRemoveFilter_clicked();
}

void MainWindow::duplicateFilter(){
    if(ui->listWidget2->currentItem() == NULL){
        QMessageBox::warning(this,"Warning","You must select a filter to remove.");
        return;
    }

    if(!ui->listWidget2->currentItem()->parent()){
        //Filtro

        //Monta o novo nome
        int sufixNumber = 2;
        string possibleName = currentFilter->getName() + to_string(sufixNumber);
        while(true){
            possibleName = currentFilter->getName() + to_string(sufixNumber);
            if(currentAlign->verifyValidFilterName(possibleName)){
                break;
            }else
                sufixNumber++;
        }

        int type;
        if(currentFilter->getType() == 9) type = 7;
        else type = currentFilter->getType();

        Filter *filter = new Filter(possibleName,currentFilter->getAlphabet(),type);//ACRESCENTAR O QTREEWIDGETITEM
        filter->setRefSeq(currentFilter->getRefSeq());
        filter->setTaxon(currentFilter->getTaxon());
        filter->setMinId(currentFilter->getMinId());
        filter->setMinOcc(currentFilter->getMinOcc());
        filter->setMaxId(currentFilter->getMaxId());
        filter->addSequences(currentFilter->getSequenceNames(),currentFilter->getSequences());
        filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
        treeItem->setText(0,possibleName.c_str());
        filter->setQtreeWidgetItem(treeItem);
        for(unsigned int i = 0; i < currentFilter->countNetworks(); i++){//Testar duplicar, depois deletar uma network e ver se o original mantem
            Network *net = new Network(&filter->sequences,&filter->sequencenames,currentFilter->getNetwork(i));
            filter->addNetwork(net);
            QTreeWidgetItem *child = new QTreeWidgetItem();
            child->setText(0,net->getName().c_str());
            treeItem->addChild(child);
        }
        currentAlign->addFilter(filter);
        ui->listWidget2->setCurrentItem(treeItem);
    }else{
        //Network
        QMessageBox::warning(this,"Warning","You can't duplicate a network.");
        return;
    }
}

void MainWindow::on_cmdSubAlignAddRes_clicked()
{
    string text = "";
    if(ui->cmbSubAlignComms->currentText() != " " && ui->cmbSubAlignComms->currentText() != ""){
        vector<string> residues = currentNetwork->getCommunitie(ui->cmbSubAlignComms->currentIndex()-1);

        for(unsigned int i = 0; i < residues.size(); i++){
            text += residues[i] + "\n";
        }
    }

    ui->txtResiduesSubAlign->setText(text.c_str());
}

void MainWindow::on_cmdGenerateSubAlignment_clicked()
{
    ui->cmdGenerateSubAlignment->setEnabled(false);
    string name = ui->txtSubAlignName->text().toStdString();

    if(!currentAlign->verifyValidFilterName(name)){
        QMessageBox::warning(this,"Invalid Filter Name","Invalid filter name.");
        ui->txtSubAlignName->setFocus();
        ui->cmdGenerateSubAlignment->setEnabled(true);
        return;
    }

    if(ui->txtResiduesSubAlign->toPlainText() == ""){
        QMessageBox::warning(this,"Invalid Dataset","The residues list is blank.");
        ui->txtResiduesSubAlign->setFocus();
        ui->cmdGenerateSubAlignment->setEnabled(true);
        return;
    }

    vector<string> lines = split(ui->txtResiduesSubAlign->toPlainText().toStdString(),'\n');
    vector<string> sequences, sequencenames;
    vector<tuple<char,int> > residuesHits;
    int hits;
    int count = 0;
    for(unsigned int i = 0; i < lines.size(); i++){
        string res = lines[i];
        if(res != ""){
            string aa(1,res[0]);
            string strPos = res.substr(1);
            QString temp = strPos.c_str();
            bool ok;
            int pos = temp.toInt(&ok);
            if(ok){
                if(pos <= currentFilter->sequences[0].size() && pos > 0){
                    std::tuple<char,int> tup (aa[0],pos);
                    residuesHits.push_back(tup);
                }
            }
            count++;
        }
    }

    int numOfValidHits = count * ui->txtSubAlignHitRate->value();

    for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
        hits = 0;
        for(unsigned int j = 0; j < residuesHits.size(); j++){
            char aa = std::get<0>(residuesHits[j]);
            int pos = std::get<1>(residuesHits[j]);

            if(currentFilter->sequences[i][pos-1] == aa)
                hits++;
        }

        if(hits >= numOfValidHits){
            sequences.push_back(currentFilter->sequences[i]);
            sequencenames.push_back(currentFilter->sequencenames[i]);
        }
    }

    if(sequences.size() == 0){
        QMessageBox::warning(this,"Null Alignment","The query result in a null alignment.");
        ui->cmdGenerateSubAlignment->setEnabled(true);
        return;
    }else{
        Filter *filter = new Filter();
        filter->setName(name);
        filter->setAlphabet(currentFilter->getAlphabet());
        if(currentFilter->getType() == 9) filter->setType(7);
        else filter->setType(currentFilter->getType());
        filter->setMaxId(currentFilter->getMaxId());
        filter->setMinId(currentFilter->getMinId());
        filter->setMinOcc(currentFilter->getMinOcc());
        filter->setRefSeq(currentFilter->getRefSeq());
        filter->setTaxon(currentFilter->getTaxon());
        filter->addSequences(sequencenames,sequences);
        filter->setSubsetFrequencies(currentFilter->getSubsetFrequencies());
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->listWidget2);
        treeItem->setText(0,name.c_str());
        filter->setQtreeWidgetItem(treeItem);

        currentAlign->addFilter(filter);

        ui->listWidget2->setCurrentItem(treeItem);

        QString msg = "The sub-alignmente were generated with " + QString::number(sequences.size()) + " sequences.";
        QMessageBox::information(this,"Sub-alignment generated",msg);

        ui->txtSubAlignName->clear();
        ui->txtResiduesSubAlign->clear();
    }
    ui->cmdGenerateSubAlignment->setEnabled(true);
}

void MainWindow::on_cmbAddSeq1_activated(const QString &arg1)
{
    Filter* f;
    vector<Filter*> filters = currentAlign->getFilters();

    ui->lstAddSeq1->clear();

    for(unsigned int i = 0; i < filters.size(); i++){
        f = filters[i];

        if(f->getName() == arg1.toStdString())
            break;
    }

    for(unsigned int i = 0; i < f->sequencenames.size(); i++){
        ui->lstAddSeq1->addItem(f->sequencenames[i].c_str());
    }
}

void MainWindow::on_cmbAddSeq2_activated(const QString &arg1)
{
    Filter* f;
    vector<Filter*> filters = currentAlign->getFilters();

    ui->lstAddSeq2->clear();

    for(unsigned int i = 0; i < filters.size(); i++){
        f = filters[i];

        if(f->getName() == arg1.toStdString())
            break;
    }

    for(unsigned int i = 0; i < f->sequencenames.size(); i++){
        ui->lstAddSeq2->addItem(f->sequencenames[i].c_str());
    }
}

void MainWindow::on_cmdAddSeq_clicked()
{
    ui->cmdAddSeq->setEnabled(false);
    Filter* filter1 = currentAlign->getFilterByName(ui->cmbAddSeq1->currentText().toStdString());
    Filter* filter2 = currentAlign->getFilterByName(ui->cmbAddSeq2->currentText().toStdString());

    string sequence = ui->lstAddSeq1->currentItem()->text().toStdString();
    bool found = false;

    for(unsigned int i = 0; i < filter2->sequencenames.size(); i++){
        if(sequence == filter2->getName()){
            found = true;
            break;
        }
    }

    if(found){
        string msg = "The sequence " + sequence + " is aleady in the filtered alignment " + ui->cmbAddSeq2->currentText().toStdString() + ".";
        QMessageBox::warning(this,"Sequence already in alignment",msg.c_str());
        return;
    }else{
        string seq = "";
        //getSequence
        for(unsigned int i = 0; i < filter1->sequencenames.size(); i++){
            if(sequence == filter1->sequencenames[i]){
                seq = filter1->sequences[i];
                break;
            }
        }

        if(seq == ""){
            string msg = "The sequence " + sequence + " was not found in the alignment " + ui->cmbAddSeq1->currentText().toStdString() + ".";
            QMessageBox::warning(this,"Sequence not found",msg.c_str());
            return;
        }

        filter2->sequencenames.push_back(sequence);
        filter2->sequences.push_back(seq);

        //printf("%s %s\n",sequence.c_str(),seq.c_str());

        //emit ui->listWidget2->activated(ui->listWidget2->currentIndex());
        emit ui->listWidget2->currentItemChanged(filter2->getQTreeWidgetItem(),filter1->getQTreeWidgetItem());

        string msg = "The sequence " + sequence + "was added in the alignment " + ui->cmbAddSeq2->currentText().toStdString() + ".";
        QMessageBox::information(this,"Sequence added",msg.c_str());
    }

    ui->cmdAddSeq->setEnabled(true);
}

void MainWindow::on_cmdExpandNetworkVisualization_clicked()
{
    NetworkVisualization* nw = new NetworkVisualization(this,currentNetwork,libpath);
    nw->setWindowFlags(Qt::Window);
    nw->show();
}

void MainWindow::on_cmdExpandTaxonomy_clicked()
{
    TaxonomicVisualization* tv = new TaxonomicVisualization(this,currentFilter,currentNetwork,libpath);
    tv->setWindowFlags(Qt::Window);
    tv->show();
}

void MainWindow::on_cmdCalculateMutations_clicked()
{
    /*
    ui->cmdCalculateMutations->setEnabled(false);

    if(ui->cmbMutationStructure->currentText() == ""){
        QMessageBox::warning(this,"Warning","You must choose a structure");
        ui->cmdCalculateMutations->setEnabled(true);
        return;
    }

    Pdb* currentStructure = new Pdb();

    for(unsigned int i = 0; i < pdbs.size(); i++){
        Pdb* structure = pdbs[i];
        if(structure->getId() == ui->cmbMutationStructure->currentText().toStdString()){
            currentStructure = structure;
        }
    }

    if(currentStructure->getId() == "nothing"){
        QMessageBox::critical(this,"Error","Error while loading the structure file");
        ui->cmdCalculateMutations->setEnabled(true);
        return;
    }

    if(ui->txtMutationsList->toPlainText() == ""){
        QMessageBox::warning(this,"Warning","You must select at least one mutation");
        ui->cmdCalculateMutations->setEnabled(true);
        return;
    }

    if(currentFilter->getCommListSize() == 0){
        QMessageBox::warning(this,"Warning","You must select run correlation methods");
        ui->cmdCalculateMutations->setEnabled(true);
        return;
    }

    vector<string> mutations = split(ui->txtMutationsList->toPlainText().toStdString(),'\n');
    for(unsigned int i = 0; i < mutations.size(); i++){
        string mutation = mutations[i];
        transform(mutation.begin(),mutation.end(),mutation.begin(),::toupper);

        if(mutation.size() < 3){
            string msg = mutation + " is not in the accepted format for mutations (i.e. A12C)";
            QMessageBox::warning(this,"Warning",msg.c_str());
            ui->cmdCalculateMutations->setEnabled(true);
            return;
        }else{
            char aa1 = mutation[0];
            char aa2 = mutation[mutation.size()-1];
            string strpos = mutation.substr(1,mutation.size()-2);

            if(!isaa(aa1)){
                string msg = aa1 + " is not a valid amino acid.";
                QMessageBox::warning(this,"Warning",msg.c_str());
                ui->cmdCalculateMutations->setEnabled(true);
                return;
            }
            if(!isaa(aa2)){
                string msg = aa2 + " is not a valid amino acid.";
                QMessageBox::warning(this,"Warning",msg.c_str());
                ui->cmdCalculateMutations->setEnabled(true);
                return;
            }

            bool isInt = true;
            for(string::const_iterator k = strpos.begin(); k != strpos.end(); k++)
                isInt = isInt && isdigit(*k);

            if(!isInt){
                string msg = strpos + " is not a valid position.";
                QMessageBox::warning(this,"Warning",msg.c_str());
                ui->cmdCalculateMutations->setEnabled(true);
                return;
            }
        }
    }

    //Positions
    if(ui->radioMutationSequence->isChecked()){
        string seq = ui->cmbMutationRefSeq->currentText().toStdString();
        if(!currentFilter->containsSequence(seq)){
            QMessageBox::warning(this,"Warning","Sequence not found.");
            ui->cmdCalculateMutations->setEnabled(true);
            return;
        }
    }

    //Calculate Frequencies
    string result = "";
    for(unsigned int i = 0; i < mutations.size(); i++){
        string mutation = mutations[i];
        transform(mutation.begin(),mutation.end(),mutation.begin(),::toupper);
        char aa1 = mutation[0];
        char aa2 = mutation[mutation.size()-1];
        string strpos = mutation.substr(1,mutation.size()-2);
        int pos = atoi(strpos.c_str());

        if(ui->radioMutationSequence->isChecked()){
            int newpos = currentFilter->sequencenumbering2alignment(ui->cmbMutationRefSeq->currentIndex()+1,pos);

            if(newpos < 0){
                QMessageBox::warning(this,"Warning","Position not valid");
                ui->cmdCalculateMutations->setEnabled(true);
                return;
            }
            strpos = to_string(newpos);
            pos = newpos;
        }else if(ui->radioMutationPDB->isChecked()){
            for(unsigned int i = 0; i < currentStructure->countResidues(); i++){
                PdbResidues* residue = currentStructure->getResidue(i);
                PdbAtom* atom = residue->getAtom(0);
                if(atom->getResidueNumber() == pos){
                    string refseq = currentStructure->getRefseq();
                    vector<string> temp = split(refseq,'/');
                    int offset = atoi(split(temp[1],'-')[0].c_str());
                    int seqnumber = i + offset;//i+1 + offset-1//TA ERRADO, CONVERTER PRA ALIGN E DEPOIS SEQ

                    int newpos = currentFilter->sequencenumbering2alignment(currentFilter->getSequenceIndex(refseq)+1,seqnumber);

                    if(newpos < 0){
                        QMessageBox::warning(this,"Warning","Position not valid");
                        ui->cmdCalculateMutations->setEnabled(true);
                        return;
                    }
                    //printf("PDB: %s\n",to_string(pos).c_str());
                    strpos = to_string(newpos);
                    pos = newpos;
                    //printf("SEQ: %s\nALI: %s\n",to_string(seqnumber).c_str(),strpos.c_str());
                    break;
                }
            }
        }

        float freq1 = currentFilter->getResidueFrequence(aa1,pos,"T20");
        float freq2 = currentFilter->getResidueFrequence(aa2,pos,"T20");

        if(freq1 == -1){
            QMessageBox::warning(this,"Warning","Position not valid");
            ui->cmdCalculateMutations->setEnabled(true);
            return;
        }

        //printf("%f - %f\n",freq1,freq2);
        result += "Position: " + strpos + " (" + aa1 + " to " + aa2 + ")<br>";
        result += (string) + "Frequencies: (" + aa1 + " - " + aa2 + ")<br>";
        if(freq1 > freq2)
            result += "T20:&nbsp;<b>" + QString::number(freq1).toStdString() + "</b> - " + QString::number(freq2).toStdString() + "<br>";
        else if(freq2 > freq1)
            result += "T20:&nbsp;" + QString::number(freq1).toStdString() + " - <b>" + QString::number(freq2).toStdString() + "</b><br>";
        else
            result += "T20:&nbsp;<b>" + QString::number(freq1).toStdString() + "</b> - <b>" + QString::number(freq2).toStdString() + "</b><br>";
        if(ui->chkAlphabetMutations->isChecked()){
            vector<string> alphabetNames {"T2","T5","T6","3IMG","5IMG","11IMG","Murphy15","Murphy10","Murphy8","Murphy4","Murphy2","Wang5","Wang5v","Wang3","Wang2","Li10","Li5","Li4","Li3"};
            for(unsigned int j = 0; j < alphabetNames.size(); j++){
                string alphabet = alphabetNames[j];
                float freq1 = currentFilter->getResidueFrequence(aa1,pos,alphabet);
                float freq2 = currentFilter->getResidueFrequence(aa2,pos,alphabet);
                if(freq1 > freq2)
                    result += alphabet + ":&nbsp;<b>" + QString::number(freq1).toStdString() + "</b> - " + QString::number(freq2).toStdString() + "<br>";
                else if(freq2 > freq1)
                    result += alphabet + ":&nbsp;" + QString::number(freq1).toStdString() + " - <b>" + QString::number(freq2).toStdString() + "</b><br>";
                else
                    result += alphabet + ":&nbsp;<b>" + QString::number(freq1).toStdString() + "</b> - <b>" + QString::number(freq2).toStdString() + "</b><br>";
            }
        }
        result += "===============================<br>";

    }

    ui->txtMutationResult->insertHtml(result.c_str());

    //currentStructure->calculateInterations();

    QMessageBox::information(this,"Mutation Analysis","The mutations were successfully calculated");
    ui->cmdCalculateMutations->setEnabled(true);
    */
}

void MainWindow::on_radioMutationAlignment_clicked(bool checked)
{
    if(checked){
        ui->radioMutationSequence->setChecked(false);
        ui->radioMutationPDB->setChecked(false);
        ui->cmbMutationRefSeq->setEnabled(false);
    }
}

void MainWindow::on_radioMutationSequence_clicked(bool checked)
{
    if(checked){
        ui->radioMutationAlignment->setChecked(false);
        ui->radioMutationPDB->setChecked(false);
        ui->cmbMutationRefSeq->setEnabled(true);
    }
}

void MainWindow::on_radioMutationPDB_clicked(bool checked)
{
    if(checked){
        ui->radioMutationAlignment->setChecked(false);
        ui->radioMutationSequence->setChecked(false);
        ui->cmbMutationRefSeq->setEnabled(false);
    }
}

QTreeWidgetItem* MainWindow::getFilterItem(){
    QTreeWidgetItem* item = currentFilter->getQTreeWidgetItem();

    if(!item){
        item = ui->listWidget2->topLevelItem(0);
    }

    return item;
}

#include "taxonomicvisualization.h"
#include "ui_taxonomicvisualization.h"

TaxonomicVisualization::TaxonomicVisualization(QWidget *parent, Filter *filter, Network *network, string lib) :
    QDialog(parent),
    ui(new Ui::TaxonomicVisualization)
{
    currentFilter = filter;
    currentNetwork = network;
    libpath = lib;

    ui->setupUi(this);

    //Resetar campos de resultado
    ui->radioSun1->setChecked(true);
    ui->radioSun2->setChecked(false);
    ui->radioSun3->setChecked(false);
    ui->radioSun4->setChecked(false);
    ui->cmbSunburstEdges->clear();
    ui->cmbSunburstCommunity->clear();
    ui->txtSunburstResidue->clear();

    if(network){
        for(unsigned int i = 0; i < currentNetwork->getGraphSize(); i++){
            std::tuple<string,string,int> edge = currentNetwork->getGraphTuple(i);
            string n1 = std::get<0>(edge);
            string n2 = std::get<1>(edge);
            string text = n1 + "," + n2;
            ui->cmbSunburstEdges->addItem(text.c_str());
        }

        for(unsigned int i = 0; i < currentNetwork->getNumOfUtilComms(); i++)
            ui->cmbSunburstCommunity->addItem(QString::number(i+1));
    }
    this->generateSunburst(vector<string>());
}

TaxonomicVisualization::~TaxonomicVisualization()
{
    delete ui;
}

vector<string> TaxonomicVisualization::split(string text, char sep){
    int start = 0, end = 0;
    vector<string> tokens;

    while((end = text.find(sep,start)) != string::npos){
        tokens.push_back(text.substr(start,end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));

    return tokens;
}

bool TaxonomicVisualization::generateSunburst(vector<string> sequencenames){
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
        //printf("\n%s",html.toStdString().c_str());
        QMessageBox::warning(this,"Fetching Failed","Error while trying to connect the webservice");
        return false;
    }else{
        string pathcsv = libpath + "sunburst/clades.csv";
        string pathhtml = libpath + "sunburst/sunburst.html";
        QFile indexHTML(pathcsv.c_str());
        indexHTML.open(QIODevice::WriteOnly);
        QTextStream out(&indexHTML);

        out << html;

        //LISTWIDGET
        mapPreTaxons.clear();
        map<string,int> mapSpecie;
        ui->lstSunburstTaxon->clear();
        vector<string> lines = this->split(html.toStdString(),'\n');
        int index = ui->cmbSunburstTaxon->currentIndex();
        for(unsigned int i = 0; i < lines.size(); i++){
            if(lines[i] != ""){
                vector<string> taxVec = this->split(lines[i],'-');
                string currentTaxon = taxVec[index];
                string specie = this->split(currentTaxon,',')[0];
                int count = atoi(split(lines[i],',')[1].c_str());
                if(mapSpecie.find(specie) == mapSpecie.end()){
                    mapSpecie[specie] = count;

                    string taxline = "";
                    for(int j = 0; j < index; j++){
                        taxline += taxVec[j] + "-";

                    }
                    taxline += taxVec[index];
                    mapPreTaxons[specie] = split(taxline,',')[0];
                }else
                    mapSpecie[specie] = mapSpecie[specie] + count;
            }
        }
        vector<pair<string,int> > species(mapSpecie.begin(), mapSpecie.end());
        sort(species.begin(),species.end(),less_second<string,int>());
        for(unsigned int i = 0; i < species.size(); i++){
            pair<string,int> p = species[i];
            string text = p.first + " (" + to_string(p.second) + ")";
            ui->lstSunburstTaxon->addItem(text.c_str());
        }

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

void TaxonomicVisualization::on_radioSun1_clicked(bool checked)
{
    if(checked){
        ui->radioSun2->setChecked(false);
        ui->cmbSunburstEdges->setEnabled(false);
        ui->radioSun3->setChecked(false);
        ui->cmbSunburstCommunity->setEnabled(false);
        ui->radioSun4->setChecked(false);
        ui->txtSunburstResidue->setEnabled(false);
    }
}

void TaxonomicVisualization::on_radioSun2_clicked(bool checked)
{
    if(checked){
        ui->cmbSunburstEdges->setEnabled(true);
        ui->radioSun1->setChecked(false);
        ui->radioSun3->setChecked(false);
        ui->cmbSunburstCommunity->setEnabled(false);
        ui->radioSun4->setChecked(false);
        ui->txtSunburstResidue->setEnabled(false);
    }
}

void TaxonomicVisualization::on_radioSun3_clicked(bool checked)
{
    if(checked){
        ui->cmbSunburstCommunity->setEnabled(true);
        ui->radioSun1->setChecked(false);
        ui->radioSun2->setChecked(false);
        ui->cmbSunburstEdges->setEnabled(false);
        ui->radioSun4->setChecked(false);
        ui->txtSunburstResidue->setEnabled(false);
    }
}

void TaxonomicVisualization::on_radioSun4_clicked(bool checked)
{
    if(checked){
        ui->txtSunburstResidue->setEnabled(true);
        ui->radioSun1->setChecked(false);
        ui->radioSun2->setChecked(false);
        ui->cmbSunburstEdges->setEnabled(false);
        ui->radioSun3->setChecked(false);
        ui->cmbSunburstCommunity->setEnabled(false);
    }
}

void TaxonomicVisualization::on_cmdSunburstFilter_clicked()
{
    if(ui->radioSun1->isChecked()){
        generateSunburst(currentFilter->sequencenames);
    }else if(ui->radioSun2->isChecked()){
        if(ui->cmbSunburstEdges->currentText() == ""){
            return;
        }

        vector<string> sequences;
        vector<string> splitted = this->split(ui->cmbSunburstEdges->currentText().toStdString(),',');
        string node1 = splitted[0];
        char aa1 = node1[0];
        int pos1 = atoi(node1.substr(1).c_str());
        string node2 = splitted[1];
        char aa2 = node2[0];
        int pos2 = atoi(node2.substr(1).c_str());

        for(unsigned int i = 0; i < currentFilter->sequencenames.size(); i++){
            if(currentFilter->sequences[i][pos1-1] == aa1 && currentFilter->sequences[i][pos2-1] == aa2)
                sequences.push_back(currentFilter->sequencenames[i]);
        }

        generateSunburst(sequences);
    }else if(ui->radioSun3->isChecked()){
        if(currentNetwork){
            vector<string> sequences;
            if(ui->cmbSunburstCommunity->count() == 0) return;
            if(currentNetwork->getNumOfUtilComms() == 0) return;

            vector<string> residues = currentNetwork->getCommunitie(ui->cmbSunburstCommunity->currentIndex());

            int nOfResidues = residues.size();
            int hits;

            for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                hits = 0;

                for(unsigned int j = 0; j < nOfResidues; j++){
                    string residue = residues[j];
                    char aa = residue[0];
                    int pos = atoi(residue.substr(1).c_str());

                    if(currentFilter->sequences[i][pos-1] == aa) hits++;
                }

                if(hits == nOfResidues){
                    sequences.push_back(currentFilter->sequencenames[i]);
                }
            }

            generateSunburst(sequences);
        }
    }else if(ui->radioSun4->isChecked()){
        vector<string> sequences;

        if(ui->txtSunburstResidue->text() == "") return;

        string residue = ui->txtSunburstResidue->text().toStdString();
        char aa = residue[0];
        int pos = atoi(residue.substr(1).c_str());

        for(unsigned int i = 0; i < currentFilter->sequences.size(); i++){
                if(aa == currentFilter->sequences[i][pos-1]){
                    sequences.push_back(currentFilter->sequencenames[i]);
                }
        }

        generateSunburst(sequences);
    }else{
        return;
    }
}

void TaxonomicVisualization::on_cmbSunburstTaxon_activated(int index)
{
    emit this->on_cmdSunburstFilter_clicked();
}

void TaxonomicVisualization::on_lstSunburstTaxon_itemActivated(QListWidgetItem *item)
{
    string currentTax = split(item->text().toStdString(),'(')[0];
    if(currentTax[currentTax.size()-1] == ' ') currentTax = currentTax.substr(0,currentTax.size()-1);
    //printf("Especie: %s\tPre-Taxon: %s\n",currentTax.c_str(),mapPreTaxons[currentTax].c_str());

    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->setAttribute(QWebSettings::JavascriptEnabled,true);
    websettings->clearMemoryCaches();
    websettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebFrame *frame = ui->webTaxons->page()->mainFrame();
    string js = "zoomFoundLineage('" + mapPreTaxons[currentTax] + "')";
    frame->evaluateJavaScript(QString::fromStdString(js));
}

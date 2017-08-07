#include "networkvisualization.h"
#include "ui_networkvisualization.h"

NetworkVisualization::NetworkVisualization(QWidget *parent, Network *net, string lib) :
    QDialog(parent),
    ui(new Ui::NetworkVisualization)
{
    currentNetwork = net;
    libpath = lib;

    ui->setupUi(this);

    createVisualization(false,false,false);
}

NetworkVisualization::~NetworkVisualization()
{
    delete ui;
}

void NetworkVisualization::createVisualization(bool hideanticorr, bool commcolor, bool scaleEdges){
    unsigned int nrows = currentNetwork->getGraphSize();
    string pathJSON = libpath + "visjs/examples/network/in.js";
    QFile fileJSON(pathJSON.c_str());
    fileJSON.open(QIODevice::WriteOnly);
    QTextStream out(&fileJSON);
    map<string,int> nodes;
    map<string,int> dic;

    if(hideanticorr)
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
    out << "edges:{smooth: false},\n";
    out << "layout:{\n";
    if(ui->txtRandomSeed->value() == 0) out << "randomSeed: undefined";
    else out << "randomSeed: " + QString::number(ui->txtRandomSeed->value());
    if(ui->cmbLayout->currentIndex() == 0) out << "\n";
    else{
        out << ",\n";
        out << "hierarchical:{\n";
        out << "enabled: true,\n";
        if(ui->cmbLayout->currentIndex() == 1) out << "direction: 'UD'\n";
        else out << "direction: 'DU'\n";
        out << "}\n";
    }
    out << "}\n";
    out << "};\n\n";

    out << "var nodes = [\n";
    unsigned int count = 1;

    for(map<string,int>::iterator it = nodes.begin(); it != nodes.end(); it++){
        string color = currentNetwork->getResidueColor(it->first);
        if(!commcolor) color = "";

        if(it!= nodes.begin()){
            out << ",\n";
        }
        if(color == "")
            out << "{id: " + QString::number(count) + ", label: '" + QString::fromStdString(it->first) + "', value: " + QString::number(it->second) + "}";
        else
            out << "{id: " + QString::number(count) + ", label: '" + QString::fromStdString(it->first) + "', value: " + QString::number(it->second) + ", color:{background:'" + color.c_str() + "'}}";
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

        if(hideanticorr){
            if(weight > 0){
                if(!scaleEdges)
                    out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + "},\n";
                else
                    out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + ", value: " + QString::number(abs(weight)) + "},\n";
            }
        }else{
            if(!scaleEdges)
                out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + "},\n";
            else
                out << "{from: " + QString::number(id1) + ", to: " + QString::number(id2) + ", color:{color:'" + color.c_str() + "'}, title: " + QString::number(weight) + ", value: " + QString::number(abs(weight)) + "},\n";
        }
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
    ui->webView->load(QUrl(localUrl.c_str()));
}

void NetworkVisualization::on_cmdReload_clicked()
{
    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
    ui->chkHideAntiCorrelations->setChecked(false);
    ui->chkCommunitiesColor->setChecked(false);
    createVisualization(false,false,false);
}

void NetworkVisualization::on_chkHideAntiCorrelations_clicked(bool checked)
{
    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
    createVisualization(checked,ui->chkCommunitiesColor->isChecked(),ui->chkScaleEdgesScore->isChecked());
}

void NetworkVisualization::on_chkScaleHubs_clicked(bool checked)
{
    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->setAttribute(QWebSettings::JavascriptEnabled,true);
    websettings->clearMemoryCaches();
    QWebFrame *frame = ui->webView->page()->mainFrame();
    if(checked) frame->evaluateJavaScript("scaleHubsize(true)");
    else frame->evaluateJavaScript("scaleHubsize(false)");
}

void NetworkVisualization::on_chkCommunitiesColor_clicked(bool checked)
{
    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
    createVisualization(ui->chkHideAntiCorrelations->isChecked(),checked,ui->chkScaleEdgesScore->isChecked());
}

void NetworkVisualization::on_chkScaleEdgesScore_clicked(bool checked)
{
    QWebSettings *websettings = QWebSettings::globalSettings();
    websettings->clearMemoryCaches();
    createVisualization(ui->chkHideAntiCorrelations->isChecked(),ui->chkCommunitiesColor->isChecked(),checked);
}

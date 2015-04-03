#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void inputAlignment_triggered();
    void fetchPFAM_triggered();
    void exportAlignment_triggered();

    void on_cmdStartWizard_clicked();
    void on_cmdMain_clicked();
    void on_cmdBack_clicked();
    void on_cmdAdvance_clicked();

    void on_cmdOpen_clicked();

    void on_cmdFetch_clicked();

    void on_cmdApplyFilter_clicked();

    void on_cmdFetchPDB_clicked();

    void on_cmdPDBfromFile_clicked();

    void on_cmdConservation_clicked();

    void on_cmdMinss_clicked();

    void on_cmdGraphPath_clicked();

    void on_cmdCorrelation_clicked();

private:
    Ui::MainWindow *ui;
    void changeWizardCmds(bool bl);
    bool wizard;
};

#endif // MAINWINDOW_H

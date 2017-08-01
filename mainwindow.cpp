#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::replot(void) {
    ui->plPlot->clearGraphs();

    const size_t l = this->plots.size();
    for(size_t i = 0; i<l; i++) {
        Plot &plot = this->plots[i];
        if(!plot.isEnabled()) continue;

        QCPGraph *graph = ui->plPlot->addGraph();

        graph->setData(plot.x(), plot.y());
        graph->setAntialiased(true);
        graph->setPen(plot.pen);
    }

    ui->plPlot->rescaleAxes();
    ui->plPlot->replot();
}

void MainWindow::addPlot(const Plot &plot) {
    this->plots.push_back(plot);
}

void MainWindow::on_actionRefresh_triggered()
{
    ui->plPlot->replot();
}

void MainWindow::on_actionRescale_triggered()
{
    ui->plPlot->rescaleAxes();
}

void MainWindow::on_actionStatusbar_toggled(bool toggled)
{
    ui->fraStatus->setVisible(toggled);
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString filter = tr("CSV file (*.csv);;All files (*.*)");
    QString filename = QFileDialog::getOpenFileName(this, "Open file", "", filter);
    if(filename.isEmpty()) return;

    FileParser parser;
    parser.readFile(filename);
    // Right now we don't check the parser for it's status
    this->addPlot(parser.getPlot());
    this->replot();
}

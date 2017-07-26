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
        QCPGraph *graph = ui->plPlot->addGraph();

        QVector<double> x = plot.x();
        QVector<double> y = plot.y();
        graph->setData(x, y);
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

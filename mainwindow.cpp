#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dockPlots->setVisible(ui->actionDockPlots->isChecked());

    // Hide statusbar, since normally we don't want to see that one
    ui->actionStatusbar->setChecked(false);
    ui->fraStatus->setVisible(false);
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
    QString title = plot.title().trimmed();
    if(title.isEmpty()) title = "Plot";

    QListWidgetItem *item = new QListWidgetItem(title, ui->lstPlots);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);
    ui->lstPlots->addItem(item);
}

void MainWindow::removePlot(const Plot &plot) {
#if 0
    for(int i=0;i<this->plots.size();i++) {
        if(this->plots[i] == plot) {
            ui->lstPlots->removeItemWidget(ui->lstPlots->item(i));
            this->plots.removeAt(i);
            return;
        }
    }
#endif
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
    QString filter = tr("Supported files (*.csv *.dat);;CSV file (*.csv);;Dat file (*.dat);;All files (*.*)");
    QString filename = QFileDialog::getOpenFileName(this, "Open file", "", filter);
    if(filename.isEmpty()) return;

    FileParser parser;
    parser.readFile(filename);
    // Right now we don't check the parser for it's status
    QList<Plot> plots = parser.getPlots();
    foreach(Plot plot, plots)
        this->addPlot(plot);
    this->replot();
}

void MainWindow::on_actionDockPlots_toggled(bool checked)
{
    ui->dockPlots->setVisible(checked);
}

void MainWindow::on_lstPlots_itemChanged(QListWidgetItem *item)
{
    const int index = ui->lstPlots->row(item);
    if(index < 0) return;

    Plot &plot = this->plots[index];
    bool isEnabled = item->checkState() == Qt::Checked;
    if(isEnabled != plot.isEnabled()) {
        plot.setEnabled(isEnabled);
        this->replot();
    }

}

void MainWindow::on_dockPlots_visibilityChanged(bool visible)
{
    if(ui->actionDockPlots->isChecked() != visible)
        ui->actionDockPlots->setChecked(visible);
}

void MainWindow::on_lstPlots_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu(ui->lstPlots);

    menu->addAction("Show plot ...");
    menu->addSeparator();
    menu->addAction("Remove");

    menu->popup(ui->lstPlots->mapToGlobal(pos));
}

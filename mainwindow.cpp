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

/**
 * @brief mimeType Mime type based on the file ending
 * @param filename input filename where the mime type is returned
 * @return -1 if no ending, -2 if not recognised ending, 1 for CSV file, 2 for image
 */
static int mimeType(const QString &filename) {
    int index = filename.lastIndexOf('.');
    if(index < 0) return -1;       // Not found
    QString ending = filename.mid(index).toLower();
    if(ending == ".csv" || ending == ".dat") return 1;
    else if(ending == ".png" || ending == ".bmp" || ending == ".eps" || ending == ".jpg" || ending == ".jpeg") return 2;
    else return -2;
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString filter = tr("Supported files (*.csv *.dat *.png *.bmp *.jpg *.eps);;CSV file (*.csv *.dat);;Image (*.png *.bmp *.jpg *.eps);;All files (*.*)");
    QString filename = QFileDialog::getOpenFileName(this, "Open file", "", filter);
    if(filename.isEmpty()) return;

    // Match file ending with filter
    try {
        const int mime = mimeType(filename);

        switch(mime) {
        case 2:
            // Load image
        {
            DialogImage *dlg = new DialogImage(filename);
            dlg->show();
        }

        default:
            // Try CSV
        {
            FileParser parser;
            parser.readFile(filename);
            // XXX: Right now we don't check the parser for it's status
            QList<Plot> plots = parser.getPlots();
            foreach(Plot plot, plots)
                this->addPlot(plot);
            this->replot();
        }
        }   // end switch
    } catch(const char* msg) {
        ui->lblStatus->setText("Error: " + QString(msg));
    } catch(...) {
        ui->lblStatus->setText("Unknown error occured");
    }

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

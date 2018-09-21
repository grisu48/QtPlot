#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QList>
#include <QFileDialog>
#include <QListWidgetItem>

#include "plot.h"
#include "fileparser.h"
#include "dialogimage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief replot Trigger a replot
     */
    void replot(void);

    /**
     * @brief addPlot adds a plot
     * @param plot to be added
     */
    void addPlot(const Plot &plot);

    /**
     * @brief removePlot removes a plot from the list
     * @param plot to be added
     */
    void removePlot(const Plot &plot);

private slots:
    void on_actionRefresh_triggered();

    void on_actionRescale_triggered();

    void on_actionStatusbar_toggled(bool arg1);

    void on_actionOpenFile_triggered();

    void on_actionDockPlots_toggled(bool arg1);

    void on_lstPlots_itemChanged(QListWidgetItem *item);

    void on_dockPlots_visibilityChanged(bool visible);

    void on_lstPlots_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;

    /** All plots in the instance */
    QList<Plot> plots;
};

#endif // MAINWINDOW_H

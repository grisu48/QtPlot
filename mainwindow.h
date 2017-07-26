#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QList>

#include "plot.h"

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
     * @brief replot Causes a replot
     */
    void replot(void);

    /**
     * @brief addPlot adds a plot
     * @param plot to be added
     */
    void addPlot(const Plot &plot);

private slots:
    void on_actionRefresh_triggered();

    void on_actionRescale_triggered();

    void on_actionStatusbar_toggled(bool arg1);

private:
    Ui::MainWindow *ui;

    /** All plots in the instance */
    QList<Plot> plots;
};

#endif // MAINWINDOW_H

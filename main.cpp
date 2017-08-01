#include "mainwindow.h"
#include <QApplication>
#include <QString>

#include <iostream>
#include <string>

#include "fileparser.h"

using namespace std;



static QChar separator = ',';           // Data separator, currently hard-coded



/**
 * @brief readStdin reads a plot from stdin
 * @return read plot
 */
static Plot readStdin(long *linesRead = NULL, long *dataLines = NULL) {


    string buf;
    Plot plot;
    long l_linesRead = 0;
    long l_dataLines = 0;

    while(getline(cin, buf)) {
        l_linesRead++;
        QString line(buf.c_str());
        if(line.isEmpty()) break;
        line = line.trimmed();
        if(line.isEmpty()) continue;
        QChar first = line.at(0);
        if(first == '#' || first == ':' || first == ';') continue;      // Comment line

        // Split into x,y values. For now, the separator is ','
        int i = line.indexOf(separator);
        if(i<0) {
            cerr << "Line " << l_linesRead << " illegal - Separator not found" << endl;
            continue;
        } else {
            QString str_x = line.left(i).trimmed();
            QString str_y = line.mid(i+1).trimmed();

            bool ok = false;

            double x = str_x.toDouble(&ok);
            if(!ok) {
                cerr << "Line " << l_linesRead << " illegal - Cannot parse x value" << endl;
                continue;
            }
            double y = str_y.toDouble(&ok);
            if(!ok) {
                cerr << "Line " << l_linesRead << " illegal - Cannot parse y value" << endl;
                continue;
            }

            plot.add(x,y);
            l_dataLines++;
        }

    }

    if(linesRead != NULL) *linesRead = l_linesRead;
    if(dataLines != NULL) *dataLines = l_dataLines;

    return plot;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Parse program arguments
    bool quiet = false;
    try {

        FileParser parser;

        for(int i=1;i<argc;i++) {
            QString arg(argv[i]);
            arg = arg.trimmed();

            if(arg.isEmpty()) continue;
            if(arg.at(0) == '-') {
                if(arg == "--help" || arg == "-h") {

                    cout << "QtPlot - Simple QT5-based plotting utitlity" << endl;
                    cout << "  2017, Felix Niederwanger" << endl << endl;
                    cout << "Usage: " << argv[0] << " [OPTIONS] [FILES]" << endl;
                    cout << "OPTIONS" << endl;
                    cout << "   -h       --help           Print this help message" << endl;
                    cout << "   -q       --quiet          Quiet output" << endl;
                    cout << "FILES are all program arguments, that do not start with a '-'." << endl;
                    cout << "  All FILES will be opened and added as plots" << endl;


                } else if(arg == "--quiet" || arg == "-q") {
                    quiet = true;
                } else if(arg == "--stdin") {
                    if(!quiet) cout << "Reading from stdin until empty line or EOF ... " << endl;

                    // Read plot from stdin
                    long linesRead = 0;
                    long dataLines = 0;
                    Plot plot = readStdin(&linesRead, &dataLines);
                    cout << linesRead << " lines read, " << dataLines << " lines of data" << endl;
                    w.addPlot(plot);
                } else {
                    cerr << "Illegal program argument: " << argv[i] << endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                QString filename = arg;
                parser.readFile(filename);
                w.addPlot(parser.getPlot());
            }
        }
    } catch (const char* msg) {
        cerr << "Error paring program arguments: " << msg << endl;
        exit(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    w.replot();
    w.show();
    return a.exec();
}

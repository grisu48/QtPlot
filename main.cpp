#include "mainwindow.h"
#include <QApplication>
#include <QString>

#include <iostream>
#include <string>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    // Parse program arguments
    bool quiet = false;
    try {
        QChar separator = ',';           // Data separator

        for(int i=1;i<argc;i++) {
            QString arg(argv[i]);
            arg = arg.trimmed();

            if(arg.isEmpty()) continue;
            if(arg.at(0) == '-') {
                if(arg == "--quiet" || arg == "-q") {
                    quiet = true;
                } else if(arg == "--stdin") {
                    // Read plot from stdin
                    Plot plot;

                    if(!quiet) cout << "Reading from stdin until empty line or EOF ... " << endl;
                    string buf;

                    long linesRead = 0;
                    long dataLines = 0;
                    while(getline(cin, buf)) {
                        linesRead++;
                        QString line(buf.c_str());
                        if(line.isEmpty()) break;
                        line = line.trimmed();
                        if(line.isEmpty()) continue;
                        QChar first = line.at(0);
                        if(first == '#' || first == ':' || first == ';') continue;      // Comment line

                        // Split into x,y values. For now, the separator is ','
                        int i = line.indexOf(separator);
                        if(i<0) {
                            cerr << "Line " << linesRead << " illegal - Separator not found" << endl;
                            continue;
                        } else {
                            QString str_x = line.left(i).trimmed();
                            QString str_y = line.mid(i+1).trimmed();

                            bool ok = false;

                            double x = str_x.toDouble(&ok);
                            if(!ok) {
                                cerr << "Line " << linesRead << " illegal - Cannot parse x value" << endl;
                                continue;
                            }
                            double y = str_y.toDouble(&ok);
                            if(!ok) {
                                cerr << "Line " << linesRead << " illegal - Cannot parse y value" << endl;
                                continue;
                            }

                            plot.add(x,y);
                            dataLines++;
                        }

                    }
                    cout << linesRead << " lines read, " << dataLines << " lines of data" << endl;
                    w.addPlot(plot);
                } else {
                    cerr << "Illegal program argument: " << argv[i] << endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                cerr << "Illegal program argument: " << argv[i] << endl;
                exit(EXIT_FAILURE);
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

#include "fileparser.h"

FileParser::FileParser()
{

}


void FileParser::clear() {
    this->plot.clear();
    this->illegalLines = 0;
    this->linesRead = 0;
}

void FileParser::readFile(const QString &filename) {
    this->clear();

    QFile inputFile(filename);
    QChar separator = ',';
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            this->linesRead++;
            QString line = in.readLine().trimmed();
            if(line.isEmpty()) continue;

            int index = line.indexOf(separator);
            if(index < 0) {
                this->illegalLines++;
                continue;     // Illegal line
            }

            QString str_x = line.left(index).trimmed();
            QString str_y = line.mid(index+1).trimmed();
            if(str_x.isEmpty() || str_y.isEmpty()) {
                this->illegalLines++;
                continue;
            }

            bool ok;
            double x,y;
            x = str_x.toDouble(&ok);
            if(!ok) {
                this->illegalLines++;
                continue;
            }
            y = str_y.toDouble(&ok);
            if(!ok) {
                this->illegalLines++;
                continue;
            }
            this->plot.add(x,y);


        }
        inputFile.close();
        this->ok = true;
    } else {
        this->ok = false;
    }
}

Plot FileParser::getPlot(void) const {
    return this->plot;
}

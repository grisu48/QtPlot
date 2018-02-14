#include "fileparser.h"

FileRow::FileRow(const FileRow &row) {
    this->_x = row._x;
    this->values = row.values;
}

FileRow::~FileRow() {}

FileParser::FileParser()
{

}


void FileParser::clear() {
    this->plots.clear();
    this->illegalLines = 0;
    this->linesRead = 0;
}


std::vector<double> FileParser::parseLine(QString line) {
    std::vector<double> ret;

    line = line.trimmed();
    if(line.size() == 0) return ret;
    if(line.at(0) == '#') return ret;


    QString buf;
    int len = line.size();
    for(int i=0;i<len;i++) {
        QChar c = line.at(i);
        // Check for valid separators
        if(c.isSpace() || c == ',') {
            buf = buf.trimmed();
            if(buf.size() > 0) {
                bool ok = false;
                double x = buf.toDouble(&ok);
                if(!ok) {
                    // Warning
                }
                ret.push_back(x);
                buf.clear();
            }
        } else
            buf.append(c);
    }
    if(buf.size() > 0) {
        bool ok = false;
        double x = buf.toDouble(&ok);
        if(!ok) {
            // Warning
        }
        ret.push_back(x);
        buf.clear();
    }

    return ret;
}

static inline size_t s_max(const size_t s1, const size_t s2) { return (s1>s2?s1:s2); }

void FileParser::readFile(const QString &filename) {
    this->clear();

    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->plots.clear();
        std::vector<FileRow> rows;
        QTextStream in(&inputFile);
        size_t columns = 0;
        while (!in.atEnd())
        {
            this->linesRead++;
            QString line = in.readLine().trimmed();
            if(line.isEmpty()) continue;

            std::vector<double> values = parseLine(line);
            if(values.size() > 0) {
                FileRow row(values);
                rows.push_back(row);
                columns = s_max(columns, row.size());
            }

        }
        inputFile.close();

        if(columns == 0) {
            // Special case. Only x values
            this->_warnings.push_back(QString("No values columns"));
            this->ok = false;
            return;
        } else {
            for(std::vector<FileRow>::iterator it=rows.begin(); it!= rows.end(); it++) {
                (*it).expand(columns);
            }

            // Build plots
            const int nPlots = columns;

            this->plots.clear();
            for(int i=0; i<nPlots; i++) {
                Plot plot;

                for(std::vector<FileRow>::iterator it=rows.begin(); it!= rows.end(); it++) {
                    const double x = (*it).x();
                    const double y = (*it)[i];
                    plot.add(x,y);
                }

                this->plots.append(plot);
            }


        }

        this->ok = true;
    } else {
        this->_warnings.push_back(QString("Cannot open file"));
        this->ok = false;
    }
}

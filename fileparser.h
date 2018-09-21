#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <vector>

#include <QString>
#include <QFile>
#include <QList>
#include <QTextStream>

#include "plot.h"

class FileParser;
class FileRow;


/**
 * @brief A single row in a file
 */
class FileRow {
private:
    double _x;
    std::vector<double> values;
protected:
    FileRow() {
        this->_x = 0.0;
    }

    FileRow(const double x) {
        this->_x = x;
    }
    FileRow(const std::vector<double> values) {
        size_t len = values.size();
        if(len < 1) throw "Cannot create empty row";
        this->_x = values[0];
        for(size_t i=1;i<len;i++)
            this->values.push_back(values[i]);
    }

    /** Add a single column value */
    void append(const double x) {
        this->values.push_back(x);
    }

    /**
     * @brief expand Expands the values to the given number of columns by adding 0.0 values
     * @param columns number of columns to achieve
     */
    void expand(size_t columns) {
        while(this->values.size() < columns)
            this->values.push_back(0.0);
    }

public:
    FileRow(const FileRow &row);
    virtual ~FileRow();

    /**
     * @brief x
     * @return  get the x value
     */
    double x(void) const { return this->_x; }

    size_t size(void) const { return this->values.size(); }
    double operator[](const int i) const {
        if(i<0||i>=(int)size()) throw "Index out of bounds";
        else
            return this->values[i];
    }
    double operator[](const size_t i) const {
        if(i>=size()) throw "Index out of bounds";
        else
            return this->values[i];
    }
    double operator[](const ssize_t i) const {
        if(i<0||i>=(ssize_t)size()) throw "Index out of bounds";
        else
            return this->values[i];
    }


    friend class FileParser;
};


/** General file parser class
 * Reads in a single file and tries to parse it in the best manner possible
 */
class FileParser
{
private:
    /** Resulting plots */
    QList<Plot> plots;

    long illegalLines = 0;
    long linesRead = 0;

    bool ok = true;
    char sep = ',';     // Separator

    /**
     * @brief parseLine This method tries to parse the given line
     * @param line to be parsed
     * @return parsed line
     */
    std::vector<double> parseLine(QString line);

    /**
     * @brief warnings Warnings during reading
     */
    QList<QString> _warnings;
public:
    FileParser();

    /** Clear current plot */
    void clear();

    void readFile(const QString &filename);

    QList<Plot> getPlots(void) const { return this->plots; }

    long getIllegalLines(void) const { return this->illegalLines; }
    long getLinesRead(void) const { return this->linesRead; }

    bool isOk() const { return this->ok; }

    QList<QString> warnings(void) const { return this->_warnings; }
};

#endif // FILEPARSER_H

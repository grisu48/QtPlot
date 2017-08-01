#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include "plot.h"

class FileParser
{
private:
    /** Separator for splitting line*/
    QChar separator = ',';

    /** Resulting plot*/
    Plot plot;

    long illegalLines = 0;
    long linesRead = 0;

    bool ok = true;
public:
    FileParser();

    /** Clear current plot */
    void clear();

    void readFile(const QString &filename);

    /**
     * @brief plot Gets the plot that has been parsed
     * @return plot that is parsed
     */
    Plot getPlot(void) const;

    long getIllegalLines(void) const { return this->illegalLines; }
    long getLinesRead(void) const { return this->linesRead; }

    bool isOk() const { return this->ok; }
};

#endif // FILEPARSER_H

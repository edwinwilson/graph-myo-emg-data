#ifndef EMGGRAPHER_H
#define EMGGRAPHER_H

#include <QStringList>
#include "emgrecordsparser.h"
#include "emggraphdrawer.h"
#include "stdio.h"
#include <iostream>


class EMGGrapher
{
public:
    EMGGrapher();
    EMGGrapher(QStringList inputFilePaths,
               QStringList outputDirectory);
    ~EMGGrapher();
    void setInputFiles(QStringList inputFilePaths);
    void setOuputDirectory(QStringList outputDirectory);
    void graph();

private:
    QStringList inputFilePaths;
    QStringList outputDirectory;
    void cleanTempFiles(QStringList temporaryFilePaths);
    static const std::string TEMPFILEPATH;
};

#endif // EMGGRAPHER_H

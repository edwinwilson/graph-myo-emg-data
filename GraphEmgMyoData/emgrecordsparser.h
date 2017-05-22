#ifndef EMGRECORDSPARSER_H
#define EMGRECORDSPARSER_H

#include <QStringList>
#include "stdio.h"
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

class EMGRecordsParser
{
public:
    EMGRecordsParser();
    ~EMGRecordsParser();
    QStringList parse();
    void setInputFiles(QStringList inputFilePaths);
    void setOutputDirectory(QString outputDirectory);

private:
    QStringList inputFiles;
    QString outputDirectory;
    void writeToTempFile(std::list<std::string> stringList, std::string path);
};

#endif // EMGRECORDSPARSER_H

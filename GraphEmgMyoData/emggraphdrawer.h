#ifndef EMGGRAPHDRAWER_H
#define EMGGRAPHDRAWER_H

#include <QStringList>
#include <sys/stat.h>
#include <time.h>
#include <string>
#include <iostream>

class EMGGraphDrawer
{
public:
    EMGGraphDrawer();
    ~EMGGraphDrawer();
    void setInputFiles(QStringList inputFilePaths);
    void setOutputDirectory(QString outputDirectory);
    void draw();

private:
    QStringList inputFiles;
    QString outputDirectory;
    std::string getColor(int plotNumber);
};

#endif // EMGGRAPHDRAWER_H

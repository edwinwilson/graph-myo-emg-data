#include "emggrapher.h"

using namespace std;

const string EMGGrapher::TEMPFILEPATH = "../test/";

EMGGrapher::EMGGrapher()
{

}

EMGGrapher::EMGGrapher(QStringList inputFilePaths,
                       QStringList outputDirectory)
{
    this->inputFilePaths = inputFilePaths;
    this->outputDirectory = outputDirectory;
}

EMGGrapher::~EMGGrapher()
{

}

void EMGGrapher::graph(){
    cout << "Starting graphing operations." << endl;
    EMGRecordsParser parser;
    EMGGraphDrawer drawer;
    QString tempPath;
    tempPath.append(EMGGrapher::TEMPFILEPATH.data());

    parser.setInputFiles(inputFilePaths);
    parser.setOutputDirectory(tempPath);
    QStringList parsedFilePaths = parser.parse();

    drawer.setInputFiles(parsedFilePaths);
    drawer.setOutputDirectory(outputDirectory.at(0));
    drawer.draw();

    cleanTempFiles(parsedFilePaths);
    cout << "Finished graphing operations." << endl;
}

void EMGGrapher::cleanTempFiles(QStringList temporaryFilePaths){
    for(int i = 0; i < temporaryFilePaths.size(); i++){
        if( remove( temporaryFilePaths.at(i).toLocal8Bit().constData() ) != 0 ){
            perror( "Error deleting file" + temporaryFilePaths.at(i).toLocal8Bit() );
        }
    }
    cout << "Temp files cleaned." << endl;
}

void EMGGrapher::setInputFiles(QStringList inputFilePaths){
    this->inputFilePaths = inputFilePaths;
}

void EMGGrapher::setOuputDirectory(QStringList outputDirectory){
    this->outputDirectory = outputDirectory;
}

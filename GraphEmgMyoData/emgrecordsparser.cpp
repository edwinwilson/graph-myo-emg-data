#include "emgrecordsparser.h"

using namespace std;

EMGRecordsParser::EMGRecordsParser()
{

}

EMGRecordsParser::~EMGRecordsParser()
{

}


void EMGRecordsParser::setInputFiles(QStringList inputFilePaths){
    for(int i = 0; i < inputFilePaths.size(); i++){
        if (FILE *file = fopen(inputFilePaths.at(i).toLocal8Bit().data(), "r")) {
            fclose(file);
            this->inputFiles.append(inputFilePaths.at(i));
            continue;
        }
        //perror("File read error : %s", inputFilePaths.at(i).toLocal8Bit().constData());
    }
}

void EMGRecordsParser::setOutputDirectory(QString outputDirectory){
    struct stat s;
    if(stat(outputDirectory.toLocal8Bit().constData(),&s) == 0){
        if(s.st_mode & S_IFDIR){
            this->outputDirectory = outputDirectory;
        }
        else{
            perror("Check value of directory for temporary files destination. Not a directory.");
            return;
        }
    }
}

QStringList EMGRecordsParser::parse(){
    cout << "Starting parse." << endl;
    QStringList returnFiles;
    if(this->inputFiles.isEmpty()){
        perror("No input files were passed to the parser");
        return returnFiles;
    }
    if(this->outputDirectory.isEmpty()){
        perror("No destination directory for parser output.");
        return returnFiles;
    }
    for(int i = 0; i < inputFiles.size(); i++){
        string line;
        string path = inputFiles.at(i).toLocal8Bit().constData();
        ifstream file (path);
        if(file.is_open()){
            cout << "Parsing file " << i+1 << endl;
            // create one vector per emg + titles vector
            // get file name for later
            string filePrefix;
            size_t lastCharBeforeBasename = path.find_last_of("/\\");
            filePrefix = path.substr(lastCharBeforeBasename+1);
            size_t extensionBeginPos = filePrefix.find('.');
            filePrefix = filePrefix.substr(0,extensionBeginPos);
            QStringList files;
            list <string> emg1;
            list <string> emg2;
            list <string> emg3;
            list <string> emg4;
            list <string> emg5;
            list <string> emg6;
            list <string> emg7;
            list <string> emg8;
            // create titles array
            getline(file,line);
            size_t pos = line.find(",", 0);
            line.erase(0,pos+1);
            string fileTitle;
            while (line.find(",", 0) != string::npos){
                pos = line.find(",",0);
                fileTitle = line.substr(0,pos);
                QString fileName;
                fileName = this->outputDirectory;
                fileName += filePrefix.data();
                fileName += "_";
                fileName += fileTitle.data();
                files.append(fileName);
                pos = line.find(",", 0);
                line.erase(0,pos+1);
                if(line.find(",", 0) == string::npos && line.find('\r',0) != string::npos){
                    pos = line.find('\r',0);
                    pos = line.find('\r',0);
                    fileTitle = line.substr(0,pos);
                    fileName = this->outputDirectory;
                    fileName += filePrefix.data();
                    fileName += "_";
                    fileName += fileTitle.data();
                    files.append(fileName);
                }
            }


            string emgValue;
            int lineNum = 1;
            while(getline(file, line)){
                int iteration = 0;
                while (line.find(",", 0) != string::npos){
                    pos = line.find(",",0);
                    emgValue = line.substr(0,pos);
                    switch (iteration) {
                    case 0:
                        break;
                    case 1:
                        emg1.push_back(emgValue);
                        break;
                    case 2:
                        emg2.push_back(emgValue);
                        break;
                    case 3:
                        emg3.push_back(emgValue);
                        break;
                    case 4:
                        emg4.push_back(emgValue);
                        break;
                    case 5:
                        emg5.push_back(emgValue);
                        break;
                    case 6:
                        emg6.push_back(emgValue);
                        break;
                    case 7:
                        emg7.push_back(emgValue);
                        break;
                    case 8:
                        emg8.push_back(emgValue);
                        break;
                    default:
                        break;
                    }
                    iteration++;
                    line.erase(0,pos+1);
                }
                pos = line.find('\r',0);
                emgValue = line.substr(0,pos);
                emg8.push_back(emgValue);
                lineNum++;
            }
            file.close();
            writeToTempFile(emg1,files.at(0).toLocal8Bit().constData());
            writeToTempFile(emg2,files.at(1).toLocal8Bit().constData());
            writeToTempFile(emg3,files.at(2).toLocal8Bit().constData());
            writeToTempFile(emg4,files.at(3).toLocal8Bit().constData());
            writeToTempFile(emg5,files.at(4).toLocal8Bit().constData());
            writeToTempFile(emg6,files.at(5).toLocal8Bit().constData());
            writeToTempFile(emg7,files.at(6).toLocal8Bit().constData());
            writeToTempFile(emg8,files.at(7).toLocal8Bit().constData());
            returnFiles += files;
        }
        else{
            perror("Unable to open file : " + inputFiles.at(i).toLocal8Bit());
        }
    }
    cout << "Ended parse." << endl;
    return returnFiles;
}

void EMGRecordsParser::writeToTempFile(list<string> stringList, string path){
    // open new temp file
    ofstream tempFile;
    tempFile.open(path.data());
    for(std::list<string>::iterator it=stringList.begin(); it != stringList.end(); ++it){
        tempFile << *it + "\n";
    }
    tempFile.close();
}

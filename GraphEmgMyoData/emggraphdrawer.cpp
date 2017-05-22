#include "emggraphdrawer.h"
#include "gnuplot_i.hpp"

using namespace std;

EMGGraphDrawer::EMGGraphDrawer()
{

}

EMGGraphDrawer::~EMGGraphDrawer()
{

}

void EMGGraphDrawer::setInputFiles(QStringList inputFilePaths){
    for(int i = 0; i < inputFilePaths.size(); i++){
        if (FILE *file = fopen(inputFilePaths.at(i).toLocal8Bit().constData(), "r")) {
            fclose(file);
            this->inputFiles.append(inputFilePaths.at(i));
            continue;
        }
        perror("File read error : " + inputFilePaths.at(i).toLocal8Bit());
    }
    cout << "Files ready to graph." << endl;
}

void EMGGraphDrawer::setOutputDirectory(QString outputDirectory){
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

void EMGGraphDrawer::draw(){
    cout << "Graphing" << endl;
    Gnuplot plotter("lines");
    plotter.set_xlabel("Measures");
    plotter.set_ylabel("emg value");
    for(int i = 0; i < inputFiles.size(); i++){
        string color = getColor(i);
        //plotter.cmd("set rgb '" + color + "'");
        plotter.cmd("set style line 5 lt 3 linecolor rgb '" + color + "' lw 3");
        plotter.set_style("lines ls 5");
        string name = inputFiles.at(i).toLocal8Bit().data();
        size_t lastCharBeforeBasename = name.find_last_of("/\\");
        name = name.substr(lastCharBeforeBasename+1);
        string saveCommand = "set terminal png size 1024,768 enhanced font \"Helvetica,20\"";
        string setOutputDirCommand = "set output '";
        setOutputDirCommand += this->outputDirectory.toLocal8Bit().data();
        setOutputDirCommand += "/" + name + ".png'";
        plotter.cmd(saveCommand);
        plotter.cmd(setOutputDirCommand);
        plotter.plotfile_x(inputFiles.at(i).toLocal8Bit().constData(),1,name);
        plotter.cmd("clear");
        plotter.reset_plot();
    }
    cout << "Finished graphing." << endl;
}

string EMGGraphDrawer::getColor(int plotNumber){
    string color;
    int modulo = plotNumber%8;
    switch (modulo) {
    case 0:
        color = "red";
        break;
    case 1:
        color = "web-green";
        break;
    case 2:
        color = "web-blue";
        break;
    case 3:
        color = "dark-magenta";
        break;
    case 4:
        color = "dark-cyan";
        break;
    case 5:
        color = "dark-orange";
        break;
    case 6:
        color = "dark-yellow";
        break;
    case 7:
        color = "royalblue";
        break;
    default:
        color = "black";
        break;
    }
    return color;
}

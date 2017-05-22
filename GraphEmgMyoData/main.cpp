#include "widget.h"
#include <QApplication>
#include <QFileDialog>
#include <iostream>
#include "emggrapher.h"
#include <QMessageBox>

using namespace std;

int main(int argc, char *argv[])
{
    static const string TEMPFILEPATH = ".";
    QApplication a(argc, argv);
    Widget w;
    QFileDialog inputFileDialog(&w);
    QFileDialog outputFileDialog(&w);
    QMessageBox endDialog(&w);
    QStringList selectedFiles;
    QStringList outputDirectory;
    EMGGrapher grapher;

    //inputFileDialog.setNameFilter("CSV (*.csv)");
    inputFileDialog.setOptions(QFileDialog::DontUseNativeDialog);
    inputFileDialog.setFileMode(QFileDialog::ExistingFiles);
    inputFileDialog.show();
    if(inputFileDialog.exec()){
        selectedFiles = inputFileDialog.selectedFiles();
    }
    cout << "Number of files selected " << selectedFiles.size() << endl;
    if(selectedFiles.size() == 0) cout << "No files" << endl;
    for (int i = 0; i < selectedFiles.size(); i++){
        cout << selectedFiles.at(i).toLocal8Bit().constData() << endl;
    }

    outputFileDialog.setOptions(QFileDialog::DontUseNativeDialog);
    outputFileDialog.setFileMode(QFileDialog::Directory);

    if(outputFileDialog.exec()){
        outputDirectory = outputFileDialog.selectedFiles();
    }

    if (outputDirectory.isEmpty()){
        cout << "No output directory was chosen." << endl;
        exit(EXIT_FAILURE);
    }
    else {
        cout << "Output directory : " << endl << outputDirectory.first().toLocal8Bit().constData() << endl;
    }

    grapher.setInputFiles(selectedFiles);
    grapher.setOuputDirectory(outputDirectory);
    grapher.graph();

    endDialog.setWindowTitle("Graphing ended");
    endDialog.setText("Your EMG values were graphed to " + outputDirectory.at(0).toLocal8Bit());
    if(!endDialog.exec()){
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

    return a.exec();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <filesystem>
#include <src/FileExplorer/header/ImageIterator.h>
#include <src/FileExplorer/header/ImageOrganizer.h>
#include <src/FaceRec/header/Clustering.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString directory_name = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    ui->input_directory_label->setText(directory_name);
    images_directory = filesystem::path(directory_name.toUtf8().constData());
}


void MainWindow::on_pushButton_2_clicked()
{
    QString directory_name = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    ui->output_directory_label->setText(directory_name);
    clusters_directory = filesystem::path(directory_name.toUtf8().constData());
}

void MainWindow::on_pushButton_3_clicked()
{
    const std::filesystem::path path = images_directory;
    std::vector<string> images;
    std::unordered_map<int, std::vector<string>> clusters;
    auto start = chrono::high_resolution_clock::now();
    try {
        images = list_all_images(path);
        Clustering helper = Clustering(images, clusters_directory);
        clusters = helper.cluster();
    }
    catch (...){
        cout<<"Caught an exception\n";
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout <<"time taken for the experiment : " << duration.count()/1000000 <<" seconds"<< endl;
    populateClusters(clusters_directory, clusters);
    MainWindow::close();
}

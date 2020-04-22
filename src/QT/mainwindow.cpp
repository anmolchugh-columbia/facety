#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <filesystem>
#include <src/FileExplorer/header/ImageIterator.h>
#include <src/FileExplorer/header/ImageOrganizer.h>
#include <src/FaceRec/header/faceClustering.h>

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
    try {
        images = list_all_images(path);
        cout<<images.size()<<endl;
        clusters = clustering(images, clusters_directory);
        cout<<"clustered"<<endl;

    }
    catch (...){
        cout<<"Caught an exception\n";
    }

    populateClusters(clusters_directory, clusters);
    MainWindow::close();
}

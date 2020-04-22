#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_fileLineEdit_textChanged(const QString &arg1) {
   // qDebug() << arg1;
    file_name = arg1;
}

void MainWindow::on_keyLineEdit_textChanged(const QString &arg1) {
    find_what = arg1;
}

// Sanan etsiminen / etsintäalgoritmi
void MainWindow::on_findPushButton_clicked() {
    std::string searched_for = find_what.QString::toStdString();
    if(not ui->matchCheckBox->isChecked()) {
        std::transform(searched_for.begin(), searched_for.end(), searched_for.begin(), ::tolower);
    }

    //  std::transform (myname.begin(), myname.end(), myname.begin(), ::tolower);

    std::ifstream tiedosto_olio(file_name.QString::toStdString());
    if(not tiedosto_olio) {
        ui->textBrowser->setText("File not found");
        return;
    }
    else if(find_what == "") {
        ui->textBrowser->setText("File found");
        return;
    }

    std::string rivi;
    while(std::getline(tiedosto_olio, rivi)){
        if(not ui->matchCheckBox->isChecked()) {
            std::transform(rivi.begin(), rivi.end(), rivi.begin(), ::tolower);
        }
        if(rivi.find(searched_for) != std::string::npos) { // text found in file
            ui->textBrowser->setText("Word found");
            return;
        }
    }
    ui->textBrowser->setText("Word not found");
}
























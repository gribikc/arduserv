#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *mainWidget=new QWidget(this);

}

void MainWindow::write_text(){

}

MainWindow::~MainWindow()
{
    delete ui;
}

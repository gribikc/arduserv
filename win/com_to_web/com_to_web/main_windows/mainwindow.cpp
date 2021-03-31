#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->textEdit_bbb->insertPlainText("Create com_to_web/htdocs\n");
}
void MainWindow::write_text(){

}

MainWindow::~MainWindow()
{
    delete ui;
}

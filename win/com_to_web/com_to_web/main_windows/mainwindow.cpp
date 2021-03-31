#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
void MainWindow::write_text(int type,QString str){
    ui->textEdit_bbb->insertPlainText(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}

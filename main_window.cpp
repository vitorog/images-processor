#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GLWidget *gl = new GLWidget();
    gl->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "main_window.h"
#include "ui_main_window.h"

#include "gl_widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ImageRenderer *gl = new ImageRenderer();
    //GLWidgetTest *gl2 = new GLWidgetTest();
    this->setCentralWidget(gl);
}

MainWindow::~MainWindow()
{
    delete ui;
}

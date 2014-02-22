#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>

#include "image_renderer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    QObject::connect(ui_->actionLoad_image,SIGNAL(triggered()),qApp,SLOT(quit()));

    image_renderer_ = new ImageRenderer();
    this->setCentralWidget(image_renderer_);


    cam_reader_ = new WebcamReader();
    if(cam_reader_->Init()){
        QObject::connect(&update_timer_,SIGNAL(timeout()),this,SLOT(UpdateImage()));
        update_timer_.setInterval(0);
        update_timer_.start();
    }
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::UpdateImage()
{    
    cv::Mat frame;
    cam_reader_->GetConvertedFrame(frame);
    image_renderer_->SetImage(QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGBA8888));
    image_renderer_->update();
}

#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>

#include "image_renderer.h"
#include "debug.h"
#include "shader_program.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    QObject::connect(ui_->actionLoad_image,SIGNAL(triggered()),qApp,SLOT(quit()));
    QObject::connect(ui_->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ChangeShader(int)));
    QObject::connect(ui_->reload_pushButton, SIGNAL(clicked()),this,SLOT(ReloadShaders()));

    image_renderer_ = new ImageRenderer();
    QObject::connect(image_renderer_,SIGNAL(GlInitialized()),this,SLOT(LoadShaders()));
    ui_->frame->layout()->addWidget(image_renderer_);

    QObject::connect(&update_timer_,SIGNAL(timeout()),this,SLOT(UpdateImage()));
    update_timer_.setInterval(0);
    cam_reader_ = new WebcamReader();
    if(cam_reader_->Init()){
        update_timer_.start();
    }
}

MainWindow::~MainWindow()
{
    delete cam_reader_;
    delete image_renderer_;
    delete ui_;
}

void MainWindow::UpdateImage()
{    
    cv::Mat frame;
    cam_reader_->GetConvertedFrame(frame);
    image_renderer_->SetImage(QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGBA8888));
    image_renderer_->update();
}

void MainWindow::ChangeShader(int index)
{
    current_index_ = index;
    image_renderer_->UseShaderProgram(index);
    image_renderer_->update();
    DEBUG_MESSAGE("Program: " + ui_->listWidget->item(index)->text().toStdString());

}

void MainWindow::ReloadShaders()
{
    QObject::disconnect(ui_->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ChangeShader(int)));
    ui_->listWidget->clear();
    update_timer_.stop();
    image_renderer_->ClearAllShaderPrograms();
    LoadShaders();
    QObject::connect(ui_->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ChangeShader(int)));
    update_timer_.start();
    if(current_index_ < ui_->listWidget->count()){
        ui_->listWidget->setCurrentRow(current_index_);
//        ChangeShader(current_index_);
    }
}

void MainWindow::LoadShaders()
{
    QStringList name_filter("*.frag");
    QDir directory(".");
    QStringList fragment_shaders = directory.entryList(name_filter);
    for(QStringList::iterator it = fragment_shaders.begin(); it != fragment_shaders.end(); it++){
        ShaderProgram *sp = new ShaderProgram();
        if(sp->CompileShaderFromFile("./basic.vert", kVertexShader)){
            DEBUG_MESSAGE("basic.vert loaded successfully.");
        }else{
            DEBUG_MESSAGE("Failed to load vertex shader.");
        }
        QString fragment_shader_name = (*it);
        QString path = directory.absolutePath() + "/" + fragment_shader_name;
        if(sp->CompileShaderFromFile(path.toStdString(), kFragmentShader)){
            DEBUG_MESSAGE((*it).toStdString() + " loaded successfully.");

            image_renderer_->AddShaderProgram(sp);
            QString effect_name = fragment_shader_name;
            effect_name.chop(5);
            effect_name[0] = effect_name.at(0).toUpper();
            ui_->listWidget->addItem(effect_name);
        }else{
            DEBUG_MESSAGE("Failed to load frag shader " + (*it).toStdString());
        }
    }
    image_renderer_->UseShaderProgram(0);
    ui_->listWidget->setCurrentRow(0);
}

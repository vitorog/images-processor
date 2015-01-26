#include "image_renderer.h"

#include <QImage>
#include <glm/gtc/matrix_transform.hpp>

#include "debug.h"

ImageRenderer::ImageRenderer(QWidget *parent) :
    QGLWidget(parent)
{

}

ImageRenderer::~ImageRenderer()
{

}

void ImageRenderer::initializeGL()
{
    bool ret = gl_context_.InitGL();
    DEBUG_MESSAGE("OpenGl initialization: " << ret);
    Initialize();
    emit GlInitialized();
}

void ImageRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(!shaders_.empty()){
        glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, &model_matrix_[0][0]);
        glUniformMatrix4fv(view_matrix_location_,1,GL_FALSE,&view_matrix_[0][0]);
        glUniformMatrix4fv(projection_matrix_location_, 1, GL_FALSE, &projection_matrix_[0][0]);
        glBindVertexArray(vao_handle_);
        glDrawArrays(GL_TRIANGLES,0,6);
    }
}

void ImageRenderer::resizeGL(int w, int h)
{
    float width = (float)w;
    float height = (float)h;
    float vertices[] = {
        0.0f,0.0f,0.0f,
        width,0.0f,0.0f,
        0.0f,height,0.0f,
        width,0.0f,0.0f,
        width,height,0.0f,
        0.0f,height,0.0f
    };
    glViewport(0,0,width,height);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0,18*sizeof(float), vertices);

    projection_matrix_ = glm::ortho(0.0f,width, 0.0f, height);
}

void ImageRenderer::Initialize()
{
    float width = (float)this->width();
    float height = (float)this->height();
    glViewport(0,0,width,height);

    float vertices[] = {
        0.0f,0.0f,0.0f,
        width,0.0f,0.0f,
        0.0f,height,0.0f,
        width,0.0f,0.0f,
        width,height,0.0f,
        0.0f,height,0.0f
    };

    float tex_coords[] = {
        0.0f,0.0f,
        1.0f,0.0f,
        0.0f,1.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f
    };

    glGenBuffers(2, &vbo_handle_[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[0]);
    glBufferData(GL_ARRAY_BUFFER,18*sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[1]);
    glBufferData(GL_ARRAY_BUFFER,12*sizeof(float), tex_coords, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao_handle_);
    glBindVertexArray(vao_handle_);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL );

    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_[1]);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL );

    model_matrix_ = glm::mat4(1.0f);
    view_matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
    projection_matrix_ = glm::ortho(0.0f,width, 0.0f, height);
}

void ImageRenderer::LoadImage(const std::string path)
{
    QImage texture_img = QGLWidget::convertToGLFormat(QImage(QString::fromStdString(path)));
    if(texture_id_ != 0){
        glDeleteTextures(1, &texture_id_);
    }
    glGenTextures(1,&texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_img.width(),
                 texture_img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_img.bits());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    this->resize(texture_img.width(),texture_img.height());
    this->setMaximumHeight(texture_img.height());
    this->setMinimumHeight(texture_img.height());
    this->setMaximumWidth(texture_img.width());
    this->setMinimumWidth(texture_img.width());
}

void ImageRenderer::SetImage(QImage img)
{
    QImage texture_img = QGLWidget::convertToGLFormat(img);
    if(texture_id_ != 0){
        glDeleteTextures(1, &texture_id_);
    }
    glGenTextures(1,&texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_img.width(),
                 texture_img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_img.bits());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    this->resize(texture_img.width(),texture_img.height());
    this->setMaximumHeight(texture_img.height());
    this->setMinimumHeight(texture_img.height());
    this->setMaximumWidth(texture_img.width());
    this->setMinimumWidth(texture_img.width());
}

void ImageRenderer::AddShaderProgram(ShaderProgram *sp)
{
    shaders_.push_back(sp);
}

void ImageRenderer::UseShaderProgram(int index)
{
    if(index >= 0 && index < shaders_.size()){
        ShaderProgram* sp = shaders_.at(index);
        glBindAttribLocation( sp->GetHandle(), 0, "vertex_position");
        glBindAttribLocation( sp->GetHandle(), 1, "vertex_texture_coords");

        sp->Link();
        sp->Use();

        model_matrix_location_ = glGetUniformLocation(sp->GetHandle(), "model_matrix");
        view_matrix_location_ = glGetUniformLocation(sp->GetHandle(), "view_matrix");
        projection_matrix_location_ = glGetUniformLocation(sp->GetHandle(), "projection_matrix");
        texture_uniform_location_ = glGetUniformLocation(sp->GetHandle(), "texture");

        glActiveTexture(GL_TEXTURE0);
        glUniform1i(texture_uniform_location_, 0);
    }
}


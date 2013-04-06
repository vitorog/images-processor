#include "gl_widget.h"

#include "debug.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    bool ret = gl_context.InitGl();
    DEBUG_MESSAGE("OpenGl initialization: " << ret);
}

void GLWidget::paintGl()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(0.0f,1.0f,0.0f);
    glVertex3f(1.0f,0.0f,0.0f);
    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0.0f,640,0.0f,480,1.0f,-1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include "gl_context.h"
#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
protected:
    virtual void initializeGL();
    virtual void paintGl();
    virtual void resizeGL(int w, int h);
signals:
    
public slots:
private:
    GLContext gl_context;
};

#endif // GL_WIDGET_H

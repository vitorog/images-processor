#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include "gl_context.h"
#include "shader_program.h"

#include <QtOpenGL/QGLWidget>
#include <QImage>

class ImageRenderer : public QGLWidget
{
    Q_OBJECT
public:
    explicit ImageRenderer(QWidget *parent = 0);
    ~ImageRenderer();
    void LoadImage(const std::string path);
    void SetImage(QImage);
    void AddShaderProgram(ShaderProgram*);
    void UseShaderProgram(int index);
protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
signals:
    void GlInitialized();
public slots:
private:
    void Initialize();

    GLContext gl_context_;
    GLuint vao_handle_;
    GLuint vbo_handle_[2];
    GLuint texture_id_;
    GLuint texture_uniform_location_;    
    glm::mat4 model_matrix_;
    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
    GLuint model_matrix_location_;
    GLuint view_matrix_location_;
    GLuint projection_matrix_location_;

    std::vector<ShaderProgram*> shaders_;
};

#endif // GL_WIDGET_H

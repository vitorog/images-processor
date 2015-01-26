#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "webcam_reader.h"

class ImageRenderer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
public slots:
    void UpdateImage();
    void ChangeShader(int index);
private slots:
    void LoadShaders();
private:

    Ui::MainWindow *ui_;
    ImageRenderer* image_renderer_;
    WebcamReader* cam_reader_;
    QTimer update_timer_;
};

#endif // MAIN_WINDOW_H

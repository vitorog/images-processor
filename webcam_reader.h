#ifndef WEBCAM_READER_H
#define WEBCAM_READER_H

#include <QObject>
#include "opencv2/opencv.hpp"

class WebcamReader : public QObject
{
    Q_OBJECT
public:
    explicit WebcamReader(QObject *parent = 0);
    bool Init();
    void GetConvertedFrame(cv::Mat&);
signals:

public slots:
private:
    cv::VideoCapture cam_;
};

#endif // WEBCAM_READER_H

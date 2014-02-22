#include "webcam_reader.h"

#include "debug.h"

WebcamReader::WebcamReader(QObject *parent) :
    QObject(parent)
{

}

bool WebcamReader::Init()
{
    cam_.open(0);
    if(!cam_.isOpened()){
        DEBUG_MESSAGE("Failed to capture webcam");
        return false;
    }
    return true;
}

void WebcamReader::GetConvertedFrame(cv::Mat &frame)
{
    if(cam_.isOpened()){
        cv::Mat original_frame;
        cam_ >> original_frame;
        cv::cvtColor(original_frame, frame, CV_BGR2RGBA);
    }
}

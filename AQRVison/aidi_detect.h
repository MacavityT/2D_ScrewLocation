#ifndef AIDI_DETECT_H
#define AIDI_DETECT_H

#include "opencv2/opencv.hpp"
#include "infer/aidi.h"
#include "infer/aidi_factory_runner_wrapper.h"
#include "infer/aidi_factory_param_wrapper.h"
#include <QObject>
#include "cpp/HalconCpp.h"
#include "base_struct.h"

using namespace Halcon;

class AIDI_DETECT : public QObject
{
    Q_OBJECT

public:
    AIDI_DETECT(std::string path);
    AIDI_DETECT();
    ~AIDI_DETECT();

    bool test_factory_runner(Hobject Image);
    Hobject Mat2HObject(cv::Mat& image);
    cv::Mat HObject2Mat(Hobject Hobj);
public:
     aq::AidiFactoryRunnerWrapper* runner;
     std::string root_path;
     aq::FactoryClientParamWrapper param;
};

#endif // AIDI_DETECT_H

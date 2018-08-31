//module：Basler Cam
//version:V1.0
//author:Xiaobin Wang
//date:2018-06-04
//something:多相机

#ifndef CAM_H
#define CAM_H
#include "pylon/PylonIncludes.h"
#include <pylon/gige/_BaslerGigECameraParams.h>
#include <pylon/gige/_GigEStreamParams.h>
#include <pylon/gige/_GigEEventParams.h>
#include <pylon/gige/_GigETLParams.h>
#include <pylon/gige/BaslerGigEDeviceInfo.h>
#include <pylon/gige/PylonGigEDevice.h>
#include <pylon/gige/BaslerGigEConfigurationEventHandler.h>
#include <pylon/gige/BaslerGigEImageEventHandler.h>
#include <pylon/gige/BaslerGigECameraEventHandler.h>
#include <pylon/gige/BaslerGigEGrabResultPtr.h>
#include <pylon/private/DeviceSpecificInstantCamera.h>
#include <pylon/DeviceClass.h>
#include <pylon/NodeMapProxy.h>

namespace Basler_GigECameraParams = Basler_GigECamera;

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using cout
using namespace std;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 5;

class basler_cam
{
public:
    basler_cam();
    ~basler_cam();

    int init();
    int open();
    int snap(int cam_index);
    int exit();

public:
    CInstantCameraArray* m_cams;
//    CDeviceInfo info;
//    string x= info.GetFullName();
    DeviceInfoList_t m_devices;
    // Get all attached devices and exit application if no device is found.
    int m_c_maxCamerasToUse;

private:
    // Get the transport layer factory.
    int m_exitCode;

public:
    uint8_t *pImageBuffer[20];
    int m_buffer_num;

    int m_cam_width;
    int m_cam_height;

};

#endif // CAM_H

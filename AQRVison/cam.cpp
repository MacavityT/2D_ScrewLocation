// Balser.cpp
#include "cam.h"

basler_cam::basler_cam()
{
    //最多5台相机
    m_c_maxCamerasToUse = 5;
    m_buffer_num = 20;
    m_cam_width = 2592;
    m_cam_height = 1944;
    for(int i = 0;i<m_buffer_num;i++)
    {
       pImageBuffer[i] = NULL;
    }

    m_cams = NULL;
    PylonInitialize();

}

basler_cam::~basler_cam()
{
    for(int i = 0;i< m_buffer_num ;i++)
    {
        if(pImageBuffer[i] != NULL)
        {
            delete pImageBuffer[i];
        }
        pImageBuffer[i] = NULL;
    }

    if(m_cams != NULL)
    {
        delete(m_cams);
        m_cams = NULL;
    }

    PylonTerminate();

}

//相机初始化
int basler_cam::init()
{
    try
    {
        CTlFactory& tlFactory = CTlFactory::GetInstance();
        //Check No Cam
        if ( tlFactory.EnumerateDevices(m_devices) == 0 )
        {
            //No Cam and Releases all pylon resources.
            PylonTerminate();
            return -1;
        }

        // Create an array of instant cameras for the found devices and avoid exceeding a maximum number of devices.
        m_cams = new CInstantCameraArray(min( m_devices.size(), m_c_maxCamerasToUse));
        // Create and attach all Pylon Devices.
        for ( size_t i = 0; i < m_cams->GetSize(); ++i)
        {
             (*m_cams)[i].Attach( tlFactory.CreateDevice(m_devices[i]));
             pImageBuffer[i] = new uint8_t[m_cam_width*m_cam_height];
            //Print the model name of the camera.
            //cout << "Using device " << cameras[ i ].GetDeviceInfo().GetModelName() << endl;
            //m_cams[i].GetTLNodeMap()
        }
    }
    catch (const GenericException &e)
    {
        // Error handling      
        cerr<<e.GetDescription();
        return -2;
    }

    return 0;
}

//相机采集
int basler_cam::snap(int cam_index)
{
    message="Unknown";
    //index 超过 cam num
    if(cam_index + 1 > (*m_cams).GetSize())
    {
        message="camera index beyond the size";
        return -1;
    }

    try
    {
        CGrabResultPtr ptrGrabResult;
       (*m_cams)[cam_index].StartGrabbing(1);
       while ( (*m_cams)[cam_index].IsGrabbing())
       {
           // Wait for an image and then retrieve it. A timeout of 2000 ms is used.
           (*m_cams)[cam_index].RetrieveResult( 2000, ptrGrabResult, TimeoutHandling_ThrowException);
       }
       // Image grabbed successfully?
       if (!ptrGrabResult->GrabSucceeded())
       {
           message="Grab failed";
           return -2;
       }
       (uint8_t *) ptrGrabResult->GetBuffer();
       memcpy(pImageBuffer[cam_index],ptrGrabResult->GetBuffer(), m_cam_width*m_cam_height*sizeof(uint8_t));

    }
    catch (const GenericException &e)
    {
        // Error handling.
        //cerr << "An exception occurred." << endl
        message=QString("An exception occurred.  ")+e.GetDescription();
        return -3;
    }

    return 0;
}

//相机关闭
int basler_cam::exit()
{
    for(int i = 0;i< m_buffer_num ;i++)
    {
        if(pImageBuffer[i] != NULL)
        {
            delete pImageBuffer[i];
        }
        pImageBuffer[i] = NULL;
    }

    if(m_cams != NULL)
    {
        delete(m_cams);
        m_cams = NULL;
    }

    PylonTerminate();

    return 0;
}




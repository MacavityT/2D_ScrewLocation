// Balser.cpp : 定义 DLL 应用程序的导出函数。
//

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed __int64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned __int64    UINT64, *PUINT64;


#include <windows.h>
#include <Windows.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\video.hpp>
using namespace cv;
using namespace std;   

#include "PylonC.h"
#pragma comment(lib, "PylonC_MD_vc120.lib")

#ifdef DEBUG
#pragma comment(lib, "opencv_core246d.lib")
#pragma comment(lib, "opencv_highgui246d.lib")
#pragma comment(lib, "opencv_imgproc246d.lib")
#pragma comment(lib, "opencv_video246d.lib")
#else
#pragma comment(lib, "opencv_core246.lib")
#pragma comment(lib, "opencv_highgui246.lib")
#pragma comment(lib, "opencv_imgproc246.lib")
#pragma comment(lib, "opencv_video246.lib")
#endif

#define CAMERA_MAX (32)

typedef struct CAM_INFO_
{
	PYLON_DEVICE_HANDLE  hPylon;
	int32_t payloadSize;
	UINT8 *imgBuf;
	int32_t img_size;
}CAM_INFO;

#define IC_ERROR     0
#define IC_SUCCESS     1

static Exception *msg_e;
static int lib_init = IC_ERROR;
static int numDevices = 0;		//相机数量
static CAM_INFO cam_info[CAMERA_MAX];

static int cam_get_idx(int uid)
{
	char c = uid + 0x30;
	char t;
	int idx;
	PylonDeviceInfo_t info;

	for(idx = 0; idx < numDevices; idx++)
	{
		memset(&info, 0, sizeof(info));
		PylonGetDeviceInfo(idx, &info);

		t = info.UserDefinedName[3];
		if(c == t) //user name格式为cam0 cam1 cam2 cam3
			return idx;	
	}
	return -1;
}

void cam_init()
{
	if(IC_SUCCESS == lib_init)
		return;

	try
	{
		PylonInitialize();
	}
	catch (Exception* e)
	{
		msg_e = e;
	}

	lib_init = IC_SUCCESS;
}

UINT32 cam_open(int uid)
{
	try
	{
		int idx;
		GENAPIC_RESULT          res; 

		CAM_INFO *cam = &cam_info[uid];

		idx = cam_get_idx(uid);
		if(idx < 0)
			return 1;

		if(NULL == cam->hPylon)
			res = PylonCreateDeviceByIndex(idx, &cam->hPylon);

		if(NULL == cam->hPylon)
			return 1;

		res = PylonDeviceOpen(cam->hPylon, PYLONC_ACCESS_MODE_CONTROL | PYLONC_ACCESS_MODE_STREAM );

		int32_t payloadSize = 0;
		//isAvail = PylonDeviceFeatureIsAvailable(cam->hPylon, "EnumEntry_TriggerSelector_FrameBurstStart");
		res = PylonDeviceGetIntegerFeatureInt32(cam->hPylon, "PayloadSize", &payloadSize );	
		cam->payloadSize = payloadSize;
		if((payloadSize > 0) && (payloadSize != cam->img_size))
		{
			if(NULL != cam->imgBuf)
			{
				free(cam->imgBuf);
				cam->imgBuf = NULL;
			}
			cam->imgBuf = (unsigned char*) malloc(payloadSize);
			cam->img_size = payloadSize;
		}
	}
	catch (Exception* e)
	{
		msg_e = e;
	}	
	return 0;
}

Mat cam_snap(int uid)
{
	try
	{
		if(IC_SUCCESS != lib_init)
			return Mat();

		CAM_INFO *cam = &cam_info[uid];

		//if(NULL == cam->hPylon)
		//	cam_basler_gige_open(cam);

		if(NULL == cam->hPylon)
			return Mat();

		if(cam->payloadSize < 1)
			return Mat();

		if(NULL == cam->imgBuf)
			return Mat();

		PylonGrabResult_t grabResult;
		GENAPIC_RESULT          res;
		bool bufferReady;

		res = PylonDeviceGrabSingleFrame(cam->hPylon, 0, cam->imgBuf, cam->payloadSize,
			&grabResult, &bufferReady, 500 );
		if ( grabResult.Status != Grabbed )
			return Mat();

		/* Success. Perform image processing. */
		//getMinMax( imgBuf, grabResult.SizeX, grabResult.SizeY, &min, &max );
		//printf("Grabbed frame #%2d. Min. gray value = %3u, Max. gray value = %3u\n", i+1, min, max);

		/* Display image */
		//res = PylonImageWindowDisplayImageGrabResult(0, &grabResult);

		//cam->imgBuf, grabResult.pBuffer, mat.data为同一个地址
		if(PixelType_Mono8 == grabResult.PixelType) //
		{
			Mat iMat(grabResult.SizeY, grabResult.SizeX, CV_8UC1, (UINT8*)grabResult.pBuffer);
			//Mat re;
			//iMat.copyTo(re);
			return iMat;
		}
		else
		{
			Mat iMat;
			return iMat;
		}	
	}
	catch (Exception* e)
	{
		msg_e = e;
		return Mat();
	}		
}

UINT32 cam_close(int uid)
{
	try
	{
		if(IC_SUCCESS != lib_init)
			return 1;

		CAM_INFO *cam = &cam_info[uid];

		if(NULL == cam->hPylon)
			return 3;

		GENAPIC_RESULT res; 
		res = PylonDeviceClose(cam->hPylon);
		res = PylonDestroyDevice (cam->hPylon);
		cam->hPylon = NULL;
		cam->payloadSize = 0;
		if(NULL != cam->imgBuf)
		{
			free(cam->imgBuf);
			cam->imgBuf = NULL;
			cam->img_size = 0;
		}
	}
	catch (Exception* e)
	{
		msg_e = e;
	}	
	return 0;
}

UINT32 cam_num()
{
	GENAPIC_RESULT          res; 
	size_t size = 0;


	cam_init();

	numDevices = 0;
	try
	{
		res = PylonEnumerateDevices( &size );
	}
	catch (Exception* e)
	{
		msg_e = e;
	}

	numDevices = (int)size;
	if(numDevices >= CAMERA_MAX)
		numDevices = CAMERA_MAX;

	return numDevices;
}

int cam_write_gray(int uid, int val)
{
	/*
	BOOL                    isAvail;
	isAvail = PylonDeviceFeatureIsAvailable(cam->hPylon, "EnumEntry_PixelFormat_Mono8");
	if (isAvail )
		res = PylonDeviceFeatureFromString(cam->hPylon, "PixelFormat", "Mono8" );
	*/
	return 0;
}

int cam_write_trig(int uid, int val)
{
	return 0;
}

int cam_write_gain(int uid, double val)
{
	if(IC_SUCCESS != lib_init)
		return 1;

	CAM_INFO *cam = &cam_info[uid];

	if(NULL == cam->hPylon)
		return 3;

	GENAPIC_RESULT res; 

	int64_t gain;
	int64_t gain_min = 0;
	int64_t gain_max = 0;
	int64_t gain_incr = 0;
	int64_t gain_set = 0;

	res = PylonDeviceGetIntegerFeatureMin(cam->hPylon,"GainRaw",&gain_min);
	res = PylonDeviceGetIntegerFeatureMax(cam->hPylon,"GainRaw",&gain_max);
	res = PylonDeviceGetIntegerFeatureInc( cam->hPylon,"GainRaw", &gain_incr);
		
	gain = (int64)val;

	if(0 == gain_incr)
		gain_incr = 1;

	if(gain < gain_min)
		gain_set = gain_min;

	if(gain_set > gain_max)
		gain_set = gain_max;

	int64_t b1 = (int64_t)gain/gain_incr;
	gain_set = b1*gain_incr;
	res = PylonDeviceSetIntegerFeature(cam->hPylon,"GainRaw",gain_set);

	return 0;
}

int cam_write_exposetime(int uid, double val)
{
	/*
	isAvail = PylonDeviceFeatureIsWritable(cam->hPylon, "ExposureTimeRaw");

	res = PylonDeviceSetIntegerFeature(cam->hPylon, "Width", width);
	res = PylonDeviceSetIntegerFeature(cam->hPylon, "Height", height);


	int64_t exposure_min = 0;
	int64_t exposure_max = 0;
	int64_t exposure_incr = 0;
	int64_t exposure_set = 0;

	res = PylonDeviceGetIntegerFeatureMin(cam->hPylon,"ExposureTimeRaw",&exposure_min);
	res = PylonDeviceGetIntegerFeatureMax(cam->hPylon,"ExposureTimeRaw",&exposure_max);
	res = PylonDeviceGetIntegerFeatureInc( cam->hPylon,"ExposureTimeRaw", &exposure_incr);
	if(0 == exposure_incr)
	exposure_incr = 1;

	if(exposure_time < exposure_min)
	exposure_set = exposure_min;

	if(exposure_time > exposure_max)
	exposure_set = exposure_max;

	int64_t b = (int64_t)exposure_time/exposure_incr;
	exposure_set = b*exposure_incr;

	res = PylonDeviceSetIntegerFeature(cam->hPylon, "ExposureTimeRaw", exposure_set);
	*/
	return 0;
}

int cam_write_sharpness(int uid, double val)
{
	return 0;
}

int cam_write_gamma(int uid, double val)
{
	return 0;
}

int cam_write_framesize(int uid, double val)
{
	return 0;
}

int cam_write_timeout(int uid, double val)
{
	return 0;
}

void cam_exit()
{
	if(IC_SUCCESS != lib_init)
		return;

	try
	{
		PylonTerminate();
	}
	catch (Exception* e)
	{
		msg_e = e;
	}
}


#ifndef MYTHREADS_H
#define MYTHREADS_H
#include <QObject>
#include <QDebug>
#include <QThread>

#include <cpp/HalconCpp.h>
#include <halfunc.h>
#include <cam.h>
#include "modbus_tcp_server.h"

using namespace Halcon;
class MyThreads:public QObject
{
    Q_OBJECT
public:
    //使用合成构造函数
    basler_cam* p_cam;
    void param_set(basler_cam* cam);
public slots:
    void slot_heartbeat_sender_control(modbus_tcp_server* m_modbus);
    void slot_image_capture(int window,int enable);
};

#endif // MYTHREADS_H

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
    //构造函数由编译器自动生成
    //控制对象及功能函数
    basler_cam* p_cam;
    void param_set(basler_cam* cam);
    //外部控制标志位
    bool m_continue=false;
signals:
    void signal_transmit_image(Hobject);
public slots:
    void slot_heartbeat_sender_control(modbus_tcp_server* m_modbus);
    void slot_image_capture();
};

#endif // MYTHREADS_H

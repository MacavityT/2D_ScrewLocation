#include "mythreads.h"

//心跳线程
void MyThreads::param_set(basler_cam* cam)
{
    p_cam=cam;
}

void MyThreads::slot_heartbeat_sender_control(modbus_tcp_server* m_modbus)
{
    while (true) {
        if(m_modbus->main_thread_quit)
            return;
        QThread::sleep(1);
        qDebug()<<"send data from thread:" <<QThread::currentThreadId();
        m_modbus->send_heartbeat_message();
    }
}

void MyThreads::slot_image_capture(int window, int enable)
{
    while (true) {
        if(enable)
        {
            p_cam->snap(0);
        }
    }
}

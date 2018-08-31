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
        m_modbus->send_heartbeat_message();
    }
}

void MyThreads::slot_image_capture()
{
    Hobject m_image;
    int m_cam_width=2592;
    int m_cam_height=1944;
    while (m_continue) {
        QThread::sleep(1);
        if(0==p_cam->snap(0))
        {
            gen_image1(&m_image,"byte",m_cam_width,m_cam_height,(Hlong)p_cam->pImageBuffer[0]);
            emit signal_transmit_image(m_image);
        }
    }
}

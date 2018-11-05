#ifndef MODBUS_TCP_SERVER_H
#define MODBUS_TCP_SERVER_H

#include <QModbusServer>
#include <QModbusTcpServer>
#include <QModbusDataUnit>
#include <QObject>
#include <QThread>
#include <QDebug>

#include <vector>
#include <math.h>
#include <bitset>

#include "inifile.h"

#define u8 unsigned char

using namespace std;

class modbus_tcp_server:public QObject
{
    Q_OBJECT

public:
    //拷贝构造函数
    modbus_tcp_server(const modbus_tcp_server& obj)
    {
        modbusDevice=new QModbusTcpServer();//相同大小的内存地址
        modbusDevice=obj.modbusDevice;//此方法传地址，析构时会报错
//        *(this->modbusDevice)=*(obj.modbusDevice);//QObject 或者其子类不允许copy或者operator=
    }
    //重载拷贝赋值运算符（也没啥用，因为QObject不允许使用重载的operator= 或者拷贝构造函数来copy其对象）
//    const modbus_tcp_server& operator=(const modbus_tcp_server& obj)
//    {
//        if(this!=&obj)
//        {
//            *(this->modbusDevice)=*(obj.modbusDevice);
//        }
//        return *this;
//    }
    //默认构造函数
    modbus_tcp_server();
    ~modbus_tcp_server();

    static bool main_thread_quit;
    //connect parameters
    QString port;
    int server_address;
    //用于调用操作，连接plc
    int connection(bool connect_flag);
    //发送心跳信号给PLC
    void send_heartbeat_message();

private:
    QModbusTcpServer *modbusDevice;
    //Control object
    IniFile m_ini_reader;
    //read&write data
    quint16 value;
    QModbusDataUnit m_data;
    QModbusDataUnit read_data;
    QModbusDataUnit write_data;
    //Heart beat for plc
    bool heartbeat_flag=true;
    //data convert function
    float quint_to_float(QVector<quint16> data, quint16 start_address);//两个寄存器转换为一个float
    int float_to_quint(float data,quint16 start_address);//一个float转换为两个寄存器
    //progress function
    int ini_modbus_server();
    int get_settings();

private Q_SLOTS:
    void updateWidgets(QModbusDataUnit::RegisterType table, int address, int size);//接收数据
    void onStateChanged(int state);
    void handleDeviceError(QModbusDevice::Error newError);

signals:
    void signal_connect_button_status(bool connected);
    void signal_read_data(float screwdriver,float screw,\
                          float enable,float receive,float reserve);
public slots:   
    //服务器数据设置（发送数据由PLC主动读取）
    int  setupDeviceData(float x_coor,float y_coor,float complete,float heartbeat,float reserve);
};

#endif // MODBUS_TCP_SERVER_H

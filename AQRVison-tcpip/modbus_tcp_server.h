#ifndef MODBUS_TCP_SERVER_H
#define MODBUS_TCP_SERVER_H

#include <QModbusServer>
#include <QModbusDataUnit>
#include <QObject>
#include <QThread>
#include <QDebug>

#include "inifile.h"

class modbus_tcp_server:public QObject
{
    Q_OBJECT

public:
    modbus_tcp_server();
    ~modbus_tcp_server();

private:
    //Control object
    IniFile m_ini_reader;
    QModbusServer *modbusDevice;
    //connect parameters
    QString port;
    int server_address;
    //capture data
    quint16 value;
    //send data
    bool coils[10];
    bool discrete[10];
    int input_registers[10];
    int holding_registers[10];
    //progress function
    int ini_modbus_server();
    int setupDeviceData(int mode);//1.coils读写 2.discrete inputs只读 3.Input Registers只读 4.Holding Registers读写
    int get_settings();
    int connection(bool connect_flag);

private Q_SLOTS:
    void updateWidgets(QModbusDataUnit::RegisterType table, int address, int size);
    void onStateChanged(int state);
    void handleDeviceError(QModbusDevice::Error newError);
};

#endif // MODBUS_TCP_SERVER_H

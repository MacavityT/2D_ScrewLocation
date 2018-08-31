#include "modbus_tcp_server.h"
#include <QModbusTcpServer>
#include <QRegularExpression>
#include <QUrl>
bool modbus_tcp_server::main_thread_quit=false;

modbus_tcp_server::modbus_tcp_server()
    :modbusDevice(nullptr)
{
    qRegisterMetaType<QModbusDataUnit>("QModbusDataUnit");
    qRegisterMetaType<QModbusDataUnit::RegisterType>("QModbusDataUnit::RegisterType");
    qRegisterMetaType<QModbusDevice::State>("QModbusDevice::State");
    qRegisterMetaType<QModbusTcpServer*>("QModbusTcpServer*");
    get_settings();
    ini_modbus_server();
}

modbus_tcp_server::~modbus_tcp_server()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;
    modbusDevice=nullptr;
}

int modbus_tcp_server::get_settings()
{
    //!!此处应该在设置界面添加LineEdit，显示port号
    //读取连接参数
    m_ini_reader.read("TCP_Param","port",port);
    m_ini_reader.read("TCP_Param","server_address",server_address);
    //注册写入参数
    QModbusDataUnit data_1(QModbusDataUnit::HoldingRegisters,0,10);
    write_data=data_1;
    //注册读取参数
    QModbusDataUnit data_2(QModbusDataUnit::HoldingRegisters,21,10);
    read_data=data_2;

    return 0;
}

int modbus_tcp_server::ini_modbus_server()
{
    if(modbusDevice)
    {
        modbusDevice->disconnect();
        delete modbusDevice;
        modbusDevice=nullptr;
    }

    modbusDevice=new QModbusTcpServer(this);
    if(!modbusDevice)
    {
        //!!此处在主界面添加连接按钮,并且设置使能信号
        //ui->connectbutton->setEsnable(true);
        return -1;
        qDebug()<<"Could not create Modbus server.";
    }
    else
    {
        //初始化modbus类，设置各项参数
        QModbusDataUnitMap reg;
        reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
        reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
        reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
        reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });

        modbusDevice->setMap(reg);

        connect(modbusDevice, &QModbusServer::stateChanged,
                this, &modbus_tcp_server::onStateChanged);
        connect(modbusDevice, &QModbusServer::errorOccurred,
                this, &modbus_tcp_server::handleDeviceError);
        connect(modbusDevice, &QModbusServer::dataWritten,
                this, &modbus_tcp_server::updateWidgets);//连接数据读取

        //此部分等待添加主界面控件后完善（繁忙模式，处理长信号）
//        connect(ui->setBusyBox, &QCheckBox::toggled, this, [this](bool toggled) {
//            if (modbusDevice)
//                modbusDevice->setValue(QModbusServer::DeviceBusy, toggled ? 0xffff : 0x0000);
//        });
//        emit ui->setBusyBox->toggled(ui->setBusyBox->isChecked());
    }
    return 0;
}

//连接状态变更处理
void modbus_tcp_server::onStateChanged(int state)
{
    if(main_thread_quit)
        return;//主线程准备退出，因为析构函数为先调用自身再调用成员变量，则应在析构之前停止发送
    if (state == QModbusDevice::UnconnectedState)
        emit signal_connect_button_status(false);
    else if (state == QModbusDevice::ConnectedState)
        emit signal_connect_button_status(true);
}

void modbus_tcp_server::handleDeviceError(QModbusDevice::Error newError)
{
    if (newError == QModbusDevice::NoError || !modbusDevice)
        return;
}

//接收数据
void modbus_tcp_server::updateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    if(size<3)
        return;//心跳
    float screwdriver=quint_to_float(20);
    float screw=quint_to_float(22);
    float enable=quint_to_float(24);
    float receive=quint_to_float(26);
    float reserve=quint_to_float(28);
    emit signal_read_data(screwdriver,screw,enable,receive,reserve);
}

//接收数据转换
float modbus_tcp_server::quint_to_float(quint16 start_address)
{
    float data;
    long double high_bit;
    long double low_bit;
    long double whole;
    high_bit=read_data.value(start_address+1)*pow(0x10,4);
    low_bit =read_data.value(start_address);
    whole=high_bit+low_bit;
    data=*((float*)&whole);//内存格式转换

    return data;
}

//发送数据
int modbus_tcp_server::setupDeviceData(float x_coor,float y_coor,\
                                       float complete,float heartbeat,float reserve)
{
    //heartbeat信息由单独线程发送
    if(!modbusDevice)
        return -1;
    //数据转换
    float_to_quint(x_coor,0);
    float_to_quint(y_coor,2);
    float_to_quint(complete,4);
    //数据发送
    modbusDevice->setData(write_data);

    return 0;
}

//待发送数据转换
int modbus_tcp_server::float_to_quint(float data,quint16 start_address)
{
    quint16 high_bit;
    quint16 low_bit;
    long double whole;
    whole=*((long double*)&data);
    high_bit=whole/pow(0x10,4);
    low_bit=whole-high_bit*pow(0x10,4);
    write_data.setValue(start_address+1,high_bit);
    write_data.setValue(start_address,low_bit);

    return 0;
}

//连接服务器
int modbus_tcp_server::connection(bool connect_flag)
{
    bool intendToConnect = (modbusDevice->state() == QModbusDevice::UnconnectedState);
    if(intendToConnect&&connect_flag)
    {
        //创建连接
        const QUrl url=QUrl::fromUserInput(port);
        //set url parameters
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter,url.port());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter,url.host());
        //set server address
        modbusDevice->setServerAddress(server_address);
        if(!modbusDevice->connectDevice())
        {
            //connect failed and show messages
            return -1;
        }
        else
        {
            //connect succeed and show messages
            return 0;
        }
    }
    else if(!intendToConnect&&!connect_flag)
    {
        //断开连接
        modbusDevice->disconnectDevice();
    }
    else
    {
        return 0;
    }
    return 0;
}

//发送心跳连接(在MainWindow类中moveToThread)
void modbus_tcp_server::send_heartbeat_message()
{
    if(!modbusDevice)
        return;//连接失效

    //发送心跳信号
    qDebug()<<"set data from thread:" <<QThread::currentThreadId();
    bool status;
    if(heartbeat_flag)
    {
        status=modbusDevice->setData(QModbusDataUnit::HoldingRegisters,7,0);
        if(status)
        {
            qDebug()<<"Heartbeat-0";
        }
    }
    else
    {
        status=modbusDevice->setData(QModbusDataUnit::HoldingRegisters,7,0x3f80);//ox3f80 0000 为浮点数1.0
        if(status)
        {
            qDebug()<<"Heartbeat-1";
        }
    }
    modbusDevice->setData(QModbusDataUnit::HoldingRegisters,6,0);
    heartbeat_flag=!heartbeat_flag;
}

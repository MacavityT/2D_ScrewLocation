#include "modbus_tcp_server.h"
#include <QModbusTcpServer>
#include <QRegularExpression>
#include <QUrl>

modbus_tcp_server::modbus_tcp_server()
    :modbusDevice(nullptr)
{
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

void modbus_tcp_server::onStateChanged(int state)
{
    bool connected = (state != QModbusDevice::UnconnectedState);
//    ui->actionConnect->setEnabled(!connected);
//    ui->actionDisconnect->setEnabled(connected);

    if (state == QModbusDevice::UnconnectedState)
//        ui->connectButton->setText(tr("Connect"));
        qDebug()<<"Connect";
    else if (state == QModbusDevice::ConnectedState)
//        ui->connectButton->setText(tr("Disconnect"));
        qDebug()<<"Disconnect";
}

void modbus_tcp_server::handleDeviceError(QModbusDevice::Error newError)
{
    if (newError == QModbusDevice::NoError || !modbusDevice)
        return;

//    statusBar()->showMessage(modbusDevice->errorString(), 5000);
}

//获取数据
void modbus_tcp_server::updateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (int i = 0; i < size; ++i)
    {
        switch (table) {
        case QModbusDataUnit::Coils:
            modbusDevice->data(QModbusDataUnit::Coils, address + i, &value);
//            coilButtons.button(address + i)->setChecked(value);//数据处理
            break;
        case QModbusDataUnit::HoldingRegisters:
            modbusDevice->data(QModbusDataUnit::HoldingRegisters, address + i, &value);
//            registers.value(QStringLiteral("holdReg_%1").arg(address + i))->setText(text
//                .setNum(value, 16));//数据处理
            break;
        default:
            break;
        }
    }
}

//发送数据
int modbus_tcp_server::setupDeviceData(int mode)
{
    if(!modbusDevice)
        return -1;

    //1.coils读写 2.discrete inputs只读 3.Input Registers只读 4.Holding Registers读写
    //1,2为位变量   3,4为16-bit整型
    switch (mode) {
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    default:
        break;
    }
    return 0;
}

int modbus_tcp_server::connection(bool connect_flag)
{
    bool intendToConnect = (modbusDevice->state() == QModbusDevice::UnconnectedState);
    if(intendToConnect&&connect_flag)
    {
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

#include "dialogsetting.h"
#include "ui_dialogsetting.h"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);
    this->setWindowTitle("Link Parameters");
    m_ini_reader.read("TCP_Param","port",port);
    m_ini_reader.read("TCP_Param","server_address",server);
    //数据初始化
    for(int i=0;i<5;i++)
    {
        data_array[i]=NULL;
    }
    //控件初始化显示
    QString Server_address;
    ui->TcpAddress->setText(port);
    ui->TcpServer->setText(Server_address.setNum(server));
    //设置界面容器
    setupWidgetContainers();
}

DialogSetting::~DialogSetting()
{
    delete ui;
}

void DialogSetting::setupWidgetContainers()
{
    QRegularExpression regexp;
    regexp.setPattern(QLatin1String("holdReg_(?<ID>\\d+)"));
    const QList<QLineEdit *> qle = findChildren<QLineEdit *>(regexp);
    foreach (QLineEdit *lineEdit, qle) {
        lineEdit->setProperty("ID", regexp.match(lineEdit->objectName()).captured("ID").toInt());
        lineEdit->setValidator(new QRegExpValidator(QRegExp(QStringLiteral("-[0-9]{0,8}.[0-9]{0,8}"),
            Qt::CaseInsensitive), this));
        connect(lineEdit, &QLineEdit::textChanged, this, &DialogSetting::data_sender);
    }
}

void DialogSetting::data_sender(const QString &value)
{
    //Get index of activate line edit
    QString address=sender()->objectName();
    address=address.replace("holdReg_","");
    int index=address.toInt();
    if(index>4)
        return;
    //Get value
    data_array[index]=value.toFloat();
    emit signal_setupDeviceData(data_array[0],data_array[1],data_array[2],data_array[3],data_array[4]);
}

void DialogSetting::on_TcpAddress_textChanged(const QString &arg1)
{
    port=arg1;
}

void DialogSetting::on_TcpServer_textChanged(const QString &arg1)
{
    server=arg1.toInt();
}

void DialogSetting::on_HeartBeatControl_clicked()
{
    m_heartbeat=!m_heartbeat;
    if(m_heartbeat)
        ui->HeartBeatControl->setText(QString("Stop"));
    else
        ui->HeartBeatControl->setText(QString("Start"));
}

void DialogSetting::slot_read_data(float screwdriver, float screw, \
                                   float enable, float receive, float mark, float xcoor, float ycoor)
{
    QString address;
    ui->holdReg_5->setText(address.setNum(screwdriver));
    ui->holdReg_6->setText(address.setNum(screw));
    ui->holdReg_7->setText(address.setNum(enable));
    ui->holdReg_8->setText(address.setNum(receive));
    ui->holdReg_9->setText(address.setNum(mark));
    ui->holdReg_10->setText(address.setNum(xcoor));
    ui->holdReg_11->setText(address.setNum(ycoor));
}

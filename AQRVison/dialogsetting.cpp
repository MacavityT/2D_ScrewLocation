#include "dialogsetting.h"
#include "ui_dialogsetting.h"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);
    m_ini_reader.read("TCP_Param","port",port);
    m_ini_reader.read("TCP_Param","server_address",server);
    //控件初始化显示
    QString Server_address;
    ui->TcpAddress->setText(port);
    ui->TcpServer->setText(Server_address.setNum(server));
}

DialogSetting::~DialogSetting()
{
    delete ui;
}

void DialogSetting::on_TcpAddress_textChanged(const QString &arg1)
{
    port=arg1;
}

void DialogSetting::on_TcpServer_textChanged(const QString &arg1)
{
    server=arg1.toInt();
}

#include "tcpip.h"

//#########
//--客户端--
//#########
TcpIp_client::TcpIp_client()
{
    m_cl_socket = new QTcpSocket;
}

TcpIp_client::~TcpIp_client()
{
    m_cl_socket->close();
    delete m_cl_socket;
    m_cl_socket = nullptr;
}

//tcpip客户端初始化
int TcpIp_client::init(QString& ip, uint& port,
                       const std::function<int(QString, QString&)>& f)
{
    //检测IP，PORT合法性
    if (false == check(ip, (int&)port))
    {
        //m_log.write(QString("TcpIp_client::init: ip, port error!!!"));
        return -1;
    }

    //connect
    m_cl_socket->abort();
    m_cl_socket->connectToHost(ip, port);

    //连接超时
    if (!m_cl_socket->waitForConnected(30000))
    {
        //m_log.write(QString("TcpIp_client::init: connect timeout!!!"));
        return -2;
    }

    //关联
    QObject::connect(m_cl_socket, &QTcpSocket::readyRead, this, &TcpIp_client::read);

    //函数绑定
    func = f;

    return 0;
}

//用于接收服务端的消息
int TcpIp_client::read()
{
    QByteArray buf;
    buf = m_cl_socket->readAll();
    QString ser_data = QString::fromLocal8Bit(buf);

    //判断消息是否为空
    if (true == ser_data.isEmpty())
    {
       //m_log.write(QString("TcpIp_client::read: server data is empty!!!"));
       return -1;
    }

    //协议解析
    QString res = "";
    func(ser_data, res);

    //发射信号
    emit tcpip_cli_signal(res);

    return 0;
}

//往服务端发送数据
int TcpIp_client::write(const QString &content)
{
    if (-1 == m_cl_socket->write(content.toLocal8Bit()))
    {
        //m_log.write(QString("TcpIp_client::write: socket write error!!!"));
        return -1;
    }

    m_cl_socket->flush();

    return 0;
}

//用于判断IP，PORT合法性
bool TcpIp_client::check(const QString& ip, const int& port)
{
    if (false == ip.isEmpty() && port > 0 && port <= 65535)
    {
        QString pattern("^(((\\d{1,2})|(1\\d{2})|(2[2-4]\\d)|(25[0-5]))\\.){3}((\\d{1,2})|(1\\d{2})|(2[2-4]\\d)|(25[0-5]))$");
        QRegExp rx(pattern);

        return rx.exactMatch(ip);
    }

    return false;
}


//#########
//--服务端--
//#########
TcpIp_server::TcpIp_server()
{
    m_server = new QTcpServer;
}

TcpIp_server::~TcpIp_server()
{
    m_server->close();
    delete m_server;
    m_server = nullptr;

    if (m_socket != nullptr)
    {
        //delete m_socket;
        m_socket = nullptr;
    }
}

//tcpip服务端初始化
int TcpIp_server::init(uint &port, const std::function<int(QString, QString&)>& f)
{
    //检测IP，PORT合法性
    if (false == check((int&)port))
    {
        //m_log.write(QString("TcpIp_server::init: port error!!!"));
        return -1;
    }

    //listening
    if (!m_server->listen(QHostAddress::Any, port))
    {
        //m_log.write(QString("TcpIp_server::init: listening error!!!"));
        return -2;
    }

    //关联
    QObject::connect(m_server, &QTcpServer::newConnection, this, &TcpIp_server::newConnection);

    //函数绑定
    func = f;

    return 0;
}

//向客户端发消息
int TcpIp_server::write(const QString &content)
{
    if (-1 == m_socket->write(content.toLocal8Bit()))
    {
        //m_log.write(QString("TcpIp_server::write: socket write error!!!"));
        return -1;
    }

    m_socket->flush();

    return 0;
}

//检测port合法性
bool TcpIp_server::check(int& port)
{
    if (port > 0 && port <= 65535)
    {
        return true;
    }

    return false;
}

//新连接处理
void TcpIp_server::newConnection()
{
    m_socket = m_server->nextPendingConnection();
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &TcpIp_server::read);
}

//读取客户端发来的消息
int TcpIp_server::read()
{
    QByteArray buf;
    buf = m_socket->readAll();
    QString cli_data = QString::fromLocal8Bit(buf);

    //判断消息是否为空
    if (true == cli_data.isEmpty())
    {
        //m_log.write(QString("TcpIp_server::read: client data is empty!!!"));
        return -1;
    }

    //协议解析
    QString res = "";
    func(cli_data, res);

    //发射信号
    emit tcpip_ser_signal(res);

    return 0;
}


//module：  TcpIp
//version:  V1.1
//author:   Wei Wu
//date:     2018-07-02
//remark:   封装了tcpip，提供基本的init, write方法
//          补充必要的开发说明

//
//客户端：
//描述：    用于tcpip通信需求，开发人员需在应用层实现自己的应用层协议解析函数，其包括两个参数，第一
//          个为传入变量，是服务端发送来的数据，QString类型；第二个为传出变量，是协议解析后的结果，
//          QString类型。当服务端有数据发送来时该模块会发射tcpip_cli_signal(QString res)信号，
//          其中res为经过应用层协议(需自定义，见下方描述)解析后的结果。
//
//用法：
//init：    直接调用对象的init方法进行初始化，其参数为3个。第一个为ip地址，QString类型；
//          第二个为端口号，uint类型；第三个为函数指针，指应用层协议解析的函数，包括两个参数：
//              第一个为传入变量，是服务端发送来的数据，QString类型；第二个为传出变量，是协议解析后
//              的结果，QString类型。
//
//返回值：  正常值为0，表示初始化成功；-1为IP或者端口号有误，-2为服务器连接失败或者超时。
//
//write：   当需要向服务端发送数据时直接调用对象的write方法，其参数为需要发送的内容，为QString类型。
//
//返回值：  正常值为0，表示发送成功；-1为发送失败。
//
//
//服务端：
//描述：    用于tcpip通信需求，开发人员需在应用层实现自己的应用层协议解析函数，其包括两个参数，第一
//          个为传入变量，是客户端发送来的数据，QString类型；第二个为传出变量，是协议解析后的结果，
//          QString类型。当客户端有数据发送来时该模块会发射tcpip_ser_signal(QString res)信号，
//          其中res为经过应用层协议(需自定义，见下方描述)解析后的结果。
//
//用法：
//init：    直接调用对象的init方法进行初始化，其参数为2个。第一个为端口号，uint类型；第二个为函数指针，
//          指应用层协议解析的函数，包括两个参数：
//              第一个为传入变量，是客户端发送来的数据，QString类型；第二个为传出变量，是协议解析后
//              的结果，QString类型。
//
//返回值：  正常值为0，表示初始化成功；-1为IP或者端口号有误，-2为本机作为服务器绑定监听失败。
//
//write：   当需要向客户端发送数据时直接调用对象的write方法，其参数为需要发送的内容，为QString类型。
//
//返回值：  正常值为0，表示发送成功；-1为发送失败。
//

#ifndef TCPIP_H
#define TCPIP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QRegExp>
#include <QObject>
#include <functional>

namespace tcpip {
    class TcpIp_client;
    class TcpIp_server;
}

//客户端
class TcpIp_client : public QObject
{
    Q_OBJECT

public:
    TcpIp_client();
    ~TcpIp_client();

    int init(QString& ip, uint& port,\
       const std::function<int(QString, QString&)>& f);  //TCPIP客户端初始化
    int write(const QString& content);                   //向服务端发送数据

signals:
    void tcpip_cli_signal(QString res);                  //信号

private:
    QTcpSocket* m_cl_socket;
    std::function<int(QString, QString&)> client_protocol;          //上层协议解析函数

    int read();                                          //接收服务端发来的数据
    bool check(const QString& ip, const int& port);      //检测IP，PORT合法性
};

//服务端
class TcpIp_server : public QObject
{
    Q_OBJECT

public:
    TcpIp_server();
    ~TcpIp_server();

    int init(uint& port,
       const std::function<int(QString, QString&)>& f);  //TCPIP服务端初始化
    int write(const QString& content);                   //向客户端发送数据

signals:
    void tcpip_ser_signal(QString res);                  //信号

private:
    QTcpServer* m_server;
    QTcpSocket* m_socket;
    std::function<int(QString, QString&)> server_protocol;          //上层协议解析函数

    int read();                                          //接收客户端发来的数据
    bool check(int& port);                               //检测PORT合法性
    void newConnection();                                //响应新连接
};

#endif // TCPIP_H


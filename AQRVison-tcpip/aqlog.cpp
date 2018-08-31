#include "aqlog.h"

aqlog::aqlog()
{
    m_path_exe = QCoreApplication::applicationDirPath();

    QString res;
    //获取当前时间
    QDateTime cur_date_time = QDateTime::currentDateTime();
    QString qs_date = cur_date_time.toString("yyyy-MM-dd");
    QString qs_time = cur_date_time.toString("hh-mm-ss");

    //创建文件夹
    QDir csv_dir(m_path_exe + "/log/" + qs_date);

    if (false == csv_dir.exists())
    {
        bool b_create_path = csv_dir.mkpath(m_path_exe + "/log/" + qs_date);
        if (false == b_create_path)
        {
            QMessageBox msg;
            msg.setText("log created failed!");
            msg.exec();
        }
    }

    QString csv_name = qs_date +"-"+ qs_time + ".txt";
    m_path = m_path_exe + "/log/" + qs_date + "/" + csv_name;

    //txt 写入抬头
    m_file = new QFile(m_path);
    if (!m_file->open(QIODevice::Append | QIODevice::Text))
    {
        //??
//        QMessageBox box;
//        box.setText(QString("创建log文件失败！"));
//        box.exec();
        return;
    }

    QString content = QString("--------------\n");
    qint64 ires = -1;
    ires = m_file->write(content.toLocal8Bit(), content.toLocal8Bit().length());
    if (-1 == ires)
    {
        QMessageBox box;
        box.setText("写入抬头log文件失败！!");
        box.exec();
        return;
    }

    m_file->close();
}

aqlog::~aqlog()
{
    delete m_file;
}

int aqlog::write_log(QString str)
{
    QString content = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz") + ",";
    content += str + "\n";

    if (!m_file->open(QIODevice::Append | QIODevice::Text))
    {
        return -1;
    }

    qint64 res = -1;
    res = m_file->write(content.toLocal8Bit(), content.toLocal8Bit().length());
    if (-1 == res)
    {
        return -2;
    }

    m_file->close();

    return 0;
}

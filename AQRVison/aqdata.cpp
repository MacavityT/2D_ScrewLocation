
#include "AQdata.h"

AQData::AQData()
{
    m_path_exe = QCoreApplication::applicationDirPath();

    QString res;
    //获取当前时间
    QDateTime cur_date_time = QDateTime::currentDateTime();
    QString qs_date = cur_date_time.toString("yyyy-MM-dd");
    QString qs_time = cur_date_time.toString("hh-mm-ss");

    //创建文件夹
    QDir csv_dir(m_path_exe + "/data/" + qs_date);

    if (false == csv_dir.exists())
    {
        bool b_create_path = csv_dir.mkpath(m_path_exe + "/data/" + qs_date);
        if (false == b_create_path)
        {
            return ;
        }
    }

    QString csv_name = qs_date +"-"+ qs_time + ".csv";
    m_path = m_path_exe + "/data/" + qs_date + "/" + csv_name;

    //csv 写入抬头
    m_file = new QFile(m_path);
    if (!m_file->open(QIODevice::Append | QIODevice::Text))
    {
        return ;
    }

    QString content = QString("日期-时间,pix-x,pix-y\n");
    qint64 ires = -1;
    ires = m_file->write(content.toLocal8Bit(), content.toLocal8Bit().length());
    if (-1 == ires)
    {
        QMessageBox box;
        box.setText("写入抬头csv文件失败！!");
        box.exec();
        return;
    }

    m_file->close();
}

AQData::~AQData()
{
    delete m_file;
}

int AQData::data_write(double x, double y)
{
    //匹配到模板，保存data
    QString content = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz") + ",";
    content += QString::number(x, 10,2) + ",";
    content += QString::number(y, 10,2) + "\n";

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


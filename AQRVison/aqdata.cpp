
#include "AQdata.h"
//构建列表，第一栏为日期时间，后面为xy数据
AQData::AQData(QString name,QString content)
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

    QString csv_name = qs_date +"-"+ qs_time +"-" +name + ".csv";
    m_path = m_path_exe + "/data/" + qs_date + "/" + csv_name;

    //csv 写入抬头
    m_file = new QFile(m_path);
    if (!m_file->open(QIODevice::Append | QIODevice::Text))
    {
        return ;
    }

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

int AQData::data_write(int mark,double xcoor, double ycoor, double pix_x, double pix_y , double offsetx, double offsety, QString status, bool enable)
{
    if(!enable)
        return 0;
    //匹配到模板，保存data
    QString content = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz") + ",";
    content += QString::number(mark, 10,2) + ",";
    content += QString::number(xcoor, 10,2) + ",";
    content += QString::number(ycoor, 10,2) + ",";
    content += QString::number(pix_x, 10,2) + ",";
    content += QString::number(pix_y, 10,2) + ",";
    content += QString::number(offsetx, 10,2) + ",";
    content += QString::number(offsety, 10,2) + ",";
    content += status + "\n";

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

int AQData::data_write(int modelIndex,int screwdriver, int screw, double xcoor, double ycoor, double pix_x, double pix_y ,
                       double offsetx, double offsety, double exact_offset_x, double exact_offset_y,double x_diff,double y_diff,
                       double xcoor_revert,double ycoor_revert, double x_work_diff, double y_work_diff,
                       double circularity_light,double circularity_dark,QString status ,bool enable)
{
    if(!enable)
        return 0;
    //匹配到模板，保存data
    QString content = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz") + ",";
    content += QString::number(modelIndex, 10,2) + ",";
    content += QString::number(screwdriver, 10,2) + ",";
    content += QString::number(screw, 10,2) + ",";
    content += QString::number(xcoor, 10,2) + ",";
    content += QString::number(ycoor, 10,2) + ",";
    content += QString::number(pix_x, 10,2) + ",";
    content += QString::number(pix_y, 10,2) + ",";
    content += QString::number(offsetx, 10,2) + ",";
    content += QString::number(offsety, 10,2) + ",";
    content += QString::number(exact_offset_x, 10,2) + ",";
    content += QString::number(exact_offset_y, 10,2) + ",";
    content += QString::number(x_diff, 10,2) + ",";
    content += QString::number(y_diff, 10,2) + ",";
    content += QString::number(xcoor_revert, 10,2) + ",";
    content += QString::number(ycoor_revert, 10,2) + ",";
    content += QString::number(x_work_diff, 10,2) + ",";
    content += QString::number(y_work_diff, 10,2) + ",";
    content += QString::number(circularity_light, 10,2) + ",";
    content += QString::number(circularity_dark, 10,2) + ",";
    content += status + "\n";

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


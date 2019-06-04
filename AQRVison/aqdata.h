//module：Data
//version:V1.0
//author:wu wei
//date:2018-06-06
//

#ifndef AQDATA_H
#define AQDATA_H

#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QMessageBox>

class AQData
{
public:
     AQData(QString name,QString content);
    ~AQData();

    int data_write(int mark,double xcoor, double ycoor, double pix_x, double pix_y , double offsetx, double offsety, QString status, bool enable);
    int data_write(int threshold, int modelIndex,int screwdriver, int screw, double xcoor, double ycoor, double pix_x, double pix_y ,
                   double offsetx, double offsety, double exact_offset_x, double exact_offset_y,double x_diff,double y_diff,
                   double xcoor_revert,double ycoor_revert, double x_work_diff, double y_work_diff, QString status ,bool enable);

private:
    QFile* m_file;
    QString m_path;
    QString m_path_exe;
};

#endif // AQDATA_H

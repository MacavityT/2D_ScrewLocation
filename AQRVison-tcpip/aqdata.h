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
     AQData();
    ~AQData();

    int data_write(double x, double y);

private:
    QFile* m_file;
    QString m_path;
    QString m_path_exe;
};

#endif // AQDATA_H

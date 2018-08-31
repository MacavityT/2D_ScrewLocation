#ifndef AQLOG_H
#define AQLOG_H

#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QMessageBox>

class aqlog
{
public:
    aqlog();
    ~aqlog();
    int write_log(QString str);
private:

    QFile* m_file;
    QString m_path;
    QString m_path_exe;
};

#endif // AQLOG_H

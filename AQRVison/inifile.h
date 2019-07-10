#ifndef INIFILE_H
#define INIFILE_H

#include <QSettings>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>

// ini file operation
class IniFile
{
public:
    IniFile();
    ~IniFile();

    int write(const QString& section, const QString& key, const bool& value);
    int write(const QString& section, const QString& key, const int& value);
    int write(const QString& section, const QString& key, const double& value);
    int write(const QString& section, const QString& key, const QString& value);

    int read(const QString& section, const QString& key, bool& value);
    int read(const QString& section, const QString& key, int& value);
    int read(const QString& section, const QString& key, QString& value);
    int read(const QString& section, const QString& key, double& value);

    QSettings* configureFile;
private:
    //exe path
    QString m_path_exe;

};

#endif // INIFILE_H

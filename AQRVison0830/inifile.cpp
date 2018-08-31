#include "inifile.h"

IniFile::IniFile()
{
    m_path_exe = QCoreApplication::applicationDirPath();

    QDir dir(m_path_exe + "/ParamIni/");

    //先检测文件夹是否完备：创建
    if (false == dir.exists())
    {
        bool is_created = dir.mkpath(m_path_exe + "/ParamIni/");
        if (false == is_created)
        {
            QMessageBox msg;
            msg.setText("文件夹ParamIni创建失败!");
            msg.exec();
            return;
        }
    }

    QString Path = m_path_exe + "/ParamIni/";
    QString fileName = "param.ini";
    configureFile = new QSettings(Path + fileName, QSettings::IniFormat);

}

IniFile::~IniFile()
{
    delete configureFile;
    configureFile=nullptr;
}

int IniFile::write(const QString& section, const QString& key, const int& value)
{
    configureFile->setValue("/"+section+"/"+key, value);

    return 0;
}

int IniFile::write(const QString& section, const QString& key, const double& value)
{
    configureFile->setValue("/"+section+"/"+key, value);

    return 0;
}

int IniFile::write(const QString& section, const QString& key, const QString& value)
{
    configureFile->setValue("/"+section+"/"+key, value);

    return 0;
}

int IniFile::read(const QString& section, const QString& key, bool& value)
{
    value = configureFile -> value(section+"/"+key).toBool();

    return 0;
}

int IniFile::read(const QString& section, const QString& key, QString& value)
{
    value = configureFile -> value(section+"/"+key).toString();

    return 0;
}

int IniFile::read(const QString& section, const QString& key, int& value)
{
    value = configureFile -> value(section+"/"+key).toInt();

    return 0;
}

int IniFile::read(const QString& section, const QString& key, double& value)
{
    value = configureFile -> value(section+"/"+key).toDouble();

    return 0;
}

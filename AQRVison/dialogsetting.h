#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>
#include "inifile.h"

namespace Ui {
class DialogSetting;
}

class DialogSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetting(QWidget *parent = 0);
    ~DialogSetting();

    QString port;
    int server;
    IniFile m_ini_reader;

private slots:
    void on_TcpAddress_textChanged(const QString &arg1);

    void on_TcpServer_textChanged(const QString &arg1);

private:
    Ui::DialogSetting *ui;
};

#endif // DIALOGSETTING_H

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
    bool m_heartbeat=true;
    IniFile m_ini_reader;
private:
    float data_array[5];
    void setupWidgetContainers();
    void data_sender(const QString &value);
signals:
    void signal_setupDeviceData(float,float,float,float,float);
public slots:
    void slot_read_data(float,float,float,float,float,float,float);

private slots:
    void on_TcpAddress_textChanged(const QString &arg1);

    void on_TcpServer_textChanged(const QString &arg1);

    void on_HeartBeatControl_clicked();

private:
    Ui::DialogSetting *ui;
};

#endif // DIALOGSETTING_H

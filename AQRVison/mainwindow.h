#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QFile>
#include <QPushButton>
#include <QDebug>
#include <QObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QRegExp>
#include <QThread>
#include <QTextCodec>
#include <map>

#include "cpp/HalconCpp.h"
#include "halfunc.h"
#include "dialogcalibration.h"
#include "dialogsetting.h"
#include "dialogshapemodel.h"
#include "cam.h"
#include "aqdata.h"
#include "aqlog.h"
#include "inifile.h"
#include "modbus_tcp_server.h"
#include "mythreads.h"

using namespace Halcon;

namespace Ui {
class MainWindow;
}

typedef struct
{
    double x;
    double y;
} aqPt;

struct cal_data
{
    aqPt StdW,StdP;
    aqPt LuoW;
    aqPt W1,W2,W3,W4;
    aqPt P1,P2,P3,P4;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
public:
    //运行标志位
    static bool Runtime;
    //data模块
    AQData m_data_file_csv;
    //采集模块
    basler_cam m_snap_cam;
    int m_cam_width,m_cam_height;
    //界面对象
    Dialog m_param_dialog;
    DialogShapeModel m_shape_model_dialog;
    DialogSetting m_setting_dialog;
    //ini
    QString m_path_exe;//路径
    IniFile m_ini;
    struct cal_data m_cal_data;
    //图片保存
    bool m_SaveRaw=false;
    bool m_SaveResult=false;
    bool m_SaveData=false;
    int image_save(Hobject& Image, bool bIsSaveRaw,bool bIsSaveResult);
    //报错管理
    aqlog m_log;
    //通讯模块
    bool connection_status=false;
    QThread m_thread_heartbeat;
    MyThreads  m_heartbeat;
    modbus_tcp_server m_modbus;
    //Hal param
    Hobject m_image;
    Hobject m_region;
    Hlong m_win_id;
    Hlong image_width,image_height;
    HTuple worldX, worldY;
    HTuple HomMat2D;
    //模板ID：不存在的模板设置为-1
    map<int, map<int, Hlong>> m_ModelID;
    int m_model_type;
    int m_model_index;

    //文件打开处理
    int file_image_to_process();
    int folder_image_to_process();
    //Hal 视觉部分初始化；视觉参数初始化
    int start_varia_init();
    int start_ui_init();
    int hal_read_shape_model();
    int cal_data_ini_read();
    //图像处理
    int image_process(Hobject& Image, Hlong model_id, double score, double& pix_x, double& pix_y);
    int cal_offset(double x,double y,
         double &world_offset_x, double &world_offset_y);    
    //处理后显示
    int image_show(Hobject& Image,HTuple& findRow,HTuple& findCol,bool bState);

private:
    Ui::MainWindow *ui;

signals:
    void signal_setupDeviceData(float x_coor,float y_coor,\
                                float complete,float heartbeat,float reserve); //与modbus类交互
    void signal_heartbeat_sender_control(modbus_tcp_server*);//控制线程发出心跳信号，由modbus类接收并setdata

public slots:
    //接收modbus tcp传送的数据
    void slot_read_data(float screwdriver,float screw,\
                        float enable,float receive,float reserve);
    void slot_connect_button_status(bool connected);

private slots:
    void on_pushButton_Connect_clicked();

    void pushButton_Snap();

    void on_menuParam();

    void on_menuShapeModel();

    void on_pushButton_TestItem_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_SaveRaw_clicked();

    void on_pushButton_SaveResult_clicked();
    void on_pushButton_SaveCoordinate_clicked();
    void on_pushButton_ChangeLink_clicked();
};

/*
问题：
1.中文路径问题
    #include <QTextCodec>
    2 QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    3 QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
*/

#endif // MAINWINDOW_H

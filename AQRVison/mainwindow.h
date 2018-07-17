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
#include <map>

#include "cpp/HalconCpp.h"
#include "halfunc.h"
#include "dialog.h"
#include "dialogshapemodel.h"
#include "cam.h"
#include "aqdata.h"
#include "aqlog.h"
#include "inifile.h"
#include "tcpip.h"

//#define MAX_MODEL_NUM 50

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

private:
    Ui::MainWindow *ui;


public slots:

    void pushButton_Snap();

    void on_menuParam();

    void on_menuShapeModel();

    void on_pushButton_TestItem_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    //tcpip函数
    int m_tcpip_slot(QString mes);

public:

    //Hal 视觉部分初始化；视觉参数初始化
    int start_varia_init();
    int start_ui_init();
    int hal_read_shape_model();

    //核心图像处理
    int image_process(Hobject& Image,Hlong model_id,double& pix_x,double& pix_y);
    int cal_offset(double x,double y,
         double &world_offset_x, double &world_offset_y);
    int cal_data_ini_read();

    int image_show(Hobject& Image,HTuple& findRow,HTuple& findCol,bool bState);

    //文件打开处理
    int file_image_to_process();
    int folder_image_to_process();

    //data模块
    AQData m_data_file_csv;

    //采集模块
    basler_cam m_snap_cam;

    //参数管理
    Dialog m_param_dialog;
    DialogShapeModel m_shape_model_dialog;

    //ini
    IniFile m_ini;
    struct cal_data m_cal_data;

    //图片保存机制
    int image_save(Hobject& Image, bool bIsSaveRaw,bool bIsSaveResult);
    //交互设计

    //报错管理
    aqlog m_log;

    //运行数据保存机制

    //系统记录:检测运行过程核心函数的状态和易错处关键数据记录

    //通讯模块
    TcpIp_client m_tcpip_client;
    int tcp_init();
    static int protocol_analysis(QString mes, QString& data);

    //Test Uint测试
    //图片保存测试
    int test_unit_image_save();
    int test_unit_tcp_socket();
    int test_unit_data();
    int test_unit_cam();
    int test_unit_image_process();
    int test_unit_log();
    int test_unit_calibration();
    int test_unit_model_list();
    int test_unit_ini();

    //Hal obj
    Hlong m_win_id;
    Hobject m_image;
    Hobject m_region;
    Hlong image_width,image_height;
    //HTuple findRow,findCol,findAngle, findScore;
    HTuple worldX, worldY;
    HTuple HomMat2D;
    //Hal param

    //模板ID：不存在的模板设置为-1
    //Hlong m_ModelID[MAX_MODEL_NUM];
    map<int, Hlong> m_ModelID;
    int m_model_index[30];

    QString m_path_exe;

    int m_cam_width,m_cam_height;

};

/*
问题：
1.中文路径问题
    #include <QTextCodec>
    2 QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    3 QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
2.OK -- 需添加10版本的库，并将disp_message

3.相对路径用不了 — — ！

4.创建模板模块框里面 draw上去的东西，需要再点一下才能显示

5.list_image_file 的东西需要全部运行完再显示

6.hom_mat_  保存

7.dialogshapemode模块删除文件后，mainwindow模块应更新模板列表及相应的m_Model1ID，未解决

8.dialogshapemode模块测试按钮需求尚未明确，未解决

*/

#endif // MAINWINDOW_H

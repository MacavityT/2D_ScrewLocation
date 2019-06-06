#include "mainwindow.h"
#include "ui_mainwindow.h"

//测试所使用头文件
#include <QLabel>
#include <QTime>
#include <math.h>
#include <bitset>
#include <iostream>

using namespace Halcon;

int save_index=0;

bool MainWindow::Runtime=false;
////界面构造及初始化
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //注册类型
    qRegisterMetaType<modbus_tcp_server>("modbus_tcp_server");
    qRegisterMetaType<Hobject>("Hobject");
    //初始化各界面
    ui->setupUi(this);
    //初始化参数变量配置   
    start_varia_init();
    //初始化界面设置
    start_ui_init();
    //Pushbutton connection
    connect(ui->actionParam, SIGNAL(triggered()), this, SLOT(on_menuParam()));
    connect(ui->actionShapeModel, SIGNAL(triggered()), this, SLOT(on_menuShapeModel()));
    //连接主流程与通信类
    connect(&m_modbus,SIGNAL(signal_connect_button_status(bool)),this,SLOT(slot_connect_button_status(bool)));
    connect(&m_modbus,SIGNAL(signal_read_data(float,float,float,float,float,float,float)),\
            this,SLOT(slot_read_data(float,float,float,float,float,float,float)));
    //连接调试界面与通信类
    connect(&m_modbus,SIGNAL(signal_read_data(float,float,float,float,float,float,float)),\
            &m_setting_dialog,SLOT(slot_read_data(float,float,float,float,float,float,float)));
    connect(&m_setting_dialog,SIGNAL(signal_setupDeviceData(float,float,float,float,float)),\
            &m_modbus,SLOT(setupDeviceData(float,float,float,float,float)));
    //心跳连接，由主线程启动，副线程中调用modbus类函数
    connect(this,SIGNAL(signal_heartbeat_sender_control(modbus_tcp_server*)),\
            &m_heartbeat,SLOT(slot_heartbeat_sender_control(modbus_tcp_server*)));
    //建立心跳连接
    m_heartbeat.moveToThread(&m_thread_heartbeat);
    m_thread_heartbeat.start();
    //开机启动
    ui->pushButton_Connect->click();
    ui->pushButton_Start->click();
}

MainWindow::~MainWindow()
{
    delete m_mark_csv;
    delete m_screw_csv;
    //回收心跳连接线程
    m_thread_heartbeat.terminate();
    m_thread_heartbeat.wait(0);
    m_thread_heartbeat.deleteLater();
    //关闭相机
    m_snap_cam.exit();
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information( this, tr("CT Control View"),
             tr("Do you really want to quit?"),
             tr("Yes"), tr("No"),
             0, 1 ) )
    {
       case 0:
        //因为析构顺序是从类开始，再执行成员变量的析构，如果在关闭之前不停止信号发送，会导致没有对象可以接受信号从而报错
        m_modbus.main_thread_quit=true;//控制通信类回调销毁
        //控制线程退出
        if(m_heartbeat.m_heartbeat)
        {
            m_heartbeat.m_heartbeat=false;
            Sleep(1000);
        }
        //断开连接
        if(connection_status)
            ui->pushButton_Connect->click();
        //程序退出
           QApplication::quit();
           break;
       case 1:
       default:
           event->ignore();
           break;
    }
}

//参数初始化
int MainWindow::start_varia_init()
{
    m_mark_csv=new AQData(QString("Mark"), QString("Date-Moment,mark,xcoor,ycoor,pix-x,pix-y,offsetx,offsety,status\n"));
    m_screw_csv=new AQData(QString("Screw"), QString("Date-Moment,threshold,modelIndex,screwdriver,screw,xcoor,ycoor,pix-x,pix-y,offsetx,offsety,exact_offset_x,exact_offset_y,x_diff,y_diff,xcoor_revert,ycoor_revert,x_work_diff,y_work_diff,status\n"));
    //exe文件所在路径
    m_path_exe = QCoreApplication::applicationDirPath();
    //cam 3840*2748,Camera size,如果参数写错可能导致图像显示错误
    m_cam_width = 2592;
    m_cam_height = 1944;
    //相机初始化状态判断
    if(0 != m_snap_cam.init())
    {
        ui->statusBar->showMessage(QString("Camera initialization failed,please exit the system!"));
//        this->setEnabled(false);
        return -1;
    }

    return 0;
}

//程序运行界面初始化，图像开窗，设置图标
int MainWindow::start_ui_init()
{
    //设置界面图标
    setWindowIcon(QIcon(":home.png"));
    //设置图标样式
    ui->pushButton_Start->setIcon(QIcon(":begin.png"));
    ui->pushButton_Stop->setIcon(QIcon(":stop.png"));
    ui->pushButton_Start->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_Stop->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(67,67,67);border-radius:10px;");
    ui->pushButton_TestItem->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_Connect->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_SaveRaw->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_SaveResult->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_SaveCoordinate->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_ChangeLink->setStyleSheet("background-color:rgb(235,235,235);\
                                               color: rgb(0,0,0);border-radius:10px;");
    //Widget WinId传递
    HWND hWnd = (HWND)ui->widget->winId();
    int widgetHeight = ui->widget->height();
    int widgetWidth  = ui->widget->width();
    Hlong m_DlgID = (Hlong)hWnd;
    open_window(0,0,widgetWidth,widgetHeight,m_DlgID,"visible", "",&m_win_id);

    return 0;
}

//将已存在的模板导出到map中，保存过程中将模板名的数字作为Map item，则要求模板命名对应编号
int MainWindow::hal_read_shape_model()
{
    //读取文件夹
    QDir dir(m_path_exe + "/match/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    //判断文件夹是否存在，不存在则创建
    if (false == dir.exists())
    {
        bool is_mkdir = dir.mkdir(m_path_exe + "/match/");
        if (false == is_mkdir)
        {
            m_log.write_log("MainWindow::hal_read_shape_model():the match folder mkdir fail!",true);
            return -1;
        }
    }
    //读取模板并保存至Map，保存过程中将“match-”字符替换为空字符，并将剩余数字作为Map index
    for (int i = 0; i < list.size(); ++i)
    {
        //正则表达式检测文件
        QFileInfo fileInfo = list.at(i);
        QString pattern("^match-\\d+\\_+\\d+\\.shm$");
        QRegExp rx(pattern);
        bool res = rx.exactMatch(fileInfo.fileName());
        if (res)
        {
            //拆解模板名，得到map映射关系
            QString template_name = fileInfo.fileName().replace("match-", "").replace(".shm", "");
            QByteArray trans=template_name.toLatin1();
            char* split_name=trans.data();
            bool screw_num_start=false;
            QString screw_driver_index="";
            QString screw_index="";
            for(split_name;*split_name!='\0';split_name++)
            {
                if(screw_num_start)
                {
                    //螺丝编号
                    screw_index+=*split_name;
                }
                if(*split_name!='_'&&!screw_num_start)
                {
                    //批头型号
                    screw_driver_index+=*split_name;
                }
                else
                {
                    screw_num_start=true;
                }
            }
            //读取模板
            Hlong modelID;
            try
            {
                read_shape_model(qPrintable(fileInfo.filePath()), &modelID);
            }
            catch (HException &except)
            {
                cerr<<except.err;
                m_log.write_log("MainWindow::hal_read_shape_model(): read_shape_model error!",true);
                return -2;
            }
            //第几张map中的第几个位置，对应批头号和螺丝号
            m_ModelID[screw_driver_index.toInt()][screw_index.toInt()] = modelID;
        }
        else
        {
            continue;
        }
    } 
    return 0;
}

int MainWindow::hal_read_mark_shape_model()
{
    //读取文件夹
    QDir dir(m_path_exe + "/match/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    //判断文件夹是否存在，不存在则创建
    if (false == dir.exists())
    {
        bool is_mkdir = dir.mkdir(m_path_exe + "/match/");
        if (false == is_mkdir)
        {
            m_log.write_log("MainWindow::hal_read_mark_shape_model():the match folder mkdir fail!",true);
            return -1;
        }
    }
    //读取模板并保存至Map，保存过程中将“mark-”字符替换为空字符，并将剩余数字作为Map index
    for (int i = 0; i < list.size(); ++i)
    {
        //正则表达式检测文件
        QFileInfo fileInfo = list.at(i);
        QString pattern("^mark-\\d+\\.shm$");
        QRegExp rx(pattern);
        bool res = rx.exactMatch(fileInfo.fileName());
        if (res)
        {
            //拆解模板名，得到map映射关系
            QString template_name = fileInfo.fileName().replace("mark-", "").replace(".shm", "");
            //读取模板
            Hlong modelID;
            try
            {
                read_shape_model(qPrintable(fileInfo.filePath()), &modelID);
            }
            catch (HException &except)
            {
                cerr<<except.err;
                m_log.write_log("MainWindow::hal_read_mark_shape_model(): read_shape_model error!",true);
                return -2;
            }
            //模板对应
            m_mark_ModelID[template_name.toInt()] = modelID;
        }
        else
        {
            continue;
        }
    }
    return 0;
}

//图像显示
int MainWindow::image_show(Hobject& Image,HTuple& findRow,HTuple& findCol,HTuple& offsetRow,HTuple& offsetCol,bool bState)
{
    try
    {
        Hobject showImage;
        HTuple Radius;
        clear_window(m_win_id);
        //图像显示
        get_image_size(Image,&image_width,&image_height);
        set_part(m_win_id,0,0,image_height,image_width);
        reduce_domain(Image,m_dynamic_region,&showImage);
        disp_obj(showImage,m_win_id);
        if(bState == true)
        {
            set_draw(m_win_id,"margin");
            set_color(m_win_id,"green");
            set_line_width(m_win_id,3);

            if(findRow.Num() > 0)
            {
                disp_cross (m_win_id, findRow, findCol, 40, 0.78);
                for (int i=0;i<findRow.Num();i++)
                {
                    Radius=Radius.Append(170);
                }
                disp_circle (m_win_id,findRow, findCol, Radius);
            }

            set_display_font (m_win_id, 20, "mono", "true", "false");

            disp_message (m_win_id, "X = " + findCol + "  Offset_X=" + offsetCol,\
                          "window", 0, 40, "green","true");
            if(findCol.Num()>1)
            {
                disp_message (m_win_id, "Y = " + findRow + "  Offset_Y=" + offsetRow,\
                              "window", 120, 40, "green","true");
            }
            else
            {
                disp_message (m_win_id, "Y = " + findRow + "  Offset_Y=" + offsetRow,\
                              "window", 50, 40, "green","true");
            }
        }
        else
        {
            set_draw(m_win_id,"margin");
            set_color(m_win_id,"red");
            set_display_font (m_win_id, 20, "mono", "true", "false");

            QString strQ("没发现匹配或位置错误");
            QByteArray ba = strQ.toLocal8Bit();
            char* ch = ba.data();
            HTuple ss = ch;

            disp_message (m_win_id, ss, "image", 40, 40,
                         "red","false");
        }
    }
    catch(HException &except)
    {
        QString message = QString(except.message)+QString::number(findRow.Num())+QString(",")+QString::number(findCol.Num());
        DialogShapeModel::print_qmess(message);
    }
    return 0;
}

////界面控制
//按钮：打开dialog界面
void MainWindow::on_menuParam()
{
    m_param_dialog.cam_init(&m_snap_cam);
    m_param_dialog.show();
    return ;
}

//按钮：打开dialogshapemodel界面
void MainWindow::on_menuShapeModel()
{
    m_shape_model_dialog.cam_init(&m_snap_cam);
    m_shape_model_dialog.show();
    return ;
}

//按钮：采集
void MainWindow::pushButton_Snap()
{
    //开始采集
    m_snap_cam.snap(0);
    //Show
    gen_image1(&m_image,"byte",m_cam_width,m_cam_height,(Hlong)m_snap_cam.pImageBuffer[0]);
    set_part(m_win_id,0,0,m_cam_height,m_cam_width);
    disp_obj(m_image,m_win_id);
    return ;
}

//按钮：停止
void MainWindow::on_pushButton_Stop_clicked()
{
    //标志位关闭
    Runtime=false;
    //disable停止按钮
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Start->setEnabled(true);

    //更改样式
    ui->pushButton_Start->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_Stop->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(67,67,67);border-radius:10px;");
    return ;
}

//按钮：开始
void MainWindow::on_pushButton_Start_clicked()
{
    if(!connection_status)
    {
        DialogShapeModel::print_qmess(QString("Please connect to server!"));
        if(!DebugEnable) return;
    }
    m_modbus.setupDeviceData(NULL,NULL,0,NULL,NULL);//开始时先将拍照完成标志置0
    //加载模板
    hal_read_shape_model();
    hal_read_mark_shape_model();
    //加载检测区域
    QString qdstr = m_path_exe + QString("/region/DetectionRegion.hobj");
    QFile qfile1(qdstr);
    if(false == qfile1.exists())
    {
        DialogShapeModel::print_qmess(QString("cann't find detection region file!"));
        return;
    }
    QByteArray ba1 = qdstr.toLocal8Bit();
    char* ch1 = ba1.data();
    read_region(&m_region,ch1);
    //加载螺丝动态检测区域
    HTuple Row,Column;
    QString qdstr_screw = m_path_exe + QString("/region/ScrewRegion.hobj");
    QFile qfile1_screw(qdstr_screw);
    if(false == qfile1_screw.exists())
    {
        DialogShapeModel::print_qmess(QString("cann't find screw region file!"));
        return;
    }
    QByteArray ba1_screw = qdstr_screw.toLocal8Bit();
    char* ch1_screw = ba1_screw.data();
    read_region(&m_dynamic_region,ch1_screw);
    smallest_circle(m_dynamic_region,&Row,&Column,&m_dynamic_region_radius);
    //读取仿射变换矩阵（判断是否存在）
    QString mat_file = m_path_exe + "/cal/TransHomMat2D.tup";
    QFile qfile(mat_file);
    if(false == qfile.exists())
    {
        DialogShapeModel::print_qmess(QString("cann't find affine trans tuple file!"));
        if(!DebugEnable) return;
    }
    char *ch;
    QByteArray ba = mat_file.toLatin1();
    ch = ba.data();
    try
    {
        read_tuple(ch, &HomMat2D);
    }
    catch(...)
    {
        m_log.write_log("MainWindow::on_pushButton_Start_clicked():Read affine trans tuple failed!",true);
        return;
    }
    //读取反仿射矩阵
    QString mat_file_revert = m_path_exe + "/cal/TransRevertHomMat2D.tup";
    QFile qfile_revert(mat_file_revert);
    if(false == qfile_revert.exists())
    {
        DialogShapeModel::print_qmess(QString("cann't find affine trans revert tuple file!"));
        if(!DebugEnable) return;
    }
    char *ch_revert;
    QByteArray ba_revert = mat_file_revert.toLatin1();
    ch_revert = ba_revert.data();
    try
    {
        read_tuple(ch_revert, &RevertHomMat2D);
    }
    catch(...)
    {
        m_log.write_log("MainWindow::on_pushButton_Start_clicked():Read revert affine trans tuple failed!",true);
        return;
    }
    //读取标准点位(拍照位)
    m_ini.read("StandardPosition","ScrewOn_x",m_cal_data.LuoW.x);
    m_ini.read("StandardPosition","ScrewOn_y",m_cal_data.LuoW.y);
    m_ini.read("StandardPosition","WorldCoordinate_x",m_cal_data.StdW.x);
    m_ini.read("StandardPosition","WorldCoordinate_y",m_cal_data.StdW.y);
    m_ini.read("StandardPosition","PixelCoordinate_x",m_cal_data.StdP.x);
    m_ini.read("StandardPosition","PixelCoordinate_y",m_cal_data.StdP.y);
    m_ini.read("StandardPosition","OffsetX",m_cal_data.Offset.x);
    m_ini.read("StandardPosition","OffsetY",m_cal_data.Offset.y);
    //界面显示--用户
    ui->pushButton_Stop->setEnabled(true);
    ui->pushButton_Start->setEnabled(false);
    //更改样式
    ui->pushButton_Start->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(67,67,67);border-radius:10px;");
    ui->pushButton_Stop->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    //运行标志位使能
    Runtime=true;
    return ;
}

//按钮：测试
void MainWindow::on_pushButton_TestItem_clicked()
{
    if(DebugEnable)
    {
        DebugRegionRow=906.039;
        DebugRegionColumn=1432.56;
        QString fileName="C:\\Users\\TTY\\Desktop\\1.bmp";
        QByteArray ba = fileName.toLocal8Bit();
        char* ch = ba.data();
        //读取并显示
        read_image(&m_image, ch);
    //    mark_process(4,1,1);
        screw_process(1,7,1,2);
    }
}

//按钮：连接或断开PLC
void MainWindow::on_pushButton_Connect_clicked()
{
    m_modbus.connection(!connection_status);
}

//按钮：保存原图使能
void MainWindow::on_pushButton_SaveRaw_clicked()
{
    m_SaveRaw=!m_SaveRaw;
    if(m_SaveRaw)
    {
        ui->pushButton_SaveRaw->setText("取消");
    }
    else
    {
        ui->pushButton_SaveRaw->setText("保存原图");
    }
}

//按钮：保存结果图使能
void MainWindow::on_pushButton_SaveResult_clicked()
{
    m_SaveResult=!m_SaveResult;
    if(m_SaveResult)
    {
        ui->pushButton_SaveResult->setText("取消");
    }
    else
    {
        ui->pushButton_SaveResult->setText("保存结果");
    }
}

//按钮：识别位置使能
void MainWindow::on_pushButton_SaveCoordinate_clicked()
{
    m_SaveData=!m_SaveData;
    if(m_SaveData)
    {
        ui->pushButton_SaveCoordinate->setText("取消");
    }
    else
    {
        ui->pushButton_SaveCoordinate->setText("保存坐标");
    }
}

//按钮：弹出更改连接地址对话框
void MainWindow::on_pushButton_ChangeLink_clicked()
{
    if(m_setting_dialog.exec())
    {
        //IP地址更改
        m_modbus.port=m_setting_dialog.port;
        m_modbus.server_address=m_setting_dialog.server;
        m_ini.write("TCP_Param","port",m_setting_dialog.port);
        m_ini.write("TCP_Param","server_address",m_setting_dialog.server);
        //心跳控制更改
        bool current_status=m_heartbeat.m_heartbeat;
        m_heartbeat.m_heartbeat=m_setting_dialog.m_heartbeat;
        if(!current_status&&m_heartbeat.m_heartbeat)
            emit signal_heartbeat_sender_control(&m_modbus);
    }
}


//////控制流程
//Modbus TCP
//连接按钮状态显示
void MainWindow::slot_connect_button_status(bool connected)
{
    connection_status=connected;
    if(connected)
    {
        ui->pushButton_Connect->setText(tr("断开"));
        ui->textBrowser->append("连接成功");
        //心跳连接
        emit signal_heartbeat_sender_control(&m_modbus);
    }
    else
    {
        ui->pushButton_Connect->setText(tr("连接"));
        ui->textBrowser->append("连接断开");
    }
}

//接收数据,由modbus类中的回调函数收到数据后发送到此处
void MainWindow::slot_read_data(float screwdriver, float screw, float enable, float receive, float mark, float xcoor, float ycoor)
{
    try
    {
        if(!Runtime)
            return;//程序未运行，接收数据不处理
        if(0.0==enable)
            return;//拍照禁止

        m_log.write_log("Start Run",m_SaveData);
        m_log.write_log("Screwdriver-"+QString::number(screwdriver)+" Screw-"+QString::number(screw)+" Mark-"+QString::number(mark)
                        +" XCoor-"+QString::number(xcoor)+" YCoor-"+QString::number(ycoor),m_SaveData);

        copy_obj(m_region,&m_dynamic_region,1,1);

        if(mark!=0.0)
        {
            int markInt=mark;
            mark_process(markInt,xcoor,ycoor);
        }
        else
        {
            int screwDriverInt=screwdriver;
            int screwInt=screw;
            screw_process(screwDriverInt,screwInt,xcoor,ycoor);
        }
        m_log.write_log("Stop Run",m_SaveData);
    }
    catch(HException &except)
    {
        QString message = QString(except.message);
        DialogShapeModel::print_qmess(message);
    }
}

//Mark点流程
void MainWindow::mark_process(int mark ,float xcoor ,float ycoor)
{
    //准备错误信息
    QString error_message;
    int mark_index=mark;
    error_message="Mark"+error_message.setNum(mark)+": ";
    //判断模板是否存在
    if(m_mark_ModelID.find(mark_index)==m_mark_ModelID.end())
    {
        ui->textBrowser->append(error_message+"The template is unexisted!\n");
        m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
        return;
    }
    //开始处理
    if(0!=m_snap_cam.snap(0))
    {
        ui->textBrowser->append(error_message+"采集图像失败！\n");
        m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
        return;
    }
    gen_image1(&m_image,"byte",m_snap_cam.m_cam_width,m_snap_cam.m_cam_height,(Hlong)m_snap_cam.pImageBuffer[0]);
    //image process
    double pix_x = 0.0;
    double pix_y = 0.0;
    double offset_x = 0.0;
    double offset_y = 0.0;

    //Get find model score
    double score=0;
    QString mark_num;
    m_ini.read("Model_Score",mark_num.setNum(mark),score);
    if(score==0)
        score=0.5;

    int err = 0;
    vector<int> model_name={1,2,3,4};
    auto use_iterator=model_name.begin();
    int use_index;
    Hobject tem_image;
    bool status=false;
    for(int modelIndex=0;modelIndex<4;modelIndex++)
    {
        if(model_name.empty()) break;

        if(modelIndex==0)
        {
            use_iterator+=mark-1;
        }
        else
        {
            use_iterator=model_name.begin();
        }
        use_index=*use_iterator;
        model_name.erase(use_iterator);


        if(m_mark_ModelID.find(use_index)==m_mark_ModelID.end())
        {
            break;
        }

        median_image(m_image,&tem_image,"circle",6,"mirrored");
        scale_image(tem_image,&tem_image,3,-100);
        err = image_process_mark(tem_image, m_mark_ModelID[use_index],score,pix_x,pix_y);
        if(0==err)
        {
            status=true;
        }

        if(status) break;
    }

    if(!status)
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        HTuple offsetX=0.0;
        HTuple offsetY=0.0;
        image_show(m_image,py,px,offsetY,offsetX,false);
        ui->textBrowser->append(error_message+"定位Mark点失败!\n");
        m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
        //图像-原图保存-处理后截图保存
        image_save(m_image,error_message,true,true);
        //写入时间及坐标
        m_mark_csv->data_write(mark,xcoor,ycoor,0,0,0,0,"Can't find mark",true);
        return;
    }

    err = cal_offset_mark(pix_x,pix_y,offset_x,offset_y);//返回的offset值为当前识别物理位置与记录的标准上螺丝物理位置的偏移量
    if(0 != err)
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        HTuple offsetX=0.0;
        HTuple offsetY=0.0;
        image_show(m_image,py,px,offsetY,offsetX,false);
        ui->textBrowser->append(error_message+"cal_offset_mark失败!!\n");
        m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
        //图像-原图保存-处理后截图保存
        image_save(m_image,error_message,true,true);
        //写入时间及坐标
        m_mark_csv->data_write(mark,xcoor,ycoor,0,0,0,0,"HomMat calculate failed",true);
        return;
    }

    //记录mark点并计算运行仿射变换矩阵
    mark_x_1[mark-1]=xcoor;
    mark_y_1[mark-1]=ycoor;
    mark_x_2[mark-1]=xcoor+offset_x;
    mark_y_2[mark-1]=ycoor+offset_y;
    if(mark==4)
    {
        try
        {
            vector_to_hom_mat2d(mark_x_1,mark_y_1,mark_x_2,mark_y_2,&HomMat2DRunTime);
            vector_to_hom_mat2d(mark_x_2,mark_y_2,mark_x_1,mark_y_1,&RevertHomMat2DRunTime);

            if(m_SaveResult)
            {
                QString qdstr = m_path_exe + "/cal/RunTimeTransHomMat2D.tup";
                QByteArray ba = qdstr.toLatin1();
                char* ch=ba.data();
                write_tuple (HomMat2DRunTime, ch);
            }
        }
        catch(...)
        {
            ui->textBrowser->append(QString("Calculate failed!"));
            m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
            m_mark_csv->data_write(mark,xcoor,ycoor,0,0,0,0,"Generate mark HomMat2D failed",true);
            return;
        }
    }

    //计算结果保存至param.ini
    if(m_SaveResult)
    {
        m_ini.write("Runtime",error_message+QString("px"),pix_x);
        m_ini.write("Runtime",error_message+QString("py"),pix_y);
        m_ini.write("Runtime",error_message+QString("xcoor"),xcoor);
        m_ini.write("Runtime",error_message+QString("ycoor"),ycoor);
        m_ini.write("Runtime",error_message+QString("offsetX"),offset_x);
        m_ini.write("Runtime",error_message+QString("offsetY"),offset_y);
    }

    //发送完成信号
    m_modbus.setupDeviceData(NULL,NULL,1.0,NULL,NULL);
    //显示当前图片
    HTuple px = HTuple(pix_x);
    HTuple py = HTuple(pix_y);
    HTuple offsetX=HTuple(offset_x);
    HTuple offsetY=HTuple(offset_y);
    image_show(m_image,py,px,offsetY,offsetX,true);
    //图像-原图保存-处理后截图保存
    image_save(m_image,error_message,m_SaveRaw,m_SaveResult);
    //保存结果
    m_mark_csv->data_write(mark,xcoor,ycoor,pix_x,pix_y,offset_x,offset_y,"OK",m_SaveData);
}

void MainWindow::screw_process(int screwdriver, int screw, float xcoor, float ycoor)
{
    Hlong length;
    tuple_length(HomMat2DRunTime,&length);
    if(length<=0)
    {
        ui->textBrowser->append("仿射变换矩阵(Runtime)不存在！");
        if(!DebugEnable) return;
    }

    x_coor=0;
    y_coor=0;
    //准备错误信息
    QString error_message;
    QString wrong_screwdriver;
    QString wrong_screw;
    error_message="Screw"+wrong_screwdriver.setNum(screwdriver)+'-'+wrong_screw.setNum(screw)+": ";
    //判断模板是否存在
    int screwdriver_index=screwdriver;
    int screw_index=screw;

    if ( m_ModelID.find(screwdriver_index)==m_ModelID.end() ||\
         (m_ModelID[screwdriver_index]).find(screw_index)==(m_ModelID[screwdriver_index]).end())
    {
        ui->textBrowser->append(error_message+"The template is unexisted!\n");
        m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
        return;
    }

    //图像坐标及偏移量初始化
    double pix_x[3]={0.0,0.0,0.0};
    double pix_y[3]={0.0,0.0,0.0};
    double offset_x[3]={0.0,0.0,0.0};
    double offset_y[3]={0.0,0.0,0.0};

    //模板分数初始化
    double score=0;
    QString driver_trans,screw_trans;
    driver_trans.setNum(screwdriver_index);
    screw_trans.setNum(screw_index);
    QString key=driver_trans+'_'+screw_trans;
    m_ini.read("Model_Score",key,score);
    if(score==0) score=0.5;

    //偏移量差值初始化
    double x_diff[3]={0.0,0.0,0.0},y_diff[3]={0.0,0.0,0.0};
    double x_offsetMin=0,x_offsetMax=0,y_offsetMin=0,y_offsetMax=0;
    x_offsetMin=m_cal_data.Offset.x<-(m_cal_data.Offset.x)? m_cal_data.Offset.x:-(m_cal_data.Offset.x);
    x_offsetMax=m_cal_data.Offset.x>-(m_cal_data.Offset.x)? m_cal_data.Offset.x:-(m_cal_data.Offset.x);
    y_offsetMin=m_cal_data.Offset.y<-(m_cal_data.Offset.y)? m_cal_data.Offset.y:-(m_cal_data.Offset.y);
    y_offsetMax=m_cal_data.Offset.y>-(m_cal_data.Offset.y)? m_cal_data.Offset.y:-(m_cal_data.Offset.y);

    double x1,y1,x2,y2;
    double exact_offset_x,exact_offset_y;
    double regionX,regionY;
    if(!DebugEnable)
    {
        //使用动态仿射矩阵计算准确位置，并进行对比
        try
        {
            x1=xcoor;
            y1=ycoor;
            affine_trans_point_2d(HomMat2DRunTime,x1,y1,&x2,&y2);

            exact_offset_x=x2-x1;
            exact_offset_y=y2-y1;
        }
        catch(...)
        {
            ui->textBrowser->append(QString("Calculate coordinate failed!"));
        }

        //采集图像
        if(0!=m_snap_cam.snap(0))
        {
            ui->textBrowser->append(error_message+"采集图像失败！\n");
            m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
            return;
        }
        gen_image1(&m_image,"byte",m_snap_cam.m_cam_width,m_snap_cam.m_cam_height,(Hlong)m_snap_cam.pImageBuffer[0]);
    }

    //生成动态检测区域
    if(!DebugEnable)
    {
        //使用反标定仿射计算当前螺丝图像坐标
        cal_offset_revert(x1,y1,x2,y2,regionX,regionY);
        gen_circle(&m_dynamic_region,regionY,regionX,m_dynamic_region_radius);
    }
    else
    {
        gen_circle(&m_dynamic_region,DebugRegionRow,DebugRegionColumn,m_dynamic_region_radius);
    }

    //开始处理
    bool status=false;
    int image_err = 0;
    int calculate_err = 0;
    int modelIndexMax=3;
    int useModelIndex=0;
    int success_index=0;
    double wrong_position_x[18]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double wrong_position_y[18]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    int wrong_index=0;

    for(int modelIndex=0;modelIndex<modelIndexMax;modelIndex++)
    {
        if(screw_index<2)
        {
            useModelIndex = modelIndex+screw_index;
        }
        else
        {
            useModelIndex = modelIndex+screw_index-1;
        }
        if((m_ModelID[screwdriver_index]).find(useModelIndex)==(m_ModelID[screwdriver_index]).end())
        {
            useModelIndex-=3;
        }
        if((m_ModelID[screwdriver_index]).find(useModelIndex)==(m_ModelID[screwdriver_index]).end())
        {
            break;
        }

        //正式处理
        Hobject tem_image,Regions;
        Hobject Regions1,ConnectedRegions,SelectedRegions,RegionOpening,RegionClosing,SelectedRegions1,RegionUnion,RegionIntersection;
        for(int i=-1;i<1;i++)
        {
            if(i==-1)
            {
                copy_image(m_image,&tem_image);
                median_image(tem_image,&tem_image,"circle",6,"mirrored");
                scale_image(tem_image,&tem_image,3,-100);
                //分离线材区域，暂时这么写，等待重构
                auto_threshold(tem_image,&Regions1,2);
                connection(Regions1,&ConnectedRegions);
                select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 2000, 999999999999);
                opening_circle (SelectedRegions, &RegionOpening, 30);
                closing_circle(RegionOpening, &RegionClosing, 30);
                select_shape(RegionClosing, &SelectedRegions1, HTuple("circularity").Append("area"),"and",HTuple(0).Append(9999),\
                             HTuple(0.3).Append(999999999));
                union1(SelectedRegions1, &RegionUnion);
                intersection(m_dynamic_region,RegionUnion,&RegionIntersection);
                difference(m_dynamic_region,RegionIntersection,&m_dynamic_region);
            }
            else
            {
                //预处理--1次不同程度二值化
                median_image(m_image,&tem_image,"circle",6,"mirrored");
                scale_image(tem_image,&tem_image,3,-100);
                //分离线材区域，暂时这么写，等待重构
                auto_threshold(tem_image,&Regions1,2);
                connection(Regions1,&ConnectedRegions);
                select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 2000, 999999999999);
                opening_circle (SelectedRegions, &RegionOpening, 30);
                closing_circle(RegionOpening, &RegionClosing, 30);
                select_shape(RegionClosing, &SelectedRegions1, HTuple("circularity").Append("area"),"and",HTuple(0).Append(9999),\
                             HTuple(0.3).Append(999999999));
                union1(SelectedRegions1, &RegionUnion);
                intersection(m_dynamic_region,RegionUnion,&RegionIntersection);
                difference(m_dynamic_region,RegionIntersection,&m_dynamic_region);


                threshold(tem_image,&Regions,70+i*10,255);
                region_to_bin(Regions,&tem_image,255,0,2592,1944);
            }

            image_err = image_process_screw(tem_image, (m_ModelID[screwdriver_index])[useModelIndex],score,pix_x,pix_y);
            if(0 == image_err)
            {
                //返回的offset值为当前识别物理位置与记录的标准上螺丝物理位置的偏移量
                calculate_err = cal_offset_screw(pix_x,pix_y,offset_x,offset_y);
                if(0 == calculate_err)
                {
                    for(int i=0;i<3;i++)
                    {
                        x_diff[i]=exact_offset_x-offset_x[i];
                        y_diff[i]=exact_offset_y-offset_y[i];

                        wrong_position_x[wrong_index]=pix_x[i];
                        wrong_position_y[wrong_index]=pix_y[i];
                        wrong_index++;

                        //过程数据保存
                        for(int n=0;n<3;n++)
                        {
                            m_screw_csv->data_write(60+i*10,modelIndex,screwdriver,screw,xcoor,ycoor,pix_x[n],pix_y[n],
                                                   offset_x[n],offset_y[n],exact_offset_x,exact_offset_y,x_diff[n],y_diff[n],
                                                    0,0,0,0,"process data",m_SaveData);
                        }

                        if(x_diff[i]>x_offsetMin && x_diff[i]<x_offsetMax && y_diff[i]>y_offsetMin && y_diff[i]<y_offsetMax)
                        {
                            x_coor=offset_x[i];
                            y_coor=offset_y[i];
                            m_modbus.setupDeviceData(x_coor,y_coor,1.0,NULL,NULL);
                            success_index=i;
                            status=true;
                            //结果OK，跳出计算偏差值循环
                            break;
                        }
                    }
                    //结果OK，跳出预处理循环
                    if(status) break;
                }
                else
                {
                    //计算失败，数据保存
                    for(int n=0;n<3;n++)
                    {
                        m_screw_csv->data_write(60+i*10,modelIndex,screwdriver,screw,xcoor,ycoor,pix_x[n],pix_y[n],
                                               offset_x[n],offset_y[n],exact_offset_x,exact_offset_y,x_diff[n],y_diff[n],
                                               0,0,0,0,"Calculate failed",true);
                    }
                }
            }
            else
            {
                //找不到螺丝，数据保存
                for(int n=0;n<3;n++)
                {
                    m_screw_csv->data_write(60+i*10,modelIndex,screwdriver,screw,xcoor,ycoor,pix_x[n],pix_y[n],
                                           offset_x[n],offset_y[n],exact_offset_x,exact_offset_y,x_diff[n],y_diff[n],
                                           0,0,0,0,"Can't find screw.",true);
                }
            }
        }
        //结果OK，跳出模板遍历循环
        if(status) break;
    }

    //结果显示及保存
    if(!status)
    {
        HTuple px;
        HTuple py;
        HTuple offsetX=0.0;
        HTuple offsetY=0.0;

        for(int i=0;i<18;i++)
        {
            if(wrong_position_x[i]!=0.0)
            {
                px=px.Append(wrong_position_x[i]);
                py=py.Append(wrong_position_y[i]);
            }
        }

        image_show(m_image,py,px,offsetY,offsetX,true);
        //图像-原图保存-处理后截图保存
        image_save(m_image,error_message,true,true);
        ui->textBrowser->append(error_message+"没发现匹配或位置错误!!\n");
        m_modbus.setupDeviceData(-1.0,-1.0,1.0,NULL,NULL);
        //保存参数
        for(int n=0;n<3;n++)
        {
            m_screw_csv->data_write(-1,-1,screwdriver,screw,xcoor,ycoor,pix_x[n],pix_y[n],
                                   offset_x[n],offset_y[n],exact_offset_x,exact_offset_y,x_diff[n],y_diff[n],
                                    0,0,0,0,"Can't find screw or wrong position",true);
        }
    }
    else
    {
        //显示当前图片
        HTuple px = HTuple(pix_x[success_index]);
        HTuple py = HTuple(pix_y[success_index]);
        HTuple offsetX=HTuple(offset_x[success_index]);
        HTuple offsetY=HTuple(offset_y[success_index]);
        image_show(m_image,py,px,offsetY,offsetX,true);
        //图像-原图保存-处理后截图保存
        image_save(m_image,error_message,m_SaveRaw,m_SaveResult);
        //反算当前拍照点的正确位置
        double xcoor_revert,ycoor_revert;
        double x_work_diff,y_work_diff;
        double x_work=xcoor+offset_x[success_index];
        double y_work=ycoor+offset_y[success_index];
        affine_trans_point_2d(RevertHomMat2DRunTime,x_work,y_work,&xcoor_revert,&ycoor_revert);
        x_work_diff=xcoor_revert-xcoor;
        y_work_diff=ycoor_revert-ycoor;
        //保存坐标
        m_screw_csv->data_write(-1,-1,screwdriver,screw,xcoor,ycoor,pix_x[success_index],pix_y[success_index],
                               offset_x[success_index],offset_y[success_index],exact_offset_x,exact_offset_y,x_diff[success_index],y_diff[success_index],
                               xcoor_revert,ycoor_revert,x_work_diff,y_work_diff,"OK",m_SaveData);
    }
}

//图像处理
int MainWindow::image_process_mark(Hobject& Image,Hlong model_id,double score,double& pix_x,double& pix_y)
{
    HTuple findRow,findCol,findAngle,findScale,findScore;
    double dradRange = HTuple(360).Rad()[0].D();
    reduce_domain(Image,m_region,&Image);
    find_scaled_shape_model(Image,  model_id, 0, dradRange , 0.8, 1.2, score, 1, 0.5,
                     "least_squares", 5, 0.3, &findRow, &findCol, &findAngle, &findScale, &findScore);

    //判断findRow有无
    if(1 != findRow.Num())
        return -1;

    pix_x = findCol[0].D();
    pix_y = findRow[0].D();

    return 0;
}

int MainWindow::image_process_screw(Hobject& Image,Hlong model_id,double score,double pix_x[],double pix_y[])
{
    HTuple findRow,findCol,findAngle,findScale,findScore;

    double dradRange = HTuple(360).Rad()[0].D();
    reduce_domain(Image,m_dynamic_region,&Image);
    find_scaled_shape_model(Image,  model_id, 0, dradRange , 0.9, 1.1, score, 3, 0.5,
                     "least_squares", 5, 0.3, &findRow, &findCol, &findAngle, &findScale, &findScore);

    //判断findRow有无
    if(1 > findRow.Num())
        return -1;

    //输出结果
    int num=findCol.Num();
    for(int i=0;i<num;i++)
    {
        pix_x[i]=findCol[i].D();
        pix_y[i]=findRow[i].D();
    }

    return 0;
}


//计算偏移量
int MainWindow::cal_offset_mark(double x,double y,double &world_offset_x, double &world_offset_y)
{
    double world_x,world_y;//仿射后的螺丝坐标
    double mid_x,mid_y;//标准螺丝图像位仿射后的坐标
    // read Mat and do affine trans
    try
    {
        affine_trans_point_2d(HomMat2D, x, y, \
                          &world_x, &world_y);
        affine_trans_point_2d(HomMat2D,m_cal_data.StdP.x,m_cal_data.StdP.y,\
                          &mid_x,&mid_y);
        world_offset_x = (world_x - mid_x) + (m_cal_data.LuoW.x - m_cal_data.StdW.x);
        world_offset_y = (world_y - mid_y) + (m_cal_data.LuoW.y - m_cal_data.StdW.y);
    }
    catch(exception &e)
    {
        cerr<<e.what();
        return -2;
    }

    return 0;
}

int MainWindow::cal_offset_screw(double x[],double y[],double world_offset_x[], double world_offset_y[])
{
    double world_x,world_y;//仿射后的螺丝坐标
    double mid_x,mid_y;//标准螺丝图像位仿射后的坐标
    // read Mat and do affine trans
    try
    {
        int num=3;
        for(int i=0;i<num;i++)
        {
            affine_trans_point_2d(HomMat2D, x[i], y[i], \
                              &world_x, &world_y);
            affine_trans_point_2d(HomMat2D,m_cal_data.StdP.x,m_cal_data.StdP.y,\
                              &mid_x,&mid_y);
            world_offset_x[i] = (world_x - mid_x) + (m_cal_data.LuoW.x - m_cal_data.StdW.x);
            world_offset_y[i] = (world_y - mid_y) + (m_cal_data.LuoW.y - m_cal_data.StdW.y);
        }
    }
    catch(exception &e)
    {
        cerr<<e.what();
        return -2;
    }
    catch(HException &except)
    {
        QString message = QString(except.message);
        DialogShapeModel::print_qmess(message);
        return -2;
    }

    return 0;
}

int MainWindow::cal_offset_revert(double xcoor ,double ycoor ,double screw_x,double screw_y,double& pix_x, double& pix_y)
{
//    double platform_x_old,platform_y_old;
//    double platform_x_new, platform_y_new;

//    try
//    {
//        double x,y;
//        affine_trans_point_2d(HomMat2D,m_cal_data.StdP.x,m_cal_data.StdP.y,&platform_x_old,&platform_y_old);
//        affine_trans_point_2d(RevertHomMat2D,platform_x_old,platform_y_old,&x,&y);
//        platform_x_new = (screw_x - xcoor) - (m_cal_data.LuoW.x - m_cal_data.StdW.x) + platform_x_old;
//        platform_y_new = (screw_y - ycoor) - (m_cal_data.LuoW.y - m_cal_data.StdW.y) + platform_y_old;
//        affine_trans_point_2d(RevertHomMat2D,platform_x_new,platform_y_new,&pix_x,&pix_y);
//    }
//    catch(exception &e)
//    {
//        cerr<<e.what();
//        return -2;
//    }
//    catch(HException &except)
//    {
//        QString message = QString(except.message);
//        DialogShapeModel::print_qmess(message);
//        return -2;
//    }


    double pix_x1,pix_y1;
    double pix_x2,pix_y2;
    double screw_x2,screw_y2;
    // read Mat and do affine trans
    try
    {
        affine_trans_point_2d(RevertHomMat2D,screw_x,screw_y,&pix_x1,&pix_y1);
        screw_x2 = xcoor + (m_cal_data.LuoW.x - m_cal_data.StdW.x);
        screw_y2 = ycoor + (m_cal_data.LuoW.y - m_cal_data.StdW.y);
        affine_trans_point_2d(RevertHomMat2D,screw_x2,screw_y2,&pix_x2,&pix_y2);
        pix_x=m_cal_data.StdP.x+(pix_x1-pix_x2);
        pix_y=m_cal_data.StdP.y+(pix_y1-pix_y2);
    }
    catch(exception &e)
    {
        cerr<<e.what();
        return -2;
    }
    catch(HException &except)
    {
        QString message = QString(except.message);
        DialogShapeModel::print_qmess(message);
        return -2;
    }

    return 0;
}


//图片保存（原图及处理后图片，处理后图片为屏幕截图）
int MainWindow::image_save(Hobject& Image, QString name, bool bIsSaveRaw, bool bIsSaveResult)
{
    name=name.replace(":","");
    //获取当前保存的日期&&时间精确到ms
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd");

    //创建文件夹 --- 存放的文件夹：当前exe路径的./ImageResult  ./ImageRaw
    //子文件夹按日期命名：2018-10-20
    QDir image_dir_raw(m_path_exe + "/ImageRaw/" + current_date + "/" + name);
    QDir image_dir_res(m_path_exe + "/ImageResult/" + current_date + "/" + name);

    //先检测文件夹是否完备：创建
    if (false == image_dir_raw.exists())
    {
        bool is_created = image_dir_raw.mkpath(m_path_exe + "/ImageRaw/" + current_date+ "/" + name);
        if (false == is_created)
        {
            m_log.write_log("MainWindow::image_save(): the folder ImageRaw created failed! " + name,true);
            return -1;
        }
    }

    if (false == image_dir_res.exists())
    {
        bool is_created = image_dir_res.mkpath(m_path_exe + "/ImageResult/" + current_date+ "/"  + name);
        if (false == is_created)
        {
            m_log.write_log("MainWindow::image_save(): the folder ImageResult created failed! " + name,true);
            return -2;
        }
    }

    //write image
    QString image_path = image_dir_raw.filePath("./") + current_date_time.toString("hh_mm_ss_zzz");
    QByteArray ba = image_path.toLatin1(); // must
    char* ch = ba.data();
    if( true == bIsSaveRaw )
    {
        // write failed
        try
        {
            write_image(Image, "bmp", 0, ch);
        }
        catch (HException &except)
        {
            cerr<<except.err;
            m_log.write_log("MainWindow::image_save(): write image1 failed! " + name + "  " +except.message,true);
            return -3;
        }
    }

    image_path = image_dir_res.filePath("./") + current_date_time.toString("hh_mm_ss_zzz");
    ba = image_path.toLocal8Bit();
    ch = ba.data();

    Hobject dump_image;
    dump_window_image (&dump_image, m_win_id);

    if(true == bIsSaveResult)
    {
       //wirte failed
       try
       {
           write_image(dump_image, "png", 0, ch);
       }
       catch (HException &except)
       {
           cerr<<except.err;
           m_log.write_log("MainWindow::image_save(): write image2 failed!" + name + "  " +except.message,true);
           return -4;
       }
    }

    return 0;
}

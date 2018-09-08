#include "mainwindow.h"
#include "ui_mainwindow.h"

//测试所使用头文件
#include <QLabel>
#include <QTime>
#include <math.h>

using namespace Halcon;

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
    connect(&m_modbus,SIGNAL(signal_read_data(float,float,float,float,float)),\
            this,SLOT(slot_read_data(float,float,float,float,float)));
    connect(&m_modbus,SIGNAL(signal_connect_button_status(bool)),this,SLOT(slot_connect_button_status(bool)));

    connect(this,SIGNAL(signal_setupDeviceData(float,float,float,float,float)),\
            &m_modbus,SLOT(setupDeviceData(float,float,float,float,float)));
    //心跳连接，由主线程启动，副中调用modbus类函数
    connect(this,SIGNAL(signal_heartbeat_sender_control(modbus_tcp_server*)),\
            &m_heartbeat,SLOT(slot_heartbeat_sender_control(modbus_tcp_server*)));
    //建立心跳连接
    m_heartbeat.moveToThread(&m_thread_heartbeat);
    m_thread_heartbeat.start();
}

MainWindow::~MainWindow()
{
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
        m_modbus.main_thread_quit=true;

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
    //exe文件所在路径
    m_path_exe = QCoreApplication::applicationDirPath();
    //cam 3840*2748,Camera size,如果参数写错可能导致图像显示错误
    m_cam_width = 2592;
    m_cam_height = 1944;
    //相机初始化状态判断
    if(0 != m_snap_cam.init())
    {
        ui->statusBar->showMessage(QString("Camer initialization failed,please exit the system!"));
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
            m_log.write_log("MainWindow::hal_read_shape_model():the match folder mkdir fail!");
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
                m_log.write_log("MainWindow::hal_read_shape_model(): read_shape_model error!");
                return -2;
            }
            //第几张map中的第几个位置，对应批头号和螺丝号
            (m_ModelID[screw_driver_index.toInt()])[screw_index.toInt()] = modelID;
        }
        else
        {
            continue;
        }
    }
    return 0;
}

//图像显示
int MainWindow::image_show(Hobject& Image,HTuple& findRow,HTuple& findCol,bool bState)
{
    //图像显示
    get_image_size(Image,&image_width,&image_height);
    set_part(m_win_id,0,0,image_height,image_width);
    disp_obj(m_image,m_win_id);
    if(bState == true)
    {
        set_draw(m_win_id,"margin");
        set_color(m_win_id,"green");
        set_line_width(m_win_id,3);
        disp_cross (m_win_id, findRow[0].D(), findCol[0].D(), 40, 0.78);
        disp_circle (m_win_id,findRow[0].D(), findCol[0].D(), 170);
        set_display_font (m_win_id, 100, "mono", "true", "false");

        disp_message (m_win_id, "X = " + findCol, "window", 40, 40,
                     "green","false");
        disp_message (m_win_id, "Y = " + findRow, "window", 90, 40,
                     "green","false");
    }
    else
    {
        set_draw(m_win_id,"margin");
        set_color(m_win_id,"red");
        set_display_font (m_win_id, 200, "mono", "true", "false");

        QString strQ("没发现匹配");
        QByteArray ba = strQ.toLocal8Bit();
        char* ch = ba.data();
        HTuple ss = ch;

        disp_message (m_win_id, ss, "image", 40, 40,
                     "red","false");
    }
    return 0;
}

////界面控制
//按钮：打开dialog界面
void MainWindow::on_menuParam()
{
    m_param_dialog.cam_init(&m_snap_cam);
    m_param_dialog.exec();
    return ;
}

//按钮：打开dialogshapemodel界面
void MainWindow::on_menuShapeModel()
{
    m_shape_model_dialog.cam_init(&m_snap_cam);
    m_shape_model_dialog.exec();
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
        return;
    }
    emit signal_setupDeviceData(NULL,NULL,0,NULL,NULL);//开始时先将拍照完成标志置0

    //加载模板
    hal_read_shape_model();
    //读取仿射变换矩阵（判断是否存在）
    QString mat_file = m_path_exe + "/cal/TransHomMat2D.tup";
    QFile qfile(mat_file);
    if(false == qfile.exists())
    {
        DialogShapeModel::print_qmess(QString("cann't find affine trans tuple file!"));
        return;
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
        m_log.write_log("MainWindow::on_pushButton_Start_clicked():Read affine trans tuple failed!");
        return;
    }
    //读取标准点位(拍照位)
    m_ini.read("StandardPosition","ScrewOn_x",m_cal_data.LuoW.x);
    m_ini.read("StandardPosition","ScrewOn_y",m_cal_data.LuoW.y);
    m_ini.read("StandardPosition","WorldCoordinate_x",m_cal_data.StdW.x);
    m_ini.read("StandardPosition","WorldCoordinate_y",m_cal_data.StdW.y);
    m_ini.read("StandardPosition","PixelCoordinate_x",m_cal_data.StdP.x);
    m_ini.read("StandardPosition","PixelCoordinate_y",m_cal_data.StdP.y);

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
    m_setting_dialog.show();
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
        m_modbus.port=m_setting_dialog.port;
        m_modbus.server_address=m_setting_dialog.server;
        m_ini.write("TCP_Param","port",m_setting_dialog.port);
        m_ini.write("TCP_Param","server_address",m_setting_dialog.server);
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
        emit signal_heartbeat_sender_control(&m_modbus);
    }
    else
    {
        ui->pushButton_Connect->setText(tr("连接"));
        ui->textBrowser->append("连接断开");
    }
}
//接收数据,由modbus类中的回调函数收到数据后发送到此处
void MainWindow::slot_read_data(float screwdriver, float screw, float enable, float receive, float reserve)
{
    if(!Runtime)
        return;//程序未运行，接收数据不处理
    if(0.0==enable)
        return;//拍照禁止
    if(1.0==receive)
    {
        emit signal_setupDeviceData(NULL,NULL,0,NULL,NULL);
        return;//接收完成拍照位置0
    }
    //判断模板是否存在
    int screwdriver_index=screwdriver;

    int screw_index=screw;
    //判断两张map是否都存在映射关系
    if ( m_ModelID.find(screwdriver_index)==m_ModelID.end() ||\
         (m_ModelID[screwdriver_index]).find(screw_index)==(m_ModelID[screwdriver_index]).end())
    {
        ui->textBrowser->append("the template is unexisted!\n");
        return;
    }
    //开始处理
    if(0!=m_snap_cam.snap(0))
    {
        ui->textBrowser->append("采集图像失败！\n");
        return;
    }
    gen_image1(&m_image,"byte",m_snap_cam.m_cam_width,m_snap_cam.m_cam_height,(Hlong)m_snap_cam.pImageBuffer[0]);
    //image process
    double pix_x = 0.0;
    double pix_y = 0.0;
    double offset_x = 0.0;
    double offset_y = 0.0;


    double score=0;
    QString driver_trans,screw_trans;
    driver_trans.setNum(screwdriver_index);
    screw_trans.setNum(screw_index);
    QString key=driver_trans+'_'+screw_trans;
    m_ini.read("Model_Score",key,score);
    if(score==0)
        score=0.5;

    int err = 0;
    err = image_process(m_image, (m_ModelID[screwdriver_index])[screw_index],score,pix_x,pix_y);
    if(0 != err)
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        image_show(m_image,py,px,false);
        ui->textBrowser->append("定位螺丝失败!\n");
        return;
    }

    err = cal_offset(pix_x,pix_y,offset_x,offset_y);//返回的offset值为当前识别物理位置与记录的标准物理位置的偏移量
    if(0 != err)
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        image_show(m_image,py,px,false);
        ui->textBrowser->append("cal_offset失败!!\n");
        return;
    }
    //结果发送
    float x_coor,y_coor;
    x_coor=offset_x;
    y_coor=offset_y;
    emit signal_setupDeviceData(x_coor,y_coor,1.0,NULL,NULL);

    //显示当前图片
    HTuple px = HTuple(pix_x);
    HTuple py = HTuple(pix_y);
    image_show(m_image,py,px,true);
    //图像-原图保存-处理后截图保存
    image_save(m_image,m_SaveRaw,m_SaveResult);
    //写入时间及坐标
    m_data_file_csv.data_write(pix_x,pix_y,m_SaveData);
}

//图像处理
int MainWindow::image_process(Hobject& Image,Hlong model_id,double score,double& pix_x,double& pix_y)
{
    HTuple findRow,findCol,findAngle,findScore;

    double dradRange = HTuple(360).Rad()[0].D();
    find_shape_model(Image,  model_id, 0, dradRange , score, 1, 0.5,
                     "least_squares", 3, 0.9, &findRow, &findCol, &findAngle, &findScore);

    //判断findRow有无
    if(1 != findRow.Num())
    {
        set_color(m_win_id,"red");
        set_display_font (m_win_id, 80, "mono", "true", "false");
        disp_message (m_win_id, "no match", "image", 40, 40, "red","true");
        pix_x = -1.0;
        pix_y = -1.0;

        return -1;
    }

    pix_x = findCol[0].D();
    pix_y = findRow[0].D();

    return 0;
}

//计算偏移量
int MainWindow::cal_offset(double x,double y,double &world_offset_x, double &world_offset_y)
{
    double world_x,world_y;
    // read Mat and do affine trans
    try
    {
        affine_trans_point_2d(HomMat2D, x, y, \
                          &world_x, &world_y);
        world_offset_x = world_x - m_cal_data.StdW.x;
        world_offset_y = world_y - m_cal_data.StdW.y;
    }
    catch(exception &e)
    {
        cerr<<e.what();
        return -2;
    }

    return 0;
}

/////功能函数，保留暂未使用，方便后期调试使用
//加载单张图片并处理
int MainWindow::file_image_to_process()
{
    QFile file;
    QString fileName;
    char*  ch;

    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config"), "", tr("Image Files (*.bmp)"));
    //tr("Image Files (*.png);;Image Files (*.bmp);;Image Files (*.jpg);"));
    //(*.png,*bmp,*jpg)
    QByteArray ba = fileName.toLocal8Bit();
    ch = ba.data();

    //操作文件
    read_image(&m_image, ch);
    double pix_x,pix_y;
    image_process(m_image,1,0.5,pix_x,pix_y);// the second number is the index of models

    //关闭文件
    file.close();
    ch = nullptr;

    return 0;
}

//打开文件夹,图片连续处理
int MainWindow::folder_image_to_process()
{
    //需要Qt刷新机制，或者改为发消息;界面会等待全部运行完后显示
    char*  ch;

    QString file_path = QFileDialog::getExistingDirectory(this,"请选择图片路径...","./");
    if(file_path.isEmpty())
    {
        return -1;
    }
    else
    {
        QByteArray ba = file_path.toLatin1(); // must
        ch=ba.data();

        qDebug() << file_path << endl;
        //
        HTuple hv_ImageFiles;
        list_image_files(ch, "png", "max_depth 5", &hv_ImageFiles);
        //操作文件
        int imageNum = hv_ImageFiles.Num();
        for(int i = 0;i < imageNum;i++)
        {
            read_image(&m_image,hv_ImageFiles[i].S());
            double pix_x = 0.0,pix_y = 0.0;
            image_process(m_image,1,0.5,pix_x,pix_y);
            //Sleep(500);
        }

        ch = NULL;
    }

    return 0;

}

//图片保存（原图及处理后图片，处理后图片为屏幕截图）
int MainWindow::image_save(Hobject& Image, bool bIsSaveRaw,bool bIsSaveResult)
{
    //获取当前保存的日期&&时间精确到ms
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd");

    //创建文件夹 --- 存放的文件夹：当前exe路径的./ImageResult  ./ImageRaw
    //子文件夹按日期命名：2018-10-20
    QDir image_dir_raw(m_path_exe + "/ImageRaw/" + current_date);
    QDir image_dir_res(m_path_exe + "/ImageResult/" + current_date);

    //先检测文件夹是否完备：创建
    if (false == image_dir_raw.exists())
    {
        bool is_created = image_dir_raw.mkpath(m_path_exe + "/ImageRaw/" + current_date);
        if (false == is_created)
        {
            m_log.write_log("MainWindow::image_save(): the folder ImageRaw created failed!");
            return -1;
        }
    }

    if (false == image_dir_res.exists())
    {
        bool is_created = image_dir_res.mkpath(m_path_exe + "/ImageResult/" + current_date);
        if (false == is_created)
        {
            m_log.write_log("MainWindow::image_save(): the folder ImageResult created failed!");
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
            m_log.write_log("MainWindow::image_save(): write image1 failed!");
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
           m_log.write_log("MainWindow::image_save(): write image2 failed!");
           return -4;
       }
    }

    return 0;
}

//读取标定参数（包括标准位置），暂不使用，保留功能，对应dialog类中保留的参数保存功能
int MainWindow::cal_data_ini_read()
{
    //数组初始化清零
    memset(&m_cal_data,0,sizeof(cal_data));

    m_ini.read("Cal","StdWX",m_cal_data.StdW.x);
    m_ini.read("Cal","StdWY",m_cal_data.StdW.y);
    m_ini.read("Cal","StdPX",m_cal_data.StdP.x);
    m_ini.read("Cal","StdPY",m_cal_data.StdP.y);
    m_ini.read("Cal","LuoWX",m_cal_data.LuoW.x);
    m_ini.read("Cal","LuoWY",m_cal_data.LuoW.y);

    m_ini.read("Cal","WX1",m_cal_data.W1.x);
    m_ini.read("Cal","WX2",m_cal_data.W2.x);
    m_ini.read("Cal","WX3",m_cal_data.W3.x);
    m_ini.read("Cal","WX4",m_cal_data.W4.x);
    m_ini.read("Cal","WY1",m_cal_data.W1.y);
    m_ini.read("Cal","WY2",m_cal_data.W2.y);
    m_ini.read("Cal","WY3",m_cal_data.W3.y);
    m_ini.read("Cal","WY4",m_cal_data.W4.y);

    m_ini.read("Cal","PX1",m_cal_data.P1.x);
    m_ini.read("Cal","PX2",m_cal_data.P2.x);
    m_ini.read("Cal","PX3",m_cal_data.P3.x);
    m_ini.read("Cal","PX4",m_cal_data.P4.x);
    m_ini.read("Cal","PY1",m_cal_data.P1.y);
    m_ini.read("Cal","PY2",m_cal_data.P2.y);
    m_ini.read("Cal","PY3",m_cal_data.P3.y);
    m_ini.read("Cal","PY4",m_cal_data.P4.y);

    return 0;
}


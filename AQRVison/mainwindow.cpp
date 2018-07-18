#include "mainwindow.h"
#include "ui_mainwindow.h"

//测试所使用头文件
#include <QLabel>
#include <QTime>

using namespace Halcon;

////界面构造及初始化
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //设置界面图标
    setWindowIcon(QIcon(":home.png"));
    ui->setupUi(this);
    //初始化参数变量配置   
    start_varia_init();
    std::memset(m_model_index,0,sizeof(int)*30);
    //初始化界面设置
    start_ui_init();
    //Pushbutton connection
    connect(ui->pushButton_Start, SIGNAL(clicked()), this, SLOT(pushButton_Start()));
    connect(ui->pushButton_Stop, SIGNAL(clicked()), this, SLOT(pushButton_Stop()));
    connect(ui->actionParam, SIGNAL(triggered()), this, SLOT(on_menuParam()));
    connect(ui->actionShapeModel, SIGNAL(triggered()), this, SLOT(on_menuShapeModel()));
    //tcp_ip connection
    connect(&m_tcpip_client,SIGNAL(tcpip_cli_signal(QString)),this,SLOT(m_tcpip_slot(QString)));
}

MainWindow::~MainWindow()
{
    //关闭相机
    m_snap_cam.exit();
    delete ui;
}

//窗口关闭
void MainWindow::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information( this, tr("CT Control View"),
             tr("Do you really want to quit?"),
             tr("Yes"), tr("No"),
             0, 1 ) )
    {
       case 0:
           QApplication::quit();
           break;
       case 1:
       default:
           event->ignore();
           break;
    }
}

//程序运行界面初始化，图像开窗，设置图标
int MainWindow::start_ui_init()
{
    //设置图标样式
    ui->pushButton_Start->setIcon(QIcon(":begin.png"));
    ui->pushButton_Stop->setIcon(QIcon(":stop.png"));
    ui->pushButton_Start->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");
    ui->pushButton_Stop->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(67,67,67);border-radius:10px;");
    //Widget WinId传递
    HWND hWnd = (HWND)ui->widget->winId();
    int widgetHeight = ui->widget->height();
    int widgetWidth  = ui->widget->width();
    Hlong m_DlgID = (Hlong)hWnd;
    open_window(0,0,widgetWidth,widgetHeight,m_DlgID,"visible", "",&m_win_id);
//    //开机显示图片，后期可更改为显示某logo图片
//    try
//    {
//        read_image(&m_image,"D:\\image\\hongfu\\1\\1.bmp");
//    }
//    catch (HException &except)
//    {
//        cerr<<except.err;
//        m_log.write_log("MainWindow::start_ui_init(): read image error!");
//        return -1;
//    }
//    get_image_size(m_image,&image_width,&image_height);
//    set_part(m_win_id,0,0,image_height,image_width);
//    disp_obj(m_image,m_win_id);

    return 0;
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
        m_log.write_log("MainWindow::start_varia_init(): cam init err!!!");
        return -1;
    }
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
            m_log.write_log("the match folder mkdir fail!");
            return -1;
        }
    }
    //读取模板并保存至Map，保存过程中将“match-”字符替换为空字符，并将剩余数字作为Map index
    for (int i = 0; i < list.size(); ++i)
    {
        //文件名是否合法检测
        QFileInfo fileInfo = list.at(i);
        QString pattern("^match-\\d+\\.shm$");
        QRegExp rx(pattern);
        bool res = rx.exactMatch(fileInfo.fileName());
        if (res)
        {
            int img_num = fileInfo.fileName().replace("match-", "").replace(".shm", "").toInt();
            Hlong temp;

            try
            {
                read_shape_model(qPrintable(fileInfo.filePath()), &temp);
            }
            catch (HException &except)
            {
                cerr<<except.err;
                m_log.write_log("MainWindow::hal_read_shape_model(): read_shape_model error!");
                return -2;
            }
            //模板名数字作为index
            m_ModelID[img_num] = temp;
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

        //QString strQ = QString::fromLocal8Bit("没发现匹配");
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
    //加载模板
    hal_read_shape_model();
    //加载模板对应关系
    for(int index=1;index<=30;index++)
    {
        QString model_index=index+'0';
        if(m_ini.configureFile->contains("TemplateIndex/ScrewIndex"+model_index))
        {
            m_ini.read("TemplateIndex","ScrewIndex"+model_index,m_model_index[index]);
        }
    }
    //读取仿射变换矩阵（判断是否存在）
    QString mat_file = m_path_exe + "/cal/TransHomMat2D.tup";
    QFile qfile(mat_file);
    if(false == qfile.exists())
    {
        m_log.write_log("cann't find affine trans tuple file");
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
        m_log.write_log("Read affine trans tuple failed!");
        return;
    }
    //读取标准点位(拍照位)
    m_ini.read("StandardPosition","ScrewOn_x",m_cal_data.LuoW.x);
    m_ini.read("StandardPosition","ScrewOn_y",m_cal_data.LuoW.y);
    m_ini.read("StandardPosition","WorldCoordinate_x",m_cal_data.StdW.x);
    m_ini.read("StandardPosition","WorldCoordinate_y",m_cal_data.StdW.y);
    m_ini.read("StandardPosition","PixelCoordinate_x",m_cal_data.StdP.x);
    m_ini.read("StandardPosition","PixelCoordinate_y",m_cal_data.StdP.y);
    //加载tcpip通信模块
    if (0 != tcp_init())
    {
        return ;
    }
    ui->pushButton_Stop->setEnabled(true);
    ui->pushButton_Start->setEnabled(false);
    //更改样式
    ui->pushButton_Start->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(67,67,67);border-radius:10px;");
    ui->pushButton_Stop->setStyleSheet("background-color:rgb(235,235,235);\
                                    color: rgb(0,0,0);border-radius:10px;");

    return ;
}

//////控制流程
//Tcpip
int MainWindow::tcp_init()
{
    //tcp parameters
    QString ip = "";
    int port = 0;
    m_ini.read("TcpIp", "ip", ip);
    m_ini.read("TcpIp", "port", port);

    if (0!=m_tcpip_client.init(ip, (uint&)port,&protocol_analysis))
    {     
        ui->textBrowser->append("tcpip初始化设置失败！");
        m_log.write_log("MainWindow::tcp_init(): connect error!");
        return -2;
    }
    ui->textBrowser->append("connect succeed");

    return 0;
}

//协议解析函数，解析来自服务器的字符
int MainWindow::protocol_analysis(QString mes, QString& data)
{
    QString key("snap-\\d+");
    QRegExp filter(key);
    if(filter.exactMatch(mes))
    {
        data=mes.replace("snap-","");
        return 0;
    }
    else
    {
        return -1;
    }
}

//tcpip模块触发槽函数，连接至tcp信息接收信号（Qt机制发送）
int MainWindow::m_tcpip_slot(QString mes)
{
    int m_template_num=mes.toInt();
    qDebug()<<m_template_num;
    if (m_ModelID.find(m_model_index[m_template_num]) == m_ModelID.end())
    {
        ui->textBrowser->append("the template is unexisted!!!\n");
        return -1;
    }

    ui->textBrowser->append("be snapping...\n");

    //开始处理
    m_snap_cam.snap(0);
    gen_image1(&m_image,"byte",m_snap_cam.m_cam_width,m_snap_cam.m_cam_height,(Hlong)m_snap_cam.pImageBuffer[0]);

    //image process
    double pix_x = 0.0;
    double pix_y = 0.0;
    double offset_x = 0.0;
    double offset_y = 0.0;

    int err = 0;
    err = image_process(m_image, m_ModelID[m_model_index[m_template_num]],pix_x,pix_y);
    if(0 != err)
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        image_show(m_image,py,px,false);
        ui->textBrowser->append("图像处理失败!!\n");
        return -2;
    }

    err = cal_offset(pix_x,pix_y,offset_x,offset_y);
    if(0 != err)
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        image_show(m_image,py,px,false);
        ui->textBrowser->append("cal_offset失败!!\n");
        return -3;
    }
    //PLC--->PC接收数据格式:SNAP-MODEL1 (对应不同的螺丝种类，需要调用不同的模板)
    //PC--->PLC发送数据格式:PLC-OFFSET-X-40.50-Y-30.50
    //视觉反馈：基于校正后基准点的偏移量
    QString res = "PLC-OFFSET-X-" + QString::number(offset_x, 10, 2);
    res += "-Y-" + QString::number(offset_y, 10, 2);
    if (-1 == m_tcpip_client.write(res.toLocal8Bit()))
    {
        HTuple px = 0.0;
        HTuple py = 0.0;
        image_show(m_image,py,px,true);
        ui->textBrowser->append("tcpip信息发送失败!!\n");
        m_log.write_log("MainWindow::m_tcpip_slot(): tcpip write error!");
        return -4;
    }

    //显示当前图片
    HTuple px = HTuple(pix_x);
    HTuple py = HTuple(pix_y);
    image_show(m_image,py,px,true);
//    //保存原图及处理后截图，后期取消
//    image_save(m_image,true,true);
//    //写入时间及坐标
//    m_data_file_csv.data_write(pix_x,pix_y);

    return 0;
}

//图像处理
int MainWindow::image_process(Hobject& Image,Hlong model_id,double& pix_x,double& pix_y)
{
    HTuple findRow,findCol,findAngle,findScore;

    double dradRange = HTuple(360).Rad()[0].D();
    find_shape_model(Image,  model_id, 0, dradRange , 0.5, 1, 0.5,
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
    image_process(m_image,1,pix_x,pix_y);// the second number is the index of models

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
            image_process(m_image,1,pix_x,pix_y);
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

//测试按钮触发函数
void MainWindow::on_pushButton_TestItem_clicked()
{
}

//Test Unit
//图片保存测试
//TcpIP通讯测试
//Data  功能测试 U•ェ•*U
//Cam :xiaobin.wang
//image_process
//Log

//Calibration
//Model
//Param ini

//报错机制/健壮

//检查每项是否能Class module

//计划ToDoList
//1.算法上的稳定：1天
// 光源配置成同轴，重新拍一些图
// 偏角问题
//
//2.程序放在工控机上跑
//
//3.程序：测试/防错
//
//4.整体流程配合程序
//
//5.鸿富：下周一/周二沟通，调试人员对上。该沟通的技术问题，沟通。
//
//6.加密事宜：：ok -- 测试
//

//-----------------
//calibration save ini /
//函数测试和单元测试。
//
//

//modify log
//------20180612完成的工作 by wuwei------
//1.on_pushButton_Start_clicked() log打印
//2.hal_read_shape_model() log打印
//3.image_save()log打印
//4.针对read_shape_model(),write_image()函数进行出错检测及后台log打印
//5.新增对ip、port的合法性检测

//------20180613完成的工作 by wuwei------
//1.dialogshapemodel界面双击功能实现
//2.主界面与子界面进行相机句柄传递
//3.实现自定义异常处理

//------20180614完成的工作 by wuwei------
//1.主、子界面dialog相机句柄共享功能基本实现
//2.主、子界面dialogshapemodel相机句柄共享功能基本实现
//3.主、子窗口关闭问题

//------20180615完成的工作 by wuwei------
//1.窗口界面图标样式
//2.部分代码维护
//3.图片上显示中文问题

//------20180619完成的工作 by wuwei------
//1.cam.cpp维护v1.0
//2.QMessageBox模块化
//3.dialog维护v1.0
//4.

//存在问题
//1.dialogshapemodel界面测试按钮需求未表明
//2.界面放大缩小问题
//4.dialog模块维护问题(按钮槽函数多且杂)
//5.aqlog问题，每个界面操作时都new一个aqlog，而每个都有自己新建的log日志
//6.cam.cpp文件维护
//7.

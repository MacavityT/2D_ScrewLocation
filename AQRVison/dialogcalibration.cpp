#include "dialogcalibration.h"
#include "ui_dialog.h"

////界面构造及内部参数初始化
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    //设置界面图标
    setWindowIcon(QIcon(":home.png"));
    ui->setupUi(this);

    hal_init();
    m_path_exe = QCoreApplication::applicationDirPath();
}

Dialog::~Dialog()
{
    delete ui;
}

//窗口关闭事件重载
void Dialog::closeEvent(QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("CT Control View"),
     tr("Do you really want to log out CT Control View?"),
     tr("Yes"), tr("No"),
     0, 1 ) )
    {
       case 0:
           //m_cam.exit();
           event->accept();
           break;
       case 1:
       default:
           event->ignore();
           break;
    }
}

//图像开窗
int Dialog::hal_init()
{
    //hal WinID
    HWND hWnd = (HWND)ui->widget->winId();
    int widgetHeight = ui->widget->height();
    int widgetWidth  = ui->widget->width();
    Hlong m_DlgID = (Hlong)hWnd;
    open_window(0,0,widgetWidth,widgetHeight,m_DlgID,"visible", "",&m_win_id);

    return 0;
}

//传递相机对象，同步父子窗口相机
int Dialog::cam_init(basler_cam *ptr_cam)
{
    p_cam = ptr_cam;
    return 0;
}

////界面控制
//拍照按钮
void Dialog::on_pushButtonSnapOne_clicked()
{
    //Cal Snap
    if(0!=p_cam->snap(0))
    {
        return;
    }

    //获取数据
    gen_image1(&m_image,"byte",\
                  (*p_cam).m_cam_width,(*p_cam).m_cam_height,\
                  (Hlong)(*p_cam).pImageBuffer[0]);
    //Show
    set_part(m_win_id,0,0,(*p_cam).m_cam_height,(*p_cam).m_cam_width);
    disp_obj(m_image,m_win_id);
}

//取图按钮
void Dialog::on_pushButtonPicOne_clicked()
{
    QFile file;
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config"), "", tr("Image Files (*.bmp)"));
    //tr("Image Files (*.png);;Image Files (*.bmp);;Image Files (*.jpg);"));
    //(*.png,*bmp,*jpg)
    QByteArray ba = fileName.toLocal8Bit();
    if(ba.size()==0){
        qDebug()<<"No image has been selected!";
        return;
    }
    char* ch = ba.data();

    //操作文件
    read_image(&m_image,ch);
    //Show Image
    Hlong part_image_width = 0;
    Hlong part_image_height = 0;

    get_image_size(m_image,&part_image_width,&part_image_height);
    set_part(m_win_id,0,0,part_image_height,part_image_width);
    disp_obj(m_image,m_win_id);

    //关闭文件
    file.close();
    ch = NULL;

    return ;
}

////标定点坐标，直接填写后点击标定按钮
//获取物理点按钮，通信获取点位过于麻烦,保留按钮，方便后期功能扩展
void Dialog::on_pushButton1_stdw_clicked()
{
    //通讯PLC交互，获取当前物理点
    ui->textEdit1_wx->toPlainText().toDouble();
    ui->textEdit1_wy->toPlainText().toDouble();
}

void Dialog::on_pushButton2_stdw_clicked()
{
    ui->textEdit2_wx->toPlainText().toDouble();
    ui->textEdit2_wy->toPlainText().toDouble();
}

void Dialog::on_pushButton3_stdw_clicked()
{
    ui->textEdit3_wx->toPlainText().toDouble();
    ui->textEdit3_wy->toPlainText().toDouble();
}

void Dialog::on_pushButton4_stdw_clicked()
{
    ui->textEdit4_wx->toPlainText().toDouble();
    ui->textEdit4_wy->toPlainText().toDouble();
}

//获取图像点按钮，用户手动圆形工具选取点坐标
void Dialog::on_pushButton1_stdp_clicked()
{
    //获取图像点
    double row = 0.0,col = 0.0,radius =0.0;

    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("请在图像上画出圆！！");
    msgBox.exec();

    draw_circle(m_win_id,&row,&col,&radius);
    //image -- 对应model ，涉及 须Process_image做成class
    //ui 交互
    ui->textEdit1_px->setText(QString::number(col, 10, 2));
    ui->textEdit1_py->setText(QString::number(row, 10, 2));

}

void Dialog::on_pushButton2_stdp_clicked()
{
    //获取图像点
    double row = 0.0,col = 0.0,radius =0.0;

    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("请在图像上画出圆！！");
    msgBox.exec();

    draw_circle(m_win_id,&row,&col,&radius);
    //image -- 对应model ，涉及 须Process_image做成class
    //ui 交互
    ui->textEdit2_px->setText(QString::number(col, 10, 2));
    ui->textEdit2_py->setText(QString::number(row, 10, 2));
}

void Dialog::on_pushButton3_stdp_clicked()
{
    //获取图像点
    double row = 0.0,col = 0.0,radius =0.0;

    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("请在图像上画出圆！！");
    msgBox.exec();

    draw_circle(m_win_id,&row,&col,&radius);
    //image -- 对应model ，涉及 须Process_image做成class
    //ui 交互
    ui->textEdit3_px->setText(QString::number(col, 10, 2));
    ui->textEdit3_py->setText(QString::number(row, 10, 2));
}

void Dialog::on_pushButton4_stdp_clicked()
{
    //获取图像点
    double row = 0.0,col = 0.0,radius =0.0;

    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("请在图像上画出圆！！");
    msgBox.exec();

    draw_circle(m_win_id,&row,&col,&radius);
    //image -- 对应model ，涉及须Process_image做成class
    //ui 交互
    ui->textEdit4_px->setText(QString::number(col, 10, 2));
    ui->textEdit4_py->setText(QString::number(row, 10, 2));
}

//Calibration
void Dialog::on_pushButtonCalibra_clicked()
{
    //输入检查
    HTuple HomMat2D;
    HTuple Px,Py,Qx,Qy;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warnning");
    //标定数据
    double t1_px = ui->textEdit1_px->toPlainText().toDouble();
    double t2_px = ui->textEdit2_px->toPlainText().toDouble();
    double t3_px = ui->textEdit3_px->toPlainText().toDouble();
    double t4_px = ui->textEdit4_px->toPlainText().toDouble();

    double t1_py = ui->textEdit1_py->toPlainText().toDouble();
    double t2_py = ui->textEdit2_py->toPlainText().toDouble();
    double t3_py = ui->textEdit3_py->toPlainText().toDouble();
    double t4_py = ui->textEdit4_py->toPlainText().toDouble();

    double t1_wx = ui->textEdit1_wx->toPlainText().toDouble();
    double t2_wx = ui->textEdit2_wx->toPlainText().toDouble();
    double t3_wx = ui->textEdit3_wx->toPlainText().toDouble();
    double t4_wx = ui->textEdit4_wx->toPlainText().toDouble();

    double t1_wy = ui->textEdit1_wy->toPlainText().toDouble();
    double t2_wy = ui->textEdit2_wy->toPlainText().toDouble();
    double t3_wy = ui->textEdit3_wy->toPlainText().toDouble();
    double t4_wy = ui->textEdit4_wy->toPlainText().toDouble();
    //检测数据情况
    if(t1_px*t2_px*t3_px*t4_px*t1_py*t2_py*t3_py*t4_py*\
            t1_wx*t2_wx*t3_wx*t4_wx*t1_wy*t2_wy*t3_wy*t4_wy==0)
    {
        msgBox.setText("Please fill up the coordinate data!");
        msgBox.exec();
        return;
    }
    //转化
    //标定时相机运动，螺丝不动，则图像为反逻辑
    Px[0] = t1_px;
    Px[1] = 2*t1_px-t2_px;
    Px[2] = 2*t1_px-t3_px;
    Px[3] = 2*t1_px-t4_px;

    Py[0] = t1_py;
    Py[1] = 2*t1_py-t2_py;
    Py[2] = 2*t1_py-t3_py;
    Py[3] = 2*t1_py-t4_py;

    Qx[0] = t1_wx;
    Qx[1] = t2_wx;
    Qx[2] = t3_wx;
    Qx[3] = t4_wx;

    Qy[0] = t1_wy;
    Qy[1] = t2_wy;
    Qy[2] = t3_wy;
    Qy[3] = t4_wy;
    //标定
    try
    {
        vector_to_hom_mat2d(Px,Py,Qx,Qy,&HomMat2D);
    }
    catch(...)
    {
        msgBox.setText("Generic affine transformation matrix failed!");
        msgBox.exec();
        return;
    }
    //判断文件夹是否存在，不存在则创建
    QDir dir(m_path_exe + "/cal/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    if (false == dir.exists())
    {
        bool is_mkdir = dir.mkdir(m_path_exe + "/cal/");
        if (false == is_mkdir)
        {
            m_log.write_log("Calibration::write calibration tuple(): the folder cal mkdir failed!");
            return;
        }
    }
    //写入hom_mat
    QString qdstr = m_path_exe + "/cal/TransHomMat2D.tup";
    QByteArray ba = qdstr.toLatin1();
    char* ch=ba.data();
    write_tuple (HomMat2D, ch);
    //Show HomMat2D
    ui->textEdit_Data->setText(QString::number(HomMat2D[0].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[1].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[2].D(),10,2)
                +QString("\n")+QString::number(HomMat2D[3].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[4].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[5].D(),10,2)
            );

}

////基准点坐标保存
void Dialog::on_pushButton_ShangStd_clicked()
{
    m_ini.write("StandardPosition","ScrewOn_x",ui->textEdit_ShangStdx->toPlainText().toDouble());
    m_ini.write("StandardPosition","ScrewOn_y",ui->textEdit_ShangStdy->toPlainText().toDouble());
}

void Dialog::on_pushButton_StdW_clicked()
{
    m_ini.write("StandardPosition","WorldCoordinate_x",ui->textEdit_wStdx->toPlainText().toDouble());
    m_ini.write("StandardPosition","WorldCoordinate_y",ui->textEdit_wStdy->toPlainText().toDouble());
}

void Dialog::on_pushButton_Stdpix_clicked()
{
    m_ini.write("StandardPosition","PixelCoordinate_x",ui->textEdit_pStdx->toPlainText().toDouble());
    m_ini.write("StandardPosition","PixelCoordinate_y",ui->textEdit_pStdy->toPlainText().toDouble());
}

////保留功能
//保存所有标定数据（包括基准点），暂未使用，保留功能
int Dialog::write_cal_point_data()
{
    //螺丝数据
    int ls_x = ui->textEdit_ShangStdx->toPlainText().toInt();
    int ls_y = ui->textEdit_ShangStdy->toPlainText().toInt();
    m_ini.write("Cal", "LuoWX", ls_x);
    m_ini.write("Cal", "LuoWY", ls_y);

    //物理数据
    int stdw_x = ui->textEdit_wStdx->toPlainText().toInt();//控件名错误
    int stdw_y = ui->textEdit_wStdy->toPlainText().toInt();//控件名错误
    m_ini.write("Cal", "StdWX", stdw_x);
    m_ini.write("Cal", "StdWY", stdw_y);

    //图像数据
    int stdp_x = ui->textEdit_pStdx->toPlainText().toInt();
    int stdp_y = ui->textEdit_pStdy->toPlainText().toInt();
    m_ini.write("Cal", "StdPX", stdp_x);
    m_ini.write("Cal", "StdPY", stdp_y);

    //点1
    int one_wx = ui->textEdit1_wx->toPlainText().toInt();
    int one_wy = ui->textEdit1_wy->toPlainText().toInt();
    int one_px = ui->textEdit1_px->toPlainText().toInt();
    int one_py = ui->textEdit1_py->toPlainText().toInt();
    m_ini.write("Cal", "WX1", one_wx);
    m_ini.write("Cal", "WY1", one_wy);
    m_ini.write("Cal", "WX1", one_px);
    m_ini.write("Cal", "WY1", one_py);

    //点2
    int two_wx = ui->textEdit2_wx->toPlainText().toInt();
    int two_wy = ui->textEdit2_wy->toPlainText().toInt();
    int two_px = ui->textEdit2_px->toPlainText().toInt();
    int two_py = ui->textEdit2_py->toPlainText().toInt();
    m_ini.write("Cal", "WX2", two_wx);
    m_ini.write("Cal", "WY2", two_wy);
    m_ini.write("Cal", "WX2", two_px);
    m_ini.write("Cal", "WY2", two_py);

    //点3
    int three_wx = ui->textEdit3_wx->toPlainText().toInt();
    int three_wy = ui->textEdit3_wy->toPlainText().toInt();
    int three_px = ui->textEdit3_px->toPlainText().toInt();
    int three_py = ui->textEdit3_py->toPlainText().toInt();
    m_ini.write("Cal", "WX3", three_wx);
    m_ini.write("Cal", "WY3", three_wy);
    m_ini.write("Cal", "WX3", three_px);
    m_ini.write("Cal", "WY3", three_py);

    //点4
    int four_wx = ui->textEdit4_wx->toPlainText().toInt();
    int four_wy = ui->textEdit4_wy->toPlainText().toInt();
    int four_px = ui->textEdit4_px->toPlainText().toInt();
    int four_py = ui->textEdit4_py->toPlainText().toInt();
    m_ini.write("Cal", "WX4", four_wx);
    m_ini.write("Cal", "WY4", four_wy);
    m_ini.write("Cal", "WX4", four_px);
    m_ini.write("Cal", "WY4", four_py);

    return 0;
}


//测试按钮
void Dialog::on_pushButton_Test_clicked()
{
//    write_cal_point_data();
}

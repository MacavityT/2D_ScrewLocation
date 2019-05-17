#include "dialogcalibration.h"
#include "ui_dialogcalibration.h"

////界面构造及内部参数初始化
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //设置界面图标
    setWindowIcon(QIcon(":home.png"));  
    this->setWindowTitle("Calibration dialog");
    //标定参数初始化
    memset(Calibrate_data_X,0,sizeof(double)*10);
    memset(Calibrate_data_Y,0,sizeof(double)*10);
    //路径初始化
    m_path_exe = QCoreApplication::applicationDirPath();
    //窗口控件初始化
    widget_init();
    //显示参数初始化
    parameter_init();
    //Halocn窗体初始化
    hal_init();
}

Dialog::~Dialog()
{
    delete ui;
}

//窗口关闭事件重载
void Dialog::closeEvent(QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("CT Control View"),
     tr("Do you really want to log out calibration View?"),
     tr("Yes"), tr("No"),
     0, 1 ) )
    {
       case 0:
           event->accept();
           break;
       case 1:
       default:
           event->ignore();
           break;
    }
}

//传递相机对象，同步父子窗口相机
int Dialog::cam_init(basler_cam *ptr_cam)
{
    p_cam = ptr_cam;
    return 0;
}

//窗口控件初始化
void Dialog::widget_init()
{
    //初始化按钮控件样式表
    auto all_object=this->children();
    QObjectList::iterator i;
    for(i=all_object.begin();i!=all_object.end();++i)
    {
        QObject* wid=*i;
        //获取对象类型名
        QString type_name="";
        const char* name_ptr=wid->metaObject()->className();
        for(name_ptr;*name_ptr!='\0';name_ptr++)
        {
            type_name+=*name_ptr;
        }
        //被操作对象的类型名
        QString name1="QPushButton";
        if(type_name==name1)
        {
            static_cast<QPushButton*>(wid)->setStyleSheet("background-color:rgb(225,225,225);\
                                                          border-radius:10px;");
        }
    }
}

//显示参数初始化
void Dialog::parameter_init()
{
    //螺丝数据
    QString ShangStdx,ShangStdy;
    m_ini.read("StandardPosition","ScrewOn_x",ShangStdx);
    m_ini.read("StandardPosition","ScrewOn_y",ShangStdy);
    ui->textEdit_ShangStdx->setText(ShangStdx);
    ui->textEdit_ShangStdy->setText(ShangStdy);
    //物理数据
    QString wStdx,wStdy;
    m_ini.read("StandardPosition","WorldCoordinate_x",wStdx);
    m_ini.read("StandardPosition","WorldCoordinate_y",wStdy);
    ui->textEdit_wStdx->setText(wStdx);
    ui->textEdit_wStdy->setText(wStdy);

    //图像数据
    QString pStdx,pStdy;
    m_ini.read("StandardPosition","PixelCoordinate_x",pStdx);
    m_ini.read("StandardPosition","PixelCoordinate_y",pStdy);
    ui->textEdit_pStdx->setText(pStdx);
    ui->textEdit_pStdy->setText(pStdy);

    //偏移量数据
    QString offsetX,offsetY;
    m_ini.read("StandardPosition","OffsetX",offsetX);
    m_ini.read("StandardPosition","OffsetY",offsetY);
    ui->textEdit_offsetX->setText(offsetX);
    ui->textEdit_offsetY->setText(offsetY);

    //标定点数据
    for(int i=1;i<10;i++)
    {
        QString index=QString::number(i);
        m_ini.read("Cal", "WX"+index, Calibrate_data_X[i]);
        m_ini.read("Cal", "WY"+index, Calibrate_data_Y[i]);
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
    set_part(m_win_id,0,0,1944,2592);
    set_color(m_win_id,"green");
    set_draw(m_win_id,"margin");
    set_line_width(m_win_id,3);

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
    //Clear window
    clear_window(m_win_id);
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

////标定点坐标，只需要填写物理坐标，图像坐标为固定坐标
void Dialog::on_PointSelector_activated(int index)
{
    Calibrate_Point=index;
    ui->XCoordinate->setText(QString::number(Calibrate_data_X[index]));
    ui->YCoordinate->setText(QString::number(Calibrate_data_Y[index]));
}

void Dialog::on_XCoordinate_textChanged()
{
    Calibrate_data_X[Calibrate_Point]=ui->XCoordinate->toPlainText().toDouble();
}

void Dialog::on_YCoordinate_textChanged()
{
    Calibrate_data_Y[Calibrate_Point]=ui->YCoordinate->toPlainText().toDouble();
}

//Calibration
void Dialog::on_pushButtonCalibra_clicked()
{
    HTuple HomMat2D;
    HTuple Px,Py,Qx,Qy;
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warnning");
    //检测数据情况
    for(int i=1;i<10;i++)
    {
        if(Calibrate_data_X[i]==0||Calibrate_data_Y[i]==0)
        {
            msgBox.setText("Please fill up the coordinate data!");
            msgBox.exec();
            return;
        }
    }
    //图像坐标
    HTuple URow=1944/4;
    HTuple UCol=2592/4;
    Px[0]=UCol;
    Py[0]=URow;
    Px[1]=2*UCol;
    Py[1]=URow;
    Px[2]=3*UCol;
    Py[2]=URow;

    Px[3]=3*UCol;
    Py[3]=2*URow;
    Px[4]=2*UCol;
    Py[4]=2*URow;
    Px[5]=UCol;
    Py[5]=2*URow;

    Px[6]=UCol;
    Py[6]=3*URow;
    Px[7]=2*UCol;
    Py[7]=3*URow;
    Px[8]=3*UCol;
    Py[8]=3*URow;
    //世界坐标
    for(int k=0;k<9;k++)
    {
        Qx[k]=Calibrate_data_X[k+1];
        Qy[k]=Calibrate_data_Y[k+1];
    }
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
    //写入所有点坐标
    write_cal_point_data();
    //Show HomMat2D
    ui->textEdit_Data->setText(QString::number(HomMat2D[0].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[1].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[2].D(),10,2)
                +QString("\n")+QString::number(HomMat2D[3].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[4].D(),10,2)
                +QString("  ")+QString::number(HomMat2D[5].D(),10,2)
            );

}

//保存所有标定数据（包括基准点）
int Dialog::write_cal_point_data()
{
    //螺丝数据
    m_ini.write("StandardPosition","ScrewOn_x",ui->textEdit_ShangStdx->toPlainText().toDouble());
    m_ini.write("StandardPosition","ScrewOn_y",ui->textEdit_ShangStdy->toPlainText().toDouble());

    //物理数据
    m_ini.write("StandardPosition","WorldCoordinate_x",ui->textEdit_wStdx->toPlainText().toDouble());
    m_ini.write("StandardPosition","WorldCoordinate_y",ui->textEdit_wStdy->toPlainText().toDouble());

    //图像数据
    m_ini.write("StandardPosition","PixelCoordinate_x",ui->textEdit_pStdx->toPlainText().toDouble());
    m_ini.write("StandardPosition","PixelCoordinate_y",ui->textEdit_pStdy->toPlainText().toDouble());

    //偏移量范围
    m_ini.write("StandardPosition","OffsetX",ui->textEdit_offsetX->toPlainText().toDouble());
    m_ini.write("StandardPosition","OffsetY",ui->textEdit_offsetY->toPlainText().toDouble());

    //标定点数据（世界坐标）
    for(int i=1;i<10;i++)
    {
        QString index=QString::number(i);
        m_ini.write("Cal", "WX"+index, Calibrate_data_X[i]);
        m_ini.write("Cal", "WY"+index, Calibrate_data_Y[i]);
    }
    return 0;
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


void Dialog::on_pushButton_OffsetValue_clicked()
{
    m_ini.write("StandardPosition","OffsetX",ui->textEdit_offsetX->toPlainText().toDouble());
    m_ini.write("StandardPosition","OffsetY",ui->textEdit_offsetY->toPlainText().toDouble());
}

//测试按钮
void Dialog::on_pushButton_Test_clicked()
{
    //判断图片是否为空
    if(m_image.Id()==H_EMPTY_REGION)
    {
        DialogShapeModel::print_qmess(QString("Please select image"));
        return;
    }
    //判断矩阵是否存在
    QString mat_file = m_path_exe + "/cal/TransHomMat2D.tup";
    QFile qfile(mat_file);
    if(false == qfile.exists())
    {
        DialogShapeModel::print_qmess(QString("Cann't find affine trans tuple file!"));
        return;
    }
    //读取仿射变换矩阵
    char *ch;
    QByteArray ba = mat_file.toLatin1();
    ch = ba.data();
    HTuple HomMat2D;
    try
    {
        read_tuple(ch, &HomMat2D);
    }
    catch(...)
    {
        DialogShapeModel::print_qmess(QString("Read affine trans tuple failed!"));
        return;
    }
    //读取标准点位(拍照位)
    double LuoW_x,LuoW_y;
    double StdW_x,StdW_y;
    double StdP_x,StdP_y;
    m_ini.read("StandardPosition","ScrewOn_x",LuoW_x);
    m_ini.read("StandardPosition","ScrewOn_y",LuoW_y);
    m_ini.read("StandardPosition","WorldCoordinate_x",StdW_x);
    m_ini.read("StandardPosition","WorldCoordinate_y",StdW_y);
    m_ini.read("StandardPosition","PixelCoordinate_x",StdP_x);
    m_ini.read("StandardPosition","PixelCoordinate_y",StdP_y);
    //获取测试点坐标
    double row = 0.0,col = 0.0,radius =0.0;
    draw_circle(m_win_id,&row,&col,&radius);
    //仿射变换
    double world_x,world_y;
    double mid_x,mid_y;
    try
    {
        affine_trans_point_2d(HomMat2D,col,row,&world_x,&world_y);//检测位置
        affine_trans_point_2d(HomMat2D,StdP_x,StdP_y,&mid_x,&mid_y);
    }
    catch(...)
    {
        DialogShapeModel::print_qmess(QString("Affine trans process failed!"));
    }
    //计算偏移量
    double world_offset_x,world_offset_y;
    world_offset_x = (world_x - mid_x) + (LuoW_x - StdW_x);
    world_offset_y = (world_y - mid_y) + (LuoW_y - StdW_y);
    //结果显示
    disp_message (m_win_id, "X="+HTuple(world_offset_x)+\
                  "  Y="+HTuple(world_offset_y),\
                  "image", 40, 40, "green","true");
}

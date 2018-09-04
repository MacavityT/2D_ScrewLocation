#include "dialogshapemodel.h"
#include "ui_dialogshapemodel.h"

#include "qfile.h"
#include "qfiledialog.h"
#include "qdebug.h"
#include <QLabel>
#include <QDebug>

DialogShapeModel::DialogShapeModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShapeModel)
{
    //设置界面图标
    setWindowIcon(QIcon(":home.png"));
    ui->setupUi(this);
    ui->pushButtonCreateShapeModel->setEnabled(false);
    //设置路径选择窗口
    fileDialog=new QFileDialog(this);
    //define fileDialog title
    fileDialog->setWindowTitle(tr("保存图片"));
    //set default path
    fileDialog->setDirectory("./");
    //初始化参数变量配置
    start_param_init();
    //初始化界面设置
    start_ui_init();
    //按钮功能
    connect(ui->pushButtonPicOne,SIGNAL(clicked()), this, SLOT(ClickButtonPicOne()));
    connect(ui->pushButtonCreateShapeModel, SIGNAL(clicked()), this, SLOT(ClickButtonCreateShapeModel()));
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_listView_activated(QModelIndex)));
    //线程采集，数据传输
    connect(this,SIGNAL(signal_image_capture()),&m_image_capture,SLOT(slot_image_capture()));
    connect(&m_image_capture,SIGNAL(signal_transmit_image(Hobject)),this,SLOT(slot_transmit_image(Hobject)));
    //刷新模版列表
    refresh_list();       
    //初始化采集线程
    m_image_capture.moveToThread(&m_thread);
    m_thread.start();
}

DialogShapeModel::~DialogShapeModel()
{
    delete fileDialog;
    fileDialog=nullptr;
    //触发标志复位
    first_trigger=true;
    //回收线程
    m_thread.terminate();
    m_thread.wait();
    m_thread.deleteLater();
    delete ui;
}

//窗口关闭事件重载
void DialogShapeModel::closeEvent(QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("CT Control View"),
     tr("Do you really want to log out Shape model View?"),
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

//主从窗口传递相机对象
int DialogShapeModel::cam_init(basler_cam *ptr_cam)
{
    p_cam = ptr_cam;
    return 0;
}

//界面初始化
int DialogShapeModel::start_ui_init()
{
    //hal WinID
    HWND hWnd = (HWND)ui->widget->winId();
    int widgetHeight = ui->widget->height();
    int widgetWidth  = ui->widget->width();
    Hlong m_DlgID = (Hlong)hWnd;
    open_window(0,0,widgetWidth,widgetHeight,m_DlgID,"visible", "",&m_win_id);
//    set_part(m_win_id,0,0,(*p_cam).m_cam_height,(*p_cam).m_cam_width); 初始化此界面类时，相机类未初始化完成
    set_part(m_win_id,0,0,1944,2592);

    return 0;
}

//参数初始化
int DialogShapeModel::start_param_init()
{
    //field init
    m_fileName = "";
    index_delete = -1;
    m_path_exe = QCoreApplication::applicationDirPath();
    standardItemModel = new QStandardItemModel(this);

    //初始化刷新list 封装函数 待改
    QDir dir(m_path_exe + "/match/");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    //读取合法的模板文件
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QString pattern("^match-\\d+\\.shm$");
        QRegExp rx(pattern);
        bool res = rx.exactMatch(fileInfo.fileName());

        if (res)
        {
            strList.append(fileInfo.fileName());
        }
        else
        {
            continue;
        }
    }

    return 0;
}

//按钮：连续采图
void DialogShapeModel::on_pushButtonPicContinue_clicked()
{
    //首次触发线程
    if(first_trigger)
    {
        m_image_capture.param_set(p_cam);
        emit signal_image_capture();
    }
    //控件使能
    bool status=ui->pushButtonPicOne->isEnabled();
    foreach (QAbstractButton* button, ui->ViewControl->buttons()) {
        if(button->objectName()!="pushButtonPicContinue")
        {
            button->setEnabled(!status);//可以写为下一行，更骚一些，但没啥必要
//            static_cast<QPushButton*>(button)->setEnabled(!status);
        }
    }
    //线程控制
    m_image_capture.m_continue=status;
    if(status)
        ui->pushButtonPicContinue->setText(tr("停止采图"));
    else
        ui->pushButtonPicContinue->setText(tr("连续采图"));
}

void DialogShapeModel::slot_transmit_image(Hobject image)
{
    //获取并显示图像，由线程不断触发
    disp_obj(image,m_win_id);
}

//按钮：单帧采图
void DialogShapeModel::on_pushButtonSnapOne_clicked()
{
    if(0!=p_cam->snap(0))
    {
        print_qmess(QString("Image capture failed!"));
        return;
    }

    //获取数据
    gen_image1(&m_image,"byte",\
                  (*p_cam).m_cam_width,(*p_cam).m_cam_height,\
                  (Hlong)(*p_cam).pImageBuffer[0]);

    //Show

    disp_obj(m_image,m_win_id);
}

//按钮：保存图片
void DialogShapeModel::on_pushButtonSaveOne_clicked()
{
    QString filename=fileDialog->getSaveFileName(this,tr("Image name"),"",tr("Image(*.bmp)"));
    if(filename.isEmpty())
    {
        print_qmess(QString("请选择命名"));
        return;
    }
    QByteArray trans=filename.toLatin1();
    try
    {
        write_image(m_image, "bmp", 0, trans.data());
    }
    catch (HException &except)
    {
        cerr<<except.err;
        m_log.write_log("DialogShapeModel::on_pushButtonSaveOne_clicked(): write image1 failed!");
        return;
    }
}

//按钮：加载图片
int DialogShapeModel::ClickButtonPicOne()
{
    QFile file;
    QString fileName;
    char*  ch;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config"), "", tr("Image Files (*.png *bmp *jpg)"));
    if (fileName.isEmpty())
    {
        return -1;
    }
    QByteArray ba = fileName.toLocal8Bit();
    ch = ba.data();
    //读取并显示
    try
    {
        read_image(&m_image, ch);
    }
    catch(HException &e)
    {
        std::cerr<<e.err;
    }
    //Show Image
    get_image_size(m_image,&image_width,&image_height);
    disp_obj(m_image,m_win_id);

    file.close();
    ch = nullptr;

    return 0;
}

//选择模版对应关系
void DialogShapeModel::on_combo_ShangStd_activated(int index)
{
    screw_num=index;
}

void DialogShapeModel::on_combo_Type_activated(int index)
{
    screw_type=index;
}


//关系确定后命名并创建模板
void DialogShapeModel::on_pushButton_confirm_clicked()
{
    //判断是否选择螺丝及模板对应关系
    if(screw_num*screw_type==0)
    {
        print_qmess(QString("Plese select the screw and driver number!"));
        return;
    }
    //模版命名
    QString screw_index,driver_index;
    driver_index.setNum(screw_type);
    screw_index.setNum(screw_num);
    m_fileName=driver_index+'_'+screw_index;

    //开始绘画模板
    draw_show();
    //完成创建后保存按钮使能
    ui->pushButtonCreateShapeModel->setEnabled(true);
}

//保存模板
int DialogShapeModel::ClickButtonCreateShapeModel()
{
    //判断是否已经为模板命名
    if (m_fileName.isEmpty())
    {
        print_qmess(QString("请选择批头及其对应螺丝编号！"));
        return -1;
    }
    //保存模板及图像
    if (0 != save_templa_image())
    {
        return -1;
    }
    print_qmess(QString("succeed!"));//结果显示
    //刷新list
    strList.append("match-" + m_fileName + ".shm");
    refresh_list();

    return 0;
}

//模板创建过程与显示
int DialogShapeModel::draw_show()
{
    //提示画一个圆圈
    set_color(m_win_id,"green");
    set_line_width(m_win_id,3);
    draw_circle(m_win_id,&m_create_row,&m_create_col,&m_create_radius);
    disp_circle(m_win_id,m_create_row,m_create_col,m_create_radius);
    copy_obj(m_image, &cpy_image, 1, 1);
    gen_circle(&m_modelRegion, m_create_row,m_create_col,m_create_radius);

    reduce_domain(cpy_image, m_modelRegion, &m_templateImage);
    try{
        create_shape_model(m_templateImage,  6, HTuple(0).Rad(), HTuple(360).Rad(),
                           HTuple(0.5896).Rad(), (HTuple("point_reduction_high").Append("no_pregeneration")),
                           "use_polarity", ((HTuple(21).Append(49)).Append(14)), 11, &m_ModelID);
    }
    catch(...)
    {
        print_qmess(QString("Create shape model failed!"));
        disp_image(m_templateImage,m_win_id);
        return -1;
    }

    //获取模板到image中并提取其中的相关要素
    get_shape_model_contours (&m_ModelContours, m_ModelID, 1);
    area_center(m_modelRegion, &hv_ModelRegionArea, &hv_RefRow, &hv_RefColumn);
    vector_angle_to_rigid(0, 0, 0, hv_RefRow, hv_RefColumn, 0, &hv_HomMat2D);
    affine_trans_contour_xld(m_ModelContours, &m_TransContours, hv_HomMat2D);

    //显示模板轮廓
    disp_obj(cpy_image, m_win_id);
    set_color(m_win_id, "green");
    set_draw(m_win_id, "margin");
    disp_obj(m_modelRegion, m_win_id);
    disp_obj(m_TransContours, m_win_id);

    return 0;
}

//模板创建后的处理，包括保存模板及对应的图片
int DialogShapeModel::save_templa_image()
{
    //保存模板
    QString qdstr = m_path_exe + QString("/match/match-" + m_fileName + ".shm");
    QByteArray ba = qdstr.toLocal8Bit();
    char* ch = ba.data();

    try
    {
        write_shape_model(m_ModelID, ch);
    }
    catch (HException &except)
    {
        m_log.write_log("DialogShapeModel::save_templa_image(): error!");
        return -1;
    }

    //保存图片
    //读取文件夹
    QDir dir(m_path_exe + "/matchImage/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    //判断文件夹是否存在，不存在则创建
    if (false == dir.exists())
    {
        bool is_mkdir = dir.mkdir(m_path_exe + "/matchImage/");
        if (false == is_mkdir)
        {
            m_log.write_log("DialogShapeModel::save_templa_image(): the folder matchImage mkdir failed!");
            return -2;
        }
    }

    qdstr = m_path_exe + QString("/matchImage/" + m_fileName + ".bmp");
    ba = qdstr.toLocal8Bit();
    ch = ba.data();

    try
    {
        write_image(m_image, "bmp", 0, ch);
    }
    catch (HException &except)
    {
        m_log.write_log("DialogShapeModel::save_templa_image(): write image failed!");
        return -3;
    }

    return 0;
}

//模板删除按钮，单击模版名后点击删除
void DialogShapeModel::on_pushButton_delete_clicked()
{
    switch( QMessageBox::information( this, tr("提示"),
             tr("Do you really want to delete the file?"),
             tr("Yes"), tr("No"),
             0, 1 ) )
    {
       case 0:
           deleteFile();
           break;
       case 1:
       default:
           break;
    }
}

//=========模板删除模块
void DialogShapeModel::deleteFile()
{
    if (index_delete != -1)
    {
        QModelIndex m_index = standardItemModel->index(index_delete, 0);
        QString del_file_name = m_index.data().toString();
        QFile del_f(m_path_exe + "/match/" + del_file_name);

        if (del_f.exists())
        {
            del_f.remove();
            print_qmess(QString("delete succeed!"));
        }
        del_f.close();

        QList<QString>::Iterator it = strList.begin(),itend = strList.end();
        for (;it != itend; it++){
            if (*it == del_file_name)
            {
                strList.erase(it);
            }
        }
        standardItemModel->removeRow(index_delete);
    }
    index_delete = -1;
    ui->pushButton_delete->setEnabled(false);
}

//列表元素激活
void DialogShapeModel::on_listView_activated(const QModelIndex &index)
{
    ui->pushButton_delete->setEnabled(true);
    index_delete = index.row();
}

//列表元素双击方法，显示保存的模版图片
void DialogShapeModel::on_listView_doubleClicked(const QModelIndex &index)
{
    //find the image name
    index_delete = index.row();
    QModelIndex m_index = standardItemModel->index(index_delete, 0);
    QString template_name = m_index.data().toString();
    QString image_name = template_name.replace("match-", "").replace(".shm", "");
    QString qdstr = m_path_exe + QString("/matchImage/" + image_name + ".bmp");
    QByteArray ba = qdstr.toLocal8Bit();
    char* ch = ba.data();

    //Show
    try
    {
        read_image(&m_image, ch);
    }
    catch (HException &except)
    {
        m_log.write_log("DialogShapeModel::on_listView_doubleClicked(): read image error!");
        return ;
    }

    get_image_size(m_image,&image_width,&image_height);
    set_part(m_win_id,0,0,image_height,image_width);
    disp_obj(m_image,m_win_id);
}

//============更新列表
void DialogShapeModel::refresh_list()
{
    //刷新list
    standardItemModel->clear();
    int nCount = strList.size();
    for(int i = 0; i < nCount; i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);
        item->setEditable(false);
        standardItemModel->appendRow(item);
    }
    ui->listView->setModel(standardItemModel);

}

//QMessage打印
void DialogShapeModel::print_qmess(QString &content)
{
    QMessageBox msg;
    msg.setWindowTitle("提示");
    msg.setText(content);
    msg.exec();
}

//测试
void DialogShapeModel::test()
{
}

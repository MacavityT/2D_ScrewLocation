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
    this->setWindowTitle("Shape model dialog");
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
           //触发标志复位
           first_trigger=true;
           //连续采集停止
           if(m_image_capture.m_continue)
               ui->pushButtonPicContinue->click();
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
    set_color(m_win_id,"green");
    set_draw(m_win_id,"margin");
    set_line_width(m_win_id,3);
    set_system("clip_region","false");

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
        QString name2="QComboBox";
        if(type_name==name1)
        {
            static_cast<QPushButton*>(wid)->setStyleSheet("background-color:rgb(225,225,225);\
                                                          border-radius:10px;");
        }
        else if(type_name==name2)
        {
            static_cast<QComboBox*>(wid)->setStyleSheet("background-color:rgb(225,225,225);\
                                                        border-radius:10px;");
        }
    }

    return 0;
}

//参数初始化
int DialogShapeModel::start_param_init()
{
    //Image init
    gen_empty_obj(&m_image);
    //field init
    m_fileName = "";
    m_mark_fileName="";
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
        QString pattern("^match-\\d+\\_+\\d+\\.shm$");
        QString mark_pattern("^mark-\\d+\\.shm$");
        QRegExp rx(pattern);
        QRegExp mark_rx(mark_pattern);

        bool res = rx.exactMatch(fileInfo.fileName());
        bool mark_res=mark_rx.exactMatch(fileInfo.fileName());

        if (res||mark_res)
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
    //检测当前状态
    bool status=ui->pushButtonPicOne->isEnabled();
    //首次触发线程
    if(first_trigger)
    {
        //线程控制
        m_image_capture.m_continue=status;
        m_image_capture.param_set(p_cam);
        emit signal_image_capture();
    }
    //控件使能    
    foreach (QAbstractButton* button, ui->ViewControl->buttons()) {
        if(button->objectName()!="pushButtonPicContinue")
        {
            button->setEnabled(!status);//可以写为下一行，更骚一些，但没啥必要
//            static_cast<QPushButton*>(button)->setEnabled(!status);
        }
    }
    ui->pushButton_confirm->setEnabled(!status);
    if(status)
        ui->pushButtonPicContinue->setText(tr("停止采图"));
    else
        ui->pushButtonPicContinue->setText(tr("连续采图"));
}

void DialogShapeModel::slot_transmit_image(Hobject image)
{
    //获取并显示图像，由线程不断触发
    disp_obj(image,m_win_id);
    if(detection_region_show)
    {
        disp_obj(m_detect_region,m_win_id);
    }
    if(detection_cross_show)
    {
        HTuple URow=1944/4;
        HTuple UCol=2592/4;
        disp_cross(m_win_id, ((HTuple(URow).Concat(2*URow)).Concat(3*URow)),\
                  ((HTuple(UCol).Concat(UCol)).Concat(UCol)), 60, 0);
        disp_cross(m_win_id, ((HTuple(URow).Concat(2*URow)).Concat(3*URow)),\
                  ((HTuple(2*UCol).Concat(2*UCol)).Concat(2*UCol)), 60, 0);
        disp_cross(m_win_id, ((HTuple(URow).Concat(2*URow)).Concat(3*URow)),\
                  ((HTuple(3*UCol).Concat(3*UCol)).Concat(3*UCol)), 60, 0);
    }
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
    //Clear window
    clear_window(m_win_id);
    //Show Image
    get_image_size(m_image,&image_width,&image_height);
    disp_obj(m_image,m_win_id);

    file.close();
    ch = nullptr;

    return 0;
}

//按钮：创建检测区域
void DialogShapeModel::on_pushButtonDetectRegion_clicked()
{
    //提示画一个圆圈
    set_color(m_win_id,"green");
    set_draw(m_win_id,"margin");
    set_line_width(m_win_id,3);
    draw_circle(m_win_id,&m_create_row,&m_create_col,&m_create_radius);
    disp_circle(m_win_id,m_create_row,m_create_col,m_create_radius);
    gen_circle(&m_detect_region, m_create_row,m_create_col,m_create_radius);
    //判断文件夹是否存在，不存在则创建
    QDir dir(m_path_exe + "/region/");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    if (false == dir.exists())
    {
        bool is_mkdir = dir.mkdir(m_path_exe + "/region/");
        if (false == is_mkdir)
        {
            print_qmess(QString("创建文件夹失败"));
            clear_window(m_win_id);
            return;
        }
    }
    //保存区域
    QString qdstr = m_path_exe + QString("/region/DetectionRegion.hobj");
    QByteArray ba = qdstr.toLocal8Bit();
    char* ch = ba.data();
    try
    {
        write_region(m_detect_region,ch);
    }
    catch(...)
    {
        print_qmess(QString("保存失败"));
        clear_window(m_win_id);
        return;
    }
    print_qmess(QString("创建成功"));
}

//选择是否在连续采集中显示圆形区域
void DialogShapeModel::on_pushButtonShowRegion_clicked()
{
    QString qdstr = m_path_exe + QString("/region/DetectionRegion.hobj");
    QByteArray ba = qdstr.toLocal8Bit();
    char* ch = ba.data();
    read_region(&m_detect_region,ch);
    //Set flag
    detection_region_show=!detection_region_show;
    if(detection_region_show)
    {
        ui->pushButtonShowRegion->setText(QString("取消显示"));
    }
    else
    {
        ui->pushButtonShowRegion->setText(QString("显示区域"));
    }
}

//显示准心
void DialogShapeModel::on_pushButtonShowCross_clicked()
{
    detection_cross_show=!detection_cross_show;
    if(detection_cross_show)
    {
        ui->pushButtonShowCross->setText(QString("取消显示"));
    }
    else
    {
        ui->pushButtonShowCross->setText(QString("显示准心"));
    }
}

//清空窗口及图像
void DialogShapeModel::on_pushButtonClearWindow_clicked()
{    
    clear_window(m_win_id);
    gen_empty_obj(&m_image);
}

//////模板创建部分
//选择模版对应关系
void DialogShapeModel::on_combo_ShangStd_activated(int index)
{
    screw_num=index;
}

void DialogShapeModel::on_combo_Type_activated(int index)
{
    screw_type=index;
}

void DialogShapeModel::on_combo_Score_activated(const QString &arg1)
{
    if(arg1=="相似度(默认0.5)")
        return;
    QString score=arg1;
    QString screw_index,driver_index;
    driver_index.setNum(screw_type);
    screw_index.setNum(screw_num);
    m_fileName=driver_index+'_'+screw_index;
    m_ini.write("Model_Score",m_fileName,score);
    model_score=score.toDouble();
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

    //开始绘画模板,完成创建后保存按钮使能
    if(0==draw_show())
    {
        m_ini.write("Model_Score",m_fileName,model_score);
        //保存使能
        ui->pushButtonCreateShapeModel->setEnabled(true);
    }
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
    if (0 != save_templa_image(false))
    {
        return -1;
    }
    //保存多螺丝信息
    if(ui->checkBox_DoubleScrew->isChecked())
    {
        m_ini.write("DoubleScrew",m_fileName,1);
    }
    print_qmess(QString("succeed!"));//结果显示
    //刷新list
    strList.append("match-" + m_fileName + ".shm");
    refresh_list();
	ui->pushButtonCreateShapeModel->setEnabled(false);

    return 0;
}

//创建mark点模板
void DialogShapeModel::on_combo_mark_Index_activated(int index)
{
    m_mark_fileName.setNum(index);
}

void DialogShapeModel::on_combo_mark_Score_activated(const QString &arg1)
{
    if(arg1=="相似度(默认0.5)")
        return;
    QString score=arg1;
    m_ini.write("Mark_Model_Score",m_mark_fileName,score);
    mark_model_score=score.toDouble();
}

void DialogShapeModel::on_pushButton_mark_confirm_clicked()
{
    //开始绘画模板,完成创建后保存按钮使能
    if(0==draw_show())
    {
        //更改模板分数
        m_ini.write("Mark_Model_Score",m_mark_fileName,mark_model_score);
        //保存使能
        ui->pushButtonCreateShapeModelMark->setEnabled(true);
    }
}

void DialogShapeModel::on_pushButtonCreateShapeModelMark_clicked()
{
    //判断是否已经为模板命名
    if (m_mark_fileName.isEmpty())
    {
        print_qmess(QString("请选择mark点编号！"));
        return;
    }
    //保存模板及图像
    if (0 != save_templa_image(true))
    {
        return;
    }
    print_qmess(QString("succeed!"));//结果显示
    //刷新list
    strList.append("mark-" + m_mark_fileName + ".shm");
    refresh_list();
    ui->pushButtonCreateShapeModelMark->setEnabled(false);

    return;
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

    //轮廓仿射变换
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
int DialogShapeModel::save_templa_image(bool isMark)
{
	//读取文件夹
    QDir dir1(m_path_exe + "/matchImage/");
    QDir dir2(m_path_exe + "/match/");
    dir1.setFilter(QDir::Files | QDir::NoSymLinks);
    dir2.setFilter(QDir::Files | QDir::NoSymLinks);
    //判断文件夹是否存在，不存在则创建
    bool is_mkdir;
    if (false == dir1.exists())
    {
        is_mkdir= dir1.mkdir(m_path_exe + "/matchImage/");
        if (false == is_mkdir)
        {
            m_log.write_log("DialogShapeModel::save_templa_image(): the folder matchImage mkdir failed!");
            return -2;
        }
    }
    if (false == dir2.exists())
    {
        is_mkdir = dir2.mkdir(m_path_exe + "/matchImage/");
        if (false == is_mkdir)
        {
            m_log.write_log("DialogShapeModel::save_templa_image(): the folder matchImage mkdir failed!");
            return -2;
        }
    }
    //保存模板
    QString qdstr;
    if(isMark)
    {
        qdstr = m_path_exe + QString("/match/mark-" + m_mark_fileName + ".shm");
    }
    else
    {
        qdstr = m_path_exe + QString("/match/match-" + m_fileName + ".shm");
    }
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
    if(isMark)
    {
        qdstr = m_path_exe + QString("/matchImage/" + m_mark_fileName + ".bmp");
    }
    else
    {
        qdstr = m_path_exe + QString("/matchImage/" + m_fileName + ".bmp");
    }
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

//模板删除模块
void DialogShapeModel::deleteFile()
{
    if (index_delete != -1)
    {
        QModelIndex m_index = standardItemModel->index(index_delete, 0);
        //delete model
        QString del_file_name = m_index.data().toString();
        QFile del_f(m_path_exe + "/match/" + del_file_name);
        //delete image
        QString image_name = del_file_name.replace("match-", "").replace(".shm", "");
        QFile del_m(m_path_exe + QString("/matchImage/" + image_name + ".bmp"));

        if (del_f.exists())
            del_f.remove();
        if (del_m.exists())
            del_m.remove();
        print_qmess(QString("delete succeed!"));
        del_f.close();

        QList<QString>::Iterator it = strList.begin(),itend = strList.end();
        for (it;it != itend; it++){
            if (*it == del_file_name)
            {
                strList.erase(it);
            }
        }
        standardItemModel->removeRow(index_delete);
        ui->listView->setModel(standardItemModel);
    }
    index_delete = -1;
    ui->pushButton_delete->setEnabled(false);
    ui->pushButton_Test->setEnabled(false);
}

//列表元素激活
void DialogShapeModel::on_listView_activated(const QModelIndex &index)
{
    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_Test->setEnabled(true);
    index_delete = index.row();
}

//列表元素双击方法，显示保存的模版图片
void DialogShapeModel::on_listView_doubleClicked(const QModelIndex &index)
{
    //find the image name
    index_delete = index.row();
    QModelIndex m_index = standardItemModel->index(index_delete, 0);
    QString template_name = m_index.data().toString();
    QString image_name = template_name.replace("match-", "").replace("mark-","").replace(".shm", "");
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

//按钮：测试
void DialogShapeModel::on_pushButton_Test_clicked()
{
    //判断图片是否为空
    Hlong num;
    count_obj(m_image,&num);
    if(0==num)
    {
        print_qmess(QString("请添加图片"));
        return;
    }
    //文件路径
    HTuple test_modelID;
    QModelIndex m_index = standardItemModel->index(index_delete, 0);
    QString template_name = m_index.data().toString();
    QString template_path = m_path_exe+"/match/"+template_name;
    QByteArray trans=template_path.toLatin1();
    char* test_model_path=trans.data();
    //读取模板
    try
    {
        read_shape_model(test_model_path,&test_modelID);
    }
    catch(...)
    {
        print_qmess(QString("读取模板失败"));
        return;
    }

    ////获取目标模板相似度
    double score;
    //获取批头号及螺丝编号
    if(template_name.contains("match"))
    {
        QString index_name = template_name.replace("match-", "").replace(".shm", "");
        QByteArray trans2=index_name.toLatin1();
        char* split_name=trans2.data();
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

        m_ini.read("Model_Score",screw_driver_index+'_'+screw_index,score);
    }
    else
    {
        QString index_name = template_name.replace("mark-", "").replace(".shm", "");
        m_ini.read("Model_Score",index_name,score);
    }
    if(score==0)
    {
        score=0.5;
    }

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
    read_region(&m_modelRegion,ch1);

    //查找模板
    Hobject image;
    HTuple findRow,findCol,findAngle,findScore;
    double dradRange = HTuple(360).Rad()[0].D();
    try
    {
        reduce_domain(m_image,m_modelRegion,&image);
        find_shape_model(m_image,  test_modelID, 0, dradRange , score, 1, 0.5,
                         "least_squares", 3, 0.9, &findRow, &findCol, &findAngle, &findScore);
    }
    catch(...)
    {
        print_qmess(QString("匹配失败"));
        return;
    }
    if(findRow.Num()!=1)
    {
        print_qmess(QString("匹配失败"));
        return;
    }

    //结果显示
    Hobject Contours;
    HTuple hom_mat_2d;
    //轮廓仿射变换
    get_shape_model_contours (&Contours, test_modelID, 1);
    vector_angle_to_rigid(0, 0, 0, findRow, findCol, findAngle, &hom_mat_2d);
    affine_trans_contour_xld(Contours, &Contours, hom_mat_2d);
    //显示模板轮廓
    set_color(m_win_id, "green");
    set_draw(m_win_id, "margin");
    disp_obj(m_image, m_win_id);
    disp_obj(Contours, m_win_id);
    //显示模板坐标
    disp_message (m_win_id, (("X="+(findCol.Select(0)))+"   Y=")+(findRow.Select(0)),\
                  "image", 40, 40, "green","true");
}

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

    //初始化参数变量配置
    start_param_init();
    //初始化界面设置
    start_ui_init();

    //关联
    connect(ui->pushButtonPicOne,SIGNAL(clicked()), this, SLOT(ClickButtonPicOne()));
    connect(ui->pushButtonCreateShapeModel, SIGNAL(clicked()), this, SLOT(ClickButtonCreateShapeModel()));
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_listView_activated(QModelIndex)));

    refresh_list();
}

DialogShapeModel::~DialogShapeModel()
{
    delete ui;
}

//主从窗口传递相机对象
int DialogShapeModel::cam_init(basler_cam *ptr_cam)
{
    p_cam = ptr_cam;

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

//界面初始化
int DialogShapeModel::start_ui_init()
{
    //hal WinID
    HWND hWnd = (HWND)ui->widget->winId();
    int widgetHeight = ui->widget->height();
    int widgetWidth  = ui->widget->width();
    Hlong m_DlgID = (Hlong)hWnd;

    open_window(0,0,widgetWidth,widgetHeight,m_DlgID,"visible", "",&m_win_id);

    //Show
    try
    {
        read_image(&m_image,"D:\\image\\hongfu\\1\\1.bmp");
    }
    catch (HException &except)
    {
        m_log.write_log("DialogShapeModel::start_ui_init(): read image failed!");
        return -1;
    }

    get_image_size(m_image,&image_width,&image_height);
    set_part(m_win_id,0,0,image_height,image_width);
    disp_obj(m_image,m_win_id);

    //模板列表界面刷新
    refresh_list();

    return 0;
}

//===========加载图片
int DialogShapeModel::ClickButtonPicOne()
{
    QFile file;
    QString fileName;
    char*  ch;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config"), "", tr("Image Files (*.bmp)"));
    //tr("Image Files (*.png);;Image Files (*.bmp);;Image Files (*.jpg);"));
    //(*.png,*bmp,*jpg)
    if (fileName.isEmpty())
    {
        return -1;
    }
    QByteArray ba = fileName.toLocal8Bit();
    ch = ba.data();

    //操作文件==========
    read_image(&m_image, ch);

    //Show Image
    get_image_size(m_image,&image_width,&image_height);
    set_part(m_win_id,0,0,image_height,image_width);
    disp_obj(m_image,m_win_id);

    file.close();
    ch = nullptr;

    return 0;
}

//创建模板
int DialogShapeModel::ClickButtonCreateShapeModel()
{
    //判断是否已经为模板命名
    if (m_fileName.isEmpty())
    {
        print_qmess(QString("请先输入模板名称"));
        return -1;
    }
    //开始绘画模板
    draw_show();
    //保存模板及图像
    if (0 != save_templa_image())
    {
        return -1;
    }

    //刷新list
    strList.append("match-" + m_fileName + ".shm");
    refresh_list();

    print_qmess(QString("succeed!"));

    //清空命名输入框
    ui->lineEdit_name->setText("");
    m_fileName = "";

    return 0;
}

//采集图片
void DialogShapeModel::on_pushButtonSnapOne_clicked()
{
    p_cam->snap(0);

    //获取数据
    gen_image1(&m_image,"byte",\
                  (*p_cam).m_cam_width,(*p_cam).m_cam_height,\
                  (Hlong)(*p_cam).pImageBuffer[0]);

    //Show
    set_part(m_win_id,0,0,(*p_cam).m_cam_height,(*p_cam).m_cam_width);
    disp_obj(m_image,m_win_id);
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

//模板删除按钮
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

//模板命名按钮
void DialogShapeModel::on_pushButton_name_clicked()
{
    m_fileName = ui->lineEdit_name->text();
    if (m_fileName.isEmpty())
    {
        print_qmess(QString("请先输入数字"));
    }
    else
    {
        //转换为Int类型后判断是否相等，若否则非数字命名
        if (m_fileName != QString::number(m_fileName.toInt()))
        {
            print_qmess(QString("请用单个数字命名模板"));
            m_fileName = "";
            ui->lineEdit_name->setText("");
            return ;
        }
        else
        {
            bool search_res = strList.contains("match-" + m_fileName + ".shm");
            if (search_res)
            {
                print_qmess(QString("该命名已存在"));
                m_fileName = "";
                ui->lineEdit_name->setText("");
                return ;
            }

            print_qmess(QString("模板命名成功，请点击\"创建模板\"按钮"));
        }
    }
}

//模板对应关系写入
void DialogShapeModel::on_pushButton_confirm_clicked()
{
    //判断是否选择螺丝及模板对应关系
    if(screw_num*screw_type==0)
    {
        print_qmess(QString("Plese select the screw number and type!"));
        return;
    }
    //写入对应关系
    QString screw_index=screw_num+'0';
    try
    {
        m_ini.write("TemplateIndex","ScrewIndex"+screw_index,screw_type);
    }
    catch(...)
    {
        print_qmess(QString("Save template information failed!"));
        return;
    }
}

//列表元素激活
void DialogShapeModel::on_listView_activated(const QModelIndex &index)
{
    ui->pushButton_delete->setEnabled(true);
    index_delete = index.row();
}

//列表元素双击方法
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

//下拉列表Index（对应模板编号及螺丝编号）
void DialogShapeModel::on_combo_ShangStd_activated(int index)
{
    screw_num=index;
    qDebug()<<"the index ="<<index;
}

void DialogShapeModel::on_combo_Type_activated(int index)
{
    screw_type=index;
}

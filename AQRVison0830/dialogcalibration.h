#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include "halfunc.h"
#include "qfile.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include "QCloseEvent"
#include "cam.h"
#include "inifile.h"
#include "aqlog.h"

using namespace Halcon;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void closeEvent(QCloseEvent * event );

private slots:
    void on_pushButtonSnapOne_clicked();
    void on_pushButtonPicOne_clicked();


    void on_pushButton1_stdw_clicked();

    void on_pushButtonCalibra_clicked();

    void on_pushButton3_stdw_clicked();

    void on_pushButton2_stdw_clicked();

    void on_pushButton4_stdw_clicked();

    void on_pushButton1_stdp_clicked();

    void on_pushButton2_stdp_clicked();

    void on_pushButton3_stdp_clicked();

    void on_pushButton4_stdp_clicked();

    void on_pushButton_StdW_clicked();

    void on_pushButton_Test_clicked();

    void on_pushButton_ShangStd_clicked();

    void on_pushButton_Stdpix_clicked();

public:
    int hal_init();
    int image_take_point(double& resX,double& resY);
    int cam_init(basler_cam* ptr_cam);
    int write_cal_point_data();

public:
    Ui::Dialog *ui;
    QString m_path_exe;
    IniFile m_ini;
    aqlog m_log;

public:
    Hlong m_win_id;
    Hlong image_width,image_height;
    Hobject m_image;
    basler_cam* p_cam;

};

#endif // DIALOG_H

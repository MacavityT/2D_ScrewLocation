#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include "dialogshapemodel.h"
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

    void on_pushButtonCalibra_clicked();

    void on_pushButton_StdW_clicked();

    void on_pushButton_Test_clicked();

    void on_pushButton_ShangStd_clicked();

    void on_pushButton_Stdpix_clicked();

    void on_PointSelector_activated(int index);

    void on_XCoordinate_textChanged();

    void on_YCoordinate_textChanged();

public:
    int hal_init();
    void widget_init();
    void parameter_init();
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
    //标定点选择
    int Calibrate_Point=0;
    double Calibrate_data_X[10];
    double Calibrate_data_Y[10];
};

#endif // DIALOG_H

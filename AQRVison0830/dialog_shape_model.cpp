#include "dialog_shape_model.h"
#include "ui_dialogshapemodel.h"

DialogShapeModel::DialogShapeModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShapeModel)
{
    ui->setupUi(this);
}

DialogShapeModel::~DialogShapeModel()
{
    delete ui;
}

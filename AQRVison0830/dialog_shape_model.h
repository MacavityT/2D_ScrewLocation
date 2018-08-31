#ifndef DIALOG_SHAPE_MODEL_H
#define DIALOG_SHAPE_MODEL_H

#include <QDialog>

namespace Ui {
class DialogShapeModel;
}

class DialogShapeModel : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShapeModel(QWidget *parent = 0);
    ~DialogShapeModel();

private:
    Ui::DialogShapeModel *ui;
};

#endif // DIALOG_SHAPE_MODEL_H

#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H

#define MAX_MODEL 20

#include "halfunc.h"

class process_image
{
public:
    process_image();

    //图像处理
    int calcul(Hobject image,double& res_x,double& res_y);

public:
    Hlong m_ModelID[MAX_MODEL];

};

#endif // PROCESS_IMAGE_H

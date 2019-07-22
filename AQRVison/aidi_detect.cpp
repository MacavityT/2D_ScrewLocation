#include "aidi_detect.h"
#include <QString>
#include <QDebug>
#include <QTime>

AIDI_DETECT::AIDI_DETECT(std::string path){
    // 工程路径
    root_path = path;
    // 模型存储路径
    std::vector<std::string> save_model_path_list;
    save_model_path_list.push_back(root_path + "/model");
    // 模块类型 Location\Detect\Classify
    std::vector<std::string> operator_type_list;
    operator_type_list.push_back("Classify");

    aq::FactoryClientParamWrapper param;
    param.save_model_path_list = save_model_path_list;
    param.operator_type_list = operator_type_list;
    // GPU编号
    param.device_number = 0;
    // 是否使用GPU
    param.use_gpu = false;
    param.use_runtime = false;

    runner = new aq::AidiFactoryRunnerWrapper("391aedab-9d40-11e9-ac29-525400162223");
    runner->set_param(param);
    runner->start();
}

AIDI_DETECT::AIDI_DETECT()
{

}

AIDI_DETECT::~AIDI_DETECT()
{
    runner->release();
    delete runner;
}

bool AIDI_DETECT::test_factory_runner(Hobject Image){
    cv::Mat image = HObject2Mat(Image);
    aq::BatchAidiImage b_image;
    b_image.set_image_list({ image });
    runner->set_test_batch_image(b_image);
    std::vector<std::string> result = runner->get_detect_result();
    BaseDetectResult struct_result;
    struct_result.from_json(result[0]);
    std::string OK="正常";
    std::string NG="不正常";
    if(struct_result.defects[0].type_name==OK)
    {
        return true;
    }
    else if(struct_result.defects[0].type_name==NG)
    {
        return false;
    }
}

void test_aidi(){
    // 工程路径
    std::string root_path = "D:/aidi_benchmark/defect_sample_cloth_spot/";
    // 模型存储路径
    std::vector<std::string> save_model_path_list;
    save_model_path_list.push_back(root_path + "Detect_0/model");
    // 模块类型 Location/Detect/Classify
    std::vector<std::string> operator_type_list;
    operator_type_list.push_back("Segment");

    aq::FactoryClientParamWrapper param;
    param.save_model_path_list = save_model_path_list;
    param.operator_type_list = operator_type_list;
    // GPU编号
    param.device_number = 0;
    // 是否使用GPU
    param.use_gpu = true;
    param.use_runtime = false;


    cv::Mat image = cv::imread(root_path + "Detect_0/source/1.bmp");
    //cv::imshow("", image);
    //cv::waitKey(0);
    aq::AidiImage s_image;
    s_image.from_mat(image);
    //s_image.show(0, "");


    //aq::AIDI factory_client("da3f7c01-59b1-11e9-ae4d-525400396520");
    aq::AIDI* factory_client = new aq::AIDI("f09d27d9-ceb8-11e8-94ef-525400396520");
    factory_client->set_param(param);
    factory_client->initial_test_model();


    s_image.draw_result(factory_client->start_test(s_image));
    s_image.show(0, "");
}

void test_factory_runner_wrapper(){
    aq::AidiFactoryRunnerWrapper client("f09d27d9-ceb8-11e8-94ef-525400396520");
    std::string param;
    param = "{\"device_number\":0,\"use_gpu\":true, \"use_runtime\":false, \"save_model_path_list\":[\"D:/aidi_benchmark/defect_sample_cloth_spot/Detect_0/model\"], \"operator_type_list\":[\"Segment\"]}";
    client.set_param(param.c_str());
    client.start();

    cv::Mat image = cv::imread("D:/aidi_benchmark/defect_sample_cloth_spot/Detect_0/source/1.bmp");
    //cv::imshow("", image);
    //cv::waitKey();
    aq::AidiImage s_image;
    s_image.from_mat(image);
    s_image.show(0, "");

    client.set_test_image(s_image);
    QString Result="";
    char* result = Result.toLocal8Bit().data();
    client.get_detect_result(result);

    //std::cout << (std::string)result << std::endl;
    s_image.show(0, "");
    std::cout << "Finish" << std::endl;
}

//	转换函数
Hobject AIDI_DETECT::Mat2HObject(cv::Mat& image)
{
    Hobject Hobj=Hobject();
    int hgt=image.rows;
    int wid=image.cols;
    int i;
    //	CV_8UC3
    if(image.type() == CV_8UC3)
    {
        std::vector<cv::Mat> imgchannel;
        split(image,imgchannel);
        cv::Mat imgB=imgchannel[0];
        cv::Mat imgG=imgchannel[1];
        cv::Mat imgR=imgchannel[2];
        uchar* dataR=new uchar[hgt*wid];
        uchar* dataG=new uchar[hgt*wid];
        uchar* dataB=new uchar[hgt*wid];
        for(i=0;i<hgt;i++)
        {
            memcpy(dataR+wid*i,imgR.data+imgR.step*i,wid);
            memcpy(dataG+wid*i,imgG.data+imgG.step*i,wid);
            memcpy(dataB+wid*i,imgB.data+imgB.step*i,wid);
        }
        gen_image3(&Hobj,"byte",wid,hgt,(Hlong)dataR,(Hlong)dataG,(Hlong)dataB);
        delete []dataR;
        delete []dataG;
        delete []dataB;
        dataR=NULL;
        dataG=NULL;
        dataB=NULL;
    }
    //	CV_8UCU1
    else if(image.type() == CV_8UC1)
    {
        uchar* data=new uchar[hgt*wid];
        for(i=0;i<hgt;i++)
            memcpy(data+wid*i,image.data+image.step*i,wid);
        gen_image1(&Hobj,"byte",wid,hgt,(Hlong)data);
        delete[] data;
        data=NULL;
    }
    return Hobj;
}

cv::Mat AIDI_DETECT::HObject2Mat(Hobject Hobj)
{
//    QTime time;
//    time.start();
    HTuple htCh=HTuple();
    HTuple cType;
    cv::Mat Image;
    convert_image_type(Hobj,&Hobj,"byte");
    count_channels(Hobj,&htCh);
    if(htCh[0].I()==3)
    {
        Hobject ImagePart1,ImagePart2,ImagePart3;
        decompose3(Hobj,&ImagePart1,&ImagePart2,&ImagePart3);
        rgb3_to_gray(ImagePart1,ImagePart2,ImagePart3,&Hobj);
        count_channels(Hobj,&htCh);
    }
    HTuple wid;
    HTuple hgt;
    int W,H;
    if(htCh[0].I()==1)
    {
        HTuple ptr;
        get_image_pointer1(Hobj,&ptr,&cType,&wid,&hgt);
        W=wid[0].I();
        H=hgt[0].I();
        Image.create(H,W,CV_8UC1);
        uchar* pdata=(uchar*)ptr[0].L();
        memcpy(Image.data,pdata,W*H);
    }
    else if(htCh[0].I()==3)
    {
        HTuple ptrR, ptrG, ptrB;
        get_image_pointer3(Hobj,&ptrR,&ptrG,&ptrB,&cType,&wid,&hgt);
        W=wid[0].I();
        H=hgt[0].I();
        Image.create(H,W,CV_8UC3);
        std::vector<cv::Mat> vecM(3);
        vecM[2].create(H,W,CV_8UC1);
        vecM[1].create(H,W,CV_8UC1);
        vecM[0].create(H,W,CV_8UC1);
        uchar* pr=(uchar*)ptrR[0].L();
        uchar* pg=(uchar*)ptrG[0].L();
        uchar* pb=(uchar*)ptrB[0].L();
        memcpy(vecM[2].data,pr,W*H);
        memcpy(vecM[1].data,pg,W*H);
        memcpy(vecM[0].data,pb,W*H);
        cv::merge(vecM,Image);//这里有问题
    }

//    qDebug()<<"time cost="<<time.elapsed()/1000.0<<"s";
    return Image;
}

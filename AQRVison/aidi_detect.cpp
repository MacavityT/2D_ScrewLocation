#include "opencv2/opencv.hpp"
#include "infer/aidi.h"
#include "infer/aidi_factory_runner_wrapper.h"
#include "infer/aidi_factory_param_wrapper.h"
#include "base_struct.h"

using namespace aq;
using namespace std;
using namespace cv;

void test_factory_runner(){
    // 工程路径
    std::string root_path = "D:/aidi_benchmark/location_sample_mobilephone/Location_0";
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

    aq::AidiFactoryRunnerWrapper runner("f09d27d9-ceb8-11e8-94ef-525400396520");
    runner.set_param(param);
    runner.start();

    cv::Mat image = cv::imread(root_path + "/source/1.bmp");
    aq::BatchAidiImage b_image;
    b_image.set_image_list({ image });
    runner.set_test_batch_image(b_image);
    std::vector<std::string> result = runner.get_detect_result();
    BaseDetectResult struct_result;
    struct_result.from_json(result[0]);
    std::cout << struct_result.defects[0].area << std::endl;

    std::cout << result[0] << std::endl;
    b_image.at(0).draw_result(result[0]);
    b_image.at(0).show(0);

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
    char* result = "";
    client.get_detect_result(result);

    //std::cout << (std::string)result << std::endl;
    s_image.show(0, "");
    std::cout << "Finish" << std::endl;
}

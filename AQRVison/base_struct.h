#include "json/json.h"
#include "opencv2\opencv.hpp"

struct BaseDefect{
	cv::Size2f size;
	cv::Size2f rotate_size;
	float angle = 0.0;
	cv::Point2f center;
	cv::Point tl;// tl for location
	double area = 0;
	int type = -1;
	std::string type_name = "";  // classify class_name
	float score = 0.0;
	std::vector<cv::Point> contours;  // detect result
	std::string rect_index = "";
	double length = 0.0; // defects length

};

struct BaseDetectResult{
	cv::Mat source_image; // source image
	cv::Mat result_image; // render result image, do not render now
	std::vector<BaseDefect> defects; // defect vector
	std::string to_json(){
		Json::Value defects_arr_details;
		for (size_t i = 0; i < defects.size(); i++){
			BaseDefect defect = defects[i];
			Json::Value defect_info;
			defect_info["cx"] = defect.center.x;
			defect_info["cy"] = defect.center.y;
			defect_info["width"] = defect.size.width;
			defect_info["height"] = defect.size.height;
			defect_info["area"] = defect.area;
			defect_info["type"] = defect.type;
			defect_info["type_name"] = defect.type_name;
			defect_info["score"] = defect.score;
			defect_info["lx"] = defect.tl.x;
			defect_info["ly"] = defect.tl.y;
			defect_info["angle"] = defect.angle;
			defect_info["length"] = defect.length;
			defect_info["rect_index"] = defect.rect_index;
			defect_info["rotate_width"] = defect.rotate_size.width;
			defect_info["rotate_height"] = defect.rotate_size.height;

			std::vector<cv::Point> contours(defect.contours);

			Json::Value contour_arr;
			if (contours.size() > 0){
				for (int k = 0; k < contours.size(); k++) {
					Json::Value point;
					point["x"] = contours[k].x;
					point["y"] = contours[k].y;
					contour_arr.append(point);
				}
			}
			else{
				// top left
				Json::Value point_tl;
				point_tl["x"] = defect.tl.x;
				point_tl["y"] = defect.tl.y;
				// bottom left
				Json::Value point_bl;
				point_bl["x"] = defect.tl.x;
				point_bl["y"] = defect.tl.y + defect.size.height;
				// bottom right
				Json::Value point_br;
				point_br["x"] = defect.tl.x + defect.size.width;
				point_br["y"] = defect.tl.y + defect.size.height;
				// top right
				Json::Value point_tr;
				point_tr["x"] = defect.tl.x + defect.size.width;
				point_tr["y"] = defect.tl.y;
				// append
				contour_arr.append(point_tl);
				contour_arr.append(point_bl);
				contour_arr.append(point_br);
				contour_arr.append(point_tr);
			}
			defect_info["contours"] = contour_arr;
			defects_arr_details.append(defect_info);
		}
		std::string json_result = defects_arr_details.toStyledString();
		//            AIDI_BOOST_LOG(debug) << "result serialized to json string";
		return json_result;
	}
	void from_json(std::string json_str){
		Json::Value json_item;
		json_item.clear();
		Json::Reader json_reader;
		json_reader.parse(json_str.c_str(), json_item);
		for (int i = 0; i < json_item.size(); i++){
			BaseDefect defect;
			Json::Value single_defect = json_item[i];
			Json::Value area_json = single_defect["area"];
			Json::Value angle_json = single_defect["angle"];
			Json::Value length_json = single_defect["length"];
			Json::Value cx_json = single_defect["cx"];
			Json::Value cy_json = single_defect["cy"];
			Json::Value height_json = single_defect["height"];
			Json::Value width_json = single_defect["width"];
			Json::Value lx_json = single_defect["lx"];
			Json::Value ly_json = single_defect["ly"];
			Json::Value score_json = single_defect["score"];
			Json::Value type_json = single_defect["type"];
			Json::Value type_name_json = single_defect["type_name"];
			Json::Value contours_json = single_defect["contours"];
			for (int j = 0; j < contours_json.size(); j++){
				Json::Value single_point_json = contours_json[j];
				cv::Point point(single_point_json["x"].asInt(), single_point_json["y"].asInt());
				defect.contours.push_back(point);
			}
			defect.area = area_json.asInt();
			defect.center = cv::Point2f(cx_json.asFloat(), cy_json.asFloat());
			defect.angle = angle_json.asFloat();
			defect.length = length_json.asFloat();
			defect.rotate_size = cv::Size2f(single_defect["rotate_width"].asFloat(), single_defect["rotate_height"].asFloat());
			defect.rect_index = single_defect["rect_index"].asString();
			defect.score = score_json.asFloat();
			defect.size = cv::Size2f(width_json.asFloat(), height_json.asFloat());
			defect.tl = cv::Point(lx_json.asInt(), ly_json.asInt());
			defect.type = type_json.asInt();
			defect.type_name = type_name_json.asString();
			defects.push_back(defect);
		}

	}
};
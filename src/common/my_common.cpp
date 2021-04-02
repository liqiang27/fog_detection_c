/*
 * @Descripttion: Some public tools function.
 * @version: 
 * @Author: Lstron
 * @Date: 2021-03-28 17:00:37
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-31 15:28:03
 */

#include "my_common.h"

std::string createID(const int cam_id) {
    time_t timer;
    struct tm y2k = {0};
    double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 2000; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time(&timer);  /* get current time; same as: timer = time(NULL)  */

    seconds = difftime(timer,mktime(&y2k));
    std::string img_id = std::to_string((long)seconds) + "_" + std::to_string(cam_id);
    return img_id;
}

cv::Mat char2Mat(char* modelImage) {
	std::string str2(modelImage, IMAGE_SIZE);
	std::vector<char> vec_data1(str2.c_str(), str2.c_str() + str2.size());
	cv::Mat dst21 = cv::imdecode(vec_data1, CV_LOAD_IMAGE_UNCHANGED);
	return dst21;
}

int getFilenames(const std::string& dir, std::vector<std::string>& filenames)
{
    namespace fs = boost::filesystem;
	fs::path path(dir);
	if (!fs::exists(path))
	{
		return -1;
	}
    fs::directory_iterator end_iter;
	for (fs::directory_iterator iter(path); iter!=end_iter; ++iter)
	{
		if (fs::is_regular_file(iter->status()))
		{
			filenames.push_back(iter->path().string());
		}

		if (fs::is_directory(iter->status()))
		{
			get_filenames(iter->path().string(), filenames);
		}
	}

	return filenames.size();
}
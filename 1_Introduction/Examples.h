//
// Created by cjdcoy on 3/1/19.
//

#ifndef OPENCV_PRACTICE_EXAMPLES_H
#define OPENCV_PRACTICE_EXAMPLES_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
using namespace std;

class Examples {
    public:
        string _imagePath = "../data/jlh.jpg";
        string _videoPath = "../data/gwp.mp4";
        cv::Mat _image = cv::imread(_imagePath, -1);

    private:
};

#endif //OPENCV_PRACTICE_EXAMPLES_H

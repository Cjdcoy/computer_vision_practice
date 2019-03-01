//
// Created by cjdcoy on 3/1/19.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>

//g++ Example3_video_gui.cpp -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab -lopencv_highgui -lopencv_core -o example3
using namespace std;

int main(int argc, char** argv ) {
    cv::Mat img_rgb, img_gry, img_cny;
    cv::namedWindow( "Example Gray",  cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "Example Canny", cv::WINDOW_AUTOSIZE );
    img_rgb = cv::imread(argv[1]);
    cv::resize(img_rgb, img_rgb, cv::Size(img_rgb.cols * 0.5, img_rgb.rows * 0.5));
    cv::imshow("Example Rgb", img_rgb);
    cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);
    cv::imshow("Example Gray", img_gry);
    cv::Canny(img_gry, img_cny, 10, 100, 3, true);
    cv::imshow("Example Canny", img_cny);
    cv::waitKey(0);
    return 0;
}
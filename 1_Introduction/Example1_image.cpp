#include <opencv2/opencv.hpp>
#include <iostream>

//g++ Example1_image.cpp -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab -lopencv_highgui -lopencv_core -o example1

int main(int ac,char **av)
{
  cv::Mat img = cv::imread(av[1], -1);
    cv::resize(img, img, cv::Size(img.cols * 0.5, img.rows * 0.5));

    if (img.empty())
      return -1;
  cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
  cv::imshow("Example1", img);
  cv::waitKey(0);
  cv::destroyWindow("Example1");
  return 0;
}

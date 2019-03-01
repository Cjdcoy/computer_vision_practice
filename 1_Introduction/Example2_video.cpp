#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>

//g++ Example2_video.cpp -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab -lopencv_highgui -lopencv_core -o example2
using namespace std;

int main(int ac,char **av)
{
  cv::namedWindow( "Example2", cv::WINDOW_AUTOSIZE );
  cv::VideoCapture cap;
  cap.open(av[1]);
  cv::Mat frame;
  for(;;) {
    cap >> frame;

    if(frame.empty())
        break;             // Ran out of film
    cv::imshow("Example2", frame);
    if(cv::waitKey(1) >= 0)
        break;
  }
  return 0;
}

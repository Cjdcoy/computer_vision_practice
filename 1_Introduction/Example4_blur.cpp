//
// Created by cjdcoy on 3/1/19.
//
#include <opencv2/opencv.hpp>


//g++ Example4_blur.cpp -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab -lopencv_highgui -lopencv_core -o example4


void example4(cv::Mat &image) { // Create some windows to show the input
    cv::resize(image, image, cv::Size(image.cols * 0.5, image.rows * 0.5));
// and output images in.A Simple Transformation | 31
    cv::namedWindow( "Example4in", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "Example4out", cv::WINDOW_AUTOSIZE );
 //Create a window to show our input image
    cv::imshow( "Example4in", image );
 //Create an image to hold the smoothed output
    cv::Mat out;
 //Do the smoothing ( Note: Could use GaussianBlur(), blur(), medianBlur() or bilateralFilter(). )

    cv::GaussianBlur(image, out, cv::Size(5,5), 3, 3);
    cv::GaussianBlur(out, out, cv::Size(5,5), 3, 3);
 //Show the smoothed image in the output window

    cv::imshow( "Example4out", out );
//Wait for the user to hit a key, windows will self destruct

    cv::waitKey( 0 );
    cv::destroyWindow("Example4out");
    cv::destroyWindow("Example4in");
}

int main(int ac,char **av)
{
    cv::Mat img = cv::imread(av[1], -1);
    if (img.empty())
        return -1;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    example4(img);
    return 0;
}

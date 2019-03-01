//
// Created by cjdcoy on 3/1/19.
//

#include "Examples.h"
using namespace std;

void example_1(Examples &ex) {
    cv::Mat img = cv::imread(ex.imagePath, -1);
    if (img.empty())
        return ;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");
}

void example_2(Examples &ex) {
    cv::namedWindow( "Example2", cv::WINDOW_AUTOSIZE );
    cv::VideoCapture cap;
    cap.open(ex.videoPath);
    cv::Mat frame;
    for(;;) {
        cap >> frame;

        if(frame.empty())
            break;             // Ran out of film
        cv::imshow("Example2", frame);
        if(cv::waitKey(5) >= 0)
            break;
    }
    cv::destroyWindow("Example2");
}

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start out in single step mode
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *) {
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    if(!g_dontset)
        g_run = 1;
    g_dontset = 0;
}

void example_3(Examples &ex) {
    cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE );
    g_cap.open(ex.videoPath);
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Video has " << frames << " frames of dimensions("
         << tmpw << ", " << tmph << ")." << endl;
    cv::createTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlide);
    cv::Mat frame;
    for(;;) {
        if( g_run != 0 ) {
            g_cap >> frame;
            if(frame.empty())
                break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            cv::setTrackbarPos("Position", "Example3", current_pos);
            cv::imshow( "Example3", frame );
            g_run-=1;
        }
        char c = (char)cv::waitKey(5);
        if( c == 's' ) {// single step
            g_run = 1;
            cout << "Single step, run = " << g_run << endl;
        }
        if( c == 'r' ) {//run mode
            g_run = -1;
            cout << "Run mode, run = " << g_run <<endl;
        }
        if( c == 27 )
            break;
    }
    cv::destroyWindow("Example3");
}

int main(int ac, char **av) {
    Examples ex;

    example_1(ex);
    example_2(ex);
    example_3(ex);
    return 0;
}
//
// Created by cjdcoy on 3/1/19.
//

#include "Examples.h"
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

//g++ Examples.cpp -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video -lopencv_videostab -lopencv_highgui -lopencv_core -o examples

void example_1(Examples &ex) {
    cv::Mat img = cv::imread(ex._imagePath, -1);
    cv::resize(img, img, cv::Size(img.cols * 0.5, img.rows * 0.5));
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
    cap.open(ex._videoPath);
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
    g_cap.open(ex._videoPath);
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

void example_4(Examples &ex) { // Create some windows to show the input
    cv::resize(ex._image, ex._image, cv::Size(ex._image.cols * 0.5, ex._image.rows * 0.5));
// and output images in.A Simple Transformation | 31
    cv::namedWindow( "Example4in", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "Example4out", cv::WINDOW_AUTOSIZE );
    //Create a window to show our input image
    cv::imshow( "Example4in", ex._image );
    //Create an image to hold the smoothed output
    cv::Mat out;
    //Do the smoothing ( Note: Could use GaussianBlur(), blur(), medianBlur() or bilateralFilter(). )

    cv::GaussianBlur(ex._image, out, cv::Size(5,5), 3, 3);
    cv::GaussianBlur(out, out, cv::Size(5,5), 3, 3);
    //Show the smoothed image in the output window

    cv::imshow( "Example4out", out );
//Wait for the user to hit a key, windows will self destruct

    cv::waitKey( 0 );
    cv::destroyWindow("Example4out");
    cv::destroyWindow("Example4in");
}

int example_5() { // Create some windows to show the input
    int pid, status;

    if (pid = fork()) {
        waitpid(pid, &status, 0); // wait for the child to exit
    } else {
        const char executable[] = "./lkdemo";
        execl(executable, executable, NULL);
    }
    return status;
}


int main(int ac, char **av) {
    Examples ex;

    example_1(ex);
    example_2(ex);
    example_3(ex);
    example_4(ex);
    example_5();
    return 0;
}
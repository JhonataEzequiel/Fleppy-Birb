#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "Deteccao.h"
#include <iostream>

using namespace std; using namespace cv;

int main()
{
    VideoCapture capture;
    Mat frame, image;

    capture.open(0);

    if(capture.isOpened())
    {
        cout << "Detecçao de Face iniciada....\n" << endl;
        while(1)
        {
            capture >> frame;

            if(frame.empty())
                break;

            Mat frame1 = frame.clone();

            DetectarFace F1;

            F1.DetectarEDesenhar(frame1);

            char c = (char)waitKey(10);

            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }else{
        cout << "Falha ao abrir a Camera\n" << endl;
        return 1;
    }

    return 0;
}


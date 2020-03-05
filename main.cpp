#include <iostream>
#include <opencv2/opencv.hpp>
#include <exception>
#include "Exceptions.h"

using namespace std; using namespace cv;

void ShowMainMenu()
{
    namedWindow("Menu", WINDOW_AUTOSIZE);
    Mat MainMenu = imread("Imagens/Menu.jpg");
    imshow("Menu", MainMenu);
    waitKey(2);
}

const char* isCapOpened(VideoCapture cap)
{
    if(!cap.isOpened())
    {
        throw CustomizedException("ERROR trying to open the capture");
    }else{
        return "Capture is opened\n";
    }
}

int main()
{
    int op;
    VideoCapture cap;
    cap.open(0);

    try{
        cout << isCapOpened(cap) << endl;
    }
    catch(CustomizedException e)
    {
        cerr << e.what() << endl;
    }
    catch(...)
    {
        cerr << "Unexpected Error\n" << endl;
    }
    ShowMainMenu();
    cin >> op;
    while(op != 2)
    {
        if(op == 1)
        {
            //jogar
            Mat Pipes = imread("Imagens/Pipes.jpg");
            namedWindow("Pipes and Stuff", WINDOW_AUTOSIZE);
            for(;;)
            {
                imshow("Pipes and Stuff", Pipes);
                waitKey(20);
                break;
            }
        }
        else if(op == 2)
        {
            break;
        }else{
            break;
        }
    }

    cap.release();

    return 0;
}

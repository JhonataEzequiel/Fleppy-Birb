#ifndef DETECCAO_H
#define DETECCAO_H

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std; using namespace cv;

class DetectarFace
{
    CascadeClassifier cascade, nestedCascade;
    double scale;
    string folder, cascadeName, nestedCascadeName;
public:
    DetectarFace();
    void DetectarEDesenhar(Mat& img);
};

#endif // DETECCAO_H

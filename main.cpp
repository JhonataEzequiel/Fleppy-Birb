#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std; using namespace cv;
/*Função para detectar a face e mostrar*/
void detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale );

/*Esses cascades, pelo que entendi, são arquivos de machine learning treinados para detectar certas coisas, como olhos e faces*/
string cascadeName, nestedCascadeName; //essas string vão apenas auxiliar a organizar o código
//a declaração de Cascades não é por string, e sim "CascadeClassifier"

int main()
{
    VideoCapture capture; //Captura de vídeo
    Mat frame, image; //Arquivos que vão armazenar um frame/imagem

    CascadeClassifier cascade, nestedCascade; //Declaração dos cascades
    double scale=1;

    string folder = "C:/opencv/source/data/haarcascades/"; //Aqui coloque o diretório que o a pasta data/haarcascades está instalada
    cascadeName = folder + "haarcascade_frontalface_alt.xml";
    nestedCascadeName = folder + "haarcascade_eye_tree_eyeglasses.xml";

    //aqui ele está carregando o arquivo do Cascade, que está no diretório data/haarcascades na pasta do opencv

    if (!nestedCascade.load(samples::findFileOrKeep(nestedCascadeName)))
        cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
    if (!cascade.load(samples::findFile(cascadeName)))
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }

    capture.open(0); //Zero = abrir pela webcam
    //se quiser que o Capture receba um vídeo diferente, especifique o diretório
    //se estiver no diretório do projeto, não precisa especificar, coloque apenas "nomeDoVideo.mp4"

    if(capture.isOpened())//Somente continua se tiver sucesso em abrir a Webcam
    {
        cout << "Detecçao de Face iniciada....\n" << endl;
        while(1)
        {
            capture >> frame;

            if(frame.empty()) //Verifica se o frame não está vazio
                break;

            Mat frame1 = frame.clone();

            detectAndDraw(frame1, cascade, nestedCascade, scale);

            char c = (char)waitKey(10);

            if( c == 27 || c == 'q' || c == 'Q' )  //ao pressionar Q ou q, a janela fechará
                break;
        }
    }else{
        cout << "Falha ao abrir a Camera\n" << endl;
        return 1;
    }

    return 0;
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale)
{
    static int frames = 0;
    double t = 0;
    vector<Rect> faces, faces2; //Rect é um template para retângulos
    const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    };
    Mat gray, smallImg;

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    t = (double)getTickCount();
    cascade.detectMultiScale( smallImg, faces,
        1.2, 2, 0
        |CASCADE_SCALE_IMAGE,
        Size(30, 30) );

    frames++;

    t = (double)getTickCount() - t;

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        printf( "[%3d, %3d]\n", r.x, r.y);
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;

        rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                   Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                   color, 3, 8, 0);

        if( nestedCascade.empty() )
            continue;

        smallImgROI = smallImg( r );

        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
            1.1, 2, 0
            |CASCADE_SCALE_IMAGE,
            Size(30, 30) );

        for ( size_t j = 0; j < nestedObjects.size(); j++ )
        {
            Rect nr = nestedObjects[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
            radius = cvRound((nr.width + nr.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
    }

    // mostra a imagem processada com detecção
    imshow( "result", img );
}


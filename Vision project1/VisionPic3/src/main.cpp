/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

// includes
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>    // ise pow


// using namespaces
using namespace std;
using namespace cv;


// function declatations
void displayImage(std::string figureText, cv::Mat img);
//void drawHistogram(cv::Mat anImage );
Mat paintHist(Mat img, int hist_w, int hist_h);
void adaptiveMedFilter(Mat src, Mat &dst, int maxSize, float quantile);
void printVector(string aMessage, vector<double> aVector);
void contraHarmonic(Mat src, Mat &dst, double Q);


int main()
{
    // Load image
    std::string filename = "../data/Image3.png";
    cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

    if (img.empty()) {
        std::cout << "Input image not found at '" << filename << "'\n";
        return 1;
    }


    // display image
    displayImage("Original Image", img);


    // Draw histogram
    cv::Mat uniform(img,Rect(1000,1500,500,300));
    Mat uniformHist = paintHist(uniform, 1500, 512);
    displayImage("UniformHist", uniformHist);
    //imwrite( "../data/UniformHist1.png", uniformHist );


    // remove the uniform/gausian noise
    /* using Gausian Blur*/
    Mat gBlur5;

    GaussianBlur( img, gBlur5, Size(5,5),0);
    displayImage("Med Blur5", gBlur5);
    //imwrite( "../data/GausianBlur5.png", gBlur5 );



    // Draw histogram blur
    cv::Mat uniform1(gBlur5,Rect(1000,1500,500,300));
    uniformHist = paintHist(uniform1, 1500, 512);
    displayImage("UniformHistBlur7", uniformHist);
    //imwrite( "../data/UniformHistB7.png", uniformHist );


    // equalize image
    Mat equImg;
    equalizeHist(gBlur5, equImg);
    displayImage("Eqialized", equImg);
    //imwrite( "../data/EqualisedBlur5.png", equImg );


    cv::waitKey();
    return 0;
}


// function definition
void displayImage(std::string figureText, cv::Mat img){
    cv::namedWindow(figureText ,CV_WINDOW_NORMAL);
    cv::resizeWindow(figureText, 600,600);
    cv::imshow(figureText, img);

}



Mat paintHist(Mat img, int hist_w, int hist_h){ // Plot the histogram

    Mat theHistogram;

    int channels[] = {0};               //number og color channels
    int histSize[] = {256};             //number of histogam colombs
    float range[] = { 0, 256 };         //input range (color values)
    const float* ranges[] = { range };  //pointer to input gange

    calcHist( &img, 1, channels, Mat(), theHistogram, 1, histSize, ranges, true, false);

    int bin_w = cvRound( (double) hist_w/theHistogram.rows );                   //calculate colum width
    Mat histImage( hist_h, bin_w*theHistogram.rows, CV_8UC3, Scalar( 0,0,0) );  // initialize image

    // Normalize histogram values to be within image height
    normalize(theHistogram, theHistogram, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 0; i < theHistogram.rows; i++ ){                             //For each histogram colum
        for(int x = 0; x < bin_w ;x++){                                         //for each vertical pixel in the colum
            for(int y = hist_h-1 ;y> hist_h-theHistogram.at<float>(i)+1;y--){       //for each horizontal pixel in the colum
                histImage.at<Vec3b>(Point(i*bin_w+x,y))[0] = 255;               //Make pixel white
                histImage.at<Vec3b>(Point(i*bin_w+x,y))[1] = 255;
                histImage.at<Vec3b>(Point(i*bin_w+x,y))[2] = 255;
            }
        }
    }
    // add borders to the histogram
    const int border = 10;
    copyMakeBorder(histImage, histImage, border, border, border,
                   border, BORDER_CONSTANT, Scalar(50,50,50));

    return histImage;

}















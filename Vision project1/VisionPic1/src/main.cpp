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
Mat paintHist(Mat img, int hist_w, int hist_h);
void adaptiveMedFilter(Mat src, Mat &dst, int maxSize, float quantile);



int main()
{
    // Load image
    std::string filename = "../data/Image1.png";
    cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);

    if (img.empty()) {
        std::cout << "Input image not found at '" << filename << "'\n";
        return 1;
    }


    // display image
    //displayImage("Original Image", img);
    imwrite( "../data/Image1Hist.png", paintHist(img, 1500, 512) );


    // Estimation of noise parameters
    Mat Orig;
    cvtColor(img, Orig, cv::COLOR_GRAY2RGB);
    rectangle(Orig, Point(1000,1500), Point(1500,1800), Scalar(0,0,255), 10, 8, 0);
    imwrite( "../data/Image1UniformArea.png", Orig );

    Mat uniform(img,Rect(1000,1500,500,300));
    imwrite( "../data/Image1UniformHist.png", paintHist(uniform, 1500, 512) );
    //displayImage("Uniform Area", paintHist(uniform, 1500, 512));


    // Remove the unipolar pepper noise
    Mat AmF;
    adaptiveMedFilter(img, AmF, 7, 0.8);
    //displayImage("Removed Pepper Noise", dst);
    imwrite( "../data/Image1AdaptiveMedFilter7.png", AmF );

    // New noise parameters
    Mat uniform1(AmF,Rect(1000,1500,500,300));
    imwrite( "../data/Image1UniformHist7.png", paintHist(uniform1, 1500, 512));
    //displayImage("Uniform Area", paintHist(uniform1, 1500, 512));

    // equalize image
    Mat equImg;

    equalizeHist(AmF, equImg);
    displayImage("Eqialized", equImg);
    imwrite( "../data/Equalised.png", equImg );


    waitKey();
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

void adaptiveMedFilter(Mat src, Mat &dst, int maxSize, float quantile){
    // setup
    Mat Image;
    Mat Ret;
    // add borders to the image
    int border = maxSize/2;
    src.copyTo(Image);

    cv::copyMakeBorder(Image,Image,border,border,border,border,cv::BORDER_REPLICATE);
    Image.copyTo(Ret);

    // for each pixel:
    Mat localDomain;
    int size = 3;
    std::vector<double> vecFromMat;
    for(int x = border; x<Image.rows-border; x++){
        for(int y = border; y<Image.cols-border; y++){

            size = 3;
            while (size <= maxSize){
                // sort the elements
                vecFromMat.clear();
                for(int s = x-(border); s <= x+(border); s++){
                    for(int t = y - (border ); t <= y + (border); t++){
                        uchar color = Image.at<uchar>(s, t);
                        vecFromMat.push_back( (double)color);
                    }
                }

                std::sort( vecFromMat.begin(), vecFromMat.end() );          // sort vecFromMat


                int q = (int)floor(size*size*quantile);
                if ((uchar)vecFromMat[q] != (uchar)vecFromMat[0] || size == maxSize){
                    Ret.at<uchar>(Point(y,x)) = (uchar)vecFromMat[q];
                    size = maxSize +1;
                }

                size += 2;

            }
        }
    }


    // remove the border
    cv::Mat Noborder(Ret,Rect(border,border,Image.cols-2*border,Image.rows-2*border));
    dst = Noborder;
}


















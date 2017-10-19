/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

// includes
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

// using namespaces
using namespace std;
using namespace cv;


// function declatations
void displayImage(std::string figureText, cv::Mat img);
void drawHistogram(cv::Mat anImage );
Mat paintHist(Mat img, int hist_w, int hist_h);


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

    // draw histogram
    //Mat hist = paintHist(img, 512, 512);
    //displayImage("Histogram", hist);

    // draw histogram of expected uniform area
    cv::Mat uniform(img,Rect(1000,1500,500,300));
    displayImage("Uniform Area", paintHist(uniform, 1500, 512));

    // remove the pepper noise

    // remove the other noise


    return 0;
}


// function definition
void displayImage(std::string figureText, cv::Mat img){
    cv::namedWindow("image",CV_WINDOW_NORMAL);
    cv::resizeWindow("image", 600,600);
    cv::imshow("image", img);
    cv::waitKey();
}



Mat paintHist(Mat img, int hist_w, int hist_h){ // Plot the histogram

    Mat theHistogram;

    int channels[] = {0};               //number og color channels
    int histSize[] = {256};             //number of histogam colombs
    float range[] = { 0, 256 };         //input range (color values)
    const float* ranges[] = { range };  //pointer to input gange

    calcHist( &img, 1, channels, Mat(), theHistogram, 1, histSize, ranges, true, false);

    int bin_w = cvRound( (double) hist_w/theHistogram.rows );                   //calculate colum width
    Mat histImage( hist_h, bin_w*theHistogram.rows, CV_8UC3, Scalar( 0,0,0) );                   // initialize image


    // Normalize histogram values to be within image height
    normalize(theHistogram, theHistogram, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    cout << "bin_w*theHistogram.rows" << bin_w*theHistogram.rows << endl;
    cout << theHistogram << endl;

    for( int i = 0; i < theHistogram.rows-1; i++ ){                             //For each histogram colum
        for(int x = 0; x < bin_w ;x++){                                         //for each vertical pixel in the colum
            for(int y = hist_h ;y> hist_h-theHistogram.at<float>(i);y--){       //for each horizontal pixel in the colum
                histImage.at<Vec3b>(Point(i*bin_w+x,y))[0] = 255;               //Make pixel white
                histImage.at<Vec3b>(Point(i*bin_w+x,y))[1] = 255;
                histImage.at<Vec3b>(Point(i*bin_w+x,y))[2] = 255;
            }
        }
    }

    // add borders to the histogram
    Mat histImage2;
    copyMakeBorder(histImage, histImage2, cvRound(hist_w*0.02), cvRound(hist_w*0.02), cvRound(hist_w*0.1),
                   cvRound(hist_w*0.1), BORDER_CONSTANT, Scalar(50,50,50));

    return histImage2;
}



















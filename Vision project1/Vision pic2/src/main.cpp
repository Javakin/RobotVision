/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat paintHist(Mat img, int hist_w, int hist_h){ // Plot the histogram

    Mat theHistogram;

    int channels[] = {0};               //number og color channels
    int histSize[] = {256};             //number of histogam colombs
    float range[] = { 0, 256 };         //input range (color values)
    const float* ranges[] = { range };  //pointer to input gange

    calcHist( &img, 1, channels, Mat(), theHistogram, 1, histSize, ranges, true, false);

    int bin_w = cvRound( (double) hist_w/theHistogram.rows );                   //calculate colum width
    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );                   // initialize image

    // Normalize histogram values to be within image height
    normalize(theHistogram, theHistogram, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 0; i < theHistogram.rows-1; i++ ){                             //For each histogram colum
        for(int x = 0; x < bin_w ;x++){                                         //for each vertical pixel in the colum
            for(int y = hist_h ;y> hist_h-theHistogram.at<float>(i);y--){       //for each horizontal pixel in the colum
                histImage.at<uint8_t>(Point(i*bin_w+x,y)) = 255;                //Make pixel white
            }
        }
    }
    return histImage;
}

int main(int argc, char* argv[])
{
    // Parse command line arguments
    cv::CommandLineParser parser(argc, argv,
        "{help   |            | print this message}"
        "{@image | ../../Image2.png | image path}"
    );

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    // Load image
    std::string filename = parser.get<std::string>("@image");
    cv::Mat img = cv::imread(filename);

    if (img.empty()) {
        std::cout << "Input image not found at '" << filename << "'\n";
        return 1;
    }
    cv::Mat imgGray;
    cvtColor(img,imgGray,CV_BGR2GRAY);
    cv::Mat hist = paintHist(imgGray,512,512);
    cv::imshow("Original",imgGray);
    cv::imshow("histogram",hist);

    cv::Mat fix1;
    medianBlur(imgGray,fix1,9);
    cv::imshow("fix1",fix1);

    Mat eqImg;
    equalizeHist( fix1, eqImg );
    cv::imshow("equilised",eqImg);



    /*// Task 4 -------------- Filtering using 2d filtering_______________________________________________________________________
    Mat kernel = (Mat_<float>(3,3) <<    0.1, 0.1, 0.1,
                                         0.1, 0.2, 0.1,
                                         0.1, 0.1, 0.1);
    Mat imgFiltered;
    //Mat kernel = Mat::ones( 3, 3, CV_32F )/ (float)(9);
    filter2D(imgGray, imgFiltered, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT);

    calcHist( &imgFiltered, 1, channels, Mat(),hist, 1, histSize, ranges,true, false);
    Mat hist3 = paintHist(hist, 400, 400);
    cv::imshow("filtered",imgFiltered);
    cv::imshow("filtered Hist",hist3);*/

    // Task 5 -------------- Filtering using 2d filtering_______________________________________________________________________

    cv::waitKey();

    return 0;
}

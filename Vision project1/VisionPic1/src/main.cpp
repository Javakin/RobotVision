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

// using namespaces
using namespace std;
using namespace cv;


// function declatations
void displayImage(std::string figureText, cv::Mat img);
//void drawHistogram(cv::Mat anImage );
Mat paintHist(Mat img, int hist_w, int hist_h);
void adaptiveMedFilter(Mat src, Mat &dst, int maxSize, float quantile);
void printVector(string aMessage, vector<double> aVector);


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


    // Estimation of noise parameters
    // Draw histogram of expected uniform area
    //cv::Mat uniform(img,Rect(1000,1500,500,300));
    //displayImage("Uniform Area", paintHist(uniform, 1500, 512));

    // remove the unipolar pepper noise
    Mat dst;
    adaptiveMedFilter(img, dst, 14, 0.8);
    displayImage("Removed Pepper Noise", dst);

    // remove the raylight noise


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

void adaptiveMedFilter(Mat src, Mat &dst, int maxSize, float quantile){
    // setup
    Mat Image;
    Mat Ret;
    // add borders to the image
    int border = 14;
    src.copyTo(Image);

    cv::copyMakeBorder(Image,Image,border,border,border,border,cv::BORDER_REPLICATE);
    Image.copyTo(Ret);

    // for each pixel:
    Mat localDomain;
    int size = 3;
    std::vector<double> vecFromMat;
    int q = (int)floor(size*size*quantile);
    for(int x = border; x<Image.cols-border; x++){
        for(int y = border; y<Image.rows-border; y++){


        // sort the elements
        // source:https://stackoverflow.com/questions/30078756/super-fast-median-of-matrix-in-opencv-as-fast-as-matlab
        Mat window(Image,Rect(x-size/2, y-size/2,size,size));    // select a specific local domain

        window.copyTo(localDomain);
        localDomain = localDomain.reshape(0,1);                     // spread Input Mat to single row

        localDomain.copyTo(vecFromMat);                             // Copy Input Mat to vector vecFromMat

        std::sort( vecFromMat.begin(), vecFromMat.end() );          // sort vecFromMat

        // select the quantile and insert in image
        Ret.at<uchar>(Point(x,y)) = (uchar)vecFromMat[q];




        }
    }

    displayImage("w borders", Ret);
    // remove the border
    cv::Mat Noborder(Ret,Rect(border,border,Image.cols-2*border,Image.rows-2*border));
    dst = Noborder;
}

void printVector(string aMessage, vector<double> aVector){
    cout << aMessage << endl;
    for(unsigned int i = 0; i<aVector.size(); i++){
        cout << aVector[i] << " ";
    }
    cout << endl;
}















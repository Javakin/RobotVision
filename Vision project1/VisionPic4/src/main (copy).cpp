/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

vector<int> X;
vector<int> Y;
int posX=0,posY=0;
void onMouse(int event, int x, int y, int flags, void* param)
{
	int held = 0;
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        held = 1;
    }
    else if (event == CV_EVENT_LBUTTONUP)
    {
        held = 0;
    }
    
    if (held){
		cout << "X = " << x <<", Y = " << y << endl;
		X.push_back(x);
		Y.push_back(y);
		posX = x;
		posY =y;
	}
}

void displayImage(cv::Mat img){
    cv::namedWindow("image",CV_WINDOW_NORMAL);
    cv::resizeWindow("image", 600,600);
	setMouseCallback("image", onMouse, 0);
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
    Mat histImage( hist_h, bin_w*theHistogram.rows, CV_8UC3, Scalar( 0,0,0) );  // initialize image

    // Normalize histogram values to be within image height
    normalize(theHistogram, theHistogram, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

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
    const int border = 10;
    copyMakeBorder(histImage, histImage, border, border, border,
                  border, BORDER_CONSTANT, Scalar(50,50,50));
	
    return histImage;
}



void dftshift(cv::Mat& mag){
    int cx = mag.cols / 2;
    int cy = mag.rows / 2;

    cv::Mat tmp;
    cv::Mat q0(mag, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(mag, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(mag, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(mag, cv::Rect(cx, cy, cx, cy));

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

void create_butterworth_lowpass_filter(Mat &dft_Filter, int D, int n, int W)
{
    Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

    Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
    double radius;

    // based on the forumla in the IP notes (p. 130 of 2009/10 version)
    // see also HIPR2 on-line

    for (int i = 0; i < dft_Filter.rows; i++)
    {
        for (int j = 0; j < dft_Filter.cols; j++)
        {
            radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));

            // Butterworth low pass:
            // tmp.at<float>(i,j) = (float)
            //                        ( 1 / (1 + pow((double) (radius /  D), (double) (2 * n))));

            // Butterworth band reject, page 244, paragraph 5.4.1, Gonzalez Woods, "Digital Image Processing 2nd Edition"
            // D(u,v) -> radius
            // D_0 -> D
            tmp.at<float>(i, j) = (float)
                                  ( 1 / (1 + pow((double) (radius * W) / ( pow((double)radius, 2) - D * D ), (double) (2 * n))));
        }
    }

    Mat toMerge[] = {tmp, tmp};
    merge(toMerge, 2, dft_Filter);
}
cv::Mat bhpf(float d0, int n, cv::Size size)
{
    cv::Mat_<cv::Vec2f> hpf(size);
    cv::Point2f c = cv::Point2f(size) / 2;

    for (int i = 0; i < size.height; ++i) {
        for (int j = 0; j < size.width; ++j) {
            // Distance from point (i,j) to the origin of the Fourier transform
            float d = std::sqrt((i - c.y) * (i - c.y) + (j - c.x) * (j - c.x));

            // Real part
            if (std::abs(d) < 1.e-9f) // Avoid division by zero
                hpf(i, j)[0] = 0;
            else {
                hpf(i, j)[0] = 1 / (1 + std::pow(d0 / d, 2 * n));
            }

            // Imaginary part
            hpf(i, j)[1] = 0;
        }
    }

    return hpf;
}
//![end]

// Returns a complex Butterworth low-pass filter of order 'n', diameter 'd0'
// and size 'size'.
//![blpf]
cv::Mat blpf(float d0, int n, cv::Size size)
{
    cv::Mat_<cv::Vec2f> lpf(size);
    cv::Point2f c = cv::Point2f(size) / 2;

    for (int i = 0; i < size.height; ++i) {
        for (int j = 0; j < size.width; ++j) {
            // Distance from point (i,j) to the origin of the Fourier transform
            float d = std::sqrt((i - c.y) * (i - c.y) + (j - c.x) * (j - c.x));

            // Real part
            lpf(i, j)[0] = 1 / (1 + std::pow(d / d0, 2 * n));

            // Imaginary part
            lpf(i, j)[1] = 0;
        }
    }

    return lpf;
}

void notch_filter(Mat src,int x, int y, int radius){
	int dist;
	for(int x1 = x-radius; x1<= x+radius; x1++){
		for(int y1 = y-radius; y1<= y+radius; y1++){
			dist = sqrt(pow(x1-x,2)+pow(y1-y,2));
			if(dist<radius){
				src.at<Vec2f>(Point(x1,y1))[0] = 0.0;
			}
		}
	}
}

void displayMagPlot(Mat complexI){
	//Mat planes[2] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	
}
int main(int argc, char* argv[])
{
    cv::CommandLineParser parser(argc, argv,
        "{help   |            | print this message}"
        "{@image | ../../Image4_2.png | image path}"
    );

    if (parser.has("help")) {
        parser.printMessage();
    }

    // Load image
    std::string filename = parser.get<std::string>("@image");
    cv::Mat I = cv::imread(filename, cv::IMREAD_GRAYSCALE);

    if (I.empty()) {
        std::cout << "Input image not found at '" << filename << "'\n";
    }
   
    displayImage(I);
	Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix
	dftshift(complexI); 
	Mat filter = blpf(320,5,complexI.size());
	cv::mulSpectrums(complexI, filter, complexI, 0);
	dftshift(complexI); 
	
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    dftshift(magI); 

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a

	displayImage(magI);
	//complexI[0]= magI;
    //calculating the idft
    cv::Mat inverseTransform;
    cv::dft(complexI, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
    normalize(inverseTransform, inverseTransform, 0, 1, CV_MINMAX);
    
    cv::Mat done(inverseTransform, cv::Rect(0,0,inverseTransform.cols-10,inverseTransform.rows-83));
	displayImage(done);

    return 0;
}

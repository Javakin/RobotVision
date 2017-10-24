/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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


uchar medianCalc(Mat src, int Xin, int Yin, int size,int MaxSize = 14){
    vector<uchar> itemList;
    uchar color;


    for(int x = -(size/2); x<(size/2)+1;x++){
        int y = 0;
        for(int y = -(size/2); y<(size/2)+1;y++){
            color = src.at<uchar>(Point(x+Xin,y+Yin));
            if(color < 255 && color>0){
                itemList.push_back(color);
            }
        }
    }
    if(itemList.size()==0){
        if(size <MaxSize)
            itemList.push_back(medianCalc(src,Xin,Yin,size+2));
        else
            itemList.push_back(color);
    }
    std::sort(itemList.begin(),itemList.end());
    return itemList.at(itemList.size()/2);
}

uchar AverageCalc(Mat src, int Xin, int Yin, int size,int MaxSize = 14){
    vector<uchar> itemList;
    uchar color;
	
	uchar colorPoint;

    for(int x = -(size/2); x<(size/2)+1;x++){
        for(int y = -(size/2); y<(size/2)+1;y++){
            color = src.at<uchar>(Point(x+Xin,y+Yin));
            if(color != 255 && color != 0){
                itemList.push_back(color);
            }
        }
    }
    if(itemList.size()==0){
        if(size <MaxSize)
            itemList.push_back(AverageCalc(src,Xin,Yin,size+2));
        else
            itemList.push_back(color);
    }
    int sum = 0;
    for(int i = 0; i<itemList.size();i++){ 
		sum+=itemList.at(i);
	}
    return sum/(itemList.size()+1);
}

void saltPepperFilter(Mat src, Mat &dst,int size, int border = 14){
    Mat Image;
    src.copyTo(Image);
    cv::copyMakeBorder(Image,Image,border,border,border,border,cv::BORDER_REPLICATE);
    for(int x = border; x<Image.cols-border; x++){
        for(int y = border; y<Image.rows-border; y++){
            if(Image.at<uchar>(Point(x,y)) == 0 || Image.at<uchar>(Point(x,y)) == 255)
                Image.at<uchar>(Point(x,y)) = medianCalc(Image,x,y,size,border);
        }
    }
    cv::Mat Noborder(Image,Rect(border,border,Image.cols-2*border,Image.rows-2*border));
    dst = Noborder;
}

void saltPepperAvgFilter(Mat src, Mat &dst,int size, int border = 14){
    Mat Image;
    src.copyTo(Image);
    cv::copyMakeBorder(Image,Image,border,border,border,border,cv::BORDER_REPLICATE);
    for(int x = border; x<Image.cols-border; x++){
        for(int y = border; y<Image.rows-border; y++){
            //if(Image.at<uchar>(Point(x,y)) == 0 || Image.at<uchar>(Point(x,y)) == 255)
				Image.at<uchar>(Point(x,y)) = AverageCalc(Image,x,y,size,border);
        }
    }
    cv::Mat Noborder(Image,Rect(border,border,Image.cols-2*border,Image.rows-2*border));
    dst = Noborder;
}

int main(int argc, char* argv[])
{
    // Parse command line arguments
    cv::CommandLineParser parser(argc, argv,
        "{help   |           | print this message}"
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

    // convert to GrayScale
    cv::Mat imgGray;
    cvtColor(img,imgGray,CV_BGR2GRAY);

    // Make histogram
	displayImage("hist",paintHist(imgGray,512,512));

    //FIX 2
	cv::Mat fix2;
	saltPepperFilter(imgGray,fix2,3);
    //displayImage("fix2",fix2);

	
    //FIX 2.1
    cv::Mat fix2_1;
    cv::Mat Rectangle(fix2,Rect(1000,1500,500,300));
    displayImage("retangle",Rectangle);
    displayImage("hist",paintHist(Rectangle,512,512));
	
    GaussianBlur(fix2,fix2_1,Size(5,5),0 ,0);
    displayImage("Gausian filtered",fix2_1);

    cv::Mat Rectangle2_1(fix2_1,Rect(1000,1500,500,300));
    displayImage("retangle",Rectangle2_1);
    displayImage("hist",paintHist(Rectangle2_1,512,512));

    return 0;
}
 //FIX 1 apply median filter
    /*cv::Mat fix1;
    medianBlur(imgGray,fix1,9);
    resize(fix1,disp,Size(),0.25,0.25,CV_INTER_AREA);
    cv::imshow("fix1",disp);*/
	
	//saltPepperAvgFilter(imgGray,fix2,7);
	
	  //This code was used to determin the gausian filter size
    /*for(int i = 1; i<20;i+=2){
        GaussianBlur(fix2,fix2_1,Size(i,i),0 ,0);
        displayImage("Gausian filtered",fix2_1);
    }*/
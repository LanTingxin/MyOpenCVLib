#include "function.h"

//#include <opencv2/core/core.hpp>
//#include <opencv2/opencv.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/highgui/highgui.hpp>
//#include <iostream>


//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"") 

using namespace cv;
//using namespace std;
#define WINDOW_0 "原图" 
#define WINDOW_1 "椒盐噪声点1"  
#define WINDOW_2 "椒盐噪声点2" 
#define Saltnum 25000

void salt(Mat&);
int SaltNoise_main()
{
	Mat image = imread("1.jpg");
	if (image.empty())
	{
		std::cout << "The image can't be loaded!";
		return 0;
	}
	imshow(WINDOW_0, image);
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);
	salt(image);
	imshow(WINDOW_1, image);
	salt(gray);
	imshow(WINDOW_2, gray);

	waitKey();
	return 0;
}

void salt(Mat&dst)
{
	int x, y;
	for (int i = 0; i < Saltnum; ++i)
	{
		x = rand() % dst.cols;	//有意思
		y = rand() % dst.rows;	//有意思
		if (dst.channels() == 1)
		{
			dst.at<uchar>(y, x) = 255;
		}
		if (dst.channels() == 3)
		{
			dst.at<Vec3b>(y, x)[0] = 255;
			dst.at<Vec3b>(y, x)[1] = 255;
			dst.at<Vec3b>(y, x)[2] = 255;
		}
	}
}

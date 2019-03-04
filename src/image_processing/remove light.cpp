#include<opencv2/opencv.hpp>
//#include "utils/MultipleImageWindow.h"

using namespace std;
using namespace cv;


Mat removeLight(Mat img, Mat pattern, int method);
Mat calculateLightPattern(Mat img);
void ConnectedComponents(Mat img);
static Scalar randomColor(RNG& rng);
void ConnectedComponentsStats(Mat img);
void FindContoursBasic(Mat img);

int RemoveLight_main()
{
	Mat prospect, pattern, gy_result, tmp_prospect, b_result;
	namedWindow("Pattern", CV_WINDOW_AUTOSIZE);
	moveWindow("Pattern", 10, 10);
	namedWindow("Gray-Result", CV_WINDOW_AUTOSIZE);
	moveWindow("Gray-Result", 600, 10);
	namedWindow("Bin-Result", CV_WINDOW_AUTOSIZE);
	moveWindow("Bin-Result", 10, 400);
	//miw = new MultipleImageWindow("Main window", 3, 2, WINDOW_AUTOSIZE);

	VideoCapture capture("videos/rect.mp4");//T_model//triangle//testvideo//
	if (!capture.isOpened())
		return -1;

	while (1)
	{
		capture >> tmp_prospect;
		if (tmp_prospect.empty())
			break;

		cvtColor(tmp_prospect, prospect, COLOR_BGR2GRAY);
		pattern = calculateLightPattern(prospect);
		imshow("Pattern", pattern);

		gy_result = removeLight(prospect, pattern, 0);
		imshow("Gray-Result", gy_result);
		medianBlur(gy_result, gy_result, 7);

		threshold(gy_result, b_result, 30, 255, THRESH_BINARY);
		imshow("Bin-Result", b_result);

		ConnectedComponents(b_result);
		if (waitKey(30) == 'c')
			break;
	}
	capture.release();
	destroyAllWindows();
	waitKey();
	return 0;
}

Mat removeLight(Mat img, Mat pattern, int method)
{
	Mat aux;
	//如果方法是归一化
	if (method == 1)
	{
		//相除时需要将图像更改为32位浮点
		Mat img32, pattern32;
		img.convertTo(img32, CV_32F);
		//图像除以模式
		aux = 1 - (img32 / pattern32);
		//对其进行缩放以转换为8位格式
		aux = aux * 255;
		aux.convertTo(aux, CV_8U);
	}
	else
	{
		aux = pattern - img;
	}
	return aux;
}

Mat calculateLightPattern(Mat img)
{
	Mat pattern;
	blur(img, pattern, Size(img.cols / 3, img.cols / 3));
	return pattern;
}

void ConnectedComponents(Mat img)
{
	Mat labels;
	int num_objects = connectedComponents(img, labels);
	if (num_objects < 2)
	{
		cout << "No objects detected" << endl;
		return;
	}
	else
		cout << "Number of objects detected:" << num_objects - 1 << endl;
	Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
	RNG rng(0xFFFFFFFF);
	for (int i = 1; i < num_objects; ++i)
	{
		Mat mask = labels == i;
		output.setTo(randomColor(rng), mask);
	}
	imshow("Result", output);
}

void ConnectedComponentsStats(Mat img)
{
	// Use connected components with stats
	Mat labels, stats, centroids;
	int num_objects = connectedComponentsWithStats(img, labels, stats, centroids);
	// Check the number of objects detected
	if (num_objects < 2) {
		cout << "No objects detected" << endl;
		return;
	}
	else {
		cout << "Number of objects detected: " << num_objects - 1 << endl;
	}
	// Create output image coloring the objects and show area
	Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
	RNG rng(0xFFFFFFFF);
	for (int i = 1; i<num_objects; i++) {
		cout << "Object " << i << " with pos: " << centroids.at<Point2d>(i) << " with area " << stats.at<int>(i, CC_STAT_AREA) << endl;
		Mat mask = labels == i;
		output.setTo(randomColor(rng), mask);
		// draw text with area
		stringstream ss;
		ss << "area: " << stats.at<int>(i, CC_STAT_AREA);

		putText(output,
			ss.str(),
			centroids.at<Point2d>(i),
			FONT_HERSHEY_SIMPLEX,
			0.4,
			Scalar(255, 255, 255));
	}
	imshow("Result", output);
	//miw->addImage("Result", output);
}

static Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

void FindContoursBasic(Mat img)
{
	vector<vector<Point> > contours;
	findContours(img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
	// Check the number of objects detected
	if (contours.size() == 0) {
		cout << "No objects detected" << endl;
		return;
	}
	else {
		cout << "Number of objects detected: " << contours.size() << endl;
	}
	RNG rng(0xFFFFFFFF);
	for (int i = 0; i<contours.size(); i++)
		drawContours(output, contours, i, randomColor(rng));
	imshow("Result", output);
	//miw->addImage("Result", output);
}
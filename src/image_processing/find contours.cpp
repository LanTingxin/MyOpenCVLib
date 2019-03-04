#include "function.h"

Mat srcGray;
int max_thresh = 255;
int thresh = 100;
RNG rng(12345);

//鼠标回调事件
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//用canny算子检测边缘
	Canny(srcGray, canny_output, thresh, thresh * 2, 3);
	//寻找轮廓
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//绘出轮廓
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//随机颜色绘制轮廓
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	//显示轮廓结果
	namedWindow("Contours", CV_WINDOW_NORMAL);
	imshow("Contours", drawing);
}
int FindContours_main()
{
	Mat srcImage = imread(img_path_elephant);
	if (!srcImage.data)
		return -1;
	cvtColor(srcImage, srcGray, COLOR_BGR2GRAY);
	blur(srcGray, srcGray, Size(3, 3));
	//创建窗体
	//char* source_window = "srcImage";
	namedWindow("srcImage", CV_WINDOW_NORMAL);
	imshow("srcImage", srcImage);
	//滑动条控制Canny阈值
	createTrackbar(" thresh:", "srcImage", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey(0);
	return 0;

}
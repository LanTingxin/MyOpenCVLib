#include "function.h"

Mat srcGray;
int max_thresh = 255;
int thresh = 100;
RNG rng(12345);

//���ص��¼�
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//��canny���Ӽ���Ե
	Canny(srcGray, canny_output, thresh, thresh * 2, 3);
	//Ѱ������
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//�������
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//�����ɫ��������
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	//��ʾ�������
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
	//��������
	//char* source_window = "srcImage";
	namedWindow("srcImage", CV_WINDOW_NORMAL);
	imshow("srcImage", srcImage);
	//����������Canny��ֵ
	createTrackbar(" thresh:", "srcImage", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);
	waitKey(0);
	return 0;

}
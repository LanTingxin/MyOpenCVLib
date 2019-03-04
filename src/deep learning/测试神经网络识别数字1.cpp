#include <io.h>
#include <string>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\ml.hpp>
using namespace cv;
using namespace ml;
//����ѵ����ɵ�������ģ�ͽ���ʶ��
int main()
{
	//������ͼƬ��Сͳһת��Ϊ8*16
	const int imageRows = 8;
	const int imageCols = 16;
	//��ȡѵ�����
	Ptr<ANN_MLP> model = StatModel::load<ANN_MLP>("F:/MLPModel.xml");
	////==========================Ԥ�ⲿ��==============================////
	//��ȡ����ͼ��
	Mat test, dst;
	test = imread("F:/2.png", 0);
	if (test.empty())
	{
		std::cout << "can not load image \n" << std::endl;
		return -1;
	}
	//������ͼ��ת��Ϊ1*128������
	resize(test, test, Size(imageRows, imageCols), (0, 0), (0, 0), INTER_AREA);
	threshold(test, test, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	Mat_<float> testMat(1, imageRows*imageCols);
	for (int i = 0; i < imageRows*imageCols; i++)
	{
		testMat.at<float>(0, i) = (float)test.at<uchar>(i / 8, i % 8);
	}
	//ʹ��ѵ���õ�MLP modelԤ�����ͼ��
	model->predict(testMat, dst);
	std::cout << "testMat: \n" << testMat << "\n" << std::endl;
	std::cout << "dst: \n" << dst << "\n" << std::endl;
	double maxVal = 0;
	Point maxLoc;
	minMaxLoc(dst, NULL, &maxVal, NULL, &maxLoc);
	std::cout << "���Խ����" << maxLoc.x << "���Ŷ�:" << maxVal * 100 << "%" << std::endl;
	imshow("test", test);
	waitKey(0);
	return 0;
}
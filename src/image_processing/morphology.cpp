#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
using namespace cv;

int Morphology_main()
{
	Mat srcImage = imread("test.png");
	imshow("��ԭʼͼ��",srcImage);
	Mat dstImage1,dstImage2, dstImage3, dstImage4, dstImage5, dstImage6, dstImage7;

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(srcImage, dstImage1, MORPH_DILATE, element);
	morphologyEx(srcImage, dstImage2, MORPH_ERODE, element);
	morphologyEx(srcImage, dstImage3, MORPH_OPEN, element);
	morphologyEx(srcImage, dstImage4, MORPH_CLOSE, element);
	morphologyEx(srcImage, dstImage5, MORPH_GRADIENT, element);
	morphologyEx(srcImage, dstImage6, MORPH_TOPHAT, element);
	morphologyEx(srcImage, dstImage7, MORPH_BLACKHAT, element);

	imshow("��Ч��ͼ_���͡�", dstImage1);
	imshow("��Ч��ͼ_��ʴ��", dstImage2);
	imshow("��Ч��ͼ_�����㡿", dstImage3);
	imshow("��Ч��ͼ_�����㡿", dstImage4);
	imshow("��Ч��ͼ_�ݶ����㡿", dstImage5);
	imshow("��Ч��ͼ_��ñ���㡿", dstImage6);
	imshow("��Ч��ͼ_��ñ���㡿", dstImage7);

	if (waitKey() == 27)
		return 0;

}
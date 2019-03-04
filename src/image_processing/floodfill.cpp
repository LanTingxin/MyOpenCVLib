
//--------------------------------------������˵����-------------------------------------------
//		����˵������OpenCV3������š�OpenCV3���鱾����ʾ������49
//		������������ˮ���floodFill�����÷�ʾ��
//		�����������ò���ϵͳ�� Windows 7 64bit
//		������������IDE�汾��Visual Studio 2010
//		������������OpenCV�汾��	3.0 beta
//		2014��11�� Created by @ǳī_ë����
//		2014��12�� Revised by @ǳī_ë����
//------------------------------------------------------------------------------------------------


//---------------------------------��ͷ�ļ��������ռ�������֡�----------------------------
//		����������������ʹ�õ�ͷ�ļ��������ռ�
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;



//-----------------------------------��main( )������--------------------------------------------  
//      ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//----------------------------------------------------------------------------------------------- 
int FloodFill_main()
{
	Mat temp = imread("test2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat src;
	resize(temp, src, Size(800, 600));
	imshow("��ԭʼͼ��", src);
	Rect ccomp;
	floodFill(src, Point(50, 300), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("��Ч��ͼ��", src);
	waitKey(0);
	return 0;
}
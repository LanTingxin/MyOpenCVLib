#include "function.h"

using namespace std;
using namespace cv;

int main()
{
	//-----------------picture processing-----------------------

	//FeatureDetector_main();	//2D特征检测
	//AdaptiveContrastEnhancement_main();	//自适应对比度增强
	//ImageTraversing_main();	//14种遍历图像方法
	//minAreaRect_main();		//最小外包矩形
	//minEnclosingCircle_main();	//最小外接圆形
	//TemplateMatching_main();		//模板匹配法
	//HistogramComputation_main();	//计算直方图
	//GrabCut_main();		//grabcut图像分割
	//SaltNoise_main();			//椒盐噪声
	//FindContours_main();	//轮廓查找
	//FloodFill_main();		//漫水填充法
	//RemoveLight_main();		//光纹去除背景	
	//Morphology_main();		//形态学处理

	//-----------------video processing-------------------------

	//MOG2_main();	//混合高斯模型实现背景建模
	//CamShift_main();	//CamShift目标跟踪
	//FarnebackOpticalFlow_main();	//Farneback光流法
	//OpenTracker_main();		//开源跟踪算法
	//PointTracking_main();		//点追踪
	//OpticalFlow_main();		//光流法
	//FaceDetector_main();		//人脸检测
	//ERROR!FaceDetectorMask_main();	//人脸检测并覆盖面具

	//---------------------------machine learning------------------------

	K_Means_main();		//K-means聚类分析法

	//-----------------------others-------------------------------

	//MouseOperator_main();		//鼠标操作


	waitKey();
	return 0;
}
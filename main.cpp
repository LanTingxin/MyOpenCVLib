#include "function.h"

using namespace std;
using namespace cv;

int main()
{
	//-----------------picture processing-----------------------

	//FeatureDetector_main();	//2D�������
	//AdaptiveContrastEnhancement_main();	//����Ӧ�Աȶ���ǿ
	//ImageTraversing_main();	//14�ֱ���ͼ�񷽷�
	//minAreaRect_main();		//��С�������
	//minEnclosingCircle_main();	//��С���Բ��
	//TemplateMatching_main();		//ģ��ƥ�䷨
	//HistogramComputation_main();	//����ֱ��ͼ
	//GrabCut_main();		//grabcutͼ��ָ�
	//SaltNoise_main();			//��������
	//FindContours_main();	//��������
	//FloodFill_main();		//��ˮ��䷨
	//RemoveLight_main();		//����ȥ������	
	//Morphology_main();		//��̬ѧ����

	//-----------------video processing-------------------------

	//MOG2_main();	//��ϸ�˹ģ��ʵ�ֱ�����ģ
	//CamShift_main();	//CamShiftĿ�����
	//FarnebackOpticalFlow_main();	//Farneback������
	//OpenTracker_main();		//��Դ�����㷨
	//PointTracking_main();		//��׷��
	//OpticalFlow_main();		//������
	//FaceDetector_main();		//�������
	//ERROR!FaceDetectorMask_main();	//������Ⲣ�������

	//---------------------------machine learning------------------------

	K_Means_main();		//K-means���������

	//-----------------------others-------------------------------

	//MouseOperator_main();		//������


	waitKey();
	return 0;
}
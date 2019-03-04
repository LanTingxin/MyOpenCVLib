//参考1：基于“局部标准差”的图像增强（原理、算法、代码）
//http://www.cnblogs.com/jsxyhelu/p/4857721.html
//参考2：使用局部标准差实现图像的局部对比度增强算法。
//http://www.cnblogs.com/Imageshop/p/3324282.html

#include "function.h"


//点乘法,elementWiseMultiplication
Mat matrixWiseMulti(Mat &m1, Mat &m2) {
	Mat dst = m1.mul(m2);//注意是对应矩阵位置的元素相乘
	return dst;
}
//ACE算法原理：
//ACE算法原理表达式：f(i,j)=Mx(i,j)+G(i,j)*[x(i,j)-Mx(i,j)]
//高频成分：x(i,j)-Mx(i,j)，x(i,j)表示当前中心像素，Mx(i,j)表示局部平均值
//增益系数：G(i,j)，可以直接令其为系数C（一般总是大于1）
//

//图像局部对比度增强算法
//float MaxCG:对高频成分的最大增益值
//int n：局部半径
//int C；对高频的直接增益系数
//Mat src：原图像
Mat ACE(Mat &src, int C = 3, int n = 3, float MaxCG = 7.5) {
	int rows = src.rows;
	int cols = src.cols;

	Mat meanLocal;
	Mat varLocal;
	Mat meanGlobal;
	Mat varGlobal;

	blur(src.clone(), meanLocal, Size(n, n));//meanMask为图像局部均值 
	imshow("低通滤波", meanLocal);
	Mat highFreq = src - meanLocal;//高频成分：x(i,j)-Mx(i,j)
	imshow("高频成分", highFreq);

	varLocal = matrixWiseMulti(highFreq, highFreq);
	blur(varLocal, varLocal, Size(n, n));    //varMask为此时为图像局部方差   
											 //换算成局部标准差（开根号）
	varLocal.convertTo(varLocal, CV_32F);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			varLocal.at<float>(i, j) = (float)sqrt(varLocal.at<float>(i, j));
		}
	}
	meanStdDev(src, meanGlobal, varGlobal); //meanGlobal为全局均值 varGlobal为全局标准差，实际均是一个数
	Mat gainArr = 0.5 * meanGlobal / varLocal;//增益系数矩阵：G(i,j)，可以直接令其为系数C（一般总是大于1）
											  /*
											  for (int i = 0; i < rows; i++){
											  for (int j = 0; j < cols; j++)
											  cout<<gainArr.at<float>(i, j)<<" " ;
											  cout << endl;
											  if (i == 1)
											  break;
											  }*/

											  //对增益矩阵进行截止
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (gainArr.at<float>(i, j) > MaxCG) {
				gainArr.at<float>(i, j) = MaxCG;
			}
		}
	}
	gainArr.convertTo(gainArr, CV_8U);
	gainArr = matrixWiseMulti(gainArr, highFreq);
	Mat dst1 = meanLocal + gainArr;
	imshow("Lee改进的D方法", dst1);
	Mat dst2 = meanLocal + C * highFreq;//直接利用系数C进行高频成分放大
	imshow("直接系数C方法", dst2);
	return dst2;
}


Mat myACE(Mat &src, int n = 7, float MaxCG = 7.5) {
	int rows = src.rows;
	int cols = src.cols;
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar::all(0));

	if (src.type() == CV_8UC1)
		int aa = src.type();
	Mat meanLocal;
	Mat varLocal;
	Mat meanGlobal;
	Mat varGlobal;

	blur(src.clone(), meanLocal, Size(n, n));//meanMask为图像局部均值 
	Mat highFreq = src - meanLocal;//高频成分：x(i,j)-Mx(i,j)

	varLocal = matrixWiseMulti(highFreq, highFreq);
	blur(varLocal, varLocal, Size(n, n));    //varMask为此时为图像局部方差   
											 //换算成局部标准差（开根号）
	varLocal.convertTo(varLocal, CV_32F);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			varLocal.at<float>(i, j) = (float)sqrt(varLocal.at<float>(i, j));
		}
	}
	meanStdDev(src, meanGlobal, varGlobal); //meanGlobal为全局均值 varGlobal为全局标准差，实际均是一个数
	Mat gainArr = 0.5 * meanGlobal / varLocal;//增益系数矩阵：G(i,j)，可以直接令其为系数C（一般总是大于1）
											  //对增益矩阵进行截止
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (gainArr.at<float>(i, j) > MaxCG) {
				gainArr.at<float>(i, j) = MaxCG;
			}
		}
	}
	gainArr.convertTo(gainArr, CV_8U);
	gainArr = matrixWiseMulti(gainArr, highFreq);
	dst = meanLocal + gainArr;
	//imshow("Lee改进的D方法", dst);
	return dst;
}

//示例
void AdaptiveContrastEnhancement_main()
{

	Mat src = imread(img_path_gakki, 0);
	imshow("src", src);
	int n = 100;

	float MaxCG = 10.5;
	Mat dst = myACE(src, n, MaxCG);
	imshow("myACE", dst);

	waitKey();
}
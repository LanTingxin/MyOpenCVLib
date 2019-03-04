#include "function.h"

//二值化并置背景为黑色
Mat binarize(Mat input)
{
	//Uses otsu to threshold the input image
	Mat binaryImage;
	cvtColor(input, input, CV_BGR2GRAY);
	threshold(input, binaryImage, 0, 255, THRESH_OTSU);

	//Count the number of black and white pixels
	int white = countNonZero(binaryImage);
	int black = binaryImage.size().area() - white;

	//If the image is mostly white (white background), invert it
	return white < black ? binaryImage : ~binaryImage;
}


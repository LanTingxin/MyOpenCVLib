// Example 12-3. Using GrabCut for background removal

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using std::cout;
using std::cerr;
using std::endl;
using namespace cv;

Mat img_preview;
Mat img;
Mat markers;
Mat drawRect;
int x_0 = -1;
int y_0 = -1;
int x_1, y_1;
int drawr = 0;

bool finished;

void displayResult() {
	int rows = img.rows;
	int cols = img.cols;
	Vec3b blackClr(0, 0, 0);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (markers.at<uchar>(i, j) != GC_FGD && markers.at<uchar>(i, j) != GC_PR_FGD) {
				img.at<Vec3b>(i, j) = blackClr;
				//img.at<Vec3b>(i, j)[0] = 0;
				//img.at<Vec3b>(i, j)[1] = 0;
				//img.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}
	imshow("image", img);
	finished = true;
}

static void onMouseClick(int event, int x, int y, int, void*) {
	if (finished) {
		return;
	}

	if (event == EVENT_LBUTTONDOWN && drawr == 0) {
		if (x_0 < 0) {
			x_0 = x;
			y_0 = y;
			ellipse(markers, Point(x, y), Size(1, 1),
				0, 0, 360, GC_FGD, 3);
			ellipse(drawRect, Point(x, y), Size(1, 1),
				0, 0, 360, Scalar(0, 0, 255), 3);
			drawr = 1;
		}

		addWeighted(img, 0.7, drawRect, 0.3, 0, img_preview);

		imshow("image", img_preview);
		return;
	}
	if (event == EVENT_LBUTTONUP) {
		drawr = 2;
	}
	if (drawr == 1) { //Just moving
		drawRect.setTo(0);
		rectangle(drawRect, Point(x_0, y_0), Point(x, y), Scalar(0, 0, 255), -1);

		addWeighted(img, 0.7, drawRect, 0.3, 0, img_preview);
		x_1 = x; y_1 = y;
		imshow("image", img_preview);
		return;
	}

	if (drawr == 2) {
		Mat bg;
		Mat fg;
		rectangle(markers, Point(x_0, y_0), Point(x_1, y_1), GC_PR_FGD, -1);
		grabCut(img, markers, Rect(0, 0, img.cols - 1, img.rows - 1),
			bg, fg, 5, GC_EVAL);
		displayResult();
		return;
	}
}

void help(char** argv) {
	cout << "\nExample 12-3. Using GrabCut for background removal"
		<< "\n- Use left mouse to drag a rectangle over the object"
		<< "\n- On release of left mouse button, we will perform GrabCut"
		<< "\n- Press any key to terminate program"
		<< "\nUsage: "
		<< argv[0] << " <path/imagename>\n"
		<< "\nExample:\n" << argv[0] << " ../stuff.jpg\n" << endl;
}


int GrabCut_main(){
	//help(argv);
	//if (argc != 2) {
	//	return -1;
	//}
	Mat temp = imread("test5.jpg");
	resize(temp, img, Size(800, 600));
	//img = imread("test.png", CV_LOAD_IMAGE_COLOR);
	if (img.channels() != 3) {
		cerr << "Input image should have 3 channels" << endl;
		exit(1);
	}

	markers = Mat(img.size(), CV_8UC1);
	markers.setTo(GC_PR_BGD);

	img_preview = img.clone();
	drawRect = img.clone();

	finished = false;

	namedWindow("image", WINDOW_AUTOSIZE);
	setMouseCallback("image", onMouseClick, 0);

	imshow("image", img_preview);

	waitKey(0);

	return 0;
}

#include "function.h"
#include <ctype.h>

//#include <opencv2/video/tracking.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>

Mat image;
bool backprojMode = false;//��ʾ�Ƿ���뷴��ͶӰģʽ��true��ʾ���뷴��ͶӰģʽ
bool selectObject = false;//ѡ��Ҫ���ٵĳ�ʼĿ�꣬true�������������ѡ��
int trackObject = 0;//����Ŀ���������
bool showHist = true;//�Ƿ���ʾֱ��ͼ
Point origin;  //�������ѡ���һ�ε���ʱ���λ��
Rect selection; //���ڱ���ѡ��ľ��ο�
int vmin = 10, vmax = 256, smin = 30;

void onMouse(int event, int x, int y, int, void*)
{
	if (selectObject) //ͨ������������ȥѡ���������
	{
		selection.x = MIN(x, origin.x);//���ζ�������
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);//���ο�
		selection.height = std::abs(y - origin.y);//���θ�

		selection &= Rect(0, 0, image.cols, image.rows);
	}
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x, y); //�յ��ʱ�ĵ�
		selection = Rect(x, y, 0, 0);
		selectObject = true; //���������ѡ��
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false; //���ֹͣѡ��
		if (selection.width > 0 && selection.height > 0)
			trackObject = -1;
		break;
	}
}

void help()
{
	cout << "\nThis is a demo that shows mean-shift based tracking\n"
		"You select a color objects such as your face and it tracks it.\n"
		"This reads from video camera (0 by default, or the camera number the user enters\n"
		"Usage: \n"
		"    ./camshiftdemo [camera number]\n";

	cout << "\n\nHot keys: \n"
		"\tESC - quit the program\n"
		"\tc - stop the tracking\n"
		"\tb - switch to/from backprojection view\n"
		"\th - show/hide object histogram\n"
		"\tp - pause video\n"
		"To initialize tracking, select the object with mouse\n";
}


int CamShift_main()
{
	help();
	VideoCapture cap; //����һ������ͷ��׽�������
	Rect trackWindow;
	RotatedRect trackBox; //����һ����ת�ľ��������
	int hsize = 16;
	float hranges[] = { 0, 180 };
	const float* phranges = hranges;

	cap.open(0);//ֱ�ӵ��ó�Ա����������ͷ

	if (!cap.isOpened())
	{
		help();
		cout << "***Could not initialize capturing...***\n";
		cout << "Current parameter's value: \n";
		return -1;
	}
	namedWindow("Histogram", 0);
	namedWindow("CamShift Demo", 0);
	setMouseCallback("CamShift Demo", onMouse, 0); //�����Ӧ����
	createTrackbar("Vmin", "CamShift Demo", &vmin, 256, 0);
	createTrackbar("Vmax", "CamShift Demo", &vmax, 256, 0);
	createTrackbar("Smin", "CamShift Demo", &smin, 256, 0);

	Mat frame, hsv, hue, mask, hist;
	Mat histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
	bool paused = false;
	for (;;)
	{
		if (!paused)  //û����ͣ
		{
			cap >> frame;//������ͷץȡһ֡ͼ�������frame��
			if (frame.empty())
				break;
		}

		frame.copyTo(image);
		if (!paused)
		{
			cvtColor(image, hsv, CV_BGR2HSV);
			if (trackObject)
			{
				int _vmin = vmin, _vmax = vmax;
				//������hsv��3��ͨ��
				inRange(hsv, Scalar(0, smin, MIN(_vmin, _vmax)), Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = { 0, 0 };
				//hue��ʼ��Ϊ��hsv��С���һ���ľ���ɫ���Ķ������ýǶȱ�ʾ�ģ�������֮�����120�ȣ���ɫ���180��
				hue.create(hsv.size(), hsv.depth());
				mixChannels(&hsv, 1, &hue, 1, ch, 1);

				if (trackObject < 0)//���ѡ�������ɿ��󣬸ú����ڲ��ֽ��丳ֵ1
				{
					//�˴��Ĺ��캯��roi�õ�ʱMat hue�ľ���ͷ����roi������ָ��ָ��hue
					Mat roi(hue, selection), maskroi(mask, selection);
					calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
					normalize(hist, hist, 0, 255, CV_MINMAX);

					trackWindow = selection;
					trackObject = 1;

					histimg = Scalar::all(0);
					int binW = histimg.cols / hsize;
					Mat buf(1, hsize, CV_8UC3); //����һ�����嵥bin����
					for (int i = 0; i < hsize; i++)
						buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
					cvtColor(buf, buf, CV_HSV2BGR);

					for (int i = 0; i < hsize; i++)
					{
						int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
						rectangle(histimg, Point(i*binW, histimg.rows), Point((i + 1)*binW, histimg.rows - val), Scalar(buf.at<Vec3b>(i)), -1, 8);

					}

				}
				calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
				backproj &= mask;

				trackBox = CamShift(backproj, trackWindow, TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));
				//meanShift(backproj, trackWindow, TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));
				if (trackWindow.area() <= 1)
				{
					int cols = backproj.cols, rows = backproj.rows;
					int r = (MIN(cols, rows) + 5) / 6;
					trackWindow = Rect(trackWindow.x - r, trackWindow.y - r, trackWindow.x + r, trackWindow.y + r) & Rect(0, 0, cols, rows);

				}
				if (backprojMode)

					cvtColor(backproj, image, CV_GRAY2BGR);
				ellipse(image, trackBox, Scalar(0, 0, 255), 3, CV_AA);
				//rectangle(image, Point(trackWindow.x, trackWindow.y), Point(trackWindow.x + trackWindow.width, trackWindow.y + trackWindow.height), Scalar(0, 0, 255), -1, CV_AA);
			}
		}
		//������벻��pauseΪ�滹�Ǽٶ���Ҫִ�е�
		else if (trackObject < 0)  //ͬʱҲ���ڰ�����ͣ��ĸ֮��
			paused = false;
		if (selectObject && selection.width>0 && selection.height > 0)
		{
			Mat roi(image, selection);
			bitwise_not(roi, roi);
		}
		imshow("CamShift Demo", image);
		imshow("Histogram", histimg);

		char c = (char)waitKey(10);
		if (c == 27)
			break;
		switch (c)
		{
		case 'b':
			backprojMode = !backprojMode;
		case 'c':
			trackObject = 0;
			histimg = Scalar::all(0);
			break;
		case 'h':
			showHist = !showHist;
			if (!showHist)
				destroyWindow("Histogram");
			else
				namedWindow("Histogram", 1);
			break;
		case 'p':
			paused = !paused;
			break;
		default:
			;
		}
	}
	return 0;
}
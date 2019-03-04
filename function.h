#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

//-----------------------------------define image file path-------------------------------

#define img_path_gakki "sources/picture/gakki.jpg"
#define img_path_Adrian "sources/picture/Adrian.jpg"
#define img_path_BlueCup "sources/picture/BlueCup.jpg"
#define img_path_Beauty_Template "sources/picture/beauty_template.jpg"
#define img_path_Beauty "sources/picture/beauty.jpg"
#define img_path_mask "sources/picture/mask.jpg"
#define img_path_elephant "sources/picture/elephant.jpg"
//-----------------------------------define video file path-------------------------------
#define video_path_dota "sources/video/dota.avi"
#define video_path_football "sources/video/football.avi"
#define video_path_helicopter "sources/video/helicopter.mkv"
#define video_path_Tsign "sources/video/Tsign.mp4"

//------------------------------------define other file path-------------------------------
#define face_cascade_name "sources/haarcascades/haarcascade_frontalface_alt.xml"
#define eyes_cascade_name  "sources/haarcascades/haarcascade_eye_tree_eyeglasses.xml"
//------------------------------------image processing-----------------------------------
void FeatureDetector_main();
void AdaptiveContrastEnhancement_main();
int ImageTraversing_main();
int minAreaRect_main();
int minEnclosingCircle_main();
int TemplateMatching_main();


int K_Means_main();
int HistogramComputation_main();
int SaltNoise_main();
int MouseOperator_main();
int GrabCut_main();
int FindContours_main();
int FloodFill_main();
int FaceDetector_main();
int FaceDetectorMask_main();
int RemoveLight_main();
int Morphology_main();
//------------------------------------video processing-----------------------------------
void MOG2_main();
int CamShift_main();
int FarnebackOpticalFlow_main();
int OpenTracker_main();
int OpticalFlow_main();
int PointTracking_main();

#endif // !FUNCTION_H


// Example 11-2. Code for perspective transformation
// Compute a perspective transformation between the 4 src control points
// in srcQuad to 4 dst control points in dstQuad and apply it the image.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

  //if(argc != 2) {
  //  cout << "Perspective Warp\nUsage: " <<argv[0] <<" <imagename>\n" << endl;
  //  return -1;
  //}

  Mat src = imread(argv[1],1);
  if( src.empty() ) { cout << "Can not load " << argv[1] << endl; return -1; }

  Point2f srcQuad[] = {
    Point2f(0, 0),                   // src Top left
    Point2f(src.cols-1, 0),          // src Top right
    Point2f(src.cols-1, src.rows-1), // src Bottom right
    Point2f(0, src.rows-1)           // src Bottom left
  };

  Point2f dstQuad[] = {
    Point2f(src.cols*0.05f, src.rows*0.33f),
    Point2f(src.cols*0.9f, src.rows*0.25f),
    Point2f(src.cols*0.8f, src.rows*0.9f),
    Point2f(src.cols*0.2f, src.rows*0.7f)
  };

  // COMPUTE PERSPECTIVE MATRIX
  //
  Mat warp_mat = getPerspectiveTransform(srcQuad, dstQuad);
  Mat dst;
  warpPerspective(src, dst, warp_mat, src.size(), INTER_LINEAR,
                      BORDER_CONSTANT, Scalar());

  for( int i = 0; i < 4; i++ )
    circle(dst, dstQuad[i], 5, Scalar(255, 0, 255), -1, LINE_AA);

  imshow("Perspective Transform Test", dst);
  waitKey();
  return 0;
}

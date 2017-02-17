#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
  // Read source image.
  Mat im_src = imread("ma.jpg");

  // 4 corners of the book in source image
  vector<Point2f> pts_dst( {Point2f(220, 54),
                              Point2f(690, 187),
                              Point2f(706, 519),
                              Point2f(207, 432)} );

  // Read destination image.
    // Mat im_dst = imread("ma.jpg");
    // Four corners of the book in destination image.
    vector<Point2f> pts_src( {Point2f(0, 0),
                              Point2f(300, 0),
                              Point2f(300, 200),
                              Point2f(0, 200)} );

  // Calc Homography
  Mat h = findHomography(pts_src, pts_dst);
  h = h.inv();

  // Output image
  Mat im_out;
  warpPerspective(im_src, im_out, h, im_src.size());

  imwrite("result.png", im_out);

  return 0;
}

// http://www.learnopencv.com/homography-examples-using-opencv-python-c

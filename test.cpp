#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
  // Read source image.
  Mat im_src = imread("book2.jpg");

  // 4 corners of the book in source image
  vector<Point2f> pts_src( {Point2f(141, 131),
                              Point2f(480, 159),
                              Point2f(493, 630),
                              Point2f(64, 601)} );

  // Read destination image.
    Mat im_dst = imread("book1.jpg");
    // Four corners of the book in destination image.
    vector<Point2f> pts_dst( {Point2f(318, 256),
                              Point2f(534, 372),
                              Point2f(316, 670),
                              Point2f(73, 473)} );

  // Calc Homography
  Mat h = findHomography(pts_src, pts_dst);

  // Output image
  Mat im_out;
  warpPerspective(im_src, im_out, h, im_dst.size());

  imwrite("result.png", im_out);

  return 0;
}

// http://www.learnopencv.com/homography-examples-using-opencv-python-c

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
  // Read source image.
  Mat im_src = imread("ma.jpg");

  Mat im_src_display = im_src.clone();
  Point2f nw_point_src(220.f, 54.f);
  Point2f ne_point_src(690.f, 187.f);
  Point2f se_point_src(706.f, 519.f);
  Point2f sw_point_src(207.f, 432.f);

  // 4 corners of the book in source image
  vector<Point2f> pts_src( {nw_point_src,
                              ne_point_src,
                              se_point_src,
                              sw_point_src} );

  

  // set destination image.
  Point2f nw_point_dst(0.f, 0.f);
  Point2f ne_point_dst(300.f, 0.f);
  Point2f se_point_dst(300.f, 200.f);
  Point2f sw_point_dst(0.f, 200.f);
  vector<Point2f> pts_dst( {nw_point_dst,
                              ne_point_dst,
                              se_point_dst,
                              sw_point_dst} );

  // Calc Homography
  Mat h = findHomography(pts_src, pts_dst);

  cout << "Homography Mat\'s size is: " ;
  cout << h.cols << ", " << h.rows << ": " << h.depth() << ": " << h.type() << endl;
  cout << h << endl << endl;

  float mem_data[3] = {220.f, 54.f, 1.f};
  Mat src_homogeneous_vector(3, 1, CV_32F, mem_data);
  cout << "homogeneous vector\'s size is: " ;
  cout << src_homogeneous_vector.cols << ", " << src_homogeneous_vector.rows << ": " << h.depth() << ": " << h.type() << endl;
  cout << src_homogeneous_vector << endl << endl;

  // Mat res_mat(3, 1, CV_32F);
  auto res_mat = h.mul(src_homogeneous_vector);
  cout << res_mat << endl << endl;
//  cout << "res mat\'s size is: " ;
//  cout << res.cols << ", " << res.rows << endl;
//  cout << res.at<float>(0, 0) << endl;
//  cout << res.at<float>(1, 0) << endl;
//  cout << res.at<float>(2, 0) << endl << endl;
  
  

  // Output image
  Mat im_out;
  warpPerspective(im_src, im_out, h, im_src.size());

  imwrite("result.png", im_out);

  return 0;
}

// http://www.learnopencv.com/homography-examples-using-opencv-python-c

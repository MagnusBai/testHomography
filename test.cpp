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
  Mat mat_homo = findHomography(pts_src, pts_dst);

  cout << "Homography Mat\'s size: " ;
  cout << mat_homo.cols << "x" << mat_homo.rows << ": " << mat_homo.depth() << endl;
  cout << mat_homo << endl << endl;

  float mem_data[3][1] = {{sw_point_src.x}, 
                          {sw_point_src.y}, 
                          {1.f}};
  Mat mat_vec(3, 1, CV_32F, mem_data);
  cout << "homogeneous vector\'s size: " ;
  cout << mat_vec.cols << "x" << mat_vec.rows << ": " << mat_vec.depth() << endl;
  cout << mat_vec << endl << endl;
  
  Mat mat_homo_;
  mat_homo.convertTo(mat_homo_, mat_vec.depth());

  Mat res_vector = mat_homo_*mat_vec;
  cout << "result vector\'s size: " ;
  cout << res_vector.cols << "x" << res_vector.rows << ": " << res_vector.depth() << endl;
  cout << res_vector << endl << endl;

  // (xd, yd)->points of destinition (xs, ys)->points of source
  //  (xd)              (xs)
  //  (yd) = (mat_homo)*(ys)
  //  (1 )              (1 )

  // Output image
  Mat im_out;
  warpPerspective(im_src, im_out, mat_homo, Size(300, 200));  // has much relationship with size

  imwrite("result.png", im_out);

  return 0;
}

// http://www.learnopencv.com/homography-examples-using-opencv-python-c

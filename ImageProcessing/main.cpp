#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;

int main()
{

	char c[10000];
	cout << "Please enter file name \n(Eg: coin1.png) : ";
	cin >> c;

	char s[1000] = "Image\\";
	strcat(s, c);
	Mat src, gray;
	src = imread(s, 1); 
	if (src.empty())
	{
		std::cout << "!!! Failed to load image.Image not found !!!" << std::endl;
		return 0;
	}
	resize(src, src, Size(640, 480));
	cvtColor(src, gray, CV_BGR2GRAY);

	// Reduce the noise so we avoid false circle detection
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	// Apply the Hough Transform to find the circles
	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0);
	float val = 0;
	// Draw the circles detected

	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);// circle center     
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);// circle outline
		int a = radius*radius;
		if (2200 <= a && a <= 3550)
			val += 5;
		else if (3600 <= a && a <= 5000)
			val += 2;
		else if (1000 <= a && a <= 2200)
			val += 1;
	}


	cout << "Value in Image ("<< c <<") : Rs. "<<val <<"/="<< endl;
	// Show your results
	namedWindow("120000507 - Assignmnt 2", CV_WINDOW_AUTOSIZE);
	imshow("120000507 - Assignmnt 2", src);

	waitKey(0);
	return 0;
}
// ImageCompressionDecompression.cpp : Defines the entry point for the console application.
//

#include "Utils.h"
#include "Algo.h"

using namespace std;
using namespace cv;

int main()
{
	Mat sampleImage1 = imread("..\\..\\..\\Sample1.bmp");
	Mat sampleImage2 = imread("..\\..\\..\\Sample2.bmp");
	Mat sampleImage3 = imread("..\\..\\..\\Sample3.bmp");

	Mat smallSample = imread("..\\..\\..\\SmallSample.bmp");
	Utils::validate(sampleImage1, Algo::uncompress(Algo::compress(sampleImage1)));

	getchar();
	return 0;
}


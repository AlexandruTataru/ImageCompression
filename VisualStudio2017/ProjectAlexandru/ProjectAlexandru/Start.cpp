// ImageCompressionDecompression.cpp : Defines the entry point for the console application.
//

#include "Utils.h"
#include "Algo.h"

using namespace std;
using namespace cv;

int main()
{
	Mat sampleImage1 = imread("Sample1.bmp");
	Mat sampleImage2 = imread("Sample2.bmp");
	Mat sampleImage3 = imread("Sample3.bmp");

	Utils::validate(sampleImage1, Algo::uncompress(Algo::compress(sampleImage1)), "Sample 1");
	Utils::validate(sampleImage2, Algo::uncompress(Algo::compress(sampleImage2)), "Sample 2");
	Utils::validate(sampleImage3, Algo::uncompress(Algo::compress(sampleImage3)), "Sample 3");

	/*uint8_t* pixelPtr = (uint8_t*)img.data;
	int cn = img.channels();
	Scalar_<uint8_t> bgrPixel;

	long pixels = 0;
	for (int i = 0; i < img.rows; i++)
	{
	for (int j = 0; j < img.cols; j++)
	{
	bgrPixel.val[0] = pixelPtr[i*img.cols*cn + j*cn + 0]; // B
	bgrPixel.val[1] = pixelPtr[i*img.cols*cn + j*cn + 1]; // G
	bgrPixel.val[2] = pixelPtr[i*img.cols*cn + j*cn + 2]; // R
	//cout << "R: " << (int)bgrPixel.val[2] << " G: " << (int)bgrPixel.val[1] << " B: " << (int)bgrPixel.val[0] << endl;
	}
	}
	cout << "Found " << pixels << " pixels" << endl;
	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);*/
	getchar();
	return 0;
}


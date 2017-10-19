#pragma once

#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;

namespace Algo
{
	std::ifstream::pos_type filesize(const char* filename)
	{
		std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	std::string compress(cv::Mat& rawImage)
	{
		std::string fileName = "compressedImage.dat";
		ofstream OutFile;
		OutFile.open(fileName, ios::out | ios::binary | ios::trunc);
		OutFile.write((char*)&rawImage.rows, sizeof(rawImage.rows));
		OutFile.write((char*)&rawImage.cols, sizeof(rawImage.cols));

		uint8_t* pixelsPtr = (uint8_t*)rawImage.data;
		for (int i = 0; i < rawImage.rows; i++)
		{
			for (int j = 0; j < rawImage.cols; j++)
			{
				uint8_t blue = pixelsPtr[i*rawImage.cols*rawImage.channels() + j*rawImage.channels() + 0];
				OutFile.write((char*)&blue, sizeof(blue));
				uint8_t green = pixelsPtr[i*rawImage.cols*rawImage.channels() + j*rawImage.channels() + 1];
				OutFile.write((char*)&green, sizeof(green));
				uint8_t red = pixelsPtr[i*rawImage.cols*rawImage.channels() + j*rawImage.channels() + 2];
				OutFile.write((char*)&red, sizeof(red));
			}
		}

		OutFile.close();
		return fileName;
	}

	cv::Mat uncompress(std::string & uncompressedImagePath)
	{
		cv::Mat uncompressedImage(0, 0, CV_8UC3);
		ifstream InFile;
		InFile.open(uncompressedImagePath, ios::in | ios::binary);
		InFile.read((char*)&uncompressedImage.rows, sizeof(uncompressedImage.rows));
		InFile.read((char*)&uncompressedImage.cols, sizeof(uncompressedImage.cols));
		uncompressedImage.data = new uint8_t[uncompressedImage.rows * uncompressedImage.cols * 3];
		int elemIdx = 0;
		for (int i = 0; i < uncompressedImage.rows; i++)
		{
			for (int j = 0; j < uncompressedImage.cols; j++)
			{
				for (size_t channels = 0; channels < 3; ++channels)
				{
					uint8_t data;
					InFile.read((char*)&data, sizeof(uint8_t));
					uncompressedImage.data[elemIdx] = data;
					++elemIdx;
				}
			}
		}

		InFile.close();

		cout << "File size is: " << filesize(uncompressedImagePath.c_str()) << endl;

		return uncompressedImage;
	}
}
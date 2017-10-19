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
		std::vector<uint16_t> data;
		int cb = -1, cg = -1, cr = -1;
		uint16_t counter = 1;
		size_t size = 0;
		for (int i = 0; i < rawImage.rows; i++)
		{
			for (int j = 0; j < rawImage.cols; j++)
			{
				uint8_t blue = pixelsPtr[i*rawImage.cols*rawImage.channels() + j*rawImage.channels() + 0];
				uint8_t green = pixelsPtr[i*rawImage.cols*rawImage.channels() + j*rawImage.channels() + 1];
				uint8_t red = pixelsPtr[i*rawImage.cols*rawImage.channels() + j*rawImage.channels() + 2];

				if (cb == -1)
				{
					cb = blue;
					cr = red;
					cg = green;
				}
				else
				{
					if (cb != blue || cr != red || cg != green)
					{
						data.emplace_back(cb);
						data.emplace_back(cg);
						data.emplace_back(cr);
						data.emplace_back(counter);
						size += 4;
						counter = 1;

						cb = blue;
						cr = red;
						cg = green;
					}
					else
					{
						counter++;
					}
				}
			}
		}
		data.emplace_back(cb);
		data.emplace_back(cg);
		data.emplace_back(cr);
		data.emplace_back(counter);
		size += 4;

		OutFile.write((char*)&size, sizeof(size_t));
		for (size_t i = 1; i <= size; ++i)
		{
			if(i % 4 != 0)
				OutFile.write((char*)&data.at(i - 1), sizeof(uint8_t));
			else
				OutFile.write((char*)&data.at(i - 1), sizeof(uint16_t));
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
		size_t sizeOfData;
		InFile.read((char*)&sizeOfData, sizeof(sizeOfData));
		uncompressedImage.data = new uint8_t[uncompressedImage.rows * uncompressedImage.cols * 3];
		int elemIdx = 0;
		for (size_t idx = 0; idx <= sizeOfData; ++idx)
		{
			uint8_t blue, green, red;
			uint16_t counter;
			InFile.read((char*)&blue, sizeof(uint8_t));
			InFile.read((char*)&green, sizeof(uint8_t));
			InFile.read((char*)&red, sizeof(uint8_t));
			InFile.read((char*)&counter, sizeof(uint16_t));
			for (uint16_t times = 0; times < counter; ++times)
			{
				uncompressedImage.data[elemIdx] = blue;
				++elemIdx;
				uncompressedImage.data[elemIdx] = green;
				++elemIdx;
				uncompressedImage.data[elemIdx] = red;
				++elemIdx;
			}
		}
		InFile.close();

		cout << "File size is: " << filesize(uncompressedImagePath.c_str()) << endl;

		return uncompressedImage;
	}
}
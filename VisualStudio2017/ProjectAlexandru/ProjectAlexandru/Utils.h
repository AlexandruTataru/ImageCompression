#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

namespace Utils
{
	void validate(const cv::Mat& expected, const cv::Mat& actual)
	{
		if (expected.rows != actual.rows)
		{
			std::cout << "TEST FAILED: Number of rows does not match expected " << expected.rows << " and got " << actual.rows << std::endl;
			return;
		}

		if (actual.cols != expected.cols)
		{
			std::cout << "TEST FAILED: Number of columns does not match expected " << expected.rows << " and got " << actual.rows << std::endl;
			return;
		}

		int expectedChannels = expected.channels();
		int actualChannels = actual.channels();
		if (actualChannels != expectedChannels)
		{
			std::cout << "TEST FAILED: Number of channels does not match expected " << expectedChannels << " and got " << actualChannels << std::endl;
			return;
		}

		uint8_t* actualPixelsPtr = (uint8_t*)actual.data;
		if (actualPixelsPtr == nullptr)
		{
			std::cout << "TEST FAILED: Actual image data is invalid" << std::endl;
			return;
		}
		uint8_t* expectedPixelsPtr = (uint8_t*)expected.data;
		if (expectedPixelsPtr == nullptr)
		{
			std::cout << "TEST FAILED: Expected image data is invalid" << std::endl;
			return;
		}

		for (int i = 0; i < actual.rows; i++)
		{
			for (int j = 0; j < actual.cols; j++)
			{
				if ((actualPixelsPtr[i*actual.cols*actualChannels + j*actualChannels + 0] != expectedPixelsPtr[i*expected.cols*expectedChannels + j*expectedChannels + 0]) ||
					(actualPixelsPtr[i*actual.cols*actualChannels + j*actualChannels + 1] != expectedPixelsPtr[i*expected.cols*expectedChannels + j*expectedChannels + 1]) || 
					(actualPixelsPtr[i*actual.cols*actualChannels + j*actualChannels + 2] != expectedPixelsPtr[i*expected.cols*expectedChannels + j*expectedChannels + 2]))
				{
					std::cout << "TEST FAILED : The pixel at (" << i << ", " << j << ") is different from source" << std::endl;
					return;
				}
			}
		}
		std::cout << "TEST SUCCESFULL" << std::endl;
	}
}
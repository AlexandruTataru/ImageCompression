#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

namespace Utils
{
    void validate(const cv::Mat& actual, const cv::Mat& expected, const std::string& message = "")
    {
        std::cout << "TEST FAILED: " << message << std::endl;
    }
}
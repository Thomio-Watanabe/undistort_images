//--------------------------------------------------------------------------
// Author: Thomio Watanabe
// Date: September 2015
// -- Brazilian Institute of Robotics --
// Description: This program reads the Camera parameters from a YAML file,
// undistort a list of images and save the results.
//--------------------------------------------------------------------------

#ifndef _UNDISTORT_HPP
#define _UNDISTORT_HPP

#include <opencv2/core/core.hpp>

class UndistortImages{
    private:
        // Camera parameters
        cv::Mat cameraMatrix;
        cv::Mat distCoeffs;
        std::vector<std::string> inputImagesPaths;

    public:
        void readCameraParameters( char* );
        void loadImages( char* );
        void undistortImages();
};

#endif

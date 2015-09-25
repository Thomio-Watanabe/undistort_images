#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "undistort.hpp"
#include <iostream>
#include <cstdlib>

using namespace cv;
using namespace std;

// Read a YAML file with the camera parameters (cameraMatrix and distCoeffs)
void UndistortImages::readCameraParameters( char* yml_filename ){
    FileStorage fs;
    fs.open(yml_filename, FileStorage::READ);
    if( !fs.isOpened() ){
        cerr << " Fail to open " << yml_filename << endl;
        exit(EXIT_FAILURE);
    }

    // Get camera parameters
    fs["camera_matrix"] >> cameraMatrix;
    fs["distortion_coefficients"] >> distCoeffs; 

    // Print out the camera parameters
    cout << "\n -- Camera parameters -- " << endl;
    cout << "\n CameraMatrix = " << endl << " " << cameraMatrix << endl << endl;
    cout << " Distortion coefficients = " << endl << " " << distCoeffs << endl << endl;

    fs.release();
}

void UndistortImages::loadImages( char* images_list ){
    FileStorage fs;
    fs.open(images_list,FileStorage::READ);
    if( !fs.isOpened() ){
        cerr << " Fail to open " << images_list << endl;
        exit(EXIT_FAILURE);
    }
    
    cout << " Images size = " << fs["images"].size() << endl;

    FileNode imagesPathNode = fs["images"];
    for(FileNodeIterator it = imagesPathNode.begin();
            it != imagesPathNode.end(); ++it){
        inputImagesPaths.push_back( *it );
    }

    fs.release();
}

void UndistortImages::undistortImages(){
    cout << " Undistorting images... " << endl;

    for(vector<string>::iterator imagePath = inputImagesPaths.begin();
            imagePath != inputImagesPaths.end(); ++imagePath)
    {
        Mat inputImage = imread( *imagePath, CV_LOAD_IMAGE_COLOR );
        if( !inputImage.data ){
            cout << " Could not open or find the image: " << *imagePath << endl;
            cout << " Verify if the input images path are absolute," << endl;
            cout << " or change the program directory." << endl;
            exit(EXIT_FAILURE);
        }
        Mat outputImage;
        undistort(inputImage,outputImage,cameraMatrix,distCoeffs);
        
        // Separate filename and path
        size_t found = imagePath->find_last_of("/");
        string path = imagePath->substr(0,found);
        string filename = imagePath->substr(found+1);

        // Save undistorted image
        string outputPath(path+ "/undistorted_" + filename);
        imwrite(outputPath,outputImage);
    }
    cout << " Done !" << endl;
}



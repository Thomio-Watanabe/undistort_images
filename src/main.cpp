
#include "undistort.hpp"
#include <iostream>
#include <cstdlib>

using namespace cv;
using namespace std;

void printHelp(char* programName){
    cout << " Correct usage: " << programName << " camera.yml" << " images_paths.xml "<< endl;
    cout << " camera.yml = file with camera matrix and distortion coefficients. " << endl;
    cout << " images_paths.xml = file with path to images that should be undistorted." << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
    if( argc == 1 ){
        cout << " Wrong number of arguments (!=3) " << endl;
        printHelp( argv[0] );
    }

    if( !string("--help").compare(argv[1]) || !string("-h").compare(argv[1]) )
        printHelp( argv[0] );

    if(argc != 3){
        cout << " Wrong number of arguments (!=3) " << endl;
        printHelp( argv[0] );
    }

    UndistortImages undistortImages;
    undistortImages.readCameraParameters( argv[1] );
    undistortImages.loadImages( argv[2] );
    undistortImages.undistortImages( );

    return 0;
}

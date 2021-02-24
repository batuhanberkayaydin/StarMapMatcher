/**
 * @file main.cpp
 * @author Berkay (batuhanberkayaydin@gmail.com)
 * @brief main code to start Matcher4D class
 * @version 0.1
 * @date 2021-02-24
 * 
 */

#include <iostream>
#include "opencv2/core.hpp"

#include "Matcher4D.hpp"

const char* keys =
        "{ help h |                        | Help message. }"
        "{ input1 | StarMap.png            | First Image. }"
        "{ input2 | Small_area_rotated.png | Second Image. }";

int main( int argc, char* argv[] )
{
    
	cv::Mat fistImage = cv::imread( argv[1] );
    cv::Mat secondImage = cv::imread( argv[2]);
    
    if ( fistImage.empty() || secondImage.empty() )
    {
        std::cout << "Image not found!\n" << std::endl;
        return -1;
    }

	Matcher4D locate;
	locate.startProcess(fistImage, secondImage);

    
    return 0;
}

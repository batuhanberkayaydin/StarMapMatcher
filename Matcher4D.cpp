/**
 * @file Matcher4D.cpp
 * @author Berkay (batuhanberkayaydin@gmail.com)
 * @brief Matcher4D C++ File
 * @version 0.1
 * @date 2021-02-24
 * 
 */

#include "Matcher4D.hpp"

/**
 * @brief Construct a new Matcher4D::Matcher4D object
 * 
 */
Matcher4D::Matcher4D(){

    orbNFeatures_ = 10000;
    scaleFactor_ = 1.2;
    pyramidLevels_ = 4;
    edgeThreshold_ = 31 ;
    firstLevel_ = 0;
    matcherType_ = "BruteForce-Hamming" ;
    ratioFilter_ = 0.65f;

    detector_ = cv::ORB::create(orbNFeatures_, scaleFactor_, pyramidLevels_, edgeThreshold_, firstLevel_);
    descriptor_ = cv::ORB::create(orbNFeatures_, scaleFactor_, pyramidLevels_, edgeThreshold_, firstLevel_);
    matcher_  = cv::DescriptorMatcher::create ( matcherType_ );
    
}

/**
 * @brief Destroy the Matcher4D::Matcher4D object
 * 
 */
Matcher4D::~Matcher4D(){
    firstImageMatches_.release();
    detector_.release();
    descriptor_.release();
    matcher_.release();
    firstImageDescriptors_.release();
}

/**
 * @brief Starts matching process.
 * 
 * @param firstImage cv::Mat RGB or GRAYSCALE.
 * @param secondImage cv::Mat RGB or GRAYSCALE.
 */
void Matcher4D::startMatching(cv::Mat& firstImage, cv::Mat& secondImage) {

    detector_->detect ( secondImage,secondImageKeypoints_ );
    detector_->detect ( firstImage,fistImageKeypoints_ );

    descriptor_->compute ( secondImage, secondImageKeypoints_, secondImageDescriptors_ );
    descriptor_->compute ( firstImage, fistImageKeypoints_, firstImageDescriptors_ );
    
    matcher_->knnMatch( secondImageDescriptors_, firstImageDescriptors_, knnMatchResult_, 3 );
    
    for (size_t i = 0; i < knnMatchResult_.size(); i++)
    {
        if (knnMatchResult_[i][0].distance < ratioFilter_ * knnMatchResult_[i][1].distance)
        {
            goodMatches_.push_back(knnMatchResult_[i][0]);
        }
    }
}

/**
 * @brief Last process of code gives result image and print points.
 * 
 * @param firstImage cv::Mat RGB or GRAYSCALE.
 * @param secondImage cv::Mat RGB or GRAYSCALE.
 */
void Matcher4D::drawResults(cv::Mat& firstImage, cv::Mat& secondImage) {

    cv::drawMatches( secondImage, secondImageKeypoints_, firstImage, fistImageKeypoints_, goodMatches_, firstImageMatches_, cv::Scalar::all(-1),
                 cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    for( size_t i = 0; i < goodMatches_.size(); i++ )
    {
        secondImagePoints_.push_back( secondImageKeypoints_[ goodMatches_[i].queryIdx ].pt );
        firstImagePoints_.push_back( fistImageKeypoints_[ goodMatches_[i].trainIdx ].pt );
    }
    H_ = cv::findHomography( secondImagePoints_, firstImagePoints_, cv::RANSAC );
    
    std::vector<cv::Point2f> secondImageCorners(4);
    secondImageCorners[0] = cv::Point2f(0, 0);
    secondImageCorners[1] = cv::Point2f( (float)secondImage.cols, 0 );
    secondImageCorners[2] = cv::Point2f( (float)secondImage.cols, (float)secondImage.rows );
    secondImageCorners[3] = cv::Point2f( 0, (float)secondImage.rows );
    std::vector<cv::Point2f> firstImageCorners(4);
    cv::perspectiveTransform( secondImageCorners, firstImageCorners, H_);

    cv::line( firstImageMatches_, firstImageCorners[0] + cv::Point2f((float)secondImage.cols, 0),
          firstImageCorners[1] + cv::Point2f((float)secondImage.cols, 0), cv::Scalar(0, 255, 0), 2 );
    cv::line( firstImageMatches_, firstImageCorners[1] + cv::Point2f((float)secondImage.cols, 0),
          firstImageCorners[2] + cv::Point2f((float)secondImage.cols, 0), cv::Scalar( 0, 255, 0), 2 );
    cv::line( firstImageMatches_, firstImageCorners[2] + cv::Point2f((float)secondImage.cols, 0),
          firstImageCorners[3] + cv::Point2f((float)secondImage.cols, 0), cv::Scalar( 0, 255, 0), 2 );
    cv::line( firstImageMatches_, firstImageCorners[3] + cv::Point2f((float)secondImage.cols, 0),
          firstImageCorners[0] + cv::Point2f((float)secondImage.cols, 0), cv::Scalar( 0, 255, 0), 2 );

    for (int i = 0; i < 4; i++) {
        std::cout << " First image matched points : " << firstImageCorners[i] << " corresponds to second image points:" << secondImageCorners[i]  << std::endl;
    }    

	cv::namedWindow("Result", cv::WINDOW_FREERATIO);
    cv::imshow("Result", firstImageMatches_ );
    
    cv::waitKey();

}


/**
 * @brief Starts matching process on this function. 
 * 
 * @param firstImage cv::Mat RGB or GRAYSCALE.
 * @param secondImage cv::Mat RGB or GRAYSCALE.
 */
void Matcher4D::startProcess(cv::Mat& firstImage, cv::Mat& secondImage){

	startMatching(firstImage, secondImage);
    drawResults(firstImage, secondImage);
    
}









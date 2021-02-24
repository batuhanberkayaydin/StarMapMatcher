/**
 * @file Matcher4D.hpp
 * @author Berkay (batuhanberkayaydin@gmail.com)
 * @brief Matcher4D Header File
 * @version 0.1
 * @date 2021-02-24
 * 
 */

#ifndef MATCHER_4D_H
#define MATCHER_4D_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv2/core.hpp"

class Matcher4D {

public:
    Matcher4D();
    ~Matcher4D();
    void startProcess(cv::Mat& firstImage, cv::Mat& secondImage);

private:

    int orbNFeatures_ ;
    float scaleFactor_ ;
    int pyramidLevels_ ;
    int edgeThreshold_ ;
    int firstLevel_ ;
    float ratioFilter_ ;
    cv::String matcherType_ ;

    cv::Ptr<cv::FeatureDetector> detector_ ;
    cv::Ptr<cv::DescriptorExtractor> descriptor_ ;
    cv::Ptr<cv::DescriptorMatcher> matcher_ ;

    std::vector<cv::KeyPoint> fistImageKeypoints_, secondImageKeypoints_ ;
    std::vector< std::vector<cv::DMatch> > knnMatchResult_ ;
    std::vector<cv::DMatch> goodMatches_ ;

    cv::Mat firstImageDescriptors_, secondImageDescriptors_ ;
    cv::Mat firstImageMatches_ ;
    std::vector<cv::Point2f> secondImagePoints_;
    std::vector<cv::Point2f> firstImagePoints_;
    cv::Mat H_;

    void startMatching(cv::Mat& firstImage, cv::Mat& secondImage);
    void drawResults(cv::Mat& firstImage, cv::Mat& secondImage);  

};

#endif // MATCHER_4D_H
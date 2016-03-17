#ifndef FEATURES_H_
#define FEATURES_H_

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <string>
#include "opencv2/nonfree/features2d.hpp"

using namespace std;
using namespace cv;


class features_
{
    public:
    cv::Mat  img1, img2;//input images
    cv::Mat descriptors1, descriptors2; // descriptors for keypoints found
    std::vector<cv::KeyPoint> keypoints1, keypoints2; // keypoints found in the images
    std::vector<cv::DMatch> matches;

    void set_detector(string a);

    void set_description(string a);

    void set_matcher(string a);

    int findKeypoints();

    int findDescriptor(std::vector<cv::KeyPoint> newKey);

    int set_source_image(cv::Mat inimg);

    int set_scene_image(cv::Mat inimg);

    int image_features_(std::vector<cv::KeyPoint> newKey);

    struct options {
        string detectorType; // feature detector method
        /*
        FAST" – FastFeatureDetector
        "STAR" – StarFeatureDetector
        "SIFT" – SIFT (nonfree module)
        "SURF" – SURF (nonfree module)
        "ORB" – ORB
        "BRISK" – BRISK
        "MSER" – MSER
        "GFTT" – GoodFeaturesToTrackDetector
        "HARRIS" – GoodFeaturesToTrackDetector with Harris detector enabled
        "Dense" – DenseFeatureDetector
        "SimpleBlob" – SimpleBlobDetector
        */
        string descriptorType;
        /*
        "SIFT" – SIFT
        "SURF" – SURF
        "BRIEF" – BriefDescriptorExtractor
        "BRISK" – BRISK
        "ORB" – ORB
        "FREAK" – FREAK
        */
        string matcherType;
        /* BruteForce (it uses L2 )
        BruteForce-L1
        BruteForce-Hamming
        BruteForce-Hamming(2)
        FlannBased
        */

    };

    struct options option;
    features_();
    features_(cv::Mat inimg1, cv :: Mat inimg2);

};

#endif






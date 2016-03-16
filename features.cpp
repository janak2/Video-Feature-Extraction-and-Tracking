 #include "features.h"


//constructors
  features_::features_(cv::Mat inimg1, cv :: Mat inimg2)
  {
    img1 = inimg1;
    img2 = inimg2;
  }
  features_::features_()
  {

  }

  void features_::set_detector(string a)
  {
    if(a.empty())
    {
      cout<"no detector is been set";
      return;
    }
    option.detectorType = a;
    return ;
    }
      
void features_::set_description(string a)
{
  if(a.empty())
    {
      cout<"no detector is been set";
      return;
    }
  option.descriptorType = a;
return;
}

void features_::set_matcher(string a)
{
  if(a.empty())
    {
      cout<"no detector is been set";
      return;
    }
  option.matcherType = a;
  }

int features_::findKeypoints() {
cv::Ptr<FeatureDetector> detector = FeatureDetector::create(option.detectorType);
cout<<"deetcted\n";
if ( detector.empty() )
{
cout << "Can not create detector or descriptor extractor or descriptor matcher of given types 4s" << endl;
return -1;
}
detector->detect(img1, keypoints1);
cout<<"deetcted\n";
detector->detect(img2, keypoints2);
return 0;
}

int features_::findDescriptor(std::vector<cv::KeyPoint> newKey) {
//Ptr<DescriptorExtractor> descri
cv::Ptr<DescriptorExtractor> descriptor = DescriptorExtractor::create(option.descriptorType);
if ( descriptor.empty() ) {
cout << "Can not create detector or descriptor extractor or descriptor matcher of given types" << endl;
return -1;
}
descriptor->compute(img1, newKey, descriptors1);
descriptor->compute(img2, keypoints2, descriptors2);
return 0;
}

int features_::set_source_image(cv::Mat inimg)
{
  if( inimg.empty())
  {
    cout<<"no input image";
    return -1;
  }
  cout<<"setting";
img1 = inimg.clone(); 
return 0;
}

int features_::set_scene_image(cv::Mat inimg)
{
  if( inimg.empty())
  {
    cout<<"no input image";
    return -1;
  }
  cout<<"setting";
img2 = inimg.clone(); 
findKeypoints();
return 0;
}


int features_::image_features_(std::vector<cv::KeyPoint> newKey)
{ 


/* if(img.empty())
 {
  cout<<"error";
  return -1;
 }
  
  Mat img2(img);
  
  cv::Ptr<FeatureDetector> detector1 = FeatureDetector::create(option.detectorType);

  //imshow("image",img2);
  if ( detector1.empty() )
  {
  cout << "Can not create detector or descriptor extractor or descriptor matcher of given types" << endl;
  return -1;
  }
  detector1->detect(img2, keypoints2);
  cv::Ptr<DescriptorExtractor> descriptor = DescriptorExtractor::create(option.descriptorType);
  descriptor->compute(img2, keypoints2, descriptors2);
  cout<<"keypoints 2"<<keypoints2.size()<<endl;
*/ Ptr<DescriptorMatcher> descriptorMatcher = DescriptorMatcher::create(option.matcherType);
  
  //find all matches
  vector<DMatch>  matches;
  descriptorMatcher->match( descriptors1, descriptors2, matches);
  cout<<"matches"<<matches.size()<<endl;

  double max_dist = 0; double min_dist = 100000000;
  std::vector<cv::DMatch > goodMatches;

  //-- Quick calculation of max and min distances between keypoints
  for( int i = 0; i < descriptors1.rows; i++ )
  { 
    double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  printf("-- Max dist : %f \n", max_dist );
  printf("-- Min dist : %f \n", min_dist );

  for( int i = 0; i < descriptors1.rows; i++ )
  { 
    if( matches[i].distance <= 3*min_dist )
      { 
        goodMatches.push_back( matches[i]); 
      }
  }

  cout<<"goodmatches"<<goodMatches.size()<<endl;
  
  Mat imgMatches; // image for storing matches
  drawMatches( img1, newKey, img2, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);  
  // Show detected matches
  //imshow( "Matches", imgMatches );

  //-- Localize the object
  std::vector<Point2f> obj ;
  std::vector<Point2f> scene ;

  for( int i = 0; i < goodMatches.size(); i++ )
    {
      //-- Get the keypoints from the good matches
      obj.push_back( newKey[ goodMatches[i].queryIdx ].pt );
      scene.push_back( keypoints2[ goodMatches[i].trainIdx ].pt );
    }

  if(obj.size() > 3)
  {
  //find the object
  Mat H = findHomography( obj, scene, CV_RANSAC );

  //-- Get the corners from the image_1 ( the object to be "detected" )
  std::vector<Point2f> obj_corners(4);
  obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img1.cols, 0 );
  obj_corners[2] = cvPoint( img1.cols, img1.rows ); obj_corners[3] = cvPoint( 0, img1.rows );
  std::vector<Point2f> scene_corners(4);

  perspectiveTransform( obj_corners, scene_corners, H);
  float  x1,x2,y1,y2;
  x1=min(scene_corners[0].x,min(scene_corners[1].x,min(scene_corners[2].x,scene_corners[3].x)));
  x2=max(scene_corners[0].x,max(scene_corners[1].x,max(scene_corners[2].x,scene_corners[3].x)));

  y1=min(scene_corners[0].y,min(scene_corners[1].y,min(scene_corners[2].y,scene_corners[3].y)));
  y2=max(scene_corners[0].y,max(scene_corners[1].y,max(scene_corners[2].y,scene_corners[3].y)));



  //-- Draw lines between the corners (the mapped object in the scene - image_2 )
  line( imgMatches, Point2f(x1,y1) + Point2f( img1.cols, 0), Point2f(x2,y1) + Point2f( img1.cols, 0), Scalar(0, 255, 0), 4 );
  line( imgMatches, Point2f(x2,y1) + Point2f( img1.cols, 0), Point2f(x2,y2) + Point2f( img1.cols, 0), Scalar( 0, 255, 0), 4 );
  line( imgMatches, Point2f(x2,y2) + Point2f( img1.cols, 0), Point2f(x1,y2) + Point2f( img1.cols, 0), Scalar( 0, 255, 0), 4 );
  line( imgMatches, Point2f(x1,y2) + Point2f( img1.cols, 0), Point2f(x1,y1) + Point2f( img1.cols, 0), Scalar( 0, 255, 0), 4 );

  //-- Show detected matches
  imshow( "Good Matches & Object detection", imgMatches );
  }

   return 0;


}

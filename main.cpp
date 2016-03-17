#include "features.h"
#include "dynamic.h"


int main( int argc, char** argv )
{ 
  int temp=0;
  dynamicStore d;
	Mat img1 = imread( argv[1], 1 );
	Mat img2;
	 VideoCapture cap(argv[2]);
  while(true)
  {
  	
   
    cap >> img2;
  
  
  features_ feature;
  feature.set_detector("ORB");
  feature.set_description("ORB");
  feature.set_matcher("BruteForce-L1");
  feature.set_source_image(img1);
  feature.set_scene_image(img2);
  
/*  if(!temp){
    d.updateDynamicStore(feature.keypoints1);
    temp++;
  }

  std::vector<cv::KeyPoint> newKey;
  for(int i=0;i<d.dynamicBucket.size();i++){
    newKey.push_back(d.dynamicBucket[i].keyPoint);
  }
*/
  feature.findDescriptor(feature.keypoints1);
  feature.image_features_(feature.keypoints1);

  if(waitKey(20)==27)
  	{
  		break;
  	}

    d.updateDynamicStore(feature.keypoints2);

}
  return(0);
}



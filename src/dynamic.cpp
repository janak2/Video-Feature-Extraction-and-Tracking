#include "dynamic.h"

using namespace std;
using namespace cv;

void dynamicStore::updateDynamicStore(std::vector <cv::KeyPoint> newKeyPoints)
{
	
	int n=dynamicBucket.size();
	int n1=newKeyPoints.size();
	for(int i=0;i<n1;i++){
		int j;
		for(j=0;j<n;j++){
			if(dynamicBucket[j].keyPoint.pt == newKeyPoints[i].pt)break;
		}
		if(j==n){
			feature_point y;
			y.keyPoint = newKeyPoints[i];
			y.count=0;
			dynamicBucket.push_back(y);
		}
	}

	n=dynamicBucket.size();

	for(int i=0;i<n;i++){
		for(int j=0;j<n1;j++){
			if(dynamicBucket[i].keyPoint.pt == newKeyPoints[j].pt){
				dynamicBucket[i].count+=x;
				break;
			}
			if(j == n1)dynamicBucket[i].count-=x;
		}
	}

	for(int i=0;i<n;i++){
		if(dynamicBucket[i].count < threshold)dynamicBucket.erase(dynamicBucket.begin() + i);
	}

}


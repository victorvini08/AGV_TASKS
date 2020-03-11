#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include<math.h>
#include<bits/stdc++.h> 
#include<vector>
#include <queue>
using namespace std;
using namespace cv;

#define infinity 100000




struct point1
{




	int point_x;
	int point_y;
	float distance;

	
     
 
};

Mat img=imread("/home/aryan/Downloads/samps/Temp.jpg",0);

//Mat img(60,100,CV_8UC1,Scalar(0));

struct compare_distance{


    bool operator()(  point1 const& p1,  point1 const& p2) 
    { 
         
        return p1.distance > p2.distance; 
    } 
};
 

int x=img.rows,y=img.cols;
Mat ax(x,y,CV_8UC1,Scalar(0));



int check_point(int i,int j)
{
  if(i>=0 && j>=0 && i<x && j<y)
    return 1;
  else
    return 0;
}




 struct point1 points[1000][1000];
 int is_visited[1000][1000];



int main()
{
for(int i=0;i<x;i++)
{
	for(int j=0;j<y;j++)
	{
		if(img.at<uchar>(i,j)>200)
		{
			img.at<uchar>(i,j)=255;
		}
		else if(img.at<uchar>(i,j)<50)
		{
			img.at<uchar>(i,j)=0;
		}
	}
}


for(int i=0;i<x;i++)
{
	for(int j=0;j<y;j++)
	{
          points[i][j].distance=infinity;
          is_visited[i][j]=0;
	}
}

is_visited[0][0]=1;
points[0][0].distance=0;

priority_queue<point1, vector<point1>, compare_distance> pq; 

point1 a;
a.point_y=0,a.point_x=0,a.distance=0;

 pq.push(a) ;  

while(!pq.empty())
{
	
    point1 p=pq.top();
    int x_cood=p.point_x;
    int y_cood=p.point_y;
    

    if( is_visited[x_cood][y_cood+1]==0 && img.at<char>(x_cood,y_cood+1)==0 && check_point(x_cood,y_cood+1)==1)
    {
    	is_visited[x_cood][y_cood+1]=1;
    	if(points[x_cood][y_cood+1].distance> points[x_cood][y_cood].distance+1)
    	{
    		points[x_cood][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood+1,a.distance=points[x_cood][y_cood+1].distance;

    		pq.push(a);
    	}
    }

    if( is_visited[x_cood+1][y_cood]==0 && img.at<char>(x_cood+1,y_cood)==0 && check_point(x_cood+1,y_cood)==1)
    {
    	is_visited[x_cood+1][y_cood]=1;
    	if(points[x_cood+1][y_cood].distance> points[x_cood][y_cood].distance+1)
    	{
    		points[x_cood+1][y_cood].distance=points[x_cood][y_cood].distance+1;


              point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood,a.distance=points[x_cood+1][y_cood].distance;

    		pq.push(a);
    	}
    }


    if( is_visited[x_cood+1][y_cood+1]==0 && img.at<char>(x_cood+1,y_cood+1)==0 && check_point(x_cood+1,y_cood+1)==1)
    {
    	is_visited[x_cood+1][y_cood+1]=1;
    	if(points[x_cood+1][y_cood+1].distance> points[x_cood][y_cood].distance+ sqrt(2))
    	{
    		points[x_cood+1][y_cood+1].distance=points[x_cood][y_cood].distance+sqrt(2);

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood+1,a.distance=points[x_cood+1][y_cood+1].distance;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood-1][y_cood+1]==0 && img.at<char>(x_cood-1,y_cood+1)==0 && check_point(x_cood-1,y_cood+1)==1)
    {
    	is_visited[x_cood-1][y_cood+1]=1;
    	if(points[x_cood-1][y_cood+1].distance> points[x_cood][y_cood].distance+sqrt(2))
    	{
    		points[x_cood-1][y_cood+1].distance=points[x_cood][y_cood].distance+sqrt(2);

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood+1,a.distance=points[x_cood-1][y_cood+1].distance;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood-1][y_cood-1]==0 && img.at<char>(x_cood-1,y_cood-1)==0 && check_point(x_cood-1,y_cood-1)==1)
    {
    	is_visited[x_cood-1][y_cood-1]=1;
    	if(points[x_cood-1][y_cood-1].distance> points[x_cood][y_cood].distance+sqrt(2))
    	{
    		points[x_cood-1][y_cood-1].distance=points[x_cood][y_cood].distance+sqrt(2);

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood-1,a.distance=points[x_cood-1][y_cood-1].distance;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood-1][y_cood]==0 && img.at<char>(x_cood-1,y_cood)==0 && check_point(x_cood-1,y_cood)==1)
    {
    	is_visited[x_cood-1][y_cood]=1;
    	if(points[x_cood-1][y_cood].distance> points[x_cood][y_cood].distance+1)
    	{
    		points[x_cood-1][y_cood].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood,a.distance=points[x_cood-1][y_cood].distance;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood+1][y_cood-1]==0 && img.at<char>(x_cood+1,y_cood-1)==0 && check_point(x_cood+1,y_cood-1)==1)
    {
    	is_visited[x_cood+1][y_cood-1]=1;
    	if(points[x_cood+1][y_cood-1].distance> points[x_cood][y_cood].distance+sqrt(2))
    	{
    		points[x_cood+1][y_cood-1].distance=points[x_cood][y_cood].distance+sqrt(2);

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood-1,a.distance=points[x_cood+1][y_cood-1].distance;

    		pq.push(a);
    	}
    }


if( is_visited[x_cood][y_cood-1]==0 && img.at<char>(x_cood,y_cood-1)==0 && check_point(x_cood,y_cood-1)==1)
    {
    	is_visited[x_cood][y_cood-1]=1;
    	if(points[x_cood][y_cood-1].distance> points[x_cood][y_cood].distance+1)
    	{
    		points[x_cood][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood-1,a.distance=points[x_cood][y_cood-1].distance;

    		pq.push(a);
    	}
    }

point1 temp=pq.top();
pq.pop();

int r=temp.point_x;
int c=temp.point_y;

ax.at<uchar>(r,c)=255;

namedWindow("window",WINDOW_NORMAL);
imshow("window",ax);
waitKey(1);
}


}	
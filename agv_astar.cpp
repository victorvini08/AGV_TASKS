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
    int parent_x;
    int parent_y; 

	
     
 
};

Mat img=imread("/home/aryan/Downloads/Test1.png",1);

//Mat img(60,100,CV_8UC1,Scalar(0));

struct compare_distance{


    bool operator()(  point1 const& p1,  point1 const& p2) 
    { 
         
        return p1.distance > p2.distance; 
    } 
};
 

int x=img.rows,y=img.cols;
Mat ax(x,y,CV_8UC1,Scalar(0));
Mat path(x,y,CV_8UC1,Scalar(0));




int check_point(int i,int j)
{
  if(i>=0 && j>=0 && i<x && j<y)
    return 1;
  else
    return 0;
}




 struct point1 points[1000][1000];
 int is_visited[1000][1000];

int r,c,aa,bb;


void print_path(struct point1 ps[1000][1000],int dx, int dy)
{
   if(ps[dx][dy].parent_x==-1 && ps[dx][dy].parent_y==-1)
    return;
   else
   {
          img.at<uchar>(dx,dy)=255;
       namedWindow("window",0);
imshow("window",img);
       waitKey(1);
       print_path(ps,ps[dx][dy].parent_x,ps[dx][dy].parent_y);
   }
}

int main()
{

priority_queue<point1, vector<point1>, compare_distance> pq; 

point1 a;

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            if(img.at<Vec3b>(i,j)[0]<50 &&  img.at<Vec3b>(i,j)[2]<50 && img.at<Vec3b>(i,j)[1]>200)
            {
                 a.point_y=j,a.point_x=i,a.distance=0;
                 //cout<<a.point_y<<a.point_x<<endl;
                 aa=i;
                 bb=j;
                 break;

            }

            if(img.at<Vec3b>(i,j)[0]<50 &&  img.at<Vec3b>(i,j)[1]<50 && img.at<Vec3b>(i,j)[2]>200)
            {
                      r=i;
                      c=j;
                      break;
            }
        }
    }

 for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
    
points[i][j].parent_x=-1;
points[i][j].parent_y=-1;
}
}

 pq.push(a) ; 

cvtColor(img,img,CV_BGR2GRAY); 


for(int i=0;i<x;i++)
{
	for(int j=0;j<y;j++)
	{
		if(img.at<uchar>(i,j)>200)
		{
			img.at<uchar>(i,j)=255;
		}
		else if(img.at<uchar>(i,j)<200)
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

is_visited[aa][bb]=1;
points[aa][bb].distance=0;


printf("happy");
cout<<"destination"<<endl;
cout<<x<<y;
namedWindow("window1",0);
imshow("window1",img);
waitKey(5000);

while(!(pq.top().point_x==r && pq.top().point_y==c))
{
	
    point1 p=pq.top();
    int x_cood=p.point_x;
    int y_cood=p.point_y;
    cout<<x_cood<<endl<<y_cood<<endl;
    int d=points[x_cood][y_cood].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c)*(y_cood-c));

    if( is_visited[x_cood][y_cood+1]==0 && img.at<char>(x_cood,y_cood+1)==0 && check_point(x_cood,y_cood+1)==1)
    {
    //	is_visited[x_cood][y_cood+1]=1;
    	if(points[x_cood][y_cood+1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c+1)*(y_cood-c+1))> d+1)
    	{
    		points[x_cood][y_cood+1].distance=points[x_cood][y_cood].distance+1;
        is_visited[x_cood][y_cood+1]=1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood+1,a.distance=points[x_cood][y_cood+1].distance;
            points[x_cood][y_cood+1].parent_x=x_cood;
            points[x_cood][y_cood+1].parent_y=y_cood;

    		pq.push(a);
    	}
    }

    if( is_visited[x_cood+1][y_cood]==0 && img.at<char>(x_cood+1,y_cood)==0 && check_point(x_cood+1,y_cood)==1)
    {
    	//is_visited[x_cood+1][y_cood]=1;
    	if(points[x_cood+1][y_cood].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c)*(y_cood-c))> d+1)
    	{
    		points[x_cood+1][y_cood].distance=points[x_cood][y_cood].distance+1;
            is_visited[x_cood+1][y_cood]=1;

              point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood,a.distance=points[x_cood+1][y_cood].distance;

            points[x_cood+1][y_cood].parent_x=x_cood;
            points[x_cood+1][y_cood].parent_y=y_cood;

    		pq.push(a);
    	}
    }


    if( is_visited[x_cood+1][y_cood+1]==0 && img.at<char>(x_cood+1,y_cood+1)==0 && check_point(x_cood+1,y_cood+1)==1)
    {
    	//is_visited[x_cood+1][y_cood+1]=1;
    	if(points[x_cood+1][y_cood+1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c+1)*(y_cood-c+1))> d+ sqrt(2))
    	{
    		points[x_cood+1][y_cood+1].distance=points[x_cood][y_cood].distance+sqrt(2);
            is_visited[x_cood+1][y_cood+1]=1;
            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood+1,a.distance=points[x_cood+1][y_cood+1].distance;

            points[x_cood+1][y_cood+1].parent_x=x_cood;
            points[x_cood+1][y_cood+1].parent_y=y_cood;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood-1][y_cood+1]==0 && img.at<char>(x_cood-1,y_cood+1)==0 && check_point(x_cood-1,y_cood+1)==1)
    {
    	//is_visited[x_cood-1][y_cood+1]=1;
    	if(points[x_cood-1][y_cood+1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c+1)*(y_cood-c+1))> d+sqrt(2))
    	{
    		points[x_cood-1][y_cood+1].distance=points[x_cood][y_cood].distance+sqrt(2);
            is_visited[x_cood-1][y_cood+1]=1;
            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood+1,a.distance=points[x_cood-1][y_cood+1].distance;

            points[x_cood-1][y_cood+1].parent_x=x_cood;
            points[x_cood-1][y_cood+1].parent_y=y_cood;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood-1][y_cood-1]==0 && img.at<char>(x_cood-1,y_cood-1)==0 && check_point(x_cood-1,y_cood-1)==1)
    {
    	//is_visited[x_cood-1][y_cood-1]=1;
    	if(points[x_cood-1][y_cood-1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c-1)*(y_cood-c-1))> d+sqrt(2))
    	{
    		points[x_cood-1][y_cood-1].distance=points[x_cood][y_cood].distance+sqrt(2);
             is_visited[x_cood-1][y_cood-1]=1;
            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood-1,a.distance=points[x_cood-1][y_cood-1].distance;

            points[x_cood-1][y_cood-1].parent_x=x_cood;
            points[x_cood-1][y_cood-1].parent_y=y_cood;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood-1][y_cood]==0 && img.at<char>(x_cood-1,y_cood)==0 && check_point(x_cood-1,y_cood)==1)
    {
    	//is_visited[x_cood-1][y_cood]=1;
    	if(points[x_cood-1][y_cood].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c)*(y_cood-c))> d+1)
    	{
    		points[x_cood-1][y_cood].distance=points[x_cood][y_cood].distance+1;
                    is_visited[x_cood-1][y_cood]=1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood,a.distance=points[x_cood-1][y_cood].distance;

            points[x_cood-1][y_cood].parent_x=x_cood;
            points[x_cood-1][y_cood].parent_y=y_cood;

    		pq.push(a);
    	}
    }

if( is_visited[x_cood+1][y_cood-1]==0 && img.at<char>(x_cood+1,y_cood-1)==0 && check_point(x_cood+1,y_cood-1)==1)
    {
    	//is_visited[x_cood+1][y_cood-1]=1;
    	if(points[x_cood+1][y_cood-1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c-1)*(y_cood-c-1))>d+sqrt(2))
    	{
    		points[x_cood+1][y_cood-1].distance=points[x_cood][y_cood].distance+sqrt(2);
             is_visited[x_cood+1][y_cood-1]=1;
            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood-1,a.distance=points[x_cood+1][y_cood-1].distance;

            points[x_cood+1][y_cood-1].parent_x=x_cood;
            points[x_cood+1][y_cood-1].parent_y=y_cood;

    		pq.push(a);
    	}
    }


if( is_visited[x_cood][y_cood-1]==0 && img.at<char>(x_cood,y_cood-1)==0 && check_point(x_cood,y_cood-1)==1)
    {
    	//is_visited[x_cood][y_cood-1]=1;
    	if(points[x_cood][y_cood-1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-1-c)*(y_cood-c-1))> d+1)
    	{
    		points[x_cood][y_cood-1].distance=points[x_cood][y_cood].distance+1;
            is_visited[x_cood][y_cood-1]=1;
            point1 a;
            a.point_x=x_cood,a.point_y=y_cood-1,a.distance=points[x_cood][y_cood-1].distance;

            points[x_cood][y_cood-1].parent_x=x_cood;
            points[x_cood][y_cood-1].parent_y=y_cood;

    		pq.push(a);
    	}
    }

point1 temp=pq.top();
pq.pop();

/*int rr=temp.point_x;
int cc=temp.point_y;

ax.at<uchar>(rr,cc)=255;

namedWindow("window",0);
imshow("window",ax);



waitKey(1);*/
}

print_path(points,r,c);
cout<<pq.size()<<endl;

waitKey(0);


}	
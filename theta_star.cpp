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

int length,breadth;
int eee,fff;

int ma=0;
struct point1
{




    int point_x;
    int point_y;
    float distance;
    int parent_y;
    int parent_x;

    
     
 
};
int n=0;
Mat img=imread("/home/aryan/Downloads/Test2.png",1);
Mat path=imread("/home/aryan/Downloads/Test2.png",1);
//Mat img(60,100,CV_8UC1,Scalar(0));

struct compare_distance{


    bool operator()(  point1 const& p1,  point1 const& p2) 
    { 
         
        return p1.distance > p2.distance; 
    } 
};
 

int x=img.rows,y=img.cols;






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



int check_validity_1(point1 p, point1 q)
{
  point1 large, small;
  int i = 0, j1 = 0, j2 = 0;
  double slope;
  if(q.point_x<p.point_x)
  {
    small = q;
    large = p;
  }
  else
  {
    small = p;
    large = q;
  }
  if(large.point_x == small.point_x)
    return 0;
  slope = ((double)large.point_y - small.point_y)/((double)large.point_x - small.point_x);
  for(i=small.point_x+1; i<large.point_x; i++)
  {
    j1 = (int)((i*slope) - (small.point_x)*(slope) + small.point_y);
    j2 = j1 + 1;
    if((i<0) || (i>r) || (j1<0) || (j1>c) || (j2<0) || (j2>c))
      continue;
    if(((int)path.at<Vec3b>(i, j1)[0] >50) && ((int)path.at<Vec3b>(i, j1)[1] > 50) && ((int)path.at<Vec3b>(i, j1)[2] > 50))
     return 0;
     if(((int)path.at<Vec3b>(i, j2)[0] >50) && ((int)path.at<Vec3b>(i, j2)[1] >50) && ((int)path.at<Vec3b>(i, j2)[2] >50))
      return 0;
  }
  return 1;
}
int check_validity_2(point1 p,point1 q)
{
  point1 large, small;
  int i = 0, j1 = 0, j2 = 0;
  double slope;
  if(q.point_y<p.point_y)
  {
    small = q;
    large = p;
  }
  else
  {
    small = p;
    large = q;
  }
  if(large.point_x == small.point_x)
    return 0;
  slope = ((double)large.point_y - small.point_y)/((double)large.point_x - small.point_x);
  for(i=small.point_y+1; i<large.point_y; i++)
  {
    j1 = (int)(((i - small.point_y)/slope) + small.point_x);
    j2 = j1 + 1;
    if((i<0) || (i>r) || (j1<0) || (j1>c) || (j2<0) || (j2>c))
      continue;
    if(((int)path.at<Vec3b>(j1, i)[0] >50) && ((int)path.at<Vec3b>(j1, i)[1] >50) && ((int)path.at<Vec3b>(j1, i)[2] >50))
     return 0;
     if(((int)path.at<Vec3b>(j2, i)[0] >50) && ((int)path.at<Vec3b>(j2, i)[1] >50) && ((int)path.at<Vec3b>(j2, i)[2] >50))
      return 0;
  }
  return 1;
}
void print_path(struct point1 ps[1000][1000],int dx, int dy)
{
   ma++;
   cout<<ma<<endl;
   if(ps[dx][dy].parent_x==-1 && ps[dx][dy].parent_y==-1)
    return;
   else
   {
       path.at<Vec3b>(dx,dy)={0,0,255};
    


/*rectangle( path, 
           cvPoint(dy-(length*0.5),dx-(0.5*breadth)),
          cvPoint(dy+0.5*length,dx+0.5*breadth),
           CV_RGB(0,0,255), 1, 8
             );

*/

waitKey(10);
   namedWindow("window",0);
imshow("window",path);



/*rectangle( path, 
           cvPoint(dy-(length*0.5),dx-(0.5*breadth)),
          cvPoint(dy+0.5*length,dx+0.5*breadth),
           CV_RGB(0,0,0), 1, 8
             );*/
path.at<Vec3b>(dx,dy)={0,0,255};

       
       print_path(ps,ps[dx][dy].parent_x,ps[dx][dy].parent_y);

   }
}

int main()
{


printf("Enter rectangle length and breadth:");
scanf("%d%d",&length,&breadth);

priority_queue<point1, vector<point1>, compare_distance> pq; 

point1 a;

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            if(img.at<Vec3b>(i,j)[0]<50 &&  img.at<Vec3b>(i,j)[2]<50 && img.at<Vec3b>(i,j)[1]>200)
            {
                 a.point_y=j,a.point_x=i,a.distance=0;
                 cout<<a.point_y<<a.point_x<<endl;
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


    

for(int i=0;i<r;i++)
{
    for(int j=0;j<c;j++)
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

  

while(!( pq.empty())) 
{
     
	
    point1 p=pq.top();
    int x_cood=p.point_x;
    int y_cood=p.point_y;
    //printf("%d  %d",x_cood,y_cood);
    int d=points[x_cood][y_cood].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c)*(y_cood-c));

    if( is_visited[x_cood][y_cood+1]==0)
    {
    	
        if(img.at<uchar>(int(x_cood+breadth),int(y_cood+1+length))==0 &&  img.at<uchar>(int(x_cood-breadth),(y_cood+1+length))==0 &&  img.at<uchar>(int(x_cood+breadth),int(y_cood+1-length))==0 &&  img.at<uchar>(int(x_cood-breadth),int(y_cood+1-length))==0 && check_point(int(x_cood+breadth),int(y_cood+1+length))==1 && check_point(int(x_cood-breadth),(y_cood+1+length))==1 && check_point(int(x_cood+breadth),int(y_cood+1-length))==1 && check_point(int(x_cood-breadth),int(y_cood+1-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood][y_cood+1]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood][y_cood+1]))
            {

        if(points[x_cood][y_cood+1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c+1)*(y_cood-c+1))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood][y_cood+1]=1;
            points[x_cood][y_cood+1].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood+1,a.distance=points[x_cood][y_cood+1].distance;
             points[x_cood][y_cood+1].parent_x=p.parent_x;
            points[x_cood][y_cood+1].parent_y=p.parent_y;

            pq.push(a);
        }
            
    }
        else if(points[x_cood][y_cood+1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c+1)*(y_cood-c+1))> d+1)
        {
            is_visited[x_cood][y_cood+1]=1;
            points[x_cood][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood+1,a.distance=points[x_cood][y_cood+1].distance;
             points[x_cood][y_cood+1].parent_x=x_cood;
            points[x_cood][y_cood+1].parent_y=y_cood;

            pq.push(a);
        }
            }

        
    	
    }

  
    if( is_visited[x_cood+1][y_cood+1]==0)
    {
        
        if(img.at<uchar>(int(x_cood+breadth+1),int(y_cood+1+length))==0 &&  img.at<uchar>(int(x_cood-breadth+1),(y_cood+1+length))==0 &&  img.at<uchar>(int(x_cood+breadth+1),int(y_cood+1-length))==0 &&  img.at<uchar>(int(x_cood-breadth+1),int(y_cood+1-length))==0 && check_point(int(x_cood+breadth+1),int(y_cood+1+length))==1 && check_point(int(x_cood-breadth+1),(y_cood+1+length))==1 && check_point(int(x_cood+breadth+1),int(y_cood+1-length))==1 && check_point(int(x_cood-breadth+1),int(y_cood+1-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood+1][y_cood+1]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood+1][y_cood+1]))
            {

        if(points[x_cood+1][y_cood+1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c+1)*(y_cood-c+1))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood+1][y_cood+1]=1;
            points[x_cood+1][y_cood+1].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood+1,a.distance=points[x_cood+1][y_cood+1].distance;
             points[x_cood+1][y_cood+1].parent_x=p.parent_x;
            points[x_cood+1][y_cood+1].parent_y=p.parent_y;

            pq.push(a);
        }

    
          }
        else if(points[x_cood+1][y_cood+1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c+1)*(y_cood-c+1))> d+1)
        {
            is_visited[x_cood+1][y_cood+1]=1;
            points[x_cood+1][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood+1,a.distance=points[x_cood+1][y_cood+1].distance;
             points[x_cood+1][y_cood+1].parent_x=x_cood;
            points[x_cood+1][y_cood+1].parent_y=y_cood;

            pq.push(a);
        }
            

        }
        
    }

  
   
  
    if( is_visited[x_cood-1][y_cood-1]==0)
    {
        
        if(img.at<uchar>(int(x_cood+breadth-1),int(y_cood-1+length))==0 &&  img.at<uchar>(int(x_cood-breadth-1),(y_cood-1+length))==0 &&  img.at<uchar>(int(x_cood+breadth-1),int(y_cood-1-length))==0 &&  img.at<uchar>(int(x_cood-breadth-1),int(y_cood-1-length))==0 && check_point(int(x_cood+breadth-1),int(y_cood-1+length))==1 && check_point(int(x_cood-breadth-1),(y_cood-1+length))==1 && check_point(int(x_cood+breadth-1),int(y_cood-1-length))==1 && check_point(int(x_cood-breadth-1),int(y_cood-1-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood-1][y_cood-1]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood-1][y_cood-1]))
            {

        if(points[x_cood-1][y_cood-1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c-1)*(y_cood-c-1))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood-1][y_cood-1]=1;
            points[x_cood-1][y_cood-1].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood-1,a.distance=points[x_cood-1][y_cood-1].distance;
             points[x_cood-1][y_cood-1].parent_x=p.parent_x;
            points[x_cood-1][y_cood-1].parent_y=p.parent_y;

            pq.push(a);
        }
}
        else if(points[x_cood-1][y_cood-1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c-1)*(y_cood-c-1))> d+1)
        {
            is_visited[x_cood-1][y_cood-1]=1;
            points[x_cood-1][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood-1,a.distance=points[x_cood-1][y_cood-1].distance;
             points[x_cood-1][y_cood-1].parent_x=x_cood;
            points[x_cood-1][y_cood-1].parent_y=y_cood;

            pq.push(a);
        }
            }

        
        
    }

  
  
    if( is_visited[x_cood-1][y_cood+1]==0)
    {
        
        if(img.at<uchar>(int(x_cood+breadth-1),int(y_cood+1+length))==0 &&  img.at<uchar>(int(x_cood-breadth-1),(y_cood+1+length))==0 &&  img.at<uchar>(int(x_cood+breadth-1),int(y_cood+1-length))==0 &&  img.at<uchar>(int(x_cood-breadth-1),int(y_cood+1-length))==0 && check_point(int(x_cood+breadth-1),int(y_cood+1+length))==1 && check_point(int(x_cood-breadth-1),(y_cood+1+length))==1 && check_point(int(x_cood+breadth-1),int(y_cood+1-length))==1 && check_point(int(x_cood-breadth-1),int(y_cood+1-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood-1][y_cood+1]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood-1][y_cood+1]))
            {

        if(points[x_cood-1][y_cood+1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c+1)*(y_cood-c+1))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood-1][y_cood+1]=1;
            points[x_cood-1][y_cood+1].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood+1,a.distance=points[x_cood-1][y_cood+1].distance;
             points[x_cood-1][y_cood+1].parent_x=p.parent_x;
            points[x_cood-1][y_cood+1].parent_y=p.parent_y;

            pq.push(a);
        }
}
        else if(points[x_cood-1][y_cood+1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c+1)*(y_cood-c+1))> d+1)
        {
            is_visited[x_cood-1][y_cood+1]=1;
            points[x_cood-1][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood+1,a.distance=points[x_cood-1][y_cood+1].distance;
             points[x_cood-1][y_cood+1].parent_x=x_cood;
            points[x_cood-1][y_cood+1].parent_y=y_cood;

            pq.push(a);
        }
            }

        
        
    }
  
   
  
    if( is_visited[x_cood+1][y_cood-1]==0)
    {
        
        if(img.at<uchar>(int(x_cood+breadth+1),int(y_cood-1+length))==0 &&  img.at<uchar>(int(x_cood-breadth+1),(y_cood-1+length))==0 &&  img.at<uchar>(int(x_cood+breadth+1),int(y_cood-1-length))==0 &&  img.at<uchar>(int(x_cood-breadth+1),int(y_cood-1-length))==0 && check_point(int(x_cood+breadth+1),int(y_cood-1+length))==1 && check_point(int(x_cood-breadth+1),(y_cood-1+length))==1 && check_point(int(x_cood+breadth+1),int(y_cood-1-length))==1 && check_point(int(x_cood-breadth+1),int(y_cood-1-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood+1][y_cood-1]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood+1][y_cood-1]))
            {

        if(points[x_cood+1][y_cood-1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c-1)*(y_cood-c-1))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood+1][y_cood-1]=1;
            points[x_cood+1][y_cood-1].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood-1,a.distance=points[x_cood+1][y_cood-1].distance;
             points[x_cood+1][y_cood-1].parent_x=p.parent_x;
            points[x_cood+1][y_cood-1].parent_y=p.parent_y;

            pq.push(a);

        }

    
           }
        else if(points[x_cood+1][y_cood-1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c-1)*(y_cood-c-1))> d+1)
        {
            is_visited[x_cood+1][y_cood-1]=1;
            points[x_cood+1][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood-1,a.distance=points[x_cood+1][y_cood-1].distance;
             points[x_cood+1][y_cood-1].parent_x=x_cood;
            points[x_cood+1][y_cood-1].parent_y=y_cood;

            pq.push(a);
        }
            

        }
        
    }
     if( is_visited[x_cood][y_cood-1]==0 )
    {
        
        if(img.at<uchar>(int(x_cood+breadth),int(y_cood-1+length))==0 &&  img.at<uchar>(int(x_cood-breadth),(y_cood-1+length))==0 &&  img.at<uchar>(int(x_cood+breadth),int(y_cood-1-length))==0 &&  img.at<uchar>(int(x_cood-breadth),int(y_cood-1-length))==0 && check_point(int(x_cood+breadth),int(y_cood-1+length))==1 && check_point(int(x_cood-breadth),(y_cood-1+length))==1 && check_point(int(x_cood+breadth),int(y_cood-1-length))==1 && check_point(int(x_cood-breadth),int(y_cood-1-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood][y_cood-1]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood][y_cood-1]))
            {

        if(points[x_cood][y_cood-1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c-1)*(y_cood-c-1))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood][y_cood-1]=1;
            points[x_cood][y_cood-1].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood-1,a.distance=points[x_cood][y_cood-1].distance;
             points[x_cood][y_cood-1].parent_x=p.parent_x;
            points[x_cood][y_cood-1].parent_y=p.parent_y;

            pq.push(a);
        }

    }
        else if(points[x_cood][y_cood-1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c-1)*(y_cood-c-1))> d+1)
        {
            is_visited[x_cood][y_cood-1]=1;
            points[x_cood][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood-1,a.distance=points[x_cood][y_cood-1].distance;
             points[x_cood][y_cood-1].parent_x=x_cood;
            points[x_cood][y_cood-1].parent_y=y_cood;

            pq.push(a);
        }
            

        }
        
    }

   if( is_visited[x_cood-1][y_cood]==0)
    {
        
        if(img.at<uchar>(int(x_cood+breadth-1),int(y_cood+length))==0 &&  img.at<uchar>(int(x_cood-1-breadth),(y_cood+length))==0 &&  img.at<uchar>(int(x_cood-1+breadth),int(y_cood-length))==0 &&  img.at<uchar>(int(x_cood-1-breadth),int(y_cood-length))==0 && check_point(int(x_cood-1+breadth),int(y_cood+length))==1 && check_point(int(x_cood-1-breadth),(y_cood+length))==1 && check_point(int(x_cood-1+breadth),int(y_cood-length))==1 && check_point(int(x_cood-1-breadth),int(y_cood-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood-1][y_cood]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood-1][y_cood]))
            {

        if(points[x_cood-1][y_cood].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c)*(y_cood-c))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood-1][y_cood]=1;
            points[x_cood-1][y_cood].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood,a.distance=points[x_cood-1][y_cood].distance;
             points[x_cood-1][y_cood].parent_x=p.parent_x;
            points[x_cood-1][y_cood].parent_y=p.parent_y;

            pq.push(a);
        }

   }
        else if(points[x_cood-1][y_cood].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c)*(y_cood-c))> d+1)
        {
            is_visited[x_cood-1][y_cood]=1;
            points[x_cood-1][y_cood].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood,a.distance=points[x_cood-1][y_cood].distance;
             points[x_cood-1][y_cood].parent_x=x_cood;
            points[x_cood-1][y_cood].parent_y=y_cood;

            pq.push(a);
        }
            }

        
        
    }
   if( is_visited[x_cood+1][y_cood]==0)
    {
        
        if(img.at<uchar>(int(x_cood+breadth+1),int(y_cood+length))==0 &&  img.at<uchar>(int(x_cood-breadth+1),(y_cood+length))==0 &&  img.at<uchar>(int(x_cood+breadth+1),int(y_cood-length))==0 &&  img.at<uchar>(int(x_cood-breadth+1),int(y_cood-length))==0 && check_point(int(x_cood+breadth+1),int(y_cood+length))==1 && check_point(int(x_cood-breadth+1),(y_cood+length))==1 && check_point(int(x_cood+breadth+1),int(y_cood-length))==1 && check_point(int(x_cood-breadth+1),int(y_cood-length))==1)
        {

            if(check_validity_2(points[p.parent_x][p.parent_y],points[x_cood+1][y_cood]) && check_validity_1(points[p.parent_x][p.parent_y],points[x_cood+1][y_cood]))
            {

        if(points[x_cood+1][y_cood].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c)*(y_cood-c))> points[p.parent_x][p.parent_y].distance+sqrt((p.parent_x-r)*(p.parent_x-r)+(p.parent_y-c)*(p.parent_y-c))+1)
        {
            is_visited[x_cood+1][y_cood]=1;
            points[x_cood+1][y_cood].distance=points[p.parent_x][p.parent_y].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood,a.distance=points[x_cood+1][y_cood].distance;
             points[x_cood+1][y_cood].parent_x=p.parent_x;
            points[x_cood+1][y_cood].parent_y=p.parent_y;

            pq.push(a);

        }

    
            }
        else if(points[x_cood+1][y_cood].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c)*(y_cood-c))> d+1)
        {
            is_visited[x_cood+1][y_cood]=1;
            points[x_cood+1][y_cood].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood,a.distance=points[x_cood+1][y_cood].distance;
             points[x_cood+1][y_cood].parent_x=x_cood;
            points[x_cood+1][y_cood].parent_y=y_cood;

            pq.push(a);
        }
            

        }
        
    }
point1 temp=pq.top();

//if(pq.size()!=1)
//{
pq.pop();
//}

//cout<<temp.parent_x<<endl<<temp.parent_y<<endl;

//print_path(points,r,c);
eee=temp.point_x;
fff=temp.point_y;
cout<<pq.size()<<endl;

}
cout<<"hello"<<endl;
print_path(points,r,c);
cout<<"hello"<<endl;





waitKey(0);

}	
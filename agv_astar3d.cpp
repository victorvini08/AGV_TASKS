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
#define pi CV_PI

int length,breadth;
int eee,fff;

int corner[4][2];
struct point1
{




    int point_x;
    int point_y;
    float distance;
    int parent_y;
    int parent_x;
    float theta;

    
     
 
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




   void calculateCorners(int y,int x,int rectHeight,int rectWidth,int rotation){

    
  
    float rectDiag = sqrt((rectWidth/2)*(rectWidth/2) + (rectHeight/2)*(rectHeight/2));
    float rectAngle = atan2(rectHeight/2, rectWidth/2);
   
    // cx1 cy1
    corner[0][1] = x + -rectDiag * cos(-rectAngle + rotation);
    corner[0][0] = y + -rectDiag * sin(-rectAngle + rotation);
   
    // cx2 cy2
    corner[1][1] = x + rectDiag * cos(rectAngle + rotation*pi);
    corner[1][0] = y + rectDiag * sin(rectAngle + rotation*pi);
   
    // cx3 cy3
    corner[2][1] = x + rectDiag * cos(-rectAngle + rotation*pi);
    corner[2][0] = y + rectDiag * sin(-rectAngle + rotation*pi);
   
    // cx4 cy4
    corner[3][1] = x + -rectDiag * cos(rectAngle + rotation*pi);
    corner[3][0] = y + -rectDiag * sin(rectAngle + rotation*pi);

    
 
  }





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


void print_path(struct point1 ps[1000][1000],int dx, int dy,int l,int b)
{  
    Point p=Point(dy,dx);

    cv::RotatedRect rotatedRectangle(p,Size(b,l),ps[dx][dy].theta);

     cv::Point2f vertices2f[4];
    rotatedRectangle.points(vertices2f);


    cv::Point vertices[4];    
    for(int i = 0; i < 4; ++i){
        vertices[i] = vertices2f[i];
    }

  
   


   if(ps[dx][dy].parent_x==-1 && ps[dx][dy].parent_y==-1)
    return;
   else
   {
       path.at<Vec3b>(dx,dy)={0,0,255};

/*        cv::fillConvexPoly(path,
                       vertices,
                       4,
                       Scalar(0,0,255));

*/
waitKey(10);
   namedWindow("window",0);
imshow("window",path);


path.at<Vec3b>(dx,dy)={0,0,255};

/*        cv::fillConvexPoly(path,
                       vertices,
                       4,
                       Scalar(0,0,0));
*/
       
       print_path(ps,ps[dx][dy].parent_x,ps[dx][dy].parent_y,l,b);

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


    


    
points[aa][bb].parent_x=-1;
points[aa][bb].parent_y=-1;


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

  

while(!(pq.top().point_x==r && pq.top().point_y==c)) 
{
     
	
    point1 p=pq.top();
    int x_cood=p.point_x;
    int y_cood=p.point_y;
    //printf("%d  %d",x_cood,y_cood);
    int d=points[x_cood][y_cood].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c)*(y_cood-c));

    for(int the=0;the<=180;the+=10)
    {

    if( is_visited[x_cood][y_cood+1]==0)
    {
        int temp=1;
        calculateCorners(x_cood,y_cood+1,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            for(int i=x_cood-(breadth/2);i<=x_cood+breadth/2;i++)
            {
                for(int j=y_cood+1-(length/2);j<=y_cood+1+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp)
            {
                    if(points[x_cood][y_cood+1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c+1)*(y_cood-c+1))> d+1)
        {
           

            is_visited[x_cood][y_cood+1]=1;

            points[x_cood][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood+1,a.distance=points[x_cood][y_cood+1].distance;
             points[x_cood][y_cood+1].parent_x=x_cood;
            points[x_cood][y_cood+1].parent_y=y_cood;
                        points[x_cood][y_cood+1].theta=the;



            pq.push(a);

        }

            }
        }
    }
    	
    	
 if( is_visited[x_cood+1][y_cood]==0)
    {
        int temp=1;
        calculateCorners(x_cood+1,y_cood,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            
            for(int i=x_cood+1-(breadth/2);i<=x_cood+1+breadth/2;i++)
            {
                for(int j=y_cood-(length/2);j<=y_cood+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp  )
            {
                    if(points[x_cood+1][y_cood].distance+sqrt((x_cood+1-r)*(x_cood+1-r)+(y_cood-c)*(y_cood-c))> d+1)
        {
           

            is_visited[x_cood+1][y_cood]=1;

            points[x_cood+1][y_cood].distance=points[x_cood+1][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood,a.distance=points[x_cood+1][y_cood].distance;
             points[x_cood+1][y_cood].parent_x=x_cood;
            points[x_cood+1][y_cood+1].parent_y=y_cood;
                        points[x_cood+1][y_cood].theta=the;



            pq.push(a);
            
        }

            }
        }
    }
        


 if( is_visited[x_cood-1][y_cood+1]==0)
    {
        int temp=1;
        calculateCorners(x_cood-1,y_cood+1,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            
            for(int i=x_cood-1-(breadth/2);i<=x_cood-1+breadth/2;i++)
            {
                for(int j=y_cood+1-(length/2);j<=y_cood+1+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp  )
            {
                    if(points[x_cood-1][y_cood+1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c+1)*(y_cood-c+1))> d+1)
        {
           

            is_visited[x_cood-1][y_cood+1]=1;

            points[x_cood-1][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood+1,a.distance=points[x_cood-1][y_cood+1].distance;
             points[x_cood-1][y_cood+1].parent_x=x_cood;
            points[x_cood-1][y_cood+1].parent_y=y_cood;
                        points[x_cood-1][y_cood+1].theta=the;



            pq.push(a);
            
        }

            }
        }
    }
        


    if( is_visited[x_cood][y_cood-1]==0)
    {
        int temp=1;
        calculateCorners(x_cood,y_cood-1,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            for(int i=x_cood-(breadth/2);i<=x_cood+breadth/2;i++)
            {
                for(int j=y_cood-1-(length/2);j<=y_cood-1+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp )
            {
                    if(points[x_cood][y_cood-1].distance+sqrt((x_cood-r)*(x_cood-r)+(y_cood-c-1)*(y_cood-c-1))> d+1)
        {
           

            is_visited[x_cood][y_cood-1]=1;

            points[x_cood][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood,a.point_y=y_cood-1,a.distance=points[x_cood][y_cood-1].distance;
             points[x_cood][y_cood-1].parent_x=x_cood;
            points[x_cood][y_cood-1].parent_y=y_cood;
                        points[x_cood][y_cood-1].theta=the;



            pq.push(a);
            
        }

            }
        }
    }
        


    if( is_visited[x_cood-1][y_cood-1]==0)
    {
        int temp=1;
        calculateCorners(x_cood-1,y_cood-1,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            
            for(int i=x_cood-1-(breadth/2);i<=x_cood-1+breadth/2;i++)
            {
                for(int j=y_cood-1-(length/2);j<=y_cood-1+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp  )
            {
                    if(points[x_cood-1][y_cood-1].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c-1)*(y_cood-c-1))> d+1)
        {
           

            is_visited[x_cood-1][y_cood-1]=1;

            points[x_cood-1][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood-1,a.distance=points[x_cood-1][y_cood-1].distance;
             points[x_cood-1][y_cood-1].parent_x=x_cood;
            points[x_cood-1][y_cood-1].parent_y=y_cood;
                        points[x_cood-1][y_cood-1].theta=the;



            pq.push(a);
            
        }

            }
        }
    }
        


    if( is_visited[x_cood+1][y_cood+1]==0)
    {
        int temp=1;
        calculateCorners(x_cood+1,y_cood+1,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            
            for(int i=x_cood+1-(breadth/2);i<=x_cood+1+breadth/2;i++)
            {
                for(int j=y_cood+1-(length/2);j<=y_cood+1+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp  )
            {
                    if(points[x_cood+1][y_cood+1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c+1)*(y_cood-c+1))> d+1)
        {
           

            is_visited[x_cood+1][y_cood+1]=1;

            points[x_cood+1][y_cood+1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood+1,a.distance=points[x_cood+1][y_cood+1].distance;
             points[x_cood+1][y_cood+1].parent_x=x_cood;
            points[x_cood+1][y_cood+1].parent_y=y_cood;
                        points[x_cood+1][y_cood+1].theta=the;



            pq.push(a);
            
        }

            }
        }
    }
        
 if( is_visited[x_cood+1][y_cood-1]==0)
    {
        int temp=1;
        calculateCorners(x_cood+1,y_cood-1,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            for(int i=x_cood+1-(breadth/2);i<=x_cood+1+breadth/2;i++)
            {
                for(int j=y_cood-1-(length/2);j<=y_cood-1+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp  )
            {
                    if(points[x_cood+1][y_cood-1].distance+sqrt((x_cood-r+1)*(x_cood-r+1)+(y_cood-c-1)*(y_cood-c-1))> d+1)
        {
           

            is_visited[x_cood+1][y_cood-1]=1;

            points[x_cood+1][y_cood-1].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood+1,a.point_y=y_cood-1,a.distance=points[x_cood+1][y_cood-1].distance;
             points[x_cood+1][y_cood-1].parent_x=x_cood;
            points[x_cood+1][y_cood-1].parent_y=y_cood;
                        points[x_cood+1][y_cood-1].theta=the;



            pq.push(a);
            
        }

            }
        }
    }
        

   if( is_visited[x_cood-1][y_cood]==0)
    {
        int temp=1;
        calculateCorners(x_cood-1,y_cood,length,breadth,the);

        if(check_point(int(corner[0][0]),int(corner[0][1]))==1 && check_point(int(corner[1][0]),int(corner[1][1]))==1 && check_point(int(corner[2][0]),int(corner[2][1]))==1 && check_point(int(corner[3][0]),int(corner[3][1]))==1 )
        {

            for(int i=x_cood-1-(breadth/2);i<=x_cood-1+breadth/2;i++)
            {
                for(int j=y_cood-(length/2);j<=y_cood+length/2;j++)
                {
                 if(img.at<uchar>(int(i),int(j))!=0)
                 temp=0;    
                }
            }
            if(temp)
            {
                    if(points[x_cood-1][y_cood].distance+sqrt((x_cood-r-1)*(x_cood-r-1)+(y_cood-c)*(y_cood-c))> d+1)
        {
           

            is_visited[x_cood-1][y_cood]=1;

            points[x_cood-1][y_cood].distance=points[x_cood][y_cood].distance+1;

            point1 a;
            a.point_x=x_cood-1,a.point_y=y_cood,a.distance=points[x_cood-1][y_cood].distance;
             points[x_cood-1][y_cood].parent_x=x_cood;
            points[x_cood-1][y_cood].parent_y=y_cood;
                        points[x_cood-1][y_cood].theta=the;



            pq.push(a);
            
        }

            }
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
print_path(points,r,c,length,breadth);
cout<<"hello"<<endl;





waitKey(0);

}	
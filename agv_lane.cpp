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

Mat img1=imread("/home/aryan/Downloads/lane.png",1);
Mat img2=imread("/home/aryan/Downloads/lanebw.png",1);

int r=img1.rows;
int c=img1.cols;

Mat imgcanny(r,c,CV_8UC1,Scalar(0));
Mat temp(r,c,CV_8UC1,Scalar(0));
Mat dst(r,0.62894*c,CV_8UC1,Scalar(0));

int center_y,center_x;
vector<vector<Point> > contours;
vector<vector<Point> > contours1;
vector<Vec4i> hierarchy;
vector<Vec4i> hierarchy1;


Mat hls=img1.clone();
int th=50;

Point2f src_vertices[4];
Point2f dst_vertices[4];




int check_point(int i,int j)
{
  if(i>=0 && j>=0 && i<r && j<c)
    return 1;
  else
    return 0;
}


void removenoise(Mat &thresh)
{


Mat erodeElement = getStructuringElement(MORPH_RECT, Size(1,1));

Mat dilateElement = getStructuringElement(MORPH_RECT, Size(3, 3));

//erode(thresh, thresh, erodeElement);
erode(thresh, thresh, erodeElement);


//dilate(thresh, thresh, dilateElement);
//dilate(thresh, thresh, dilateElement);

}




int main()
{
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			if(img2.at<Vec3b>(i,j)[0]==0 && img2.at<Vec3b>(i,j)[1]==0 && img2.at<Vec3b>(i,j)[2]==0)
			{
				img1.at<Vec3b>(i,j)[0]=0;
				img1.at<Vec3b>(i,j)[1]=0;
				img1.at<Vec3b>(i,j)[2]=0;

			}
		}
	}



	Mat img4=img1.clone();
		Mat imggray=img1.clone();


	cvtColor(img1,hls,CV_BGR2HSV);
cvtColor(img1,imggray,CV_BGR2GRAY);
//cout<<r<<endl<<c<<endl;

/*src_vertices[0]=(Point(0.2734*c,0.5234*r));
src_vertices[1]=(Point(0.7265*c,0.5234*r));
src_vertices[2]=(Point(0.90234*c,0.78125*r));
src_vertices[3]=(Point(0.0976*c,0.78125*r));

dst_vertices[0]=(Point(0.2734*c,0));
dst_vertices[1]=(Point(0.90234*c,0));
dst_vertices[2]=(Point(0.90234*c,r));
dst_vertices[3]=(Point(0.2734*c,r));


Mat M=getPerspectiveTransform(src_vertices,dst_vertices);
Mat MI=getPerspectiveTransform(dst_vertices,src_vertices);

 warpPerspective(imggray,dst,M,Size(r,0.62894*c));
*/
GaussianBlur(imggray,imggray,Size(5,5),0);

Canny(imggray,imgcanny,th,th*3,3);

//removenoise(imgcanny);


	int flag=1;

Mat ix=img4.clone();
Mat j=img4.clone();

  
  
    //vector<Vec4i> linesP;
   //HoughLinesP(imgcanny, linesP, 1, CV_PI/180, 5, 2, 10 ); 
      findContours(imgcanny,contours,hierarchy,RETR_LIST,CHAIN_APPROX_NONE);
      cout<<contours.size()<<endl;
   // cout<<linesP.size();

  //   drawContours(j,contours,-1,Scalar(255,0,0),1,LINE_AA,hierarchy,0);

      vector<Moments> mu(contours.size());

      for( int i = 0; i<contours.size(); i++ )
{ mu[i] = moments( contours[i], false ); }

      vector<Point2f> mc(contours.size());


      
    for( int k = 0; k < contours.size(); k++ )
    {
        double area = contourArea(contours[k] );
       mc[k] = Point2f( mu[k].m10/mu[k].m00 , mu[k].m01/mu[k].m00 );
       center_x=mc[k].x,center_y=mc[k].y;


for(int i=-1;i<=1;i++)
{
	for(int j=-1;j<=1;j++)
	{
		if(!(i==0 && j==0))
		{	
		if(check_point(center_x+i,center_y+j))
		{
			if(imggray.at<uchar>(center_x+i,center_y+j)==0)
			{
             flag=0;       
			}
		}

	}
}
}
if(flag)
{
	if(center_x<320)
	{
	
        drawContours(j,contours,k,Scalar(0,0,255),2,LINE_AA,hierarchy,0);
    }
    else
    {
                  drawContours(j,contours,k,Scalar(255,0,0),2,LINE_AA,hierarchy,0);
	
    }

}

       
       
    }



flag=1;

    vector<Vec4i> linesP;
    HoughLinesP(imgcanny, linesP, 1, CV_PI/180, 1, 1, 10 ); 
    cout<<linesP.size()<<endl;
    
       
    for( int i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        int k=(l[0]+l[2])/2;
        int z=(l[1]+l[3])/2;


for(int m=-1;m<=1;m++)
{
	for(int l=-1;l<=1;l++)
	{
		if(!(m==0 && l==0))
		if(check_point(k+m,z+l))
		{
			if(imggray.at<uchar>(k+m,z+l)==0)
			{
             flag=0;       
			}
		}
	}
}
if(flag)
{
	if(k<320)
	{
        line( j, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 2, CV_AA);
    }
    else
    {
    	        line( j, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 2, CV_AA);

    }
}

       
       
    }

   for(int i=0;i<r;i++)
	{
		for(int jj=0;jj<c;jj++)
		{

			if(j.at<Vec3b>(i,jj)[2]>150 || j.at<Vec3b>(i,jj)[1]<20 || j.at<Vec3b>(i,jj)[0]<20)
			{


		for(int k=-5;k<=5;k++)
		{
			for(int l=-5;l<=5;l++)
			{
				if(!(k==0 && l==0))
				{	
				if(check_point(i+k,jj+l))
				{
					if(j.at<Vec3b>(i+k,jj+l)[0]==0 && j.at<Vec3b>(i+k,jj+l)[1]==0 && j.at<Vec3b>(i+k,jj+l)[2]==0)
					{
             		        j.at<Vec3b>(i,jj)[2]=ix.at<Vec3b>(i,jj)[2];  
             		        j.at<Vec3b>(i,jj)[1]=ix.at<Vec3b>(i,jj)[1];    
             		        j.at<Vec3b>(i,jj)[0]=ix.at<Vec3b>(i,jj)[0];    
             		       // cout<<"hello"<<endl;
  
					}

				}

			}
		}
		}
					}

					 if(j.at<Vec3b>(i,jj)[0]>150 || j.at<Vec3b>(i,jj)[1]<20 || j.at<Vec3b>(i,jj)[2]<20)
					{

			


		for(int k=-5;k<=5;k++)
		{
			for(int l=-5;l<=5;l++)
			{
				if(!(k==0 && l==0))
				{	
				if(check_point(i+k,jj+l))
				{
					if(j.at<Vec3b>(i+k,jj+l)[0]==0 && j.at<Vec3b>(i+k,jj+l)[1]==0 && j.at<Vec3b>(i+k,jj+l)[2]==0)
					{
             		        j.at<Vec3b>(i,jj)[2]=ix.at<Vec3b>(i,jj)[2];  
             		        j.at<Vec3b>(i,jj)[1]=ix.at<Vec3b>(i,jj)[1];    
             		        j.at<Vec3b>(i,jj)[0]=ix.at<Vec3b>(i,jj)[0];    
             		       // cout<<"hello"<<endl;
  
					}

				}

			}
		}
		}
					

				}
			}
		}
cout<<contours.size()<<endl;


/*flag=1;

    vector<Vec4i> linesP;
    HoughLinesP(imgcanny, linesP, 1, CV_PI/180, 5, 5, 10 ); 
    cout<<linesP.size()<<endl;
    
       
    for( int i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        int k=(l[0]+l[2])/2;
        int z=(l[1]+l[3])/2;


for(int m=-1;m<=1;m++)
{
	for(int l=-1;l<=1;l++)
	{
		if(!(m==0 && l==0))
		if(check_point(k+m,z+l))
		{
			if(imggray.at<uchar>(k+m,z+l)==0)
			{
             flag=0;       
			}
		}
	}
}
if(flag)
{
	if(k<300)
	{
        line( j, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 2, CV_AA);
    }
    else
    {
    	        line( j, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 2, CV_AA);

    }
}

       
       
    }*/
namedWindow("segmented_lane",WINDOW_NORMAL);
//imshow("segmented_lane",j);
namedWindow("lanebw",WINDOW_NORMAL);
imshow("lanebw",imgcanny);
namedWindow("lanehough",WINDOW_NORMAL);
imshow("lanehough",imggray);
namedWindow("hsv",WINDOW_NORMAL);
imshow("hsv",j);
waitKey(0);

	
}
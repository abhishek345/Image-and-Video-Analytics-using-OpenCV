#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    
    Mat I;
    I= imread("/Users/gayatriprabhu/Desktop/pic.png");
    if(! I.data )
    {
        cout<<  "Could not open or find the image" << endl ;
        return -1;
    }
    
    //Q3 Brightness adjustment
    
    Mat B1=I.clone();
    
    for( int y = 0; y < B1.rows; y++ )
        for( int x = 0; x < B1.cols; x++ )
            for( int c = 0; c < 3; c++ )
                B1.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( B1.at<Vec3b>(y,x)[c]  + 50 );
    
    
    namedWindow("Original Image");
    namedWindow("Brightened Image");
    
    imshow("Original Image", I);
    moveWindow("Original Image", 10, 100);
    
    imshow("Brightened Image", B1);
    moveWindow("Brightened Image", 650, 100);
    
    waitKey(0);
    
    //Q2 Salt and Pepper
    
    Mat saltpepper_noise = Mat::zeros(I.rows, I.cols,CV_8U);
    randu(saltpepper_noise,0,255);
    
    float d=0.02;
    int d_=d*255;
    
    Mat black = saltpepper_noise <= (d_/2);
    Mat white = saltpepper_noise > (d_/2) & saltpepper_noise <= (d_) ;
    
    Mat N2= I.clone();
    N2.setTo(0,black);
    N2.setTo(255,white);
    

    imshow("Salt&Pepper Noise", N2);
    moveWindow("Salt&Pepper Noise", 650, 100);
    
    waitKey(0);
    
    Mat H2=N2.clone();
    
    for (int y = 1; y < H2.rows - 1; y++)
    {
        for (int x = 1; x < H2.cols - 1; x++)
        {
            for (int z = 0; z < 3; z++)
            {
                int window[9];
                window[0] = N2.at<Vec3b>(y - 1 ,x - 1)[z];
                window[1] = N2.at<Vec3b>(y, x - 1)[z];
                window[2] = N2.at<Vec3b>(y + 1, x - 1)[z];
                window[3] = N2.at<Vec3b>(y - 1, x)[z];
                window[4] = N2.at<Vec3b>(y, x)[z];
                window[5] = N2.at<Vec3b>(y + 1, x)[z];
                window[6] = N2.at<Vec3b>(y - 1, x + 1)[z];
                window[7] = N2.at<Vec3b>(y, x + 1)[z];
                window[8] = N2.at<Vec3b>(y + 1, x + 1)[z];
                sort(window, window + 9);
                H2.at<Vec3b>(y, x)[z] = window[4];
            }
        }
    }

    
    imshow("Salt&Pepper Noise removal", H2);
    moveWindow("Salt&Pepper Noise removal", 650, 100);
    
    waitKey(0);
    
    /*Mat H2_3;
    medianBlur(N2, H2_3, 3);
    imshow("Salt&Pepper Noise removal_3", H2_3);
    moveWindow("Salt&Pepper Noise removal_3", 650, 100);
    
    waitKey(0);
    
    Mat H2_5;
    medianBlur(N2, H2_5, 5);
    imshow("Salt&Pepper Noise removal_5", H2_5);
    moveWindow("Salt&Pepper Noise removal_5", 650, 100);
    
    waitKey(0);*/
    
    //Q1 Gaussian
    
    Mat Gaussian_noise = Mat(I.size(),I.type());
    randn(Gaussian_noise,0,15);
    
    Mat N1 = I.clone();
    N1 += Gaussian_noise;
    
    imshow("Gaussian Noise", N1);
    moveWindow("Gaussian Noise", 650, 100);
    
    waitKey(0);
    
    Mat H1=N1.clone();
    
    for (int y = 1; y < H1.rows - 1; y++)
    {
        for (int x = 1; x < H1.cols - 1; x++)
        {
            for (int z = 0; z < 3; z++)
            {
                int window[9];
                window[0] = N1.at<Vec3b>(y - 1 ,x - 1)[z];
                window[1] = N1.at<Vec3b>(y, x - 1)[z];
                window[2] = N1.at<Vec3b>(y + 1, x - 1)[z];
                window[3] = N1.at<Vec3b>(y - 1, x)[z];
                window[4] = N1.at<Vec3b>(y, x)[z];
                window[5] = N1.at<Vec3b>(y + 1, x)[z];
                window[6] = N1.at<Vec3b>(y - 1, x + 1)[z];
                window[7] = N1.at<Vec3b>(y, x + 1)[z];
                window[8] = N1.at<Vec3b>(y + 1, x + 1)[z];
                int sum=window[0]+window[1]+window[2]+window[3]+window[4]+window[5]+window[6]+window[7]+window[8];
                sum=sum/9;
                H1.at<Vec3b>(y, x)[z] = sum;
            }
        }
    }
    
    
    imshow("Gaussian Noise removal", H1);
    moveWindow("Gaussian Noise removal", 650, 100);
    
    waitKey(0);
    
    //Q4 Counting
    
    int dilation_type = MORPH_RECT;
    int dilation_size ;
    Mat element;
    
    //I
    
    Mat C=I.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else 
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, Mat());
    dilate(C, C, Mat());

    int n=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Original Image "<<n<<endl;
    
    //B1
    
    C=B1.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=150)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, Mat());
    dilate(C, C, Mat());
    
    n=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Brightened Image "<<n<<endl;
    
    //N1
    
    dilation_size= 20 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));

    
    C=N1.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    n=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Gaussain Noise Image "<<n<<endl;
    
    
    //H1
    
    dilation_size= 24 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));
    
    
    C=H1.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    n=connectedComponents(C,  C, 4,CV_32S);
    cout<<"Gaussain Noise Cleared Image "<<n<<endl;
    
    
    //N2
    
    dilation_size= 11 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));
    
    
    C=N2.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    n=connectedComponents(C,  C, 8,CV_32S);
    cout<<"Salt and pepper noise Image "<<n<<endl;
    
    
    //H2
    
    dilation_size= 15 ;
    
    element=getStructuringElement(dilation_type,
                                  Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                  Point(dilation_size, dilation_size));
    
    
    C=H2.clone();
    
    cvtColor(C, C, CV_BGR2GRAY);
    
    for (int i=0; i<C.rows ;i++)
        
    {
        
        for (int j=0;  j<C.cols ;j++)
            
        {
            if (C.at<uchar>(i,j)>=100)
                
                C.at<uchar>(i,j)=255;
            else
                C.at<uchar>(i,j)=0;
            
        }
        
    }
    
    erode(C, C, element);
    dilate(C, C, Mat());
    
    n=connectedComponents(C,  C, 8,CV_32S);
    cout<<"Salt and pepper noise cleared Image "<<n<<endl;
    

    

}

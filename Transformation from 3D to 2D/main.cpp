#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include<fstream>

using namespace std;
using namespace cv;

int main() {

	ifstream FILE;

	//Frame 1 -- color92331
	Mat C1;
	C1 = imread("/Users/gayatriprabhu/Desktop/Frame1.png");
	if (!C1.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat D1;
	D1 = imread("/Users/gayatriprabhu/Desktop/Depth1.png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	if (!D1.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	//Frame 2 -- color94764
		Mat C2;
	C2 = imread("/Users/gayatriprabhu/Desktop/Frame2.png");
	if (!C2.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat D2;
	D2 = imread("/Users/gayatriprabhu/Desktop/Depth2.png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
	if (!D2.data)
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}


	//reading the Intrinsic Matrix
	float IntrinsicRGB[3][3];
	FILE.open("/Users/gayatriprabhu/Desktop/IntrinsicRGB1.txt");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			FILE >> IntrinsicRGB[i][j];
		}
	}
	FILE.close();


	//reading the Inverse Intrinsic Matrix
	float InvIntrinsicIR[3][3];
	FILE.open("/Users/gayatriprabhu/Desktop/InvIntrinsicIR1.txt");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			FILE >> InvIntrinsicIR[i][j];
	}
	FILE.close();


	//reading the Transformation Matrix
	float Transformation[4][4];
	FILE.open("/Users/gayatriprabhu/Desktop/TransformationD-C.txt");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			FILE >> Transformation[i][j];
	}
	FILE.close();

	//**colorizing**

	//for Frame 1 -- color92331

	Mat D1c(D1.rows, D1.cols, CV_8UC3);

	D1.convertTo(D1, CV_32F);


	for (int y = 0; y < D1.rows; y++)
		for (int x = 0; x < D1.cols; x++)
		{
			float Zd = D1.at<float>(y, x, 0);
			//cout<<Zd<<endl;

			if (Zd != 0)
			{

				float Xd = (x*InvIntrinsicIR[0][0] + y*InvIntrinsicIR[1][0] + 1 * InvIntrinsicIR[2][0])*Zd;
				float Yd = (x*InvIntrinsicIR[0][1] + y*InvIntrinsicIR[1][1] + 1 * InvIntrinsicIR[2][1])*Zd;

				float Xc = (Xd*Transformation[0][0] + Yd*Transformation[1][0] + Zd * Transformation[2][0] + Transformation[3][0]);
				float Yc = (Xd*Transformation[0][1] + Yd*Transformation[1][1] + Zd * Transformation[2][1] + Transformation[3][1]);
				float Zc = (Xd*Transformation[0][2] + Yd*Transformation[1][2] + Zd * Transformation[2][2] + Transformation[3][2]);

				float s = Xc / Zc;
				float t = Yc / Zc;

				int u = (int)(s*IntrinsicRGB[0][0] + t*IntrinsicRGB[1][0] + 1 * IntrinsicRGB[2][0]);
				int v = (int)(s*IntrinsicRGB[0][1] + t*IntrinsicRGB[1][1] + 1 * IntrinsicRGB[2][1]);


				//cout<<u<<endl;
				// cout<<v<<endl;

				if (!(u >= C1.cols || v >= C1.rows || u<0 || v<0))
					for (int c = 0; c < 3; c++)
						D1c.at<Vec3b>(y, x)[c] = C1.at<Vec3b>(v, u)[c];
			}

		}


	//for Frame 2--color94764

	Mat D2c(D2.rows, D2.cols, CV_8UC3);

	D2.convertTo(D2, CV_32F);


	for (int y = 0; y < D2.rows; y++)
		for (int x = 0; x < D2.cols; x++)
		{
			float Zd = D2.at<float>(y, x, 0);
			//cout<<Zd<<endl;

			if (Zd != 0)
			{
				float Xd = (x*InvIntrinsicIR[0][0] + y*InvIntrinsicIR[1][0] + 1 * InvIntrinsicIR[2][0])*Zd;
				float Yd = (x*InvIntrinsicIR[0][1] + y*InvIntrinsicIR[1][1] + 1 * InvIntrinsicIR[2][1])*Zd;

				float Xc = (Xd*Transformation[0][0] + Yd*Transformation[1][0] + Zd * Transformation[2][0] + Transformation[3][0]);
				float Yc = (Xd*Transformation[0][1] + Yd*Transformation[1][1] + Zd * Transformation[2][1] + Transformation[3][1]);
				float Zc = (Xd*Transformation[0][2] + Yd*Transformation[1][2] + Zd * Transformation[2][2] + Transformation[3][2]);

				float s = Xc / Zc;
				float t = Yc / Zc;

				int u = (int)(s*IntrinsicRGB[0][0] + t*IntrinsicRGB[1][0] + 1 * IntrinsicRGB[2][0]);
				int v = (int)(s*IntrinsicRGB[0][1] + t*IntrinsicRGB[1][1] + 1 * IntrinsicRGB[2][1]);


				//cout<<u<<endl;
				// cout<<v<<endl;

				if (!(u >= C2.cols || v >= C2.rows || u<0 || v<0))
					for (int c = 0; c < 3; c++)
						D2c.at<Vec3b>(y, x)[c] = C2.at<Vec3b>(v, u)[c];
			}

		}


	imshow("Colorized depth image Frame 1", D1c);
	waitKey();

	imshow("Colorized depth image Frame 2", D2c);
	waitKey();


	//**detection**

	uchar red, green, blue;

	//for Frame 1 -- color92331

	int x_max = 0, y_max = 0, x_min = D1c.cols, y_min = D1c.rows;

	//purple ball
	for (int y = 0; y<D1c.rows; y++)
	{
		for (int x = 0; x<D1c.cols; x++)
		{
			blue = D1c.at<Vec3b>(y, x)[0];
			green = D1c.at<Vec3b>(y, x)[1];
			red = D1c.at<Vec3b>(y, x)[2];
			//left
			if (red >= 100 && red <= 105 && green >= 60 && green <= 70 && blue >= 120 && blue <= 127)
			{
				if (x <= x_min)
					x_min = x;
			}

			//right
			if (red >= 65 && red <= 73 && green >= 45 && green <= 52 && blue >= 80 && blue <= 90)
			{
				if (x >= x_max)
					x_max = x;
			}

			//top
			if (red >= 215 && red <= 220 && green >= 205 && green <= 213 && blue >= 240 && blue <= 250)
			{
				if (y <= y_min)
					y_min = y;
			}

			//bottom
			if (red >= 25 && red <= 35 && green >= 15 && green <= 25 && blue >= 15 && blue <= 25)
			{
				if (y >= y_max)
					y_max = y;
			}

		}
	}

	int center_x1p = (x_min + x_max) / 2;
	int center_y1p = (y_min + y_max) / 2;

	rectangle(D1c, Point(x_min, y_min), Point(x_max, y_max), Scalar(0, 0, 255), 2, 8);



	//orange ball
	x_max = 0, y_max = 0, x_min = D1c.cols, y_min = D1c.rows;

	for (int y = 0; y<D1c.rows; y++)
	{
		for (int x = 0; x<D1c.cols; x++)
		{
			blue = D1c.at<Vec3b>(y, x)[0];
			green = D1c.at<Vec3b>(y, x)[1];
			red = D1c.at<Vec3b>(y, x)[2];
			//left
			if (red >= 115 && red <= 125 && green >= 65 && green <= 70 && blue >= 27 && blue <= 35)
			{
				if (x <= x_min)
					x_min = x;
			}

			//right
			if (red >= 79 && red <= 85 && green >= 30 && green <= 38 && blue >= 10 && blue <= 17)
			{
				if (x >= x_max)
					x_max = x;
			}

			//top
			if (red >= 140 && red <= 145 && green >= 85 && green <= 90 && blue >= 43 && blue <= 50)
			{
				if (y <= y_min)
					y_min = y;
			}

			//bottom
			if (red >= 50 && red <= 60 && green >= 20 && green <= 30 && blue >= 10 && blue <= 17)
			{
				if (y >= y_max)
					y_max = y;
			}

		}
	}

	int center_x1o = (x_min + x_max) / 2;
	int center_y1o = (y_min + y_max) / 2;

	rectangle(D1c, Point(x_min, y_min), Point(x_max, y_max), Scalar(0, 0, 255), 2, 8);


	imshow("Detection Frame 1", D1c);
	waitKey();


	//for Frame 2--color94764

	x_max = 0, y_max = 0, x_min = D2c.cols, y_min = D2c.rows;

	//purple ball
	for (int y = 0; y<D2c.rows; y++)
	{
		for (int x = 0; x<D2c.cols; x++)
		{
			blue = D2c.at<Vec3b>(y, x)[0];
			green = D2c.at<Vec3b>(y, x)[1];
			red = D2c.at<Vec3b>(y, x)[2];
			//left
			if (red >= 95 && red <= 105 && green >= 70 && green <= 75 && blue >= 125 && blue <= 135)
			{
				if (x <= x_min)
					x_min = x;
			}

			//right
			if (red >= 30 && red <= 35 && green >= 20 && green <= 25 && blue >= 20 && blue <= 25)
			{
				if (x >= x_max)
					x_max = x;
			}

			//top
			if (red >= 140 && red <= 155 && green >= 120 && green <= 130 && blue >= 178 && blue <= 195)
			{
				if (y <= y_min)
					y_min = y;
			}

			//bottom
			if (red >= 25 && red <= 35 && green >= 15 && green <= 25 && blue >= 15 && blue <= 25)
			{
				if (y >= y_max)
					y_max = y;
			}

		}
	}

	int center_x2p = (x_min + x_max) / 2;
	int center_y2p = (y_min + y_max) / 2;

	rectangle(D2c, Point(x_min, y_min), Point(x_max, y_max), Scalar(0, 0, 255), 2, 8);



	//orange ball
	x_max = 0, y_max = 0, x_min = D2c.cols, y_min = D2c.rows;

	for (int y = 0; y<D2c.rows; y++)
	{
		for (int x = 0; x<D2c.cols; x++)
		{
			blue = D2c.at<Vec3b>(y, x)[0];
			green = D2c.at<Vec3b>(y, x)[1];
			red = D2c.at<Vec3b>(y, x)[2];
			//left
			if (red >= 98 && red <= 105 && green >= 40 && green <= 48 && blue >= 13 && blue <= 20)
			{
				if (x <= x_min)
					x_min = x;
			}

			//right
			if (red >= 65 && red <= 70 && green >= 30 && green <= 38 && blue >= 12 && blue <= 20)
			{
				if (x >= x_max)
					x_max = x;
			}

			//top
			if (red >= 200 && red <= 210 && green >= 159 && green <= 170 && blue >= 150 && blue <= 160)
			{
				if (y <= y_min)
					y_min = y;
			}

			//bottom
			if (red >= 50 && red <= 60 && green >= 20 && green <= 30 && blue >= 10 && blue <= 17)
			{
				if (y >= y_max)
					y_max = y;
			}

		}
	}

	int center_x2o = (x_min + x_max) / 2;
	int center_y2o = (y_min + y_max) / 2;

	rectangle(D2c, Point(x_min, y_min), Point(x_max, y_max), Scalar(0, 0, 255), 2, 8);


	imshow("Detection Frame 2", D2c);
	waitKey();

	//purple
	//initial coordinates
	float purple_Z1 = D1.at<float>(center_y1p, center_x1p, 0);
	float purple_X1 = (center_x1p*InvIntrinsicIR[0][0] + center_y1p*InvIntrinsicIR[1][0] + 1 * InvIntrinsicIR[2][0])*purple_Z1;
	float purple_Y1 = (center_x1p*InvIntrinsicIR[0][1] + center_y1p*InvIntrinsicIR[1][1] + 1 * InvIntrinsicIR[2][1])*purple_Z1;

	//final coordinates
	float purple_Z2 = D2.at<float>(center_y2p, center_x2p, 0);
	float purple_X2 = (center_x2p*InvIntrinsicIR[0][0] + center_y2p*InvIntrinsicIR[1][0] + 1 * InvIntrinsicIR[2][0])*purple_Z2;
	float purple_Y2 = (center_x2p*InvIntrinsicIR[0][1] + center_y2p*InvIntrinsicIR[1][1] + 1 * InvIntrinsicIR[2][1])*purple_Z2;

	//orange
	//initial coordinates
	float orange_Z1 = D1.at<float>(center_y1o, center_x1o, 0);
	float orange_X1 = (center_x1o*InvIntrinsicIR[0][0] + center_y1o*InvIntrinsicIR[1][0] + 1 * InvIntrinsicIR[2][0])*orange_Z1;
	float orange_Y1 = (center_x1o*InvIntrinsicIR[0][1] + center_y1o*InvIntrinsicIR[1][1] + 1 * InvIntrinsicIR[2][1])*orange_Z1;

	//final coordinates
	float orange_Z2 = D2.at<float>(center_y2o, center_x2o, 0);
	float orange_X2 = (center_x2o*InvIntrinsicIR[0][0] + center_y2o*InvIntrinsicIR[1][0] + 1 * InvIntrinsicIR[2][0])*orange_Z2;
	float orange_Y2 = (center_x2o*InvIntrinsicIR[0][1] + center_y2o*InvIntrinsicIR[1][1] + 1 * InvIntrinsicIR[2][1])*orange_Z2;

	//velocity for purple ball
	float pVel_x = (purple_X2 - purple_X1) / 2.433;
	float pVel_y = (purple_Y2 - purple_Y1) / 2.433;
	float pVel_z = (purple_Z2 - purple_Z1) / 2.433;
	float pVel = sqrt(pow((pVel_x), 2) + pow((pVel_y), 2) + pow((pVel_z), 2));
	cout << "velocity for purple ball: " << pVel_x << "i+" << pVel_y << "j+" << pVel_z << "k" << endl;
	cout << "magnitude for velocity (speed): " << pVel << "milimeters/second" << endl;

	//velocity for orange ball
	float oVel_x = (orange_X2 - orange_X1) / 2.433;
	float oVel_y = (orange_Y2 - orange_Y1) / 2.433;
	float oVel_z = (orange_Z2 - orange_Z1) / 2.433;
	float oVel = sqrt(pow((oVel_x), 2) + pow((oVel_y), 2) + pow((oVel_z), 2));
	cout << "velocity for orange ball: " << oVel_x << "i+" << oVel_y << "j+" << oVel_z << "k" << endl;
	cout << "magnitude for velocity (speed): " << oVel << "milimeters/second" << endl;

	//relative velocity of purple ball wrt orange
	cout << "realtive velocity of purple ball wrt orange: " << (pVel_x - oVel_x) << "i+" << (pVel_y - oVel_y) << "j+" << pVel_z - oVel_z << "k" << endl;
	//relative velocity of purple ball wrt orange
	cout << "relative velocity of orange ball wrt purple: " << (oVel_x - pVel_x) << "i+" << (oVel_y - pVel_y) << "j+" << oVel_z - pVel_z << "k" << endl;

	float Rel_vel = sqrt(pow((pVel_x - oVel_x), 2) + pow((pVel_y - oVel_y), 2) + pow((pVel_z - oVel_z), 2));
	cout << "magnitude of relative velocity: " << Rel_vel << "milimeters/second" << endl;

}

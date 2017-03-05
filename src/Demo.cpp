// IDCR_Demo.cpp : 定义控制台应用程序的入口点。
//

#include  <stdio.h>

#include "MC_PixelMap.h"
#include "MC_LoadTools.h"

/*
#include "MC_EasyImage.h"

*/
int main(int argc, char* argv[])
{
	PixelMap<bgr> pixel;


	LoadTools::LoadBMP("F:\\LKF\\HP-Socket\\data\\1_front.bmp", &pixel);
	LoadTools::SaveTGA("F:\\LKF\\test_bk.tga", &pixel);


	/*
	PixelMap pixel;

	//LoadTools::LoadBMP("F:\\LKF\\HP-Socket\\data\\1_front.bmp", &pixel);
	LoadTools::LoadTGA("F:\\LKF\\test.TGA", &pixel);


	//pixel.RGBToGray();
	LoadTools::SaveTGA("F:\\LKF\\test_bk.tga", &pixel);

	*/
	return 0;
}


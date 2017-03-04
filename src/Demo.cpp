// IDCR_Demo.cpp : 定义控制台应用程序的入口点。
//

#include  <stdio.h>
#include "MC_PixelMap.h"

#include "MC_LoadTools.h"

int main(int argc, char* argv[])
{

	PixelMap pixel;

	LoadTools::LoadBMP("F:\\LKF\\HP-Socket\\data\\1_front.bmp", &pixel);


	pixel.RGBToGray();
	LoadTools::SaveTGA("F:\\LKF\\test.TGA", &pixel);


	return 0;
}


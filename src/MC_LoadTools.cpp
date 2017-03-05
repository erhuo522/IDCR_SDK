
#include "MC_LoadTools.h"
#include "MC_PixelMap.h"

#include <Windows.h>
#include <stdio.h>

 
/*

bool LoadTools::LoadTGA(const char* filename, PixelMap* pPixel)
{


#pragma pack(1)
	struct TGAHeader
	{
		unsigned char   idLength,           // Length of optional identification sequence.
			paletteType,        // Is a palette present? (1=yes)
			imageType;          // Image data type (0=none, 1=indexed, 2=rgb,
		// 3=grey, +8=rle packed).
		unsigned short  firstPaletteEntry,  // First palette index, if present.
			numPaletteEntries;  // Number of palette entries, if present.
		unsigned char   paletteBits;        // Number of bits per palette entry.
		unsigned short  x,                  // Horiz. pixel coord. of lower left of image.
			y,                  // Vert. pixel coord. of lower left of image.
			width,              // Image width in pixels.
			height;             // Image height in pixels.
		unsigned char   depth,              // Image color depth (bits per pixel).
			descriptor;         // Image attribute flags.
	};
#pragma pack(pop)



	FILE* pfile = fopen(filename, "rb");
	if (pfile)
	{
		TGAHeader header;
		fread(&header, 1 , sizeof(TGAHeader),  pfile);


		int bmpWidth = header.width;
		int bmpHeight = header.height;
		int biBitCount = header.depth; 

		int lineByte = (bmpWidth * biBitCount/8+3)/4*4; 

		unsigned char* pBmpBuf=new unsigned char[lineByte * bmpHeight]; 

		fread(pBmpBuf,1, lineByte * bmpHeight, pfile);

		fclose(pfile);//¹Ø±ÕÎÄ¼þ 

		pPixel->Create(bmpWidth, bmpHeight);

		for(int i=0; i<bmpHeight; i++)
		{
			unsigned char* pSrcRow = pBmpBuf + lineByte* i;
			unsigned char* pDestRow = pPixel->RowPtr(i);

			memcpy(pDestRow, pSrcRow, lineByte);
		}
	}
	return true;
}

 
 */
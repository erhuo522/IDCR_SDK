
#include "MC_LoadTools.h"
#include "MC_PixelMap.h"

#include <Windows.h>
#include <stdio.h>

bool LoadTools::LoadBMP(const char* filename, PixelMap* pPixel)
{

	FILE *fp=fopen(filename,"rb"); 
 
     if(fp==0)
	 {
         return 0;
	 }

     BITMAPFILEHEADER hdr;
     fread(&hdr, 1 , sizeof(BITMAPFILEHEADER),  fp );
     

     BITMAPINFOHEADER head;  
     fread(&head, 1, sizeof(BITMAPINFOHEADER), fp); //获取图像宽、高、每像素所占位数等信息
 
     int bmpWidth = head.biWidth;
     int bmpHeight = head.biHeight;
     int biBitCount = head.biBitCount; 

     int lineByte = (bmpWidth * biBitCount/8+3)/4*4; 
 
     unsigned char* pBmpBuf=new unsigned char[lineByte * bmpHeight];
 
	 fseek(fp,hdr.bfOffBits, SEEK_SET);
     fread(pBmpBuf,1,lineByte * bmpHeight,fp);
 
     fclose(fp);//关闭文件

	 pPixel->Create(bmpWidth, bmpHeight);

	 for(int i=0; i<bmpHeight; i++)
	 {
		 unsigned char* pSrcRow = pBmpBuf + lineByte* i;
		 unsigned char* pDestRow = pPixel->RowPtr(bmpHeight - i- 1);

		 memcpy(pDestRow, pSrcRow, lineByte);
	 }

	return true;
}

 

void LoadTools::SaveTGA(const char* filename,  const PixelMap* pPixel)
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



	FILE* pfile = fopen(filename, "wb");
	if (pfile)
	{
		TGAHeader header;
		memset(&header, 0, sizeof(TGAHeader));
		header.imageType  = 2;
		header.width = pPixel->Width();
		header.height = pPixel->Height();
		header.depth = 24;
		header.descriptor = 0x20;

		fwrite((const char *)&header, 1, sizeof(TGAHeader), pfile);
		fwrite((const char *)pPixel->m_buf, 1, 3 * pPixel->Width() * pPixel->Height(), pfile);

		fclose(pfile);


	}

}
 
 
#ifndef MC_EASY_IMAGE_INCLUDE_H__
#define MC_EASY_IMAGE_INCLUDE_H__




class EasyImage
{
public:
	struct EIHeader
	{
		unsigned short  magic;     // 标志头
		unsigned short  version;   // 版本
		unsigned int    crc32;     // crc校验
		unsigned int    reserved;  // 保留
	};

	struct EIInfo
	{
		unsigned int    width;     // 图片宽
		unsigned int    height;    // 图片高度
		unsigned int    rowBytes;  // 行字节数
		unsigned short  bitCount;  // 位深度 8 24
		unsigned short	reserved;  // 保留

	};


public:
	template <typename ImageT>
	static bool Save(const char* szfile,  const typename ImageT* pPixel)
	{

		FILE* pfile = fopen(filename, "rb");
		if (pfile)
		{
			EIHeader hdr;
			if(fread(&hdr, 1 , sizeof(EIHeader),  pfile) !=  sizeof(EIHeader) )
			{
				fclose(pfile);
				return false; 
			}

			//检查头和版本
			if(hdr.magic == 0x4945 && hdr.version  == 1)
			{
				fclose(pfile);
				return false; 
			}

			//检查crc校验
			if(hdr.crc32 != 0)
			{
				fclose(pfile); 
				return false; 
			}

			//读取图片信息
			EIInfo info;
			if(fread(&info, 1 , sizeof(EIInfo),  pfile) !=  sizeof(EIInfo) )
			{
				fclose(pfile); 
				return false; 
			}

			//分配内存
			unsigned int   nBufSize = info.rowBytes * info.height;
			unsigned char* pBmpBuf = new unsigned char[nBufSize];
			if(!pBmpBuf)
			{
				fclose(pfile);  
				return false; 
			}

			//读取像素
			if(fread(pBmpBuf, 1, nBufSize, pfile) == nBufSize)
			{
				if(pPixel->Create(info.width, info.height))
				{
					//复制像素
					for(int i=0; i<info.height; i++)
					{
						unsigned char* pDestRow = pPixel->RowPtr(i); 
						unsigned char* pSrcRow = pBmpBuf + info.rowBytes * i; 

						memcpy(pDestRow, pSrcRow, info.rowBytes);
					}

					//清理
					delete[] pBmpBuf;
					fclose(pfile);  

					return true;
				} 
			}

			//清理
			delete [] pBmpBuf;
			fclose(pfile);  

		}
		return false;
	}

	template <typename ImageT>
	static bool Load(const char* szfile, typename ImageT* pPixel)
	{
		int xwx = sizeof(EIHeader);
		int xx = sizeof(EIInfo);


		FILE* pfile = fopen(filename, "wb");
		if (pfile)
		{
			EIHeader hdr;

			hdr.magic    = 0x4945;
			hdr.version  = 1;
			hdr.crc32    = 0; 
			hdr.reserved = 0;

			if(fwrite(&hdr, 1, sizeof(EIHeader), pfile) != sizeof(EIHeader))
			{
				fclose(pfile);

				return false;
			}

			EIInfo info; 
			info.width    = pPixel->Width();
			info.height   = pPixel->Height();
			info.rowBytes = pPixel->RowBytes();  
			info.bitCount = 24;  
			info.reserved = 0; 

			if(fwrite(&info, 1, sizeof(EIInfo), pfile) != sizeof(EIInfo))
			{
				fclose(pfile);

				return false;
			}


			unsigned int  nWriteBytes = pPixel->RowBytes() * pPixel->Height();

			if(fwrite(pPixel->DataPtr(), 1, nWriteBytes, pfile) != nWriteBytes)
			{
				fclose(pfile); 

				return false;
			}
			else
			{
				fclose(pfile);

				return true;
			}
		}

		return false;

	}

};


#endif  //MC_EASY_IMAGE_INCLUDE_H__
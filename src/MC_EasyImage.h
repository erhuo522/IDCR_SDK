 
#ifndef MC_EASY_IMAGE_INCLUDE_H__
#define MC_EASY_IMAGE_INCLUDE_H__




class EasyImage
{
public:
	struct EIHeader
	{
		unsigned short  magic;     // ��־ͷ
		unsigned short  version;   // �汾
		unsigned int    crc32;     // crcУ��
		unsigned int    reserved;  // ����
	};

	struct EIInfo
	{
		unsigned int    width;     // ͼƬ��
		unsigned int    height;    // ͼƬ�߶�
		unsigned int    rowBytes;  // ���ֽ���
		unsigned short  bitCount;  // λ��� 8 24
		unsigned short	reserved;  // ����

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

			//���ͷ�Ͱ汾
			if(hdr.magic == 0x4945 && hdr.version  == 1)
			{
				fclose(pfile);
				return false; 
			}

			//���crcУ��
			if(hdr.crc32 != 0)
			{
				fclose(pfile); 
				return false; 
			}

			//��ȡͼƬ��Ϣ
			EIInfo info;
			if(fread(&info, 1 , sizeof(EIInfo),  pfile) !=  sizeof(EIInfo) )
			{
				fclose(pfile); 
				return false; 
			}

			//�����ڴ�
			unsigned int   nBufSize = info.rowBytes * info.height;
			unsigned char* pBmpBuf = new unsigned char[nBufSize];
			if(!pBmpBuf)
			{
				fclose(pfile);  
				return false; 
			}

			//��ȡ����
			if(fread(pBmpBuf, 1, nBufSize, pfile) == nBufSize)
			{
				if(pPixel->Create(info.width, info.height))
				{
					//��������
					for(int i=0; i<info.height; i++)
					{
						unsigned char* pDestRow = pPixel->RowPtr(i); 
						unsigned char* pSrcRow = pBmpBuf + info.rowBytes * i; 

						memcpy(pDestRow, pSrcRow, info.rowBytes);
					}

					//����
					delete[] pBmpBuf;
					fclose(pfile);  

					return true;
				} 
			}

			//����
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
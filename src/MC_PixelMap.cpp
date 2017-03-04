#include "MC_PixelMap.h"

#include <stdio.h>
#include <string.h>


	
PixelMap::PixelMap()
	:m_width(0),m_height(0),m_buf(NULL)
{


}


	
PixelMap::~PixelMap()
{


}



bool PixelMap::Create(unsigned int width, unsigned int height)
{

	unsigned int line_len = ((width * 3 + 3) >> 2) << 2;

	m_buf = new unsigned char [line_len * height];
	if(!m_buf)
	{
		return false;
	}

	m_width = width;
	m_height = height;

	return true;

}

void PixelMap::Destroy()
{
	if(m_buf)
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	m_width = m_height = 0;
}

unsigned char* PixelMap::RowPtr(int index)
{
	unsigned int line_len = ((m_width * 3 + 3) >> 2) << 2;
	unsigned char* rowPtr = m_buf + line_len * index;

	return rowPtr;
}

unsigned int PixelMap::Width() const
{
	return m_width;
}

unsigned int PixelMap::Height() const
{
	return m_height;
}


void PixelMap::RGBToGray()
{
	unsigned int line_len = ((m_width * 3 + 3) >> 2) << 2;

	for(int i=0; i<m_height; i++)
	{
		unsigned char* rowPtr = m_buf + line_len * i;
		for(int j=0; j<m_width; j++)
		{
			unsigned char uB = rowPtr[j*3 + 0];
			unsigned char uG = rowPtr[j*3 + 1];
			unsigned char uR = rowPtr[j*3 + 2];

			float gray = 0.3f * uR + 0.59f * uG + 0.11f * uB;
			
			if( gray > 255)
			{
				rowPtr[j*3 + 0] =  rowPtr[j*3 + 1] =  rowPtr[j*3 + 2] = 255;
			}
			else if( gray < 0)
			{
				rowPtr[j*3 + 0] =  rowPtr[j*3 + 1] =  rowPtr[j*3 + 2] = 0;
			}
			else
			{
				rowPtr[j*3 + 0] =  rowPtr[j*3 + 1] =  rowPtr[j*3 + 2] = (unsigned char)gray;
			}
		}
	}

}


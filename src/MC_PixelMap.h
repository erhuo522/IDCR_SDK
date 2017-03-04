 
#ifndef MC_PIXEL_MAP_INCLUDE_H__
#define MC_PIXEL_MAP_INCLUDE_H__


class PixelMap
{
public:
	PixelMap();
	~PixelMap();

public:
	bool Create(unsigned int width, unsigned int height);
	void Destroy();

	unsigned char* RowPtr(int index);
	unsigned int   Width() const;
	unsigned int   Height() const;

	void RGBToGray();

 

public:
		unsigned char*  m_buf;
private:
	
	 unsigned int    m_width;
	 unsigned int    m_height;
};


#endif  //
 
#ifndef MC_PIXEL_MAP_TEMPLATE_INCLUDE_H__
#define MC_PIXEL_MAP_TEMPLATE_INCLUDE_H__


struct rgb
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	rgb() {}
 
	rgb(unsigned char r_, unsigned char g_, unsigned char b_) 
		:r(r_), g(g_), b(b_)
	{

	}
};

struct bgr
{
	unsigned char b;
    unsigned char g;
    unsigned char r;

	bgr() {}
 
	bgr(unsigned char b_, unsigned char g_, unsigned char r_) 
		:b(b_), g(g_), r(r_)
	{

	}
};


template<typename  ColorT> 
class PixelMap
{
public:
	typedef ColorT  color_type;

public:
	PixelMap();
	~PixelMap();

public:
	bool Create(unsigned int width, unsigned int height);
	void Destroy();

	ColorT* DataPtr() const;
	ColorT* RowPtr(int index) ;

	unsigned int   Width() const;
	unsigned int   Height() const;
	unsigned int   RowBytes() const;


private:
	 unsigned char*  m_buf;
	 unsigned int    m_lineBytes;
	 unsigned int    m_width;
	 unsigned int    m_height;
};

template<typename  ColorT> 
PixelMap<ColorT>::PixelMap()
	:m_width(0),m_height(0),m_lineBytes(0),m_buf(NULL)
{

}

template<typename  ColorT> 
PixelMap<ColorT>::~PixelMap()
{

}

template<typename  ColorT> 
bool PixelMap<ColorT>::Create(unsigned int width, unsigned int height)
{
	m_lineBytes = ((width * sizeof(ColorT) + 3) >> 2) << 2;

	m_buf = new unsigned char [m_lineBytes * height];
	if(!m_buf)
	{
		return false;
	}

	m_width = width;
	m_height = height;

	return true;
}

template<typename  ColorT>
void PixelMap<ColorT>::Destroy()
{
	if(m_buf)
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	m_width = m_height = 0;

}

template<typename  ColorT> 
ColorT* PixelMap<ColorT>::DataPtr() const
{
	return (ColorT*)m_buf;
}

template<typename  ColorT> 
ColorT* PixelMap<ColorT>::RowPtr(int index) 
{
	unsigned char* rowPtr = m_buf + m_lineBytes * index;

	return (ColorT*)rowPtr;
}

template<typename  ColorT> 
unsigned int   PixelMap<ColorT>::Width() const
{
	return m_width;
}

template<typename  ColorT> 
unsigned int   PixelMap<ColorT>::Height() const
{
	return m_height;
}

template<typename  ColorT> 
unsigned int  PixelMap<ColorT>::RowBytes() const
{
	return m_lineBytes;
}


typedef PixelMap<rgb>   PixelMap_RGB;
typedef PixelMap<bgr>   PixelMap_BGR;


#endif  //MC_PIXEL_MAP_TEMPLATE_INCLUDE_H__
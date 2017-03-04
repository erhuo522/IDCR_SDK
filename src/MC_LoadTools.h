 
#ifndef MC_LOAD_TOOLS_INCLUDE_H__
#define MC_LOAD_TOOLS_INCLUDE_H__

class PixelMap;

class LoadTools
{
public:
	static bool LoadBMP(const char* filename, PixelMap* pPixel);
	
	static void SaveTGA(const char* szfile,  const PixelMap* pPixel);

 
};


#endif  //MC_LOAD_TOOLS_INCLUDE_H__
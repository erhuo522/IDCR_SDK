 
#ifndef MC_BINARIZATION_INCLUDE_H__
#define MC_BINARIZATION_INCLUDE_H__

 

class Binarization
{
public:
	template <typename ImageT>
	static bool ThresholdProcess(ImageT * pPixel, unsigned char iThreshold)
	{
        
        typedef typename ImageT::color_type  color_type;
        
		for(int i=0; i<pPixel->Height(); i++)
		{
			color_type* rowPtr = pPixel->RowPtr(i);

			for(int j=0; j<pPixel->Width(); j++)
			{
				unsigned char uB = rowPtr[j].b;
				unsigned char uG = rowPtr[j].g;
				unsigned char uR = rowPtr[j].r;

				float gray = 0.3f * uR + 0.59f * uG + 0.11f * uB;

				if( gray > 128)
				{
					//rowPtr[j*3 + 0] =  rowPtr[j*3 + 1] =  rowPtr[j*3 + 2] = 255;
				}
				else 
				{
					//rowPtr[j*3 + 0] =  rowPtr[j*3 + 1] =  rowPtr[j*3 + 2] = 0;
				}
				

			}
		}


		return true;
	}



};


#endif  //MC_BINARIZATION_INCLUDE_H__

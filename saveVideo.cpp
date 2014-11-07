
#include "VideoThread.h"
#include "itkNumericSeriesFileNames.h"

saveVideo::saveVideo(){};

saveVideo::saveVideo( circ_buffer<circ_buffer_VideoData>* buff , Timer *timer)
{
	m_ringBuffer = buff;

	//m_numericSeriesFileNames = itk::NumericSeriesFileNames::New();
 // m_numericSeriesFileNames->SetStartIndex(0);
 // m_numericSeriesFileNames->SetEndIndex(2000);
 // m_numericSeriesFileNames->SetIncrementIndex(1);
 // m_numericSeriesFileNames->SetSeriesFormat("D:/CVTest/output_%d.png");
}

void saveVideo::Initialize(const char *fmt, ...)
{
  /*!
  Initialization of the TrakStar system. 
  */
	va_list args;
	va_start(args, fmt);
	m_BasePath=va_arg( args, char * );;
	m_BaseImageFileName=va_arg( args, char * );;
	m_BaseImageExtension=va_arg( args, char * );;
  va_end(args);	
}

void saveVideo::ThreadEntryPoint ()
{
	circ_buffer_VideoData frame;
	int itr = 0;
	char newFilename[512];
	for (;;)
	{

		if ( m_ringBuffer->size() > 2 )
		{
			frame = m_ringBuffer->receive();
			IplImage* iplImg=cvCloneImage(&(IplImage)frame.Mat);

			//std::vector< std::string > fileNames = m_numericSeriesFileNames->GetFileNames();
 
			if (itr<10)
					sprintf(newFilename,"%s%s000%1d%s",m_BasePath.c_str(),m_BaseImageFileName.c_str(),itr,m_BaseImageExtension.c_str());
				else
					if (itr<100)
						sprintf(newFilename,"%s%s00%2d%s",m_BasePath.c_str(),m_BaseImageFileName.c_str(),itr,m_BaseImageExtension.c_str());
					else
						if (itr<1000)
								sprintf(newFilename,"%s%s0%3d%s",m_BasePath.c_str(),m_BaseImageFileName.c_str(),itr,m_BaseImageExtension.c_str());
							else
									sprintf(newFilename,"%s%s%4d%s",m_BasePath.c_str(),m_BaseImageFileName.c_str(),itr,m_BaseImageExtension.c_str());
			std::cout << "save frame at iteration " << itr << std::endl;

			cvSaveImage(newFilename ,iplImg);
			cvReleaseImage(&iplImg);

		  //cvSaveImage(fileNames[itr].c_str() ,iplImg);
			//frame.Mat
			//frame.currentCount
			++itr;
		}
	}




}
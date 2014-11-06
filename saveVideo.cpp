
#include "VideoThread.h"
#include "itkNumericSeriesFileNames.h"

saveVideo::saveVideo(){};

saveVideo::saveVideo( circ_buffer<circ_buffer_VideoData>* buff , Timer *timer)
{
	m_ringBuffer = buff;

	m_numericSeriesFileNames = itk::NumericSeriesFileNames::New();
  m_numericSeriesFileNames->SetStartIndex(0);
  m_numericSeriesFileNames->SetEndIndex(2000);
  m_numericSeriesFileNames->SetIncrementIndex(1);
  m_numericSeriesFileNames->SetSeriesFormat("D:/CVTest/output_%d.png");
}

void saveVideo::ThreadEntryPoint ()
{
	circ_buffer_VideoData frame;
	int itr = 0;
	for (;;)
	{

		if ( m_ringBuffer->size() > 2 )
		{
			frame = m_ringBuffer->receive();
			IplImage* iplImg=cvCloneImage(&(IplImage)frame.Mat);

			std::vector< std::string > fileNames = m_numericSeriesFileNames->GetFileNames();
 

			cvSaveImage(fileNames[itr].c_str() ,iplImg);
			//frame.Mat
			//frame.currentCount
			++itr;
		}
	}




}
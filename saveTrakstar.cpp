
#include "trakstarThread.h"

saveTrakstar::saveTrakstar(){};

saveTrakstar::saveTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff , Timer *timer)
{
  m_ringBuffer = buff;
}

void saveTrakstar::Initialize(const char *fmt, ...)
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

void saveTrakstar::ThreadEntryPoint ()
{
  circ_buffer_TrakstarData TrakstarData;
  int itr = 0;
  for (;;)
  {
		if ( m_ringBuffer->size() > 2 )
		{
			TrakstarData = m_ringBuffer->receive();
			//TrakstarData.measuresCH1
			//TrakstarData.measuresCH2
			++itr;
		}
	}

}
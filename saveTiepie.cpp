
#include "TiepieThread.h"

saveTiepie::saveTiepie(){};

saveTiepie::saveTiepie( circ_buffer<circ_buffer_TiepieData>* buff , Timer *timer)
{
	m_ringBuffer = buff;
}

void saveTiepie::Initialize(const char *fmt, ...)
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

void saveTiepie::ThreadEntryPoint ()
{
	circ_buffer_TiepieData frame;
	int itr = 0;
	for (;;)
	{
	}
}
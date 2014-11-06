
#include "TiepieThread.h"

showTiepie::showTiepie(){};

showTiepie::showTiepie( circ_buffer<circ_buffer_TiepieData>* buff , Timer *timer)
{
	m_ringBuffer = buff;
}

void showTiepie::ThreadEntryPoint () 
{
	circ_buffer_TiepieData frame;
	int itr = 0;
	for (;;)
	{
	}
}
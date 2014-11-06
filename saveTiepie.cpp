
#include "TiepieThread.h"

saveTiepie::saveTiepie(){};

saveTiepie::saveTiepie( circ_buffer<circ_buffer_TiepieData>* buff , Timer *timer)
{
	m_ringBuffer = buff;
}

void saveTiepie::ThreadEntryPoint ()
{
	circ_buffer_TiepieData frame;
	int itr = 0;
	for (;;)
	{
	}
}
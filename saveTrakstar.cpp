
#include "trakstarThread.h"

saveTrakstar::saveTrakstar(){};

saveTrakstar::saveTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff , Timer *timer)
{
  m_ringBuffer = buff;
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
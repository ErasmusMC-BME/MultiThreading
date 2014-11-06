
#include "trakstarThread.h"

showTrakstar::showTrakstar(){};

showTrakstar::showTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff , Timer *timer)
{
  m_ringBuffer = buff;
}

void showTrakstar::ThreadEntryPoint () 
{
  circ_buffer_TrakstarData frame;
  int itr = 0;
  for (;;)
  {
  }
}


#include <iostream>            // c++ I/O

#include "opencv2/opencv.hpp"

#include <windows.h>          // for HANDLE
#include <process.h>          // for _beginthread()

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/circular_buffer.hpp>
#include "circ_buffer.txx"
#include "Timer.h"

struct circ_buffer_TiepieData 
{
	cv::Mat Mat;
	LARGE_INTEGER time;
};

class showTiepie 
{
  circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;
  
public:
	showTiepie(){};

  showTiepie( circ_buffer<circ_buffer_TiepieData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
   }

	void operator () ()
	{
    circ_buffer_TiepieData frame;
    int itr = 0;
    for (;;)
    {
    }
  }
};

class saveTiepie 
{
  circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;
  
public:
	saveTiepie(){};

  saveTiepie( circ_buffer<circ_buffer_TiepieData>* buff , Timer *timer)
  {
    m_ringBuffer = buff;
   }

	void operator () ()
	{
    circ_buffer_TiepieData frame;
    int itr = 0;
    for (;;)
    {
    }
  }
};
class captureTiepie

{
private:

public:
  circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;
	captureTiepie(){};

	captureTiepie( circ_buffer<circ_buffer_TiepieData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
  }

	void Initialize(const char *fmt=NULL, ...)
	{

	}


	~captureTiepie(){};
	static void StaticFunction()
	{
		//for (int i=0; i < 10; i++)  // Hard-coded upper limit
		//{
		//	cout<<i<<"Do something in parallel (Static function)."<<endl;

		//	boost::this_thread::yield(); // 'yield' discussed in section 18.6
		//}
	}
	void operator () ()
	{
    {
      std::cout << "Tiepie capture could not be opened. ABORT!" << std::endl;
    }
   // else
    {
      circ_buffer_TiepieData frame;
      int itr = 0;
			std::cout << "Tiepie capture started" << std::endl;
      for (;;)
			{
      } 
		}



	}
public:

 	private:



};

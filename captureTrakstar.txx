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

struct circ_buffer_TrakstarData 
{
	cv::Mat Mat;
	LARGE_INTEGER currentCount;
	LARGE_INTEGER frequency;                    // ticks per second
  LARGE_INTEGER startCount;                   //
};

class showTrakstar 
{
  circ_buffer<circ_buffer_TrakstarData>* m_ringBuffer;
  
public:
	showTrakstar(){};

  showTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff , Timer *timer)
  {
    m_ringBuffer = buff;
  }

	void operator () ()
	{
    circ_buffer_TrakstarData frame;
    int itr = 0;
    for (;;)
    {
    }
   }
};

class saveTrakstar 
{
  circ_buffer<circ_buffer_TrakstarData>* m_ringBuffer;
  
public:
	saveTrakstar(){};

  saveTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
  }

	void operator () ()
	{
    circ_buffer_TrakstarData frame;
    int itr = 0;
    for (;;)
    {
    }
   }
};

class captureTrakstar

{
private:

public:
  circ_buffer<circ_buffer_TrakstarData>* m_ringBuffer;
	captureTrakstar(){};

	captureTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
  }

	void Initialize(const char *fmt=NULL, ...)
	{

		}


	void StartRecorderThread()
	{

		do 
		{
		} while (1);

	};
	~captureTrakstar(){};
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
		//for (int i=0; i<12; i++)
		//{
		//	cout<<i<<" - Do something in parallel ddddddd (operator() )."<<endl;
		//	boost::this_thread::yield(); // 'yield' discussed in section 18.6
		//}
		std::cout << "Trakstar capture started" << std::endl;
   
		
	
		std::cout << "Trakstar capture started" << std::endl;
    {
      std::cout << "Trakstar capture could not be opened. ABORT!" << std::endl;
    }
   // else
    {
      circ_buffer_TrakstarData frame;
      int itr = 0;
			std::cout << "Trakstar capture started" << std::endl;
      for (;;)
      {
      } 
		}
	}
public:

 	private:



};

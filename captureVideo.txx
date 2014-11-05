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

struct circ_buffer_VideoData 
{
	cv::Mat Mat;
	LARGE_INTEGER currentCount;
};

class showVideo 
{
  circ_buffer<circ_buffer_VideoData>* m_ringBuffer;
  
public:
	showVideo(){};

  showVideo( circ_buffer<circ_buffer_VideoData>* buff, Timer *timer)
  {
    m_ringBuffer = buff;
  }

	void operator () ()
	{
    circ_buffer_VideoData frame;
    int itr = 0;
    //cv::namedWindow( "threadedVideoShow",  cv::WINDOW_AUTOSIZE );
    for (;;)
    {
      if ( m_ringBuffer->size() > 2 )
	    {
	      frame = m_ringBuffer->receive();
	      cv::imshow( "threadedVideoShow", frame.Mat );
        cv::waitKey(10);
        cv::Scalar meanVal = cv::mean( frame.Mat, cv::Mat() );
        std::cout << "GET frame at iteration " << itr << ". Buffer size: " << m_ringBuffer->size() << ". Mean intensity in frame: " << meanVal[0] << std::endl;
        ++itr;
	    }
    }
    
  }

};



class saveVideo 
{
  circ_buffer<circ_buffer_VideoData>* m_ringBuffer;
  
public:
	saveVideo(){};

  saveVideo( circ_buffer<circ_buffer_VideoData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
  }

	void operator () ()
	{
    circ_buffer_VideoData frame;
    int itr = 0;
     for (;;)
    {
      if ( m_ringBuffer->size() > 2 )
	    {
	    }
    }
   }
};




class captureVideo

{
private:

public:
  circ_buffer<circ_buffer_VideoData>* m_ringBuffer;
	captureVideo(){};

	captureVideo( circ_buffer<circ_buffer_VideoData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
  }

	void Initialize(const char *fmt=NULL, ...)
	{

		CvCapture* capture ;
		capture = cvCaptureFromCAM( 0 );
		if( capture )
		{

			for(;;)
			{
				//std:: cout << "camera awake" << std::endl;
				IplImage* iplImg = cvQueryFrame( capture );
				cv::Mat  frame = iplImg;
				if( !frame.empty())
				{
					break;
				}
			}
		}
	}

	~captureVideo(){};
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
		std::cout << "Video capture started" << std::endl;
   
		
	
		m_cap.open(0);
		std::cout << "Video capture started" << std::endl;
    if ( !m_cap.isOpened() )
    {
      std::cout << "Video capture could not be opened. ABORT!" << std::endl;
    }
    else
    {
      circ_buffer_VideoData frame;
      int itr = 0;
			std::cout << "Video capture started" << std::endl;
      for (;;)
      {
        m_cap >> frame.Mat;
        cv::Size sizeFrame = frame.Mat.size();
        std::cout << "Frame Size:" << frame.Mat.size() << std::endl;
        if ( sizeFrame.height > 0 && sizeFrame.width > 0 )
        {
          std::cout << frame.Mat.size();
          cv::cvtColor( frame.Mat, frame.Mat, cv::COLOR_BGR2GRAY );
          double minVal, maxVal;
          int minInd, maxInd;
          cv::minMaxIdx( frame.Mat, &minVal, &maxVal, &minInd, &maxInd, cv::Mat() );
          cv::Scalar meanVal = cv::mean( frame.Mat, cv::Mat() );
					QueryPerformanceCounter(&frame.currentCount);
          m_ringBuffer->send( frame );
          std::cout << "SET frame at iteration " << itr << ". Buffer size: " << m_ringBuffer->size() << ". Mean intensity in frame: " << meanVal[0] << std::endl;
          ++itr;
        }
      }
    } 



	}
public:

 	private:

  cv::VideoCapture m_cap;

};

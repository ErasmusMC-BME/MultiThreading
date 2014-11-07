
#include "VideoThread.h"

showVideo::showVideo(){};

showVideo::showVideo( circ_buffer<circ_buffer_VideoData>* buff , Timer *timer)
{
	m_ringBuffer = buff;
}

void showVideo::ThreadEntryPoint () 
{

	circ_buffer_VideoData frame;
	int itr = 0;
	//cv::namedWindow( "threadedVideoShow",  cv::WINDOW_AUTOSIZE );
	for (;;)
	{
		if ( m_ringBuffer->size() > 2 )
		{
			frame = m_ringBuffer->back();
			cv::imshow( "threadedVideoShow", frame.Mat );
			cv::waitKey(10);
			//cv::Scalar meanVal = cv::mean( frame.Mat, cv::Mat() );
		//	std::cout << "GET frame at iteration " << itr << ". Buffer size: " << m_ringBuffer->size() << ". Mean intensity in frame: " << meanVal[0] << std::endl;
				std::cout << "show frame at iteration " << itr << std::endl;
			++itr;
		}
	}
}



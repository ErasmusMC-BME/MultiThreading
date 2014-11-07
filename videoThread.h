
#ifndef Video_H_DEF
#define Video_H_DEF
#include "Timer.h"
#include "circ_buffer.txx"
#include "opencv2/opencv.hpp"
#include "itkNumericSeriesFileNames.h"

struct circ_buffer_VideoData 
{
	cv::Mat Mat;
	LARGE_INTEGER currentCount;
};


class showVideo 
{
	circ_buffer<circ_buffer_VideoData>* m_ringBuffer;

public:
	showVideo();

	showVideo( circ_buffer<circ_buffer_VideoData>* buff , Timer *timer);
	void ThreadEntryPoint();
	void operator () () {	ThreadEntryPoint();};
};

class saveVideo 
{
	circ_buffer<circ_buffer_VideoData>* m_ringBuffer;
	itk::NumericSeriesFileNames::Pointer m_numericSeriesFileNames; 
	std::string m_BasePath;
	std::string m_BaseImageFileName;
	std::string m_BaseImageExtension;
public:
	saveVideo();

	saveVideo( circ_buffer<circ_buffer_VideoData>* buff , Timer *timer);
	void Initialize(const char *fmt=NULL, ...);
	void ThreadEntryPoint();
	void operator () () {ThreadEntryPoint();};
};




class captureVideo

{
private:

public:
	circ_buffer<circ_buffer_VideoData>* m_ringBuffer;
	captureVideo(){};

	captureVideo( circ_buffer<circ_buffer_VideoData>* buff, Timer *timer );

	void Initialize(const char *fmt=NULL, ...);

	~captureVideo(){};
	static void StaticFunction()
	{
		//for (int i=0; i < 10; i++)  // Hard-coded upper limit
		//{
		//	cout<<i<<"Do something in parallel (Static function)."<<endl;

		//	boost::this_thread::yield(); // 'yield' discussed in section 18.6
		//}
	}
	void ThreadEntryPoint();
	void operator () ()
	{
		//for (int i=0; i<12; i++)
		//{
		//	cout<<i<<" - Do something in parallel ddddddd (operator() )."<<endl;
		//	boost::this_thread::yield(); // 'yield' discussed in section 18.6
		//}
		std::cout << "Video capture started" << std::endl;

		ThreadEntryPoint();
	} 

public:

private:

	cv::VideoCapture m_cap;

};
#endif
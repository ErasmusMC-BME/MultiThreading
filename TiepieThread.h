
#ifndef Tiepie_H_DEF
#define Tiepie_H_DEF
#include "Timer.h"
#include "circ_buffer.txx"
#include "opencv2/opencv.hpp"
#include "TiePieDLL.h"
#include "tiepie.h"

struct circ_buffer_TiepieData 
{
	cv::Mat Mat;
	LARGE_INTEGER time;
};


class showTiepie 
{
	circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;

public:
	showTiepie();

	showTiepie( circ_buffer<circ_buffer_TiepieData>* buff , Timer *timer);
	void ThreadEntryPoint();
	void operator () () {	ThreadEntryPoint();};
};

class saveTiepie 
{
	circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;
	std::string m_BasePath;
	std::string m_BaseImageFileName;
	std::string m_BaseImageExtension;
public:
	saveTiepie();

	saveTiepie( circ_buffer<circ_buffer_TiepieData>* buff , Timer *timer);
	void Initialize(const char *fmt=NULL, ...);
	void ThreadEntryPoint();
	void operator () () {ThreadEntryPoint();};
};


class captureTiepie

{

private:
	vnl_vector<double> _voltageCh1;
	vnl_vector<double> _timeCh1;
	bool _bTiepieFound;
	bool _bTiepieReady;
	bool _bTiepieDataReady;
	dword _recordLength;
	double _samplingFreq;
	double _tMeasurementStarted;
	Timer *m_timer;

public:
	dword  recLen;
	double sensCh1;
	double fs; 


public:
	circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;
	captureTiepie();

	captureTiepie( circ_buffer<circ_buffer_TiepieData>* buff, Timer *timer );

	void Initialize(const char *fmt=NULL, ...);

	~captureTiepie();
	static void StaticFunction()
	{
		//for (int i=0; i < 10; i++)  // Hard-coded upper limit
		//{
		//	cout<<i<<"Do something in parallel (Static function)."<<endl;

		//	boost::this_thread::yield(); // 'yield' discussed in section 18.6
		//}
	}
	void ThreadEntryPoint();
	void operator () () {ThreadEntryPoint();};

	void PrepareCh1ForAcq( dword recLen, double* sensCh1, double* fs );
	void RetrieveCh1DataFromInstrument();
public:

private:



};


#endif
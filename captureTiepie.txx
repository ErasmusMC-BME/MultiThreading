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
#include "vnl/vnl_vector.h"
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
	vnl_vector<double> _voltageCh1;
	vnl_vector<double> _timeCh1;
	bool _bTiepieFound;
	bool _bTiepieReady;
	bool _bTiepieDataReady;
	dword _recordLength;
	double _samplingFreq;
	double _tMeasurementStarted;

public:
	dword  recLen;
	double sensCh1;
	double fs; 


public:
  circ_buffer<circ_buffer_TiepieData>* m_ringBuffer;
	captureTiepie(){};

	captureTiepie( circ_buffer<circ_buffer_TiepieData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;
  }

	void Initialize(const char *fmt=NULL, ...)
	{


		//  initialization of TiePie
		word wAddress = 0x308;
		char sssPath[22];
		strcpy(sssPath,"hs3.dll");

		if ( OpenDLL(sssPath) ) //Tiepie test
		{	
			if ( InitInstrument( wAddress ) == E_NO_ERRORS )
			{
				_bTiepieFound=true;
				std::cerr << "TiePie initialization finished." << std::endl;
			}
			else
			{
				_bTiepieFound=false;
				std::cerr << "TiePie initialization failed." << std::endl;
			}
		}
		else
		{
			_bTiepieFound=false;
			std::cerr << "Opening TiePie DLL failed." << std::endl;
		}

		va_list args;
		// actual parameter passing
		dword recLen;
		double sensCh1;
		double fs;
		va_start(args, fmt);
		recLen = va_arg(args, dword);
		sensCh1= va_arg(args, double);
		fs = va_arg(args, double);
		PrepareCh1ForAcq( recLen, &sensCh1, &fs );
		va_end(args);


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



	vnl_vector<double>  GetTimeCh1()
	{
		return _timeCh1;
	}
	vnl_vector<double>  GetVoltageCh1()
	{
		return _voltageCh1;
	}
	void  SetTimeCh1(vnl_vector<double> timeCh1)
	{
		_timeCh1=timeCh1;
	}
	void SetVoltageCh1(vnl_vector<double> voltageCh1 )
	{
		_voltageCh1=voltageCh1;
	}

void PrepareCh1ForAcq( dword recLen, double* sensCh1, double* fs )
{  
	_recordLength = recLen;
	_samplingFreq = *fs;
	_bTiepieReady = false;
	if ( _bTiepieFound )
	{
		// setup channel 1
		SetSensitivity( lCh1,  sensCh1 );
		SetCoupling( lCh1, lctAC );

		// setup trigger
		SetTriggerSource( ltsNoTrig );

		// setup time base
		_recordLength = recLen;
		SetRecordLength( _recordLength );
		SetPostSamples( _recordLength );
		_samplingFreq = *fs;
		SetSampleFrequencyF( fs );

		// select channels to record
		SetMeasureMode( mmCh1 );

		// write settings to instrument and start measuring
		ADC_Start();
		ADC_Abort();
		_bTiepieReady = true;
		std::cout << "TiePie ready to measure." << std::endl;
	}
	else
	{
		_bTiepieReady = false;
	}
}

void RetrieveCh1DataFromInstrument()
{
	//m_OutputData->TiepieObject::recLen=0;
//	m_OutputData = (TiepieObjects *) new TiepieObjects;
	vnl_vector<double> _voltageCh1;
	vnl_vector<double> _timeCh1;
	//	double Time = m_timer->getElapsedTimeInSec();
	//Timer *m_timer= (Timer *) m_SyncObject;

	//double Time = m_timer->getElapsedTimeInSec();
	//std::cout << "Start Time RetrieveCh1DataFromInstrument: " << Time << std::endl;
	_timeCh1.set_size( _recordLength );
	double * Ch1DoubleArray = new double[_recordLength];
	_voltageCh1.set_size( _recordLength );

	if ( _bTiepieFound ) ADC_GetDataVoltCh( mmCh1, Ch1DoubleArray );

	// put data into vnl vectors
	for( int it = 0; it < _recordLength; ++it )
	{
		_timeCh1[it] = _tMeasurementStarted + (double)it/_samplingFreq;
		if ( _bTiepieFound ) _voltageCh1[it] = Ch1DoubleArray[it];
	}
//	m_OutputData->TiepieObjects::SetTimeCh1(_timeCh1);
//	m_OutputData->SetVoltageCh1(_voltageCh1);
	//m_sharedobjs->SetTimeCh1(_timeCh1);
	//m_sharedobjs->SetVoltageCh1(_voltageCh1);
	// m_sharedobjs->StopTiepieSync();
	//Time = m_timer->getElapsedTimeInSec();
	// std::cout << "End Time RetrieveCh1DataFromInstrument: " << Time << std::endl;
	delete [] Ch1DoubleArray;


	//m_OutputData->TiepieObject::_timeCh1.set_size( _recordLength );

}



public:

 	private:



};

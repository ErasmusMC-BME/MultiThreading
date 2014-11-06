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
#include "tiepieThread.h"

	captureTiepie::captureTiepie(){};
	captureTiepie::~captureTiepie(){};

	captureTiepie::captureTiepie( circ_buffer<circ_buffer_TiepieData>* buff, Timer *timer )
  {
    m_ringBuffer = buff;	 
		m_timer=timer;

  }

	void captureTiepie::Initialize(const char *fmt, ...)
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


	void captureTiepie::ThreadEntryPoint ()
	{


    circ_buffer_TiepieData frame;
    int itr = 0;
		std::cout << "Tiepie capture started" << std::endl;

		std::cout << "Press Key to RetrieveCh1DataFromInstrument" << std::endl;


		getchar();


		_tMeasurementStarted = m_timer->getElapsedTimeInSec();
		std::cout << "TiePie started measuring at time: " << _tMeasurementStarted << std::endl;

		if ( _bTiepieReady )
		{
			// start measuring
			ADC_Start();
			//m_sharedobjs->StopTiepieSync();
			// wait till data is acquired
			while( ADC_Ready() != 1 )
			{
			}
			_bTiepieDataReady = true;
		}
		else
		{
			_bTiepieDataReady = false;
		}
	}



void  captureTiepie::PrepareCh1ForAcq( dword recLen, double* sensCh1, double* fs )
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

void  captureTiepie::RetrieveCh1DataFromInstrument()
{
	vnl_vector<double> _voltageCh1;
	vnl_vector<double> _timeCh1;
	
	double Time = m_timer->getElapsedTimeInSec();
	std::cout << "Start Time RetrieveCh1DataFromInstrument: " << Time << std::endl;
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
	Time = m_timer->getElapsedTimeInSec();
	std::cout << "End Time RetrieveCh1DataFromInstrument: " << Time << std::endl;
	delete [] Ch1DoubleArray;

}


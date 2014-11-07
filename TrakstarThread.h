
#ifndef TRAKSTAR_H_DEF
#define TRAKSTAR_H_DEF
#include "Timer.h"
#include "circ_buffer.txx"
#include <ATC3DG.h>
#include <sample2.h>

struct circ_buffer_TrakstarData 
{
	vnl_matrix<double> measuresCH1;
	vnl_matrix<double> measuresCH2;
	vnl_matrix<double> measuresCH3;
	vnl_matrix<double> measuresCH4;
	//std::vector<vnl_matrix<double>> measures;
};


class showTrakstar 
{
	circ_buffer<circ_buffer_TrakstarData>* m_ringBuffer;

public:
	showTrakstar();

	showTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff , Timer *timer);
	void ThreadEntryPoint();
	void operator () () {	ThreadEntryPoint();};
};

class saveTrakstar 
{
	circ_buffer<circ_buffer_TrakstarData>* m_ringBuffer;
	std::string m_BasePath;
	std::string m_BaseImageFileName;
	std::string m_BaseImageExtension;
public:
	saveTrakstar();

	saveTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff , Timer *timer);
	void Initialize(const char *fmt=NULL, ...);
	void ThreadEntryPoint();
	void operator () () {ThreadEntryPoint();};
};


class captureTrakstar

{
private:

	//	SharedObjects* m_sharedobjs;
	Timer *m_timer;
	bool _bTrakstarFound;
	bool _bTrakstarReady;
	int _numSamples;
	int _numSensors;
	double _samplingFreq;

	std::vector<vnl_matrix<double>> _measures;

	std::vector<int> _sensorID;
	int _transmitterID;
	int errorCode;

  CSensor			*_pSensor;
  CSystem			_ATC3DG;



public:
  circ_buffer<circ_buffer_TrakstarData>* m_ringBuffer;
	captureTrakstar();

	captureTrakstar( circ_buffer<circ_buffer_TrakstarData>* buff, Timer *timer );



	~captureTrakstar();
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
   
		RecordPositionData();
	}

	bool isTrakstarFound(){return _bTrakstarFound;}

	void SetNumSensors(int numSensors)
	{
		_numSensors=numSensors;
	}


void Initialize(const char *fmt=NULL, ...);;

void RecordPositionData();

void errorHandler(int error);
void PrintSystemParamters();
void PrintSensorParameters(int sensorID);
void PrintTransmitterParameters(int transmitterID);

public:

private:
};
#endif
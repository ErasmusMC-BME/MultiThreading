
#include <iostream>

#include <windows.h>  
#include <process.h>   
#include "videoThread.h"
#include "tiepieThread.h"
#include "trakstarThread.h"
#include "View3DThread.h"

//#define USEOPENCVTHREAD
//#define USELEGOTHREAD
//#define USEVIEWINGTHREAD
//#define USETIEPIETHREAD
//#define USERECONSTRUCTIONTHREAD
//#define USETRAKSTARTHREAD

int main( int argc, char** argv )
{


	std::string m_BasePath;
	std::string m_BaseImageFileName;
	std::string m_BaseImageextension;

	if ( argc > 3)
	{
		
		m_BasePath = argv[1];;
		m_BaseImageFileName = argv[2];
		m_BaseImageextension = argv[3];
	}


  std::cout << "Now in the main() function." << std::endl;

	circ_buffer<circ_buffer_TiepieData> *tiepieringBuffer = new circ_buffer<circ_buffer_TiepieData>(100);
	circ_buffer<circ_buffer_VideoData> *videoringBuffer = new circ_buffer<circ_buffer_VideoData>(100);
	circ_buffer<circ_buffer_TrakstarData> *trakstarringBuffer = new circ_buffer<circ_buffer_TrakstarData>(100);
	
	double acquisitionTime = 30; // (sec)

	//initialize Trakstar Params
	double df_TrakStar = 80; // (Hz)
	int recordLength_TrakStar = ceil( df_TrakStar * acquisitionTime );


	// initialize Tiepie Params	
	double df_Tiepie = 1000.0; // (Hz)
	double sensCh1_Tiepie = 1.0;
	dword recordLength_Tiepie = (dword) ceil( df_Tiepie * acquisitionTime );


	Timer  timer;
	timer.start();	// in future use boost timer

	// Create threads
	captureVideo captureVideoThread(videoringBuffer,&timer); 
	showVideo showVideoThread(videoringBuffer,&timer); 
	saveVideo saveVideoThread(videoringBuffer,&timer); 
	View3D View3DThread(videoringBuffer,trakstarringBuffer,tiepieringBuffer,&timer); 
	boost::thread t(&View3D::StaticFunction);

	captureTrakstar captureTrakstarThread(trakstarringBuffer,&timer); 
	showTrakstar showTrakstarThread(trakstarringBuffer,&timer); 
	saveTrakstar savetrakstarThread(trakstarringBuffer,&timer); 
	
#ifdef USETIEPIETHREAD
	captureTiepie captureTiepieThread(tiepieringBuffer,&timer); 
	showTiepie showTiepieThread(tiepieringBuffer,&timer); 
	saveTiepie savetiepieThread(tiepieringBuffer,&timer); 
#endif
	captureTrakstarThread.Initialize("id", recordLength_TrakStar, df_TrakStar  );

	saveVideoThread.Initialize("ccc", "D:/CVTest/","videoDemo",".jpg" );

//Start threads

	boost::thread tvid1(captureVideoThread); 
	boost::thread tvid2(showVideoThread); 
	boost::thread tvid3(saveVideoThread);
	//boost::thread tV3d(View3DThread);
	boost::thread ttrak1(captureTrakstarThread); 
	//boost::thread ttrak2(showTrakstarThread); 
	boost::thread ttrak3(savetrakstarThread); 	

#ifdef USETIEPIETHREAD	
	captureTiepieThread.Initialize("Wdd",  recordLength_Tiepie, sensCh1_Tiepie, df_Tiepie  );
	boost::thread tTiepie1(captureTiepieThread); 
	boost::thread tTiepie2(showTiepieThread); 
	boost::thread tTiepie3(savetiepieThread); 
#endif


	for (;;)
	{

	}
	//producers.interrupt_all();
  std::cin.ignore();

	return 0;
}

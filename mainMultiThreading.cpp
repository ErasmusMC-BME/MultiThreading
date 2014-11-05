// NXT++ test.cpp : Defines the entry point for the console application.
//
//LEGO 


#include <iostream>

#include <windows.h>  
#include <process.h>   
#include "captureVideo.txx"   
#include "captureTiepie.txx"   
#include "capturetrakstar.txx"   
// test pc alex

int main()
{
	//printf( "Now in the main() function.\n" );
  std::cout << "Now in the main() function." << std::endl;

	circ_buffer<circ_buffer_VideoData> *videoringBuffer = new circ_buffer<circ_buffer_VideoData>(100);
	circ_buffer<circ_buffer_TiepieData> *tiepieringBuffer = new circ_buffer<circ_buffer_TiepieData>(100);
	circ_buffer<circ_buffer_TrakstarData> *trakstarringBuffer = new circ_buffer<circ_buffer_TrakstarData>(100);
	double acquisitionTime = 30; // (sec)

	Timer  timer;
	timer.start();	// in future use boost timer


	captureVideo capVid(videoringBuffer,&timer); 
	showVideo showVid(videoringBuffer,&timer); 
	saveVideo saveVid(videoringBuffer,&timer); 

	captureTrakstar capTrak(trakstarringBuffer,&timer); 

	double df_TrakStar = 80; // (Hz)
	int recordLength_TrakStar = ceil( df_TrakStar * acquisitionTime );
	capTrak.Initialize("id", recordLength_TrakStar, df_TrakStar  );



	//showTrakstar showTrak(trakstarringBuffer,&timer); 
	saveTrakstar savetrak(trakstarringBuffer,&timer); 

	captureTiepie capTiepie(tiepieringBuffer,&timer); 
	// initialize Tiepie object	

	double df_Tiepie = 1000.0; // (Hz)
	double sensCh1_Tiepie = 1.0;
	dword recordLength_Tiepie = (dword) ceil( df_Tiepie * acquisitionTime );
	capTiepie.Initialize("Wdd",  recordLength_Tiepie, sensCh1_Tiepie, df_Tiepie  );

//	showTiepie showTiepie(tiepieringBuffer,&timer); 
	saveTiepie savetiepie(tiepieringBuffer,&timer); 


//	c.Initialize();

	boost::thread tvid1(capVid); 
	boost::thread tvid2(showVid); 
	//boost::thread tvid3(saveVid);

	boost::thread ttrak1(capTrak); 
	//boost::thread ttrak2(showTrak); 
	boost::thread ttrak3(savetrak); 	
	
	boost::thread tTiepie1(capTiepie); 
	//boost::thread tTiepie2(showTiepie); 
//	boost::thread tTiepie3(savetiepie); 
	for (;;)
	{

	}


  std::cin.ignore();

	return 0;
}

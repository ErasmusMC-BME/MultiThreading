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

	int numberIterations = 20; 
	Timer  timer;
	timer.start();	// in future use boost timer


	captureVideo capVid(videoringBuffer,&timer); 
	showVideo showVid(videoringBuffer,&timer); 
	saveVideo saveVid(videoringBuffer,&timer); 

	captureTrakstar capTrak(trakstarringBuffer,&timer); 
	//showTrakstar showTrak(trakstarringBuffer,&timer); 
	saveTrakstar savetrak(trakstarringBuffer,&timer); 

	captureTiepie capTiepie(tiepieringBuffer,&timer); 
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

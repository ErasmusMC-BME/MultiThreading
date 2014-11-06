// NXT++ test.cpp : Defines the entry point for the console application.
//
//LEGO 

#include <itkGPUImage.h>
#include <itkGPUGradientAnisotropicDiffusionImageFilter.h>
#include <itkGradientAnisotropicDiffusionImageFilter.h>
#include <itkGPUDiscreteGaussianImageFilter.h>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <iostream>

#include <windows.h>  
#include <process.h>   
#include "videoThread.h"
#include "tiepieThread.h"
#include "trakstarThread.h"  
// test pc alex






int main()
{

	// Create a circular buffer with a capacity for 3 integers.
boost::circular_buffer<int> cb(3);

// Insert threee elements into the buffer.
cb.push_back(1);
cb.push_back(2);
cb.push_back(3);

int a = cb[0];  // a == 1
int b = cb[1];  // b == 2
int c = cb[2];  // c == 3

// The buffer is full now, so pushing subsequent
// elements will overwrite the front-most elements.

cb.push_back(4);  // Overwrite 1 with 4.
cb.push_back(5);  // Overwrite 2 with 5.

// The buffer now contains 3, 4 and 5.
a = cb[0];  // a == 3
b = cb[1];  // b == 4
c = cb[2];  // c == 5

// Elements can be popped from either the front or the back.
cb.pop_back();  // 5 is removed.
int size = cb.size();
cb.pop_front(); // 3 is removed.
 size = cb.size();
// Leaving only one element with value = 4.
int d = cb[0];  // d == 4
cb.push_back(7);  // Overwrite 1 with 4.
size = cb.size();
cb.push_back(8); 
size = cb.size();
cb.push_back(7);  // Overwrite 1 with 4.
size = cb.size();
cb.push_back(8); 
size = cb.size();
return 0;

	{
		typedef  unsigned char InputPixelType;
		typedef   unsigned char  OutputPixelType;
		typedef itk::GPUImage< InputPixelType,  3 >   InputImageType;
		typedef itk::GPUImage< OutputPixelType, 3 >   OutputImageType;
		typedef itk::ImageFileReader< InputImageType  >  ReaderType;
		typedef itk::ImageFileWriter< OutputImageType >  WriterType;


		// macro to set if GPU is used


		std::string inFile( "D:/Data/GOKTAS/LinearCartVolume001.mhd" );
		std::string outFile( "D:/Data/GOKTAS/LinearCartVolume001Filt.mhd" );

		float variance = 4.0;

		typedef itk::GPUDiscreteGaussianImageFilter< InputImageType,	OutputImageType> GPUDiscreteGaussianFilterType;
		typedef itk::GradientAnisotropicDiffusionImageFilter< InputImageType, OutputImageType > CPUAnisoDiffFilterType; 
		typedef itk::GPUGradientAnisotropicDiffusionImageFilter< InputImageType, OutputImageType > GPUAnisoDiffFilterType; 

		GPUDiscreteGaussianFilterType::Pointer GPUFilter = GPUDiscreteGaussianFilterType::New();
		CPUAnisoDiffFilterType::Pointer CPUFilter1 = CPUAnisoDiffFilterType::New(); 
		GPUAnisoDiffFilterType::Pointer GPUFilter1 = GPUAnisoDiffFilterType::New(); 




		ReaderType::Pointer reader;

		WriterType::Pointer writer;

		reader = ReaderType::New();

		writer = WriterType::New();


		reader->SetFileName( inFile );

		writer->SetFileName( outFile );

		reader->Update();
		CPUFilter1->SetInput( reader->GetOutput() );
		CPUFilter1->SetNumberOfIterations( 9 ); 
		CPUFilter1->SetTimeStep( 0.0325 );//125 ); 
		CPUFilter1->SetConductanceParameter( 3.0 ); 
		CPUFilter1->UseImageSpacingOn(); 

		GPUFilter1->SetInput( reader->GetOutput() );
		GPUFilter1->SetNumberOfIterations( 9 ); 
		GPUFilter1->SetTimeStep( 0.0325 );//125 ); 
		GPUFilter1->SetConductanceParameter( 3.0 ); 
		GPUFilter1->UseImageSpacingOn(); 

		GPUFilter->SetInput( reader->GetOutput() );

		GPUFilter->SetVariance( variance );
		GPUFilter->ReleaseDataFlagOn();
		GPUFilter->SetInternalNumberOfStreamDivisions(4);

		GPUFilter->SetMaximumKernelWidth(10);

		GPUFilter->SetUseImageSpacingOff();

		//    GPUFilter->DebugOn();

		//    GPUFilter->GPUEnabledOff();

		GPUFilter->Print(std::cout);

		GPUFilter->Update();



		GPUFilter->GetOutput()->UpdateBuffers(); // synchronization point

		writer->SetInput( GPUFilter1->GetOutput() ); 
		writer->Update();
		writer->Write();

	}


	for (;;)
	{

	}

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

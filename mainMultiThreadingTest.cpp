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

// test pc alex






int main()
{


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

	
	return 0;
}

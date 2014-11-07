#include <vtkMatrix4x4.h>
#include <vtkCellArray.h>
#include <vtkTransform.h>



#include "vtkSmartPointer.h"
#include "vtkImageReader.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
//#include "vtkImageMapper3D.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformation.h"
#include <vtkMetaImageReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkImageViewer2.h>
#include <vtkImageViewer.h>
#include <vtkPoints.h>
#include <vtkLandmarkTransform.h>
#include <vtkTransform.h>
#include <vtkMath.h>
#include <vtkBorderRepresentation.h>
#include <vtkBorderWidget.h>

#include "vtkCamera.h"
#include "vtkColorTransferFunction.h"
#include "vtkPiecewiseFunction.h"
#include "vtkPlanes.h"
#include "vtkProperty.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkImageMapToColors.h"
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataWriter.h>
#include <vtkTransformPolyDataFilter.h>
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkPointData.h"
#include "vtkCellArray.h"
#include "vtkPolyDataMapper.h"
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataWriter.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkParametricFunctionSource.h>
#include <vtkSplineWidget.h>
#include <vtkKochanekSpline.h>
#include <vtkParametricSpline.h>
#include <vtkPlaneSource.h>
#include <vtkImageProperty.h>

#include "vtkSmartPointer.h"
#include "vtkPNGReader.h"
#include "vtkLookupTable.h" // not needed?
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"

#include "vtkMatrix4x4.h"
#include "vtkTransform.h"
#include "vtkImageViewer.h"
#include "vtkCamera.h"
#include "vtkImageData.h"
#include "vtkImageImport.h"


#include "View3DThread.h"
  // some additional stuff
  static double XYPlaneElements[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 };

  static double XZPlaneElements[16] = {
    1, 0, 0, 0,
    0, 0, 1, 0,
    0,-1, 0, 0,
    0, 0, 0, 1 };

  static double YZPlaneElements[16] = {
    0, 0,-1, 0,
    1, 0, 0, 0,
    0,-1, 0, 0,
    0, 0, 0, 1 };

void fromIpl2Vtk( IplImage*  _src, vtkImageImport* importer ) 
{ 
    importer->SetDataSpacing( 1, 1, 1 ); 
    importer->SetDataOrigin( 0, 0, 0 ); 
    importer->SetWholeExtent(   0, _src->width-1, 0, _src->height-1, 0, _src->nChannels-1 ); 
    importer->SetDataExtentToWholeExtent(); 
    importer->SetDataScalarTypeToUnsignedChar(); 
    importer->SetNumberOfScalarComponents( _src->nChannels ); 
    importer->SetImportVoidPointer( _src->imageData ); 
    importer->Update(); 
} 

View3D::View3D(){};
View3D::View3D( circ_buffer<circ_buffer_VideoData>* buffvideo ,  circ_buffer<circ_buffer_TrakstarData>* buffTrakstar , circ_buffer<circ_buffer_TiepieData>* buffTiepie ,Timer *timer)

{
	m_VideoRingBuffer = buffvideo;
	m_TrakstarRingBuffer = buffTrakstar;
	m_TiepieingBuffer = buffTiepie;
	_PreviousiplImg=NULL;
	_ActualiplImg=NULL;

	_importer = vtkSmartPointer<vtkImageImport>::New();
	_GrabberPlaneimageActor =	vtkSmartPointer<vtkImageActor>::New();
	_GrabberPlaneMapper = vtkSmartPointer<vtkImageMapToColors>::New();
	_GrabberPlaneRenderer = vtkSmartPointer<vtkRenderer>::New();
	_GrabberPlaneRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		std::string fileName = "D:/Data/ExperimentalData/EPExperiments/EP1_24-Feb-2014/consecutiveInputDataNC/IM_0007/600Images/2DinputImage_0584.png";
	vtkSmartPointer<vtkPNGReader> reader = vtkPNGReader::New();
	reader->SetFileName( fileName.c_str() );
	reader->Update();
			
	int* Dimensions = reader->GetOutput()->GetDimensions(); //429 608
	double * Spacing=reader->GetOutput()->GetSpacing();
	
	double Origin[2];
	Origin[0]=Dimensions[0]*Spacing[0];
	Origin[1]=Dimensions[1]*Spacing[1];

  vtkSmartPointer<vtkMatrix4x4> resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
  resliceAxes->DeepCopy(XZPlaneElements);
  resliceAxes->SetElement(0, 3, 0.0 );resliceAxes->SetElement(1, 3, Origin[0]/2 );resliceAxes->SetElement(2, 3, 0.0 );
  
  vtkSmartPointer<vtkTransform> resliceAxesTransform = vtkSmartPointer<vtkTransform>::New();
  resliceAxesTransform->SetMatrix( resliceAxes );
  resliceAxesTransform->Update();


  resliceAxes->DeepCopy(YZPlaneElements);
  resliceAxes->SetElement(0, 3, Origin[0]/2);resliceAxes->SetElement(1, 3, 0.0 );resliceAxes->SetElement(2, 3, 0.0 );
  
	vtkSmartPointer<vtkTransform> resliceAxesTransform2 = vtkSmartPointer<vtkTransform>::New();
  resliceAxesTransform2->SetMatrix( resliceAxes );
  resliceAxesTransform2->Update();

	
	resliceAxes->DeepCopy(XYPlaneElements);
	resliceAxes->SetElement(0, 3, 0.0 );resliceAxes->SetElement(1, 3, 0 );resliceAxes->SetElement(2, 3, -Origin[1]/2  );

	vtkSmartPointer<vtkTransform> resliceAxesTransform3 = vtkSmartPointer<vtkTransform>::New();
	resliceAxesTransform3->SetMatrix( resliceAxes );
	resliceAxesTransform3->Update();
	  
  // Create a greyscale lookup table
  vtkSmartPointer<vtkLookupTable> table = vtkSmartPointer<vtkLookupTable>::New();
  table->SetRange(0, 255); // image intensity range
  table->SetValueRange(0.0, 1.0); // from black to white
  table->SetSaturationRange(0.0, 0.0); // no color saturation
  table->SetRampToLinear();
  table->Build();

  vtkSmartPointer<vtkImageMapToColors> mapper2 = vtkSmartPointer<vtkImageMapToColors>::New();
  mapper2->SetLookupTable( table );
  mapper2->SetInputConnection( reader->GetOutputPort() );
  // actor
  vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
  actor->SetUserTransform( resliceAxesTransform );
  actor->GetMapper()->SetInputConnection( mapper2->GetOutputPort() );

  
  vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();
  actor2->SetUserTransform( resliceAxesTransform2 );
	actor2->GetMapper()->SetInputConnection( mapper2->GetOutputPort() );


	_GrabberPlaneMapper->SetInputConnection( reader->GetOutputPort() );
	_GrabberPlaneimageActor->SetUserTransform( resliceAxesTransform3 );
	_GrabberPlaneimageActor->GetMapper()->SetInputConnection(_GrabberPlaneMapper->GetOutputPort() );

  // renderer

	
  _GrabberPlaneRenderer->AddActor(_GrabberPlaneimageActor);
  _GrabberPlaneRenderer->AddActor(actor);
	_GrabberPlaneRenderer->AddActor(actor2);

  //render window
  _GrabberPlaneRenderWindow->AddRenderer(_GrabberPlaneRenderer);
	_GrabberPlaneInteractor =    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  _GrabberPlaneRenderWindow->SetInteractor( _GrabberPlaneInteractor );

	//_GrabberPlaneRenderWindow->SetSize( 255,255);
 // _GrabberPlaneRenderWindow->Render();

 // _GrabberPlaneInteractor ->Start(


}

void WindowThreadEntryPoint(circ_buffer<circ_buffer_VideoData>*	m_VideoRingBuffer, vtkSmartPointer<vtkImageActor> _GrabberPlaneimageActor,vtkSmartPointer<vtkRenderWindowInteractor> _GrabberPlaneInteractor ,	vtkSmartPointer<vtkRenderWindow> _GrabberPlaneRenderWindow)
{
	circ_buffer_VideoData frame;
	
	_GrabberPlaneRenderWindow->SetSize( 255,255);
	 vtkSmartPointer<vtkImageImport> importer = vtkSmartPointer<vtkImageImport>::New();
	for (;;)
	{
		if ( m_VideoRingBuffer->size() > 2 )
		{
			frame = m_VideoRingBuffer->back();
			IplImage* _ActualiplImg =cvCloneImage(&(IplImage)frame.Mat);
			fromIpl2Vtk( _ActualiplImg, importer ) ;

			_GrabberPlaneimageActor->SetInput(importer->GetOutput());
			_GrabberPlaneRenderWindow->Render();
			_GrabberPlaneInteractor->Start();
		}
	}
};

void View3D::ThreadEntryPoint () 
{

	circ_buffer_VideoData frame;
	int itr = 0;
	//cv::namedWindow( "threadedVideoShow",  cv::WINDOW_AUTOSIZE );
//	boost::thread tvid1(&View3D::WindowThreadEntryPoint); 
	boost::thread deep_thought_2(WindowThreadEntryPoint,	m_VideoRingBuffer,_GrabberPlaneimageActor,_GrabberPlaneInteractor , _GrabberPlaneRenderWindow);

//  m_thread=new boost::thread(boost::ref(*this)); 
	for (;;)
	{
		if ( m_VideoRingBuffer->size() > 2 )
		{
			frame = m_VideoRingBuffer->back();
			//cv::imshow( "threadedVideoShow", frame.Mat );
			//cv::waitKey(10);

		
		_ActualiplImg=cvCloneImage(&(IplImage)frame.Mat);
		fromIpl2Vtk( _ActualiplImg, _importer ) ;

		_GrabberPlaneimageActor->SetInput(_importer->GetOutput());
		//_GrabberPlaneimageActor->GetMapper()->Modified();
	//	_GrabberPlaneimageActor->GetMapper()->Update();
		//_GrabberPlaneRenderWindow->Render();
		if(_PreviousiplImg) cvReleaseImage(&_PreviousiplImg);
		_PreviousiplImg=_ActualiplImg;


			//cv::Scalar meanVal = cv::mean( frame.Mat, cv::Mat() );
		//	std::cout << "GET frame at iteration " << itr << ". Buffer size: " << m_ringBuffer->size() << ". Mean intensity in frame: " << meanVal[0] << std::endl;
			++itr;

		 try 
		 { 
			// Interrupt can only occur in wait/sleep or  
			// join operation. If you don't do that,  
			// call interuption_point(). Remove this line,  
			// and the thread will never be interrupted. 
			boost::this_thread::interruption_point(); 
		 } 
		 catch(const boost::thread_interrupted&) 
		 { 
			// Thread interruption request received, break the loop 
			cout<<"- Thread interrupted. Exiting thread."<<endl; 
			break; 
		 } 



		}
	}
}



#ifndef View3D_H_DEF
#define View3D_H_DEF

#include "Timer.h"
#include "circ_buffer.txx"
#include "opencv2/opencv.hpp"
#include "itkNumericSeriesFileNames.h"
#include "tiepieThread.h"
#include "trakstarThread.h"
#include "videoThread.h"
#include "vtkImageActor.h"
#include "vtkSmartPointer.h"
#include "vtkImageMapToColors.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"



class View3D 
{
	circ_buffer<circ_buffer_VideoData>*			m_VideoRingBuffer;
	circ_buffer<circ_buffer_TrakstarData>*	m_TrakstarRingBuffer;
	circ_buffer<circ_buffer_TiepieData>*		m_TiepieingBuffer;

private: 
 	public:

	vtkSmartPointer<vtkImageMapToColors> _GrabberPlaneMapper; 
	vtkSmartPointer<vtkImageActor> _GrabberPlaneimageActor;
	vtkSmartPointer<vtkRenderer> _GrabberPlaneRenderer ;
	vtkSmartPointer<vtkRenderWindow> _GrabberPlaneRenderWindow ;
	vtkSmartPointer<vtkRenderWindowInteractor> _GrabberPlaneInteractor ;

public:

	View3D();
	static void StaticFunction()
	{
		vtkSmartPointer<vtkRenderer> GrabberPlaneRenderer;
	}

	View3D( circ_buffer<circ_buffer_VideoData>* buffvideo ,  circ_buffer<circ_buffer_TrakstarData>* buffTrakstar , circ_buffer<circ_buffer_TiepieData>* buffTiepie ,Timer *timer);
	void ThreadEntryPoint();
	void operator () () {	ThreadEntryPoint();};

};
#endif
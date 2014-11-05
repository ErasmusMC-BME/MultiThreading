PROJECT( MultiThread )
#https://github.com/sintefmath/sist/blob/master/CMakeLists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

INCLUDE ($ENV{BME_BASE_DIR}/Config/BMECMakeLists.txt)
INCLUDE_DIRECTORIES($ENV{NIG_COMMON_DIR})
INCLUDE_DIRECTORIES($ENV{NIG_COMMON_DIR}/../Timer)
SET( MultiThreadFiles
	mainMultiThreading.cpp
	captureTrakstar.txx
	captureTiepie.txx
	captureVideo.txx
	circ_buffer.txx
	$ENV{NIG_COMMON_DIR}/../Timer/Timer.cpp
	$ENV{NIG_COMMON_DIR}/../Timer/Timer.h
 	)

# common stuff

INCLUDE_DIRECTORIES( $ENV{ALEX_COMMON_DIR} )

ADD_EXECUTABLE( MultiThread ${MultiThreadFiles})
TARGET_LINK_LIBRARIES ( MultiThread ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} )



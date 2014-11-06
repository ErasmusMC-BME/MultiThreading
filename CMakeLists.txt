PROJECT( MultiThread )
#https://github.com/sintefmath/sist/blob/master/CMakeLists.txt
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

INCLUDE ($ENV{BME_BASE_DIR}/Config/BMECMakeLists.txt)
INCLUDE_DIRECTORIES($ENV{NIG_COMMON_DIR})
INCLUDE_DIRECTORIES($ENV{NIG_COMMON_DIR}/../Timer)

SET (EXT_hdr 
	$ENV{BME_BASE_DIR}/TiePie/include/TiePie.h
	$ENV{BME_BASE_DIR}/TiePie/include/TiePieDLL.h
	$ENV{BME_BASE_DIR}/Ascension/Include/ATC3DG.h
	)
SET (EXT_files  
	$ENV{BME_BASE_DIR}/TiePie/Source/tiepiedll.cpp
	)
SET( MultiThreadBaseFiles 
	videoThread.h
	trakstarThread.h
	tiepieThread.h
	captureVideo.cpp
	captureTrakstar.cpp
	captureTiepie.cpp
	showVideo.cpp
	showTrakstar.cpp
	showTiepie.cpp
	saveVideo.cpp
	saveTrakstar.cpp
	saveTiepie.cpp
	circ_buffer.txx
	$ENV{NIG_COMMON_DIR}/../Timer/Timer.cpp
	$ENV{NIG_COMMON_DIR}/../Timer/Timer.h
	${EXT_hdr}
	${EXT_files}
 	)

SET( MultiThreadFiles
	mainMultiThreading.cpp
	${MultiThreadBaseFiles}
	)

SET( MultiThreadTestFiles
	mainMultiThreadingTest.cpp
	${MultiThreadBaseFiles}
 	)

# common stuff

INCLUDE_DIRECTORIES( $ENV{ALEX_COMMON_DIR} )



   

LINK_DIRECTORIES ($ENV{BME_BASE_DIR}/Ascension/Lib) 

INCLUDE_DIRECTORIES($ENV{BME_BASE_DIR}/Ascension/Include)
INCLUDE_DIRECTORIES($ENV{BME_BASE_DIR}/TiePie/include)

ADD_EXECUTABLE( MultiThreadTest ${MultiThreadTestFiles})
TARGET_LINK_LIBRARIES ( MultiThreadTest ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} ATC3DG )
ADD_EXECUTABLE( MultiThread ${MultiThreadFiles})
TARGET_LINK_LIBRARIES ( MultiThread ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} ATC3DG )




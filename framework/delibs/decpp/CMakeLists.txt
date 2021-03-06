# cmake file for drawElements C++ base library

if (NOT DE_DEFS)
	message(FATAL_ERROR "Include Defs.cmake")
endif ()

set(DECPP_SRCS
	deBlockBuffer.cpp
	deBlockBuffer.hpp
	deCommandLine.cpp
	deCommandLine.hpp
	deDefs.cpp
	deDefs.hpp
	deDirectoryIterator.cpp
	deDirectoryIterator.hpp
	deDynamicLibrary.cpp
	deDynamicLibrary.hpp
	deFilePath.cpp
	deFilePath.hpp
	deMemPool.cpp
	deMemPool.hpp
	deMutex.cpp
	deMutex.hpp
	dePoolArray.cpp
	dePoolArray.hpp
	dePoolString.cpp
	dePoolString.hpp
	deProcess.cpp
	deProcess.hpp
	deRandom.cpp
	deRandom.hpp
	deRingBuffer.cpp
	deRingBuffer.hpp
	deSemaphore.cpp
	deSemaphore.hpp
	deSTLUtil.hpp
	deSTLUtil.cpp
	deSharedPtr.cpp
	deSharedPtr.hpp
	deSocket.cpp
	deSocket.hpp
	deStringUtil.cpp
	deStringUtil.hpp
	deThread.cpp
	deThread.hpp
	deThreadLocal.cpp
	deThreadLocal.hpp
	deThreadSafeRingBuffer.cpp
	deThreadSafeRingBuffer.hpp
	deUniquePtr.cpp
	deUniquePtr.hpp
	deArrayBuffer.cpp
	deArrayBuffer.hpp
	)

add_library(decpp STATIC ${DECPP_SRCS})
target_link_libraries(decpp debase depool dethread deutil)

# glu - Generic OpenGL (ES 2.0/3.0) test utilities

if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/simplereference)
	add_subdirectory(simplereference)
endif ()

add_subdirectory(wrapper)

set(GLUTIL_SRCS
	gluCallLogWrapper.hpp
	gluContextInfo.cpp
	gluContextInfo.hpp
	gluDefs.cpp
	gluDefs.hpp
	gluDrawUtil.cpp
	gluDrawUtil.hpp
	gluES3PlusWrapperContext.cpp
	gluES3PlusWrapperContext.hpp
	gluFboRenderContext.cpp
	gluFboRenderContext.hpp
	gluPixelTransfer.cpp
	gluPixelTransfer.hpp
	gluProgramInterfaceQuery.cpp
	gluProgramInterfaceQuery.hpp
	gluRenderConfig.cpp
	gluRenderConfig.hpp
	gluRenderContext.cpp
	gluRenderContext.hpp
	gluShaderProgram.cpp
	gluShaderProgram.hpp
	gluShaderUtil.cpp
	gluShaderUtil.hpp
	gluStateReset.cpp
	gluStateReset.hpp
	gluTexture.cpp
	gluTexture.hpp
	gluTextureUtil.cpp
	gluTextureUtil.hpp
	gluVarType.cpp
	gluVarType.hpp
	gluVarTypeUtil.cpp
	gluVarTypeUtil.hpp
	gluStrUtil.cpp
	gluStrUtil.hpp
	gluCallLogWrapper.cpp
	gluCallLogWrapper.hpp
	gluObjectWrapper.cpp
	gluObjectWrapper.hpp
	gluContextFactory.hpp
	gluContextFactory.cpp
	gluDummyRenderContext.cpp
	gluDummyRenderContext.hpp
	gluPlatform.cpp
	gluPlatform.hpp
	)

set(GLUTIL_LIBS
	tcutil
	glwrapper
	)

add_library(glutil STATIC ${GLUTIL_SRCS})
target_link_libraries(glutil ${GLUTIL_LIBS})

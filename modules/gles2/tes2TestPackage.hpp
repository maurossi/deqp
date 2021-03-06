#ifndef _TES2TESTPACKAGE_HPP
#define _TES2TESTPACKAGE_HPP
/*-------------------------------------------------------------------------
 * drawElements Quality Program OpenGL ES 2.0 Module
 * -------------------------------------------------
 *
 * Copyright 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *//*!
 * \file
 * \brief OpenGL ES 2.0 Test Package
 *//*--------------------------------------------------------------------*/

#include "tcuDefs.hpp"
#include "tcuTestPackage.hpp"
#include "tes2TestCaseWrapper.hpp"
#include "tes2Context.hpp"
#include "tcuResource.hpp"

namespace deqp
{
namespace gles2
{

class PackageContext
{
public:
									PackageContext			(tcu::TestContext& testCtx);
									~PackageContext			(void);

	Context&						getContext				(void) { return *m_context;		}
	tcu::TestCaseWrapper&			getTestCaseWrapper		(void) { return *m_caseWrapper; }

private:
	Context*						m_context;
	TestCaseWrapper*				m_caseWrapper;
};

class TestPackage : public tcu::TestPackage
{
public:
									TestPackage				(tcu::TestContext& testCtx);
	virtual							~TestPackage			(void);

	virtual void					init					(void);
	virtual void					deinit					(void);

	tcu::TestCaseWrapper&			getTestCaseWrapper		(void) { return m_packageCtx->getTestCaseWrapper(); }
	tcu::Archive&					getArchive				(void) { return m_archive; }

private:
	PackageContext*					m_packageCtx;
	tcu::ResourcePrefix				m_archive;
};

} // gles2
} // deqp

#endif // _TES2TESTPACKAGE_HPP

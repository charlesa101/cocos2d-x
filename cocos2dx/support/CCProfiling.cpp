/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCProfiling.h"

#if CC_ENABLE_PROFILERS

#include <stdio.h>
#include <iostream>

namespace cocos2d
{
	using namespace std;
	static CCProfiler *g_sSharedProfiler;

	CCProfiler* CCProfiler::sharedProfiler(void)
	{
        if (! g_sSharedProfiler)
		{
			g_sSharedProfiler = new CCProfiler();
			g_sSharedProfiler->init();
		}

		return g_sSharedProfiler;
	}

	CCProfilingTimer* CCProfiler::timerWithName(const char *pszTimerName, NSObject *pInstance)
	{
		CCProfiler *p = CCProfiler::sharedProfiler();
		CCProfilingTimer *t = new CCProfilingTimer();
		t->initWithName(pszTimerName, pInstance);
		p->m_pActiveTimers->addObject(t);
		t->release();

		return t;
	}

	void CCProfiler::releaseTimer(CCProfilingTimer *pTimer)
	{
		CCProfiler *p = CCProfiler::sharedProfiler();
		p->m_pActiveTimers->removeObject(pTimer);
	}

	bool CCProfiler::init()
	{
		m_pActiveTimers = new NSMutableArray<CCProfilingTimer*>();

		return true;
	}

	CCProfiler::~CCProfiler(void)
	{
		CCX_SAFE_RELEASE(m_pActiveTimers);
	}

	void CCProfiler::displayTimers()
	{
		NSMutableArray<CCProfilingTimer*>::NSMutableArrayIterator it;
		for (it = m_pActiveTimers->begin(); it != m_pActiveTimers->end(); ++it)
		{
			char *pszDescription = (*it)->description();
			cout << pszDescription << endl;
			delete pszDescription;
		}
	}

	// implementation of CCProfilingTimer

	bool CCProfilingTimer::initWithName(const char* pszTimerName, NSObject *pInstance)
	{
		char tmp[100];
		sprintf(tmp, "%s (0x%.8x)", pszTimerName, pInstance);
		m_NameStr = string(tmp);

		return true;
	}

	CCProfilingTimer::~CCProfilingTimer(void)
	{
		
	}

	char* CCProfilingTimer::description()
	{
        char *pszDes = new char[m_NameStr.length() + sizeof(double) + 20];
		sprintf(pszDes, "%s: avg time, %fms", m_NameStr.c_str(), m_dAverageTime);
		return pszDes;
	}

	void CCProfilingBeginTimingBlock(CCProfilingTimer *pTimer)
	{
		CCTime::gettimeofday(&pTimer->getStartTime(), NULL);
	}

	void CCProfilingEndTimingBlock(CCProfilingTimer *pTimer)
	{
        struct cc_timeval currentTime;
		CCTime::gettimeofday(&currentTime, NULL);
		CCTime::timersub(&currentTime, &pTimer->getStartTime(), &currentTime);
		double duration = currentTime.tv_sec * 1000.0 + currentTime.tv_usec / 1000.0;

		// return in milliseconds
		pTimer->setAverageTime((pTimer->getAverageTime() + duration) / 2.0f);
	}

} // end of namespace cocos2d

#endif // CC_ENABLE_PROFILERS

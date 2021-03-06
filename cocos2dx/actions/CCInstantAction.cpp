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

#include "CCInstantAction.h"
#include "CCXCocos2dDefine.h"
#include "CCNode.h"
#include "CCSprite.h"
namespace cocos2d {
	//
	// InstantAction
	//
	CCInstantAction::CCInstantAction()
	{
		m_fDuration = 0;
	}

	NSObject * CCInstantAction::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone *pNewZone = NULL;
		CCInstantAction *pRet = NULL;
		if (pZone && pZone->m_pCopyObject)
		{
			pRet = (CCInstantAction*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new CCInstantAction();
			pZone = pNewZone = new NSZone(pRet);
		}
		CCFiniteTimeAction::copyWithZone(pZone);
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}
	bool CCInstantAction::isDone()
	{
		return true;
	}
	void CCInstantAction::step(ccTime dt)
	{
		update(1);
	}
	void CCInstantAction::update(ccTime time)
	{
		// ignore
	}
	CCFiniteTimeAction * CCInstantAction::reverse()
	{
		return (CCFiniteTimeAction*)(copy()->autorelease());
	}

	//
	// Show
	//
	CCShow* CCShow::action()
	{
		CCShow* pRet = new CCShow();
		pRet->autorelease();
		return pRet;
	}
	void CCShow::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		pTarget->setIsVisible(true);
	}
	CCFiniteTimeAction *CCShow::reverse()
	{
		return (CCFiniteTimeAction*)(CCHide::action());
	}
	//
	// Hide
	//
	CCHide * CCHide::action()
	{
		CCHide *pRet = new CCHide();
		pRet->autorelease();
		return pRet;
	}
	void CCHide::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		pTarget->setIsVisible(false);
	}

	CCFiniteTimeAction *CCHide::reverse()
	{
		return (CCFiniteTimeAction*)(CCShow::action());
	}

	//
	// ToggleVisibility
	//
	CCToggleVisibility * CCToggleVisibility::action()
	{
		CCToggleVisibility *pRet = new CCToggleVisibility();
		pRet->autorelease();
		return pRet;
	}
	void CCToggleVisibility::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		pTarget->setIsVisible(! pTarget->getIsVisible());
	}
	//
	// FlipX
	//
	CCFlipX *CCFlipX::actionWithFlipX(bool x)
	{
		CCFlipX *pRet = new CCFlipX();
		pRet->initWithFlipX(x);
		pRet->autorelease();
		return pRet;
	}
	bool CCFlipX::initWithFlipX(bool x)
	{
		m_bFlipX = x;
		return true;
	}
	void CCFlipX::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		((CCSprite*)(pTarget))->setFlipX(m_bFlipX);
	}

	CCFiniteTimeAction* CCFlipX::reverse()
	{
		return CCFlipX::actionWithFlipX(!m_bFlipX);
	}

	NSObject * CCFlipX::copyWithZone(NSZone *pZone)
	{
		NSZone *pNewZone = NULL;
		CCFlipX *pRet = NULL;
		if (pZone && pZone->m_pCopyObject)
		{
			pRet = (CCFlipX*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new CCFlipX();
			pZone = pNewZone = new NSZone(pRet);
		}
		CCInstantAction::copyWithZone(pZone);
		pRet->initWithFlipX(m_bFlipX);
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}

	//
	// FlipY
	//
	CCFlipY * CCFlipY::actionWithFlipY(bool y)
	{
		CCFlipY *pRet = new CCFlipY();
		pRet->initWithFlipY(y);
		pRet->autorelease();
		return pRet;
	}
	bool CCFlipY::initWithFlipY(bool y)
	{
		m_bFlipY = y;
		return true;
	}

	void CCFlipY::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		((CCSprite*)(pTarget))->setFlipY(m_bFlipY);
	}

	CCFiniteTimeAction* CCFlipY::reverse()
	{
		return CCFlipY::actionWithFlipY(!m_bFlipY);
	}

	NSObject * CCFlipY::copyWithZone(NSZone *pZone)
	{
		NSZone *pNewZone = NULL;
		CCFlipY *pRet = NULL;
		if (pZone && pZone->m_pCopyObject)
		{
			pRet = (CCFlipY*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new CCFlipY();
			pZone = pNewZone = new NSZone(pRet);
		}
		CCInstantAction::copyWithZone(pZone);
		pRet->initWithFlipY(m_bFlipY);
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}

	//
	// Place
	//
	CCPlace * CCPlace::actionWithPosition(CGPoint pos)
	{
		CCPlace *pRet = new CCPlace();
		pRet->initWithPosition(pos);
		pRet->autorelease();
		return pRet;
	}
	bool CCPlace::initWithPosition(CGPoint pos)
	{
		m_tPosition = pos;
		return true;
	}

	NSObject * CCPlace::copyWithZone(NSZone *pZone)
	{
		NSZone *pNewZone = NULL;
		CCPlace *pRet = NULL;
		if (pZone && pZone->m_pCopyObject)
		{
			pRet = (CCPlace*)(pZone->m_pCopyObject);
		}
		else
		{
			pRet = new CCPlace();
			pZone = pNewZone = new NSZone(pRet);
		}
		CCInstantAction::copyWithZone(pZone);
		pRet->initWithPosition(m_tPosition);
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}

	void CCPlace::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		m_pTarget->setPosition(m_tPosition);
	}

	//
	// CallFunc
	//

	CCCallFunc * CCCallFunc::actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFunc selector)
	{
		CCCallFunc* pCallFunc = new CCCallFunc();
		pCallFunc->autorelease();

		pCallFunc->initWithTarget(pSelectorTarget);
		pCallFunc->m_pCallFunc = selector;

		return pCallFunc;
	}
	bool CCCallFunc::initWithTarget(SelectorProtocol* pSelectorTarget)
	{
		if (pSelectorTarget)
		{
			pSelectorTarget->selectorProtocolRetain();
		}
		if (m_pSelectorTarget)
		{
			m_pSelectorTarget->selectorProtocolRelease();
		}
		m_pSelectorTarget = pSelectorTarget;
		return true;
	}

	NSObject * CCCallFunc::copyWithZone(cocos2d::NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCCallFunc* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
			pRet = (CCCallFunc*)(pZone->m_pCopyObject);
		else
		{
			pRet = new CCCallFunc();
			pZone = pNewZone = new NSZone(pRet);
		}
		CCInstantAction::copyWithZone(pZone);
		pRet->initWithTarget(m_pSelectorTarget);
		pRet->m_pCallFunc = m_pCallFunc;
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}
	void CCCallFunc::startWithTarget(CCNode *pTarget)
	{
		CCInstantAction::startWithTarget(pTarget);
		this->execute();
	}
	void CCCallFunc::execute()
	{
		if(m_pCallFunc)
		{
			(m_pSelectorTarget->*m_pCallFunc)();
		}
	}
	//
	// CallFuncN
	//
	void CCCallFuncN::execute()
	{
		if(m_pCallFuncN)
		{
			(m_pSelectorTarget->*m_pCallFuncN)(m_pTarget);
		}
	}
	CCCallFuncN * CCCallFuncN::actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncN selector)
	{
		CCCallFuncN *pRet = new CCCallFuncN();
		if(pRet->initWithTarget(pSelectorTarget, selector))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet);
		return NULL;
	}
	bool CCCallFuncN::initWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncN selector)
	{
		if( CCCallFunc::initWithTarget(pSelectorTarget) ) 
		{
			m_pCallFuncN = selector;
			return true;
		}
		return false;
	}
	NSObject * CCCallFuncN::copyWithZone(NSZone* zone)
	{
		NSZone* pNewZone = NULL;
		CCCallFuncN* pRet = NULL;
		if(zone && zone->m_pCopyObject) //in case of being called at sub class
			pRet = (CCCallFuncN*)(zone->m_pCopyObject);
		else
		{
			pRet = new CCCallFuncN();
			zone = pNewZone = new NSZone(pRet);
		}
		CCCallFunc::copyWithZone(zone);
		pRet->initWithTarget(m_pSelectorTarget, m_pCallFuncN);
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}
	//
	// CallFuncND
	//
	CCCallFuncND * CCCallFuncND::actionWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncND selector, void* d)
	{
		CCCallFuncND* pRet = new CCCallFuncND();
		if (pRet->initWithTarget(pSelectorTarget, selector, d))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet);
		return NULL;
	}

	bool CCCallFuncND::initWithTarget(SelectorProtocol* pSelectorTarget, SEL_CallFuncND selector, void* d)
	{
		if( CCCallFunc::initWithTarget(pSelectorTarget) ) 
		{
			m_pData = d;	
			m_pCallFuncND = selector;
			return true;
		}
		return false;
	}

	NSObject * CCCallFuncND::copyWithZone(NSZone* zone)
	{
		NSZone* pNewZone = NULL;
		CCCallFuncND* pRet = NULL;
		if(zone && zone->m_pCopyObject) //in case of being called at sub class
			pRet = (CCCallFuncND*)(zone->m_pCopyObject);
		else
		{
			pRet = new CCCallFuncND();
			zone = pNewZone = new NSZone(pRet);
		}
		CCCallFunc::copyWithZone(zone);
		pRet->initWithTarget(m_pSelectorTarget, m_pCallFuncND, m_pData);
		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}

	void CCCallFuncND::execute()
	{
		if(m_pCallFuncND)
		{
			(m_pSelectorTarget->*m_pCallFuncND)(m_pTarget, m_pData);
		}
	}
	

#if NS_BLOCKS_AVAILABLE

#pragma mark CCCallBlock

		@implementation CCCallBlock

		+(id) actionWithBlock:(void(^)())block {
			return [[[self alloc] initWithBlock:block] autorelease];
	}

	-(id) initWithBlock:(void(^)())block {
		if ((self = [super init])) {

			block_ = [block retain];
		}
		return self;
	}

	-(id) copyWithZone: (NSZone*) zone {
		CCInstantAction *copy = [[[self class] allocWithZone: zone] initWithBlock:block_];
		return copy;
	}

	-(void) startWithTarget:(id)aTarget {
		[super startWithTarget:aTarget];
		[self execute];
	}

	-(void) execute {
		block_();
	}

	-(void) dealloc {
		[block_ release];
		[super dealloc];
	}

	@end

#pragma mark CCCallBlockN

		@implementation CCCallBlockN

		+(id) actionWithBlock:(void(^)(CCNode *node))block {
			return [[[self alloc] initWithBlock:block] autorelease];
	}

	-(id) initWithBlock:(void(^)(CCNode *node))block {
		if ((self = [super init])) {

			block_ = [block retain];
		}
		return self;
	}

	-(id) copyWithZone: (NSZone*) zone {
		CCInstantAction *copy = [[[self class] allocWithZone: zone] initWithBlock:block_];
		return copy;
	}

	-(void) startWithTarget:(id)aTarget {
		[super startWithTarget:aTarget];
		[self execute];
	}

	-(void) execute {
		block_(target);
	}

	-(void) dealloc {
		[block_ release];
		[super dealloc];
	}

	@end


#endif // NS_BLOCKS_AVAILABLE

}

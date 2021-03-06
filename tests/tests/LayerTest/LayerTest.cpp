#include "LayerTest.h"
#include "../testResource.h"

enum 
{
	kTagLayer = 1,
};

static int sceneIdx = -1; 

#define MAX_LAYER	3

CCLayer* createTestLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new LayerTest1();
		case 1: return new LayerTest2();
		case 2: return new LayerTestBlend();
	}

	return NULL;
}

CCLayer* nextTestAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backTestAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartTestAction()
{
	CCLayer* pLayer = createTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 

//------------------------------------------------------------------
//
// LayerTest
//
//------------------------------------------------------------------

LayerTest::LayerTest(void)
{
}

LayerTest::~LayerTest(void)
{
}

std::string LayerTest::title()
{
	return "No title";
}

void LayerTest::onEnter()
{
	CCLayer::onEnter();

	CGSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabel* label = CCLabel::labelWithString(title().c_str(), "Arial", 32);
	addChild(label, 1);
	label->setPosition( CGPointMake(s.width/2, s.height-50) );

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(LayerTest::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(LayerTest::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(LayerTest::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CGPointZero );
	item1->setPosition( CGPointMake( s.width/2 - 100,30) );
	item2->setPosition( CGPointMake( s.width/2, 30) );
	item3->setPosition( CGPointMake( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void LayerTest::restartCallback(NSObject* pSender)
{
	CCScene* s = new LayerTestScene();
	s->addChild(restartTestAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void LayerTest::nextCallback(NSObject* pSender)
{
	CCScene* s = new LayerTestScene();
	s->addChild( nextTestAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void LayerTest::backCallback(NSObject* pSender)
{
	CCScene* s = new LayerTestScene();
	s->addChild( backTestAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

//------------------------------------------------------------------
//
// LayerTest1
//
//------------------------------------------------------------------
void LayerTest1::onEnter()
{
	LayerTest::onEnter();

	setIsTouchEnabled(true);
	
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCColorLayer* layer = CCColorLayer::layerWithColorWidthHeight( ccc4(0xFF, 0x00, 0x00, 0x80), 200, 200); 
	
	layer->setIsRelativeAnchorPoint(true);
	layer->setPosition( CGPointMake(s.width/2, s.height/2) );
	addChild(layer, 1, kTagLayer);
}

void LayerTest1::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

void LayerTest1::updateSize(CCTouch*touch)
{
	CGPoint touchLocation = touch->locationInView(touch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	
	CGSize newSize = CGSizeMake( std::abs( (int)(touchLocation.x - s.width/2)*2), abs((int)(touchLocation.y - s.height/2)*2));
	
	CCColorLayer* l = (CCColorLayer*) getChildByTag(kTagLayer);

	l->setContentSize( newSize );
}

bool LayerTest1::ccTouchBegan(CCTouch* touch, UIEvent* event)
{
	updateSize(touch);

	return true;
}

void LayerTest1::ccTouchMoved(CCTouch* touch, UIEvent* event)
{
	updateSize(touch);
}

void LayerTest1::ccTouchEnded(CCTouch* touch, UIEvent* event)
{
	updateSize(touch);
}

std::string LayerTest1::title()
{
	return "ColorLayer resize (tap & move)";
}

//------------------------------------------------------------------
//
// LayerTest2
//
//------------------------------------------------------------------
void LayerTest2::onEnter()
{
	LayerTest::onEnter();

	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCColorLayer* layer1 = CCColorLayer::layerWithColorWidthHeight( ccc4(255, 255, 0, 80), 100, 300);
	layer1->setPosition(CGPointMake(s.width/3, s.height/2));
	layer1->setIsRelativeAnchorPoint(true);
	addChild(layer1, 1);
	
	CCColorLayer* layer2 = CCColorLayer::layerWithColorWidthHeight( ccc4(0, 0, 255, 255), 100, 300);
	layer2->setPosition(CGPointMake((s.width/3)*2, s.height/2));
	layer2->setIsRelativeAnchorPoint(true);
	addChild(layer2, 1);
	
	CCIntervalAction* actionTint = CCTintBy::actionWithDuration(2, -255, -127, 0);
	CCIntervalAction* actionTintBack = actionTint->reverse();
	CCIntervalAction* seq1 = (CCIntervalAction*)CCSequence::actions( actionTint, actionTintBack, NULL);
	layer1->runAction(seq1);

	CCIntervalAction* actionFade = CCFadeOut::actionWithDuration(2.0f);
	CCIntervalAction* actionFadeBack = actionFade->reverse();
	CCIntervalAction* seq2 = (CCIntervalAction*)CCSequence::actions(actionFade, actionFadeBack, NULL);		
	layer2->runAction(seq2);
}

std::string LayerTest2::title()
{
	return "ColorLayer: fade and tint";
}

//------------------------------------------------------------------
//
// LayerTestBlend
//
//------------------------------------------------------------------

LayerTestBlend::LayerTestBlend()
{
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCColorLayer* layer1 = CCColorLayer::layerWithColor( ccc4(255, 255, 255, 80) );
	
	CCSprite* sister1 = CCSprite::spriteWithFile(s_pPathSister1);
	CCSprite* sister2 = CCSprite::spriteWithFile(s_pPathSister2);
	
	addChild(sister1);
	addChild(sister2);
	addChild(layer1, 100, kTagLayer);
	
	sister1->setPosition( CGPointMake( 160, s.height/2) );
	sister2->setPosition( CGPointMake( 320, s.height/2) );

	schedule( schedule_selector(LayerTestBlend::newBlend), 1.0f);
}

void LayerTestBlend::newBlend(ccTime dt)
{
 	CCColorLayer *layer = (CCColorLayer*)getChildByTag(kTagLayer);

    GLenum src;
    GLenum dst;

	if( layer->getBlendFunc().dst == GL_ZERO )
    {
        src = CC_BLEND_SRC;
        dst = CC_BLEND_DST;
    }
	else
    {
        src = GL_ONE_MINUS_DST_COLOR;
        dst = GL_ZERO;
    }

    ccBlendFunc bf = {src, dst};
    layer->setBlendFunc( bf );
}


std::string LayerTestBlend::title()
{
	return "ColorLayer: blend";
}

void LayerTestScene::runThisTest()
{
    CCLayer* pLayer = nextTestAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}

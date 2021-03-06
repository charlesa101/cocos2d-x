#ifndef _TILEMAP_TEST_H_
#define _TILEMAP_TEST_H_

#include "../testBasic.h"

class TileDemo : public CCLayer
{
protected:
	CCLabel* m_label;
	CCLabel* m_subtitle;

public:
	TileDemo(void);
	virtual ~TileDemo(void);

	virtual std::string title();
	virtual std::string subtitle();
	virtual void onEnter();

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);

	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch* touch, UIEvent* event);
	void ccTouchEnded(CCTouch* touch, UIEvent* event);
	void ccTouchCancelled(CCTouch* touch, UIEvent* event);
	void ccTouchMoved(CCTouch* touch, UIEvent* event);
};

class TileMapTest : public TileDemo
{
public:
	TileMapTest(void);
	virtual std::string title();
};

class TileMapEditTest : public TileDemo
{
public:
	TileMapEditTest (void);
	virtual std::string title();

	void updateMap(ccTime dt);
};

class TMXOrthoTest : public TileDemo
{
public:
	TMXOrthoTest(void);
	virtual std::string title();

	virtual void onEnter();
	virtual void onExit();
};

class TMXOrthoTest2 : public TileDemo
{
public:
	TMXOrthoTest2(void);
	virtual std::string title();
};

class TMXOrthoTest3 : public TileDemo
{
public:
	TMXOrthoTest3(void);
	virtual std::string title();
};

class TMXOrthoTest4 : public TileDemo
{
public:
	TMXOrthoTest4(void);
	void removeSprite(ccTime dt);
	virtual std::string title();
};

class TMXReadWriteTest : public TileDemo
{
	unsigned int m_gid;
	unsigned int m_gid2;
public:
	TMXReadWriteTest(void);
	virtual std::string title();

	void removeSprite(CCNode* sender);
	void updateCol(ccTime dt);
	void repaintWithGID(ccTime dt);
	void removeTiles(ccTime dt);
};

class TMXHexTest : public TileDemo
{
public:
	TMXHexTest(void);
	virtual std::string title();
};

class TMXIsoTest : public TileDemo
{
public:
	TMXIsoTest(void);
	virtual std::string title();
};

class TMXIsoTest1 : public TileDemo
{
public:
	TMXIsoTest1(void);
	virtual std::string title();
};

class TMXIsoTest2 : public TileDemo
{
public:
	TMXIsoTest2(void);
	virtual std::string title();
};

class TMXUncompressedTest : public TileDemo
{
public:
	TMXUncompressedTest(void);
	virtual std::string title();
};

class TMXTilesetTest : public TileDemo
{
public:
	TMXTilesetTest(void);
	virtual std::string title();
};



class TMXOrthoObjectsTest : public TileDemo
{
public:
	TMXOrthoObjectsTest(void);
	virtual std::string title();

	virtual void draw();
	virtual std::string subtitle();
};

class TMXIsoObjectsTest : public TileDemo
{
public:
	TMXIsoObjectsTest(void);
	virtual std::string title();

	virtual void draw();
	virtual std::string subtitle();
};

class TMXResizeTest : public TileDemo
{
public:
	TMXResizeTest(void);
	virtual std::string title();

	virtual std::string subtitle();
};

class TMXIsoZorder : public TileDemo
{
	CCSprite*	m_tamara;
public:
	TMXIsoZorder(void);
	virtual std::string title();
	virtual std::string subtitle();
	virtual void onExit(void);

	~TMXIsoZorder();
	void repositionSprite(ccTime dt);
};

class TMXOrthoZorder : public TileDemo
{
	CCSprite*	m_tamara;
public:
	TMXOrthoZorder(void);
	virtual std::string title();
	virtual std::string subtitle();

	virtual ~TMXOrthoZorder();
	void repositionSprite(ccTime dt);
};

class TMXIsoVertexZ : public TileDemo
{
	CCSprite*	m_tamara;
public:
	TMXIsoVertexZ(void);
	virtual std::string title();
	virtual std::string subtitle();

	~TMXIsoVertexZ();
	void repositionSprite(ccTime dt);
	virtual void onEnter();
	virtual void onExit();
};

class TMXOrthoVertexZ : public TileDemo
{
	CCSprite*	m_tamara;
public:
	TMXOrthoVertexZ(void);
	virtual std::string title();
	virtual std::string subtitle();

	~TMXOrthoVertexZ();
	void repositionSprite(ccTime dt);
	virtual void onEnter();
	virtual void onExit();
};

class TMXIsoMoveLayer : public TileDemo
{
public:
	TMXIsoMoveLayer(void);
	virtual std::string title();
	virtual std::string subtitle();
};

class TMXOrthoMoveLayer : public TileDemo
{
public:
	TMXOrthoMoveLayer(void);
	virtual std::string title();
	virtual std::string subtitle();
};

class TileMapTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif

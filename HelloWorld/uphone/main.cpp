// Application main file.
 
// Original file name: cocosTemplateEntry.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-09-27

// uphone headers
#include "TG3.h"
#include "helloworld_res_c.h"

// cocos2d
#include "AppDelegate.h"
#include "cocos2d.h"

// cocos2d-uphone
#include "Resource.h"

const  ResourceRegisterEntry		ResRegList_HelloWorld[]  =
{
	TG_RESOURCE_DEFINE
};

extern const  AppResourceEntry		HelloWorldResourceEntry  =
{
	(ResourceRegisterEntry*)ResRegList_HelloWorld,                    //  res  list  in  this  app
		sizeof(ResRegList_HelloWorld) /  sizeof(ResourceRegisterEntry),    //number  of  item  in  res
};


Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	// set the ResourceEntry
	cocos2d::CCFileUtils::setResourceEntry(&HelloWorldResourceEntry);
    // set the Images ResInfo (name and ResID)
	cocos2d::CCFileUtils::setResourceInfo(ResInfo, sizeof(ResInfo) / sizeof(T_ResourceInfo));

	AppDelegate app;
	app.WM_SetResourceEntry(&HelloWorldResourceEntry);
	app.Run();

	return 1;
}



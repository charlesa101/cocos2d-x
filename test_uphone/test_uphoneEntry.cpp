// Application main file.
 
// Original file name: test_uphoneEntry.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-7-26
 

 
#include  "test_uphoneEntry.h"
#include  "test_uphoneApp.h"
#include  "test_uphone_res_c.h"

const  ResourceRegisterEntry		ResRegList_test_uphone[]  =
{
	TG_RESOURCE_DEFINE
};

const  AppResourceEntry		test_uphoneResourceEntry  =
{
	(ResourceRegisterEntry*)ResRegList_test_uphone,                    //  res  list  in  this  app
		sizeof(ResRegList_test_uphone) /  sizeof(ResourceRegisterEntry),    //number  of  item  in  res
};

Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	switch(nCmd)
	{
	case 0: // �����
		{
			// UIӦ�ó������ӣ�
			Ttest_uphoneApp  *  pApp= new  Ttest_uphoneApp();
			pApp->WM_SetResourceEntry(&test_uphoneResourceEntry);
			pApp->Run();

			delete pApp;
			break;
		}
	}
	return 1;
}


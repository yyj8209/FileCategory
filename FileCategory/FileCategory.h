
// FileCategory.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileCategoryApp: 
// �йش����ʵ�֣������ FileCategory.cpp
//

class CFileCategoryApp : public CWinApp
{
public:
	CFileCategoryApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileCategoryApp theApp;

// AR_model.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CARmodelApp:
// Сведения о реализации этого класса: AR_model.cpp
//

class CARmodelApp : public CWinApp
{
public:
	CARmodelApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CARmodelApp theApp;

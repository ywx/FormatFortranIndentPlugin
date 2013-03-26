/***************************************************************
 * Name:        CMyFortranIndentConfig.h
 * Purpose:     declaration of CMyFortranIndentConfig struct
 * Author:      YWX (wxFortranIndent@163.com)
 * Created:     2013-3-26
 * Copyright:   (c) YWX <wxFortranIndent@163.com>
 * Licence:     GNU General Public License, version 3
 **************************************************************/

#ifndef _MY_WX_CMyFortranIndentConfig_H_
#define _MY_WX_CMyFortranIndentConfig_H_


enum PreprocessorType
{
    PreprocessorType_NoPreprocessor, PreprocessorType_IntelFortran, PreprocessorType_CoCo
};

struct CMyFortranIndentConfig
{
	bool isSameAsEditor;
	bool isUseTab;
	int  iTabWidth;
	bool isKeepBlankLineOnly;
	bool isTrimLineFromRight;
	int iPreprocessorType;

	CMyFortranIndentConfig()
	{
		reset();
	}

	void reset();

};


#endif // _MY_WX_CMyFortranIndentConfig_H_

/***************************************************************
 * Name:        CMyFortranIndentConfig.cpp
 * Purpose:     Struct to Configure Fortran Indent
 * Author:      YWX (wxFortranIndent@163.com)
 * Created:     2013-3-26
 * Copyright:   (c) YWX <wxFortranIndent@163.com>
 * Licence:     GNU General Public License, version 3
 **************************************************************/

#include "CMyFortranIndentConfig.h"


void CMyFortranIndentConfig::reset()
{
	isSameAsEditor = true;
	isUseTab = false;
	iTabWidth = 4;
	isKeepBlankLineOnly = false;
	isTrimLineFromRight = false;
	iPreprocessorType = PreprocessorType_NoPreprocessor; // PreprocessorType_None = 0
}

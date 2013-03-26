///////////////////////////////////////////////////////////////////////////////
// Name:        CMyWxFortranIndent.h
// Purpose:     declaration of CMyWxFortranIndent class
// Author:      YWX (wxFortranIndent@163.com)
// Created:     2012-4-23
// Copyright:   (c) YWX <wxFortranIndent@163.com>
// Licence:     GNU General Public License, version 3
///////////////////////////////////////////////////////////////////////////////

#ifndef _MY_WX_CMyWxFortranIndent_H_
#define _MY_WX_CMyWxFortranIndent_H_

#include <wx/string.h>
#include <wx/regex.h>
#include <wx/hashmap.h>

/// declaration
WX_DECLARE_STRING_HASH_MAP( wxRegEx *, MyFortranRegEx );

class CMyWxFortranIndent
{
public:

    /** Constructor. */
    CMyWxFortranIndent( )
	{
		myCreateFortranRegEx();
	}

    /** Destructor. */
	~CMyWxFortranIndent( )
	{
		myDelFortranRegEx();
	}

	void myCreateFortranRegEx();
	void myDelFortranRegEx();

	bool BuffersDiffer( const wxString &a, const wxString &b, const wxString &eolChars,const bool isDelBlank=true );
	bool getIsHasLineContinuation( const wxString & srcLine );
	bool getIsHasPreprocessor( const wxString & srcLine, int iPreprocessorType );
	void delLineContinuation( wxString & srcLine );
	void delComment( wxString & srcLine );
	void getFortranIndentLine( const wxString & src, int & indentNum, bool & isCur, bool & isCaseBegin );

protected:

	MyFortranRegEx myFortranRegEx;
};


#endif // _MY_WX_CMyWxFortranIndent_H_

/////////////////////////////////////////////////////////////////////////////
// Name:        CMyWxFortranIndent.cpp
// Purpose:     Class to Process Fortran Indent
// Author:      YWX (wxFortranIndent@163.com)
// Created:     2012-4-23
// Copyright:   (c) YWX <wxFortranIndent@163.com>
// Licence:     GNU General Public License, version 3
///////////////////////////////////////////////////////////////////////////////

#include "CMyWxFortranIndent.h"


void CMyWxFortranIndent::myDelFortranRegEx()
{
    if( myFortranRegEx.empty() )
    {
        return ;
    }
    MyFortranRegEx::iterator it = myFortranRegEx.begin();
    // iterate over all the Hash Map
    while( it != myFortranRegEx.end() )
    {
        wxRegEx * pIt = it->second;
        delete pIt;
        ++it;
    }
    myFortranRegEx.clear();
}


void CMyWxFortranIndent::myCreateFortranRegEx()
{
	int options = wxRE_DEFAULT | wxRE_ADVANCED | wxRE_ICASE ;

	myDelFortranRegEx();

	myFortranRegEx[wxT("regexMultiLines")] = new wxRegEx( wxT("(&)((\r\n)|(\r)|(\n))?$"), options );
	myFortranRegEx[wxT("regexEndProgram")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)((program)|(module)|((block)(\\s*)(data))|(subroutine)|(function))((\\s+)([a-zA-Z0-9_]+))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexProgram")] = new wxRegEx( wxT("^(\\s*)((program)|(module)|((block)(\\s*)(data)))((\\s+)([a-zA-Z0-9_]+))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexInterface")] = new wxRegEx( wxT("^(\\s*)((abstract)(\\s+))?(interface)((\\s+)(([a-zA-Z0-9_]+)|((assignment)(\\s*)\\((\\s*)(=)(\\s*)\\))|((operator)(\\s*)\\((.+)\\))))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndInterface")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(interface)((\\s+)(([a-zA-Z0-9_]+)|((assignment)(\\s*)\\((\\s*)(=)(\\s*)\\))|((operator)(\\s*)\\((.+)\\))))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexContains")] = new wxRegEx( wxT("^(\\s*)(contains)((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexSubroutine")] = new wxRegEx( wxT("^(\\s*)(((pure)|(impure))(\\s+))?(((recursive)|(elemental))(\\s+))?((module)(\\s+))?(subroutine)(\\s+)([a-zA-Z0-9_]+)((\\s*)(\\()(\\s*)(([a-zA-Z0-9_]+)((\\s*)(,)(\\s*)([a-zA-Z0-9_]+))*)?(\\s*)(\\))(\\s*))?"), options );
	myFortranRegEx[wxT("regexFunction")] = new wxRegEx( wxT("^(\\s*)(((pure)|(impure))\\s+)?(((recursive)|(elemental))\\s+)?(((integer)|(real)|(complex)|(logical)|(character)|((double)(\\s*)(precision))|((type)(\\s*)\\((\\s*)([a-zA-Z0-9_]+)((\\s*)\\((\\s*)([a-zA-Z0-9_]+)(\\s*)\\))?(\\s*)\\)))(\\((\\s*)((len)(\\s*)=(\\s*))?(\\d*)(\\s*)\\))?)?(\\s*)((module)(\\s+))?(function)(\\s+)([a-zA-Z0-9_]+)(\\s*)\\((\\s*)(([a-zA-Z0-9_]+)((\\s*)(,)(\\s*)([a-zA-Z0-9_]+))*)?(\\s*)\\)"), options );
	myFortranRegEx[wxT("regexType")] = new wxRegEx( wxT("^(\\s*)((type)(\\s*)(\\()(\\s*)([a-zA-Z0-9_]+)(\\s*)(\\)))(\\s*)"), options );
	myFortranRegEx[wxT("regexTypeDefine")] = new wxRegEx( wxT("^(\\s*)((type)((\\s*),(\\s*)((public)|(private)|(protected)))?((\\s*),(\\s*)((abstract)|((extends)(\\s*)\\((\\s*)([a-zA-Z0-9_]+)(\\s*)\\))))?((\\s*),(\\s*)((bind)(\\s*)\\((\\s*)(c)(\\s*)\\)))?((\\s*)(::)?(\\s*)([a-zA-Z0-9_]+)))(\\s*)"), options );
	myFortranRegEx[wxT("regexEndType")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(type)((\\s+)([a-zA-Z0-9_]+))?(\\s*)"), options );
	myFortranRegEx[wxT("regexEndDo")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)((do)|(forall))((\\s+)([a-zA-Z0-9_]+))?(\\s*)"), options );
	myFortranRegEx[wxT("regexDo")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?(do)((\\s+)([a-zA-Z0-9_])(.+))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexForall")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?((forall)|((do)(\\s+)(while)))(\\s*)(\\()(.+)(\\))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndSelect")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(select)((\\s+)([a-zA-Z0-9_]+))?(\\s*)"), options );
	myFortranRegEx[wxT("regexSelectCase")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?((select)(\\s*)((case)|(type)))(\\s*)(\\()(.+)(\\))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexCase")] = new wxRegEx( wxT("^(\\s*)((((case)|(((type)|(class))(\\s+)(is)))(\\s*)(\\()(.+)(\\))((\\s+)([a-zA-Z0-9_]+))?)|(((case)|(class))(\\s+)(default)((\\s+)([a-zA-Z0-9_]+))?))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexIfThen")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?((if)(\\s*)(\\()(.+)(\\))(\\s*)(then))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexElse")] = new wxRegEx( wxT("^(\\s*)(else)(\\s*)(((\\s+)([a-zA-Z0-9_]+))|((if)(\\s*)(\\()(.+)(\\))(\\s*)(then)((\\s+)([a-zA-Z0-9_]+))?))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndIf")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(if)((\\s+)([a-zA-Z0-9_]+))?(\\s*)"), options );
	myFortranRegEx[wxT("regexWhere")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?((where)(\\s*)(\\()(.+)(\\)))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexElseWhere")] = new wxRegEx( wxT("^(\\s*)(else)(\\s*)(where)(((\\s+)([a-zA-Z0-9_]+))|((\\s*)\\((.+)\\)((\\s+)([a-zA-Z0-9_]+))?))?((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndWhere")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(where)((\\s+)([a-zA-Z0-9_]+))?(\\s*)"), options );
	myFortranRegEx[wxT("regexEndOnly")] = new wxRegEx( wxT("^(\\s*)(end)((\\s*)!(.*))?(\\s*)$"), options );

	myFortranRegEx[wxT("regexAssociate")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?(associate)(\\s*)\\((.+)\\)((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndAssociate")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(associate)((\\s+)([a-zA-Z0-9_]+))?((\\s*)!(.*))?(\\s*)$"), options );

	myFortranRegEx[wxT("regexCritical")] = new wxRegEx( wxT("^(\\s*)(([a-zA-Z0-9_]+)(\\s*)(:)(\\s*))?((block)|(critical)|((submodule)(\\s*)\\((.+)\\)(\\s*)([a-zA-Z0-9_]+)))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndCritical")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)((block)|(critical)|(submodule))((\\s+)([a-zA-Z0-9_]+))?((\\s*)!(.*))?(\\s*)$"), options );

	myFortranRegEx[wxT("regexEnum")] = new wxRegEx( wxT("^(\\s*)(enum)((\\s*),(\\s*)((bind)(\\s*)\\((\\s*)(c)(\\s*)\\)))((\\s*)!(.*))?(\\s*)$"), options );
	myFortranRegEx[wxT("regexEndEnum")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(enum)((\\s*)!(.*))?(\\s*)$"), options );

	myFortranRegEx[wxT("regexComment")] = new wxRegEx( wxT("(!(.*))((\r\n)|(\r)|(\n))?$"), options | wxRE_NEWLINE );

	myFortranRegEx[wxT("regexBlankLine")] = new wxRegEx( wxT("([ \t]+)((\r\n)|(\r)|(\n))"), options | wxRE_NEWLINE );

}


void CMyWxFortranIndent::getFortranIndentLine( const wxString & src1, int & indentNum, bool & isCur, bool & isCaseBegin )
{
    // module program subroutine function forall
    // Add a shiftwidth to statements following module, program, subroutine,
    // function and forall statements
    //Manager::Get()->GetLogManager()->Log( src1 );

    wxString srct = src1;
    wxString src = srct.Trim(true); // trim from right

    // Program, Module, Interface, Bblock Data, Subroutine, Function
    if ( myFortranRegEx[wxT("regexEndProgram")]->Matches( src ) ||
            myFortranRegEx[wxT("regexEndInterface")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

	if ( myFortranRegEx[wxT("regexInterface")]->Matches( src ) ||
            myFortranRegEx[wxT("regexSubroutine")]->Matches( src ) ||
            myFortranRegEx[wxT("regexFunction")]->Matches( src ) ||
            myFortranRegEx[wxT("regexProgram")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }
    // Contains
    if ( myFortranRegEx[wxT("regexContains")]->Matches( src ) )
    {
        isCur = false;
        return ;
    }

    // do while # end do
    // forall() # end forall
    // Indent do loops only if they are all guaranteed to be of do/end do type
    if ( myFortranRegEx[wxT("regexEndDo")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

    if ( myFortranRegEx[wxT("regexDo")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }

    if ( myFortranRegEx[wxT("regexForall")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }

    // if select
    // Add a shiftwidth to statements following if, else, case,
    // where, elsewhere, type and interface statements

    // select case # case | case dafault # end select
    if ( myFortranRegEx[wxT("regexEndSelect")]->Matches( src ) )
    {
        indentNum -= 2;
        isCur = true;
        return ;
    }

    if ( myFortranRegEx[wxT("regexSelectCase")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        isCaseBegin = true;
        return ;
    }

    if ( myFortranRegEx[wxT("regexCase")]->Matches( src ) )
    {
        if( true == isCaseBegin )
        {
            indentNum += 1;
            isCaseBegin = false;
        }
        isCur = false;
        return ;
    }

    // if ## if then # else # end if
    if ( myFortranRegEx[wxT("regexIfThen")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }
    if ( myFortranRegEx[wxT("regexElse")]->Matches( src ) )
    {
        isCur = false;
        return ;
    }
    if ( myFortranRegEx[wxT("regexEndIf")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

    // where elsewhere
    if ( myFortranRegEx[wxT("regexWhere")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }
    if ( myFortranRegEx[wxT("regexElseWhere")]->Matches( src ) )
    {
        isCur = false;
        return ;
    }
    if ( myFortranRegEx[wxT("regexEndWhere")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

    // type
    if ( myFortranRegEx[wxT("regexEndType")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

    if ( ( false == myFortranRegEx[wxT("regexType")]->Matches( src ) ) &&
            ( myFortranRegEx[wxT("regexTypeDefine")]->Matches( src ) ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }

    // associate
    if ( myFortranRegEx[wxT("regexEndAssociate")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

	if ( myFortranRegEx[wxT("regexAssociate")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }

	// block critical submodule
    if ( myFortranRegEx[wxT("regexEndCritical")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

	if ( myFortranRegEx[wxT("regexCritical")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }

	// enum
    if ( myFortranRegEx[wxT("regexEndEnum")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

	if ( myFortranRegEx[wxT("regexEnum")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        return ;
    }

    // end only
    if ( myFortranRegEx[wxT("regexEndOnly")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
        return ;
    }

}

// Special code to compare strings which doesn't care
// about spaces leading up to the EOL.
bool CMyWxFortranIndent::BuffersDiffer( const wxString &a, const wxString &b, const wxString &eolChars, const bool isDelBlank )
{
    wxString ta = a;
    wxString tb = b;

    if( isDelBlank )
    {
        ta.Trim(); //ta.Trim(true) from right
        tb.Trim();

        wxASSERT( 0 != myFortranRegEx[wxT("regexBlankLine") ] );
        {
            myFortranRegEx[wxT("regexBlankLine")]->ReplaceAll( &ta, eolChars );
            myFortranRegEx[wxT("regexBlankLine")]->ReplaceAll( &tb, eolChars );
        }
    }

    bool changed = false;
    changed = !( ta == tb );

    return changed;
}

bool CMyWxFortranIndent::getIsHasLineContinuation( const wxString & srcLine )
{
    wxASSERT( myFortranRegEx[wxT("regexMultiLines")] );
    return myFortranRegEx[wxT("regexMultiLines")]->Matches( srcLine );
}


void CMyWxFortranIndent::delLineContinuation( wxString & srcLine )
{
    wxASSERT( myFortranRegEx[wxT("regexMultiLines")] );
    myFortranRegEx[wxT("regexMultiLines")]->ReplaceAll( &srcLine, wxT("") );
}


void CMyWxFortranIndent::delComment( wxString & srcLine )
{
    wxASSERT( myFortranRegEx[wxT("regexComment")] );
    myFortranRegEx[wxT("regexComment")]->ReplaceAll( &srcLine, wxT("") );
}

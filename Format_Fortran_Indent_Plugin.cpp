/***************************************************************
 * Name:      Format_Fortran_Indent_Plugin.cpp
 * Purpose:   Code::Bloacks Plugin to Format Source Code Indent in Fortran 95, Fortran 90 (free source form)
 * Author:    YWX (wxFortranIndent@163.com) or wxFortranIndent (wxFortranIndent@gmail.com)
 * Created:   2011-12-22
 * Copyright: (c) 2011 YWX <wxFortranIndent@163.com>
 * License:   GNU General Public License, version 3
 **************************************************************/

#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "Format_Fortran_Indent_Plugin.h"

#include <wx/progdlg.h>
#include "cbstyledtextctrl.h"

//#include <wx/regex.h>


namespace
{
    const int idCodeFortranIndentFile = wxNewId();
    const int idCodeFortranIndentActiveFile = wxNewId();
    const int idCodeFortranIndentProject = wxNewId();
}

BEGIN_EVENT_TABLE( Format_Fortran_Indent_Plugin, cbPlugin )
    EVT_MENU( idCodeFortranIndentActiveFile, Format_Fortran_Indent_Plugin::OnFormatActiveFile )
    EVT_MENU( idCodeFortranIndentProject, Format_Fortran_Indent_Plugin::OnFormatProject )
END_EVENT_TABLE()

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<Format_Fortran_Indent_Plugin> reg(_T("Format_Fortran_Indent_Plugin"));
}

// constructor
Format_Fortran_Indent_Plugin::Format_Fortran_Indent_Plugin()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("Format_Fortran_Indent_Plugin.zip")))
    {
        NotifyMissingFile(_T("Format_Fortran_Indent_Plugin.zip"));
    }

    ///pre
	myCreateFortranRegEx( );
}

// destructor
Format_Fortran_Indent_Plugin::~Format_Fortran_Indent_Plugin()
{
}

void Format_Fortran_Indent_Plugin::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

void Format_Fortran_Indent_Plugin::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

int Format_Fortran_Indent_Plugin::Configure()
{
    //create and display the configuration dialog for your plugin
    cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Your dialog title"));
    cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
    if (panel)
    {
        dlg.AttachConfigurationPanel(panel);
        PlaceWindow(&dlg);
        return dlg.ShowModal() == wxID_OK ? 0 : -1;
    }
    return -1;
}


void Format_Fortran_Indent_Plugin::BuildModuleMenu( const ModuleType type, wxMenu* menu, const FileTreeData* data )
{
    if ( !menu || !IsAttached() )
        return;

    switch ( type )
    {
        case mtEditorManager:
            menu->AppendSeparator();
            menu->Append( idCodeFortranIndentActiveFile, _( "Format Fortran Indent" ), _( "Format the selected Fortran source code Indent (selected line) in the current file" ) );
            break;

        case mtProjectManager:
            if ( data ) switch ( data->GetKind() )
                {
                    case FileTreeData::ftdkProject:
                        menu->AppendSeparator();
                        menu->Append( idCodeFortranIndentProject, _( "Format Fortran Indent this project" ), _( "Format the Fortran source code Indent in this project" ) );
                        break;

                    case FileTreeData::ftdkFile:
                        menu->AppendSeparator();
                        menu->Append( idCodeFortranIndentProject, _( "Format Fortran Indent this file" ), _( "Format the Fortran source code Indent in this file" ) );
                        break;

                    default:
                        // Do nothing.
                        break;
                }
            break;

        default:
            break;
    }
}


///
static bool isFortranFilename( const wxFileName fname )
{
    wxString fExt;
    fExt = fname.GetExt().Lower();
    if( wxT("f90") == fExt || wxT("f95") == fExt || wxT("f03") == fExt )
        return true;
    if( wxT("for") == fExt || wxT("f") == fExt || wxT("fi") == fExt || wxT("fd") == fExt )
        return true;
    return false;
}

static bool isFortranFilename( const wxString & filename )
{
    bool isFortran = false;
    wxFileName fname;
    fname.Assign(filename);
    isFortran = isFortranFilename( fname );
    return isFortran;
}


void Format_Fortran_Indent_Plugin::OnFormatProject( wxCommandEvent& /*event*/ )
{
    ProjectManager* manager = Manager::Get()->GetProjectManager();
    wxTreeCtrl *tree = manager->GetTree();

    if ( !tree )
        return;

    wxTreeItemId treeItem =  tree->GetSelection();

    if ( !treeItem.IsOk() )
        return;

    const FileTreeData *data = static_cast<FileTreeData*>( tree->GetItemData( treeItem ) );

    if ( !data )
        return;

    switch ( data->GetKind() )
    {
        case FileTreeData::ftdkProject:
            {
                cbProject* prj = data->GetProject();
                wxProgressDialog progressDlg(_("Please wait"), _("Formatting..."), prj->GetFilesCount(), 0, wxPD_CAN_ABORT|wxPD_AUTO_HIDE|wxPD_SMOOTH );
                progressDlg.Show();
                for ( int i = 0; i < prj->GetFilesCount(); ++i )
                {
                    ProjectFile* pf = prj->GetFile( i );
                    wxString filename = pf->file.GetFullPath();

                    FileType fileType = FileTypeOf( filename );
                    if ( fileType == ftSource || fileType == ftHeader )
                    {
                        if( isFortranFilename( pf->file ) )
                        {
                            FormatFile( filename );
                            if ( false == progressDlg.Update( i, wxString(_("Formatting ")) + pf->relativeFilename ) )
                                break;
                        }
                    }
                }
            }
            break;

        case FileTreeData::ftdkFile:
            {
                ProjectFile* f = data->GetProject()->GetFile( data->GetFileIndex() );
                if ( f )
                    if( isFortranFilename( f->file ) )
                        FormatFile( f->file.GetFullPath() );
            }
            break;

        default:
            break;
    }
}

void Format_Fortran_Indent_Plugin::OnFormatActiveFile( wxCommandEvent& /*event*/ )
{
        Execute();
}

int Format_Fortran_Indent_Plugin::Execute()
{
    // do your magic ;)
    //NotImplemented(_T("Format_Fortran_Indent_Plugin::Execute()"));
    if( !IsAttached() )
        return -1;

    cbEditor *ed = Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor();

    if (!ed)
        return 0;

    if( ! isFortranFilename( ed->GetFilename() ) )
	{
        if( cbMessageBox( wxT("Are you sure \n") + ed->GetFilename() +
            wxT("\n is a Fortran Source File?\nContinue to Format the Indent?"), _("Error Message"),
            wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT ) == wxID_NO )
            return 0;
	}

    FormatEditor( ed );

    Manager::Get()->GetLogManager()->Log( _("Format Fortran Indent Plugin!") );
    return 0;
    //return -1;
}

void Format_Fortran_Indent_Plugin::FormatFile( const wxString &filename )
{
    cbEditor* ed = Manager::Get()->GetEditorManager()->IsBuiltinOpen( filename );

    if ( ed ) // File is already open
        FormatEditor( ed );
    else
    {
        // File is not open.  We must open it.
        ed = Manager::Get()->GetEditorManager()->Open( filename );

        if ( ed )
        {
            bool changed = FormatEditor( ed );

            if ( !changed ) // We opened a file and it didn't change.  Close it.
                Manager::Get()->GetEditorManager()->Close( filename );
        }
    }
}



void Format_Fortran_Indent_Plugin::myCreateFortranRegEx( )
{
	int options = wxRE_DEFAULT | wxRE_ADVANCED | wxRE_ICASE ;

	//pFortranRegEx = ( MyFortranRegEx * ) NULL;
	//pFortranRegEx = new MyFortranRegEx;
	myFortranRegEx.clear();
	myFortranRegEx[wxT("regexEndProgram")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)((program)|(module)|(interface)|((block)(\\s*)(data))|(subroutine)|(function))((\\s+)([[:alnum:]_]+))?((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexProgram")] = new wxRegEx( wxT("^(\\s*)((program)|(module)|(interface))((\\s+)([[:alnum:]_]+))?((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexBlock")] = new wxRegEx( wxT("^(\\s*)(((block)(\\s*)(data)))(\\s*)"), options );
	myFortranRegEx[wxT("regexSubroutine")] = new wxRegEx( wxT("^(\\s*)(((pure)(\\s+))?((recursive)(\\s+))?((elemental)(\\s+))?(subroutine))((\\s+)([[:alnum:]_]+)(\\s*)(\\()(\\s*)(.*)(\\s*)(\\)))(\\s*)"), options );
	myFortranRegEx[wxT("regexFunction")] = new wxRegEx( wxT("^(\\s*)((pure)(\\s+))?(((recursive)(\\s+))?((elemental)(\\s+))?(((((integer)|(real)|(complex)|(logical)|(character))((\\()(\\s*)(\\d*)(\\s*)(\\)))?)|(type))(\\s*))?(function))((\\s+)([[:alnum:]_]+)(\\s*)(\\()(\\s*)(.*)(\\s*)(\\)))(\\s*)"), options );
	myFortranRegEx[wxT("regexType")] = new wxRegEx( wxT("^(\\s*)((type)(\\s*)(\\())(\\s*)"), options );
	myFortranRegEx[wxT("regexTypeDefine")] = new wxRegEx( wxT("^(\\s*)(((type)(\\s*)(,(\\s*)((public)|(privat)e|(protected))?)))(\\s*)"), options );
	myFortranRegEx[wxT("regexEndType")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(type)(\\s*)"), options );
	myFortranRegEx[wxT("regexEndDo")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(((do)((\\s+)([[:alnum:]_]+))?)|(forall))(\\s*)"), options );
	myFortranRegEx[wxT("regexDo")] = new wxRegEx( wxT("^(\\s*)(([[:alnum:]_]+(\\s*)(:)(\\s*)))?(do)((\\s+)((.*)+))?((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexForall")] = new wxRegEx( wxT("^(\\s*)(forall)(\\s*)(\\()(\\s*)(.*)(\\s*)(\\))((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexEndSelect")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(select)(\\s*)"), options );
	myFortranRegEx[wxT("regexSelectCase")] = new wxRegEx( wxT("^(\\s*)((select)(\\s+)(case))(\\s*)(\\()(\\s*)(.*)(\\s*)(\\))((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexCase")] = new wxRegEx( wxT("^(\\s*)(((case)(\\s*)(\\()(\\s*)(.*)(\\s*)(\\)))|((case)(\\s+)(default)))((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexIfThen")] = new wxRegEx( wxT("^(\\s*)((if)(\\s*)(\\()(\\s*)(.*)(\\s*)(\\))(\\s*)(then))(\\s*)"), options );
	myFortranRegEx[wxT("regexElse")] = new wxRegEx( wxT("^(\\s*)(else)(\\s*)((if)(\\s*)(\\()(\\s*)(.*)(\\s*)(\\))(\\s*)(then))?((\\s*)!(.*))?$"), options );
	myFortranRegEx[wxT("regexEndIf")] = new wxRegEx( wxT("^(\\s*)(end)(\\s*)(if)(\\s*)"), options );
	myFortranRegEx[wxT("regexEndOnly")] = new wxRegEx( wxT("^(\\s*)(end)((\\s*)!(.*))?$"), options );

}


void Format_Fortran_Indent_Plugin::getFortranIndentLine( MyFortranRegEx pFortranRegEx, const wxString & src1, int & indentNum, bool & isCur, bool & isCaseBegin )
{
    // module program subroutine function forall
    // Add a shiftwidth to statements following module, program, subroutine,
    // function and forall statements
    wxString srct = src1;
    wxString src = srct.Trim(true); // trim from right

    if ( pFortranRegEx[wxT("regexEndProgram")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
		//msg = wxT("Match (end program)    ");
        return ;
    }

    if ( pFortranRegEx[wxT("regexProgram")]->Matches( src ) ||
            pFortranRegEx[wxT("regexBlock")]->Matches( src ) ||
            pFortranRegEx[wxT("regexSubroutine")]->Matches( src ) ||
            pFortranRegEx[wxT("regexFunction")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
		//msg = wxT("Match (program )    ");
        return ;
    }

    // type
    if ( pFortranRegEx[wxT("regexEndType")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
		//msg = wxT("Match (end type)    ");
        return ;
    }

    if ( ( ! pFortranRegEx[wxT("regexType")]->Matches( src ) ) &&
            ( pFortranRegEx[wxT("regexTypeDefine")]->Matches( src ) ) )
    {
        indentNum += 1;
        isCur = false;
		//msg = wxT("Match (type)    ");
        return ;
    }

    // do while # end do
    // forall() # end forall
    // Indent do loops only if they are all guaranteed to be of do/end do type
    if ( pFortranRegEx[wxT("regexEndDo")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
		//msg = wxT("Match (end do)    ");
        return ;
    }

    if ( pFortranRegEx[wxT("regexDo")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
		//msg = wxT("Match (do)    ");
        return ;
    }

    if ( pFortranRegEx[wxT("regexForall")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
		//msg = wxT("Match (forall)    ");
        return ;
    }

    // if select
    // Add a shiftwidth to statements following if, else, case,
    // where, elsewhere, type and interface statements

    // select case # case | case dafault # end select
    if ( pFortranRegEx[wxT("regexEndSelect")]->Matches( src ) )
    {
        indentNum -= 2;
        isCur = true;
		//msg = wxT("Match (end select)    ");
        return ;
    }

    if ( pFortranRegEx[wxT("regexSelectCase")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
        isCaseBegin = true;
		//msg = wxT("Match (select case)    ");
        return ;
    }

    if ( pFortranRegEx[wxT("regexCase")]->Matches( src ) )
    {
        if( true == isCaseBegin )
        {
            indentNum += 1;
            isCaseBegin = false;
        }
        isCur = false;
		//msg = wxT("Match (case)    ");
        return ;
    }

    // if ## if then # else # end if
    if ( pFortranRegEx[wxT("regexIfThen")]->Matches( src ) )
    {
        indentNum += 1;
        isCur = false;
		//msg = wxT("Match (if then)    ");
        return ;
    }
    if ( pFortranRegEx[wxT("regexElse")]->Matches( src ) )
    {
        isCur = false;
		//msg = wxT("Match (else)    ");
        return ;
    }
    if ( pFortranRegEx[wxT("regexEndIf")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
		//msg = wxT("Match (end if)    ");
        return ;
    }

    if ( pFortranRegEx[wxT("regexEndOnly")]->Matches( src ) )
    {
        indentNum -= 1;
        isCur = true;
		//msg = wxT("Match (end only)    ");
        return ;
    }

    // where elsewhere
}

// Special code to compare strings which doesn't care
// about spaces leading up to the EOL.
/*
static bool BuffersDiffer( const wxString &a, const wxString &b )
{
    const wxChar *aCurrent = a.c_str();
    const wxChar *bCurrent = b.c_str();
    const wxChar * const aEnd = aCurrent + a.Len();
    const wxChar * const bEnd = bCurrent + b.Len();

    while ( aCurrent != aEnd && bCurrent != bEnd )
    {
        if ( *aCurrent != *bCurrent )
        {
            // Check for varying space at EOL
            while ( *aCurrent == ' ' || *aCurrent == '\t' )
            {
                if ( ++aCurrent == aEnd )
                    break;
            }
            while ( *bCurrent == ' ' || *bCurrent == '\t' )
            {
                if ( ++bCurrent == bEnd )
                    break;
            }

            // Make sure it was at EOL
            if ( ( *aCurrent != '\r' && *aCurrent != '\n' ) || ( *bCurrent != '\r' && *bCurrent != '\n' ) )
                return true;
        }

        ++aCurrent;
        ++bCurrent;
    }

    while ( aCurrent != aEnd )
    {
        if ( *aCurrent != ' ' && *aCurrent != '\t' )
            return true;
        ++aCurrent;
    }

    while ( bCurrent != bEnd )
    {
        if ( *bCurrent != ' ' && *bCurrent != '\t' )
            return true;
        ++bCurrent;
    }

    return false;
}
*/
static bool BuffersDiffer( const wxString &a, const wxString &b, const wxString &eolChars )
//static bool BuffersDiffer( const wxString &a, const wxString &b )
{
    wxString ta = a;
    wxString tb = b;

    ta.Trim(); //ta.Trim(true) from right
    tb.Trim();

    wxRegEx re;
    int options = wxRE_DEFAULT | wxRE_ADVANCED | wxRE_NEWLINE;
    wxString wx_pattern;
    //wx_pattern = wxT("([ \t]+)(") + eolChars + wxT(")");
    wx_pattern = wxT("([ \t]+)((\r\n)|(\r)|(\n))");

    if ( re.Compile( wx_pattern, options ) )
    {
        re.ReplaceAll( &ta, eolChars );
        //re.ReplaceAll( &ta, wxT("\n") );
        re.ReplaceAll( &tb, eolChars );
        //re.ReplaceAll( &tb, wxT("\n") );
    }

    bool changed = false;
    changed = !( ta == tb );

    return changed;
}

bool Format_Fortran_Indent_Plugin::FormatEditor( cbEditor *ed )
{
    cbStyledTextCtrl* control = ed->GetControl();
    if (control->GetReadOnly())
    {
        cbMessageBox(_("The file is read-only!"), _("Error"), wxICON_ERROR);
        return false;
    }

    ed->UnfoldAll();

    bool onlySelected = false;
    wxString edText;
    wxString selText;
    int leftBracesNumber = 0;
    const int pos = control->GetCurrentPos();
    int start = control->GetSelectionStart();
    int end = control->GetSelectionEnd();
    int indexLineStart = 0, indexLineEnd = 0;

    wxString fromWord;
    if (start != end)
    {
        onlySelected = true;
        start = control->GetLineIndentPosition(control->LineFromPosition(start));
        control->GotoPos(start);
        control->Home();
        indexLineStart = control->GetCurrentLine();
        start = control->GetCurrentPos();
        control->SetSelectionStart(start);
        end = control->GetLineEndPosition(control->LineFromPosition(end));
        control->GotoPos(end);
        indexLineEnd = control->GetCurrentLine();
        control->GotoPos(start);
        control->SetSelectionEnd(end);
        selText = control->GetTextRange(start, end);
    }
    else
        edText = control->GetText();

    wxString formattedText;

    // load settings
    //FormatterSettings settings;
    //settings.ApplyTo(formatter);

    wxString eolChars;

    switch (control->GetEOLMode())
    {
        case wxSCI_EOL_CRLF:
            eolChars = _T("\r\n");
            break;

        case wxSCI_EOL_CR:
            eolChars = _T("\r");
            break;

        case wxSCI_EOL_LF:
            eolChars = _T("\n");
            break;
    }

    //if (edText.size() && edText.Last() != _T('\r') && edText.Last() != _T('\n') && !onlySelected)
    //    edText += eolChars;

    bool isRemoveSelEOL = false;
    int nLines = control->GetLineCount();
    //cbMessageBox(wxT("This is my Plugin test Message Dialog\n")+ed->GetFilename()+
    //            wxString::Format(wxT(" : has line = %d"), nLines ), _("File Info"), wxICON_INFORMATION );
    int indentNum = 0;
    wxString firstLineIndentStr;
    if (!onlySelected)
    {
        indexLineStart = 0;
        indexLineEnd = nLines;
    }
    else
    {
        ++indexLineEnd;
        if( indexLineEnd < nLines )
            isRemoveSelEOL = true;
        int indentW = ed->GetLineIndentInSpaces(indexLineStart);
        int tabW = control->GetTabWidth();
        indentNum = indentW / tabW;
        if( (indentW % tabW) )
        {
            ++indentNum;
        }
        firstLineIndentStr = ed->GetLineIndentString(indexLineStart);
    }
    bool isCur = true;
    bool isCaseBegin = false;
    wxString tmpLine;
    //int tmpn = nLines - 1;
    int tmpn = indexLineEnd - 1;

    wxString indentStr;
    if( control->GetUseTabs() )
        indentStr = wxT("\t");
    else
        indentStr = wxString(_T(' '), control->GetTabWidth() );

    bool isOnlyBlankLine = false;
    bool isTrimLineFromRight = false;

    int lineCounter = 0;
    std::vector<int> new_bookmark;
    std::vector<int> ed_breakpoints;


    wxSetCursor(*wxHOURGLASS_CURSOR);

    ///formattedText = edText;
    //for( int i = 0; i < nLines; ++i )
    for( int i = indexLineStart; i < indexLineEnd; ++i )
    {
		if (ed->HasBookmark(i))
            new_bookmark.push_back(i);
		if (ed->HasBreakpoint(i))
            ed_breakpoints.push_back(i);

        isCur = true;
        tmpLine = control->GetLine( i ).Trim(false);

        if( 0 == tmpLine.length() && i < tmpn )
        {
            if( isOnlyBlankLine )
            {
                formattedText += eolChars;
                continue;
            }
            else
                tmpLine += eolChars;
        }
        else
        {
            if( isTrimLineFromRight )
            {
                tmpLine.Trim();
                tmpLine += eolChars;
            }
            getFortranIndentLine( myFortranRegEx, tmpLine, indentNum, isCur, isCaseBegin );
        }

        int tmpN = indentNum;
        if( 0 == isCur )
        {
            tmpN = tmpN - 1;
        }
        for( int j = 0; j < tmpN; ++j )
        {
            formattedText += indentStr;
        }
        formattedText += tmpLine;
        //if( i < tmpn )
        //    formattedText += eolChars; //wxT("\n");
    }

    if( onlySelected )
    {
        if( isRemoveSelEOL )
        {
            //for( int i = 0; i < eolChars.Length(); ++i )
            //    formattedText.RemoveLast();
            formattedText.Trim();
        }
        formattedText.Trim(false);
        formattedText = firstLineIndentStr + formattedText;
    }

    bool changed = BuffersDiffer( formattedText, !onlySelected ? edText : selText, eolChars );
    //bool changed = BuffersDiffer( formattedText, !onlySelected ? edText : selText );

    if ( changed )
    {
        control->BeginUndoAction();
        if (!onlySelected)
        {
            control->SetText(formattedText);

            for (std::vector<int>::const_iterator i = new_bookmark.begin(); i != new_bookmark.end(); ++i)
                ed->ToggleBookmark(*i);

            for (std::vector<int>::const_iterator i = ed_breakpoints.begin(); i != ed_breakpoints.end(); ++i)
                ed->ToggleBreakpoint(*i);
        }
        else
            control->ReplaceSelection(formattedText);

        control->EndUndoAction();
        control->GotoPos(pos);
        ed->SetModified(true);
    }

    wxSetCursor(wxNullCursor);

    return changed;
}


/***************************************************************
 * Name:      Format_Fortran_Indent_Plugin.cpp
 * Purpose:   Code::Blocks Plugin to Format Source Code Indent
 * in Fortran 95, Fortran 90 Source Code (free source form)
 * Author:    YWX (wxFortranIndent@163.com)
 * Created:   2011-12-22
 * Copyright: (c) YWX <wxFortranIndent@163.com>
 * License:   GNU General Public License, version 3
 **************************************************************/

#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "Format_Fortran_Indent_Plugin.h"
#include "CFortranIndentConfigDlg.h"

#include <wx/progdlg.h>
#include "cbstyledtextctrl.h"

#include <editormanager.h>
#include <projectmanager.h>
#include <logmanager.h>
#include <cbproject.h>
#include <cbeditor.h>

#include <wx/dynarray.h>

WX_DEFINE_ARRAY_INT(int, intArray);


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
    //cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Your dialog title"));
    //cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
    //if (panel)
    //{
    //    dlg.AttachConfigurationPanel(panel);
    //    PlaceWindow(&dlg);
    //    return dlg.ShowModal() == wxID_OK ? 0 : -1;
    //}
    //return -1;
    return 0;
}

cbConfigurationPanel* Format_Fortran_Indent_Plugin::GetConfigurationPanel(wxWindow* parent)
{
    CFortranIndentConfigDlg* dlg = new CFortranIndentConfigDlg(parent);
    // deleted by the caller

    return dlg;
}

void Format_Fortran_Indent_Plugin::BuildMenu(wxMenuBar* menuBar)
{
    //The application is offering its menubar for your plugin,
    //to add any menu items you want...
    if (!IsAttached())
        return;
    //Append any items you need in the menu...
    /// Append to Menu Fortran
    int pos = menuBar->FindMenu(_("&Fortran"));
    if( pos != wxNOT_FOUND )
    {
        wxMenu* m_FortranMenu = menuBar->GetMenu(pos);
        m_FortranMenu->Append(idCodeFortranIndentActiveFile, _("Format Fortran Indent"));
    }
    else
    {
        //Manager::Get()->GetLogManager()->Log( _("Could not find Fortran Menu!") );
        /// Append to Menu Tools
        pos = menuBar->FindMenu(_("&Tools"));
        if( pos != wxNOT_FOUND )
        {
            /// Create Fortran Menu
            wxMenu* m_FortranMenu = new wxMenu();  // pointer to the Fortran menu
            menuBar->Insert(pos, m_FortranMenu, _("&Fortran"));
            /// Append to Menu Fortran
            m_FortranMenu->Append(idCodeFortranIndentActiveFile, _("Format Fortran Indent"));
        }
        else
        {
            Manager::Get()->GetLogManager()->Log( _("Could not find Tools Menu!") );
        }
    }

    /// Append to Menu Plugins
    pos = menuBar->FindMenu(_("P&lugins"));
    if( pos != wxNOT_FOUND )
    {
        wxMenu* m_PluginsMenu = menuBar->GetMenu(pos);
        m_PluginsMenu->Prepend(idCodeFortranIndentActiveFile, _("Format Fortran Indent"));
    }
    else
    {
        Manager::Get()->GetLogManager()->Log( _("Could not find Plugins Menu!") );
    }
    //NOTE: Be careful in here... The application's menubar is at your disposal.
    //NotImplemented(_T("Format_Fortran_Indent_Plugin::BuildMenu()"));
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
                        menu->AppendSeparator();
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


bool Format_Fortran_Indent_Plugin::BuildToolBar(wxToolBar* toolBar)
{
    //The application is offering its toolbar for your plugin,
    //to add any toolbar items you want...
    //Append any items you need on the toolbar...
    NotImplemented(_T("Format_Fortran_Indent_Plugin::BuildToolBar()"));

    // return true if you add toolbar items
    return false;
}


///
bool Format_Fortran_Indent_Plugin::isFortranFilename( const wxFileName fname )
{
    wxString fExt;
    fExt = fname.GetExt().Lower();
    if( wxT("f90") == fExt || wxT("f95") == fExt || wxT("f03") == fExt )
        return true;
    if( wxT("for") == fExt || wxT("f") == fExt || wxT("fi") == fExt || wxT("fd") == fExt )
        return true;
    return false;
}

bool Format_Fortran_Indent_Plugin::isFortranFilename( const wxString & filename )
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

    const int pos = control->GetCurrentPos();
    int start = control->GetSelectionStart();
    int end = control->GetSelectionEnd();
    int indexLineStart = 0, indexLineEnd = 0;

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
    CMyFortranIndentConfig myFortranIndentConfig;

	ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("fortran_indent"));
	wxASSERT( 0 != cfg );

	if( cfg->Read( _T("is_SameAsEditor"), & myFortranIndentConfig.isSameAsEditor ) )
	{
		cfg->Read( _T("is_UseTab"), & myFortranIndentConfig.isUseTab );
		cfg->Read( _T("i_TabWidth"), & myFortranIndentConfig.iTabWidth );
		cfg->Read( _T("is_KeepBlankLineOnly"), & myFortranIndentConfig.isKeepBlankLineOnly );
		cfg->Read( _T("is_TrimLineFromRight"), & myFortranIndentConfig.isTrimLineFromRight );
	}

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

    bool isRemoveSelEOL = false;
    int nLines = control->GetLineCount();
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
    IsMultiLines isMultiLines;
	isMultiLines.reset();
    wxString tmpLine;
    wxString tmpMultiLines;
    const int tmpn = indexLineEnd - 1;

    wxString indentStr;
    if( myFortranIndentConfig.isSameAsEditor )
    {
        if( control->GetUseTabs() )
            indentStr = wxT("\t");
        else
            indentStr = wxString(wxT(' '), control->GetTabWidth() );
    }
    else
    {
        if( myFortranIndentConfig.isUseTab )
            indentStr = wxT("\t");
        else
            indentStr = wxString(wxT(' '), myFortranIndentConfig.iTabWidth );
    }

    bool isOnlyBlankLine = myFortranIndentConfig.isKeepBlankLineOnly;
    bool isTrimLineFromRight = myFortranIndentConfig.isTrimLineFromRight;

    int lineCounter = 0;
    /// WX_DEFINE_ARRAY_INT(int, intArray);
    intArray new_bookmark_array;
    intArray ed_breakpoints_array;


    wxSetCursor(*wxHOURGLASS_CURSOR);

    ///formattedText
    for( int i = indexLineStart; i < indexLineEnd; ++i )
    {
        if (ed->HasBookmark(i))
        {
            new_bookmark_array.Add( i );
        }
        if (ed->HasBreakpoint(i))
        {
            ed_breakpoints_array.Add( i );
        }

        isCur = true;
        tmpLine = control->GetLine( i ).Trim(false); // trim from left


        if( myWxFortranIndent.getIsHasLineContinuation( tmpLine ) )
        {
            wxString tempLine;
            tempLine = tmpLine; // trim from left

            if( false ==  isMultiLines.isHaveMultiLines )
            {
                isMultiLines.isHaveMultiLines = true;
                isMultiLines.iFirstLineNo = i;
                tmpMultiLines.Empty();
            }

            myWxFortranIndent.delLineContinuation( tempLine );

            if( tempLine.Len() > 0 )
            {
                if( wxT('&') == tempLine[0] )
                {
                    tempLine = tempLine.Mid( 1 );
                }
            }

            myWxFortranIndent.delComment( tempLine );

            tmpMultiLines += tempLine;

            continue ;
        }

        if( true ==  isMultiLines.isHaveMultiLines )
        {
            isMultiLines.iEndLineNo = i;

            wxString tempLine;
            tempLine = tmpLine; // trim from left

            if( tempLine.Len() > 0 )
            {
                if( wxT('&') == tempLine[0] )
                {
                    tempLine = tempLine.Mid( 1 );
                }
            }

            tmpMultiLines += tempLine;

            myWxFortranIndent.getFortranIndentLine( tmpMultiLines, indentNum, isCur, isCaseBegin );

            for( int j = isMultiLines.iFirstLineNo; j <= isMultiLines.iEndLineNo; ++j )
            {
                tempLine = control->GetLine( j ).Trim(false); // trim from left

                if( 0 == tempLine.Len() && j < tmpn )
                {
                    if( isOnlyBlankLine )
                    {
                        formattedText += eolChars;
                        continue;
                    }
                    else
                    {
                        tempLine += eolChars;
                    }
                }
                else
                {
                    if( isTrimLineFromRight )
                    {
                        tempLine.Trim(); //trim from right
                        if( j < tmpn )
                        {
                            tempLine += eolChars;
                        }
                    }
                }

                int tmpN = indentNum;
                if( j == isMultiLines.iFirstLineNo )
                {
                    if( false == isCur )
                    {
                        tmpN -= 1;
                    }
                }
				else
                {
                    tmpN += 1;
                }

                for( int k = 0; k < tmpN; ++k )
                {
                    formattedText += indentStr;
                }

                formattedText += tempLine;
            }

            isMultiLines.reset();
        }
        else
        {
            if( 0 == tmpLine.Len() && i < tmpn )
            {
                if( isOnlyBlankLine )
                {
                    formattedText += eolChars;
                    continue;
                }
                else
                {
                    tmpLine += eolChars;
                }
            }
            else
            {
                if( isTrimLineFromRight )
                {
                    tmpLine.Trim(); //trim from right
                    if( i < tmpn )
                    {
                        tmpLine += eolChars;
                    }
                }
                myWxFortranIndent.getFortranIndentLine( tmpLine, indentNum, isCur, isCaseBegin );
            }

            int tmpN = indentNum;
            if( false == isCur )
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
    }

    if( onlySelected )
    {
        if( isRemoveSelEOL )
        {
            //for( int i = 0; i < eolChars.Length(); ++i )
            //    formattedText.RemoveLast();
            formattedText.Trim(); // trim from right
        }
        formattedText.Trim(false); // trim from left
        formattedText = firstLineIndentStr + formattedText;
    }

    bool changed = myWxFortranIndent.BuffersDiffer( formattedText, !onlySelected ? edText : selText, eolChars, !( isOnlyBlankLine || isTrimLineFromRight ) );

    if ( changed )
    {
        control->BeginUndoAction();
        if (onlySelected)
        {
            control->ReplaceSelection(formattedText);
            if( 0 < new_bookmark_array.GetCount() )
            {
                ed->ToggleBookmark( tmpn );
            }
        }
        else
        {
            control->SetText(formattedText);
        }

        size_t iCount = new_bookmark_array.GetCount();
        for( size_t i = 0; i < iCount; ++i )
        {
            ed->ToggleBookmark( new_bookmark_array[i] ); // new_bookmark_array.Item(i)
        }

        iCount = 0;
        iCount = ed_breakpoints_array.GetCount();
        for( size_t i = 0; i < iCount; ++i )
        {
            ed->ToggleBreakpoint( ed_breakpoints_array[i] ); // ed_breakpoints_array.Item(i)
        }

        control->EndUndoAction();
        control->GotoPos(pos);
        ed->SetModified(true);
    }

    wxSetCursor(wxNullCursor);

    new_bookmark_array.Clear();
    ed_breakpoints_array.Clear();

    return changed;
}

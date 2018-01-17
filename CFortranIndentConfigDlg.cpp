/***************************************************************
 * Name:        CFortranIndentConfigDlg.cpp
 * Purpose:     Class to Configure Fortran Indent Dialog
 * Author:      YWX (wxFortranIndent@163.com)
 * Created:     2012-4-24
 * Copyright:   (c) YWX <wxFortranIndent@163.com>
 * Licence:     GNU General Public License, version 3
 **************************************************************/

#include <sdk.h>
#include "CFortranIndentConfigDlg.h"
#include "CMyFortranIndentConfig.h"
#include <configmanager.h>
#include <wx/xrc/xmlres.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/radiobox.h>
#include <string>

BEGIN_EVENT_TABLE( CFortranIndentConfigDlg, wxPanel )
    EVT_CHECKBOX( XRCID("cb_SameAsEditor"), CFortranIndentConfigDlg::OnIsSameAsEditorClick )
    EVT_CHECKBOX( XRCID("cb_UseTab"), CFortranIndentConfigDlg::OnIsUseTabClick )
END_EVENT_TABLE()

CFortranIndentConfigDlg::CFortranIndentConfigDlg(wxWindow* parent)
{
    wxXmlResource::Get()->LoadPanel(this, parent, _T("dlgFortranIndent"));

    LoadSettings();
}

CFortranIndentConfigDlg::~CFortranIndentConfigDlg()
{
}

void CFortranIndentConfigDlg::LoadSettings()
{
	ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("fortran_indent"));

	CMyFortranIndentConfig myFortranIndentConfig;

	if( cfg->Read( _T("is_SameAsEditor"), & myFortranIndentConfig.isSameAsEditor ) )
	{
		cfg->Read( _T("is_UseTab"), & myFortranIndentConfig.isUseTab );
		cfg->Read( _T("i_TabWidth"), & myFortranIndentConfig.iTabWidth );
		cfg->Read( _T("is_KeepBlankLineOnly"), & myFortranIndentConfig.isKeepBlankLineOnly );
		cfg->Read( _T("is_TrimLineFromRight"), & myFortranIndentConfig.isTrimLineFromRight );
		cfg->Read( _T("i_PreprocessorType"), & myFortranIndentConfig.iPreprocessorType );
	}

    XRCCTRL(*this, "cb_SameAsEditor", wxCheckBox)->SetValue( myFortranIndentConfig.isSameAsEditor );
    XRCCTRL(*this, "cb_UseTab", wxCheckBox)->SetValue( myFortranIndentConfig.isUseTab );
	XRCCTRL(*this, "cb_UseTab", wxCheckBox)->Enable( ! myFortranIndentConfig.isSameAsEditor );
    XRCCTRL(*this, "sp_TabWidth", wxSpinCtrl)->SetValue( myFortranIndentConfig.iTabWidth );
	XRCCTRL(*this, "sp_TabWidth", wxSpinCtrl)->Enable( ! ( myFortranIndentConfig.isSameAsEditor || myFortranIndentConfig.isUseTab ) );
    XRCCTRL(*this, "cb_KeepBlankLineOnly", wxCheckBox)->SetValue( myFortranIndentConfig.isKeepBlankLineOnly );
    XRCCTRL(*this, "cb_TrimLineFromRight", wxCheckBox)->SetValue( myFortranIndentConfig.isTrimLineFromRight );
    XRCCTRL(*this, "rb_PreprocessorType", wxRadioBox)->SetSelection( myFortranIndentConfig.iPreprocessorType );
}

void CFortranIndentConfigDlg::SaveSettings()
{
    ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("fortran_indent"));

    cfg->Write(_T("is_SameAsEditor"), (bool) XRCCTRL(*this, "cb_SameAsEditor", wxCheckBox)->GetValue());
    cfg->Write(_T("is_UseTab"), (bool) XRCCTRL(*this, "cb_UseTab", wxCheckBox)->GetValue());
	cfg->Write(_T("i_TabWidth"), (int) XRCCTRL(*this, "sp_TabWidth", wxSpinCtrl)->GetValue());
	cfg->Write(_T("is_KeepBlankLineOnly"), (bool) XRCCTRL(*this, "cb_KeepBlankLineOnly", wxCheckBox)->GetValue());
    cfg->Write(_T("is_TrimLineFromRight"), (bool) XRCCTRL(*this, "cb_TrimLineFromRight", wxCheckBox)->GetValue());
    cfg->Write(_T("i_PreprocessorType"), (int) XRCCTRL(*this, "rb_PreprocessorType", wxRadioBox)->GetSelection());
}

void CFortranIndentConfigDlg::OnIsSameAsEditorClick(wxCommandEvent& event)
{
    bool isSameAsEditor = XRCCTRL(*this, "cb_SameAsEditor", wxCheckBox)->GetValue();
    XRCCTRL(*this, "cb_UseTab", wxCheckBox)->Enable( ! ( isSameAsEditor ) );
    bool isUseTab = XRCCTRL(*this, "cb_UseTab", wxCheckBox)->GetValue();
    XRCCTRL(*this, "sp_TabWidth", wxSpinCtrl)->Enable( ! ( isSameAsEditor || isUseTab ) );
}

void CFortranIndentConfigDlg::OnIsUseTabClick(wxCommandEvent& event)
{
    ///
    XRCCTRL(*this, "sp_TabWidth", wxSpinCtrl)->Enable( ! ( XRCCTRL(*this, "cb_UseTab", wxCheckBox)->GetValue() ) ); // event.IsChecked()
}

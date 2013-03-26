/***************************************************************
 * Name:        CFortranIndentConfigDlg.h
 * Purpose:     declaration of CFortranIndentConfigDlg class
 * Author:      YWX (wxFortranIndent@163.com)
 * Created:     2012-4-25
 * Copyright:   (c) YWX <wxFortranIndent@163.com>
 * Licence:     GNU General Public License, version 3
 **************************************************************/

#ifndef _MY_WX_CFortranIndentConfigDlg_H_
#define _MY_WX_CFortranIndentConfigDlg_H_

#include <wx/intl.h>
#include "configurationpanel.h"


class CFortranIndentConfigDlg : public cbConfigurationPanel
{
	public:
		CFortranIndentConfigDlg(wxWindow* parent);
		virtual ~CFortranIndentConfigDlg();

	protected:
        virtual wxString GetTitle() const { return _("Fortran Indent"); }
        virtual wxString GetBitmapBaseName() const { return _T("Format_Fortran_Indent_Plugin"); }
        virtual void OnApply(){ SaveSettings(); }
        virtual void OnCancel(){}

        void LoadSettings();
        void SaveSettings();

        void OnIsSameAsEditorClick(wxCommandEvent& event);
        void OnIsUseTabClick(wxCommandEvent& event);

	private:
        DECLARE_EVENT_TABLE()
};


#endif // _MY_WX_CFortranIndentConfigDlg_H_

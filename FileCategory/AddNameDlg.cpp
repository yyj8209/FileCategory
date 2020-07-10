// AddName.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCategory.h"
#include "AddNameDlg.h"
#include "afxdialogex.h"


// CAddNameDlg 对话框

IMPLEMENT_DYNAMIC(CAddNameDlg, CDialog)

CAddNameDlg::CAddNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNameDlg::IDD, pParent)
	, m_strName(_T(""))
{

}

CAddNameDlg::~CAddNameDlg()
{
}

void CAddNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CAddNameDlg, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



void CAddNameDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	(CEdit *)GetDlgItem(IDC_EDIT_NAME)->SetFocus();
}


BOOL CAddNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(m_strDlgCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

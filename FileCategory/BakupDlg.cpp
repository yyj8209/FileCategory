// BakupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCategory.h"
#include "BakupDlg.h"
#include "afxdialogex.h"


// CBakupDlg 对话框

IMPLEMENT_DYNAMIC(CBakupDlg, CDialog)

CBakupDlg::CBakupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBakupDlg::IDD, pParent)
	, m_strInfo(_T("提示:"))
	, bChecked(true)
{

}

CBakupDlg::~CBakupDlg()
{
}

void CBakupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBakupDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_BACKUP, &CBakupDlg::OnBnClickedCheckBackup)
END_MESSAGE_MAP()


// CBakupDlg 消息处理程序


BOOL CBakupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemTextA(IDC_STATIC, m_strInfo);
	CButton *pCheckBox = (CButton *)GetDlgItem(IDC_CHECK_BACKUP);
	pCheckBox->SetCheck(1);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CBakupDlg::OnBnClickedCheckBackup()
{
	// TODO:  在此添加控件通知处理程序代码
	bChecked = ~bChecked;
}

// AddName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCategory.h"
#include "AddNameDlg.h"
#include "afxdialogex.h"


// CAddNameDlg �Ի���

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

	// TODO:  �ڴ˴������Ϣ����������
	(CEdit *)GetDlgItem(IDC_EDIT_NAME)->SetFocus();
}


BOOL CAddNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(m_strDlgCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

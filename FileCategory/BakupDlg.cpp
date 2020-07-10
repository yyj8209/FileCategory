// BakupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCategory.h"
#include "BakupDlg.h"
#include "afxdialogex.h"


// CBakupDlg �Ի���

IMPLEMENT_DYNAMIC(CBakupDlg, CDialog)

CBakupDlg::CBakupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBakupDlg::IDD, pParent)
	, m_strInfo(_T("��ʾ:"))
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


// CBakupDlg ��Ϣ�������


BOOL CBakupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemTextA(IDC_STATIC, m_strInfo);
	CButton *pCheckBox = (CButton *)GetDlgItem(IDC_CHECK_BACKUP);
	pCheckBox->SetCheck(1);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CBakupDlg::OnBnClickedCheckBackup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bChecked = ~bChecked;
}

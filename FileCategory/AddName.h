#pragma once


// CAddNameDlg �Ի���

class CAddNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddNameDlg)

public:
	CAddNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddNameDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strDlgCaption;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
};

#pragma once


// CBakupDlg �Ի���

class CBakupDlg : public CDialog
{
	DECLARE_DYNAMIC(CBakupDlg)

public:
	CBakupDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBakupDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInfo;
	BOOL bChecked;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckBackup();
};

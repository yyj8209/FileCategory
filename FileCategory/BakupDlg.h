#pragma once


// CBakupDlg 对话框

class CBakupDlg : public CDialog
{
	DECLARE_DYNAMIC(CBakupDlg)

public:
	CBakupDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBakupDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInfo;
	BOOL bChecked;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckBackup();
};

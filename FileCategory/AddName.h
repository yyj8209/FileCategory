#pragma once


// CAddNameDlg 对话框

class CAddNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddNameDlg)

public:
	CAddNameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddNameDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strDlgCaption;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
};


// FileCategoryDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <string.h>
#include "CWMPPlayer40.h"
#include <vector>
#include "afxdtctl.h"
using namespace std;

// CFileCategoryDlg 对话框
class CFileCategoryDlg : public CDialogEx
{
// 构造
public:
	CFileCategoryDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FILECATEGORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CString m_decDriver;
	vector<CString> vecFileSource;//将源文件路径保存到vecFileSource对象中
	vector<CString> vecFileDest;  //将目的路径保存到vecFileDest对象中

public:
	CString CheckMobileDisk();
	void InitMobileDisk();
	void InitUploader();
	void InitRecorder();
	void InitListCtrl();
	void UpdateListCtrl();
	void UpdateTreeCtrl();
	vector<CString> GenDestPath();
	void InitDestPath(CString FileName);
	void EditDestPath(int n);
	void MP4Info(int n);
	void CreateDirectory(CString destination);


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox cbMobileDisk;
//	CString sPlace;
	CWMPPlayer40 wnpPlayer;
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnCbnSelchangeComboUploader();
	afx_msg void OnChangeEditPlace();
	afx_msg void OnSelchangeComboRecorde();


	DECLARE_EVENTSINK_MAP()
//	void OnClickOcx(short nButton, short nShiftState, long fX, long fY);
	CComboBox cbRecorder;
	CComboBox cbUploader;
	afx_msg void OnBnClickedButtonSource();
	CListCtrl listCtrl;
	CDateTimeCtrl dtTime;
	afx_msg void OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonDel();
//	afx_msg void OnItemclickList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit edPlace;
//	afx_msg void OnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEdit();
	CProgressCtrl progressCtrl;
};

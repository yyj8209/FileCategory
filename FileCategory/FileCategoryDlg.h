
// FileCategoryDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "CWMPPlayer40.h"

// CFileCategoryDlg �Ի���
class CFileCategoryDlg : public CDialogEx
{
// ����
public:
	CFileCategoryDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILECATEGORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CString m_decDriver;

private:
	CString CheckMobileDisk();
	void InitMobileDisk();
	void InitUploader();
	void InitRecorder();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox cbMobileDisk;
	CString sPlace;
	CTreeCtrl treePath;
	CWMPPlayer40 wnpPlayer;
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnCbnSelchangeComboUploader();
	afx_msg void OnChangeEditPlace();
	afx_msg void OnSelchangeComboRecorde();


	DECLARE_EVENTSINK_MAP()
	void OnClickOcx1(short nButton, short nShiftState, long fX, long fY);
	CComboBox cbRecorder;
	CComboBox cbUploader;
	afx_msg void OnBnClickedButtonSource();
};

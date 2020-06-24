
// FileCategoryDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <string.h>
#include "DLEdit.h"
#include "CWMPPlayer40.h"
#include <vector>
#include "afxdtctl.h"
using namespace std;

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
	CToolBar m_Toolbar;
	CBitmap m_bmpSettings, m_bmpRun, m_bmpExit;
	CImageList m_Imagelist;
	int nEditSel;     // ѡ�еı����

private:
	CString m_decDriver;
	vector<CString> vecFileSource;//��Դ�ļ�·�����浽vecFileSource������
	vector<CString> vecFileDest;  //��Ŀ��·�����浽vecFileDest������
	vector<CString> DiskName;


public:
	void CheckMobileDisk();
	void InitMobileDisk();
	void InitUploader();
	void InitRecorder();
	void InitListCtrl();
	void UpdateListCtrl();
	void UpdateTreeCtrl();
	void InitToolBar();
	vector<CString> GenDestPath();
	void InitDestPath(CString FileName);
	CString EditDestPath(int n);
	void MP4Info(int n);
	void CreateDirectory(CString destination);


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL   OnDeviceChange(UINT   nEventType, DWORD   dwData);
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);  // ��������ʾ 
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
	CDLEdit edPlace;
//	afx_msg void OnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEdit();
	CProgressCtrl progressCtrl;
	CButton m_btnDel;
	CButton m_btnEdit;
	afx_msg void OnIdrToolbarStart();
	afx_msg void OnIdrToolbarStop();
	afx_msg void OnIdrToolbarSettings();
//	afx_msg void OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};

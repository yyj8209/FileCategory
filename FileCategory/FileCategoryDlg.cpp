
// FileCategoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCategory.h"
#include "FileCategoryDlg.h"
#include "afxdialogex.h"
#include "shlwapi.h"
#include <algorithm>
#include "AddNameDlg.h"
#include "BakupDlg.h"
#include <shlobj.h>
#include <assert.h>

#import <Shell32.dll>
using namespace std;
#pragma comment(lib, "shlwapi.lib")



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnIdrToolbarSettings();
//	afx_msg void OnIdrToolbarStart();
//	afx_msg void OnIdrToolbarStop();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_INPUT_DEVICE_CHANGE()
//	ON_COMMAND(IDR_TOOLBAR_SETTINGS, &CAboutDlg::OnIdrToolbarSettings)
//	ON_COMMAND(IDR_TOOLBAR_START, &CAboutDlg::OnIdrToolbarStart)
//	ON_COMMAND(IDR_TOOLBAR_STOP, &CAboutDlg::OnIdrToolbarStop)
END_MESSAGE_MAP()


// CFileCategoryDlg �Ի���



CFileCategoryDlg::CFileCategoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileCategoryDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nEditSel = 0;
}

void CFileCategoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MOBILEDISK, cbMobileDisk);
	//  DDX_Text(pDX, IDC_EDIT_PLACE, sPlace);
	DDX_Control(pDX, IDC_OCX, wnpPlayer);
	DDX_Control(pDX, IDC_COMBO_RECORDE, cbRecorder);
	DDX_Control(pDX, IDC_COMBO_UPLOADER, cbUploader);
	DDX_Control(pDX, IDC_LIST, listCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER, dtTime);
	DDX_Control(pDX, IDC_EDIT_PLACE, edPlace);
	DDX_Control(pDX, IDC_PROGRESS, progressCtrl);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BUTTON_ADD_LOADER, m_btnAddLoader);
	DDX_Control(pDX, IDC_BUTTON_ADD_RECORDER, m_btnAddRecorder);
}

BEGIN_MESSAGE_MAP(CFileCategoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DEVICECHANGE()// U�̲�����γ�
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CFileCategoryDlg::OnBnClickedButtonMove)
	ON_CBN_SELCHANGE(IDC_COMBO_UPLOADER, &CFileCategoryDlg::OnCbnSelchangeComboUploader)
	ON_EN_CHANGE(IDC_EDIT_PLACE, &CFileCategoryDlg::OnChangeEditPlace)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORDE, &CFileCategoryDlg::OnSelchangeComboRecorde)
	ON_BN_CLICKED(IDC_BUTTON_SOURCE, &CFileCategoryDlg::OnBnClickedButtonSource)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER, &CFileCategoryDlg::OnDtnDatetimechangeDatetimepicker)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CFileCategoryDlg::OnClickedButtonDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CFileCategoryDlg::OnClickList)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CFileCategoryDlg::OnBnClickedButtonEdit)

	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xffff, OnToolTipText)
	ON_BN_CLICKED(ID_TOOLBAR_RUN, &CFileCategoryDlg::OnIdrToolbarStart)
	ON_BN_CLICKED(ID_TOOLBAR_EXIT, &CFileCategoryDlg::OnIdrToolbarStop)
	ON_BN_CLICKED(ID_TOOLBAR_SETTINGS, &CFileCategoryDlg::OnIdrToolbarSettings)
	ON_BN_CLICKED(ID_TOOLBAR_ADD, &CFileCategoryDlg::OnIdrToolbarAdd)
	//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, &CFileCategoryDlg::OnCustomdrawList)
	ON_BN_CLICKED(IDOK, &CFileCategoryDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_LOADER, &CFileCategoryDlg::OnBnClickedButtonAddLoader)
	ON_BN_CLICKED(IDC_BUTTON_ADD_RECORDER, &CFileCategoryDlg::OnBnClickedButtonAddRecorder)
	ON_CBN_SELCHANGE(IDC_COMBO_MOBILEDISK, &CFileCategoryDlg::OnSelchangeComboMobiledisk)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CFileCategoryDlg, CDialogEx)
//	ON_EVENT(CFileCategoryDlg, IDC_OCX, 6505, CFileCategoryDlg::OnClickOcx, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

// CFileCategoryDlg ��Ϣ�������

BOOL CFileCategoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//m_decDriver = CheckMobileDisk();
	//CheckMobileDisk();
	edPlace.SetWindowText(_T("��鳡������"));
	InitMobileDisk();
	InitUploader();
	InitRecorder();
	InitListCtrl();
	InitToolBar();
	InitImageButton();
	GetDlgItem(IDC_BUTTON_SOURCE)->SetFocus();
	
	return false;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFileCategoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileCategoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFileCategoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��������ʼ��
void CFileCategoryDlg::InitToolBar(){
	if (!m_Toolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS) ||
		!m_Toolbar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("δ�ܴ���������\n");
		return;      // δ�ܴ���  
	}
	m_Toolbar.ShowWindow(SW_SHOW);
	//�ؼ�����λ  
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 40);

	m_bmpSettings.LoadBitmapA(IDB_BITMAP_SETTINGS);
	m_bmpAdd.LoadBitmapA(IDB_BITMAP_ADD);
	m_bmpRun.LoadBitmapA(IDB_BITMAP_START);
	m_bmpExit.LoadBitmapA(IDB_BITMAP_STOP);
	m_Imagelist.Create(32, 32, ILC_COLOR32 | ILC_MASK, 10, 0);
	m_Imagelist.Add(&m_bmpSettings, RGB(0,0,0));
	m_Imagelist.Add(&m_bmpAdd, RGB(0, 0, 0));
	m_Imagelist.Add(&m_bmpRun, RGB(0, 0, 0));
	m_Imagelist.Add(&m_bmpExit, RGB(0, 0, 0));
	m_Toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist);
}

// ��������ʾ
BOOL CFileCategoryDlg::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	TOOLTIPTEXT   *pTTT = (TOOLTIPTEXT*)pNMHDR;
	UINT  uID = pNMHDR->idFrom;     // �൱��ԭWM_COMMAND���ݷ�ʽ��wParam��low-order��, ��wParam�зŵ����ǿؼ���ID��  

	if (pTTT->uFlags  &  TTF_IDISHWND)
		uID = ::GetDlgCtrlID((HWND)uID);
	if (uID == NULL)
		return   FALSE;
	switch (uID)
	{
	case ID_TOOLBAR_EXIT:
		pTTT->lpszText = _T("�˳�����");
		break;

	case ID_TOOLBAR_RUN:
		pTTT->lpszText = _T("ִ����Ƶ����");
		break;

	case ID_TOOLBAR_SETTINGS:
		pTTT->lpszText = _T("����");
		break;

	case ID_TOOLBAR_ADD:
		pTTT->lpszText = _T("�����Ƶ");
		break;
	}

	return TRUE;
}

void CFileCategoryDlg::CheckMobileDisk()
{
	int DSLength = 64;  // GetLogicalDriveStrings(0, NULL);
	//ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ���ȡ�
	char* DStr = new char[DSLength];//�û�ȡ�ĳ����ڶ�������һ��c�����ַ�������
	::GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);
	//ͨ��GetLogicalDriveStrings���ַ�����Ϣ���Ƶ�����������,���б�������������������Ϣ��
	CString a;
	BOOL bFirst = true;
	int DType;
	int si = 0;
	for (int i = 0; i < DSLength / 4; ++i)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		char dir[3] = { DStr[si], ':', '\\' };
		DType = GetDriveType((LPTSTR)DStr + i * 4);
		//GetDriveType���������Ի�ȡ���������ͣ�����Ϊ�������ĸ�Ŀ¼
		//if (DType == DRIVE_REMOVABLE)
		//{
			CString a(dir[0]);
			a = a + ':' + '\\';
			DiskName.push_back(a);
			//if (bFirst)
			//{
			//	DiskName.push_back(a);
			//	bFirst = false;
			//}
			for (int j = 0; j < DiskName.size(); j++)
			{
				if (!a.Compare(DiskName.at(j)))
				{
					continue;
				}
			}
		//}
		si += 4;
	}
	sort(DiskName.begin(), DiskName.end());
	DiskName.erase(unique(DiskName.begin(), DiskName.end()), DiskName.end());//ʹ�� erase ɾ��
	for (int i = 0; i < DiskName.size(); i++)
		cbMobileDisk.InsertString(i, DiskName.at(i));
	cbMobileDisk.SetCurSel(0);
//	return _T("δ�����ƶ�Ӳ��");
}

BOOL  CFileCategoryDlg::OnDeviceChange(UINT   nEventType, DWORD   dwData)
{

	//CheckMobileDisk();
	return true;
}

void CFileCategoryDlg::InitMobileDisk()
{
	CString sDisk[10] = { _T("D:\\"), _T("E:\\"), _T("F:\\"), _T("G:\\"), _T("H:\\"), \
		_T("I:\\"), _T("J:\\"), _T("K:\\"), _T("L:\\"), _T("M:\\") };
	int strLen = sizeof(sDisk) / sizeof(sDisk[0]);
	for (int i = 0; i < strLen; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbMobileDisk.InsertString(i, sDisk[i]);
	}
	cbMobileDisk.SetCurSel(0);
}

void CFileCategoryDlg::InitUploader()
{
	CString sUploader[8] = { _T("������"), _T("������"), _T("����"), _T("����ʤ"), _T("����"), _T("ʷ�̻�"), _T("��ɾ�"), _T("���Ƚ�") };
	int strLen = sizeof(sUploader) / sizeof(sUploader[0]);
	for (int i = 0; i < strLen; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbUploader.InsertString(i, sUploader[i]);
	}
	cbUploader.SetCurSel(0);
}

void CFileCategoryDlg::InitRecorder()
{
	CString sRecorder[8] = { _T("������"), _T("������"), _T("����"), _T("����ʤ"), _T("����"), _T("����ܿ"), _T("��ɾ�"), _T("���Ƚ�") };
	int strLen = sizeof(sRecorder) / sizeof(sRecorder[0]);
	for (int i = 0; i < strLen; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbRecorder.InsertString(i, sRecorder[i]);
	}
	cbRecorder.SetCurSel(0);
}

void CFileCategoryDlg::InitListCtrl()
{

	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // ����ѡ��������
	listCtrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, 50);   // ��ͷ
	listCtrl.InsertColumn(1, _T("ԭ��Ƶ�ļ�"), LVCFMT_LEFT, 450);
	listCtrl.InsertColumn(2, _T("������λ��"), LVCFMT_LEFT, 450);

}

void CFileCategoryDlg::UpdateListCtrl()
{
	listCtrl.DeleteAllItems();
	int size = vecFileSource.size();
	for (int i = 0; i < size; i++)
	{   //������
		CString a;
		a.Format(_T("%d"), i + 1);
		listCtrl.InsertItem(i, a);  // �������
		listCtrl.SetItemText(i, 1, vecFileSource.at(i));
		listCtrl.SetItemText(i, 2, vecFileDest.at(i));
		
	}
	listCtrl.SetSelectionMark(0);
}

void CFileCategoryDlg::InitImageButton()
{
	HINSTANCE hInstance;
	HBITMAP hBitmap;
	hInstance = ::AfxGetInstanceHandle();
	hBitmap = ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP_ADDER));
	m_btnAddLoader.SetBitmap(hBitmap);
	m_btnAddRecorder.SetBitmap(hBitmap);
}

void CFileCategoryDlg::CreateDirectory(CString destination)

{
	CString dir, tmp;
	dir.Empty();
	while (destination.Find('\\') > 0)
	{
		dir.Append(destination.Left(destination.Find('\\') + 1));//��·���н�ȡ�ļ���;
		if (!PathIsDirectory(dir))
		{
			::CreateDirectory(dir, NULL);//����Ŀ¼,���еĻ���Ӱ��
		}
		tmp = destination;
		destination = tmp.Right(tmp.GetLength() - tmp.Find('\\') - 1);
	}
}

void CFileCategoryDlg::DeleteDirectory(CString strDir)
{
	if (strDir.IsEmpty())
	{
		RemoveDirectory(strDir);
		return;
	}
	//����ɾ���ļ������ļ��� 
	CFileFind   ff;
	BOOL bFound = ff.FindFile(strDir + _T("\\*"),0);
	while (bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.GetFileName() == _T(".") || ff.GetFileName() == _T(".."))
			continue;
		//ȥ���ļ�(��)ֻ�������� 
		CString strFilePath = ff.GetFilePath();
		SetFileAttributes(strFilePath, FILE_ATTRIBUTE_NORMAL);
		if (ff.IsDirectory())
		{
			//�ݹ�ɾ�����ļ��� 
			DeleteDirectory(strFilePath);
			RemoveDirectory(strFilePath);
		}
		else
		{
			DeleteFile(strFilePath);   //ɾ���ļ� 
		}
	}
	ff.Close();

	//Ȼ��ɾ�����ļ��� 
	RemoveDirectory(strDir);
}
//	��������������������������������
//	��Ȩ����������ΪCSDN������Ambition_ZB����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�http://blog.sina.com.cn/s/blog_733880070102vrmv.html
void CFileCategoryDlg::OnBnClickedButtonMove()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int size = vecFileSource.size();
	if (size < 1)
	{
		MessageBox(_T("��ѡ���ļ����༭��Ϣ����ִ�з��ࡣ"), _T("δѡ���κ���Ƶ"), MB_OK);
		return;
	}
	CBakupDlg dlg;
	vector<CString> vecDelPath = GenDelPath();
	CString sDelPath("");
	for (int i = 0; i < vecDelPath.size(); i++)
		sDelPath += vecDelPath.at(i) + _T(" & ") ;
	
	dlg.m_strInfo = _T("��Ƶ���࣬������Ҫ������\r\n""���β�����ɾ������Ŀ¼��\r\n") + sDelPath + _T("\r\n");

	int ID = dlg.DoModal();
	if ( ID == IDCANCEL) // MessageBox(_T("����ִ����Ƶ���࣬������Ҫ�����ӡ�"), _T("�Ƿ�ִ����Ƶ���ࣿ"), MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
		return;

	// ɾ��Ŀ¼
	for (int i = 0; i < vecDelPath.size(); i++)
		DeleteDirectory(vecDelPath.at(i));

	// �����ļ�
	BOOL bChecked = dlg.bChecked;
	vector<CString> vecBackPath = GenBackpath();
	CString src, dest;
	progressCtrl.SetRange(0, size);
	progressCtrl.SetStep(1);
	progressCtrl.SetPos(0);
	progressCtrl.ShowWindow(true);
	for (int i = 0; i < size; i++)
	{
		src = vecFileSource.at(i);
		dest = vecFileDest.at(i);
		CreateDirectory(dest);
		progressCtrl.SetPos(i+1);
		SetDlgItemText(IDC_STATIC_PROGRESS, _T("������������ڿ��� ") + dest);
		CopyFile((LPCSTR)src, (LPCSTR)dest, true);
		if (bChecked)
		{
			CreateDirectory(vecBackPath.at(i));
			CopyFile((LPCSTR)src, (LPCSTR)vecBackPath.at(i), true);   // �����ļ�
		}
	}
	progressCtrl.ShowWindow(false);
	(CStatic *)GetDlgItem(IDC_STATIC_PROGRESS)->ShowWindow(false);
	AfxMessageBox(_T("��Ƶ�������"));

	// �ѵ����ִ�е�λ��ϸд���ļ���
	CString CurDisk;
	CComboBox * pCb = (CComboBox *)GetDlgItem(IDC_COMBO_MOBILEDISK);
	pCb->GetLBText(pCb->GetCurSel(), CurDisk);
	CString pszFileName = CurDisk + _T("ִ������Ƶ����\\��Ƶ�ļ���¼.txt");
	vector<CString> vecTxt = GenVec4Txt(vecFileDest);
	WriteTxt((LPCSTR)pszFileName, vecTxt);
}



void CFileCategoryDlg::OnCbnSelchangeComboUploader()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFileCategoryDlg::OnChangeEditPlace()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFileCategoryDlg::OnSelchangeComboRecorde()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFileCategoryDlg::OnBnClickedButtonSource()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TCHAR        szLargeBuf[4096]; // ����һ����ʱ������
	memset(szLargeBuf, '\0', 4096);
	CFileDialog dlg(TRUE, _T("*.mp4"), NULL, OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, _T("��Ƶ�ļ�(*.mp4;*.avi)|*.mp4|All Files (*.*)|*.*||"), NULL);
	dlg.m_ofn.lpstrFile = szLargeBuf;

#ifdef UNICODE
	dlg.m_ofn.nMaxFile = 4096;
#else
	dlg.m_ofn.nMaxFile = sizeof (szLargeBuf);
#endif

	CString filename;

	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		while (fileNamesPosition != NULL)
		{
			filename = dlg.GetNextPathName(fileNamesPosition);
			vecFileSource.push_back(filename);
			InitDestPath(filename);   // ��ԴĿ¼��Сһ��
		}
	}

	UpdateListCtrl();
	/*��������������������������������
		��Ȩ����������ΪCSDN�������̺����ơ���ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
	ԭ�����ӣ�https ://blog.csdn.net/u012260238/article/details/56489318
	*/

}

vector<CString> CFileCategoryDlg::GenDestPath()
{
	vector<CString> vecPath;
	CString sHD, sUp, sDt, sPl, sRc;
	int i = cbMobileDisk.GetCurSel();//��ȡ������0-N
	cbMobileDisk.GetLBText(i, sHD);

	i = cbUploader.GetCurSel();//��ȡ������0-N
	cbUploader.GetLBText(i, sUp);

	CTime timeDest;
	dtTime.GetTime(timeDest);
	sDt = timeDest.Format("%Y%m%d");

	edPlace.GetWindowText(sPl);

	i = cbRecorder.GetCurSel();//��ȡ������0-N
	cbRecorder.GetLBText(i, sRc);

	vecPath.push_back(sHD);   // �弶Ŀ¼
	vecPath.push_back(sUp);
	vecPath.push_back(sDt);
	vecPath.push_back(sPl);
	vecPath.push_back(sRc);

	sHD.ReleaseBuffer();
	sUp.ReleaseBuffer();
	sDt.ReleaseBuffer();
	sPl.ReleaseBuffer();
	sRc.ReleaseBuffer();

	return vecPath;
}

void CFileCategoryDlg::InitDestPath(CString FileName)
{
	vector<CString> tmp = GenDestPath();
	CString sHD, sUp, sDt, sPl, sRc, sFile;
	sHD = tmp.at(0);
	sUp = tmp.at(1);
	sDt = tmp.at(2);
	sPl = tmp.at(3);
	sRc = tmp.at(4);
	sFile = FileName.Right(FileName.GetLength() - FileName.ReverseFind('\\') - 1);//��·���н�ȡ�ļ���;

	vecFileDest.push_back(sHD + sUp + "\\" + sDt + "\\" + sPl + "\\" + sRc + "\\" + sFile);

	sHD.ReleaseBuffer();
	sUp.ReleaseBuffer();
	sDt.ReleaseBuffer();
	sPl.ReleaseBuffer();
	sRc.ReleaseBuffer();

}

vector<CString> CFileCategoryDlg::GenDelPath()
{
	vector<CString> vecDelPath;
	int size = vecFileDest.size();
	CString disk, uploader, dest, tmp, sDelPath;
	for (int i = 0; i < size; i++)
	{
		dest = vecFileDest.at(i);
		disk = dest.Left(dest.Find('\\'));
		tmp = dest.Right(dest.GetLength() - dest.Find('\\') - 1);
		uploader = tmp.Left(tmp.Find('\\'));
		sDelPath = disk + "\\" + uploader;
		if (vecDelPath.size()==0)
			vecDelPath.push_back(sDelPath);

		if (!PathExist(vecDelPath, sDelPath))
			vecDelPath.push_back(sDelPath);
	}

	return vecDelPath;
}

BOOL CFileCategoryDlg::PathExist(vector<CString> vecPath, CString strPath)
{
	BOOL bExist = false;
	for (int j = 0; j < vecPath.size(); j++)
	{
		if (vecPath.at(j).Compare(strPath) == 0)
		{
			bExist = true;
			break;
		}
	}
	return bExist;
}

vector<CString> CFileCategoryDlg::GenBackpath()
{
	vector<CString> vecBackPath;
	int size = vecFileDest.size();
	CString disk, uploader, dest, tmp, sOld, sNew;
	for (int i = 0; i < size; i++)
	{
		dest = vecFileDest.at(i);
		disk = dest.Left(dest.Find('\\'));
		tmp = dest.Right(dest.GetLength() - dest.Find('\\') - 1);
		uploader = tmp.Left(tmp.Find('\\'));
		sOld = disk + "\\" + uploader;
		sNew = disk + "\\ִ������Ƶ����";
		dest.Replace(sOld, sNew);
		vecBackPath.push_back(dest);
	}

	return vecBackPath;
}

CString CFileCategoryDlg::EditDestPath(int nSel)
{
	vecFileDest.erase(vecFileDest.begin() + nSel);

	vector<CString> tmp = GenDestPath();
	CString FileName = listCtrl.GetItemText(nSel, 1);

	CString sHD, sUp, sDt, sPl, sRc, sFile;
	sHD = tmp.at(0);
	sUp = tmp.at(1);
	sDt = tmp.at(2);
	sPl = tmp.at(3);
	sRc = tmp.at(4);
	sFile = FileName.Right(FileName.GetLength() - FileName.ReverseFind('\\') - 1);//��·���н�ȡ�ļ���;
	

	vecFileDest.insert(vecFileDest.begin() + nSel, sHD + sUp + "\\" + sDt + "\\" + sPl + "\\" + sRc + "\\" + sFile);
	FileName = sHD + sUp + "\\" + sDt + "\\" + sPl + "\\" + sRc + "\\" + sFile;
	sHD.ReleaseBuffer();
	sUp.ReleaseBuffer();
	sDt.ReleaseBuffer();
	sPl.ReleaseBuffer();
	sRc.ReleaseBuffer();

	return FileName;

}


void CFileCategoryDlg::MP4Info(int nSel)
{
	CString PathName, tmp;
	PathName = vecFileDest.at(nSel);

	vector<CString> sInfo;
	while (PathName.Find('\\') > 0)
	{
		tmp = PathName.Left(PathName.Find('\\') + 0);//��·���н�ȡ�ļ���;
		sInfo.push_back(tmp);
		tmp = PathName;
		PathName = tmp.Right(tmp.GetLength() - tmp.Find('\\') - 1);
	}

	cbUploader.SelectString(0, sInfo.at(1));  // �ϴ���Ա��
	edPlace.SetWindowTextA(sInfo.at(3));      // ����
	cbRecorder.SelectString(0, sInfo.at(4));  // ������Ա��

	COleDateTime dt;
	tmp = sInfo.at(2);
//	dt.ParseDateTime("2020/05/01");    //������ֵ�浽dt��
	dt.ParseDateTime(tmp.Left(4) + "/" + tmp.Mid(4, 2) + "/" + tmp.Right(2));    //������ֵ�浽dt��
	SYSTEMTIME st;    //����һ��ϵͳʱ�����͵ı���
	dt.GetAsSystemTime(st);    //��dt�е�ʱ�䰴ϵͳʱ���ʽ��
	CTime m_Date(st);
	dtTime.SetTime(&m_Date);
}


void CFileCategoryDlg::OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}



void CFileCategoryDlg::OnClickedButtonDel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int n = listCtrl.GetSelectionMark();
	if (vecFileSource.size() < 1)
	{
		MessageBox(_T("�ļ��б�Ϊ�գ��뵼���ļ���"));
		return;
	}
	if (MessageBox(_T("���β������������� " + vecFileSource.at(n)), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
		return;

	listCtrl.DeleteItem(n);
	vecFileSource.erase(vecFileSource.begin() + n);
	vecFileDest.erase(vecFileDest.begin() + n);
	wnpPlayer.close();

	UpdateListCtrl();

}


void CFileCategoryDlg::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nSel = listCtrl.GetSelectionMark();
	CString strFisrtEdit = listCtrl.GetItemText(nSel, 0);
	CString strFileName = listCtrl.GetItemText(nSel, 1);
	if (strFisrtEdit.Find(_T("���")) != -1)
		MP4Info(nSel);    // ��ʾ��Ƶ��Ϣ��
	wnpPlayer.put_URL(strFileName);
	//vector<CString> vecFileInfo = GetMediaDuration(strFileName);   // ��ȡ��Ƶ�ļ���Ϣ
	m_btnDel.EnableWindow(true);
	m_btnEdit.EnableWindow(true);

	*pResult = 0;
}


void CFileCategoryDlg::OnBnClickedButtonEdit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("���δѡ��"));
		return;
	}
	int nSel = listCtrl.GetNextSelectedItem(pos);
	CString FileName = EditDestPath(nSel);
	CString a;
	a.Format("%d", nSel+1);

	listCtrl.SetItemText(nSel, 0, a+_T("���"));
	listCtrl.SetItemText(nSel, 2, FileName);
}

void CFileCategoryDlg::OnIdrToolbarAdd()
{
	// TODO:  �ڴ���������������
	OnBnClickedButtonSource();
}


void CFileCategoryDlg::OnIdrToolbarStart()
{
	// TODO:  �ڴ���������������
	OnBnClickedButtonMove();
}


void CFileCategoryDlg::OnIdrToolbarStop()
{
	// TODO:  �ڴ���������������
	OnBnClickedOk();
}


void CFileCategoryDlg::OnIdrToolbarSettings()
{
	// TODO:  �ڴ���������������
	AfxMessageBox("���������С���");
}



void CFileCategoryDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox(_T("�Ƿ��˳�����"), _T("�Ƿ��˳�����"), MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
		return;

	CDialogEx::OnOK();
}



void CFileCategoryDlg::OnBnClickedButtonAddLoader()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAddNameDlg dlg;
	dlg.m_strDlgCaption = _T("����ϴ���Ա");
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_strName)
		cbUploader.InsertString(0, dlg.m_strName);
		cbUploader.SetCurSel(0);
	}
}


void CFileCategoryDlg::OnBnClickedButtonAddRecorder()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAddNameDlg dlg;
	dlg.m_strDlgCaption = _T("���������Ա");
	if (dlg.DoModal() == IDOK)
	{
		cbRecorder.InsertString(0, dlg.m_strName);
		cbRecorder.SetCurSel(0);
	}
}


void CFileCategoryDlg::OnSelchangeComboMobiledisk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CComboBox *pCb = (CComboBox *)GetDlgItem(IDC_COMBO_MOBILEDISK);
	int nOldSel = pCb->GetCurSel();
	if (IDCANCEL == MessageBox(_T("�˸��Ľ�Ӧ����������ѡ�ļ�"), _T("��ʾ"), MB_OKCANCEL))
	{
		pCb->SetCurSel(nOldSel);
		return;
	}
	int size = vecFileDest.size();
	if (size < 1) return;
	CString OldDisk, tmp, NewDisk;
	pCb->GetLBText(pCb->GetCurSel(), NewDisk);
	for (int i = 0; i < size; i++)
	{
		tmp = vecFileDest.at(i);
		vecFileDest.erase(vecFileDest.begin() + i);
		OldDisk = tmp.Left(tmp.Find('\\')+1);
		tmp.Replace(OldDisk, NewDisk);
		vecFileDest.insert( vecFileDest.begin() + i, tmp);
	}
	UpdateListCtrl();
}

vector<CString> CFileCategoryDlg::GenVec4Txt(vector<CString> vecDest)
{
	vector<CString> vecTxt;

	CString PathName, tmp;
	CString sDt, sPl, sRc(_T("   ")), sFile;

	for (int i = 0; i < vecDest.size(); i++){
		PathName = vecDest.at(i);

		vector<CString> sInfo;
		while (PathName.Find('\\') > 0)
		{
			tmp = PathName.Left(PathName.Find('\\') + 0);//��·���н�ȡ�ļ���;
			sInfo.push_back(tmp);
			tmp = PathName;
			PathName = tmp.Right(tmp.GetLength() - tmp.Find('\\') - 1);
		}
		sDt = sInfo.at(2);
		sPl = sInfo.at(3);
		sRc = sInfo.at(4);    // �������������ּӿո�
		if (sRc.GetLength() < 3)
			sRc.Append(" ");
		sFile = PathName.Right(PathName.GetLength() - PathName.ReverseFind('\\') - 1);//��·���н�ȡ�ļ���;

		vecTxt.push_back(sDt + _T("\t") + sRc + _T("\t") + sPl + _T("\t") + sFile + _T("\n"));
	}

	sDt.ReleaseBuffer();
	sPl.ReleaseBuffer();
	sRc.ReleaseBuffer();
	sFile.ReleaseBuffer();

	return vecTxt;
}
// д��Txt�ļ�
void CFileCategoryDlg::WriteTxt(LPCTSTR lpszFileName, vector<CString> vecTxt)
{
	CStdioFile myFile;
	CFileException fileException;
	if (myFile.Open(lpszFileName,  CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite), &fileException)   // | CFile::modeCreate
	{
		for (int i = 0; i < vecTxt.size(); i++)
		{
			myFile.SeekToEnd();  // ָ�뵽���Ҳ�����������
			myFile.WriteString(vecTxt.at(i));
		}
	}
	else
	{
		TRACE(_T("�޷����ļ� %s,error=%u\n"), lpszFileName, fileException.m_cause);
	}
	myFile.Close();
}
// ��ȡ��ִ���ļ�Ŀ¼
CString GetModuleDir()
{
	HMODULE module = GetModuleHandle(0);
	char pFileName[MAX_PATH];
	GetModuleFileName(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos);
}

/// ��ȡý�岥��ʱ�䳤�ȣ���ʽ00:00:00��
/// </summary>
/// <param name="path">ý��·��</param>
/// <returns>����ʱ�䳤��</returns>
vector<CString> CFileCategoryDlg::GetMediaDuration(CString path)
{
	CoInitialize(NULL);

	Shell32::IShellDispatchPtr ptrShell;
	ptrShell.CreateInstance(__uuidof(Shell32::Shell));
	_variant_t var((short)Shell32::ssfRECENT);
	CString strPath = path.Left(path.ReverseFind('\\'));
	CString strFile = path.Right(path.ReverseFind('\\') + 1);
	Shell32::FolderPtr ptrFolder = ptrShell->NameSpace((LPCSTR)strPath);
	Shell32::FolderItemPtr ptrItem = ptrFolder->ParseName((LPCSTR)strFile);

	vector<CString> vecFileInfo;
	for (int i = 0; i < 10; i++)
	{
		CString strName = ptrFolder->GetDetailsOf(0, i);
		CString strValue = ptrFolder->GetDetailsOf(_variant_t((IDispatch *)ptrItem), i);
		vecFileInfo.push_back(strName);
	}
	ptrItem.Release();
	ptrFolder.Release();
	ptrShell.Release();
	//��������������������������������
	//	��Ȩ����������ΪCSDN������liangls1982����ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
	//ԭ�����ӣ�https ://blog.csdn.net/liangls1982/article/details/6233765
	CoUninitialize();
	return vecFileInfo;

}
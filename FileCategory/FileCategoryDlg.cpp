
// FileCategoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCategory.h"
#include "FileCategoryDlg.h"
#include "afxdialogex.h"
#include "shlwapi.h"

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
}

BEGIN_MESSAGE_MAP(CFileCategoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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
	ON_BN_CLICKED(IDR_TOOLBAR_START, &CFileCategoryDlg::OnIdrToolbarStart)
	ON_BN_CLICKED(IDR_TOOLBAR_STOP, &CFileCategoryDlg::OnIdrToolbarStop)
	ON_BN_CLICKED(IDR_TOOLBAR_SETTINGS, &CFileCategoryDlg::OnIdrToolbarSettings)
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
	edPlace.SetWindowText(_T("����д����"));
	InitMobileDisk();
	InitUploader();
	InitRecorder();
	InitListCtrl();
	InitToolBar();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 20);

	m_bmpSettings.LoadBitmapA(IDB_BITMAP_SETTINGS);
	m_bmpRun.LoadBitmapA(IDB_BITMAP_START);
	m_bmpExit.LoadBitmapA(IDB_BITMAP_STOP);
	m_Imagelist.Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);
	m_Imagelist.Add(&m_bmpSettings, RGB(0,0,0));
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
	case IDB_BITMAP_STOP:
		pTTT->lpszText = _T("�˳�����");
		break;

	case IDB_BITMAP_START:
		pTTT->lpszText = _T("ִ����Ƶ����");
		break;

	case IDR_TOOLBAR_SETTINGS:
		pTTT->lpszText = _T("����");
		break;

	}

	return TRUE;
}

CString CFileCategoryDlg::CheckMobileDisk()
{
	int DSLength = GetLogicalDriveStrings(0, NULL);
	//ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ���ȡ�
	char* DStr = new char[DSLength];//�û�ȡ�ĳ����ڶ�������һ��c�����ַ�������
	GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);
	//ͨ��GetLogicalDriveStrings���ַ�����Ϣ���Ƶ�����������,���б�������������������Ϣ��
	CString a;
	int DType;
	int si = 0;
	for (int i = 0; i < DSLength / 4; ++i)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		char dir[3] = { DStr[si], ':', '\\' };
		DType = GetDriveType((LPTSTR)DStr + i * 4);
		//GetDriveType���������Ի�ȡ���������ͣ�����Ϊ�������ĸ�Ŀ¼
		if (DType == DRIVE_REMOVABLE)
		{
			a = dir;  //  = dir[0];
			return a;
		}
		cbMobileDisk.InsertString(i,a);
		si += 4;
	}
	return _T("δ�����ƶ�Ӳ��");
}

void CFileCategoryDlg::InitMobileDisk()
{
	CString sDisk[5] = { _T("E:\\"), _T("F:\\"), _T("G:\\"), _T("H:\\"), _T("I:\\") };
	for (int i = 0; i < 5; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbMobileDisk.InsertString(i, sDisk[i]);
	}
	cbMobileDisk.SetCurSel(0);
}

void CFileCategoryDlg::InitUploader()
{
	CString sUploader[5] = { _T("����ʦ"), _T("����ʦ"), _T("����ʦ"), _T("����ʦ"), _T("����ʦ") };
	for (int i = 0; i < 5; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbUploader.InsertString(i, sUploader[i]);
	}
	cbUploader.SetCurSel(0);
}

void CFileCategoryDlg::InitRecorder()
{
	CString sRecorder[5] = { _T("��sir"), _T("��sir"), _T("��sir"), _T("��sir"), _T("��sir") };
	for (int i = 0; i < 5; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbRecorder.InsertString(i, sRecorder[i]);
	}
	cbRecorder.SetCurSel(0);
}

void CFileCategoryDlg::InitListCtrl()
{

	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // ����ѡ��������
	listCtrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, 40);   // ��ͷ
	listCtrl.InsertColumn(1, _T("��ѡ�ļ�"), LVCFMT_LEFT, 400);

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
	}
	listCtrl.SetSelectionMark(0);
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

void CFileCategoryDlg::OnBnClickedButtonMove()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int size = vecFileSource.size();
	if (size < 1)
	{
		MessageBox(_T("��ѡ���ļ����༭��Ϣ����ִ�з��ࡣ"), _T("δѡ���κ���Ƶ"), MB_OK);
		return;

	}
	if (MessageBox(_T("����ִ����Ƶ���࣬������Ҫ�����ӡ�"), _T("�Ƿ�ִ����Ƶ���ࣿ"), MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
		return;

	CString src, dest, filename;
	progressCtrl.SetRange(0, size);
	progressCtrl.SetStep(1);
	progressCtrl.SetPos(0);
	progressCtrl.ShowWindow(true);
	for (int i = 0; i < size; i++)
	{
		src = vecFileSource.at(i);
		dest = vecFileDest.at(i);
		filename = src.Right(src.GetLength() - src.ReverseFind('\\') - 1);
		CreateDirectory(dest);
		progressCtrl.SetPos(i+1);
		progressCtrl.SetWindowTextA("���ڿ��� "+ filename);
		CopyFile((LPCSTR)src, (LPCSTR)dest, true);
	}
	AfxMessageBox(_T("��Ƶ�������"));
	progressCtrl.ShowWindow(false);

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
	CFileDialog dlg(TRUE, _T("*.mp4"), NULL, OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, _T("��Ƶ�ļ�(*.mp4;*.avi)|*.mp4|All Files (*.*)|*.*||"), NULL);
	dlg.m_ofn.lpstrTitle = _T("ѡ����Ƶ�ļ�");
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

void CFileCategoryDlg::EditDestPath(int nSel)
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
	sHD.ReleaseBuffer();
	sUp.ReleaseBuffer();
	sDt.ReleaseBuffer();
	sPl.ReleaseBuffer();
	sRc.ReleaseBuffer();
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
	MP4Info(nSel);    // ��ʾ��Ƶ��Ϣ��
	wnpPlayer.put_URL(listCtrl.GetItemText(nSel, 1));

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
	EditDestPath(nSel);

}


void CFileCategoryDlg::OnIdrToolbarStart()
{
	// TODO:  �ڴ���������������
	OnBnClickedButtonMove();
}


void CFileCategoryDlg::OnIdrToolbarStop()
{
	// TODO:  �ڴ���������������
	OnOK();
}


void CFileCategoryDlg::OnIdrToolbarSettings()
{
	// TODO:  �ڴ���������������
	AfxMessageBox("���������С���");
}

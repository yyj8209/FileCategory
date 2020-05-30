
// FileCategoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileCategory.h"
#include "FileCategoryDlg.h"
#include "afxdialogex.h"

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
END_MESSAGE_MAP()


// CFileCategoryDlg �Ի���



CFileCategoryDlg::CFileCategoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileCategoryDlg::IDD, pParent)
	, sPlace(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileCategoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MOBILEDISK, cbMobileDisk);
	DDX_Text(pDX, IDC_EDIT_PLACE, sPlace);
	DDX_Control(pDX, IDC_TREE1, treePath);
	DDX_Control(pDX, IDC_OCX1, wnpPlayer);
	DDX_Control(pDX, IDC_COMBO_RECORDE, cbRecorder);
	DDX_Control(pDX, IDC_COMBO_UPLOADER, cbUploader);
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
END_MESSAGE_MAP()


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
	InitMobileDisk();
	InitUploader();
	InitRecorder();

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
	CString sDisk[5] = { "E:\\", "F:\\", "G:\\", "H:\\", "I:\\"};
	for (int i = 0; i < 5; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbMobileDisk.InsertString(i, sDisk[i]);
	}
	cbMobileDisk.SetCurSel(0);
}

void CFileCategoryDlg::InitUploader()
{
	CString sUploader[5] = { "����ʦ", "����ʦ", "����ʦ", "����ʦ", "����ʦ" };
	for (int i = 0; i < 5; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbUploader.InsertString(i, sUploader[i]);
	}
	cbUploader.SetCurSel(0);
}

void CFileCategoryDlg::InitRecorder()
{
	CString sRecorder[5] = { "��sir", "��sir", "��sir", "��sir", "��sir" };
	for (int i = 0; i < 5; i++)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{
		cbRecorder.InsertString(i, sRecorder[i]);
	}
	cbRecorder.SetCurSel(0);
}



void CFileCategoryDlg::OnBnClickedButtonMove()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
BEGIN_EVENTSINK_MAP(CFileCategoryDlg, CDialogEx)
	ON_EVENT(CFileCategoryDlg, IDC_OCX1, 6505, CFileCategoryDlg::OnClickOcx1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CFileCategoryDlg::OnClickOcx1(short nButton, short nShiftState, long fX, long fY)
{
	// TODO:  �ڴ˴������Ϣ����������
	wnpPlayer.put_URL("F:\\FILM\\������-����ս��.mp4");
}


void CFileCategoryDlg::OnBnClickedButtonSource()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fDlgGetTxt(TRUE);//���ļ��Ի���
	//ֻ��ʾtxt�ļ���ʽ����ʾ����\0 ��������\0 ... �����\0��β
	fDlgGetTxt.m_ofn.lpstrFilter = "�����ļ�(*.*)\0 * .mp4; *.jpg\0"
		"MP4(*.mp4)\0*.mp4\0"
		"JPEG(*.jpg,*.jpeg)\0*.jpg;*.jpeg\0";
	fDlgGetTxt.m_ofn.lpstrTitle = "��txt�ļ�";
	fDlgGetTxt.m_ofn.Flags |= OFN_ALLOWMULTISELECT;//����ѡ�����ļ�

	fDlgGetTxt.m_ofn.nMaxFile = 20 * 101;//�����Դ�20���ļ���ÿ���ļ������ַ���<=100

	//�趨һ���ļ������棬��ΪCFileDialog���õ��ļ������泤��ֻ��200�����Ǻܶ�ʱ��
	//�ļ���·��Զ�����������Ϊ�˱������������Ҫ�Լ��趨һ���ļ�������

	char fileNameBuffer[20 * 101] = { 0 };//��ʼ��Ϊ�㣬����ᷢ���������
	fDlgGetTxt.m_ofn.lpstrFile = fileNameBuffer;//�趨һ���ļ�������

	CStringArray strArrFilePaths;//���ļ�·�����浽CStringArray������

	if (fDlgGetTxt.DoModal() == IDOK)
	{
		POSITION pos = fDlgGetTxt.GetStartPosition();//��ȡ��һ���ļ�����λ��

		while (pos != NULL) //GetNextPathName()���ص�ǰpos���ļ�����������һ���ļ�����λ�ñ��浽pos��
			strArrFilePaths.Add(fDlgGetTxt.GetNextPathName(pos));
	}
	//��������������������������������
	//	��Ȩ����������ΪCSDN��������ӱ���������ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
	//ԭ�����ӣ�https ://blog.csdn.net/qq_25244495/article/details/78405175
}


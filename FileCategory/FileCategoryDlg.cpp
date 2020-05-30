
// FileCategoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCategory.h"
#include "FileCategoryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CFileCategoryDlg 对话框



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


// CFileCategoryDlg 消息处理程序

BOOL CFileCategoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//m_decDriver = CheckMobileDisk();
	InitMobileDisk();
	InitUploader();
	InitRecorder();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileCategoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileCategoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CFileCategoryDlg::CheckMobileDisk()
{
	int DSLength = GetLogicalDriveStrings(0, NULL);
	//通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度。
	char* DStr = new char[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组
	GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);
	//通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。
	CString a;
	int DType;
	int si = 0;
	for (int i = 0; i < DSLength / 4; ++i)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		char dir[3] = { DStr[si], ':', '\\' };
		DType = GetDriveType((LPTSTR)DStr + i * 4);
		//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录
		if (DType == DRIVE_REMOVABLE)
		{
			a = dir;  //  = dir[0];
			return a;
		}
		cbMobileDisk.InsertString(i,a);
		si += 4;
	}
	return _T("未发现移动硬盘");
}

void CFileCategoryDlg::InitMobileDisk()
{
	CString sDisk[5] = { "E:\\", "F:\\", "G:\\", "H:\\", "I:\\"};
	for (int i = 0; i < 5; i++)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		cbMobileDisk.InsertString(i, sDisk[i]);
	}
	cbMobileDisk.SetCurSel(0);
}

void CFileCategoryDlg::InitUploader()
{
	CString sUploader[5] = { "陈老师", "杨老师", "张老师", "朱老师", "江老师" };
	for (int i = 0; i < 5; i++)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		cbUploader.InsertString(i, sUploader[i]);
	}
	cbUploader.SetCurSel(0);
}

void CFileCategoryDlg::InitRecorder()
{
	CString sRecorder[5] = { "陈sir", "杨sir", "张sir", "朱sir", "江sir" };
	for (int i = 0; i < 5; i++)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		cbRecorder.InsertString(i, sRecorder[i]);
	}
	cbRecorder.SetCurSel(0);
}



void CFileCategoryDlg::OnBnClickedButtonMove()
{
	// TODO:  在此添加控件通知处理程序代码

}



void CFileCategoryDlg::OnCbnSelchangeComboUploader()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CFileCategoryDlg::OnChangeEditPlace()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CFileCategoryDlg::OnSelchangeComboRecorde()
{
	// TODO:  在此添加控件通知处理程序代码
}
BEGIN_EVENTSINK_MAP(CFileCategoryDlg, CDialogEx)
	ON_EVENT(CFileCategoryDlg, IDC_OCX1, 6505, CFileCategoryDlg::OnClickOcx1, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CFileCategoryDlg::OnClickOcx1(short nButton, short nShiftState, long fX, long fY)
{
	// TODO:  在此处添加消息处理程序代码
	wnpPlayer.put_URL("F:\\FILM\\爱剪辑-合力战疫.mp4");
}


void CFileCategoryDlg::OnBnClickedButtonSource()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fDlgGetTxt(TRUE);//打开文件对话框
	//只显示txt文件格式：显示内容\0 过滤条件\0 ... 最后以\0结尾
	fDlgGetTxt.m_ofn.lpstrFilter = "所有文件(*.*)\0 * .mp4; *.jpg\0"
		"MP4(*.mp4)\0*.mp4\0"
		"JPEG(*.jpg,*.jpeg)\0*.jpg;*.jpeg\0";
	fDlgGetTxt.m_ofn.lpstrTitle = "打开txt文件";
	fDlgGetTxt.m_ofn.Flags |= OFN_ALLOWMULTISELECT;//允许选择多个文件

	fDlgGetTxt.m_ofn.nMaxFile = 20 * 101;//最多可以打开20个文件，每个文件名的字符数<=100

	//设定一个文件名缓存，因为CFileDialog内置的文件名缓存长度只有200，但是很多时候，
	//文件的路径远大于这个数，为了保险起见，所以要自己设定一个文件名缓存

	char fileNameBuffer[20 * 101] = { 0 };//初始化为零，否则会发生意外错误
	fDlgGetTxt.m_ofn.lpstrFile = fileNameBuffer;//设定一个文件名缓存

	CStringArray strArrFilePaths;//将文件路径保存到CStringArray对象中

	if (fDlgGetTxt.DoModal() == IDOK)
	{
		POSITION pos = fDlgGetTxt.GetStartPosition();//获取第一个文件名的位置

		while (pos != NULL) //GetNextPathName()返回当前pos的文件名，并将下一个文件名的位置保存到pos中
			strArrFilePaths.Add(fDlgGetTxt.GetNextPathName(pos));
	}
	//————————————————
	//	版权声明：本文为CSDN博主「风从北边来」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
	//原文链接：https ://blog.csdn.net/qq_25244495/article/details/78405175
}


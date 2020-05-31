
// FileCategoryDlg.cpp : 实现文件
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
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CFileCategoryDlg::OnItemclickList)
//	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CFileCategoryDlg::OnColumnclickList)
ON_NOTIFY(NM_CLICK, IDC_LIST, &CFileCategoryDlg::OnClickList)
ON_BN_CLICKED(IDC_BUTTON_EDIT, &CFileCategoryDlg::OnBnClickedButtonEdit)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CFileCategoryDlg, CDialogEx)
//	ON_EVENT(CFileCategoryDlg, IDC_OCX, 6505, CFileCategoryDlg::OnClickOcx, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

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
	edPlace.SetWindowText(_T("请填写名称"));
	InitMobileDisk();
	InitUploader();
	InitRecorder();
	InitListCtrl();

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
	CString sDisk[5] = { _T("E:\\"), _T("F:\\"), _T("G:\\"), _T("H:\\"), _T("I:\\") };
	for (int i = 0; i < 5; i++)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		cbMobileDisk.InsertString(i, sDisk[i]);
	}
	cbMobileDisk.SetCurSel(0);
}

void CFileCategoryDlg::InitUploader()
{
	CString sUploader[5] = { _T("陈老师"), _T("杨老师"), _T("张老师"), _T("朱老师"), _T("江老师") };
	for (int i = 0; i < 5; i++)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		cbUploader.InsertString(i, sUploader[i]);
	}
	cbUploader.SetCurSel(0);
}

void CFileCategoryDlg::InitRecorder()
{
	CString sRecorder[5] = { _T("陈sir"), _T("杨sir"), _T("张sir"), _T("朱sir"), _T("江sir") };
	for (int i = 0; i < 5; i++)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{
		cbRecorder.InsertString(i, sRecorder[i]);
	}
	cbRecorder.SetCurSel(0);
}

void CFileCategoryDlg::InitListCtrl()
{

	listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	listCtrl.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 40);   // 表头
	listCtrl.InsertColumn(1, _T("所选文件"), LVCFMT_LEFT, 400);

}

void CFileCategoryDlg::UpdateListCtrl()
{
	listCtrl.DeleteAllItems();
	int size = vecFileSource.size();
	for (int i = 0; i < size; i++)
	{   //的数据
		CString a;
		a.Format(_T("%d"), i + 1);
		listCtrl.InsertItem(i, a);  // 表格内容
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
		dir.Append(destination.Left(destination.Find('\\') + 1));//从路径中截取文件名;
		if (!PathIsDirectory(dir))
		{
			::CreateDirectory(dir, NULL);//创建目录,已有的话不影响
		}
		tmp = destination;
		destination = tmp.Right(tmp.GetLength() - tmp.Find('\\') - 1);
	}


}

void CFileCategoryDlg::OnBnClickedButtonMove()
{
	// TODO:  在此添加控件通知处理程序代码
	int size = vecFileSource.size();
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
		progressCtrl.SetWindowTextA("正在拷贝 "+ filename);
		CopyFile((LPCSTR)src, (LPCSTR)dest, true);
	}
	AfxMessageBox(_T("视频分类完成"));
	progressCtrl.ShowWindow(false);

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


void CFileCategoryDlg::OnBnClickedButtonSource()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("*.mp4"), NULL, OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, _T("视频文件(*.mp4;*.avi)|*.mp4|All Files (*.*)|*.*||"), NULL);
	dlg.m_ofn.lpstrTitle = _T("选择视频文件");
	CString filename;

	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		while (fileNamesPosition != NULL)
		{
			filename = dlg.GetNextPathName(fileNamesPosition);
			vecFileSource.push_back(filename);
			InitDestPath(filename);   // 和源目录大小一致
		}
	}

	UpdateListCtrl();
	/*————————————————
		版权声明：本文为CSDN博主「碧海凌云」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
	原文链接：https ://blog.csdn.net/u012260238/article/details/56489318
	*/

}

vector<CString> CFileCategoryDlg::GenDestPath()
{
	vector<CString> vecPath;
	CString sHD, sUp, sDt, sPl, sRc;
	int i = cbMobileDisk.GetCurSel();//获取索引，0-N
	cbMobileDisk.GetLBText(i, sHD);

	i = cbUploader.GetCurSel();//获取索引，0-N
	cbUploader.GetLBText(i, sUp);

	CTime timeDest;
	dtTime.GetTime(timeDest);
	sDt = timeDest.Format("%Y%m%d");

	edPlace.GetWindowText(sPl);

	i = cbRecorder.GetCurSel();//获取索引，0-N
	cbRecorder.GetLBText(i, sRc);

	vecPath.push_back(sHD);   // 五级目录
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
	sFile = FileName.Right(FileName.GetLength() - FileName.ReverseFind('\\') - 1);//从路径中截取文件名;

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
	sFile = FileName.Right(FileName.GetLength() - FileName.ReverseFind('\\') - 1);//从路径中截取文件名;

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
		tmp = PathName.Left(PathName.Find('\\') + 0);//从路径中截取文件名;
		sInfo.push_back(tmp);
		tmp = PathName;
		PathName = tmp.Right(tmp.GetLength() - tmp.Find('\\') - 1);
	}

	cbUploader.SelectString(0, sInfo.at(1));  // 上传人员；
	edPlace.SetWindowTextA(sInfo.at(3));      // 场所
	cbRecorder.SelectString(0, sInfo.at(4));  // 拍摄人员；

	COleDateTime dt;
	tmp = sInfo.at(2);
//	dt.ParseDateTime("2020/05/01");    //将日期值存到dt中
	dt.ParseDateTime(tmp.Left(4) + "/" + tmp.Mid(4, 2) + "/" + tmp.Right(2));    //将日期值存到dt中
	SYSTEMTIME st;    //定义一个系统时间类型的变量
	dt.GetAsSystemTime(st);    //将dt中的时间按系统时间格式化
	CTime m_Date(st);
	dtTime.SetTime(&m_Date);
}


void CFileCategoryDlg::OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}



void CFileCategoryDlg::OnClickedButtonDel()
{
	// TODO:  在此添加控件通知处理程序代码
	int n = listCtrl.GetSelectionMark();
	listCtrl.DeleteItem(n);
	vecFileSource.erase(vecFileSource.begin() + n);
	vecFileDest.erase(vecFileDest.begin() + n);
	wnpPlayer.close();

	UpdateListCtrl();

}


void CFileCategoryDlg::OnClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	int nSel = listCtrl.GetSelectionMark();
	MP4Info(nSel);    // 显示视频信息。
	wnpPlayer.put_URL(listCtrl.GetItemText(nSel, 1));

	*pResult = 0;
}


void CFileCategoryDlg::OnBnClickedButtonEdit()
{
	// TODO:  在此添加控件通知处理程序代码
	POSITION pos = listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("表格未选中"));
		return;
	}
	int nSel = listCtrl.GetNextSelectedItem(pos);
	EditDestPath(nSel);

}


// weederDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "weeder.h"
#include "weederDlg.h"
#include "afxdialogex.h"
#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CweederDlg 对话框



CweederDlg::CweederDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WEEDER_DIALOG, pParent)
	, m_filepath(_T(""))
	, m_rulefile(false)
	, m_isedit(false)
	, g_isstop(false)
	, m_isrecover(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CweederDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILEPATH, m_filepath);
	DDX_Control(pDX, IDC_TYPELIST, m_filetype);
	DDX_Control(pDX, IDC_EDITRULE, m_editrule);
	DDX_Control(pDX, IDC_EDIT, m_btnedit);
	DDX_Control(pDX, IDC_SAVE, m_saverule);
	DDX_Control(pDX, IDC_BUTTON5, m_btnclear);
	DDX_Control(pDX, IDC_CHECKHIDE, m_noclrhide);
	DDX_Control(pDX, IDC_CHECKUSE, m_noclruse);
}

BEGIN_MESSAGE_MAP(CweederDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, &CweederDlg::OnBnClickedBrowse)
	ON_CBN_SELCHANGE(IDC_TYPELIST, &CweederDlg::OnCbnSelchangeTypelist)
	ON_BN_CLICKED(IDC_SAVE, &CweederDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_EDIT, &CweederDlg::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_RESET, &CweederDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BUTTON5, &CweederDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BTNSTOP, &CweederDlg::OnBnClickedBtnstop)
	ON_BN_CLICKED(IDC_BTNEXIT, &CweederDlg::OnBnClickedBtnexit)
	ON_BN_CLICKED(IDC_ADDRULE, &CweederDlg::OnBnClickedAddrule)
END_MESSAGE_MAP()


// CweederDlg 消息处理程序

BOOL CweederDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	initstr();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CweederDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CweederDlg::OnPaint()
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
HCURSOR CweederDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CweederDlg::OnBnClickedBrowse()
{
	BROWSEINFO DirDialogInfo;
	DirDialogInfo.hwndOwner = NULL;
	DirDialogInfo.iImage = 0;
	DirDialogInfo.lParam = NULL;
	DirDialogInfo.lpfn = NULL;
	DirDialogInfo.lpszTitle = L">>除草者将清理您所选择的文件夹<<  ------------------------------(date:20161012;author: xcyk)-----";
	DirDialogInfo.pidlRoot = NULL;
	DirDialogInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
	DirDialogInfo.pszDisplayName = NULL;

	InitCommonControls();
	LPITEMIDLIST pidl = SHBrowseForFolder(&DirDialogInfo);

	CString filepath = _T("");

	SHGetPathFromIDList(pidl, filepath.GetBuffer(MAX_PATH));
	filepath.ReleaseBuffer();

	if ("" == filepath) return;

	CString folder;//路径后面加'\'
	int index = filepath.ReverseFind('\\');
	if (index != filepath.GetLength() - 1)
		folder.Format(L"%s\\", filepath);
	else
		folder = filepath;
	m_filepath = folder;
	UpdateData(FALSE);

	// TODO: 在此添加控件通知处理程序代码
}



void CweederDlg::initstr()
{
	m_noclrhide.SetCheck(TRUE);
	m_noclruse.SetCheck(TRUE);
	initfiletype();
}


bool CweederDlg::initfiletype()
{
	CStdioFile fp;
	if (!fp.Open(L"rules.dat", CFile::modeRead))//是否有保存的规则文件
	{
		OnBnClickedReset();
	}
	else//有规则文件，则按照文件来
	{
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode 乱码问题
		setlocale(LC_CTYPE, "chs");// 设定
		m_rulefile = TRUE;
		CString buffer_tyep;//读取的类型
		CString buffer_rule;//规则
		CString tyepstr;//解析后的类型
		BOOL noend = false;
		do
		{
			noend = fp.ReadString(buffer_tyep);
			noend = fp.ReadString(buffer_rule);
			if (noend)
			{
				tyepstr = buffer_tyep.Mid(1, buffer_tyep.GetLength() - 2);
				m_filetype.AddString(tyepstr);
				m_rulearray.Add(buffer_rule);
			}
		} while (noend);
		setlocale(LC_CTYPE, old_locale);
		free(old_locale);// 还原区域设定
	}
	fp.Close();
	m_filetype.SetCurSel(0);
	m_editrule.SetWindowTextW(m_rulearray.GetAt(0));
	return false;
}


bool CweederDlg::initrule()
{
	int nIndex = m_filetype.GetCurSel();
	m_editrule.SetWindowTextW(m_rulearray.GetAt(nIndex));

	return true;
}


void CweederDlg::OnCbnSelchangeTypelist()
{
	initrule();
	// TODO: 在此添加控件通知处理程序代码
}


void CweederDlg::OnBnClickedSave()
{
	CStdioFile fp;
	CString rulestr, filetype, writerule;
	m_filetype.GetWindowTextW(filetype);
	m_editrule.GetWindowTextW(rulestr);
	writerule.Format(L"[%s]\n%s\n", filetype, rulestr);
	if (m_rulefile)
	{
		if (!fp.Open(L"rules.dat",CFile::modeWrite | CFile::modeNoTruncate))
		{
			AfxMessageBox(L"打开规则文件失败！");
			return;
		}
		fp.SeekToEnd();
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode 乱码问题
		setlocale(LC_CTYPE, "chs");// 设定

		fp.WriteString(writerule);

		setlocale(LC_CTYPE, old_locale);
		free(old_locale);// 还原区域设定
	}
	else//如果不存规则文件
	{
		if (!fp.Open(L"rules.dat", CFile::modeCreate | CFile::modeWrite))
		{
			AfxMessageBox(L"创建规则文件失败！");
			return;
		}
		m_rulefile = true;
		fp.SeekToEnd();
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode 乱码问题
		setlocale(LC_CTYPE, "chs");// 设定

		fp.WriteString(writerule);

		setlocale(LC_CTYPE, old_locale);
		free(old_locale);// 还原区域设定
	}
	fp.Close();
	AfxMessageBox(L"保存成功！");
	int nIndex = m_filetype.GetCurSel();
	m_rulearray.SetAt(nIndex,rulestr);
	UpdateData(TRUE);
	return;
	// TODO: 在此添加控件通知处理程序代码
}


void CweederDlg::OnBnClickedEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_isedit)
	{
		m_editrule.SetReadOnly(FALSE);
		m_btnedit.SetWindowTextW(L"退出编辑");
		m_isedit = TRUE;
		m_saverule.EnableWindow(FALSE);
	}
	else
	{
		m_editrule.SetReadOnly(TRUE);
		m_btnedit.SetWindowTextW(L"编辑当前规则");
		m_isedit = FALSE;
		m_saverule.EnableWindow(TRUE);
	}
}


void CweederDlg::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isrecover = true;
	m_rulearray.RemoveAll();
	m_filetype.ResetContent();

	m_filetype.AddString(TEMPFILE);
	m_filetype.AddString(TEXTFILE);
	m_filetype.AddString(VIDEOFILE);
	m_filetype.AddString(MUSICFILE);
	m_filetype.AddString(PICFILE);
	m_filetype.AddString(VCFILE);

	m_rulearray.Add(TEMPRULE);
	m_rulearray.Add(TEXTRULE);
	m_rulearray.Add(VIDEORULE);
	m_rulearray.Add(MUSICRULE);
	m_rulearray.Add(PICRULE);
	m_rulearray.Add(VCRULE);

	m_filetype.SetCurSel(0);
	m_editrule.SetWindowTextW(m_rulearray.GetAt(0));

	m_editrule.SetReadOnly(TRUE);//如果当前处于编辑规则状态，则退出
	m_btnedit.SetWindowTextW(L"编辑当前规则");
	m_isedit = FALSE;
	m_saverule.EnableWindow(FALSE);

}


void CweederDlg::OnBnClickedButton5()
{
	CString str;
	GetDlgItem(IDC_EDITRULE)->GetWindowTextW(str);
	if (m_filepath.IsEmpty() || str.IsEmpty())
	{
		AfxMessageBox(L"请检查路径和规则是否填写正确！");
		return;
	}
	ParsingRule();
	g_isstop = FALSE;
	CWinThread* pThread = AfxBeginThread(CweederDlg::CleanerThread, this);
	CloseHandle(pThread->m_hThread);
	AfxMessageBox(L"删除完毕！");
	return;
}


// 清理函数
bool CweederDlg::OnCleaner(const CString path)
{
	BOOL noclrhide = (m_noclrhide.GetCheck() != BST_CHECKED);//是否不清除隐藏文件
	BOOL noclruse = (m_noclruse.GetCheck() != BST_CHECKED);//是否不清除占用文件
	CString  findfile(path);
	findfile += "*.*";
	WIN32_FIND_DATA filedir;
	HANDLE hfind = FindFirstFile(findfile, &filedir);
	if (INVALID_HANDLE_VALUE == hfind)
		return false;
	do
	{
		CString sub;
		if (filedir.cFileName[0] == '.')//忽略"." 和".."
			continue;
		if ((filedir.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && noclrhide)//过滤隐藏文件
			continue;
		//过滤目录
		sub.Format(L"%s%s", path, filedir.cFileName);
		if (filedir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString dirsub;
			dirsub.Format(L"%s%s\\", path, filedir.cFileName);
			OnCleaner(dirsub);
			continue;
		}
		else
		{
			int pos = sub.ReverseFind('.');
			if (pos == -1)
				continue;
			CString ext = sub.Mid(pos);
			if (ext.IsEmpty())
				continue;
			ext.MakeLower();
			for (int i = 0; i < m_rules.GetCount(); i++)
			{
				if (ext == m_rules.GetAt(i))
				{
					if (!(DeleteFile(sub)) && !noclruse)
					{
						MoveFileEx(sub, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
					}
					continue;
				}
			}
		}
	} while (!g_isstop && FindNextFile(hfind, &filedir));
	FindClose(hfind);
	return false;
}

UINT CweederDlg::CleanerThread(LPVOID lParam)
{
	CweederDlg* pthead = (CweederDlg*)lParam;
	pthead->m_btnclear.EnableWindow(FALSE);
	pthead->m_btnclear.SetWindowTextW(L"清除中...");

	pthead->OnCleaner(pthead->m_filepath);

	pthead->m_btnclear.SetWindowTextW(L"清除");
	pthead->m_btnclear.EnableWindow(TRUE);
	return 1;
}

// 用来解析规则
bool CweederDlg::ParsingRule()
{
	CString rulestr;
	const CString sep(";");

	m_editrule.GetWindowTextW(rulestr);
	rulestr.Trim();//去除里面的空格
	if (rulestr.IsEmpty())
		return FALSE;

	int pos = rulestr.Find(sep);
	while (pos != -1)
	{
		if (!rulestr.Left(pos).IsEmpty()) // Trim后再判断是否为空，为空则舍弃 防止";;"
		{
			m_rules.Add(rulestr.Left(pos));
			rulestr = rulestr.Mid(pos + sep.GetLength());
		}
		pos = rulestr.Find(sep);
	}
	m_rules.Add(rulestr);
	return TRUE;
}



void CweederDlg::OnBnClickedBtnstop()
{
	g_isstop = TRUE;
}


void CweederDlg::OnBnClickedBtnexit()
{
	OnBnClickedBtnstop();
	CweederDlg::OnOK();
}


void CweederDlg::OnBnClickedAddrule()
{
	if (m_addnew.DoModal() == IDOK)
	{
		Addnewrule();
	}
	return;
}


void CweederDlg::Addnewrule()
{
	m_filetype.AddString(m_addnew.addruletype);
	m_rulearray.Add(m_addnew.addrule);
	UpdateData(TRUE);
}

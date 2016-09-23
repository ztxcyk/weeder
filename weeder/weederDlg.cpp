
// weederDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "weeder.h"
#include "weederDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CweederDlg �Ի���



CweederDlg::CweederDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WEEDER_DIALOG, pParent)
	, m_filepath(_T(""))
	, m_rulefile(false)
	, m_isedit(false)
	, g_isstop(false)
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
END_MESSAGE_MAP()


// CweederDlg ��Ϣ�������

BOOL CweederDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	initstr();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CweederDlg::OnPaint()
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
	DirDialogInfo.lpszTitle= L">>�����߽���������ѡ����ļ���<<";
	DirDialogInfo.pidlRoot = NULL;
	DirDialogInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS ;
	DirDialogInfo.pszDisplayName = NULL;

	InitCommonControls();
	LPITEMIDLIST pidl = SHBrowseForFolder(&DirDialogInfo);

	CString filepath = _T("");

	SHGetPathFromIDList(pidl, filepath.GetBuffer(MAX_PATH));
	filepath.ReleaseBuffer();

	if ("" == filepath) return;

	CString folder;//·�������'\'
	int index = filepath.ReverseFind('\\');
	if (index != filepath.GetLength() - 1)
		folder.Format(L"%s\\", filepath);
	else
		folder = filepath;
	m_filepath = folder;
	UpdateData(FALSE);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void CweederDlg::initstr()
{
	initfiletype();
}


bool CweederDlg::initfiletype()
{
	CFile fp;
	CFileException e;
	if (!fp.Open(L"rules.dat", CFile::modeRead, &e))//�Ƿ��б���Ĺ����ļ�
	{
		OnBnClickedReset();
	}
	else//�й����ļ��������ļ���
	{
		//m_rulefile = TRUE;
		OnBnClickedReset();//�����ã�֮��ɾ��
		
	}

	return false;
}


bool CweederDlg::initrule()
{
	//��ȡѡ����ļ�����
	CString filetype;
	int nIndex = m_filetype.GetCurSel();
	//m_filetype.GetLBText(nIndex, filetype);

	if (m_rulefile)//���ڹ����ļ�
	{

	}
	else
	{
		switch (nIndex)
		{
		case 0:
			m_editrule.SetWindowTextW(TEMPRULE);
			break;
		case 1:
			m_editrule.SetWindowTextW(TEXTRULE);
			break;
		case 2:
			m_editrule.SetWindowTextW(VIDEORULE);
			break;
		case 3:
			m_editrule.SetWindowTextW(MUSICRULE);
			break;
		case 4:
			m_editrule.SetWindowTextW(PICRULE);
			break;
		case 5:
			m_editrule.SetWindowTextW(VCRULE);
			break;
		default:
			break;
		}
	}

	return false;
}


void CweederDlg::OnCbnSelchangeTypelist()
{
	initrule();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CweederDlg::OnBnClickedSave()
{
	if (m_rulefile)
	{

	}
	else//�����������ļ�����Ĭ�Ϲ���д��
	{
		CFile fp;
		if (!fp.Open(L"rules.dat", CFile::modeCreate | CFile::modeWrite))
		{
			AfxMessageBox(L"���������ļ�ʧ�ܣ�");
			return;
		}
		CString rulestr, filetype;
		for (int index = 0; index < 5; ++index)
		{
	//		fp.SeekToEnd();
			m_filetype.GetLBText(index, filetype);//���� ��������
			//rulestr.Format(L"[%s]//r//n",filetype);
			AfxMessageBox(filetype);
		//	fp.Write((LPCTSTR)filetype, filetype.GetLength());
		}
		fp.Close();
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CweederDlg::OnBnClickedEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_isedit)
	{
		m_editrule.SetReadOnly(FALSE);
		m_btnedit.SetWindowTextW(L"�˳��༭");
		m_isedit = TRUE;
		m_saverule.EnableWindow(FALSE);
	}
	else
	{
		m_editrule.SetReadOnly(TRUE);
		m_btnedit.SetWindowTextW(L"�༭��ǰ����");
		m_isedit = FALSE;
		m_saverule.EnableWindow(TRUE);
	}
}


void CweederDlg::OnBnClickedReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_filetype.ResetContent();
	m_filetype.AddString(TEMPFILE);
	m_filetype.AddString(TEXTFILE);
	m_filetype.AddString(VIDEOFILE);
	m_filetype.AddString(MUSICFILE);
	m_filetype.AddString(PICFILE);
	m_filetype.AddString(VCFILE);
	m_filetype.SetCurSel(0);
	m_editrule.SetWindowTextW(TEMPRULE);

	m_editrule.SetReadOnly(TRUE);//�����ǰ���ڱ༭����״̬�����˳�
	m_btnedit.SetWindowTextW(L"�༭��ǰ����");
	m_isedit = FALSE;
	m_saverule.EnableWindow(FALSE);

}


void CweederDlg::OnBnClickedButton5()
{
	CString str;
	GetDlgItem(IDC_EDITRULE)->GetWindowTextW(str);
	if (m_filepath.IsEmpty() || str.IsEmpty())
	{
		AfxMessageBox(L"����·���͹����Ƿ���д��ȷ��");
	}
	ParsingRule();
	g_isstop = FALSE;
	CWinThread* pThread = AfxBeginThread(CweederDlg::CleanerThread, this);
	CloseHandle(pThread->m_hThread);
}


// ������
bool CweederDlg::OnCleaner(const CString path)
{
	CString  findfile(path);
	findfile += "*.*";
	WIN32_FIND_DATA filedir;
	HANDLE hfind = FindFirstFile(findfile, &filedir);
	if (INVALID_HANDLE_VALUE == hfind)
		return false;
	do
	{
		CString sub;
		if (filedir.cFileName[0] == '.')//����"." ��".."
			continue;
		//����Ŀ¼
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
					DeleteFile(sub);
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
	pthead->m_btnclear.SetWindowTextW(L"�����...");

	pthead->OnCleaner(pthead->m_filepath);

	pthead->m_btnclear.SetWindowTextW(L"���");
	pthead->m_btnclear.EnableWindow(TRUE);
	return 1;
}

// ������������
bool CweederDlg::ParsingRule()
{
	CString rulestr;
	const CString sep(";");
	//int len = m_editrule.LineLength();//xcyk  ����ֻ�ܻ�ȡ��һ��
	//m_editrule.GetLine(0, rulestr.GetBuffer(len), len);
	//rulestr.ReleaseBuffer(len);
	//20160923 xcyk  ���Ի�ȡm_editrule��ȫ���ı�
	m_editrule.GetWindowTextW(rulestr);
	rulestr.Trim();//ȥ������Ŀո�
	if (rulestr.IsEmpty())
		return FALSE;

	int pos = rulestr.Find(sep);
	while (pos != -1)
	{
		if (!rulestr.Left(pos).IsEmpty()) // Trim�����ж��Ƿ�Ϊ�գ�Ϊ�������� ��ֹ";;"
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

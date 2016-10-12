
// weederDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "weeder.h"
#include "weederDlg.h"
#include "afxdialogex.h"
#include <locale>

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
	DirDialogInfo.lpszTitle = L">>�����߽���������ѡ����ļ���<<  ------------------------------(date:20161012;author: xcyk)-----";
	DirDialogInfo.pidlRoot = NULL;
	DirDialogInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
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
	m_noclrhide.SetCheck(TRUE);
	m_noclruse.SetCheck(TRUE);
	initfiletype();
}


bool CweederDlg::initfiletype()
{
	CStdioFile fp;
	if (!fp.Open(L"rules.dat", CFile::modeRead))//�Ƿ��б���Ĺ����ļ�
	{
		OnBnClickedReset();
	}
	else//�й����ļ��������ļ���
	{
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode ��������
		setlocale(LC_CTYPE, "chs");// �趨
		m_rulefile = TRUE;
		CString buffer_tyep;//��ȡ������
		CString buffer_rule;//����
		CString tyepstr;//�����������
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
		free(old_locale);// ��ԭ�����趨
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			AfxMessageBox(L"�򿪹����ļ�ʧ�ܣ�");
			return;
		}
		fp.SeekToEnd();
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode ��������
		setlocale(LC_CTYPE, "chs");// �趨

		fp.WriteString(writerule);

		setlocale(LC_CTYPE, old_locale);
		free(old_locale);// ��ԭ�����趨
	}
	else//�����������ļ�
	{
		if (!fp.Open(L"rules.dat", CFile::modeCreate | CFile::modeWrite))
		{
			AfxMessageBox(L"���������ļ�ʧ�ܣ�");
			return;
		}
		m_rulefile = true;
		fp.SeekToEnd();
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode ��������
		setlocale(LC_CTYPE, "chs");// �趨

		fp.WriteString(writerule);

		setlocale(LC_CTYPE, old_locale);
		free(old_locale);// ��ԭ�����趨
	}
	fp.Close();
	AfxMessageBox(L"����ɹ���");
	int nIndex = m_filetype.GetCurSel();
	m_rulearray.SetAt(nIndex,rulestr);
	UpdateData(TRUE);
	return;
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
		return;
	}
	ParsingRule();
	g_isstop = FALSE;
	CWinThread* pThread = AfxBeginThread(CweederDlg::CleanerThread, this);
	CloseHandle(pThread->m_hThread);
	AfxMessageBox(L"ɾ����ϣ�");
	return;
}


// ������
bool CweederDlg::OnCleaner(const CString path)
{
	BOOL noclrhide = (m_noclrhide.GetCheck() != BST_CHECKED);//�Ƿ���������ļ�
	BOOL noclruse = (m_noclruse.GetCheck() != BST_CHECKED);//�Ƿ����ռ���ļ�
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
		if ((filedir.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && noclrhide)//���������ļ�
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

// Addrule.cpp : 实现文件
//

#include "stdafx.h"
#include "weeder.h"
#include "Addrule.h"
#include "afxdialogex.h"
#include <locale>

// Addrule 对话框

IMPLEMENT_DYNAMIC(Addrule, CDialogEx)

Addrule::Addrule(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADDRULE, pParent)
	, addruletype(_T(""))
	, addrule(_T(""))
{

}

Addrule::~Addrule()
{
}

void Addrule::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDTYPE, m_addtype);
	DDX_Control(pDX, IDC_ADDRULE, m_addrule);
}


BEGIN_MESSAGE_MAP(Addrule, CDialogEx)
	ON_BN_CLICKED(IDOK, &Addrule::OnBnClickedOk)
END_MESSAGE_MAP()


// Addrule 消息处理程序


void Addrule::OnBnClickedOk()
{
	m_addtype.GetWindowTextW(addruletype);
	m_addrule.GetWindowTextW(addrule);
	if (addruletype.IsEmpty() || addrule.IsEmpty())
	{
		AfxMessageBox(L"请检查规则名和规则是否填写正确！");
		return;
	}
	CStdioFile fp;
	if (!fp.Open(L"rules.dat", CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		AfxMessageBox(L"读取规则文件失败！");
		return;
	}
	fp.SeekToEnd();
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode 乱码问题
	setlocale(LC_CTYPE, "chs");// 设定

	CString writerule;

	writerule.Format(L"[%s]\n%s\n", addruletype, addrule);
	fp.WriteString(writerule);

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);// 还原区域设定
	fp.Close();
	AfxMessageBox(L"新建规则成功！");
	CDialogEx::OnOK();
}

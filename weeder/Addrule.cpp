// Addrule.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "weeder.h"
#include "Addrule.h"
#include "afxdialogex.h"
#include <locale>

// Addrule �Ի���

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


// Addrule ��Ϣ�������


void Addrule::OnBnClickedOk()
{
	m_addtype.GetWindowTextW(addruletype);
	m_addrule.GetWindowTextW(addrule);
	if (addruletype.IsEmpty() || addrule.IsEmpty())
	{
		AfxMessageBox(L"����������͹����Ƿ���д��ȷ��");
		return;
	}
	CStdioFile fp;
	if (!fp.Open(L"rules.dat", CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		AfxMessageBox(L"��ȡ�����ļ�ʧ�ܣ�");
		return;
	}
	fp.SeekToEnd();
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));//unicode ��������
	setlocale(LC_CTYPE, "chs");// �趨

	CString writerule;

	writerule.Format(L"[%s]\n%s\n", addruletype, addrule);
	fp.WriteString(writerule);

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);// ��ԭ�����趨
	fp.Close();
	AfxMessageBox(L"�½�����ɹ���");
	CDialogEx::OnOK();
}

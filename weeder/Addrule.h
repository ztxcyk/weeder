#pragma once
#include "afxwin.h"


// Addrule �Ի���

class Addrule : public CDialogEx
{
	DECLARE_DYNAMIC(Addrule)

public:
	Addrule(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Addrule();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDRULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_addtype;
	CEdit m_addrule;
	CString addruletype;
	CString addrule;
};

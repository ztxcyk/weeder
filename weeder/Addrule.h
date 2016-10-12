#pragma once
#include "afxwin.h"


// Addrule 对话框

class Addrule : public CDialogEx
{
	DECLARE_DYNAMIC(Addrule)

public:
	Addrule(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Addrule();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDRULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_addtype;
	CEdit m_addrule;
	CString addruletype;
	CString addrule;
};

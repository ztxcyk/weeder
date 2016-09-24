
// weederDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcoll.h"

#define TEMPFILE   L"临时文件"
#define TEXTFILE   L"文本文件"
#define VIDEOFILE  L"视频文件" 
#define MUSICFILE  L"音频文件"
#define PICFILE    L"图片文件"
#define VCFILE     L"VC垃圾文件"

#define TEMPRULE   L".tmp;._mp;.log;.gid;.chk;.old;.bak"
#define TEXTRULE   L".txt;.pdf;.chm;.pdg;.wdl;.doc;.docx;.xml;.html;.c;.cpp;.h;.java;.class"
#define VIDEORULE  L".avi;.wma;.rmvb;.rm;.flash;.mp4;.mid;.3gp" 
#define MUSICRULE  L".cda;.wav;.mp3;.wma;.ra;.midi;.ogg;.ape;.flac;.aac"
#define PICRULE    L".tiff;.psd;.png;.swf;.pcx;.wmf;.emf;.lic;.eps;.tga;.bmp;.jpeg;.jpg;.gif"
#define VCRULE     L".pdb;.ncb;.suo;.obj;.htm;.idb;.bsr;.pch;.exp;.dep;.aps;.db;.tlog"

// CweederDlg 对话框
class CweederDlg : public CDialogEx
{
// 构造
public:
	CweederDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEEDER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBrowse();
	// 绝对路径
	CString m_filepath;
	void initstr();
	bool initfiletype();
	// 保存删除文件类型的变量
	CComboBox m_filetype;
	bool initrule();
public:
	CEdit m_editrule;
	afx_msg void OnCbnSelchangeTypelist();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedEdit();
	// 编辑当前规则
	CButton m_btnedit;
private:
	// 是否存在规则文件
	bool m_rulefile;
	// 是否处于编辑规则状态
	bool m_isedit;
public:
	CButton m_saverule;
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedButton5();
	// 清理函数
	bool OnCleaner(const CString path);
	static UINT  CleanerThread(LPVOID lParam);
private:
	// 用来保存规则的数组
	CStringArray m_rules;
public:
	// 用来解析规则
	bool ParsingRule();
private:
	// 是否停止清理
	bool g_isstop;
public:
	afx_msg void OnBnClickedBtnstop();
	// 清理的控件变量
	CButton m_btnclear;
	afx_msg void OnBnClickedBtnexit();
	afx_msg void OnBnClickedAddrule();
	CButton m_noclrhide;
	CButton m_noclruse;
};

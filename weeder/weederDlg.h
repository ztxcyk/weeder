
// weederDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcoll.h"

#define TEMPFILE   L"��ʱ�ļ�"
#define TEXTFILE   L"�ı��ļ�"
#define VIDEOFILE  L"��Ƶ�ļ�" 
#define MUSICFILE  L"��Ƶ�ļ�"
#define PICFILE    L"ͼƬ�ļ�"
#define VCFILE     L"VC�����ļ�"

#define TEMPRULE   L".tmp;._mp;.log;.gid;.chk;.old;.bak"
#define TEXTRULE   L".txt;.pdf;.chm;.pdg;.wdl;.doc;.docx;.xml;.html;.c;.cpp;.h;.java;.class"
#define VIDEORULE  L".avi;.wma;.rmvb;.rm;.flash;.mp4;.mid;.3gp" 
#define MUSICRULE  L".cda;.wav;.mp3;.wma;.ra;.midi;.ogg;.ape;.flac;.aac"
#define PICRULE    L".tiff;.psd;.png;.swf;.pcx;.wmf;.emf;.lic;.eps;.tga;.bmp;.jpeg;.jpg;.gif"
#define VCRULE     L".pdb;.ncb;.suo;.obj;.htm;.idb;.bsr;.pch;.exp;.dep;.aps;.db;.tlog"

// CweederDlg �Ի���
class CweederDlg : public CDialogEx
{
// ����
public:
	CweederDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEEDER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBrowse();
	// ����·��
	CString m_filepath;
	void initstr();
	bool initfiletype();
	// ����ɾ���ļ����͵ı���
	CComboBox m_filetype;
	bool initrule();
public:
	CEdit m_editrule;
	afx_msg void OnCbnSelchangeTypelist();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedEdit();
	// �༭��ǰ����
	CButton m_btnedit;
private:
	// �Ƿ���ڹ����ļ�
	bool m_rulefile;
	// �Ƿ��ڱ༭����״̬
	bool m_isedit;
public:
	CButton m_saverule;
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedButton5();
	// ������
	bool OnCleaner(const CString path);
	static UINT  CleanerThread(LPVOID lParam);
private:
	// ����������������
	CStringArray m_rules;
public:
	// ������������
	bool ParsingRule();
private:
	// �Ƿ�ֹͣ����
	bool g_isstop;
public:
	afx_msg void OnBnClickedBtnstop();
	// ����Ŀؼ�����
	CButton m_btnclear;
	afx_msg void OnBnClickedBtnexit();
	afx_msg void OnBnClickedAddrule();
	CButton m_noclrhide;
	CButton m_noclruse;
};

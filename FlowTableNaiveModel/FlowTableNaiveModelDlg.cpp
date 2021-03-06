
// FlowTableNaiveModelDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FlowTableNaiveModel.h"
#include "FlowTableNaiveModelDlg.h"
#include "afxdialogex.h"
#include <thread>

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


// CFlowTableNaiveModelDlg 对话框



CFlowTableNaiveModelDlg::CFlowTableNaiveModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FLOWTABLENAIVEMODEL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFlowTableNaiveModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFlowTableNaiveModelDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFlowTableNaiveModelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_FILE_SELECTOR, &CFlowTableNaiveModelDlg::OnBnClickedFileSelector)
	ON_BN_CLICKED(IDC_RESULT_SAVE, &CFlowTableNaiveModelDlg::OnBnClickedResultSave)
END_MESSAGE_MAP()


// CFlowTableNaiveModelDlg 消息处理程序

BOOL CFlowTableNaiveModelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	//设置默认参数
	CEdit * hashLenEdit = (CEdit *)GetDlgItem(IDC_HASH_LEN);
	hashLenEdit->SetWindowTextW(_T("9"));

	CEdit * cbfCountersLen = (CEdit *)GetDlgItem(IDC_CBF_COUNTERS_LEN);
	cbfCountersLen->SetWindowTextW(_T("14"));

	CEdit * scbfCountersLen = (CEdit *)GetDlgItem(IDC_SCBF_COUNTRES_INIT_LEN);
	scbfCountersLen->SetWindowTextW(_T("14"));

	CEdit * scbfInitCapacity = (CEdit *)GetDlgItem(IDC_SCBF_INIT_CAPACITY);
	scbfInitCapacity->SetWindowTextW(_T("2048"));

	CEdit * benignPktNum = (CEdit *)GetDlgItem(IDC_BENIGN_PKT_NUM);
	benignPktNum->SetWindowTextW(_T("2"));

	CEdit * attackPktNum = (CEdit *)GetDlgItem(IDC_ATTACK_PKT_NUM);
	attackPktNum->SetWindowTextW(_T("1"));

	CEdit * attackStartTime = (CEdit *)GetDlgItem(IDC_ATTACK_START_TIME);
	attackStartTime->SetWindowTextW(_T("30"));

	CEdit * attackEndTime = (CEdit *)GetDlgItem(IDC_ATTACK_END_TIME);
	attackEndTime->SetWindowTextW(_T("70"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFlowTableNaiveModelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFlowTableNaiveModelDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFlowTableNaiveModelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFlowTableNaiveModelDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_configInfo.fileList.empty())
	{
		CString msg("您还没有选择数据源文件！");
		AfxMessageBox(msg);
		return;
	}
	if (m_configInfo.resultPath.GetLength() == 0) {
		CString msg("您还没有选择结果保存目录！");
		AfxMessageBox(msg);
		return;
	}

	CString m_strHashLenStr;
	GetDlgItem(IDC_HASH_LEN)->GetWindowTextW(m_strHashLenStr);
	CStringA m_strHashLen(m_strHashLenStr);
	UINT uiHashLen = atoi(m_strHashLen);

	CString m_CbfCountersLenStr;
	GetDlgItem(IDC_CBF_COUNTERS_LEN)->GetWindowTextW(m_CbfCountersLenStr);
	CStringA m_strCbfCountersLen(m_CbfCountersLenStr);
	ULONG cbfCountersLen = atoi(m_strCbfCountersLen);

	CString m_ScbfCountersLenStr;
	GetDlgItem(IDC_SCBF_COUNTRES_INIT_LEN)->GetWindowTextW(m_ScbfCountersLenStr);
	CStringA m_strScbfCountersLen(m_ScbfCountersLenStr);
	ULONG scbfCountersLen = atoi(m_strScbfCountersLen);

	CString m_ScbfInitCapacityStr;
	GetDlgItem(IDC_SCBF_INIT_CAPACITY)->GetWindowTextW(m_ScbfInitCapacityStr);
	CStringA m_strScbfInitCapacity(m_ScbfInitCapacityStr);
	ULONG scbfInitCapacity = atoi(m_strScbfInitCapacity);

	CString m_attackPktNumStr;
	GetDlgItem(IDC_ATTACK_PKT_NUM)->GetWindowTextW(m_attackPktNumStr);
	CStringA m_attackPktNum(m_attackPktNumStr);
	ULONG attackPktNum = atoi(m_attackPktNum);

	CString m_benignPktNumStr;
	GetDlgItem(IDC_BENIGN_PKT_NUM)->GetWindowTextW(m_benignPktNumStr);
	CStringA m_benginPktNum(m_benignPktNumStr);
	ULONG benginPktNum = atoi(m_benginPktNum);

	CString m_attackStartTimeStr;
	GetDlgItem(IDC_ATTACK_START_TIME)->GetWindowTextW(m_attackStartTimeStr);
	CStringA m_strAttackStartTime(m_attackStartTimeStr);
	ULONG attackStartTime = atoi(m_strAttackStartTime);

	CString m_attackEndTimeStr;
	GetDlgItem(IDC_ATTACK_END_TIME)->GetWindowTextW(m_attackEndTimeStr);
	CStringA m_strAttackEndTime(m_attackEndTimeStr);
	ULONG attackEndTime = atoi(m_strAttackEndTime);

	if (uiHashLen<1 || uiHashLen>16)
	{
		CString msg("输入的数据超出范围(0-16)!");
		AfxMessageBox(msg);
		return;
	}

	m_configInfo.uiHashLen = (UINT)pow(2, uiHashLen);
	m_configInfo.cbfCountersLen = cbfCountersLen;
	m_configInfo.scbfCountersLen = scbfCountersLen;
	m_configInfo.scbfInitCapacity = scbfInitCapacity;
	m_configInfo.attackPktNum = attackPktNum;
	m_configInfo.benignPktNum = benginPktNum;
	m_configInfo.attackStartTime = attackStartTime;
	m_configInfo.attackEndTime = attackEndTime;

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	PacketLookup manager(m_configInfo);
	manager.LookupTestProc(m_configInfo);

	CString msg("虚拟流表查找测试完毕！");
	AfxMessageBox(msg);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CFlowTableNaiveModelDlg::OnBnClickedFileSelector()
{
	CString strFile = _T("");
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT;
	CFileDialog dlgFile(TRUE, _T("cap"), NULL, dwFlags, _T("Ip trace(*.hsn)|*.hsn||"), NULL);
	if (dlgFile.DoModal() != IDOK)
	{
		return;
	}
	
	POSITION pos = dlgFile.GetStartPosition();
	while(NULL != pos) {
		CString strFileName = dlgFile.GetNextPathName(pos);
		m_configInfo.fileList.push_back(strFileName);

		CString oldMessage;
		GetDlgItem(IDC_MESSAGE_AREA)->GetWindowTextW(oldMessage);
		GetDlgItem(IDC_MESSAGE_AREA)->SetWindowTextW(oldMessage + strFileName + "\r\n");
	}
}

void CFlowTableNaiveModelDlg::OnBnClickedResultSave()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("选择需要保存的路径");
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl) {
		return;
	}
	SHGetPathFromIDList(idl, szBuffer);
	m_configInfo.resultPath = szBuffer;
}

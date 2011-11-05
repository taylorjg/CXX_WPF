#include "stdafx.h"
#include "WineDemo.h"
#include "WineDemoDlg.h"
#include "WineListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg ();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange (CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP ()
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
//* Function Name: Constructor
//*   Description: 
//*****************************************************************************
CAboutDlg::CAboutDlg () : CDialog (CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}


//*****************************************************************************
//* Function Name: DoDataExchange
//*   Description: 
//*****************************************************************************
void CAboutDlg::DoDataExchange (CDataExchange* pDX)
{
	CDialog::DoDataExchange (pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWineDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CWineDemoDlg)
	ON_WM_SYSCOMMAND ()
	ON_WM_PAINT ()
	ON_WM_SIZE ()
	ON_WM_NCHITTEST ()
	ON_WM_QUERYDRAGICON ()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
//* Function Name: Constructor
//*   Description: 
//*****************************************************************************
CWineDemoDlg::CWineDemoDlg (CWnd* pParent /*=NULL*/) :
	CDialog(CWineDemoDlg::IDD, pParent),
	m_pWineListCtrl (NULL)
{
	//{{AFX_DATA_INIT(CWineDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon16 = AfxGetApp ()->LoadIcon (IDI_DATAFEEDS_16);
	m_hIcon32 = AfxGetApp ()->LoadIcon (IDI_DATAFEEDS_32);
}


//*****************************************************************************
//* Function Name: Destructor
//*   Description: 
//*****************************************************************************
CWineDemoDlg::~CWineDemoDlg ()
{
	delete m_pWineListCtrl;
}


//*****************************************************************************
//* Function Name: DoDataExchange
//*   Description: 
//*****************************************************************************
void CWineDemoDlg::DoDataExchange (CDataExchange* pDX)
{
	CDialog::DoDataExchange (pDX);

	//{{AFX_DATA_MAP(CWineDemoDlg)
	DDX_Control (pDX, IDC_SEPARATOR, m_lblSeparator);
	DDX_Control (pDX, IDOK, m_btnOK);
	DDX_Control (pDX, IDCANCEL, m_btnCancel);
	//}}AFX_DATA_MAP
}


//*****************************************************************************
//* Function Name: OnInitDialog
//*   Description: 
//*****************************************************************************
BOOL CWineDemoDlg::OnInitDialog ()
{
	CDialog::OnInitDialog ();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT ((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT (IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu (FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString (IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty ())
		{
			pSysMenu->AppendMenu (MF_SEPARATOR);
			pSysMenu->AppendMenu (MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon (m_hIcon16, FALSE);		// Set small icon
	SetIcon (m_hIcon32, TRUE);		// Set big icon
	
	CWnd* l_pwndPlaceHolder = GetDlgItem (IDC_WINELISTPLACEHOLDER);
	CRect l_rcPlaceHolder;
	l_pwndPlaceHolder->GetWindowRect (l_rcPlaceHolder);
	ScreenToClient (l_rcPlaceHolder);
	l_pwndPlaceHolder->ShowWindow (SW_HIDE);
	l_pwndPlaceHolder->EnableWindow (FALSE);

	m_pWineListCtrl = new CWineListCtrl ();
	m_pWineListCtrl->Create (
		LBS_OWNERDRAWVARIABLE |
		LBS_NOINTEGRALHEIGHT | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP,
		l_rcPlaceHolder,
		this,
		IDC_WINELIST);
	m_pWineListCtrl->SetFont (GetFont ());

	m_pWineListCtrl->GetWindowRect (m_rcWineListCtrl);
	m_lblSeparator.GetWindowRect (m_rcSeparator);
	m_btnOK.GetWindowRect (m_rcOK);
	m_btnCancel.GetWindowRect (m_rcCancel);

	// Convert all the window rects from screen co-ordinates to client co-ordinates.
	ScreenToClient (m_rcWineListCtrl);
	ScreenToClient (m_rcSeparator);
	ScreenToClient (m_rcOK);
	ScreenToClient (m_rcCancel);

	CRect l_rcDialog;
	GetClientRect (l_rcDialog);
	m_cx = l_rcDialog.Width ();
	m_cy = l_rcDialog.Height ();

	CWineServiceContext l_WineServiceContext ("http://wine.cloudapp.net");

	ProductDataServiceQueryPtr l_pProductQuery (l_WineServiceContext.GetProducts ());
	l_pProductQuery->AddQueryOption ("apikey", API_KEY);
	l_pProductQuery->AddQueryOption ("$orderby", "PriceRetail desc");
	l_pProductQuery->AddQueryOption ("$top", "20");

	CEntityCollection<CProduct>::type l_pProducts = l_pProductQuery->Execute ();

	std::vector<boost::shared_ptr<CProduct> >::iterator it;

	for (it = l_pProducts->begin (); it != l_pProducts->end (); it++) {

		CItemData* l_pItemData = new CItemData (*it);

		CString l_strItem;
		l_strItem.Format (
			_T("%s ($%6.2f)"),
			l_pItemData->GetProduct ()->GetName (),
			l_pItemData->GetProduct ()->GetPriceRetail ());

		INT l_nIndex = m_pWineListCtrl->AddString (l_strItem);
		m_pWineListCtrl->SetItemData (l_nIndex, reinterpret_cast<DWORD>(l_pItemData));
	}

	// Displaying a JPG in your MFC Application
	// http://msdn.microsoft.com/en-us/magazine/cc301454.aspx

	return TRUE;  // return TRUE  unless you set the focus to a control
}


//*****************************************************************************
//* Function Name: OnSysCommand
//*   Description: 
//*****************************************************************************
void CWineDemoDlg::OnSysCommand (UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal ();
	}
	else
	{
		CDialog::OnSysCommand (nID, lParam);
	}
}


//*****************************************************************************
//* Function Name: OnPaint
//*   Description: If you add a minimize button to your dialog, you will need
//*                the code below to draw the icon.  For MFC applications using
//*                the document/view model, this is automatically done for you
//*                by the framework.
//*****************************************************************************
void CWineDemoDlg::OnPaint () 
{
	if (IsIconic ())
	{
		CPaintDC dc (this); // device context for painting

		SendMessage (WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc (), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics (SM_CXICON);
		int cyIcon = GetSystemMetrics (SM_CYICON);
		CRect rect;
		GetClientRect (&rect);
		int x = (rect.Width () - cxIcon + 1) / 2;
		int y = (rect.Height () - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon (x, y, m_hIcon16);
	}
	else
	{
		// Calculate the position of the size grip.
		GetClientRect (m_rcGripper);
		m_rcGripper.left = m_rcGripper.right - ::GetSystemMetrics (SM_CXVSCROLL);
		m_rcGripper.top = m_rcGripper.bottom - ::GetSystemMetrics (SM_CYHSCROLL);

		// Draw the grip.
		CPaintDC l_dc (this);
		BOOL l_bDrawFrameControl = l_dc.DrawFrameControl (m_rcGripper, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);

		CDialog::OnPaint ();
	}
}


//*****************************************************************************
//* Function Name: OnSize
//*   Description: 
//*****************************************************************************
void CWineDemoDlg::OnSize (UINT nType, int cx, int cy) 
{
	CDialog::OnSize (nType, cx, cy);
	
	InvalidateRect (m_rcGripper);
	m_rcGripper.right = cx;
	m_rcGripper.bottom = cy;
	m_rcGripper.left = m_rcGripper.right - ::GetSystemMetrics (SM_CXVSCROLL);
	m_rcGripper.top = m_rcGripper.bottom - ::GetSystemMetrics (SM_CYHSCROLL);
	InvalidateRect (m_rcGripper);

	if (m_btnOK.GetSafeHwnd () != NULL) {

		InvalidateRect (m_rcWineListCtrl);
		InvalidateRect (m_rcSeparator);
		InvalidateRect (m_rcOK);
		InvalidateRect (m_rcCancel);

		int l_dx = cx - m_cx; // amount by which the width has grown (or shrunk if negative)
		int l_dy = cy - m_cy; // amount by which the height has grown (or shrunk if negative)

		BOOL l_bRepaint = TRUE;

		m_rcWineListCtrl.right += l_dx;
		m_rcWineListCtrl.bottom += l_dy;
		m_pWineListCtrl->MoveWindow (m_rcWineListCtrl, l_bRepaint);
		
		m_rcSeparator.top += l_dy;
		m_rcSeparator.bottom += l_dy;
		m_rcSeparator.right += l_dx;
		m_lblSeparator.MoveWindow (m_rcSeparator, l_bRepaint);
		
		m_rcOK.OffsetRect (l_dx, l_dy);
		m_btnOK.MoveWindow (m_rcOK, l_bRepaint);

		m_rcCancel.OffsetRect (l_dx, l_dy);
		m_btnCancel.MoveWindow (m_rcCancel, l_bRepaint);
	}

	// Update the current size of the dialog.
	m_cx = cx;
	m_cy = cy;
}


//*****************************************************************************
//* Function Name: OnNcHitTest
//*   Description: 
//*****************************************************************************
UINT CWineDemoDlg::OnNcHitTest (CPoint point)
{
	UINT l_uResult = CDialog::OnNcHitTest (point);

	if (l_uResult == HTCLIENT) {
		CRect l_rc;
		GetWindowRect (l_rc); // point is in screen coordinates
		// Adjust l_rc to describe the size of the gripper.
		l_rc.left = l_rc.right - ::GetSystemMetrics (SM_CXVSCROLL);
		l_rc.top = l_rc.bottom - ::GetSystemMetrics (SM_CYHSCROLL);
		if (l_rc.PtInRect (point)) {
			l_uResult = HTBOTTOMRIGHT;
		}
	}

	return l_uResult;
}


//*****************************************************************************
//* Function Name: OnQueryDragIcon
//*   Description: The system calls this to obtain the cursor to display while
//*                the user drags the minimized window.
//*****************************************************************************
HCURSOR CWineDemoDlg::OnQueryDragIcon ()
{
	return (HCURSOR) m_hIcon32;
}

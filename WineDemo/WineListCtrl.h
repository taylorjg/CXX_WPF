#ifndef _CWineListCtrl_
#define _CWineListCtrl_

class CItemData
{
public:
	CItemData (boost::shared_ptr<CProduct> p_pProduct) :
		m_pProduct (p_pProduct)
	{
	}

	const CProduct* GetProduct (void) const { return m_pProduct.get (); }
	const IPicturePtr& GetPicture (void) const { return m_spPicture; }
	void SetPicture (const IPicturePtr& p_spPicture) { m_spPicture = p_spPicture; }

private:
	boost::shared_ptr<CProduct>	m_pProduct;
	IPicturePtr					m_spPicture;
};

class CWineListCtrl : public CListBox
{
// Construction
public:
	CWineListCtrl ();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWineListCtrl)
	public:
	virtual void MeasureItem (LPMEASUREITEMSTRUCT p_pMeasureItemStruct);
	virtual void DrawItem    (LPDRAWITEMSTRUCT    p_pDrawItemStruct);
	virtual void DeleteItem  (LPDELETEITEMSTRUCT  p_pDeleteItemStruct);
	protected:
	virtual BOOL PreCreateWindow (CREATESTRUCT& p_cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWineListCtrl ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWineListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP ()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif

// ChildView.h : CChildView ��Ľӿ�
//


#pragma once


// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	// The main D3D object
	LPDIRECT3D9 m_pD3D;
	// The D3D rendering device
	LPDIRECT3DDEVICE9 m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9	m_pGroundVB;
	LPDIRECT3DVERTEXBUFFER9	m_pLineVB;

	LPDIRECT3DTEXTURE9		m_pGroundTexture;

	BOOL InitD3D(void);
	// ��ʾ����
	void Render(void);
};


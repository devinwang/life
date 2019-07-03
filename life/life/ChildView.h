// ChildView.h : CChildView 类的接口
//


#pragma once


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 属性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
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
	// 显示函数
	void Render(void);
};


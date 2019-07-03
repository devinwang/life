// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "life.h"
#include "ChildView.h"
#include ".\childview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_pd3dDevice = NULL;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= (WS_EX_CLIENTEDGE);
	cs.style &= ~WS_BORDER;
	//cs.style = WS_OVERLAPPEDWINDOW ;

	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}



void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	//Render();

	//ValidateRect(NULL);
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}


#define D3DFVF_GROUNDVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)//(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
struct GROUNDVERTEX
{
	FLOAT x, y, z; //rhw; // The transformed position for the vertex.
	//DWORD color;        // The vertex color.
	FLOAT tu,tv;
};

#define D3DFVF_POINTVERTEX (D3DFVF_XYZ)//D3DFVF_SPECULAR)//(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
struct POINTVERTEX
{
	FLOAT x, y, z; //rhw; // The transformed position for the vertex.
	DWORD color;        // The vertex color.
};




BOOL CChildView::InitD3D(void)
{
   HRESULT hr;

    // Create the Direct3D object
    m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    if( m_pD3D == NULL )
        return 0;


	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	//d3dpp.Windowed = TRUE;
	//d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	//d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	//d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;
	//d3dpp.EnableAutoDepthStencil=TRUE;
	//d3dpp.Windowed=TRUE;
	//d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	//d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;
	//d3dpp.EnableAutoDepthStencil=TRUE;
	//d3dpp.AutoDepthStencilFormat=D3DFMT_D16;
	//d3dpp.Windowed               = TRUE;
	//d3dpp.SwapEffect             = D3DSWAPEFFECT_COPY;
	//d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed=TRUE;
	d3dpp.SwapEffect=D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat=D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil=TRUE;
	d3dpp.AutoDepthStencilFormat=D3DFMT_D16;



	if( FAILED(hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &d3dpp, &m_pd3dDevice ) ) )
	{
		MessageBox(DXGetErrorString9(hr), TEXT("Error!"), MB_OK | MB_ICONERROR);
		return 0;
	}

	m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	
	m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	
	m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	//m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 1000.0f, 1000.0f,-1000.0f ),
                              &D3DXVECTOR3( 1000.0f, 1000.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );


	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.6428f, 1.0f, 4000.0f );
	m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );




	/* 创建草地*/

	// Rendering of scene objects happens here.


	static GROUNDVERTEX vertices[] =
	{
		{ -1000.0f,	1000.0f,	0.0f,	0.0f,	0.0f}, // x, y, z, rhw, color
		{ 1000.0f,	1000.0f,	0.0f,	0.0f,	1.0f},
		{ -1000.0f,	-1000.0f,	0.0f,	1.0f,	0.0f},
		{ 1000.0f,	-1000.0f,	0.0f,	1.0f,	1.0f},
	};



	if( FAILED( m_pd3dDevice->CreateVertexBuffer( 4*sizeof(GROUNDVERTEX),
         0 /* Usage */, D3DFVF_GROUNDVERTEX, D3DPOOL_DEFAULT, &m_pGroundVB, NULL) ) )
		return FALSE;

	VOID* pVertices;
	
	if( FAILED( m_pGroundVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 ) ) )
		return FALSE;
	memcpy( pVertices, vertices, sizeof(vertices) );
	m_pGroundVB->Unlock();



	static POINTVERTEX vertices2[] =
	{
		{  0.0f,	0.0f,	10.0f,	0xff123456}, // x, y, z, rhw, color
		{ 2000.0f,	2000.0f,	10.0f,	0xff123456},
		{ 2000.0f,	0.0f,	10.0f,	0xff123456},
		{ 1000.0f,	-1000.0f,	10.0f,	0xff123456},
	};

	//POINTVERTEX *ppp;

	//if( FAILED( m_pd3dDevice->CreateVertexBuffer( 1500*1500*sizeof(POINTVERTEX),
    //     0 /* Usage */, D3DFVF_POINTVERTEX, D3DPOOL_DEFAULT, &m_pLineVB, NULL) ) )
	//	return FALSE;

	
	//if( FAILED( m_pLineVB->Lock( 0, /*sizeof(vertices2)*/sizeof(POINTVERTEX)*1500*1500, (void**)&ppp, 0 ) ) )
	//	return FALSE;
//
//	for(int i = 0; i < 1500*1500; i++)
//		ppp[i].x = i;
//		ppp[i].y = i+10;
//		ppp[i].z = i+30;
//		ppp[i].color = GetTickCount();
	//memcpy( pVertices, vertices2, sizeof(vertices2) );
//	m_pLineVB->Unlock();


	


	hr  = D3DXCreateTextureFromFile(m_pd3dDevice,"Winter.bmp",&m_pGroundTexture);



	
	ShowWindow(SW_SHOW);
	

	UpdateWindow();

	return 0;
}

// 显示函数
void CChildView::Render(void)
{
	// TODO: 在此处添加消息处理程序代码
   HRESULT hr;


	hr = m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,78,152), 1.0f, 0 );

	hr = m_pd3dDevice->BeginScene();


	D3DXMATRIX matWorld,matYRound,matXRound;
		

	D3DXMatrixTranslation(&matWorld,1000.0f,500.0f,1300.0f);
	D3DXMatrixRotationX(&matXRound,D3DX_PI/2);
	D3DXMatrixMultiply(&matXRound,&matXRound,&matWorld);
	m_pd3dDevice->SetTransform(D3DTS_WORLD,&matXRound);
	
	// 画草地
	m_pd3dDevice->SetTexture( 0, m_pGroundTexture );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

	m_pd3dDevice->SetStreamSource( 0, m_pGroundVB, 0, sizeof(GROUNDVERTEX));
	m_pd3dDevice->SetFVF( D3DFVF_GROUNDVERTEX );
	m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP , 0, 2 );

	//m_pd3dDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(POINTVERTEX));
	//m_pd3dDevice->SetFVF( D3DFVF_POINTVERTEX );
	//m_pd3dDevice->DrawPrimitive(D3DPT_LINESTRIP  , 0, 1500*1500/2 );


	// End the scene.
	hr = m_pd3dDevice->EndScene();

	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );

}

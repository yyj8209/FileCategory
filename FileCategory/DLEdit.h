#pragma once

/*
											CDLEdit 2012��2��3��14:07:01
�ܵ����Ѵ�ţ�ǵ��������Լ�Ҳ�ٵ�ԾԾ���ԡ�
���ࣺCEdit
ʵ�ֹ��ܣ�ʵ���˷ֱ�ΪFOCUS_DEFAULT��FOCUS_BKCOLOR��FOCUS_FONTBOLD��
					FOCUS_SHADOW�����û����뽹������ͣ�߿�������ܣ���qq��¼
					���ڵı༭�������ƣ��������Զ������������Ĵ�С��
��δʵ�ֵĹ��ܣ�����ԭ�����ģ�����*�����༭���Զ��屳�������д�Ҷ�����Ϥ
								����������Զ���Բ�Ǳ߿�

�����ջ񣺿���Ӧ�˴�ţ˵�ģ����ģʽ����Ҫ�����������ôС��һ��������˵��
					�����Ϥ���ģʽ���ˣ���MFC������ʵ��Ӳ�Ļ����£����Խ�ʡ��ܶ�
					��ʱ�䣬��߳������Ч�ʡ�
*/

// CDLEdit
enum				//ö�ٽ�����
{
	FOCUS_DEFAULT,
	FOCUS_BKCOLOR,
	FOCUS_FONTBOLD,
	FOCUS_SHADOW
};

class CDLEdit : public CEdit
{
	DECLARE_DYNAMIC(CDLEdit)

public:
	CDLEdit();
	virtual ~CDLEdit();

//�༭����Ҫ��Ԫ��
public:
	CRect m_rctEdit;		//�༭��rct��screen���ݶ���client����
	CFont m_Font;			//����

	BOOL m_bHover;		//is��ͣ
	BOOL m_bTrack;		//is���
	BOOL m_bUser;		//is���û��޸ģ�setWindowText���ᴥ��change��Ϣ
	BOOL m_bEmpty;		//is�ı�Ϊ��

	COLORREF m_clrShadow;				//��Ӱ	
	COLORREF m_clrBkGndNormal;		//Ĭ�����뽹���ɫ
	COLORREF m_clrBkGndFocus;		//���뽹���ɫ
	COLORREF m_clrBorderNormal;		//Ĭ�ϱ߿�����ɫ
	COLORREF m_clrBorderHorver;		//��ͣ�߿�����ɫ
	COLORREF m_clrBorderEdit;			//�༭�������ɫ

	int m_nFocusStyle;						//������
	CString m_strGrayString;

	CString m_strFaceName;
	int m_nPointSize;

protected:
	DECLARE_MESSAGE_MAP()

//����ƺ���
public:
	void SetFont(int nPointSize, LPCTSTR lpszFaceName);
	void SetFocusStyle(int nStyle = FOCUS_DEFAULT);
	void SetBkGndColor(
		COLORREF clrNormal = RGB(255,255,255),
		COLORREF clrFocus = RGB(255,255,255)
		);
	void SetBorderColor(
		COLORREF clrBorderEdit = RGB(0xEA,0xEA,0xEA),
		COLORREF clrBorderNormal = RGB(51, 139, 192),
		COLORREF clrBorderHover = RGB(96, 200, 253));
	void SetShadowColor(COLORREF clrShadow = RGB(0xB8,0xB8,0xB8));
	void SetGrayString(CString str);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEnChange();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};



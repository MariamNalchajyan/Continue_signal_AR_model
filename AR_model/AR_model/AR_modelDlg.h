
// AR_modelDlg.h: файл заголовка
//

#pragma once
#include "drawer.h"
#include <fstream>
// Диалоговое окно CARmodelDlg
class CARmodelDlg : public CDialogEx
{
// Создание
public:
	CARmodelDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AR_MODEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	double _A1;
	double _A2;
	double _A3;
	double _N;
	double _M;
	double _f1;
	double _f2;
	double _f3;
	double _fi1;
	double _fi2;
	double _fi3;
	double _fd;
	double _alpha;
	double E_N;
	double E_S;

	Drawer Signal;
	Drawer ContinuedSignal;

	void CARmodelDlg::Signal_and_horizAxis_Points();
	void CARmodelDlg::White_noise_Points();
	void CARmodelDlg::Calculation_Rxx();
	void CARmodelDlg::Calculation_a();
	void CARmodelDlg::СontinueSignal();
	vector<double> horizAxis;
	vector<double> sig;//сигнал по исходным параметрам
	vector<double> continued_signal;
	vector<double> white_noise;
	vector<double> signal;//сигнал,с которым будем работать. С шумом или без,зависит от alpha
	vector<double> R;//автокорреляционная матрица:вектор всех коэф-ов СЛАУ Юла-Уокера
	vector<double> a;//коэф-ы АР-модели
	vector<double> y;//правая часть системы
	double ro;
	afx_msg void OnBnClickedButton1();

	double _range;
	ofstream fout;
};

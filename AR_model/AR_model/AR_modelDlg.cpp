
// AR_modelDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "AR_model.h"
#include "AR_modelDlg.h"
#include "afxdialogex.h"
#include "functions.h"
#include "drawer.h"
#include <fstream>
# define pi 3.141592653589793238462643383279502884L 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define RANGE _range

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CARmodelDlg



CARmodelDlg::CARmodelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AR_MODEL_DIALOG, pParent)
	, _A1(1)
	, _A2(2)
	, _A3(3)
	, _N(1024)
	, _M(512)
	, _f1(0.03)
	, _f2(0.06)
	, _f3(0.09)
	, _fi1(0)
	, _fi2(0)
	, _fi3(0)
	, _fd(3)
	, _alpha(0)
	, _range(25)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CARmodelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_A1, _A1);
	DDX_Text(pDX, IDC_A2, _A2);
	DDX_Text(pDX, IDC_A3, _A3);
	DDX_Text(pDX, IDC_N, _N);
	DDX_Text(pDX, IDC_M, _M);
	DDX_Text(pDX, IDC_F1, _f1);
	DDX_Text(pDX, IDC_F2, _f2);
	DDX_Text(pDX, IDC_F3, _f3);
	DDX_Text(pDX, IDC_FI1, _fi1);
	DDX_Text(pDX, IDC_FI2, _fi2);
	DDX_Text(pDX, IDC_FI3, _fi3);
	DDX_Text(pDX, IDC_FD, _fd);
	DDX_Text(pDX, IDC_EDIT14, _alpha);
	//DDX_Control(pDX, IDC_EDIT1, _tmp);
	//DDX_Control(pDX, IDC_EDIT2, _matrix);
	DDX_Text(pDX, IDC_EDIT3, _range);
}

BEGIN_MESSAGE_MAP(CARmodelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CARmodelDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CARmodelDlg

BOOL CARmodelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	Signal.Create(GetDlgItem(IDC_SIGNAL)->GetSafeHwnd());
	ContinuedSignal.Create(GetDlgItem(IDC_CONTINUED_SIGNAL)->GetSafeHwnd());

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CARmodelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CARmodelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CARmodelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//расчет точек
void CARmodelDlg::Signal_and_horizAxis_Points()

{
	if (sig.size() != 0) {
		sig.clear();
		horizAxis.clear();
	}
	UpdateData(TRUE);
	double dt = 1 / _fd;

	for (int i = 0; i < _N; i++)
	{
		horizAxis.push_back(i * dt);
	}

	for (int i = 0; i < _N; i++)
	{
		double tmp = _A1 * sin(2 * pi * _f1 * i * dt + _fi1) + _A2 * sin(2 * pi * _f2 * i * dt + _fi2) + _A3 * sin(2 * pi * _f3 * i * dt + _fi3);
		sig.push_back(tmp);
	}
}


//расчет отсчетов шума
void CARmodelDlg::White_noise_Points()
{
	if (white_noise.size() != 0) {
		white_noise.clear();
		signal.clear();
	}
	UpdateData(TRUE);
	srand(time(NULL));
	vector<int> g;//g*
	E_N = 0;
	E_S = 0;
	for (int i = 0; i < _N; i++)
	{
		E_S += (sig[i] * sig[i]);//энергия сигнала
		int sum = 0;
		for (int j = 0; j < 12; j++)
		{
			sum += (rand() - RAND_MAX / 2);
		}
		g.push_back(sum);
		E_N += ((double)g[i] * (double)g[i]);//энергия шума
	}

	double alpha = _alpha / 100;
	double betta = sqrt(alpha * E_S / E_N);
	for (int i = 0; i < _N; i++)
	{
		white_noise.push_back(betta * g[i]);
		signal.push_back(sig[i] + white_noise[i]);
		
	}
}

//автокорреляционная матрица Rxx
void CARmodelDlg::Calculation_Rxx()
{
	if (R.size() != 0) {
		R.clear();
		continued_signal.clear();
	}
	UpdateData(TRUE);

	vector<double> rxx(RANGE+1);
	vector<double> corr;
	for (int m = 0; m <= RANGE; m++)
	{
		double sum = 0;
		for (int n = 0; n <= (_M - m - 1); n++)
		{
			sum += signal[n] * signal[n + m];
		}
		rxx[m] = sum / (_M - m - 1);
		corr.push_back(rxx[m]);
	}
	ro = rxx[0] - rxx[1];

	fout.open("Rxx.txt");
	if (fout.is_open())
	{
		fout << "Автокорреляции rxx:\n";
		for (int i = 0; i < corr.size(); i++)
		{
			fout << corr[i] <<"\n";
		}
		fout << "\n";
	}
	vector<vector<double>> Rxx(RANGE+1, vector<double>(RANGE+1));
	string t="";
	for (int i = 0; i < RANGE+1; i++)
	{
		for (int j = 0; j < RANGE+1; j++)
		{
			Rxx[i][j] = rxx[abs(i - j)];
			R.push_back(Rxx[i][j]);
			t += (to_string(Rxx[i][j]) + "	");
		}
		t += '\n';
	}
	if (fout.is_open())
	{
		fout << "(Матрица коэффициентов Юла-Уокера)Rxx:\n";
		for (int i = 0; i < t.size(); i++)
		{
			fout << t[i];
		}
		fout << "\n";
	}
}

//расчет коэф-ов АР-модели
void CARmodelDlg::Calculation_a()
{
	if (a.size() != 0) {
		a.clear();
	}
	UpdateData(TRUE);
	vector<double> x(RANGE+1);
	vector<double> y(RANGE+1);
	y[0] = ro;
	for (int i = 1; i < RANGE; i++)
	{
		y[i] = 0;
	}
	x = kazf(R, y, RANGE+1, RANGE+1);
	string str = "";
	for (int m = 0; m <= RANGE; m++)
	{
		a.push_back(x[m]);
		str += (to_string(a[m])+"\n");
	}
	if (fout.is_open())
	{
		fout << "Векор неизвестных\n";
		for (int i = 0; i < str.size(); i++)
		{
			fout <<str[i];
		}
	}
	fout.close();
}

//расчет продолжения сигнала
void CARmodelDlg::СontinueSignal()
{
	if (continued_signal.size() != 0) {
		continued_signal.clear();
	}

	UpdateData(TRUE);
	for (int i = 0; i < _M; i++)
	{
		continued_signal.push_back(signal[i]);
	}
	
	for (int i = _M; i < _N; i++)
	{
		double sum = 0;
		for (int k = 1; k <= RANGE; k++)
		{
			sum += a[k] * continued_signal[i - k];
		}
		continued_signal.push_back(-sum);
	}
}
void CARmodelDlg::OnBnClickedButton1()
{
	Signal_and_horizAxis_Points();
	White_noise_Points();
	Calculation_Rxx();
	Calculation_a();
	СontinueSignal();
	Signal.Draw(signal,0, -MaxElement(signal), (_N - 1) / _fd, MaxElement(signal), horizAxis);
	ContinuedSignal.Draw(continued_signal, 0, -MaxElement(continued_signal), (_N - 1) / _fd, MaxElement(continued_signal), horizAxis);
	ShellExecute(nullptr, L"open", L"Rxx.txt", nullptr, nullptr, SW_SHOW);
}


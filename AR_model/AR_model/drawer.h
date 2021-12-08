#pragma once
#pragma once
#include <afxwin.h>
#include <vector>

using namespace std;

class Drawer
{
	CRect frame;//������������� ������� ���������
	CWnd* wnd;//��������� �� ������ ����, ������� ���������
	CDC* dc;//��������� ���������, ����������� � ������� ���������
	CDC memDC;//�������� ���������,����������� � ������
	CBitmap bmp;//������ ��� ��������� ��������� memDC,
				//����� Bitmap ��������� �������� � ������ ���������� �����������
	bool init;//���� ��� ������������ ��������� ������������� ������ 

	CPen subgrid_pen;//���� ��� ��������� ��������
	CPen grid_pen;//���� ��� ��������� �����
	CPen data_pen;//���� ��� ��������� �������
	CPen data_pen1;//���� ��� ��������� �������
	CPen data_pen2;//���� ��� ��������� �������
	CFont font;//����� 

	int actual_top;
	int actual_bottom;
	int actual_left;
	int actual_right;

	vector<double> y;
	vector<double> x;
public:
	void Create(HWND hWnd)
	{
		wnd = CWnd::FromHandle(hWnd);//�������� ��������� �� ����
		wnd->GetClientRect(frame);//���������� ��������������(�������/���������� ������� ���������) ����
		dc = wnd->GetDC();//�������� ��������� � ���� ����
		memDC.CreateCompatibleDC(dc);//������� �����-��������(�������� ���������� ������)
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());//������� ��������� �����������(������� �������) 
		memDC.SelectObject(&bmp);//�������� ��������� �����������(� ������ ��������) ��� ������������� �����-���������

		subgrid_pen.CreatePen(PS_DOT, 0.7, RGB(51, 51, 51));//�������������� ���� ��������
		grid_pen.CreatePen(PS_SOLID, 0.8, RGB(0, 0, 0));//�������������� ���� �����
		data_pen.CreatePen(PS_SOLID, 2, RGB(/*0, 93, 108*/0, 0, 128));//������������� ���� �������
		data_pen1.CreatePen(PS_SOLID, 1, RGB(/*0, 93, 108*/0, 0, 128));//������������� ���� �������
		data_pen2.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));//������������� ���� ������� ����������������
		//�����
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// ������
			FALSE,				// ������������
			FALSE,				// �������������
			DEFAULT_CHARSET,	// ����� ��������
			OUT_OUTLINE_PRECIS,	// �������� ������������.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// ��������
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		init = true;
	}

	//����� ��������� ����� � �������
	void Draw(vector<double>& data, double xMin, double yMin, double xMax, double yMax, vector<double>& keys = vector<double>())
	{
		if (!init) return;

		int padding = 30;//�����. �� ����� �����
		int left_keys_padding = 27;//�����. ��� ������ �������� �� ������������ ���(�����)
		int bottom_keys_padding = 10;// �����.��� ������ �������� �� �������������� ���(�����)
		int actual_width = frame.Width() - 2 * padding - left_keys_padding;//������ �������
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;//������ �������

		actual_top = padding;
		actual_bottom = actual_top + actual_height;
		actual_left = padding + left_keys_padding;
		actual_right = actual_left + actual_width;
		memDC.FillSolidRect(frame, RGB(255, 255, 255));//��� �����-�����

		unsigned int grid_size = 10;//�� ������� ������ ����� ���

		memDC.SelectObject(&subgrid_pen);//����� ���� ��� ��������
		//������ ��������
		for (double i = 0.5; i < grid_size; i += 1.0)
		{
			//������������
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			//��������������
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}
		memDC.SelectObject(&grid_pen);//����� ���� ��� �����
		//������ �����
		for (double i = 0.0; i < grid_size + 1; i += 1.0)
		{
			//������������
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);//����� �����
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);//����� �� ���� �����
			//��������������
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}


		if (data.empty()) return;
		if (keys.size() != data.size())
		{
			keys.resize(data.size());
			for (int i = 0; i < keys.size(); i++)
			{
				keys[i] = i;
			}
		}
		memDC.SelectObject(&data_pen);//����� ���� ��� �������
		double data_y_max(yMax), data_y_min(yMin);
		double data_x_max(xMax), data_x_min(xMin);
		//�������������� ��������� � ��������
		vector<double> y = convert_range(data, actual_top, actual_bottom, data_y_max, data_y_min);
		vector<double> x = convert_range(keys, actual_right, actual_left, data_x_max, data_x_min);
		//������ ������
		memDC.MoveTo(x[0], y[0]);
		for (unsigned int i = 0; i < y.size(); i++)
		{
			memDC.LineTo(x[i], y[i]);
		}
		//����������� �������� �� ����
		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));

		for (int i = 0; i < grid_size / 2 + 1; i++)
		{
			CString str;
			str.Format(L"%.1f", data_x_min + i * (data_x_max - data_x_min) / (grid_size / 2));
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding / 2, str);

			str.Format(L"%.1f", data_y_min + i * (data_y_max - data_y_min) / (grid_size / 2));
			memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size / 2) - bottom_keys_padding, str);
		}


		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);//�������� ����������� 
																		//�� ������ �� ���������� ���������
	}
	//�������������� ��������� � ��������
	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}
};
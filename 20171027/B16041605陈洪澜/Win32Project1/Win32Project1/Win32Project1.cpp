// Win32.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100                      ////��MAX_LOADSTRING��100�滻

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��     HINSTANCE:����ĵ�ǰʵ���ľ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�   WCHAR:���ַ�����,C/C++���ַ����ͣ���һ����չ�Ĵ洢��ʽ
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

												// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);//ATOM��WORD�ͣ��޷��ŵĶ����ͣ�ռ2���ֽ�
BOOL                InitInstance(HINSTANCE, int);//BOOL��int�ͣ���ֵ�߼���TRUE / FALSE / ERROR������ֵΪ>0������ΪTRUE��0ΪFALSE�� - 1ΪERROR
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);//LRESULT��long�ͣ��Ӵ��ڳ�����߻ص��������ص�32λֵ
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);//CALLBACK����__stdcall����Ӧ����Ϊ�ص�����

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,//APIENTRY����__stdcall,�����˺�����Ӧ�ó������ڵ�
	_In_opt_ HINSTANCE hPrevInstance,//_In_opt_:�꣬��ѡ���������, ���غ󲻻�ı���ֵ
	_In_ LPWSTR    lpCmdLine,//LPSTR���� char *��ָ����'/0'��β��8λ�����ֽڣ�ANSI�ַ�����ָ��
	_In_ int       nCmdShow)//_In_:�꣬����Ϊ������������������ֵ
{
	UNREFERENCED_PARAMETER(hPrevInstance);//UNREFERENCED_PARAMETER�����߱��������Ѿ�ʹ���˸ñ��������ؼ�⾯��
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣

	// ��ʼ��ȫ���ַ���
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);//LoadStringW��Unicode�����ڰ�String Table��Caption������ַ�����������CString������
	LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);//MyRegisterClass��ע�ᴰ���ຯ��

							   // ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance(hInstance, nCmdShow))//InitInstance������ʵ���������������ʾ�����ڵĺ������ɹ��򷵻ط�0ֵ
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));//HACCEL�����ټ����, LoadAccelerators����������ָ���ļ��ټ���
																						   //MAKEINTRESOURCE����Դ��ת���ĺ꣬��һ����������ת����ָ�����ͣ�IDC_WINDOWSPROJECT1��ʵ����
	MSG msg; /*typedef struct tagMSG{HWND        hwnd;
			 UINT        message;
			 WPARAM      wParam;
			 LPARAM      lParam;
			 DWORD       time;
			 POINT       pt;
			 #ifdef _MAC
			 DWORD       lPrivate;
			 #endif
			 } MSG;
			 ��Ϣ����MSG�ṹ������ʾ�ġ���Ա�������壺��һ����Ա����hwnd��ʾ��Ϣ�����Ĵ��ڣ�
			 �ڶ�����Ա����messageָ������Ϣ�ı�ʶ�������������ĸ���Ա����wParam��lParam������
			 ָ����Ϣ�ĸ�����Ϣ��������������ֱ��ʾ��ϢͶ�ݵ���Ϣ�����е�ʱ������ĵ�ǰλ��*/

			 // ����Ϣѭ��: 
	while (GetMessage(&msg, nullptr, 0, 0))//GetMessage���ӵ����̵߳���Ϣ������ȡ��һ����Ϣ���������ָ���Ľṹ������ֵ���������ȡ��WM_QUIT֮���������Ϣ�����ط���ֵ���������ȡ��WM_QUIT��Ϣ������ֵ���㡣��������˴��󣬷���ֵ��-1��
	{//nullptr:��ָ�����͵Ĺؼ���
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//TranslateAccelerator:������ټ���,����˵������еļ��ټ�;����ֵ�����������óɹ����򷵻ط���ֵ������������ʧ�ܣ��򷵻�ֵΪ��
		{
			TranslateMessage(&msg);//TranslateMessage:���������Ϣת��Ϊ�ַ���Ϣ���ַ���Ϣ�����͵������̵߳���Ϣ���������һ���̵߳��ú���GetMessage��PeekMessageʱ������;����ֵ�������Ϣ��ת���������ַ���Ϣ�����͵������̵߳���Ϣ����������ط���ֵ
			DispatchMessage(&msg);// DispatchMessage:�ַ�һ����Ϣ�����ڳ���,����Ϣ���ݸ�����ϵͳ��Ȼ�����ϵͳȥ���ûص�����������ֵ������ֵ�Ǵ��ڳ��򷵻ص�ֵ
		}
	}

	return (int)msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;//WNDCLASSEXW��WNDCLASSEXW��̨��ṹ����ע�ᴰ����
					 /*1.cbSize��WNDCLASSEX �Ĵ�С�����ǿ�����sizeof��WNDCLASSEX�������׼ȷ��ֵ��
					 2.style������������������Ĵ��ھ��еķ���������á�or�����������Ѽ�������һ��
					 3.lpfnWndProc�����ڴ�������ָ�롣
					 4.cbClsExtra��ָ�������ڴ�����ṹ��ĸ����ֽ�����
					 5.cbWndExtra��ָ�������ڴ���ʵ���ĸ����ֽ��������һ��Ӧ�ó�������Դ����CLASSαָ��ע��һ���Ի�����ʱ�������������Ա���DLGWINDOWEXTRA��
					 6.hInstance����ģ���ʵ�������
					 7.hIcon��ͼ��ľ����
					 8.hCursor�����ľ����
					 9.hbrBackground��������ˢ�ľ����
					 10.lpszMenuName��ָ��˵���ָ�롣
					 11.lpszClassName��ָ�������Ƶ�ָ�롣
					 12.hIconSm���ʹ����������Сͼ�ꡣ�����ֵΪNULL�����hIcon�е�ͼ��ת���ɴ�С���ʵ�Сͼ�ꡣ*/
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;//CS_HREDRAW��һ���ƶ���ߴ����ʹ�ͻ����Ŀ�ȷ����仯�������»��ƴ��ڣ�CS_VREDRAW��һ���ƶ���ߴ����ʹ�ͻ����ĸ߶ȷ����仯�������»��ƴ���
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));//LoadIcon��������hInstanceģ��������Ŀ�ִ���ļ���װ��lpIconNameָ����ͼ����Դ������ͼ����Դ��û�б�װ��ʱ�ú�����ִ��װ�����������ֻ��ȡװ�����Դ���
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//LoadCursor����һ����Ӧ��������صĿ�ִ���ļ���EXE�ļ���������ָ���Ĺ����Դ��IDC_ARROW ��׼�ļ�ͷ
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//HBRUSH����ˢ�ľ����COLOR_WINDOW����ɫ��
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);//RegisterClassExW������Ϊ����ڵ���Createwindow������CreatewindowEx������ʹ�õĴ���ע��һ��������
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
					   //HWND�����ھ��
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,//WS_OVERLAPPEDWINDOW������һ������WS_OVERLAPPED��WS_CAPTION��WS_SYSMENU WS_THICKFRAME��WS_MINIMIZEBOX��WS_MAXIMIZEBOX���Ĳ�����ڣ���WS_TILEDWINDOW�����ͬ
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);//CW_USEDEFAULT�����ڵĴ�Сλ�õ�λĬ��ֵ
																				  //CreateWindowW����������һ���ص�ʽ���ڡ�����ʽ���ڻ��Ӵ��ڡ���ָ�������࣬���ڱ��⣬���ڷ���Լ����ڵĳ�ʼλ�ü���С����ѡ�ģ�������Ҳָ�ô��ڵĸ����ڻ��������ڣ�������ڵĻ����������ڵĲ˵�
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);//�ú�������ָ�����ڵ���ʾ״̬���������֮ǰ�ɼ����򷵻�ֵΪ���㡣�������֮ǰ�����أ��򷵻�ֵΪ��
	UpdateWindow(hWnd);//����ָ�����ڵĿͻ���

	return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//WndProc���ص�������WndProc�ĵ�һ������hWnd���ǵ�ǰ������Ϣ�Ĵ��ھ�����ڶ����������Ǳ����͹�������Ϣ�����������ĸ��������Ǹ�������Ϣ�ϵ�����
{//UINT����Ϣ���ƣ�WPARAM��WORD���͵�32λ���ͱ���
	switch (message)
	{
	case WM_COMMAND://��Ϣ�����û�����˵�����ť�������б��ȿؼ�ʱ�򣬻ᴥ��
	{
		int wmId = LOWORD(wParam);//LOWORD����ָ���� 32 λֵ��������˳�򵥴ʣ�����ֵ��ָ��ֵ�ĵ�λ����
								  // �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);//DialogBox��Windows API���������������Ǵ�һ���Ի�����Դ�д���һ��ģ̬�Ի��򡣸ú���ֱ��ָ���Ļص�����ͨ������EndDialog������ֹģ̬�ĶԻ�����ܷ��ؿ���;About:�����ڡ������Ϣ�������
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);//�������ܣ�����ָ���Ĵ���
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);//DefWindowProc��������ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д�����κδ�����Ϣ�ṩȱʡ�Ĵ���
		}
	}
	break;
	case WM_PAINT://��������ʾ�����һ������ʾ���ݻ���ȫ����Ϊ����Ч���������ڱ��롰���»��桱ʱ�����������Ϣ֪ͨ����
	{
		PAINTSTRUCT ps;// PAINTSTRUCT���ṹ�壬������Ӧ�ó���������������ӵ�еĴ��ڿͻ�������Ҫ����Ϣ
		HDC hdc = BeginPaint(hWnd, &ps);//HDC��MFC�е��豸�����ľ��; BeginPaint:Ϊָ�����ڽ��л�ͼ������׼�������ý��ͻ�ͼ�йص���Ϣ��䵽һ��PAINTSTRUCT�ṹ��
										// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY://�������ٺ�(����DestroyWindow()��)����Ϣ���еõ�����Ϣ
		PostQuitMessage(0);//PostQuitMessage:�ú�����ϵͳ�����и��߳�����ֹ����
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)//INT_PTR:��ָ�볤����ȵ�INT
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:// WM_INITDIALOG:��Ϣ,�Ի�������յ�����Ϣ,�����Ի����������ӿؼ����������
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)//IDOK:ȷ����ť,IDCANCEL:ȡ����ť
		{
			EndDialog(hDlg, LOWORD(wParam));//�ú������һ��ģ̬�Ի���,��ʹϵͳ��ֹ�ԶԻ�����κδ���
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


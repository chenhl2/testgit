// Win32.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100                      ////将MAX_LOADSTRING用100替换

// 全局变量: 
HINSTANCE hInst;                                // 当前实例     HINSTANCE:程序的当前实例的句柄
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本   WCHAR:宽字符类型,C/C++的字符类型，是一种扩展的存储方式
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

												// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);//ATOM：WORD型，无符号的短整型，占2个字节
BOOL                InitInstance(HINSTANCE, int);//BOOL：int型，三值逻辑，TRUE / FALSE / ERROR，返回值为>0的整数为TRUE，0为FALSE， - 1为ERROR
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);//LRESULT：long型，从窗口程序或者回调函数返回的32位值
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);//CALLBACK：即__stdcall，对应函数为回调函数

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,//APIENTRY：即__stdcall,表明此函数是应用程序的入口点
	_In_opt_ HINSTANCE hPrevInstance,//_In_opt_:宏，可选的输入参数, 返回后不会改变其值
	_In_ LPWSTR    lpCmdLine,//LPSTR：即 char *，指向以'/0'结尾的8位（单字节）ANSI字符数组指针
	_In_ int       nCmdShow)//_In_:宏，含义为这个变量或参数是输入值
{
	UNREFERENCED_PARAMETER(hPrevInstance);//UNREFERENCED_PARAMETER：告诉编译器，已经使用了该变量，不必检测警告
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);//LoadStringW：Unicode中用于把String Table中Caption里面的字符串读出来到CString对象里
	LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);//MyRegisterClass：注册窗口类函数

							   // 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))//InitInstance：保存实例句柄并创建和显示主窗口的函数，成功则返回非0值
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));//HACCEL：加速键句柄, LoadAccelerators：函数调入指定的加速键表
																						   //MAKEINTRESOURCE：资源名转换的宏，把一个数字类型转换成指针类型；IDC_WINDOWSPROJECT1：实例名
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
			 消息是由MSG结构体来表示的。成员变量含义：第一个成员变量hwnd表示消息所属的窗口；
			 第二个成员变量message指定了消息的标识符。第三、第四个成员变量wParam和lParam，用于
			 指定消息的附加信息。最后两个变量分别表示消息投递到消息队列中的时间和鼠标的当前位置*/

			 // 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))//GetMessage：从调用线程的消息队列里取得一个消息并将其放于指定的结构；返回值：如果函数取得WM_QUIT之外的其他消息，返回非零值。如果函数取得WM_QUIT消息，返回值是零。如果出现了错误，返回值是-1。
	{//nullptr:空指针类型的关键字
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))//TranslateAccelerator:翻译加速键表,处理菜单命令中的加速键;返回值：若函数调用成功，则返回非零值；若函数调用失败，则返回值为零
		{
			TranslateMessage(&msg);//TranslateMessage:将虚拟键消息转换为字符消息。字符消息被寄送到调用线程的消息队列里，当下一次线程调用函数GetMessage或PeekMessage时被读出;返回值：如果消息被转换（即，字符消息被寄送到调用线程的消息队列里），返回非零值
			DispatchMessage(&msg);// DispatchMessage:分发一个消息给窗口程序,将消息传递给操作系统，然后操作系统去调用回调函数；返回值：返回值是窗口程序返回的值
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;//WNDCLASSEXW：WNDCLASSEXW窗台类结构用于注册窗口类
					 /*1.cbSize：WNDCLASSEX 的大小。我们可以用sizeof（WNDCLASSEX）来获得准确的值。
					 2.style：从这个窗口类派生的窗口具有的风格。您可以用“or”操作符来把几个风格或到一起。
					 3.lpfnWndProc：窗口处理函数的指针。
					 4.cbClsExtra：指定紧跟在窗口类结构后的附加字节数。
					 5.cbWndExtra：指定紧跟在窗口实例的附加字节数。如果一个应用程序在资源中用CLASS伪指令注册一个对话框类时，则必须把这个成员设成DLGWINDOWEXTRA。
					 6.hInstance：本模块的实例句柄。
					 7.hIcon：图标的句柄。
					 8.hCursor：光标的句柄。
					 9.hbrBackground：背景画刷的句柄。
					 10.lpszMenuName：指向菜单的指针。
					 11.lpszClassName：指向类名称的指针。
					 12.hIconSm：和窗口类关联的小图标。如果该值为NULL。则把hIcon中的图标转换成大小合适的小图标。*/
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;//CS_HREDRAW：一旦移动或尺寸调整使客户区的宽度发生变化，就重新绘制窗口；CS_VREDRAW：一旦移动或尺寸调整使客户区的高度发生变化，就重新绘制窗口
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));//LoadIcon函数从与hInstance模块相关联的可执行文件中装入lpIconName指定的图标资源，仅当图标资源还没有被装入时该函数才执行装入操作，否则只获取装入的资源句柄
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//LoadCursor：从一个与应用事例相关的可执行文件（EXE文件）中载入指定的光标资源；IDC_ARROW 标准的箭头
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//HBRUSH：画刷的句柄；COLOR_WINDOW：颜色宏
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);//RegisterClassExW：函数为随后在调用Createwindow函数和CreatewindowEx函数中使用的窗口注册一个窗口类
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中
					   //HWND：窗口句柄
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,//WS_OVERLAPPEDWINDOW：创建一个具有WS_OVERLAPPED，WS_CAPTION，WS_SYSMENU WS_THICKFRAME，WS_MINIMIZEBOX，WS_MAXIMIZEBOX风格的层叠窗口，与WS_TILEDWINDOW风格相同
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);//CW_USEDEFAULT：窗口的大小位置等位默认值
																				  //CreateWindowW：函数创建一个重叠式窗口、弹出式窗口或子窗口。它指定窗口类，窗口标题，窗口风格，以及窗口的初始位置及大小（可选的）。函数也指该窗口的父窗口或所属窗口（如果存在的话），及窗口的菜单
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);//该函数设置指定窗口的显示状态，如果窗口之前可见，则返回值为非零。如果窗口之前被隐藏，则返回值为零
	UpdateWindow(hWnd);//更新指定窗口的客户区

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//WndProc：回调函数，WndProc的第一个参数hWnd就是当前接收消息的窗口句柄，第二个参数就是被传送过来的消息，第三、第四个参数都是附加在消息上的数据
{//UINT：消息名称；WPARAM：WORD类型的32位整型变量
	switch (message)
	{
	case WM_COMMAND://消息，当用户点击菜单、按钮、下拉列表框等控件时候，会触发
	{
		int wmId = LOWORD(wParam);//LOWORD：从指定的 32 位值，检索低顺序单词，返回值是指定值的低位单字
								  // 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);//DialogBox：Windows API函数。它的作用是从一个对话框资源中创建一个模态对话框。该函数直到指定的回调函数通过调用EndDialog函数中止模态的对话框才能返回控制;About:“关于”框的消息处理程序
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);//函数功能：销毁指定的窗口
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);//DefWindowProc函数调用缺省的窗口过程来为应用程序没有处理的任何窗口消息提供缺省的处理
		}
	}
	break;
	case WM_PAINT://当窗口显示区域的一部分显示内容或者全部变为“无效”，以致于必须“更新画面”时，将由这个消息通知程序
	{
		PAINTSTRUCT ps;// PAINTSTRUCT：结构体，包含了应用程序用来绘制它所拥有的窗口客户区所需要的信息
		HDC hdc = BeginPaint(hWnd, &ps);//HDC：MFC中的设备上下文句柄; BeginPaint:为指定窗口进行绘图工作的准备，并用将和绘图有关的信息填充到一个PAINTSTRUCT结构中
										// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY://窗口销毁后(调用DestroyWindow()后)，消息队列得到的消息
		PostQuitMessage(0);//PostQuitMessage:该函数向系统表明有个线程有终止请求
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)//INT_PTR:和指针长度相等的INT
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:// WM_INITDIALOG:消息,对话框才能收到的消息,表明对话框及其所有子控件都创建完毕
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)//IDOK:确定按钮,IDCANCEL:取消按钮
		{
			EndDialog(hDlg, LOWORD(wParam));//该函数清除一个模态对话框,并使系统中止对对话框的任何处理
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


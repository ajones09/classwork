#include <windows.h>

// menu id
#define IDM_QUIT		1200
#define IDM_CLEAR		1000
#define IDM_TEXT1		1010
#define IDM_TEXT2		1020
#define IDM_TEXT3		1030
#define IDM_HEIGHT1		1040
#define IDM_HEIGHT2		1050
#define IDM_HEIGHT3		1060
#define IDM_WEIGHT1		1070
#define IDM_WEIGHT2		1080
#define IDM_WEIGHT3		1090
#define IDM_WEIGHT4		1100
#define IDM_WEIGHT5		1110
#define IDM_COLOR1		1120
#define IDM_COLOR2		1130
#define IDM_COLOR3		1140
#define IDM_COLOR4		1150
#define IDM_COLOR5		1160
#define IDM_COLOR6		1170
#define IDM_ITALICS1	1180
#define IDM_ITALICS2	1190
#define IDM_UNDERLINE1	1210
#define IDM_UNDERLINE2	1220

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ShowText1(HWND hWnd);
void ShowText2(HWND hWnd);

TCHAR lpClassName[] = TEXT("Lesson8");
TCHAR lpWindowName[] = TEXT("Assignment 1");

int textNo = IDM_CLEAR;
COLORREF color  = RGB(0,0,0);
int height = 0;
int weight = 0;
LPCTSTR font = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS myProg;
	if (!hPreInst) {
		myProg.style =CS_HREDRAW | CS_VREDRAW;
		myProg.lpfnWndProc =WndProc;
		myProg.cbClsExtra =0;
		myProg.cbWndExtra =0;
		myProg.hInstance =hInstance;
		myProg.hIcon =NULL;
		myProg.hCursor =LoadCursor(NULL, IDC_ARROW);
		myProg.hbrBackground =(HBRUSH)GetStockObject(WHITE_BRUSH); //RGB(0x80, 0xFF, 0x80)); //WHITE_BRUSH);
		myProg.lpszMenuName =NULL;
		myProg.lpszClassName =lpClassName;
		if (!RegisterClass(&myProg))
			return FALSE;
	}

	hWnd = CreateWindow(
		lpClassName,
		lpWindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,  // x
		CW_USEDEFAULT,  // y
		CW_USEDEFAULT,  // width
		CW_USEDEFAULT,  // height
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); //call WM_PAINT in WndProc

	while (GetMessage(&msg, NULL, 0, 0)) {
		// continue until WM_QUIT message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

void createMenu(HWND hwnd) {

	HMENU hMenu, hSubMenu;  // local variable

	hMenu = CreateMenu();

	// submenu
	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Font"));

	AppendMenu(hSubMenu, MF_STRING, IDM_TEXT1, TEXT("Times New Roman"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_TEXT2, TEXT("Courier"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_TEXT3, TEXT("Arial"));

	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Height"));

	AppendMenu(hSubMenu, MF_STRING, IDM_HEIGHT1, TEXT("24"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_HEIGHT2, TEXT("32"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_HEIGHT3, TEXT("48"));



	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Weight"));

	AppendMenu(hSubMenu, MF_STRING, IDM_WEIGHT1, TEXT("FW_EXTRALIGHT (200)"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_WEIGHT2, TEXT("FW_NORMAL (400)"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_WEIGHT3, TEXT("FW_MEDIUM (500)"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_WEIGHT4, TEXT("FW_BOLD (700)"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_WEIGHT5, TEXT("FW_HEAVY (900)"));



	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Italic"));
	AppendMenu(hSubMenu, MF_STRING, IDM_ITALICS1, TEXT("True"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_ITALICS2, TEXT("False"));


	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Underline"));
	AppendMenu(hSubMenu, MF_STRING, IDM_UNDERLINE1, TEXT("True"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_UNDERLINE2, TEXT("False"));


	hSubMenu = CreatePopupMenu();
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Color"));
	AppendMenu(hSubMenu, MF_STRING, IDM_COLOR1, TEXT("Red"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_COLOR2, TEXT("Green"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_COLOR3, TEXT("Blue"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_COLOR1, TEXT("EXC1"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_COLOR2, TEXT("EXC2"));
	AppendMenu(hSubMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(hSubMenu, MF_STRING, IDM_COLOR3, TEXT("EXC3"));


	// no submenu
	AppendMenu(hMenu, MF_STRING, IDM_CLEAR, TEXT("&Clear"));

	AppendMenu(hMenu, MF_STRING, IDM_QUIT, TEXT("&Quit"));





	SetMenu(hwnd, hMenu);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//HDC hDC;
	TCHAR str_org[] = TEXT("left=\n%d top=%d right=%d bottom=%d");
	TCHAR strx[256]; 
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg) {
	case WM_CREATE:
		createMenu(hWnd);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDM_QUIT:
			int id;
			id = MessageBox(hWnd, //NULL=OS, hWnd=this window
				TEXT("Are you sure to quit?"),
				TEXT("Confirm"),
				MB_OKCANCEL);
			if (id == IDCANCEL)
				return (0L);
			SendMessage(hWnd, WM_CLOSE, 0, 0L);
			break;

		case IDM_CLEAR:
			textNo = IDM_CLEAR;
			InvalidateRect(hWnd, NULL, TRUE);  // call WM_PAINT
			break;

		case IDM_TEXT1:
			textNo = IDM_TEXT1; // Times New Roman
			font = TEXT("Times New Roman");
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_TEXT2:
			textNo = IDM_TEXT2; // Courier
			font = TEXT("Courier");
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_TEXT3:
			textNo = IDM_TEXT3; // Arial
			font = TEXT("Arial");
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_HEIGHT1:
			textNo = IDM_HEIGHT1; // Font Height 24
			height = 24;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_HEIGHT2:
			textNo = IDM_HEIGHT2; // Font Height 32
			height = 32;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_HEIGHT3:
			textNo = IDM_HEIGHT3; // Font Height 48
			height = 48;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_WEIGHT1: // Font Weight  FW_EXTRALIGHT (200)
			weight = 200;
			textNo = IDM_WEIGHT1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_WEIGHT2: // Font Weight FW_NORMAL (400)
			weight = 400;
			textNo = IDM_WEIGHT2; 
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_WEIGHT3: // Font Weight  FW_MEDIUM (500)
			weight = 500;
			textNo = IDM_WEIGHT3;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_WEIGHT4:// Font Weight FW_BOLD (700)
			weight=700;
			textNo = IDM_WEIGHT4;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_WEIGHT5: // Font Weight FW_HEAVY (900)
			weight=900;
			textNo = IDM_WEIGHT5;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_ITALICS1: // Italics TRUE
			textNo = IDM_ITALICS1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_ITALICS2: // Italics FALSE
			textNo = IDM_ITALICS2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_UNDERLINE1: // Underline TRUE
			textNo = IDM_UNDERLINE1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_UNDERLINE2: // Uunderline FALSE
			textNo = IDM_UNDERLINE2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_COLOR1: // COLOR
			textNo = IDM_COLOR1;
			color = RGB(255,0,0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_COLOR2: // COLOR
			textNo = IDM_COLOR2;
			color = RGB(0,255,0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case IDM_COLOR3: // COLOR
			textNo = IDM_COLOR3;
			color = RGB(0,0,255);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		PAINTSTRUCT paint;
		//hDC = BeginPaint(hWnd, &paint);
		HBRUSH hBrush;
		HFONT hFont;
		hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		RECT rt;
		GetClientRect(hWnd, &rt);
		wsprintf(strx, str_org, rt.left, rt.top, rt.right, rt.bottom); 


		switch(textNo) {
		case IDM_CLEAR:
			// fill screen with black/white
			BitBlt(hdc, 0, 0, rt.right-rt.left, rt.bottom-rt.top, 0, 0, 0,WHITENESS);
			break;
		case IDM_TEXT1:

			hFont = CreateFont(height,20,-300,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);

			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;
		case IDM_TEXT2:

			hFont = CreateFont(height,20,-300,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);

			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_TEXT3:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);

			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_HEIGHT1:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_HEIGHT2:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_HEIGHT3:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_WEIGHT1:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony DeJuan Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_WEIGHT2:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_WEIGHT3:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_WEIGHT4:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_WEIGHT5:

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_ITALICS1: // Italics TRUE

			hFont = CreateFont(height,20,0,0,weight,TRUE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_ITALICS2: // Italics FALSE

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_UNDERLINE1: // Underline TRUE

			hFont = CreateFont(height,20,0,0,weight,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_UNDERLINE2: // Underline FALSE

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_COLOR1: // COLOR

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;


		case IDM_COLOR2: // COLOR

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;

		case IDM_COLOR3: // COLOR

			hFont = CreateFont(height,20,0,0,weight,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,font);
			SelectObject(hdc,hFont);
			//Sets the coordinates for the rectangle in which the text is to be formatted.
			SetRect(&rect, 100, 200, 900, 800);
			SetTextColor(hdc, color);
			DrawText(hdc, TEXT("Anthony D Jones"), -1,&rect, DT_NOCLIP);
			break;
		}
		EndPaint(hWnd, &paint);
		break;

	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}
	return (0L);
}

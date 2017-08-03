#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "scrollbar.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApp(HINSTANCE, TCHAR*);
BOOL InitInstance(HINSTANCE, TCHAR*, int);
int initDlg(HWND);
int getDlg(HWND);
int SetWinCenter(HWND);
int ShowScroll(HWND);
int ShowStatic(HWND);
int ShowText(HWND);

int Scr1Min = 1, Scr1Max = 12, Scr2Min = 1, Scr2Max = 31;

//TCHAR edit_str[256];
int ListNo=1, ComboNo=2, ScrPos1=2, ScrPos2=10;
int radio1 = 1; // checked
int radio2 = 0;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
	LPSTR lpsCmdLine, int nCmdShow)
{
    MSG msg;
	TCHAR szClassName[] = TEXT("Dialog Box with two scrollbars");

    if (!hPrevInst) {
        if (!InitApp(hCurInst, szClassName))
            return FALSE;
    }
    if (!InitInstance(hCurInst, szClassName, nCmdShow)) {
        return FALSE;
    }
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

BOOL InitApp(HINSTANCE hInst, TCHAR* szClassName)
{
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = TEXT("MYMENU");
    wc.lpszClassName = szClassName;
    return (RegisterClass(&wc));
}

BOOL InitInstance(HINSTANCE hInst, TCHAR* szClassName, int nCmdShow)
{
    HWND hWnd;

    hWnd = CreateWindow(
			szClassName,
            TEXT("Press any key"),
            WS_OVERLAPPEDWINDOW,
            0, //CW_USEDEFAULT,
            0, //CW_USEDEFAULT,
            400, 
            300,
            NULL,
            NULL,
            hInst,
            NULL);
    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    HINSTANCE hInst1;

	switch (msg) {
        case WM_CREATE:
            SetWinCenter(hWnd);
            break;

		case WM_COMMAND:
            switch (LOWORD(wp)) {
                case IDM_END:
                    SendMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;

				case IDM_ABOUT:
                    MessageBox(hWnd,
                        TEXT("ダイアログボックス Ver1.00"),
                        TEXT("About"),
                        MB_OK | MB_ICONINFORMATION);
                    break;

				case IDM_DLG:
					// See Lesson 15
					hInst1 = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
                    DialogBox(hInst1, TEXT("MYDIALOG"), hWnd, (DLGPROC)DlgProc);
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
            }
            break;

		case WM_PAINT:
            ShowText(hWnd);
            break;

		case WM_CLOSE:
/*            
			id = MessageBox(hWnd, 
                TEXT("Quit?"),
                TEXT("Confirm"),
                MB_OKCANCEL | MB_ICONQUESTION);
            if (id == IDOK)
                DestroyWindow(hWnd);
            break;
*/
		case WM_DESTROY:
            PostQuitMessage(0);
            break;

		default:
            return (DefWindowProc(hWnd, msg, wp, lp));
    }
    return 0L;
}

int SetWinCenter(HWND hWnd)
{
    HWND hDeskWnd;
    RECT deskrc, rc;
    int x, y;
    
    hDeskWnd = GetDesktopWindow();
    GetWindowRect(hDeskWnd, (LPRECT)&deskrc);
    GetWindowRect(hWnd, (LPRECT)&rc);
    //x = (deskrc.right - (rc.right-rc.left)) / 2;
    x = (deskrc.left + deskrc.right) / 2 - (rc.right - rc.left) / 2;
    //y = (deskrc.bottom - (rc.bottom-rc.top)) / 2;
	y = (deskrc.top + deskrc.bottom) / 2 - (rc.bottom - rc.top) / 2;
    SetWindowPos(hWnd, HWND_TOP, x, y, (rc.right-rc.left), (rc.bottom-rc.top), SWP_SHOWWINDOW); 
    return 0;
}

int ShowText(HWND hWnd)
{
    HDC hdc;
    RECT rt;
    PAINTSTRUCT ps;
    TCHAR str[256];
    wsprintf(str, TEXT("Month=%d\nDay=%d"), ScrPos1, ScrPos2);
    GetClientRect(hWnd, &rt);
    hdc = BeginPaint(hWnd, &ps);
    DrawText(hdc, str, -1, &rt, DT_WORDBREAK);
    EndPaint(hWnd, &ps);
    return 0;
}

LRESULT CALLBACK DlgProc(HWND hDlgWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
        case WM_INITDIALOG:
            SetWinCenter(hDlgWnd);
            initDlg(hDlgWnd);
			SetFocus(GetDlgItem(hDlgWnd, IDC_SCROLLBAR1)); 
			return FALSE; // if TRUE, SetFocus() does not work

        case WM_HSCROLL:
			int *ScrPos;
			if ((HWND)lp == GetDlgItem(hDlgWnd, IDC_SCROLLBAR1)) ScrPos = &ScrPos1;
			else if ((HWND)lp == GetDlgItem(hDlgWnd, IDC_SCROLLBAR2)) ScrPos = &ScrPos2;

			switch(LOWORD(wp)) {
                case SB_LINELEFT:
                    (*ScrPos)--;
                    break;
                case SB_LINERIGHT:
                    (*ScrPos)++;
                    break;
                case SB_PAGELEFT:
                    *ScrPos -= 10;
                    break;
                case SB_PAGERIGHT:
                    *ScrPos += 10;
                    break;
                case SB_THUMBTRACK:
                    *ScrPos =(int)(HIWORD(wp));
                    break;
            }
            ShowScroll(hDlgWnd);
            break;

		case WM_COMMAND:
			switch (LOWORD(wp)) {
                case IDC_BUTTON1:
                    getDlg(hDlgWnd);
                    EndDialog(hDlgWnd, IDC_BUTTON1);
                    break;
                case IDC_BUTTON2:
                    EndDialog(hDlgWnd, IDC_BUTTON2);
                    break;
                default:
                    return FALSE;
            }
            break;

		default:
            return FALSE;
    }
    return TRUE;
}

int initDlg(HWND hDlgWnd)
{
	SetScrollRange(GetDlgItem(hDlgWnd, IDC_SCROLLBAR1), SB_CTL, 1, 12, TRUE);
	ShowScroll(hDlgWnd);
	SetScrollRange(GetDlgItem(hDlgWnd, IDC_SCROLLBAR2), SB_CTL, 1, 31, TRUE);
	ShowScroll(hDlgWnd);

	return 0;
}

int getDlg(HWND hDlgWnd)
{
    ScrPos1 = GetScrollPos(GetDlgItem(hDlgWnd, IDC_SCROLLBAR1), SB_CTL);
    ScrPos2 = GetScrollPos(GetDlgItem(hDlgWnd, IDC_SCROLLBAR2), SB_CTL);
    return 0;
}

int ShowScroll(HWND hWnd)
{
    if (ScrPos1 < Scr1Min)
        ScrPos1 = Scr1Min;
    if (ScrPos1 > Scr1Max)
        ScrPos1 = Scr1Max;
    if (ScrPos2 < Scr2Min)
        ScrPos2 = Scr2Min;
    if (ScrPos2 > Scr2Max)
        ScrPos2 = Scr2Max;
    SetScrollPos(GetDlgItem(hWnd, IDC_SCROLLBAR1), SB_CTL, ScrPos1, TRUE);
    SetScrollPos(GetDlgItem(hWnd, IDC_SCROLLBAR2), SB_CTL, ScrPos2, TRUE);
    ShowStatic(hWnd);

	return 0;
}

int ShowStatic(HWND hWnd)
{
	TCHAR str[8];
    wsprintf(str, TEXT("%3d"), ScrPos1);
    SetWindowText(GetDlgItem(hWnd, IDC_STATIC1), str);
    wsprintf(str, TEXT("%3d"), ScrPos2);
    SetWindowText(GetDlgItem(hWnd, IDC_STATIC2), str);
    return 0;
}

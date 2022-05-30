#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <iostream>
#include <tchar.h>
#include<math.h>
#include <windows.h>
#include <list>
#include <string>
#include<sstream>
#include <fstream>
#define GREEN 1
#define BLACK 2
#define BLUE 3
#define RED 4
#define YELLOW 5
#define HAND 6
#define STANDARDARROW 7
#define CROSS 8
#define WAIT 9
#define DirectC 10
#define PolarC 11
#define ItPolarC 12
#define MidpointC 13
#define ModifiedMidpointC 14
#define POINTCLIPPINCIRCLE 15
#define LINECLIPPINCIRCLE 16
#define DIRECTELLIPSE 17
#define POLARELLIPSE 18
#define MIDPOINTELLIPSE 19
#define LINEFILLING 20
#define CIRCLEFILLING 21
#define CONVEX 22
#define NONCONVEX 23
#define POINTCLIPPINGRECT 24
#define LINECLIPPINGRECT 25
#define SAVE 26
#define LINEDDA 27
#define LINEMIDPOINT 28
#define LINEPARAMETRIC 29

using namespace std;

//---------------------------
list<string> fileContent;
string line;

void save()
{
    ofstream MyFile("Commands.txt");
    list<string>::iterator it;
    for (it = fileContent.begin(); it != fileContent.end(); ++it)
    {
        MyFile << *it<<endl;
    }
    MyFile.close();
}
string tostring(int a)
{
    stringstream stream;

    stream << a;

    // initializing a string

    string str;

    stream >> str;

    return str;
}

string color_tostring(COLORREF c)
{
    if(c == RGB(255,0,0))
        return "red";
    else if(c == RGB(255,255,0))
        return "yellow";
    else if(c==RGB(0,0,0))
        return "black";
    else if(c == RGB(0,0,255))
        return "blue";
    else if(c == RGB(0,255,0))
        return "green";


}
//---------------------------
int algo = 0;
COLORREF c;
LPCSTR mouse = IDC_ARROW;
HMENU hmenu;
void printColorOptions()
{
    int color;
    cout<<"color options:"<<endl;
    cout<<"1-red"<<endl;
    cout<<"2-yellow"<<endl;
    cout<<"3-black"<<endl;
    cout<<"4-blue"<<endl;
    cout<<"5-green"<<endl;
    cin>>color;
    switch(color)
    {
    case 1:
        c = RGB(255,0,0);
        break;
    case 2:
        c = RGB(255,255,0);
        break;
    case 3:
        c = RGB(0,0,0);
        break;
    case 4:
        c = RGB(0,0,255);
        break;
    case 5:
        c = RGB(0,255,0);
        break;

     default:
        break;

    }
}

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
   wincl.hbrBackground = CreateSolidBrush(RGB(255,255,255));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           844,                 /* The programs width */
           575,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    printColorOptions();
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void menus(HWND hwnd)
{
    hmenu = CreateMenu();

    HMENU colorMenu = CreateMenu();
    AppendMenu(colorMenu, MF_STRING, RED, _T("Red"));
    AppendMenu(colorMenu, MF_STRING, YELLOW, _T("Yellow"));
    AppendMenu(colorMenu, MF_STRING, BLACK, _T("Black"));
    AppendMenu(colorMenu, MF_STRING, BLUE, _T("Blue"));
    AppendMenu(colorMenu, MF_STRING, GREEN, _T("GREEN"));

    HMENU mouseMenu = CreateMenu();
    AppendMenu(mouseMenu, MF_STRING, HAND, _T("Hand"));
    AppendMenu(mouseMenu, MF_STRING, CROSS, _T("Cross"));
    AppendMenu(mouseMenu, MF_STRING, WAIT, _T("Wait"));
    AppendMenu(mouseMenu, MF_STRING, STANDARDARROW, _T("Standardarrow"));

    HMENU LineMenu = CreateMenu();
	AppendMenu(LineMenu, MF_STRING, LINEDDA, _T("DDA"));
	AppendMenu(LineMenu, MF_STRING, LINEMIDPOINT, _T("Midpoint"));
	AppendMenu(LineMenu, MF_STRING, LINEPARAMETRIC, _T("Parametric"));

    HMENU circleMenu = CreateMenu();
    AppendMenu(circleMenu, MF_STRING, DirectC, _T("Direct"));
    AppendMenu(circleMenu, MF_STRING, PolarC, _T("Polar"));
    AppendMenu(circleMenu, MF_STRING, ItPolarC, _T("Iterative polar"));
    AppendMenu(circleMenu, MF_STRING, MidpointC, _T("Midpoint"));
    AppendMenu(circleMenu, MF_STRING, ModifiedMidpointC, _T("Modified midpoint"));

    HMENU ellipseMenu = CreateMenu();
    AppendMenu(ellipseMenu, MF_STRING,DIRECTELLIPSE ,"Direct");
    AppendMenu(ellipseMenu, MF_STRING,POLARELLIPSE ,"Polar");
    AppendMenu(ellipseMenu, MF_STRING,MIDPOINTELLIPSE ,"Mid-Point");

    HMENU clippingMenu = CreateMenu();
    HMENU circleClippingMenu = CreateMenu();
    HMENU rectangleClippingMenu = CreateMenu();
    HMENU squareClippingMenu = CreateMenu();

    AppendMenu(clippingMenu, MF_POPUP, (UINT_PTR)circleClippingMenu, _T("Circle Window"));
    AppendMenu(clippingMenu, MF_POPUP, (UINT_PTR)rectangleClippingMenu, _T("Rectangle Window"));
    AppendMenu(clippingMenu, MF_POPUP, (UINT_PTR)squareClippingMenu, _T("Square Window"));

    AppendMenu(rectangleClippingMenu, MF_STRING, POINTCLIPPINGRECT, _T("Point"));
    AppendMenu(rectangleClippingMenu, MF_STRING, LINECLIPPINGRECT, _T("Line"));

    AppendMenu(circleClippingMenu, MF_STRING, POINTCLIPPINCIRCLE, _T("Point"));
    AppendMenu(circleClippingMenu, MF_STRING, LINECLIPPINCIRCLE, _T("Line"));

    HMENU fillingMenu = CreateMenu();
    AppendMenu(fillingMenu, MF_STRING, LINEFILLING, _T("Line"));
    AppendMenu(fillingMenu, MF_STRING, CIRCLEFILLING, _T("Circle"));

    HMENU fillingPolygonMenu = CreateMenu();
    AppendMenu(fillingPolygonMenu, MF_STRING, CONVEX, _T("Convex"));
    AppendMenu(fillingPolygonMenu, MF_STRING, NONCONVEX, _T("Non-convex"));

    AppendMenu(hmenu, MF_STRING, SAVE, _T("Save"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) colorMenu, _T("Color"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) mouseMenu, _T("Mouse"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)LineMenu, _T("Line"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) circleMenu, _T("Circle"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) ellipseMenu, _T("Ellipse"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) clippingMenu, _T("Clipping"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) fillingMenu, _T("Filling Circle"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) fillingPolygonMenu, _T("Filling Polygon"));
    SetMenu(hwnd, hmenu);
}
int Round(double x )
{
    return (int) (x+0.5);
}

void Swap(int& x1, int& y1, int& x2, int& y2)
{
    int temp = x1;
    x1 = x2;
    x2 = temp;

    temp = y1;
    y1 = y2;
    y2 = temp;
}

void LineDDA(HDC hdc, int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) <= abs(dx)) {

        if (x1 > x2) Swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);

        int x = x1;
        double y = y1;
        double m = (double)dy/dx;

        while (x < x2) {
            x++;
            y += m;
            SetPixel(hdc, x, Round(y), c);
        }

    }
    else {

        if (y1 > y2) Swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1, c);

        int y = y1;
        double x = x1;
        double m = (double)dx/dy;

        while (y < y2) {
            y++;
            x += m;
            SetPixel(hdc, Round(x), y, c);
        }

    }
}

void LineParametric(HDC hdc, int x1, int y1, int x2, int y2)
{
    int x, y;
    for (double t = 0; t <= 1; t += 0.001) {
        x = x1 + t * (x2 - x1);
        y = y1 + t * (y2 - y1);
        SetPixel(hdc, x, y, c);
    }
}

void LineMidPoint(HDC hdc, int x1, int y1, int x2, int y2)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    double m = (double)dy / dx;

    if (m > 0 && m < 1) {

        if (x1 > x2) {
            Swap(x1, y1, x2, y2);
            dy = y2 - y1;
            dx = x2 - x1;
        }

        SetPixel(hdc, x1, y1, c);

        int d = dx - (2 * dy);
        int x = x1;
        int y = y1;

        while (x < x2) {
            if (d <= 0) {
                d += 2 * (dx - dy);
                x++;
                y++;
            }
            else {
                d += -2 * dy;
                x++;
            }
            SetPixel(hdc, x, y, c);
        }

    }

    else if (m > 1) {

        if (y1 > y2) {
            Swap(x1, y1, x2, y2);
            dy = y2 = y1;
            dx = x2 - x1;
        }

        SetPixel(hdc, x1, y1, c);

        int d = 2 * dx - dy;
        int x = x1;
        int y = y1;

        while (y < y2) {

            if (d <= 0) {
                d += 2 * dx;
                y++;
            }
            else {
                d += 2 * (dx - dy);
                x++;
                y++;
            }
            SetPixel(hdc, x, y, c);

        }

    }

    else if(m > -1 && m < 0) {

        if (x1 < x2) {
            Swap(x1, y1, x2, y2);
            dy = y2 - y1;
            dx = x2 - x1;
        }

        SetPixel(hdc, x1, y1, c);

        int d = dx + (2 * dy);
        int x = x1;
        int y = y1;

        while(x > x2) {

            if (d <= 0) {
                d += 2 * dy;
                x--;
            }
            else {
                d += 2 * (dx + dy);
                x--;
                y++;
            }

            SetPixel(hdc, x, y, c);
        }
    }
    else {

        if(y1 > y2) {
            Swap(x1, y1, x2, y2);
            dy = y2 - y1;
            dx = x2 - x1;
        }

        SetPixel(hdc, x1, y1, c);

        int d = (2 * dx) + dy;
        int x = x1;
        int y = y1;

        while(y < y2) {

            if(d <= 0) {
                d += 2 * (dx + dy);
                x--;
                y++;
            }
            else {
                d += 2 * dx;
                y++;
            }

            SetPixel(hdc, x, y, c);
        }
    }
}

void draw8points(HDC hdc, int xc, int yc, int x, int y)
{
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc + y, yc + x, c);
    SetPixel(hdc, xc - y, yc + x, c);
    SetPixel(hdc, xc - y, yc - x, c);
    SetPixel(hdc, xc + y, yc - x, c);
}

void circleDirect(HDC hdc, int xc, int yc, int r)
{
    int x = 0, y = r;
    int r2 = r*r;

    draw8points(hdc, xc, yc, x, y);
    while(x<y)
    {
        x++;
        y = Round(sqrt ( (double) (r2 - (x*x)) ));
        draw8points(hdc, xc, yc, x, y);
    }
}

void circlePolar(HDC hdc, int xc, int yc, int r)
{
    int x = r, y = 0;
    double theta = 0, dtheta = 1.0/r;
    draw8points(hdc, xc, yc, x, y);
    while(x>y)
    {
        theta+=dtheta;
        x = Round(r*cos(theta));
        y = Round(r*sin(theta));
        draw8points(hdc, xc, yc, x, y);
    }
}

void circleIterative(HDC hdc, int xc, int yc, int r)
{
    double x = r, y = 0;
    double dtheta = 1.0/r;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    draw8points(hdc, xc, yc, x, y);
    while(x > y)
    {
        double x1 = x*cdtheta - y*sdtheta;
        y = x*sdtheta + y*cdtheta;
        x = x1;
        draw8points(hdc, xc, yc, Round(x), Round(y));
    }
}

void midpointCircle(HDC hdc, int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 1 - r;

    draw8points(hdc, xc, yc, x, y);

    while (x < y)
    {
        if (d < 0)
        {
            d += 2*x + 2;
        }
        else
        {
            d += 2*(x-y) + 5;
            y--;
        }
        x++;
        draw8points(hdc, xc, yc, x, y);
    }

}

void modifiedMidpointCircle(HDC hdc, int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 1 - r;
    int change1 = 3, change2 = 5 - 2*r;

    draw8points(hdc, xc, yc, x, y);

    while (x < y)
    {
        if (d < 0)
        {
            d += change1;
            change2 += 2;
        }
        else
        {
            d += change2;
            change2 += 4;
            y--;
        }
        change1 += 2;
        x++;
        draw8points(hdc, xc, yc, x, y);
    }
}

void pointClippingCircle(HDC hdc,int x, int y, int xc, int yc, int r)
{
    int xdis = xc-x;
    int ydis = yc-y;

    if(sqrt(pow(xdis, 2) + pow(ydis, 2)) <= r)
            SetPixel(hdc, x, y, c);
}
void Swap(int& x,int& y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

void lineClippingCircle(HDC hdc, int x1, int y1, int x2, int y2, int xc, int yc, int r)
{

    if (x1 > x2) {
		Swap(x1, x2);  Swap(y1, y2);
	}
	double xInter1, yInter1, xInter2, yInter2, slope, d1, d2;

	slope = (y2 - y1)*1.0 / (x2 - x1)*1.0;

	xInter1 = -(sqrt((r*r - xc*xc + 2 * x1*xc - x1*x1)*slope*slope + ((2 * xc - 2 * x1)*yc - 2 * y1*xc + 2 * y1*x1)*slope + r*r - yc*yc + 2 * y1*yc - y1*y1) - x1*slope*slope + (y1 - yc)*slope - xc) / (double)(slope*slope + 1);
	yInter1 = y1 + (xInter1 - x1)*slope;

	xInter2 = (sqrt((r*r - xc*xc + 2 * x1*xc - x1*x1)*slope*slope + ((2 * xc - 2 * x1)*yc - 2 * y1*xc + 2 * y1*x1)*slope + r*r - yc*yc + 2 * y1*yc - y1*y1) + x1*slope*slope + (yc - y1)*slope + xc) / (double)(slope*slope + 1);
	yInter2 = y1 + (xInter2 - x1)*slope;

	d1 = sqrt((x1 - xc)*(x1 - xc) + (y1 - yc)*(y1 - yc));
	d2 = sqrt((x2 - xc)*(x2 - xc) + (y2 - yc)*(y2 - yc));

	if (d1 < r && d2 < r) {
		LineDDA(hdc, x1, y1, x2, y2);
	}
	else if (d1 < r) {
		LineDDA(hdc, x1, y1, xInter2, yInter2);
	}
	else if (d2 < r) {
		LineDDA(hdc, xInter1, yInter1, x2, y2);
	}
	else {
		LineDDA(hdc, xInter1, yInter1, xInter2, yInter2);
	}

}

void draw4points(HDC hdc, int xc, int yc, int x, int y)
{
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc - x, yc + y, c);


}

void directEllipse (HDC hdc, int xc, int yc, int a, int b)
{
    int x = 0;
    double y = b;
    draw4points(hdc, xc, yc, x, y);

    double as = a * a;
    double bs = b * b;

    while (x * bs < y * as)
    {
        x++;
        y = b * sqrt(1 - ((double)(x*x) / as));
        draw4points(hdc, xc, yc, x, Round(y));
    }

    int _y = 0;
    int _x = a;
    draw4points(hdc, xc, yc, _x, _y);

    double _as = a * a;
    double _bs = b * b;

    while (_x * _bs > _y * _as)
    {
        _y++;
        _x = a * sqrt(1 - ((double)(_y * _y) / _bs ));
        draw4points(hdc, xc, yc, Round(_x), _y);
    }
}

void polarEllipse (HDC hdc, int xc, int yc, int a, int b)
{
    double x = a, y = 0;
    double theta = 0;
    double inc = 0;
    draw4points(hdc, xc, yc, x, y);

    if(a > b)
        inc = 1.0 / (double) a;
    else
        inc = 1.0 / (double) b;

    while (x > 0)
    {
        theta += inc;
        x = a * cos(theta);
        y = b * sin(theta);
        draw4points(hdc, xc, yc, Round(x), Round(y));
    }
}

void ellipseMidPoint (HDC hdc, int xc, int yc, int a, int b)
{
    //first region
    int x = 0;
    int y = b;
    draw4points(hdc, xc, yc, x, y);

    double as = a * a;
    double bs = b * b;

    int d = bs + (as * 0.25) - (as * b);
    int d1 = (3 * bs) - (3 * b * as) + (as * 2);
    int d2 = 3 * bs;

    while (bs * x <= as * y)
    {
        if(d > 0)
        {
           y--;
           d+= bs * (2 * x + 3) + as * (-2 * y +2);
        }
        else
        {
            d += bs * (2 * x + 3);
        }
        x++;
        draw4points(hdc, xc, yc, Round(x), Round(y));
    }

    //second region
    d = bs * (x + 0.5) * (x + 0.5) + as * (y - 1) * (y - 1) - as * bs;
    draw4points(hdc, xc, yc, Round(x), Round(y));

    while (y > 0)
    {
        if (d > 0)
        {
            d += as * (-2 * y + 3);
        }
        else
        {
            x++;
            d += bs * (2 * x + 2) + as * (-2 * y + 3);
        }
        y--;
        draw4points(hdc, xc, yc, Round(x), Round(y));


    }
}
void drawQuarterByLines(HDC hdc, int xc, int yc, int x, int y, int quarter)
{
    if(quarter == 1)
    {
        LineDDA(hdc, xc - x, yc - y, xc, yc);
        LineDDA(hdc, xc - y, yc - x, xc, yc);
    }

     else if(quarter == 2)
     {

        LineDDA(hdc, xc + x, yc - y, xc, yc);
        LineDDA(hdc, xc + y, yc - x, xc, yc);
     }

    else if(quarter == 3)
    {
        LineDDA(hdc, xc + x, yc + y, xc, yc);
        LineDDA(hdc, xc + y, yc + x, xc, yc);
    }


    else if(quarter == 4)
    {
        LineDDA(hdc, xc - x, yc + y, xc, yc);
        LineDDA(hdc, xc - y, yc + x, xc, yc);
    }

}


int determineQuarter(int x1, int y1, int xc, int yc, int r)
{
    int q = 0;
    if(x1 >= xc-r && x1 <= xc && y1 >= yc-r && y1 <= yc)
    {
        q = 1;
    }
    else if(x1 >= xc && x1 <= xc+r && y1 >= yc-r && y1 <= yc)
    {
        q = 2;
    }
    else if(x1 >= xc && x1 <= xc+r && y1 >= yc && y1 <= yc+r)
    {
        q = 3;
    }
    else if(x1 >= xc-r && x1 <= xc && y1 >= yc && y1 <= yc+r)
    {
        q = 4;
    }

    return q;
}
void draw2points(HDC hdc, int xc, int yc, int x, int y, int q)
{
    if(q == 1)
    {
        SetPixel(hdc, xc - x, yc - y, c);
        SetPixel(hdc, xc - y, yc - x, c);
    }

    else if(q == 2)
    {
        SetPixel(hdc, xc + x, yc - y, c);
        SetPixel(hdc, xc + y, yc - x, c);
    }

    else if(q==3)
    {
        SetPixel(hdc, xc + x, yc + y, c);
        SetPixel(hdc, xc + y, yc + x, c);
    }

    else if(q == 4)
    {
        SetPixel(hdc, xc - x, yc + y,c);
        SetPixel(hdc, xc - y, yc + x, c);
    }

}

void midpointCircle2Points(HDC hdc, int xc, int yc, int r,int q)
{
    int x = 0, y = r;
    int d = 1 - r;
    int change1 = 3, change2 = 5 - 2*r;

    draw2points(hdc, xc, yc, x, y,q);

    while (x < y)
    {
        if (d < 0)
        {
            d += change1;
            change2 += 2;
        }
        else
        {
            d += change2;
            change2 += 4;
            y--;
        }
        change1 += 2;
        x++;
        draw2points(hdc, xc, yc, x, y,q);
    }
}

void circleFillingCircle(HDC hdc, int x1, int y1, int xc, int yc, int r)
{
    int q = determineQuarter(x1, y1, xc, yc, r);
    int i;
    for(i = r; i >= 0; i--)
        midpointCircle2Points(hdc, xc, yc, i, q);
}

void circleFillingLine(HDC hdc, int x1, int y1, int xc, int yc, int r)
{
    int q = determineQuarter(x1, y1, xc, yc, r);

    int x = 0, y = r;
    int d = 1 - r;
    int change1 = 3, change2 = 5 - 2*r;

    drawQuarterByLines(hdc, xc, yc, x, y, q);

    while (x < y)
    {
        if (d < 0)
        {
            d += change1;
            change2 += 2;
        }
        else
        {
            d += change2;
            change2 += 4;
            y--;
        }
        change1 += 2;
        x++;
        drawQuarterByLines(hdc, xc, yc, x, y, q);
    }
}
// convex polygon filling

typedef struct
{
    int xLeft, xRight;
} edgeTable[800];
struct Point
{
    int x , y;

    Point()
    {
        x = 0;
        y = 0;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }


};
void initEdgeTable(edgeTable table)
{
    for (int i = 0; i < 800; i++)
    {
        table[i].xLeft = INT_MAX;
        table[i].xRight = -INT_MAX;

    }
}

void edge2Table (Point p1, Point p2, edgeTable table)
{
    if (p1.y == p2.y)
        return;
    if (p1.y > p2.y)
    {
        Swap(p1.x, p2.x);
        Swap(p1.y, p2.y);
    }

    double minv = (p2.x - p1.x) / (double) (p2.y - p1.y);
    double x = p1.x;
    int y = p1.y;

    while (y < p2.y)
    {
        if (x < table[y].xLeft)
        {
            table[y].xLeft = (int) ceil(x);
        }
        if (x > table[y].xRight)
        {
            table[y].xRight = (int) floor(x);
        }
        y++;
        x += minv;
    }

}

void polygon2Table (Point points[], int n, edgeTable table)
{
    Point p1 = points[n-1];

    for (int i = 0; i < n; i++)
    {
        Point p2 = points[i];
        edge2Table(p1, p2, table);
        p1 = p2;
    }
}

void  table2Screen (HDC hdc, edgeTable table)
{
    for (int i = 0; i < 800; i++)
    {
        if (table[i].xLeft < table[i].xRight)
        {
            LineDDA(hdc, table[i].xLeft, i, table[i].xRight, i);
        }
    }
}

void fillPolygon (HDC hdc, Point points[], int n)
{
    edgeTable table;
    initEdgeTable(table);
    polygon2Table(points, n, table);
    table2Screen(hdc, table);

}
//Rectangle clipping
void PointClippingRect(HDC hdc, int x, int y, int xleft, int ytop, int xright, int ybottom)
{
	if (x >= xleft && x <= xright && y >= ytop && y <= ybottom)
		SetPixel(hdc, x, y, c);
}

union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1, top:1, right:1, bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All = 0;
    if(x < xleft)
        out.left = 1;
    else if(x > xright)
        out.right = 1;
    if(y < ytop)
        out.top = 1;
    else if(y > ybottom)
        out.bottom = 1;
    return out;
}

void VIntersect(double xs, double ys, double xe, double ye, int x, double *xi, double *yi)
{
    *xi = x;
    *yi = ys+(x-xs)*(ye-ys)/(xe-xs);
}

void HIntersect(double xs, double ys, double xe,double ye, int y, double *xi, double *yi)
{
    *yi = y;
    *xi = xs+(y-ys)*(xe-xs)/(ye-ys);
}

void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom)
{
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1, xleft, ytop, xright, ybottom);
    OutCode out2=GetOutCode(x2,y2, xleft, ytop, xright, ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        LineDDA(hdc,x1,y1,x2,y2);
    }
}
/*  This function is called by the Windows function DispatchMessage()  */

int cnt = 0, xc, yc, x, y, radius,x1,y_1, x2,y2, a, b;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {


        case WM_RBUTTONDOWN:
            if(cnt == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                cnt++;
                if(algo == POINTCLIPPINCIRCLE)
                {
                    pointClippingCircle(hdc, x,  y,  xc,  yc,  radius);
                    line = "pointClippingCircle,"+tostring(x)+','+tostring(y)+','+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == POINTCLIPPINGRECT)
                {
                    PointClippingRect(hdc, x, y, 100,50, 400,200);
                    line = "PointClippingRect,"+tostring(x)+','+tostring(y)+','+tostring(100)+','+tostring(50)+','+tostring(400)+','+tostring(200)+','+color_tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == LINEFILLING)
                {
                    circleFillingLine(hdc, x, y, xc, yc, radius);
                    line = "circleFillingLine,"+tostring(x)+','+tostring(y)+','+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == CIRCLEFILLING)
                {
                    circleFillingCircle(hdc, x, y, xc, yc, radius);
                    line = "circleFillingCircle,"+tostring(x)+','+tostring(y)+','+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }

            }
            else
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                if(algo == LINECLIPPINCIRCLE)
                {
                    lineClippingCircle(hdc, x, y, x2, y2, xc, yc, radius);
                    line = "lineClippingCircle,"+tostring(x)+','+tostring(y)+','+tostring(x2)+','+tostring(y2)+','+tostring(xc)+','+tostring(yc)+','+tostring(radius);
                    fileContent.push_back(line);
                    cnt = 0;
                }
            }
            break;

        case WM_LBUTTONDOWN:
            if(cnt == 0)
                {
                    xc = LOWORD(lParam);
                    yc = HIWORD(lParam);

                    cnt++;
                }
                else if(cnt == 1)
                {
                    x = LOWORD(lParam);
                    y = HIWORD(lParam);
                    cnt++;
                    radius = sqrt(pow((x-xc),2) + pow((y-yc),2));
                    switch(algo)
                    {
                        case LINEDDA:
                            LineDDA(hdc, xc, yc, x, y);
                            line = "LineDDA,"+tostring(xc)+','+tostring(yc)+','+tostring(x)+tostring(y)+','+color_tostring(c);
                            break;
                        case LINEMIDPOINT:
                            LineMidPoint(hdc, xc, yc, x, y);
                            line = "LineMidpoint,"+tostring(xc)+','+tostring(yc)+','+tostring(x)+tostring(y)+','+color_tostring(c);
                            break;
                        case LINEPARAMETRIC:
                            line = "LineParametric,"+tostring(xc)+','+tostring(yc)+','+tostring(x)+tostring(y)+','+color_tostring(c);
                            LineParametric(hdc, xc, yc, x, y);
                            break;
                        case DirectC:
                            circleDirect(hdc, xc, yc, radius);
                            line = "circleDirect,"+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                            fileContent.push_back(line);;
                            break;
                        case PolarC:
                            circlePolar(hdc, xc, yc, radius);
                            line = "circlePolar,"+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                            fileContent.push_back(line);
                            break;
                        case ItPolarC:
                            circleIterative(hdc, xc, yc, radius);
                            line = "circleIterative,"+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                            fileContent.push_back(line);
                            break;
                        case MidpointC:
                            midpointCircle(hdc, xc, yc, radius);
                            line = "midpointCircle,"+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                            fileContent.push_back(line);
                            break;
                        case ModifiedMidpointC:
                            modifiedMidpointCircle(hdc, xc, yc, radius);
                            line = "modifiedMidpointCircle,"+tostring(xc)+','+tostring(yc)+','+tostring(radius)+','+color_tostring(c);
                            fileContent.push_back(line);
                            break;
                        case DIRECTELLIPSE:
                            a = abs(xc - x);
                            b = abs(yc - y);
                            directEllipse(hdc, xc, yc, a, b);
                            line = "directEllipse,"+tostring(xc)+','+tostring(yc)+','+tostring(a)+','+tostring(b)+','+color_tostring(c);
                            fileContent.push_back(line);
                            cnt = 0;
                            break;
                        case POLARELLIPSE:
                            a = abs(xc - x);
                            b = abs(yc - y);
                            polarEllipse(hdc, xc, yc, a, b);
                            line = "polarEllipse,"+tostring(xc)+','+tostring(yc)+','+tostring(a)+','+tostring(b)+','+color_tostring(c);
                            fileContent.push_back(line);
                            break;
                        case MIDPOINTELLIPSE:
                            a = abs(xc - x);
                            b = abs(yc - y);
                            ellipseMidPoint(hdc, xc, yc, a, b);
                            line = "ellipseMidPoint,"+tostring(xc)+','+tostring(yc)+','+tostring(a)+','+tostring(b)+','+color_tostring(c);
                            fileContent.push_back(line);
                            break;
                        case LINECLIPPINGRECT:
                            CohenSuth(hdc, xc, yc, x, y, 100,50, 400,200);
                            line = "CohenSuth,"+tostring(xc)+','+tostring(yc)+','+tostring(x)+','+tostring(y)+','+tostring(100)+','+tostring(50)+','+tostring(400)+','+tostring(200);
                            fileContent.push_back(line);
                            break;
                        default:
                            break;
                    }
                    cnt = 0;
                }
                else if(cnt == 2)
                {
                    x1 = LOWORD(lParam);
                    y_1 = HIWORD(lParam);
                    cnt++;
                }
                else if(cnt == 3)
                {
                    x2 = LOWORD(lParam);
                    y2 = HIWORD(lParam);
                    switch(algo)
                    {
                        case CONVEX:
                        {
                            Point points [] = {Point(xc, yc), Point(x, y), Point(x1, y_1), Point(x2, y2)};
                            fillPolygon(hdc, points, 4);
                            break;
                        }

                        default:
                            break;
                    }
                    cnt = 0;
                }
                break;

            case WM_CREATE:
                menus(hwnd);
                break;

            case WM_COMMAND:
                cnt = 0;
                switch(LOWORD(wParam))
                {
                    case POINTCLIPPINGRECT:
                        Rectangle(hdc, 100,200, 400,50);
                        algo = POINTCLIPPINGRECT;
                        break;

                    case LINECLIPPINGRECT:
                        Rectangle(hdc, 100,200, 400,50);
                        algo = LINECLIPPINGRECT;
                        break;

                    case RED:
                        c = RGB(255,0,0);
                        break;

                    case YELLOW:
                        c = RGB(255,255,0);
                        break;

                    case BLACK:
                        c = RGB(0,0,0);
                        break;

                    case BLUE:
                        c = RGB(0,0,255);
                        break;

                    case GREEN:
                        c = RGB(0,255,0);
                        break;

                    case HAND:
                        mouse = IDC_HAND;
                        break;

                    case STANDARDARROW:
                        mouse = IDC_ARROW;
                        break;

                    case CROSS:
                        mouse = IDC_CROSS;
                        break;
                    case WAIT:
                        mouse = IDC_WAIT;
                        break;
                    case SAVE:
                        save();
                        break;

                    default:
                        algo = LOWORD(wParam);
                        break;
                    }

                    case WM_SETCURSOR:
                        if (LOWORD(lParam) == HTCLIENT)
                        {
                            SetCursor(LoadCursor(NULL,mouse));
                            return TRUE;
                        }
                        break;

                case WM_DESTROY:
                    PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
                    break;
                default:                      /* for messages that we don't deal with */
                    return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

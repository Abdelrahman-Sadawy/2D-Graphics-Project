#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <iostream>
#include <tchar.h>
#include <math.h>
#include <windows.h>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstdarg>
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
#define CARDINALSPLINE 30
#define FLOODRECURSIVE 31
#define FLOODNONRECURSIVE 32
#define LOAD 33
#define LINECLIPPINGSQUARE 34
#define POINTCLIPPINGSQUARE 35
#define RECTBEZIER 36
#define SQUAREHERMITE 37
#define CLEAR 38
#define POLYGONCLIPPING 39
#define MAXENTRIES 600
using namespace std;

int algo = 0;
COLORREF c;
COLORREF tempC;
LPCSTR mouse = IDC_ARROW;
HMENU hmenu;

//---------------------------
list<string> fileContent;
string line;
#define max 20

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
    string str;
    stream >> str;

    return str;
}

string tostring(COLORREF c)
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

string concatenateString(string funName,int ni, ...)
{
    string temp;
    va_list v;
    va_start(v, ni);
    temp+=funName;
    for(int i=0; i<ni; i++)
    {
        temp+=',';
        int arg = va_arg(v, int);
        temp+= tostring(arg);
    }
    temp+=',';
    va_end(v);
    return temp;
}


string* split (string str, char seperator)
{
    string* strings = new string[max];
    //string strings[max];
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= str.length())
    {
        if (str[i] == seperator || i == str.length())
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            strings[currIndex] = subStr;
            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
    for(int i=currIndex; i<max; i++)
         strings[i] = "";
    return strings;
}

void stringToColor(string color, COLORREF &c)
{

    if(color == "red")
        c = RGB(255,0,0);
    else if(color == "yellow")
        c = RGB(255,255,0);
    else if(color == "black")
        c = RGB(0,0,0);
    else if(color == "blue")
        c = RGB(0,0,255);
    else if(color == "green")
        c = RGB(0,255,0);
}

int toInt(string str)
{
    stringstream ss;

    int num;

    ss << str;

    ss >> num;

    return num;
}



//---------------------------

void printColorOptions()
{
    int color;
    cout<<"Enter a color to begin drawing with:"<<endl;
    cout<<"1- Red"<<endl;
    cout<<"2- Yellow"<<endl;
    cout<<"3- Black"<<endl;
    cout<<"4- Blue"<<endl;
    cout<<"5- Green"<<endl;
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

    printColorOptions();

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
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
    AppendMenu(rectangleClippingMenu, MF_STRING, POLYGONCLIPPING, _T("Polygon"));

    AppendMenu(circleClippingMenu, MF_STRING, POINTCLIPPINCIRCLE, _T("Point"));
    AppendMenu(circleClippingMenu, MF_STRING, LINECLIPPINCIRCLE, _T("Line"));

    HMENU Cardinal = CreateMenu();

    HMENU fillingMenu = CreateMenu();
    AppendMenu(fillingMenu, MF_STRING, LINEFILLING, _T("Line"));
    AppendMenu(fillingMenu, MF_STRING, CIRCLEFILLING, _T("Circle"));

    HMENU fillingPolygonMenu = CreateMenu();
    AppendMenu(fillingPolygonMenu, MF_STRING, CONVEX, _T("Convex"));
    AppendMenu(fillingPolygonMenu, MF_STRING, NONCONVEX, _T("Non-convex"));

    HMENU FloodFill = CreateMenu();
    AppendMenu(FloodFill, MF_STRING, FLOODRECURSIVE, _T("Recursive"));
    AppendMenu(FloodFill, MF_STRING, FLOODNONRECURSIVE, _T("Non Recursive"));

    AppendMenu(squareClippingMenu, MF_STRING, POINTCLIPPINGSQUARE, _T("Point"));
    AppendMenu(squareClippingMenu, MF_STRING, LINECLIPPINGSQUARE, _T("Line"));

    HMENU curveFillingMenu = CreateMenu();
    AppendMenu(curveFillingMenu, MF_STRING, RECTBEZIER, _T("Rectangle"));
    AppendMenu(curveFillingMenu, MF_STRING, SQUAREHERMITE, _T("Square"));

    AppendMenu(hmenu, MF_STRING, SAVE, _T("Save"));
    AppendMenu(hmenu, MF_STRING, LOAD, _T("load"));
    AppendMenu(hmenu, MF_STRING, CLEAR, _T("Clear"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) colorMenu, _T("Color"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) mouseMenu, _T("Mouse"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)LineMenu, _T("Line"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) circleMenu, _T("Circle"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) ellipseMenu, _T("Ellipse"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) clippingMenu, _T("Clipping"));
    AppendMenu(hmenu, MF_STRING, CARDINALSPLINE, "Cardinal Spline");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) fillingMenu, _T("Filling Circle"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) fillingPolygonMenu, _T("Filling Polygon"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)FloodFill, _T("Flood Fill"));
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR) curveFillingMenu, _T("Curve Filling"));
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

struct Point {
    int x, y;
    Point(): x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

void DrawHermiteCurve(HDC hdc, Point& p1, Point& t1, Point& p2, Point& t2)
{
    int a0 = p1.x,
        a1 = t1.x,
        a2 = -3 * p1.x - 2 * t1.x + 3 * p2.x - t2.x,
        a3 = 2 * p1.x + t1.x - 2 * p2.x + t2.x;

    int b0 = p1.y,
        b1 = t1.y,
        b2 = -3 * p1.y - 2 * t1.y + 3 * p2.y - t2.y,
        b3 = 2 * p1.y + t1.y - 2 * p2.y + t2.y;

    for (double t = 0; t <= 1; t += 0.001)
    {
        double tSquare = t * t,
            tCube = tSquare * t;

        double x = a0 + a1 * t + a2 * tSquare + a3 * tCube;
        double y = b0 + b1 * t + b2 * tSquare + b3 * tCube;

        SetPixel(hdc, x, y, c);
    }
}

void CardinalSpline(HDC hdc, vector<Point> P, int n, int c)
{
	Point* T = new Point[n];

	Point t;

	for (int i = 1; i < n - 1; i++) {

		t.x = c / 2 * (P[i + 1].x - P[i - 1].x);
		t.y = c / 2 * (P[i + 1].y - P[i - 1].y);
		T[i] = t;

	}

	t.x = c / 2 * (P[1].x - P[0].x);
	t.y = c / 2 * (P[1].y - P[0].y);

	T[0] = t;

	t.x = c / 2 * (P[n - 1].x - P[n - 2].x);
	t.y = c / 2 * (P[n - 1].y - P[n - 2].y);

	T[n - 1] = t;

	for (int i = 0; i < n - 1; i++) {
		DrawHermiteCurve(hdc, P[i], T[i], P[i + 1], T[i + 1]);
	}

	delete[] T;
}


void FloodFillRec(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillingColor)
{
    COLORREF color = GetPixel(hdc, x, y);
    if (color == borderColor || color == fillingColor) return;
    SetPixel(hdc, x, y, fillingColor);

    FloodFillRec(hdc, x + 1, y, borderColor, fillingColor);
    FloodFillRec(hdc, x - 1, y, borderColor, fillingColor);
    FloodFillRec(hdc, x, y + 1, borderColor, fillingColor);
    FloodFillRec(hdc, x, y - 1, borderColor, fillingColor);
}
void FLoodFillNonRec(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillingColor)
{
    stack<Point> s;
    s.push(Point(x, y));
    while (!s.empty()) {
        Point p = s.top();
        s.pop();
        COLORREF color = GetPixel(hdc, p.x, p.y);
        if (color == borderColor || color == fillingColor)
            continue;
        SetPixel(hdc, p.x, p.y, fillingColor);
        s.push(Point(p.x + 1, p.y));
        s.push(Point(p.x - 1, p.y));
        s.push(Point(p.x, p.y + 1));
        s.push(Point(p.x, p.y - 1));
    }
}

// convex polygon filling

typedef struct
{
    int xLeft, xRight;
} edgeTable[800];

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

void polygon2Table (vector<Point> points, int n, edgeTable table)
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

void fillPolygon (HDC hdc, vector<Point> points, int n)
{
    edgeTable table;
    initEdgeTable(table);
    polygon2Table(points, n, table);
    table2Screen(hdc, table);

}

//Non convex polygon filling
struct EdgeRec
{
    double x;
    double minv;
    int ymax;
    bool operator<(EdgeRec r)
    {
        return x<r.x;
    }
};
typedef list<EdgeRec> EdgeList;

EdgeRec InitEdgeRec(Point& v1,Point& v2)
{
     if(v1.y>v2.y)
        swap(v1,v2);
    EdgeRec rec;
    rec.x = v1.x;
    rec.ymax = v2.y;
    rec.minv = (double)(v2.x-v1.x)/(v2.y-v1.y);
    return rec;
}

void InitEdgeTable(vector<Point> polygon,int n,EdgeList table[])
{
    Point v1=polygon[n-1];
    for(int i=0;i<n;i++)
    {
        Point v2=polygon[i];
        if(v1.y==v2.y)
        {
            v1=v2;
            continue;
        }
        EdgeRec rec = InitEdgeRec(v1, v2);
        table[v1.y].push_back(rec);
        v1 = polygon[i];
    }
}

void NonConvexPolygonFill(HDC hdc, vector<Point> polygon, int n)
{
    EdgeList *table = new EdgeList [MAXENTRIES];
    InitEdgeTable(polygon, n, table);
    int y = 0;
    while(y < MAXENTRIES && table[y].size()== 0)
        y++;
    if(y == MAXENTRIES)
        return;
    EdgeList ActiveList = table[y];
    while (ActiveList.size()>0)
    {
        ActiveList.sort();
        for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
        {
            int x1 = (int)ceil(it->x);
            it++;
            int x2 = (int)floor(it->x);
            for(int x = x1; x <= x2; x++)
                SetPixel(hdc, x, y, c);
        }

        y++;
        EdgeList::iterator it=ActiveList.begin();

        while(it!=ActiveList.end())
            if(y==it->ymax)
                it=ActiveList.erase(it);
            else
                it++;

        for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
            it->x+=it->minv;

        ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
    }
    delete[] table;
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

//////////////horizontal filling
void DrawModifiedHermiteCurve(HDC hdc, Point& p1, Point& t1, Point& p2, Point& t2, int xl, int yt, int xr, int yb)
{
    int a0 = p1.x,
        a1 = t1.x,
        a2 = -3 * p1.x - 2 * t1.x + 3 * p2.x - t2.x,
        a3 = 2 * p1.x + t1.x - 2 * p2.x + t2.x;

    int b0 = p1.y,
        b1 = t1.y,
        b2 = -3 * p1.y - 2 * t1.y + 3 * p2.y - t2.y,
        b3 = 2 * p1.y + t1.y - 2 * p2.y + t2.y;

    for (double t = 0; t <= 1; t += 0.001)
    {
        double tSquare = t * t,
            tCube = tSquare * t;

        double x = a0 + a1 * t + a2 * tSquare + a3 * tCube;
        double y = b0 + b1 * t + b2 * tSquare + b3 * tCube;

        if(Round(x) > xl && Round(x) < xr-1 && Round(y) > yt && Round(y) < yb-1)
            SetPixel(hdc, Round(x), Round(y), c);

    }
}

void DrawBezierCurve(HDC hdc, Point p0, Point p1, Point p2, Point p3, int xl, int yt, int xr, int yb) {
	Point t1, t2;
	t1.x = 3 * (p1.x - p0.x);
	t1.y = 3 * (p1.y - p0.y);
	t2.x = 3 * (p3.x - p2.x);
	t2.y = 3 * (p3.y - p2.y);
	DrawModifiedHermiteCurve(hdc, p0, t1, p3, t2, xl, yt, xr, yb);
}


void fillHorizontal (HDC hdc, int xl, int yt, int xr, int yb)
{
    for(int y = yt+1; y < yb ; y++)
    {
        Point p1(xl+1, y);
        Point p2(xr-1, y);
        Point t1(xl+50, y-40);
        Point t2(xr+10, y-50);
        DrawBezierCurve(hdc, p1, t1, p2, t2, xl, yt, xr, yb);
    }

}
/////////////////////////////Vertical Filling
void fillVertical (HDC hdc, int xl, int yt, int xr, int yb)
{
    for(int x = xl+1; x < xr ; x++)
    {
        Point p1(x, yt+1);
        Point p2(x, yb-1);
        Point t1(x+50, yt+40);
        Point t2(x+10, yb-50);
        DrawModifiedHermiteCurve(hdc, p1, t1, p2, t2, xl, yt, xr, yb);
    }

}

/////////////////////////polygon clipping

struct Vertex
{
    double x,y;
    Vertex(int x1=0,int y1=0)
    {
        x=x1;
        y=y1;
    }
};
typedef vector<Vertex> VertexList;
typedef bool(*IsInFunc)(Vertex& v,int edge);
typedef Vertex(*IntersectFunc)(Vertex& v1,Vertex& v2,int edge);

VertexList ClipWithEdge(VertexList p,int edge,IsInFunc In,IntersectFunc Intersect)
{
    VertexList OutList;
    Vertex v1=p[p.size()-1];
    bool v1_in=In(v1,edge);
    for(int i=0;i<(int)p.size();i++)
    {
        Vertex v2=p[i];
        bool v2_in=In(v2,edge);
        if(!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1,v2,edge));
            OutList.push_back(v2);
        }
        else if(v1_in && v2_in)
            OutList.push_back(v2);
        else if(v1_in)
            OutList.push_back(Intersect(v1,v2,edge));
        v1=v2;
        v1_in=v2_in;
        }
        return OutList;
    }
bool InLeft(Vertex& v,int edge)
{
    return v.x>=edge;
}
bool InRight(Vertex& v,int edge)
{
    return v.x<=edge;
}
bool InTop(Vertex& v,int edge)
{
    return v.y>=edge;
}
bool InBottom(Vertex& v,int edge)
{
    return v.y<=edge;
}

Vertex VIntersect(Vertex& v1,Vertex& v2,int xedge)
{
    Vertex res;
    res.x = xedge;
    res.y = v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return res;
}
Vertex HIntersect(Vertex& v1,Vertex& v2,int yedge)
{
    Vertex res;
    res.y = yedge;
    res.x = v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return res;
}

void PolygonClip(HDC hdc, vector<Point> p,int n,int xleft,int ytop,int xright,int ybottom)
{
    VertexList vlist;
    for(int i=0;i<n;i++)
        vlist.push_back(Vertex(p[i].x,p[i].y));
    vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);

    Vertex v1=vlist[vlist.size()-1];
    for(int i=0;i<(int)vlist.size();i++)
    {
        Vertex v2 = vlist[i];

        MoveToEx(hdc,Round(v1.x),Round(v1.y),NULL);
        //LineTo(hdc,Round(v2.x), Round(v2.y));
        LineParametric(hdc,Round(v1.x),Round(v1.y),Round(v2.x), Round(v2.y));
        v1=v2;
    }
}
/*  This function is called by the Windows function DispatchMessage()  */



//---------------------------------------------------
void callFunc(string* functionData, HDC hdc)
{
    string funName = functionData[0];

    int ctr = 0;
    for(int i=0;i<max;i++)
        if(functionData[i]!="")
            ctr++;
    stringToColor(functionData[ctr-1], c);

    int a = toInt(functionData[1]);
    int b = toInt(functionData[2]);
    int c = toInt(functionData[3]);
    int d = toInt(functionData[4]);
    int e = toInt(functionData[5]);
    int f = toInt(functionData[6]);
    int g = toInt(functionData[7]);
    int h = toInt(functionData[8]);

    if(funName=="LineDDA")  //LineDDA(hdc, xc, yc, x, y)
        LineDDA(hdc, a, b, c, d);
    else if(funName=="FloodFillRec") //FloodFillRec(hdc, x, y, tempC, c);
    {
        stringToColor(functionData[3], tempC);
        //stringToColor(functionData[4], c);
        FloodFillRec(hdc, a, b, tempC, c);
    }
    else if(funName=="FLoodFillNonRec")
    {
        stringToColor(functionData[3], tempC);
        //stringToColor(functionData[4], c);
        FLoodFillNonRec(hdc, a, b, tempC, c);
    }
    else if(funName=="pointClippingCircle")
        pointClippingCircle(hdc, a, b, c, d, e);
    else if(funName=="PointClippingRect")
        PointClippingRect(hdc, a, b, c, d, e, g);
    else if(funName=="circleFillingLine")
        circleFillingLine(hdc, a, b, c, d, e);
    else if(funName=="circleFillingCircle")
        circleFillingCircle(hdc, a, b, c, d, e);
    else if(funName=="lineClippingCircle")
        lineClippingCircle(hdc, a, b, c, d, e, f, g);
    else if(funName=="LineMidPoint")
        LineMidPoint(hdc, a, b, c, d);
    else if(funName=="LineParametric")
        LineParametric(hdc, a, b, c, d);
    else if(funName=="circleDirect")
        circleDirect(hdc, a, b, c);
    else if(funName=="circlePolar")
        circlePolar(hdc, a, b, c);
    else if(funName=="circleIterative")
        circleIterative(hdc, a, b, c);
    else if(funName=="midpointCircle")
        midpointCircle(hdc, a, b, c);
    else if(funName=="modifiedMidpointCircle")
        modifiedMidpointCircle(hdc, a, b, c);
    else if(funName=="directEllipse")
        directEllipse(hdc, a, b, c, d);
    else if(funName=="polarEllipse")
        polarEllipse(hdc, a, b, c, d);
    else if(funName=="ellipseMidPoint")
        ellipseMidPoint(hdc, a, b, c, d);
    else if(funName=="CohenSuth")
        CohenSuth(hdc, a, b, c, d, e, f, g, h);
    else if(funName=="PointClippingRect")
        PointClippingRect(hdc, a, b, c, d, e, f);
    else if(funName=="fillHorizontal")
        fillHorizontal(hdc, a, b, c,d);
    else if(funName=="fillVertical")
        fillVertical(hdc, a, b, c,d);

    else if(funName=="CardinalSpline")
    {
        vector<Point> vect;
        for(int i=3; i<3+(2*a);i+=2)
        {
            Point p(toInt(functionData[i]),toInt(functionData[i+1]));
            vect.push_back(p);
        }
        CardinalSpline(hdc, vect, a, b);
    }
    else if(funName=="fillPolygon")
    {
        vector<Point> vect;
        for(int i=2; i<2+(2*a);i+=2)
        {
            Point p(toInt(functionData[i]),toInt(functionData[i+1]));
            vect.push_back(p);
        }
        fillPolygon(hdc, vect, a);
    }


}
void load(HDC hdc)
{
    string myText;

    char seperator = ',';

    ifstream MyReadFile("Commands.txt");

    while (getline (MyReadFile, myText)) {

        string* functionData = split(myText,seperator);

        callFunc(functionData, hdc);
    }

    MyReadFile.close();
}
//-------------------------------------------------

int cnt = 0, xc, yc, x, y, radius,x1,y_1, x2,y2, a, b;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    static vector<Point> cardinalVector;
	static int cardinalCtr = 0;
	static vector<Point> convexVector;
	static int convexCtr = 0;
	static vector<Point> polygonVector;
    static int polygonCtr = 0;
    switch (message)                  /* handle the messages */
    {
        case WM_RBUTTONDOWN:
            if (algo == CARDINALSPLINE) {
                cardinalVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                cardinalCtr++;
                CardinalSpline(hdc, cardinalVector, cardinalCtr, 2);
                line = concatenateString("CardinalSpline",2,cardinalCtr,2);
                for(std::size_t i = 0; i < cardinalVector.size(); ++i)
                {
                    line+=tostring(cardinalVector[i].x);
                    line= line + ',' + tostring(cardinalVector[i].y)+',';
                }
                line+=tostring(c);
                fileContent.push_back(line);
                cardinalCtr = 0;
                cardinalVector.clear();
            }
            else if (algo == CONVEX) {
                convexVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                convexCtr++;
                fillPolygon(hdc, convexVector, convexCtr);
                line = concatenateString("fillPolygon",1,convexCtr);
                for(std::size_t i = 0; i < convexVector.size(); ++i)
                {
                    line+=tostring(convexVector[i].x);
                    line= line + ',' + tostring(convexVector[i].y)+',';
                }
                line+=tostring(c);
                fileContent.push_back(line);
                convexCtr = 0;
                convexVector.clear();
            }
            else if(algo == NONCONVEX)
            {
                polygonVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                polygonCtr++;
                NonConvexPolygonFill(hdc, polygonVector, polygonCtr);
                polygonCtr = 0;
                polygonVector.clear();
            }
            else if(algo == POLYGONCLIPPING)
            {
                polygonVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                polygonCtr++;
                cout<<"Right here\n";
                PolygonClip(hdc, polygonVector, polygonCtr, 100, 50, 400, 200);
                polygonCtr = 0;
                polygonVector.clear();
            }
            if(cnt == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                cnt++;
                if (algo == FLOODRECURSIVE) {
                    FloodFillRec(hdc, x, y, tempC, c);
                    line = concatenateString("FloodFillRec", 2, x,  y) + tostring(tempC) +','+ tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if (algo == FLOODNONRECURSIVE) {
                    FLoodFillNonRec(hdc, x, y, tempC, c);
                    line = concatenateString("FLoodFillNonRec", 2, x,  y) + tostring(tempC) +','+ tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                if(algo == POINTCLIPPINCIRCLE)
                {
                    pointClippingCircle(hdc, x,  y,  xc,  yc,  radius);
                    line = concatenateString("pointClippingCircle", 5, x,  y,  xc, yc, radius) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == POINTCLIPPINGRECT)
                {
                    PointClippingRect(hdc, x, y, 100, 50, 400, 200);
                    line = concatenateString("PointClippingRect", 6, x,  y,  100, 50, 400, 200) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == LINEFILLING)
                {
                    circleFillingLine(hdc, x, y, xc, yc, radius);
                    line = concatenateString("circleFillingLine", 5, x,  y,  xc, yc, radius) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == CIRCLEFILLING)
                {
                    circleFillingCircle(hdc, x, y, xc, yc, radius);
                    line = concatenateString("circleFillingCircle", 5, x,  y,  xc, yc, radius) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == POINTCLIPPINGSQUARE)
                {
                    //(hdc,150, 100, 350, 300);
                    PointClippingRect(hdc, x, y, 150,100, 350,300);
                    line = concatenateString("PointClippingRect", 6, x,  y,  150,100, 350,300) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == RECTBEZIER)
                {
                    fillHorizontal(hdc, 100,50, 400,200);
                    line = concatenateString("fillHorizontal", 4, 100,50, 400,200) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
                else if(algo == SQUAREHERMITE)
                {
                    fillVertical(hdc, 150,100, 350,300);
                    line = concatenateString("fillVertical", 4, 150,100, 350,300) + tostring(c);
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
                    line = concatenateString("lineClippingCircle", 7, x, y, x2, y2, xc, yc, radius) + tostring(c);
                    fileContent.push_back(line);
                    cnt = 0;
                }
            }
            break;

        case WM_LBUTTONDOWN:
            if (algo == CARDINALSPLINE) {
                cardinalVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                cardinalCtr++;
            }
            else if (algo == CONVEX) {
                convexVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                convexCtr++;
            }
            else if(algo == NONCONVEX)
            {
                polygonVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                polygonCtr++;
            }
            else if(algo == POLYGONCLIPPING)
            {
                polygonVector.push_back(Point(LOWORD(lParam), HIWORD(lParam)));
                polygonCtr++;
            }
            else if(cnt == 0)
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
                        line = concatenateString("LineDDA", 4, xc, yc, x, y) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case LINEMIDPOINT:
                        LineMidPoint(hdc, xc, yc, x, y);
                        line = concatenateString("LineMidPoint", 4, xc, yc, x, y) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case LINEPARAMETRIC:
                        LineParametric(hdc, xc, yc, x, y);
                        line = concatenateString("LineParametric", 4, xc, yc, x, y) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case DirectC:
                        circleDirect(hdc, xc, yc, radius);
                        line = concatenateString("circleDirect", 3, xc, yc, radius) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case PolarC:
                        circlePolar(hdc, xc, yc, radius);
                        line = concatenateString("circlePolar", 3, xc, yc, radius) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case ItPolarC:
                        circleIterative(hdc, xc, yc, radius);
                        line = concatenateString("circleIterative", 3, xc, yc, radius) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case MidpointC:
                        midpointCircle(hdc, xc, yc, radius);
                        line = concatenateString("midpointCircle", 3, xc, yc, radius) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case ModifiedMidpointC:
                        modifiedMidpointCircle(hdc, xc, yc, radius);
                        line = concatenateString("modifiedMidpointCircle", 3, xc, yc, radius) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case DIRECTELLIPSE:
                        a = abs(xc - x);
                        b = abs(yc - y);
                        directEllipse(hdc, xc, yc, a, b);
                        line = concatenateString("directEllipse", 4, xc, yc, a, b) + tostring(c);
                        fileContent.push_back(line);
                        cnt = 0;
                        break;
                    case POLARELLIPSE:
                        a = abs(xc - x);
                        b = abs(yc - y);
                        polarEllipse(hdc, xc, yc, a, b);
                        line = concatenateString("polarEllipse", 4, xc, yc, a, b) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case MIDPOINTELLIPSE:
                        a = abs(xc - x);
                        b = abs(yc - y);
                        ellipseMidPoint(hdc, xc, yc, a, b);
                        line = concatenateString("ellipseMidPoint", 4,  xc, yc, a, b) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case LINECLIPPINGRECT:
                        CohenSuth(hdc, xc, yc, x, y, 100, 50, 400, 200);
                        line = concatenateString("CohenSuth", 8, xc, yc, x, y, 100, 50, 400, 200) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    case LINECLIPPINGSQUARE:
                        CohenSuth(hdc, xc, yc, x, y, 150,100, 350,300);
                        line = concatenateString("CohenSuth", 8, xc, yc, x, y, 150, 100, 350, 300) + tostring(c);
                        fileContent.push_back(line);
                        break;
                    default:
                        break;
                }
                tempC = c;
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
                    case CLEAR:
                    {
                        ofstream file("Commands.txt");
                        InvalidateRect(hwnd, NULL, true);
                        break;
                    }
                    case POINTCLIPPINGRECT:
                    {
                        Rectangle(hdc, 100,200, 400,50);
                        algo = POINTCLIPPINGRECT;
                        break;
                    }
                    case LINECLIPPINGRECT:
                    {
                        Rectangle(hdc, 100,200, 400,50);
                        algo = LINECLIPPINGRECT;
                        break;
                    }
                    case LINECLIPPINGSQUARE:
                    {
                        Rectangle(hdc,150, 100, 350, 300);
                        algo = LINECLIPPINGSQUARE;
                        break;
                    }
                    case POINTCLIPPINGSQUARE:
                    {
                        Rectangle(hdc,150, 100, 350, 300);
                        algo = POINTCLIPPINGSQUARE;
                        break;
                    }
                    case RECTBEZIER:
                    {
                        Rectangle(hdc, 100,200, 400,50);
                        algo = RECTBEZIER;
                        break;
                    }

                    case SQUAREHERMITE:
                    {
                        Rectangle(hdc,150, 100, 350, 300);
                        algo = SQUAREHERMITE;
                        break;
                    }

                    case POLYGONCLIPPING:
                    {
                        Rectangle(hdc, 100,200, 400,50);
                        algo = POLYGONCLIPPING;
                        break;

                    }

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
                    case LOAD:
                        load(hdc);
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

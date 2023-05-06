
#include "graphics.h"
#pragma comment(lib,"LibBGI.lib")
#include <limits.h>
#include <math.h>
#define PI 3.14159265
using namespace std;
struct dot {
    float x;
    float y;
    float z;
    
};


void drawLine(dot d1, dot d2, dot center = {800, 500, 400}, int color = 15) {
    int x1 = -d1.x * cos(7 * PI / 180) + d1.y*cos(41*PI/180) + center.x;
    int y1 = -d1.z + d1.x * sin(7 * PI / 180) + d1.y * sin(41 * PI / 180) + center.y;
    int x2 = -d2.x * cos(7 * PI / 180) + d2.y * cos(41 * PI / 180) + center.x;
    int y2 = -d2.z + d2.x * sin(7 * PI / 180) + d2.y * sin(41 * PI / 180) + center.y;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = 0;
    int deltaErr = ((deltaX > deltaY) ? deltaY : deltaX) + 1;
    putpixel(x2, y2, color);
    if (deltaX > deltaY) {
        for (x1; x1 != x2; (x2 > x1) ? x1++ : x1--) {
            putpixel(x1, y1, color);
            error += deltaErr;
            if (error >= deltaX + 1) {
                y1 += signY;
                error = error - (deltaX + 1);
            }
        }
    }
    else {
        for (y1; y1 != y2; (y2 > y1) ? y1++ : y1--) {
            putpixel(x1, y1, color);
            error += deltaErr;
            if (error >= deltaY + 1) {
                x1 += signX;
                error = error - (deltaY + 1);
            }
        }
    }
    setcolor(15);
}
void plotCoordsLines() {
    struct dot zero = { 0, 0, 0 };
    struct dot endX = { 500, 0, 0 };
    struct dot endY = { 0, 500, 0 };
    struct dot endZ = { 0, 0, 400 };
    drawLine(zero, endX);
    drawLine(zero, endY);
    drawLine(zero, endZ);
}
void drawFigure(dot* dots) {
    drawLine(dots[0], dots[1]);
    drawLine(dots[0], dots[2]);
    drawLine(dots[0], dots[3]);
    drawLine(dots[0], dots[4]);
    drawLine(dots[1], dots[2]);
    drawLine(dots[2], dots[3]);
    drawLine(dots[3], dots[4]);
    drawLine(dots[4], dots[1]);
}
void shift(dot* dots, int dx, int dy, int dz) {
    for (int i = 0; i < 5; i++) {
        dots[i].x += dx;
        dots[i].y += dy;
        dots[i].z += dz;
    }
}
void scale(dot* dots, float c) {
    for (int i = 0; i < 5; i++) {
        dots[i].x = dots[i].x * c;
        dots[i].y = dots[i].y * c;
        dots[i].z = dots[i].z * c;
    }
}
void rotate(dot* dots, int angle) {
    float ox = (dots[1].x + dots[2].x + dots[3].x + dots[4].x) / 4;
    float oy = (dots[1].y + dots[2].y + dots[3].y + dots[4].y) / 4;
    float s = sin(angle * 3.14 / 180);
    float c = cos(angle * 3.14 / 180);
    float x = 0;
    float y = 0;
    x = dots[1].x;
    y = dots[1].y;
    dots[1].x = (x - ox) * c - (y - oy) * s + ox;
    dots[1].y = (x - ox) * s + (y - oy) * c + oy;
    x = dots[2].x;
    y = dots[2].y;
    dots[2].x = (x - ox) * c - (y - oy) * s + ox;
    dots[2].y = (x - ox) * s + (y - oy) * c + oy;
    x = dots[3].x;
    y = dots[3].y;
    dots[3].x = (x - ox) * c - (y - oy) * s + ox;
    dots[3].y = (x - ox) * s + (y - oy) * c + oy;
    x = dots[4].x;
    y = dots[4].y;
    dots[4].x = (x - ox) * c - (y - oy) * s + ox;
    dots[4].y = (x - ox) * s + (y - oy) * c + oy;
}

int main()
{
    struct dot v0 = { 150, 150, 300 };
    struct dot v1 = { 350, 50, 0 };
    struct dot v2 = { 350, 350, 0 };
    struct dot v3 = { 50, 350, 0 };
    struct dot v4 = { 50, 50, 0 };
    struct dot dots[5] = { v0, v1, v2, v3, v4 };
    
    
    
    initwindow(1600, 1000, "LAB4", 0, 0, false);
    outtext(_strdup("Стрелки + Z и X - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; 0 - Выход."));
    plotCoordsLines();
    drawFigure(dots);


   int  c = (char)getch();


    
   do {
       clearviewport();
       outtext(_strdup("Стрелки + Z и X - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; 0 - Выход."));
       plotCoordsLines();
       drawFigure(dots);
        c = (char)getch();
       
       
        switch (c) {
        case (KEY_UP):
            shift(dots, 0, -15, 0);
            break;
        case (KEY_DOWN):
            shift(dots, 0, +15, 0);
            break;
        case (KEY_LEFT):
            shift(dots, +15, 0, 0);
            break;
        case (KEY_RIGHT):
            shift(dots, -15, 0, 0);
            break;
        case '4':
            shift(dots, 0, 0, 15);
            break;
        case '1':
            shift(dots, 0, 0, -15);
            break;
        case 'i':
            scale(dots, 1.1);
            break;
        case 'o':
            scale(dots, 0.9);
            break;
        case 'r':
            rotate(dots, 15);
            break;

        }
        
    } while (c != '0');
    
}

#include "graphics.h"
#pragma comment(lib,"LibBGI.lib")
#include <limits.h>
#include <math.h>
#define PI 3.14159265
#define angdx 7 * PI / 180
#define angdy 41 * PI / 180
using namespace std;
struct dot {
    float x;
    float y;
    float z;
};



void drawLine(dot d1, dot d2, int color = 15, dot center = { 800, 500, 400 }) {
    int x1 = -d1.x * cos(angdx) + d1.y*cos(angdy) + center.x;
    int y1 = -d1.z + d1.x * sin(angdx) + d1.y * sin(angdy) + center.y;
    int x2 = -d2.x * cos(angdx) + d2.y * cos(angdy) + center.x;
    int y2 = -d2.z + d2.x * sin(angdx) + d2.y * sin(angdy) + center.y;
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
    drawLine(zero, endX, 8);
    drawLine(zero, endY, 8);
    drawLine(zero, endZ, 8);
}
float vec_cos(dot d1, dot d2) {
    return (d1.x * d2.x + d1.y * d2.y + d1.z * d2.z) / (sqrt(d1.x * d1.x + d1.y * d1.y + d1.z * d1.z) * sqrt(d2.x * d2.x + d2.y * d2.y + d2.z * d2.z));
}
dot convert3dto2d(dot d) {
    dot center = { 800, 500, 400 };
    struct dot dd = {-d.x * cos(angdx) + d.y * cos(angdy) + center.x, -d.z + d.x * sin(angdx) + d.y * sin(angdy) + center.y, 0};
    return dd;
}
void fill(int x, int y, int color = 15) {
    int p = getpixel(x, y);
    if (p == 0 || p == 8) {
        putpixel(x, y, color);
        fill(x, y - 1, color);
        fill(x - 1, y, color);
        fill(x + 1, y, color);
        fill(x, y + 1, color);
    }
}

void drawFigure(dot* dots) {
    struct dot vec1;
    struct dot vec2;
    struct dot result_vec;
    struct dot faceVector = { cos(angdy) / cos(angdx) / (sin(angdy) + sin(angdx) * cos(angdy) / cos(angdx)), 1 / (sin(angdy) + sin(angdx) * cos(angdy) / cos(angdx)), 1 };
    vec1 = { dots[1].x - dots[0].x,dots[1].y - dots[0].y, dots[1].z - dots[0].z }; // face 1
    vec2 = { dots[2].x - dots[0].x,dots[2].y - dots[0].y, dots[2].z - dots[0].z };
    result_vec = { vec1.y * vec2.z - vec2.y * vec1.z, vec2.x * vec1.z - vec1.x * vec2.z, vec1.x * vec2.y - vec2.x * vec1.y };
    if (vec_cos(result_vec, faceVector) > 0) {
        drawLine(dots[0], dots[1]);
        drawLine(dots[1], dots[2]);
        drawLine(dots[2], dots[0]);
        int x = (convert3dto2d(dots[0]).x + convert3dto2d(dots[1]).x + convert3dto2d(dots[2]).x) / 3;
        int y = (convert3dto2d(dots[0]).y + convert3dto2d(dots[1]).y + convert3dto2d(dots[2]).y) / 3;
        fill(x, y, 4);
        outtextxy(x, y, _strdup ("Грань 1"));

    }
    vec1 = { dots[2].x - dots[0].x,dots[2].y - dots[0].y, dots[2].z - dots[0].z }; // face 2
    vec2 = { dots[3].x - dots[0].x,dots[3].y - dots[0].y, dots[3].z - dots[0].z };
    result_vec = { vec1.y * vec2.z - vec2.y * vec1.z, vec2.x * vec1.z - vec1.x * vec2.z, vec1.x * vec2.y - vec2.x * vec1.y };
    if (vec_cos(result_vec, faceVector) > 0) {
        drawLine(dots[0], dots[2]);
        drawLine(dots[2], dots[3]);
        drawLine(dots[3], dots[0]);
        int x = (convert3dto2d(dots[0]).x + convert3dto2d(dots[2]).x + convert3dto2d(dots[3]).x) / 3;
        int y = (convert3dto2d(dots[0]).y + convert3dto2d(dots[2]).y + convert3dto2d(dots[3]).y) / 3;
        fill(x, y, 1);
        outtextxy(x, y, _strdup("Грань 2"));
        
    }
    vec1 = { dots[3].x - dots[0].x,dots[3].y - dots[0].y, dots[3].z - dots[0].z }; // face 3
    vec2 = { dots[4].x - dots[0].x,dots[4].y - dots[0].y, dots[4].z - dots[0].z };
    result_vec = { vec1.y * vec2.z - vec2.y * vec1.z, vec2.x * vec1.z - vec1.x * vec2.z, vec1.x * vec2.y - vec2.x * vec1.y };
    if (vec_cos(result_vec, faceVector) > 0) {
        drawLine(dots[0], dots[3]);
        drawLine(dots[3], dots[4]);
        drawLine(dots[4], dots[0]);
        int x = (convert3dto2d(dots[0]).x + convert3dto2d(dots[3]).x + convert3dto2d(dots[4]).x) / 3;
        int y = (convert3dto2d(dots[0]).y + convert3dto2d(dots[3]).y + convert3dto2d(dots[4]).y) / 3;
        fill(x, y, 2);
        outtextxy(x, y, _strdup("Грань 3"));
    }
    vec1 = { dots[4].x - dots[0].x,dots[4].y - dots[0].y, dots[4].z - dots[0].z }; // face 4
    vec2 = { dots[1].x - dots[0].x,dots[1].y - dots[0].y, dots[1].z - dots[0].z };
    result_vec = { vec1.y * vec2.z - vec2.y * vec1.z, vec2.x * vec1.z - vec1.x * vec2.z, vec1.x * vec2.y - vec2.x * vec1.y };
    if (vec_cos(result_vec, faceVector) > 0) {
        drawLine(dots[0], dots[1]);
        drawLine(dots[1], dots[4]);
        drawLine(dots[4], dots[0]);
        int x = (convert3dto2d(dots[0]).x + convert3dto2d(dots[1]).x + convert3dto2d(dots[4]).x) / 3;
        int y = (convert3dto2d(dots[0]).y + convert3dto2d(dots[1]).y + convert3dto2d(dots[4]).y) / 3;
        fill(x, y, 14);
        outtextxy(x, y, _strdup("Грань 4"));
    }
    vec1 = { dots[4].x - dots[1].x,dots[4].y - dots[1].y, dots[4].z - dots[1].z }; // face 5
    vec2 = { dots[2].x - dots[1].x,dots[2].y - dots[1].y, dots[2].z - dots[1].z };
    result_vec = { vec1.y * vec2.z - vec2.y * vec1.z, vec2.x * vec1.z - vec1.x * vec2.z, vec1.x * vec2.y - vec2.x * vec1.y };
    if (vec_cos(result_vec, faceVector) > 0) {
        drawLine(dots[1], dots[2]);
        drawLine(dots[2], dots[3]);
        drawLine(dots[3], dots[4]);
        drawLine(dots[4], dots[1]);
        int x = (convert3dto2d(dots[0]).x + convert3dto2d(dots[1]).x + convert3dto2d(dots[2]).x) / 3;
        int y = (convert3dto2d(dots[0]).y + convert3dto2d(dots[1]).y + convert3dto2d(dots[2]).y) / 3;
        fill(x, y, 8);
        outtextxy(x, y, _strdup("Грань 5"));
    }
    
    swapbuffers();

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
    struct dot v0 = { 200, 200, 300 };
    struct dot v1 = { 350, 50, 0 };
    struct dot v2 = { 350, 350, 0 };
    struct dot v3 = { 50, 350, 0 };
    struct dot v4 = { 50, 50, 0 };
    struct dot dots[5] = { v0, v1, v2, v3, v4 };
   
    
    
    
    initwindow(1600, 1000, "LAB4", 0, 0, true);
    
    outtext(_strdup("Стрелки + 1 и 4 - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; 0 - Выход."));
    plotCoordsLines();
    drawFigure(dots);


   int  c = (char)getch();


    
   do {
       clearviewport();
       outtext(_strdup("Стрелки + 1 и 4 - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; 0 - Выход."));
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
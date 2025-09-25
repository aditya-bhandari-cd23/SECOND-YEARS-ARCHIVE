#include<lpc214x.h>
#define LED_OFF IO0SET = 1<<31
#define LED_ON  IO0CLR = 1<<31
#define COL0 (IO1PIN & (1 << 19))
#define COL1 (IO1PIN & (1 << 18))
#define COL2 (IO1PIN & (1 << 17))
#define COL3 (IO1PIN & (1 << 16))

void delayMs(int x)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < 10000; j++);
}

char lookUp[4][4] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

int main()
{
    uartInit();
    int row, col;
    IO1DIR = 1 << 31 | 0x00FF0000;

    while (1) {
        for (row = 0; row < 4; row++) {
            IO0SET = 0x00FF0000;
            IO0CLR = 1 << (16+row);
            if (!COL0) { col = 0; break; }
            if (!COL1) { col = 1; break; }
            if (!COL2) { col = 2; break; }
            if (!COL3) { col = 3; break; }
        }

        while (!COL0 || !COL1 || !COL2 || !COL3);
        U0THR = lookUp[row][col];////////////////////////////////////////
    }
}

void uartInit()
{
    PINSEL1 = 0x5;
    U0LCR = 0x83
    U0DLM = 0x0
    U0DLL = 0x8
    U0LCR = 0x3
    U0FCR = 0x7
}

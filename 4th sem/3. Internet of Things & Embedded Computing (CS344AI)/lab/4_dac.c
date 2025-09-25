#include<lpc214x.h>
#include <math.h>
#define LED_OFF IO0SET = 1<<31
#define LED_ON  IO0CLR = 1<<31
#define SW2 = IO0PIN & 1 << 14
#define SW3 = IO0PIN & 1 << 15
#define SW4 = IO1PIN & 1 << 18
#define SW5 = IO1PIN & 1 << 19
#define SW6 = IO1PIN & 1 << 20

void delayMs(int x)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < 10000; j++);
}

int sin[60];
int rectSin[30];

void makeTables()
{
    int i;
    for (i = 0; i < 60; i++)
        sin[i] = 512 + 511 * sin(i*6);
    for (i = 0; i < 30; i++)
        rectSin[i] = 512 + 511 * sin(i*6);
}

int main()
{
    int i, val;
    IO0DIR |= 1 << 31 | 0x00FF0000;

    while (1) {
        if (!SW2) 
            for (i = 0; i < 60; i++) {
                val = sin[i];
                DACR = (1 << 16) & (val << 6);
            }
        else if (!SW3) 
            for (i = 0; i < 30; i++) {
                val = rectSin[i];
                DACR = (1 << 16) | (val << 6); //////////////////////////////////
            }
        else if (!SW4) {
            for (i = 0; i < 1023; i++) 
                DACR = (1 << 16) | (i << 6); //////////////////////////////////
            for (i = 1023; i >= 0; i--) 
                DACR = (1 << 16) | (i << 6); //////////////////////////////////
        }
        else if (!SW5) {
            for (i = 0; i < 1023; i++) 
                DACR = (1 << 16) | (i << 6); //////////////////////////////////
        }
        else if (!SW6) {
            DACR = (1 << 16) | (1023 << 6); //////////////////////////////////
            delayMs(10);
            DACR = (1 << 16) | (0 << 6); //////////////////////////////////
            delayMs(10);
        }
        else {
            DACR = (1 << 16) | (1023 << 6); //////////////////////////////////
        }
    }
}

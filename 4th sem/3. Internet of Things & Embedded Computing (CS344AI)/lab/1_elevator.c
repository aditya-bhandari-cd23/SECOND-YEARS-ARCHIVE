#include<lpc214x.h>
#define LED_OFF IO0SET = 1<<31
#define LED_ON  IO0CLR = 1<<31

void delayMs(int x)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < 10000; j++);
}

void elevator()
{
    int i, val, counter = 0xF;
    IO1CLR = 1 << 24;/////////////////////////////////////////////////////////////
    while (1) {
        IO0CLR = 0x00F00000;
        IO0SET = 0x00F00000;///////////////////////////////////////////////////////
        while (counter == 0xF)
            counter = (IO1PIN >> 16) & 0xF;////////////////////////////////////////
        if (counter == 0xe)
            val = 3;
        else if (counter == 0xd)
            val = 6;
        else if (counter == 0xb)
            val = 8;
        else if (counter == 0x7)
            val = 10;

        for (i = 0; i < val; i++) {
            IO0CLR = 0x000F0000;
            IO0SET = i << val;//////////////////////////////////////////////////////
            delayMs(100);
        }

        for (i = val; i >= 0; i--) {
            IO0CLR = 0x000F0000;
            IO0SET = i << val;//////////////////////////////////////////////////////
            delayMs(100);
        }
    }
}

int main()
{
    IO0DIR |= 1 << 31 | 0x00FF0000;
    IO1DIR |= 1 << 24; ////////////////////////////////////////////////////////////////
    IO0CLR = 0x000F0000; ////////////////////////////////////////////////////////////
    elevator();
}

#include<lpc214x.h>
#define LED_OFF IO0SET = 1<<31
#define LED_ON  IO0CLR = 1<<31

int getCharData(int c);
void display(char* s);

void delayMs(int x)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < 10000; j++);
}

int main()
{
    IO0DIR |= 1 << 31 | 1 << 19 | 1 << 20 | 1 << 30;
    while (1) {
        display("fire");
        delayMs(500);
        display("help");
        delayMs(500);
    }
}

int getCharData(int c)
{
    switch (c) {
    case 'f':
        return 0x00;
    case 'i':
        return 0x00;
    case 'r':
        return 0x00;
    case 'e':
        return 0x00;
    case 'h':
        return 0x00;
    case 'l':
        return 0x00;
    case 'p':
        return 0x00;
    }
    return 0xFF;
}

void display(char* s)
{
    int i, data;
    for (i = 0; i < 5; i++) {
        for (data = getCharData(s[i]); data != 0; data >>= 1) {
            if (data & 0x80 == 0x80)///////////////////////////////////////////////
                IO0SET |= 1 << 19;///////////////////////////////////////////////
            else
                IO0CLR |= 1 << 19;///////////////////////////////////////////////
            IO0SET |= 1 << 20;///////////////////////////////////////////////
            IO0CLR |= 1 << 20;///////////////////////////////////////////////
        }
    }
    IO0SET |= 1 << 30;///////////////////////////////////////////////
    IO0CLR |= 1 << 30;///////////////////////////////////////////////
}


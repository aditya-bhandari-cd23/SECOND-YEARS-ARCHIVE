#include<lpc214x.h>
#define LED_OFF IO0SET = 1<<31
#define LED_ON  IO0CLR = 1<<31

void delayMs(int x)
{
    for (int i = 0; i < x; i++)
        for (int j = 0; j < 10000; j++);
}

int main()
{
    int val;
    IO0DIR = 1 << 31 | 0x00FF0000 | 1 << 28;

    while (1) {
        val = adc(1,3) / 10;
        if (val > 100)
            val = 100;
        runMotor(2, val);
    }
}

int adc(int no, int ch)
{
    if (no == 0) {
        AD0CR = 0x00200600 | (1 << ch) | (1 << 24);/////////////////////////////////
        while (AD0GDR & (1 << 31) == 0);
        return (AD0GDR >> 6) & 0x3FF;
    }
    else if (no == 1) {
        AD1CR = 0x00200600 | (1 << ch) | (1 << 24);/////////////////////////////////
        while (AD1GDR & (1 << 31) == 0);
        return (AD1GDR >> 6) & 0x3FF;
    }
}

void runMotor(int no, int val)
{
    PINSEL0 = 1 << 18;/////////////////////////////////////
    if (no == 1)
        IO0SET = 1 << 28;//////////////////////////////////////////////
    else
        IO0CLR = 1 << 28;//////////////////////////////////////////////

    PWMPCR = 1 << 14;
    PWMMR0 = 1000;
    PWMMR6 = 10 * val;
    PWMTCR = 0x9;
    PWMLER = 0x70;
}

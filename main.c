
#define GPIO_BASE_PADDR 0xfe200000 // Low peripheral mode

volatile unsigned int *GPFSEL4 = (unsigned int *)(GPIO_BASE_PADDR + 0x10);
volatile unsigned int *GPSET1 = (unsigned int *)(GPIO_BASE_PADDR + 0x20);
volatile unsigned int *GPCLR1 = (unsigned int *)(GPIO_BASE_PADDR + 0x2c);

volatile unsigned int GPIO42_OUTPUT = (1 << 6); // ACT LED is GPIO42
volatile unsigned int GPIO42_SET = (1 << 10);
volatile unsigned int GPIO42_CLR = (1 << 10);

int main(void)
{
    *GPFSEL4 = GPIO42_OUTPUT;
    volatile unsigned int timer = 0;
    while (1)
    {
        for (timer = 0; timer < 500000; ++timer)
        {
        }
        *GPSET1 = GPIO42_SET;

        for (timer = 0; timer < 500000; ++timer)
        {
        }
        *GPCLR1 = GPIO42_CLR;
    }
    return 0;
}

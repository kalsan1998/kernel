
const int GPIO_BASE = 0xfe200000; // Low peripheral mode
const int AUX_BASE = 0xfe215000;

const int AUX_ENABLES = AUX_BASE + 0x04;
const int AUX_MU_IO_REG = AUX_BASE + 0x40;
const int AUX_MU_IER_REG = AUX_BASE + 0x44;
const int AUX_MU_IIR_REG = AUX_BASE + 0x48;
const int AUX_MU_LCR_REG = AUX_BASE + 0x4c;
const int AUX_MU_MCR_REG = AUX_BASE + 0x50;
const int AUX_MU_LSR_REG = AUX_BASE + 0x54;
const int AUX_MU_CNTL_REG = AUX_BASE + 0x60;
const int AUX_MU_BAUD_REG = AUX_BASE + 0x68;

const int GPSET1 = GPIO_BASE + 0x20;
const int GPCLR1 = GPIO_BASE + 0x2c;
const int GPIO42_SET = (1 << 10);
const int GPIO42_CLR = (1 << 10);

void put(int addr, int val)
{
    *((volatile unsigned int *)addr) = val;
}

unsigned int get(int addr)
{
    return *((volatile unsigned int *)addr);
}

int gpclr_addr(int pin)
{
}

int gpset_addr(int pin)
{
}

int gpfsel_addr(int pin)
{
    if (pin <= 9)
    {
        return GPIO_BASE + 0x00;
    }
    else if (pin <= 19)
    {
        return GPIO_BASE + 0x04;
    }
    else if (pin <= 29)
    {
        return GPIO_BASE + 0x08;
    }
    else if (pin <= 39)
    {
        return GPIO_BASE + 0x0c;
    }
    else if (pin <= 49)
    {
        return GPIO_BASE + 0x10;
    }
    else if (pin <= 57)
    {
        return GPIO_BASE + 0x14;
    }
    return 0;
}

// mode in [0,8]
void set_gpfsel(int pin, int mode)
{
    put(gpfsel_addr(pin), mode << (3 * (pin % 10)));
}

void set_gpset(int pin, int val)
{
}

void set_gpclr(int pin, int val)
{
}

void init_uart(void)
{
    set_gpfsel(14, 2); // pin14 uses TXD
    set_gpfsel(15, 2); // pin15 uses RXD

    // From: https://s-matyukevich.github.io/raspberry-pi-os/docs/lesson01/rpi-os.html
    put(AUX_ENABLES, 1);     // enables mini UART
    put(AUX_MU_CNTL_REG, 0); // Disable auto flow control and disable receiver and transmitter (for now)
    put(AUX_MU_IER_REG, 0);  // Disable receive and transmit interrupts
    put(AUX_MU_LCR_REG, 3);  // Enable 8 bit mode
    put(AUX_MU_MCR_REG, 0);  // Set RTS line to be always high since we don't need it.
    put(AUX_MU_IIR_REG, 7);  // Clears FIFO and sets no interrupt pending
    // Serial port is capable of transferring max 115200 bits per second.
    // Mini UART calculates baud with:
    //      baudrate = system_clock_freq / (8 * ( baudrate_reg + 1 ))
    //  system_clock_freq = 250 MHz
    put(AUX_MU_BAUD_REG, 270); // Set baud rate to 115200

    put(AUX_MU_CNTL_REG, 3); // Finally, enable transmitter and receiver
}

int main(void)
{
    volatile const char *ON = "ON\0";
    volatile const char *OFF = "OFF\0";

    volatile unsigned int i = 0;
    volatile unsigned int timer = 0;

    init_uart();
    set_gpfsel(42, 1);
    volatile int count = 0;
    while (1)
    {
        for (timer = 0; timer < 500000; ++timer)
        {
        }
        put(GPSET1, GPIO42_SET);

        while (1)
        {
            if (get(AUX_MU_LSR_REG) & 0x20)
            {
                break;
            }
        }
        put(AUX_MU_IO_REG, 'o');

        for (timer = 0; timer < 500000; ++timer)
        {
        }
        put(GPCLR1, GPIO42_CLR);

        // for (i = 0; i < 3; ++i)
        // {
        //     put(AUX_MU_IO_REG, OFF[i]);
        // }
    }
    return 0;
}

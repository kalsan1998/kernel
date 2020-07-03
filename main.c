
const int GPIO_BASE = 0xfe200000; // Low peripheral mode
const int UART0_BASE = 0xfe201000;
const int AUX_BASE = 0xfe215000;

const int GPSET1 = GPIO_BASE + 0x20;
const int GPCLR1 = GPIO_BASE + 0x2c;
const int GPIO42_SET = (1 << 10);
const int GPIO42_CLR = (1 << 10);

const int UART0_DR = UART0_BASE;
const int UART0_FR = UART0_BASE + 0x18;
const int UART0_IBRD = UART0_BASE + 0x24;
const int UART0_FBRD = UART0_BASE + 0x28;
const int UART0_LCRH = UART0_BASE + 0x2c;
const int UART0_CR = UART0_BASE + 0x30;

const int AUX_ENABLES = AUX_BASE + 0x04;
const int AUX_MU_IO_REG = AUX_BASE + 0x40;
const int AUX_MU_IER_REG = AUX_BASE + 0x44;
const int AUX_MU_IIR_REG = AUX_BASE + 0x48;
const int AUX_MU_LCR_REG = AUX_BASE + 0x4c;
const int AUX_MU_MCR_REG = AUX_BASE + 0x50;
const int AUX_MU_LSR_REG = AUX_BASE + 0x54;
const int AUX_MU_CNTL_REG = AUX_BASE + 0x60;
const int AUX_MU_BAUD_REG = AUX_BASE + 0x68;

void put(unsigned int addr, unsigned int val)
{
    *((volatile unsigned int *)addr) = val;
}

unsigned int get(unsigned int addr)
{
    return *((volatile unsigned int *)addr);
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

int gpio_pup_pdn_cntrl_reg_addr(int pin)
{
    if (pin <= 15)
    {
        return GPIO_BASE + 0xe4;
    }
    else if (pin <= 31)
    {
        return GPIO_BASE + 0xe8;
    }
    else if (pin <= 47)
    {
        return GPIO_BASE + 0xec;
    }
    else if (pin <= 57)
    {
        return GPIO_BASE + 0xf0;
    }
    return 0;
}

// mode in [0,8]
void set_gpfsel(int pin, unsigned int mode)
{
    unsigned int addr = gpfsel_addr(pin);
    unsigned int sel = get(addr);
    int shift = 3 * (pin % 10);
    sel &= ~(5 << shift);
    sel |= (mode << shift);
    put(addr, sel);
}

void set_gpset(int pin, unsigned int val)
{
}

void set_gpclr(int pin, unsigned int val)
{
}

void set_gpio_pup_pdn_cntrl(int pin, unsigned int val)
{
    unsigned int addr = gpio_pup_pdn_cntrl_reg_addr(pin);
    unsigned int sel = get(addr);
    int shift = 2 * (pin % 16);
    sel &= ~(3 << shift);
    sel |= (val << shift);
    put(addr, sel);
}

void init_uart(void)
{
    set_gpfsel(14, 2); // pin14 uses TXD0 (ALT0)
    set_gpfsel(15, 2); // pin15 uses RXD0 (ALT0)

    // Clear pull up and pull down resistors
    set_gpio_pup_pdn_cntrl(14, 0);
    set_gpio_pup_pdn_cntrl(15, 0);

    // // Set FEN bit to 0 to flush tansmit.
    // put(UART0_LCRH, 0);
    // // Disable UART before changing control registers.
    // put(UART0_CR, 0);

    // // - The UART_IBRD Register is the integer part of the baud rate divisor value.
    // // - The UART_FBRD Register is the fractional part of the baud rate divisor value.
    // // - The baud rate divisor is calculated as follows:
    // //    BAUDDIV = (FUARTCLK/(16 * Baud rate)) where FUARTCLK is the UART reference clock frequency.
    // // - NOTE: The contents of the IBRD and FBRD registers are not updated until transmission or
    // // reception of the current character is complete
    // put(UART0_IBRD, 26);
    // put(UART0_FBRD, 3);

    // // Word length is set to 8 and enables FIFO buffer.
    // put(UART0_LCRH, (3 << 5) | (1 << 4));
    // // Enable Tx and UART.
    // put(UART0_CR, (1 << 8) | 1);

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

    put(AUX_MU_CNTL_REG, 2); // Enable transmitter
}

void uart_write(char c)
{
    // while (get(UART0_FR) & (1 << 5))
    // {
    //     // Transmit FIFO is full.
    // }
    // put(UART0_DR, c);
    while (1)
    {
        if (get(AUX_MU_LSR_REG) & 0x20)
            break;
    }
    put(AUX_MU_IO_REG, 0x30 + (c & 7));
}

void print_string(const char *c)
{
    while (*c)
    {
        uart_write(*c++);
    }
}

int main(void)
{
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

        print_string("Wow.\r\n");

        for (timer = 0; timer < 500000; ++timer)
        {
        }
        put(GPCLR1, GPIO42_CLR);
    }
    return 0;
}

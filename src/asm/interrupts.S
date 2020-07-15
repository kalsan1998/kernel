.global enable_irq
enable_irq:
    msr daifclr, #15
    ret

.globl disable_irq
disable_irq:
    msr daifset, #15
    ret
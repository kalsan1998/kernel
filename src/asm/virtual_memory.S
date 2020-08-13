.globl test_el1_translation
test_el1_translation:
    at s1e1r, x0
    DSB SY
	ISB
	mrs x0, par_el1
    ret
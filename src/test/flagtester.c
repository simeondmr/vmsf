#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t calc_sum(uint8_t a, uint8_t b, uint8_t carry)
{
	return a + b + carry;
}

int8_t calc_sumi(int8_t a, int8_t b, int8_t carry)
{
	return a + b + carry;
}

uint8_t calc_neg(uint8_t a)
{
	int bitsize = 1<<7;
	return (a & bitsize) ? 1 : 0;
}

uint8_t calc_abs(uint8_t a)
{
	return calc_neg(a) ? -a : a;
}

uint8_t calc_abs2(uint8_t a)
{
	int bitsize = 1<<7;
	return a & (~bitsize);
}

uint8_t calc_overflow(uint8_t a, uint8_t b, int carry, int neg)
{
	if(neg) {
		b = ~b;
		carry = !carry;
	}
	uint8_t s = calc_sum(a, b, carry);
	return (!calc_neg(a) && !calc_neg(b) && calc_neg(s)) || (calc_neg(a) && calc_neg(b) && !calc_neg(s));
}

uint8_t calc_subcarry(uint8_t a, uint8_t b, int carry, int neg)
{
	if(neg) {
		b = ~b;
		carry = !carry;
	}
	uint8_t s = calc_sum(calc_abs2(a), calc_abs2(b), carry);
	return calc_neg(s) ^ neg;
}

uint8_t calc_carry(uint8_t a, uint8_t b, int carry, int neg)
{
	return calc_overflow(a, b, carry, neg) ^ calc_subcarry(a, b, carry, neg);
}

int flagtester(int print_err, int print_all)
{
	int err = 0;
	for(int a = 0 ; a < 256 ; a++) {
		for(int b = 0 ; b < 256 ; b++) {
			for(int carry = 0 ; carry <= 1 ; carry++) {
				for(int neg = 0 ; neg <= 1 ; neg++) {
					int8_t ia = a;
					int8_t ib = b;
					int aa = a;
					int bb = b;
					int iaa = ia;
					int ibb = ib;
					int ccarry = carry;
					if(neg) {
						bb = ~b;
						ibb = ~ib;
						ccarry = !carry;
					}
					int s = aa + bb + ccarry;
					int is = iaa + ibb + ccarry;
					uint8_t s2 = calc_sum(aa, bb, ccarry);
					int8_t is2 = calc_sumi(aa, bb, ccarry);
					if((s != s2) ^ calc_carry(a, b, carry, neg)) {
						err = 1;
						if(print_err) {
							printf("carry:\n");
							printf("\ta=%d(%hhd) b=%d(%hhd)\n", a, a, b, b);
							printf("\tcarry=%d neg=%d\n", carry, neg);
							printf("\tcalc_overflow=%d\n", calc_overflow(a, b, carry, neg));
							printf("\tcalc_carry=%d\n", calc_carry(a, b, carry, neg));
							printf("\tcalc_subcarry=%d\n", calc_subcarry(a, b, carry, neg));
							printf("\taa=%d(%hhd) bb=%d(%hhd)\n", aa, aa, bb, bb);
							printf("\tia=%d(%hhd) ib=%d(%hhd)\n", ia, ia, ib, ib);
							printf("\tiaa=%d(%hhd) ibb=%d(%hhd)\n", iaa, iaa, ibb, ibb);
							printf("\tccarry=%d\n", ccarry);
							printf("\ts=%d(%hhd)\n", s, s);
							printf("\ts2=%d(%hhd)\n", s2, s2);
							printf("\tis2=%d(%hhd)\n", is2, is2);
							printf("\tis=%d(%hhd)\n", is, is);
						}
					}
					if((is != is2) ^ calc_overflow(a, b, carry, neg)) {
						err = 1;
						if(print_err) {
							printf("overflow:\n");
							printf("\ta=%d(%hhd) b=%d(%hhd)\n", a, a, b, b);
							printf("\tcarry=%d neg=%d\n", carry, neg);
							printf("\tcalc_overflow=%d\n", calc_overflow(a, b, carry, neg));
							printf("\tcalc_carry=%d\n", calc_carry(a, b, carry, neg));
							printf("\tcalc_subcarry=%d\n", calc_subcarry(a, b, carry, neg));
							printf("\taa=%d(%hhd) bb=%d(%hhd)\n", aa, aa, bb, bb);
							printf("\tia=%d(%hhd) ib=%d(%hhd)\n", ia, ia, ib, ib);
							printf("\tiaa=%d(%hhd) ibb=%d(%hhd)\n", iaa, iaa, ibb, ibb);
							printf("\tccarry=%d\n", ccarry);
							printf("\ts=%d(%hhd)\n", s, s);
							printf("\ts2=%d(%hhd)\n", s2, s2);
							printf("\tis2=%d(%hhd)\n", is2, is2);
							printf("\tis=%d(%hhd)\n", is, is);
						}
					}
					if(print_all) {
						printf("test:\n");
						printf("\ta=%d(%hhd) b=%d(%hhd)\n", a, a, b, b);
						printf("\tcarry=%d neg=%d\n", carry, neg);
						printf("\tcalc_overflow=%d\n", calc_overflow(a, b, carry, neg));
						printf("\tcalc_carry=%d\n", calc_carry(a, b, carry, neg));
						printf("\tcalc_subcarry=%d\n", calc_subcarry(a, b, carry, neg));
						printf("\taa=%d(%hhd) bb=%d(%hhd)\n", aa, aa, bb, bb);
						printf("\tia=%d(%hhd) ib=%d(%hhd)\n", ia, ia, ib, ib);
						printf("\tiaa=%d(%hhd) ibb=%d(%hhd)\n", iaa, iaa, ibb, ibb);
						printf("\tccarry=%d\n", ccarry);
						printf("\ts=%d(%hhd)\n", s, s);
						printf("\ts2=%d(%hhd)\n", s2, s2);
						printf("\tis2=%d(%hhd)\n", is2, is2);
						printf("\tis=%d(%hhd)\n", is, is);
					}
				}
			}
		}
	}
	return err;
}

#ifdef FLAGTESTER_MAIN

int main()
{
	printf("started flagtester\n");
	int err = flagtester(1, 0);
	if(err) {
		printf("!completed flagtester with errors\n");
	}
	else {
		printf("completed flagtester without errors\n");
	}
	return err;
}

#endif
#include <stdio.h>
#include <string.h>

char ones[][10] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

char teens[][10] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

char tens[][10] = { "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };

int main()
{
	int     sum = 0;
	int	ones_digits = 0;    // for 1 - 9 counting
	int	teens_digits = 0;    // for 10 - 19 counting
	int	tens_digits = 0;     // for 20 - 99 counting
	int	i = 0;
	for (i = 0; i < sizeof(ones) / 10; i++)
		ones_digits += strlen(ones[i]);

	for (i = 0; i < sizeof(teens) / 10; i++)
		teens_digits += strlen(teens[i]);

	for (i = 0; i < sizeof(tens) / 10; i++)
		tens_digits += strlen(tens[i]);

	tens_digits *= 10;
	tens_digits += ones_digits * 8;
	sum = ones_digits * 100;
	sum += (ones_digits + teens_digits + tens_digits) * 10;
	sum += strlen("hundred") * 9 + strlen("hundredand") * 9 * 99;
	sum += strlen("onethousand");
	printf("%d\n", sum);
        return 0;
}

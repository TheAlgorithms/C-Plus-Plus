#include <iostream.h>
#include <conio.h>
#include <math.h>

float eq(float i)
{
	return (pow(i, 3) - (4 * i) - 9); // original equation
}

void main()
{
	float a, b, x, z;
	clrscr();
	for (int i = 0; i < 100; i++)
	{
		z = eq(i);
		if (z >= 0)
		{
			b = i;
			a = --i;
			goto START;
		}
	}

START:

	cout << "\nFirst initial: " << a;
	cout << "\nSecond initial: " << b;
	for (i = 0; i < 100; i++)
	{
		x = (a + b) / 2;
		z = eq(x);
		cout << "\n\nz: " << z << "\t[" << a << " , " << b << " | Bisect: " << x << "]";

		if (z < 0)
		{
			a = x;
		}
		else
		{
			b = x;
		}

		if (z > 0 && z < 0.0009) // stoping criteria
		{
			goto END;
		}
	}

END:
	cout << "\n\nRoot: " << x;
	getch();
}

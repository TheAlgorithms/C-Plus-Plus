#include <conio.h>
#include <iostream.h>
#include <math.h>
float eq(float y)
{
	return ((3 * y) - (cos(y)) - 2);
}
float eqd(float y)
{
	return ((0.5) * ((cos(y)) + 2));
}

void main()
{
	float y, x1, x2, x3, sum, s, a, f1, f2, gd;
	int i, n;

	clrscr();
	for (i = 0; i < 10; i++)
	{
		sum = eq(y);
		cout << "value of equation at " << i << " " << sum << "\n";
		y++;
	}
	cout << "enter the x1->";
	cin >> x1;
	cout << "enter the no iteration to perform->\n";
	cin >> n;

	for (i = 0; i <= n; i++)
	{
		x2 = eqd(x1);
		cout << "\nenter the x2->" << x2;
		x1 = x2;
	}
	getch();
}
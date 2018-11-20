身份证确认有效性

计算方法编辑
1、将前面的身份证号码17位数分别乘以不同的系数。从第一位到第十七位的系数分别为：7 9 10 5 8 4 2 1 6 3 7 9 10 5 8 4 2 ；
2、将这17位数字和系数相乘的结果相加；
3、用加出来和除以11，看余数是多少；
4、余数只可能有0 1 2 3 4 5 6 7 8 9 10这11个数字。其分别对应的最后一位身份证的号码为1 0 X 9 8 7 6 5 4 3 2；
5、通过上面得知如果余数是2，就会在身份证的第18位数字上出现罗马数字的X。



//C++  	
#include "iostream.h"
using namespace std;
#define chartonumber(x) (x-'0')

bool IsIdNumRight(string idNum)
{
bool Rtn = false;
if(idNum.length() !=18)
	return Rtn;


int coefficient[] = {7, 9, 10, 5, 8, 4, 2, 1, 6,3, 7, 9, 10, 5, 8, 4, 2};
int MulToatl = 0;
for (int i = 0; i < 17; i++)
{
	MulToatl +=  chartonumber(idNum[i]) * coefficient[i];
}
int remainder = MulToatl % 11;
char RemCorrTable[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};


if (idNum[17] == RemCorrTable[remainder])
	Rtn = true;

return Rtn;
}
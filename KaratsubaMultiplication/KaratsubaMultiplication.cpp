#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

/* if
x = (10^n/2)a+b
and
y = (10^n/2)c+d

where a,b,c,d are n/2 digits numbers

x.y = (10^n)ac + (10^n/2)(ad + bc) + bd
*/

int KARATSUBA_BASECASE = 1; //10^KARATSUBA_BASECASE

long double KaratsubaMultiplication(long double x, long double y){
	long double result;

	if ((x < pow(10.0, KARATSUBA_BASECASE)) || (y < pow(10.0, KARATSUBA_BASECASE)))
		result = x*y;
	else{
		//1. Find n
		int n = KARATSUBA_BASECASE + 1;
		long double tenPow = pow(10.0, n);
		while (((x / tenPow) > 1) && ((y / tenPow) > 1)){
			n++;
			tenPow = pow(10.0, n);
		}
		cout << "n = " << n << endl;

		long double tenPowOver2 = pow(10.0, n / 2);

		long double a = floor(x / tenPowOver2);
		long double temp = a * tenPowOver2;
		long double b = x - temp;

		cout << "a = " << a << " b = " << b;

		long double c = floor(y / tenPowOver2);
		temp = c * tenPowOver2;
		long double d = y - temp;

		cout << " c = " << c << " d = " << d;

		/*		//2. compute ac
		long double ac = KaratsubaMultiplication(a, c);
		//3. compute ad
		long double ad = KaratsubaMultiplication(a, d);
		//4. compute bc
		long double bc = KaratsubaMultiplication(b, c);
		//5. compute bd
		long double bd = KaratsubaMultiplication(b, d);

		result = pow(10.0, n) * ac + pow(10.0, n / 2)* (ad + bc) + bd;
		*/

		long double step1 = KaratsubaMultiplication(a, c);
		long double step2 = KaratsubaMultiplication(b, d);
		long double step3 = KaratsubaMultiplication((a + b), (c + d));
		long double step4 = step3 - step2 - step1;

		result = pow(10.0, n) *step1;
		result += step2;
		long double tmp = pow(10.0, n / 2)*step4;
		result += tmp;
	}


	return result;
}

void KaratsubaMultiplicationAndTest(){
	long double x = 5678;
	long double y = 1234;
	long double result = KaratsubaMultiplication(x, y);

	cout << "result is " << result << endl;
}

int main(int argc, char* argv[])
{
	KaratsubaMultiplicationAndTest();
	system("pause");
	return 0;
}


// Playground3D_V0-2.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "Playground3D_V0-2.h"
#include "Numeric_Structs.h"

using namespace std;

struct SinCos
{
	double sin = 0, cos = 0;

	SinCos(double s, double c) {
		sin = s;
		cos = c;
	}
	SinCos() { }
};


int r = 0;

void CalcSCtrad(SinCos& obj) {
	obj.sin = sin(r);
	obj.cos = cos(r);
}

//-------------------------------------------------------------------------
const double PI = M_PI;
double noArg = 0;
void CalcSCsqrt(SinCos& obj) {
	obj.sin = sin(r);
	obj.cos = sqrt(1 - (obj.sin * obj.sin));
	noArg = (double)r;
	noArg -= 2 * PI * floor(noArg / (2 * PI)); // 2PI division slow as f*ck
	if (noArg < 3 * PI / 2 && noArg > PI / 2)  obj.cos = -obj.cos;
}
// unfortunately shet until i have a better solution
//-------------------------------------------------------------------------

void Test1() {
	SinCos a = SinCos(), b = SinCos();
	string answer;
	while (true) {
		cout << endl << endl;

		r = rand();
		chrono::time_point start = chrono::high_resolution_clock::now();
		chrono::time_point stop = chrono::high_resolution_clock::now();

		start = chrono::high_resolution_clock::now();
		for (int d = 0; d < 100000; d++)
			CalcSCtrad(a);
		stop = chrono::high_resolution_clock::now();

		cout << "Exe time trad. = " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "micrs\n";

		start = chrono::high_resolution_clock::now();
		//for (d = 0; d < 100000; d++)
			//CalcSCsqrt(b);
		stop = chrono::high_resolution_clock::now();

		cout << "Exe time sqrt = " << chrono::duration_cast<chrono::microseconds>(stop - start).count() << "micrs\n";

		cout << "a.sin = sin(r) = " << a.sin << endl << "a.cos = cos(r) = " << a.cos << endl <<
			"b.sin = sin(r) = " << b.sin << endl << "b.cos = sqrt(1 - (obj.sin * obj.sin)) = " << b.cos << endl <<
			"Error, that is abs(a.cos - b.cos): " << abs(a.cos - b.cos) << endl;
		cout << "Size of int*, string*, bool*:\n" << sizeof(int*) << endl << sizeof(SinCos*) << endl << sizeof(bool*) << endl;
		cout << endl << "Type 's' and enter to gen another,\nor anything else and enter to quit: ";
		cin >> answer;
		if (!(answer == "s")) break;
	}
}

long double Facto(int arg)
{
	// highest value a LONG DOUBLE can hold is 170! =~ 7.2574156153079940e+306
	// after that cout writes "inf" ))))
	if (arg < 0) return 0;
	if (arg < 2) return 1;

	long double ret = 2;
	for (int i = 3; i <= arg; i++) {
		ret *= i;
	}
	return ret;
}


const int MySineArrLen = 10; // in last expression n = 10

double MySine(double ang) {
	double x, factor = 1, sine = 0;
	double ps[MySineArrLen + 1]; // expressions from 0 to 10, 11 in total

	x = ang;

	ps[0] = x;

	for (int i = 1; i <= MySineArrLen; i++) {
		x *= ang * ang;
		factor *= 2 * i * (2 * i + 1);

		ps[i] = x / factor;
	}

	for (int i = MySineArrLen; i >= 0; i--)
	{
		if (i % 2 == 1) sine -= ps[i];
		else sine += ps[i]; 
	}

	return sine;
}

double MySine(double ang, int acc) {
	// forward version
	/*long double x, factor = 1, sine = 0;
	x = ang;
	sine += x;
	for (int i = 1; i <= acc; i++)
	{
		x *= ang * ang;
		factor *= 2 * i * (2 * i + 1);
		if (i % 2 == 1) sine -= x / factor;
		else sine += x / factor;
	}
	return (double)sine;*/

	// backward version (arrays)
	double x, factor = 1, sine = 0;
	double* ps = (double*)malloc((acc + 1) * sizeof(double));
	int psn = 0;

	x = ang;

	*ps = x;

	for (int i = 1; i <= acc; i++) {
		x *= ang * ang;
		factor *= 2 * i * (2 * i + 1);

		ps++; psn++;
		*ps = x / factor;
	}

	for (int i = acc; i >= 0; i--)
	{
		if (i % 2 == 1) sine -= *ps;
		else sine += *ps;
		ps--; psn--;
	}
	ps++; psn++;
	free(ps);
	return sine;
}

void Test2()
{
	//	       i
	//sin(x) = ∑ (-1)^n * x^(2n+1) / (2n+1)!
	//	      n=0

	//	       i
	//cos(x) = ∑ (-1)^n * x^(2n) / (2n)!
	//	      n=0

	double angle, accuracy;
	cout << "Give angle in deg.: ";
	cin >> angle;
	cout << endl << "give accuracy as int: ";
	cin >> accuracy;

	angle *= M_PI * 2;
	angle /= 360;

	/*
	for(int i = 0; i < accuracy; i++)
	{
		cout << endl << "Das ist meine Sine(acc = " << i << "): " << MySine(angle, i);
	}
	*/
	// acc. is 10(actually Arr. Len. is 11) for angle ∊ [0°, 90°]

	for (int i = 0; i <= 90; i++)
	{
		cout << endl << "Das ist meine Sine(nr. " << i << ", acc = " << (int)accuracy << ") : " << MySine(i * M_PI * 2 / 360) << endl;
		cout << "Das ist ihre Sine:                    " << sin(i * M_PI * 2 / 360) << endl;
	}

	cout << endl << "Das ist meine Sine(acc = " << (int)accuracy << "): " << MySine(angle, accuracy) << endl;
	cout << "Das ist ihre Sine:            " << sin(angle) << endl;
}


int main()
{
	// two below lines set up cout to properly and accurately display double values
	cout.precision(numeric_limits<double>::max_digits10 - 1);
	cout.setf(ios_base::scientific);

	// randoms may always be useful
	srand(time(NULL));

	Test2();

	//ending section
	cout << endl << "Enter to close";
	return 0 * getchar();
}

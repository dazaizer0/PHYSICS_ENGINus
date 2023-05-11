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

		int d;
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


int main()
{
	// two below lines set up cout to properly and accurately display double values
	cout.precision(numeric_limits<double>::max_digits10 - 1);
	cout.setf(ios_base::scientific);

	// randoms may always be useful
	srand(time(NULL));



	//ending section
	cout << endl << "Enter to close";
	getchar();
	return 0;
}

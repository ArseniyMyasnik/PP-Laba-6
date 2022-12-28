#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	int amount;
	cout << "Vvedite kolichestvo kriteriev: ";  // Vvod kolichestva kriteriev
	cin >> amount;
	vector <string> names(amount);
	for (int i = 0; i < amount; i++) {
		cout << "Vvedite nazvanie " << i + 1 << "-go kriteriya: ";
		cin >> names[i];
	}
	double** nums = new double* [amount];
	for (int i = 0; i < amount; i++) {	//
		nums[i] = new double[amount];
	}
	for (int i = 0; i < amount; i++) {	// Zapolnenie matricy
		for (int j = 0; j < amount; j++) {
			if (i == j) {
				nums[i][j] = 1;
			}
			else if (i < j) {
				while (true) {
					cout << "Vvedite koefficient sravneniya(1-9) " << names[i]<< " s " << names[j] << ": ";	// Vvod koeficientov sravneniya
					cin >> nums[i][j];
					if ((nums[i][j] > 9) or (nums[i][j] <= 0)) {
						cout << "Vvedite cifru ot 1 do 9!" << endl;	// Obrabotka oshibok (esli vvedeno ne cifra 1-9)
					}
					else {
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < amount; i++) {	// Schitaem obratnye znacheniya (1/koef.sravneniya)
		for (int j = 0; j < amount; j++) {
			if (i > j) {
				nums[i][j] = 1 / nums[j][i];
			}
		}
	}
	vector<double> vec;
	double sum = 0;
	cout << "Itogovaya matrica: " << endl;	// Vyvod itogovoj matricy
	for (int i = 0; i < amount; i++) {			
		for (int j = 0; j < amount; j++) {
			cout << setprecision(2) << nums[i][j] << "	";
			sum += nums[i][j];
		}
		vec.push_back(sum); // Summa strok
		sum = 0;
		cout << endl;
	}
	for (int i = 0; i < amount; i++) {	// Summa vsekh znachenij matricy
		sum += vec[i];
	}
	cout << "Summa vsekh znachenij matricy - " << sum << endl;
	cout << "Vesovye koefficienty: ";	//Vyvod vesovyh koefficientov
	for (int i = 0; i < amount; i++) {
		cout << i + 1 << " - " << vec[i] / sum << ", ";
	}
}
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;


int main() {
	setlocale(LC_ALL, "rus");
	int amount;
	// Zapolnenie vhodnymi dannymi
	cout << "Skol'ko budet vvedeno kriteriev i ob"ektov dlya sravneniya ? : ";
		cin >> amount;
	string* names_cr = new string[amount];
	string* names_vr = new string[amount];
	for (int i = 0; i < amount; i++) {
		cout << "Vvedite nazvanie " << i + 1 << "-go kriteriya(na latinice): ";
		cin >> names_cr[i];
	}

	for (int i = 0; i < amount; i++) {
		cout << "Vvedite nazvanie " << i + 1 << "-go varianta(na latinice): ";
		cin >> names_vr[i];
	}
	/////////////////////////////////////////////////

	// Sozdanie dvumernogo massiva razmerom kriterijXvarianty 
	double** nums = new double* [amount];
	for (int i = 0; i < amount; i++) {
		nums[i] = new double[amount];
	}
	/////////////////////////////////////////////////

	// Zapolnenie vsekh yacheek massiva randomnymi chislami dlya polnoj inicializacii massiva
	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < amount; j++) {
			if (i == j) {
				nums[i][j] = 1;
			}
			else {
				nums[i][j] = rand() % 10 + 2;
			}
		}
	}
	/////////////////////////////////////////////////

	// Zapolnyaem koefficienty sravneniya odnogo kriteriya s drugim
	for (int i = 0; i < amount; i++) {
	START1:
		for (int j = 0; j < amount; j++) {
			if (i == j) {
				i++;
				if (i >= amount) {
					goto START2;
				}
				goto START1;
			}
			else {
				float a;
				cout << "Vvedite koefficient sravneniya " << names_cr[i] << " s " << names_cr[j] << "(1-9): ";
				cin >> a;
				nums[i][j] = a;
			}
		}
	}
	/////////////////////////////////////////////////

	// Transponiruem kazhduyu strochku dvumernogo massiva po diagonali, s dop.usloviem 1/kriterij
START2:

	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < amount; j++) {
			if (nums[i][j] == 1) {
				for (int k = (j + 1); k < amount; k++) {
					nums[i][k] = 1 / nums[k][i];
				}
			}
		}
	}
	/////////////////////////////////////////////////

	// Vyvod massiva
START3:
	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < amount; j++) {
			cout << nums[i][j] << "	  ";
		}
		cout << endl;
	}
	/////////////////////////////////////////////////

	// Schitaem Ocenki komponent sobstvennogo vektora
	double* ocsv_cr = new double[amount];
	double stepen_cr = 1.0 / amount;
	double sum_ocsv_cr = 0;
	for (int i = 0; i < amount; i++) {
		ocsv_cr[i] = 1;
		for (int j = 0; j < amount; j++) {
			ocsv_cr[i] = ocsv_cr[i] * nums[i][j];
		}
		ocsv_cr[i] = pow(ocsv_cr[i], stepen_cr);
	}
	/////////////////////////////////////////////////

	// Schitaem summu Ocenki komponent sobstvennogo vektora
	for (int i = 0; i < amount; i++) {
		sum_ocsv_cr = sum_ocsv_cr + ocsv_cr[i];
	}
	cout << "sum_ocsv=" << sum_ocsv_cr;
	cout << endl;
	/////////////////////////////////////////////////

	// Schitaem Normalizovannye	ocenki vektora prioritet
	double* novp_cr = new double[amount];
	for (int i = 0; i < amount; i++) {
		novp_cr[i] = ocsv_cr[i] / sum_ocsv_cr;
	}
	/////////////////////////////////////////////////

	// Vyvodim poluchennye vyshe dannye
	cout << "---------------------------------" << endl;
	cout << "Ocenki komponent sobstvennogo vektora: " << endl;
	for (int i = 0; i < amount; i++) {
		cout << ocsv_cr[i] << endl;
	}
	cout << "Normalizovannye ocenki vektora prioriteta: " << endl;
	for (int i = 0; i < amount; i++) {
		cout << novp_cr[i] << endl;
	}
	/////////////////////////////////////////////////

	// Sozdaem massiv dlya itogovogo vyvoda
	double** total = new double* [amount];
	for (int i = 0; i < amount; i++) {
		total[i] = new double[amount];
	}
	/////////////////////////////////////////////////

	// Sozdaem massiv dlya poparnogo sravneniya
	double** poparn = new double* [amount];
	double* novp_vr = new double[amount];
	for (int i = 0; i < amount; i++) {
		poparn[i] = new double[amount];
	}
	/////////////////////////////////////////////////

	// Zapolnenie vsekh yacheek massiva randomnymi chislami dlya polnoj inicializacii massiva
	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < amount; j++) {
			if (i == j) {
				poparn[i][j] = 1;
			}
			else {
				poparn[i][j] = rand() % 10 + 2;
			}
		}
	}
	/////////////////////////////////////////////////


	// Sravnivaem varianty po kazhdomu kriteriyu
	for (int i = 0; i < amount; i++) {
		if (i < amount) {
			cout << "Sravnivaem varianty po kriteriyu " << names_cr[i] << endl;
		}
		else {

		}
		for (int j = 0; j < amount; j++) {
		START4:
			for (int k = 0; k < amount; k++) {
				if (j == k) {
					j++;
					if (j >= amount) {
						goto START5;
					}
					if (i >= amount) {
						goto START6;
					}
					goto START4;
				}
				else {
					float a;
					cout << "Vvedite koefficient sravneniya " << names_vr[j] << " s " << names_vr[k] << "(1-9): ";
					cin >> a;
					poparn[j][k] = a;
				}
			}

		}
		/////////////////////////////////////////////////

		// Transponiruem kazhduyu strochku dvumernogo massiva po diagonali, s dop.usloviem 1/kriterij
	START5:
		for (int q = 0; q < amount; q++) {
			for (int w = 0; w < amount; w++) {
				if (poparn[q][w] == 1) {
					for (int e = (w + 1); e < amount; e++) {
						poparn[q][e] = 1 / poparn[e][q];
					}
				}
			}
		}
		/////////////////////////////////////////////////

		// Vyvodim transponirovannyj massiv
		for (int r = 0; r < amount; r++) {
			for (int t = 0; t < amount; t++) {
				cout << poparn[r][t] << "	  ";
			}
			cout << endl;
		}
		/////////////////////////////////////////////////

		// Schitaem Ocenki komponent sobstvennogo vektora
		double* ocsv_vr = new double[amount];
		double stepen_vr = 1.0 / amount;
		double sum_ocsv_vr = 0;
		for (int o = 0; o < amount; o++) {
			ocsv_vr[o] = 1;
			for (int p = 0; p < amount; p++) {
				ocsv_vr[o] = ocsv_vr[o] * poparn[o][p];
			}
			ocsv_vr[o] = pow(ocsv_vr[o], stepen_vr);
		}
		/////////////////////////////////////////////////

		// Schitaem summu Ocenki komponent sobstvennogo vektora poparnogo sravneniya variantov
		for (int x = 0; x < amount; x++) {
			sum_ocsv_vr = sum_ocsv_vr + ocsv_vr[x];
		}
		cout << "sum_ocsv=" << sum_ocsv_vr;
		cout << endl;
		/////////////////////////////////////////////////

		// Schitaem Normalizovannye	ocenki vektora prioritet poparnogo sravneniya variantov
		for (int c = 0; c < amount; c++) {
			novp_vr[c] = ocsv_vr[c] / sum_ocsv_vr;
		}
		/////////////////////////////////////////////////

		// Vyvodim poluchennye vyshe dannye
		cout << "---------------------------------" << endl;
		cout << "Ocenki komponent sobstvennogo vektora: " << endl;
		for (int v = 0; v < amount; v++) {
			cout << ocsv_vr[v] << endl;
		}
		cout << "Normalizovannye ocenki vektora prioriteta: " << endl;
		for (int b = 0; b < amount; b++) {
			cout << novp_vr[b] << endl;
		}
		/////////////////////////////////////////////////

		for (int n = i; n < amount; n++) {
			for (int u = 0; u < amount; u++) {
				total[n][u] = novp_vr[u];
			}
		}
		cout << endl;
	}
	// Vyvodim itogovuyu tablicu s rezul'tatami
	cout << "Itogovaya tablica s rezul'tatami, v kotoroj po gorizontali - kriterii, a po vertikali - varianty: " << endl;
	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < amount; j++) {
			cout << total[i][j] << "	";
		}
		cout << endl;
	}
	/////////////////////////////////////////////////

	// Vyvodim itogovye rezul'taty s variantami
	cout << "Global'nye prioritety:";
	for (int i = 0; i < amount; i++) {
		double result = 0;
		for (int j = 0; j < amount; j++) {
			result = result + (total[i][j] * novp_cr[j]);
		}
		cout << names_vr[i] << " = " << result << endl;
	}
	/////////////////////////////////////////////////
START6:
	cout << " ";
}
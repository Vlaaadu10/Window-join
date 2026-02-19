//Stefan Alexandru Vladut 314CA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NMAX 100001
#define RMAX 100000

typedef struct {
	unsigned long long t, x;
} pereche;
typedef struct {
	unsigned long long cmmmc_val;
	unsigned long long cmmdc_val;
	unsigned long long min_t;
	unsigned long long max_t;
} rezultat;
//cel mai mare divizor comun folosind algoritmul lui euclid iterativ
unsigned long long cmmdc(unsigned long long a, unsigned long long b)
{
	while (b != 0) {
		unsigned long long r = a % b;
		a = b;
		b = r;
	}
	return a;
}

//cel mai mic multiplu comun folosind relatia matematica
unsigned long long cmmmc(unsigned long long a, unsigned long long b)
{
	return (a / cmmdc(a, b)) * b;
}

//sortare folosind Bubble Sort a rezultatelor
void sortare(rezultat rez[], int k)
{
	rezultat aux;
	for (int i = 0; i < k - 1; i++) {
		for (int j = i + 1; j < k; j++) {
			//primar se sorteaza dupa timpii minimi crescator
			if (rez[i].min_t > rez[j].min_t) {
				aux = rez[i];
				rez[i] = rez[j];
				rez[j] = aux;
			} else if (rez[i].min_t == rez[j].min_t) {
				//daca sunt egali se ia maximul timpilor descrescator
				if (rez[i].max_t > rez[j].max_t) {
					aux = rez[i];
					rez[i] = rez[j];
					rez[j] = aux;
				}
			}
		}
	}
}

int main(void)
{
	unsigned long long window;
	unsigned long long t, x;
	scanf("%llu", &window);
	pereche pereche[NMAX];
	rezultat rezultat[RMAX];
	int n = 0;
	while (true) {
		scanf("%llu %llu", &t, &x);
		//conditia de oprire a citirii de valori
		if (t == 0 && x == 0) {
			break;
	}
		pereche[n].t = t;
		pereche[n].x = x;
		n++;
	}
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			//verifica fiecare element cu cele anterioare
			if (pereche[i].t - pereche[j].t <= window) {
				unsigned long long a = pereche[i].x;
				unsigned long long b = pereche[j].x;
				rezultat[k].cmmdc_val = cmmdc(a, b);
				rezultat[k].cmmmc_val = cmmmc(a, b);
				rezultat[k].min_t = pereche[j].t;
				rezultat[k].max_t = pereche[i].t;
				k++;
			}
		}
	}
	sortare(rezultat, k);
	//afiseaza cmmmc si cmmdc pentru rezultate
	for (int i = 0; i < k; i++) {
		printf("%llu %llu\n", rezultat[i].cmmmc_val, rezultat[i].cmmdc_val);
	}
	return  0;
}

#include <stdio.h>
#include<stdlib.h>
int count = 0;

//Sortarea sirului
void sort(int *arr, int lungime)
{

	int temp;
	for (int i = 0; i < lungime; i++) {
		for (int j = i + 1; j < lungime; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}


//Controleaza daca sirul formeaza o progresie aritmetica
int checkIsAP(int arr[], int n)
{
	// Caz de baza
	if (n == 1)
		return 0;

	// Sortarea elementelor
	sort(arr, n);

	// Dupa sortare, diferenta
	// dintre 2 elemente consecutive 
	// trebuie sa fie asemenea
	int d = arr[1] - arr[0];

	// Trece prin sir
	// si controleaza daca diferenta
	// dintre 2 elemente consecutive
	// este aceeasi sau nu
	for (int i = 2; i < n; i++) {
		if (arr[i] - arr[i - 1] != d) {
			return 0;
		}
	}

	return 1;
}

/*  Functia ce genereaza combinatiile  */
void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
	FILE *output;
	int j, i;
	// Afiseaza combinatiile care creaza o progresie aritmetica
	if (index == r && checkIsAP(data, r)) {
		count++;
		output = fopen("out.txt", "at");
		for (j = 0; j < r; j++)
			fprintf(output, "%d ", data[j]);
		fprintf(output, "\n");
		fclose(output);
		return;
	}

	/*Inlocuim indexul cu toate elementele posibile.
	Conditia „end - i + 1 >= r - index” asigura includerea unui element
	la index va face o combinatie cu elementele ramase la pozitiile ramase*/
	for (i = start; i <= end && end - i + 1 >= r - index; i++)
	{
		data[index] = arr[i];
		combinationUtil(arr, data, i + 1, end, index + 1, r);
	}
}

/*  Functie de afisare a combinatiilor  */
void printCombination(int arr[], int n, int r)
{
	int data[1000];
	combinationUtil(arr, data, 0, n - 1, 0, r);
}


int main()
{
	FILE *input, *output;
	input = fopen("in.txt", "rt");
	int arr[200000], r, n, i;
	fscanf(input, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(input, "%d", &arr[i]);
	}
	fclose(input);
	sort(arr, n);
	output = fopen("out.txt", "wt");
	fclose(output);
	for (r = 1; r <= n; r++)
		printCombination(arr, n, r);
	output = fopen("out.txt", "at");
	fprintf(output, "Numarul de subsiruri: %d", count);
	fclose(output);
	return 0;
}
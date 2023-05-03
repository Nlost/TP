#include <stdio.h>
#include <stdlib.h>


int MAX_SIZE=100;


int* Reuniune(int arr1[], int arr2[], int s1, int s2, int *size_final)
{
    int i, j;
    int* r = (int*)malloc(MAX_SIZE * sizeof(int));
    int size_r = 0;
    i = j = 0;
    while (i < s1 && j < s2) {
        if (arr1[i] < arr2[j]) {
            r[size_r++] = arr1[i++]; 
        }
        else if (arr2[j] < arr1[i])
        {
            r[size_r++] = arr2[j++];
        }
        else {
            r[size_r++] = arr2[j++];
            i++;
        }
    }

    while (i < s1)
        r[size_r++] = arr1[i++];
    while (j < s2)
        r[size_r++] = arr2[j++];
        
    *size_final = size_r;
    int* uniune = (int*)malloc(size_r * sizeof(int));
    for (int i = 0; i < size_r; i++)
    {
        uniune[i] = r[i];
    }
    free(r);
    return uniune;
}

int* Intersectie(int arr1[], int arr2[], int s1, int s2, int *size_final)
{
    int i, j;
    int* r = (int*)malloc(MAX_SIZE * sizeof(int));
    int size_r = 0;
    i = j = 0;
    while (i < s1 && j < s2) {
        if (arr1[i] < arr2[j])
            i++;
        else if (arr2[j] < arr1[i])
            j++;
        else 
        {
            r[size_r++] = arr2[j++];
            i++;
        }
    }
    *size_final = size_r;
    int* inter = (int*)malloc(size_r * sizeof(int));
    for (int i = 0; i < size_r; i++)
    {
        inter[i] = r[i];
    }
    free(r);
    return inter;
}



int* Diferenta(int arr1[], int arr2[], int s1, int s2, int* size_final)
{
    int i, j;
    int* r = (int*)malloc(MAX_SIZE * sizeof(int));
    int size_d = 0;
    i = j = 0;
    while (i < s1 && j < s2)
    {
        if (arr1[i] == arr2[j])
        {
            i++;
            j++;
        }
        else if (arr1[i] < arr2[j])
        {
            r[size_d++] = arr1[i++];
        }
        else {
            j++;
        }
    }
    while (i < s1)
    {
        r[size_d++] = arr1[i++];
    }
    *size_final = size_d;
    int* diff = (int*)malloc(size_d * sizeof(int));
    for (int i = 0; i < s1; i++)
    {
        diff[i] = r[i];
    }
    free(r);
    return diff;
}

int main()
{
    FILE* f;
    int* A, * B;
    int s1, s2;
    int* Reun, *Inter, *Diff, *Diff1,  size_reun=0, size_inter=0, size_diff=0, size_diff1=0;
    f = fopen("in.txt", "rt");
    do {
        fscanf(f, "%d %d", &s1, &s2);
        //scanf("%d %d", &s1, &s2);
    }
    while (s1 > MAX_SIZE / 2 || s2 > MAX_SIZE / 2);
    A = (int*)malloc(s1 * sizeof(int));
    B = (int*)malloc(s2 * sizeof(int));
    for (int i = 0; i < s1; i++)
    {
        fscanf(f, "%d", &A[i]);
        //scanf("%d", &A[i]);
    }
    for (int i = 0; i < s2; i++)
    {
        fscanf(f, "%d", &B[i]);
        //scanf("%d", &B[i]);
    }
    fclose(f);
    f = fopen("out.txt", "wt");
    fprintf(f, "Reuniunea este: ");
    //printf("Reuniunea este: ");
    Reun=Reuniune(A, B, s1, s2, &size_reun);
    for (int i = 0; i < size_reun; i++)
    {
        fprintf(f, "%d ", Reun[i]);
        //printf("%d ", Reun[i]);
    }
    fprintf(f, "\nIntersectia este: ");
    //printf("\nIntersectia este: ");
    Inter=Intersectie(A, B, s1, s2, &size_inter);
    for (int i = 0; i < size_inter; i++)
    {
        fprintf(f, "%d ", Inter[i]);
        //printf("%d ", Inter[i]);
    }
    fprintf(f, "\nDifferenta (A, B) este: ");
   // printf("\nDifferenta (A, B) este: ");
    Diff = Diferenta(A, B, s1, s2, &size_diff);
    for (int i = 0; i < size_diff; i++)
    {
        fprintf(f, "%d ", Diff[i]);
        //printf("%d ", Diff[i]);
    }
    fprintf(f, "\nDifferenta (B, A) este: ");
    //printf("\nDifferenta (B, A) este: ");
    Diff1 = Diferenta(B, A, s2, s1, &size_diff1);
    for (int i = 0; i < size_diff1; i++)
    {
        fprintf(f, "%d ", Diff1[i]);
       // printf("%d ", Diff1[i]);
    }
    fprintf(f, "\n");
    //printf("\n");
    return 0;
}

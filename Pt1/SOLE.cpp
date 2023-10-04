#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdio>

#include <cstdlib>
#include <ctime>


using namespace std;

void read_dimensions(int *n, int *m)
{
    ifstream dimention("dimention.txt");
    dimention >> *n;
    dimention >> *m;
    dimention.close();
}

void create_random_matryx(int n, int m){            //Delete at the end
    ofstream alFile("al.txt");
    int x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            srand(time(0)*rand());
            x = -10 + rand() % 20;
            alFile << x << "   ";
        }
        alFile << endl;
    }    
    alFile.close();
}

void read_matrices(int n, int m, double **al, double *d, double **au, double *vec_b, double **L, double **U){
    printf("Matrix al:\n");
    ifstream alFile("al.txt");
    for (int i = 0; i < n; i++)
    {
        al[i] = new double[m];
        for (int j = 0; j < m; j++)
        {
            alFile >> al[i][j];
            printf("%10.2f ", al[i][j]);
        }
        printf("\n");
    }
    alFile.close();
}

int main()
{
    int n, m;
    double **al = new double *[n];
    double *d = new double[n];
    double **au = new double *[n];
    double *vec_b = new double[n];
    double **L = new double *[n];
    double **U = new double *[n];

    read_dimensions(&n, &m);
    create_random_matryx(n, m);                     //Delete at the end
    read_matrices(n, m, al, d, au, vec_b, L, U);
}
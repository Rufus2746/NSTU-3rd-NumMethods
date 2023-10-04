#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>

#include <cstdlib>                                  //Delete at the end
#include <ctime>                                    //Delete at the end


using namespace std;

void read_dimensions(int *n, int *m)
{
    ifstream dimension("dimention.txt");
    dimension >> *n;
    dimension >> *m;
    dimension.close();
}

void create_random_matryx(int n, int m){            //Delete at the end
    ofstream alFile("al.txt");                      //A nahui ya eto delal
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
    ifstream alFile("al.txt");
    for (int i = 0; i < n; i++)
    {
        al[i] = new double[m];
        for (int j = 0; j < m; j++)
        {
            alFile >> al[i][j];
        }
    }
    alFile.close();

    ifstream auFile("au.txt");
    for (int i = 0; i < n; i++)
    {
        au[i] = new double[m];
        for (int j = 0; j < m; j++)
        {
            auFile >> au[i][j];
        }
    }
    auFile.close();

    ifstream vecFile("vec.txt");
    for (int i = 0; i < n; i++)
        vecFile >> vec_b[i];
    vecFile.close();

    for (int i = 0; i < n; i++)
    {
        L[i] = new double[n];
        U[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            L[i][j] = 0.0;
            U[i][j] = 0.0;
        }
    }
}

int main()
{
    int n, m;
    read_dimensions(&n, &m);

    double **al = new double *[n];
    double *d = new double[n];
    double **au = new double *[n];
    double *vec_b = new double[n];
    double **L = new double *[n];
    double **U = new double *[n];
    read_matrices(n, m, al, d, au, vec_b, L, U);
}
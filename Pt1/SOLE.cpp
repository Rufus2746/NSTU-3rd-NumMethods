#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>


using namespace std;
int dimension, notNullElements;

void read_dimensions(int *dimension){
    ifstream dimensionFile("dimension.txt");
    dimensionFile >> *dimension;
    dimensionFile.close();

    ifstream iaFile("ia.txt");
    
}

void read_data(string fileName, float *element){
    ifstream file(fileName);
    for(int i; i<dimension; i++){
        file >> *element;
    }
}

int main(){
    int alIndex, auIndex, iaIndex, diagnalIndex, fIndex, xIndex, yIndex;

    read_dimensions(&dimension);

    float **memory = new float*[1000000];
    iaIndex = 0;
    alIndex = iaIndex + (dimension+1);
    auIndex = alIndex + (notNullElements);
    diagnalIndex = auIndex + (notNullElements);
    fIndex = diagnalIndex + (dimension);
    yIndex = fIndex;
    xIndex = fIndex;
    string fileNames[] = {"ia.txt", "al.txt", "au.txt", "diagnal.txt", "f.txt"};

    for(int i=0; i<sizeof(fileNames); i++){
        read_data(fileNames[i], memory[i]);
    };
/*
    float **al = new float *[n];
    float *d = new float[n];
    float **au = new float *[n];
    float *vec_b = new float[n];
    float **L = new float *[n];
    float **U = new float *[n];
    read_matrices(n, m, al, d, au, vec_b, L, U);
*/
}

enum{
    iaIndex = 0,
    alIndex = 1,
    auIndex = 2,
    diagnalIndex = 3,
    fIndex = 4
};
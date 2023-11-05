#include <iostream>
#include <fstream>

using namespace std;
int notNullElements, dimension, diagnal, ia, al, au;
float memory[100000];

void read_dimensions(int* dimension) {
   ifstream dimensionFile("dimension.txt");
   dimensionFile >> *dimension;
   dimensionFile.close();

   ifstream iaFile("ia.txt");
   al = 0;
   for (int i = 0; i < *dimension + 1; i++) {
      iaFile >> memory[i];
      al++;
      notNullElements = static_cast<int>(memory[i]);
   }
   iaFile.close();
   notNullElements = notNullElements - 1;
}

void read_data(string fileName, int index) {
   ifstream file(fileName);
   if (file.is_open()) {
      for (int i = 0; i < dimension; i++) {
         file >> memory[index + i];
      }
      file.close();
   }
   else {
      cerr << "Can't open the input file" << fileName << endl;
   }
}

float getA(int i, int j) {
   float element = 0;
   int count = 0;
   int index = 0;

   if (i == j) { return memory[diagnal + i]; }

   if (i > j) {                                                                                //Lower triangle
      count = static_cast<int>(memory[ia + i + 1]) - static_cast<int>(memory[ia + i]);
      index = static_cast<int>(memory[ia + i + 1]) - 1;
      if (j >= i - count) {                                                                     //check if element is 0
         for (int k = 0; i > j - 1; k++) {
            element = memory[al + index - k];
            i--;
         }
      }
   }
   else {                                                                                  //Upper triangle
      count = static_cast<int>(memory[ia + j + 1] - static_cast<int>(memory[ia + j]));
      index = static_cast<int>(memory[ia + j + 1]) - 1;
      if (i >= j - count) {                                                                         //check if element is 0
         for (int k = 0; j > i - 1; k++) {
            element = memory[au + index - k];
            j--;
         }
      }
   }

   return element;
}

void LUdecomposition() {                                                                 //Doesn't work after changes. Need to fix ranges
   float buffer, oldElement, L = 0, U = 0;
   int Li = 0, Ui = 0;
   for (int h = 0; h < dimension; h++) {
      buffer = 0;
      for (int j = h; j < dimension; j++) {
         oldElement = getA(h, j);
         if (oldElement != 0) {
            for (int k = 0; k < h - 1 && k != h; k++) {
               if (h != k) {
                  L = getA(h, k);
               }
               else {L = 1;}
               U = getA(k, j);
               buffer = buffer + L*U;
            }
            if (h == j) {
               memory[diagnal + h] = oldElement - buffer;
            }
            else { memory[au + Ui] = oldElement - buffer; Ui++; }
         }
      }

      buffer = 0;
      for (int i = h + 1; i < dimension; i++) {
         oldElement = getA(i, h);
         if (oldElement != 0) {
            for (int k = 0; k < h - 1 && k != h; k++) {
               if (i != k) {
                  L = getA(i, k);
               }
               else {L = 1;}
               U = getA(k, h);
               buffer = buffer + L*U;
            }
            memory[al + Li] = (oldElement - buffer) / getA(h, h); Li++;
         }
      }
   }
}

void calculateY(int f, int y) {
   float buffer;
   for (int i = 0; i < dimension; i++) {
      buffer = 0;
      for (int k = 0; k < i - 1; k++) {
         buffer = buffer + getA(i, k) * memory[f + k];
      }
      memory[y + i] = memory[f + i] - buffer;
   }
}

void calculateX(int y, int x) {
   float buffer;
   for (int i = 0; i < dimension; i++) {
      buffer = 0;
      for (int k = 0; k < dimension; k++) {
         buffer = buffer + getA(i, k) * memory[x + k];
      }
      memory[y + i] = (memory[x + i] - buffer) / getA(i, i);
   }
}

int main() {
   int f, x, y;
   fill_n(memory, 100000, 0);
   read_dimensions(&dimension);

   ia = 0;
   au = al + notNullElements;
   diagnal = au + notNullElements;
   f = diagnal + dimension;
   y = f;
   x = f;

   read_data("al.txt", al);
   read_data("au.txt", au);
   read_data("diagnal.txt", diagnal);
   read_data("f.txt", f);

   for (int i = 0; i < dimension; i++) {
      for (int j = 0; j < dimension; j++) {
         cout << getA(i, j);
      }
      cout << '\n';
   }

   cout << "\n3 thousand years later\n\n";
   LUdecomposition();

   for (int i = 0; i < dimension; i++) {
      for (int j = 0; j < dimension; j++) {
         cout << getA(i, j) << "\t";
      }
      cout << '\n';
   }
}
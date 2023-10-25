#include <iostream>
#include <fstream>

using namespace std;
int notNullElements, dimension, diagnal, ia, al, au;
float memory[100000];

void read_dimensions(int *dimension){
    ifstream dimensionFile("dimension.txt");
    dimensionFile >> *dimension;
    dimensionFile.close();

    ifstream iaFile("ia.txt");
    al = 0;
    for(int i=0; i<*dimension+1; i++){
        iaFile >> memory[i];
        al++;
        notNullElements = memory[i];
    }
    iaFile.close();
    notNullElements = notNullElements - 1;
}

void read_data(string fileName, int index){
    ifstream file(fileName);
    if (file.is_open()){
        for(int i=0; i<dimension; i++){
         file >> memory[index+i];
        }
     file.close();
    }else{
        cerr << "Can't open the input file" << fileName << endl;
    }
}

float getA(int i, int j){
    float element = 0;
    int count = 0;
    int index = 0;

    if(i==j){return memory[diagnal+i];}

    if(i>j){                                                                                //Lower triangle
        count = static_cast<int>(memory[ia+i+1])-static_cast<int>(memory[ia+i]);
        index = static_cast<int>(memory[ia+i+1])-1;
        if(j>=i-count){                                                                     //check if element is 0
            for(int k=0; i>j-1; k++){
                element = memory[al+index-k];
                i--;
            }
        }
    }else{                                                                                  //Upper triangle
        count = static_cast<int>(memory[ia+j+1]-static_cast<int>(memory[ia+j]));
        index = static_cast<int>(memory[ia+j+1])-1;
    if(i>=j-count){                                                                         //check if element is 0
        for(int k=0; j>i-1; k++){
            element = memory[au+index-k];
            j--;
        }
    }
    }

    return element;
}

void LUdecomposition(){                                                                 //Doesn't work after changes. Need to fix ranges
    float buffer, oldElement;
    int li = 0, ui = 0;
    for(int l=0; l<dimension; l++){
        buffer = 0;
        for(int j=l; j<dimension; j++){
            oldElement = getA(l,j);
            if(oldElement!=0){
                for(int k=0; k<l-1 && k!=l; k++){
                    buffer = buffer +getA(l,k)*getA(k,j);
                }
                if(l==j){
                    memory[diagnal+l] = oldElement - buffer;
                }else{memory[au+ui] = oldElement - buffer;ui++;}
            }
        }

        buffer = 0;
        for(int i=l+1; i<dimension; i++){
            oldElement = getA(i,l);
            if(oldElement!=0){
                for(int k=0; k<l-1 && k!=l; k++){
                    buffer = buffer + getA(i,k)*getA(k,l);
                }
                memory[al+li] = (oldElement - buffer) / getA(i,i);li++;
            }
        }
    }
}

int main(){
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

    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            cout<<getA(i,j);
        }
        cout<<'\n';
    }

    cout<<"\n3 thousand years later\n\n";
    LUdecomposition();
    
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            cout<<getA(i,j)<<"   ";
        }
        cout<<'\n';
    }
}
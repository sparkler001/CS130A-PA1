// Implement Dictionary methods.
#include "Dictionary.h"
#include <string>
using namespace std;


void Dictionary::bulkInsert(int n, string *keys) {
    //create a matrix for the first hashing
    int rows    = log(n);
    int columns = n;
    bytes [][] matrix = new matrix[rows][columns];

    for(row = 0; row < rows; row++){
        for(column = 0; column < columns; column++){
            matrix[row][column] = rand() % 2;
        }
    }



}

void Dictionary::insert(string key) {
// TODO:: Write this.

}

void Dictionary::remove(string key) {
// TODO:: Write this.

}

bool Dictionary::find(string key) {
// TODO:: Write this.

    return false;
}

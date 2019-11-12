//
// Haochen Yang
//

#include "Dictionary.h"
#include <time.h>
#include <stdlib.h>

// Implement Dictionary methods.
#include "Dictionary.h"
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void Dictionary::bulkInsert(int n, string *keys) {

    srand((unsigned)time(NULL));

    int numberOfBucket = pow(2, ceil(log2(n)));
//    cout << "numberOfBucket is " << numberOfBucket << endl;
    getFirstHashFunction(n, keys);


    //create first hash table
    SecondHashTable** firstHashTable = new SecondHashTable* [numberOfBucket];

    //print the first hash matrix
//    cout << "The first hash matrix is: " << endl;
//    printMatrix(firstHashMatrix, firstMatrixRow, 32);

    //find the collision number and create the second hash table and number of vectors to store name
    //this hash table consists with collision number for each bucket
//    int *collisionTable = new int[n];

    // create an array to store each number of keys
    unsigned int *keyNumbers = new unsigned int[n];
    for(int each = 0; each < n; each++) {
        keyNumbers[each] = namesChangeToNumber(keys[each]);
//        cout << keyNumbers[each] << endl;
    }

    //for each bucket in first hash table, create second hash table
    for (int num = 0; num < numberOfBucket; num++) {
        //create a matrix for the second hashing
        //use rows and columns as collision numbers in every bucket and every key number size
        SecondHashTable* secondHashTable = new SecondHashTable;
        secondHashTable->numOfCollision      = 0;
        secondHashTable->secondHashTableSize = 0;
        secondHashTable->matrixSize          = 0;

//        secondHashTable->secondHash = new vector<string>*;

        firstHashTable[num] = secondHashTable;
    }

    //for each key that have been changed to number, calculate its position and put it into the bucket
    for(int num = 0; num < n; num++){
        int number = keyNumbers[num];

        int firstHashTablePosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);
//        cout << "number is "<< number << endl;
//        cout << "position is " << firstHashTablePosition << endl;

        // put the name in keys into the secondHash vector<string> temporarily
        // and collision number increase by 1
        firstHashTable[firstHashTablePosition]->tempStoreNames.push_back(keys[num]);
        firstHashTable[firstHashTablePosition]->numOfCollision++;

//        cout << "key is " << keys[num] << endl;
//        cout << "store in " << firstHashTablePosition << endl;
//        cout << "numOfCollision is "  << firstHashTable[firstHashTablePosition].numOfCollision << endl;
    }


    //print all the elements in the second hash table
    for(int i = 0; i < numberOfBucket; i++){
        if(!firstHashTable[i]->tempStoreNames.empty()){
            cout << "in the firstHashTable[" << i << "]:" << endl;
            cout << "collision is " << firstHashTable[i]->numOfCollision;
            for (int j = 0; j < firstHashTable[i]->tempStoreNames.size(); j++){
                cout << firstHashTable[i]->tempStoreNames.at(j) << namesChangeToNumber(firstHashTable[i]->tempStoreNames.at(j)) << endl;
            }
        }
        cout << "-----" << endl;
    }
    cout << "finish print all the elements" << endl;
//    cout << numberOfBucket << endl;

    //find the second hash matrix, store it and names with same matrix
    for(int num = 0; num < numberOfBucket; num++) {
        SecondHashTable* tempHashTable = firstHashTable[num];
        int collision = tempHashTable->numOfCollision;
        cout << "collision is " << collision << endl;

        if (collision != 0) {
            //create the square of collision number of space in secondHash
            int size            = ceil(log2(collision * collision));
            int numberOfBucket  = pow(2, ceil(log2(collision * collision)));
            if(collision == 1){
                size           = 1;
                numberOfBucket = 2;
            }
            tempHashTable->matrixSize = size;

            tempHashTable->secondHash = new vector<string>*[numberOfBucket];

            cout << "size is " << size << endl;
//            cout << "the second hash vector has been newed" << endl;

//            for(int i = 0; i < numberOfBucket; i++){
//                tempHashTable->secondHash[i] = new vector<string>[1];
//            }

            tempHashTable->secondHashTableSize = numberOfBucket;
//            tempHashTable->secondHash[]resize(size);

            //create an array to check the collision times after using second hash matrix
            int *checkCollision = new int[numberOfBucket];
            for(int temp = 0; temp < numberOfBucket; temp++){
                checkCollision[temp] = 0;
            }

//            cout << "second collision list has been created" << endl;

            string name_array[collision];

            for (int each = 0; each < collision; each++){
                name_array[each] = firstHashTable[num]->tempStoreNames[each];
                cout << firstHashTable[num]->tempStoreNames[each] << endl;
            }

            cout << "number of bucket is " << numberOfBucket << endl;
            tempHashTable->secondMatrix = getSecondHashFunction(collision, numberOfBucket, name_array);
//            break;

            //check the second hash matrix in order to keep every names in different position
//            bool matrixWorks    = true;
//            int **secondMatrix  = randomMatrix(size, 32);
            cout << "in the firstHashTable[" << num << "]:" << endl;
            cout << "The second matrix is: " << endl;
            printMatrix(tempHashTable->secondMatrix, size, 32);

            //set every name in second hash table into its vector unique position
            for(int each = 0; each < collision; each++){
//                cout<<"one"<<endl;
                string name = tempHashTable->tempStoreNames[each];
//                string name = name_array[each];
//                cout << name << endl;
                cout << "name is " << name << endl;
                unsigned int elementsNumberOfKey     = namesChangeToNumber(name);
                int secondHashTablePosition = numberTimesMatrix(tempHashTable->secondMatrix, size, elementsNumberOfKey);
                cout<<secondHashTablePosition<<endl;
//                cout << elementsNumberOfKey << endl;
                cout << secondHashTablePosition << endl;
//                cout << tempHashTable->secondHash->size() << endl;

                tempHashTable->secondHash[secondHashTablePosition] = new vector<string>[1];
                tempHashTable->secondHash[secondHashTablePosition]->push_back(name);
                cout << "secondHash table size is " << tempHashTable->secondHash[secondHashTablePosition]->size() << endl;
                cout << "this table is empty: " << tempHashTable->secondHash[secondHashTablePosition]->empty() << endl;
                cout << "finish" << endl;
            }
        }else{
            tempHashTable->secondHash = new vector<string>*[1];
            tempHashTable->secondHash[0] = new vector<string>[1];

            cout << "finish 2" << endl;
        }
    }

    this->firstHashTable = firstHashTable;
}

void Dictionary::insert(string key) {
    if(key.empty()){
        cout << "empty input" << endl;
        return;
    }

    if(firstHashMatrix == NULL){
        cout << "there is no exist hash table" << endl;
        return;
    }

    if(find(key)){
        cout << "The key has already in the dictionary" << endl;
        return;
    }

    //change key to number and get Position in first hash table
    unsigned int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    firstHashTable[firstPosition]->secondHash[secondPosition]->push_back(key);
    return;
}

void Dictionary::remove(string key) {
    if(key.empty()){
        cout << "empty input" << endl;
        return;
    }

    if(firstHashMatrix == NULL){
        cout << "there is no exist hash table" << endl;
        return;
    }

    if(!find(key)){
        cout << "The key does not exist in the dictionary" << endl;
        return;
    }

    //change key to number and get Position in first hash table
    unsigned int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    //get position in second hash table
    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    //delete the element
    vector<string>* secondHashTable = firstHashTable[firstPosition]->secondHash[secondPosition];
    for(vector<string>::iterator it = secondHashTable->begin(); it != secondHashTable->end(); ) {
        if (*it == key) {
            it = secondHashTable->erase(it);
            return;
        } else {
            ++it;
        }
    }
}

bool Dictionary::find(string key) {
    if(key.empty() || firstHashMatrix == NULL) return false;

    //change key to number and get Position in first hash table
    unsigned int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    if(firstHashTable[firstPosition]->secondMatrix == NULL) return false;

    //get position in second hash table
    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    if(firstHashTable[firstPosition]->secondHash == NULL) return false;

    vector<string>* secondHashTable = firstHashTable[firstPosition]->secondHash[secondPosition];
    for(int i = 0; i < secondHashTable->size(); i++){
        if(key == secondHashTable->at(i))
            return true;
    }
    return false;
}

void Dictionary::getFirstHashFunction(int n, string *keys){
    int matrix_row       = ceil(log2(n));
    this->firstMatrixRow = matrix_row;

    while(true){
        int** Newmatrix=randomMatrix(matrix_row,32);

        int collision_array[int(pow(2,matrix_row))];

        for(int c=0;c<matrix_row;c++){
            collision_array[c]=0;
        }

        for(int d=0;d<n;d++){
            keys[d] = "        " + keys[d];
            int* array=Array_keys(keys[d].substr(keys[d].length()-8));
            int position[matrix_row];
            for(int k=0; k<matrix_row; k++){
                int result=0;
                for(int i=0; i<32; i++){
                    result+=(Newmatrix[k][i])*array[i];
                }
                position[k]=result%2;
            }
            int int_position=0;
            for(int b=0; b<matrix_row; b++){
                int_position+=position[b]*pow(2,b);
            }
            collision_array[int_position]+=1;
        }

        int sum=0;
        for(int e=0;e<pow(2,matrix_row);e++){
            sum+=pow(collision_array[e],2);
        }
        if (sum<(4*n)) {
            this->firstHashMatrix = Newmatrix;
//            return Newmatrix;
//            printMatrix(Newmatrix, matrix_row, 32);
            break;
        }
    }
}

int** Dictionary::getSecondHashFunction(int sizeOfKeys, int nsquare, string *keys){
    int matrix_row = ceil(log2(nsquare));
    if (nsquare == 1) matrix_row = 1;
    int tableSize = pow(2, matrix_row);
    cout << matrix_row << endl;
    cout << tableSize << endl;

    int collision_array[tableSize];

    while (true) {
        int **Newmatrix = randomMatrix(matrix_row, 32);
        printMatrix(Newmatrix, matrix_row, 32);

        for (int c = 0; c < tableSize; c++) {
            collision_array[c] = 0;
        }

//        cout << "2" << endl;

        for (int d = 0; d < sizeOfKeys; d++) {
            keys[d] = "        " + keys[d];
            int *array = Array_keys(keys[d].substr(keys[d].length() - 8));
            cout << d << endl;
            int position[matrix_row];
            for (int k = 0; k < matrix_row; k++) {
                int result = 0;
                for (int i = 0; i < 32; i++) {
                    result += (Newmatrix[k][i]) * array[i];
                }
                position[k] = result % 2;
            }

            int int_position = 0;
            for (int b = 0; b < matrix_row; b++) {
                int_position += position[b] * pow(2, b);
            }

//            cout << int_position << endl;
            collision_array[int_position] += 1;
        }

        cout << "the collision array is " << endl;

        int sum = 0;
        for (int e = 0; e < tableSize; e++) {
            cout << collision_array[e] << endl;
            if(collision_array[e] > 1) {
                sum++;
            }
        }

        cout << "sum is " << sum << endl;

//        if (sum < (4 * n)) {
//            this->firstHashMatrix = Newmatrix;
//            return Newmatrix;
//            break;
        if(sum == 0) return Newmatrix;

        }
    }

void Dictionary::print(){
    //print the first hash matrix
    cout << "The first hash matrix is: " << endl;
    printMatrix(firstHashMatrix, firstMatrixRow, 32);

    int numberOfBucket = pow(2, this->firstMatrixRow);
    //print all second hash matrix and elements
    for(int each = 0; each < numberOfBucket; each++){
        if(firstHashTable[each]->secondHashTableSize > 0) {
            cout << "in the firstHashTable[" << each << "]:" << endl;
            cout << "The second matrix is: " << endl;
            printMatrix(firstHashTable[each]->secondMatrix, firstHashTable[each]->matrixSize, 32);
            int secondHashSize =  firstHashTable[each]->secondHashTableSize;
            cout << "size is " << firstHashTable[each]->secondHashTableSize << endl;

            for(int j = 0; j < secondHashSize; j++) {
//                cout << firstHashTable[each]->secondHash[j]->empty() << endl;
//                cout << j << endl;
                if(firstHashTable[each]->secondHash[j]){
                    cout << "there is something on this vector" << j << endl;
//                    cout << firstHashTable[each]->secondHash[j]->size() << endl;
//                    cout << "-----" << endl;
//                    for(int i = 0; i < firstHashTable[each]->secondHash[j]->size(); i++)
//                        cout << "The elements stored in position " << i << " is: "
//                         << firstHashTable[each]->secondHash[j]->at(i) << endl;
                }
            }
        }
    }
}

int main(){

//    Dictionary dic;
//    string* key = new string[3];
//    key[1] = "2asdfkgkygghdjrdjdfgjffsdfafdsafsffghmklughlh";
//    key[2] = "asdfweghmfkulhlhiuohiuhksdfsdfsafdsafasdf";
//    key[0] = "yhjykgkguguasdfasdfasflyluyhuluhliughhuhiuhoisdfsafdaf";
//
//    int** matrix = dic.getFirstHashFunction(3, key);
//    printMatrix(matrix, 2, 32);
//    for(int i = 0; i < 3; i++) {
//        int number   = namesChangeToNumber(key[i]);
//        cout << key[i] << " number is " << number << endl;
//        int position = numberTimesMatrix(matrix, 2, number);
//        cout << key[i] << " position is " << position << endl;
//    }

//    int** matrix = randomMatrix(3, 4);
//    printMatrix(matrix, 3, 4);


//    string s = "ssqqqqq";
//    int a = namesChangeToNumber(s);
//    cout << a << endl;
//    int **matrix = randomMatrix(4,32);
//    printMatrix(matrix, 4, 32);
//    int c = numberTimesMatrix(matrix, 4, 100);
//    cout << c << endl;

    Dictionary dic;
    string* key = new string[10];
    key[1] = "2asdfkgkygghdjrdjdfgjfffghm";
    key[2] = "asdfweghmfhk";
    key[0] = "yhjykgkgugulyluyhuluh";
    key[3] = "weqrwezxsdfsdf";
    key[4] = "aseqwerqwr";
    key[5] = "aseqwersdfaqqwerzz";
    key[6] = "122123asdaserqwerolxzc";
    key[7] = "12sdf2123asdaserqwerolsdfaqxzc";
    key[8] = "12sdf2123asdaserqwerolsdfaqxzcsafqewr12313";
    key[9] = "12sdf2123asdaserqwerolsdfqwerqewsxczc";
//    dic.getSecondHashFunction(49, key);
//    dic.getFirstHashFunction(7, key);
    dic.bulkInsert(10, key);
    dic.print();

    vector<string>** a = new vector<string>*[1];
}
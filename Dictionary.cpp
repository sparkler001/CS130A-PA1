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


//    print all the elements in the second hash table
//    for(int i = 0; i < numberOfBucket; i++){
//        if(!firstHashTable[i]->tempStoreNames.empty()){
//            cout << "in the firstHashTable[" << i << "]:" << endl;
//            cout << "collision is " << firstHashTable[i]->numOfCollision;
//            for (int j = 0; j < firstHashTable[i]->tempStoreNames.size(); j++){
//                cout << firstHashTable[i]->tempStoreNames.at(j) << namesChangeToNumber(firstHashTable[i]->tempStoreNames.at(j)) << endl;
//            }
//        }
//        cout << "-----" << endl;
//    }
//    cout << "finish print all the elements" << endl;
//    cout << numberOfBucket << endl;

    //find the second hash matrix, store it and names with same matrix
    for(int num = 0; num < numberOfBucket; num++) {
        SecondHashTable* tempHashTable = firstHashTable[num];
        int collision = tempHashTable->numOfCollision;
//        cout << "collision is " << collision << endl;

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

            //initialize every second hash table buckect
            for(int each = 0; each < numberOfBucket; each++){
                tempHashTable->secondHash[each] = new vector<string>[1];
            }

//            cout << "size is " << size << endl;
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
//                cout << firstHashTable[num]->tempStoreNames[each] << endl;
            }

//            cout << "number of bucket is " << numberOfBucket << endl;
            tempHashTable->secondMatrix = getSecondHashFunction(collision, numberOfBucket, name_array);
//            break;

            //check the second hash matrix in order to keep every names in different position
//            bool matrixWorks    = true;
//            int **secondMatrix  = randomMatrix(size, 32);
//            cout << "in the firstHashTable[" << num << "]:" << endl;
//            cout << "The second matrix is: " << endl;
//            printMatrix(tempHashTable->secondMatrix, size, 32);

            //set every name in second hash table into its vector unique position
            for(int each = 0; each < collision; each++){
//                cout<<"one"<<endl;
                string name = tempHashTable->tempStoreNames[each];
//                string name = name_array[each];
//                cout << name << endl;
//                cout << "name is " << name << endl;
                unsigned int elementsNumberOfKey     = namesChangeToNumber(name);
                int secondHashTablePosition = numberTimesMatrix(tempHashTable->secondMatrix, size, elementsNumberOfKey);
//                cout<<secondHashTablePosition<<endl;
//                cout << elementsNumberOfKey << endl;
//                cout << secondHashTablePosition << endl;
//                cout << tempHashTable->secondHash->size() << endl;

                tempHashTable->secondHash[secondHashTablePosition] = new vector<string>[1];
                tempHashTable->secondHash[secondHashTablePosition]->push_back(name);
//                cout << "secondHash table size is " << tempHashTable->secondHash[secondHashTablePosition]->size() << endl;
//                cout << "this table is empty: " << tempHashTable->secondHash[secondHashTablePosition]->empty() << endl;
//                cout << "finish" << endl;
            }
        }else{
            tempHashTable->secondHash = new vector<string>*[1];
            tempHashTable->secondHash[0] = new vector<string>[1];

//            cout << "finish 2" << endl;
        }
    }

    this->firstHashTable = firstHashTable;
    print();
}

void Dictionary::insert(string key) {
    if(key.empty()){
        cout << "the input key is empty!" << endl;
        return;
    }

    if(firstHashMatrix == NULL){
        cout << "there is no exist hash table" << endl;
        return;
    }

    if(find(key)){
        cout << "The key: " << key << " has already in the dictionary" << endl;
        return;
    }

    key = "        " + key;
    //change key to number and get Position in first hash table
    unsigned int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    firstHashTable[firstPosition]->secondHash[secondPosition]->push_back(key);
    firstHashTable[firstPosition]->secondHashTableSize++;
    cout << "insert key: " << key << "is successful!" << endl;
    return;
}

void Dictionary::remove(string key) {
    if(key.empty()){
        cout << "the input key is empty!" << endl;
        return;
    }

    if(firstHashMatrix == NULL){
        cout << "there is no exist hash table" << endl;
        return;
    }

    if(!find(key)){
        cout << "The key: " << key << " does not exist in the dictionary" << endl;
        return;
    }

    key = "        " + key;
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
            cout << "this key: " << key << " has already been removed!" << endl;
            return;
        }
            ++it;
    }
}

bool Dictionary::find(string key) {
    if(key.empty()){
        cout << "the input key is empty!" << endl;
        return false;
    }

    if(firstHashMatrix == NULL){
        cout << "the dictionary is not exist" << endl;
        return false;
    }

    key = "        " + key;
    //change key to number and get Position in first hash table
    unsigned int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    if(firstHashTable[firstPosition]->secondHashTableSize == 0) return false;

    //get position in second hash table
    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

//    cout << "secondMatrix is " << endl;
//    printMatrix(secondMatrix, secondMatrixRow, 32);
//    cout << "second position is " << secondPosition << endl;

    if(firstHashTable[firstPosition]->secondHash == NULL) return false;

    vector<string>* secondHashTable = firstHashTable[firstPosition]->secondHash[secondPosition];
    for(int i = 0; i < secondHashTable->size(); i++){
        if(key == secondHashTable->at(i)) {
            cout << "this key: " << key << " has been stored in this dictionary!" << endl;
            return true;
        }
    }
    cout << "this key: " << key << " has not been stored in this dictionary!" << endl;
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
//    cout << matrix_row << endl;
//    cout << tableSize << endl;

    int collision_array[tableSize];

    while (true) {
        int **Newmatrix = randomMatrix(matrix_row, 32);
//        printMatrix(Newmatrix, matrix_row, 32);

        for (int c = 0; c < tableSize; c++) {
            collision_array[c] = 0;
        }

//        cout << "2" << endl;

        for (int d = 0; d < sizeOfKeys; d++) {
            keys[d] = "        " + keys[d];
            int *array = Array_keys(keys[d].substr(keys[d].length() - 8));
//            cout << d << endl;
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

//        cout << "the collision array is " << endl;

        int sum = 0;
        for (int e = 0; e < tableSize; e++) {
//            cout << collision_array[e] << endl;
            if(collision_array[e] > 1) {
                sum++;
            }
        }

//        cout << "sum is " << sum << endl;

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
//            cout << "size is " << firstHashTable[each]->secondHashTableSize << endl;

            for(int j = 0; j < secondHashSize; j++) {

                if(!firstHashTable[each]->secondHash[j]->empty()){
                    for(int i = 0; i < firstHashTable[each]->secondHash[j]->size(); i++)
                        cout << "The elements stored in position " << j << " is: "
                         << firstHashTable[each]->secondHash[j]->at(i) << endl;
                }
            }
        }
    }
}

//int main(){
//
//    Dictionary dic;
//    string* key = new string[10];
//    key[1] = "2asdfkgkygghdjrdjdfgjfffghm";
//    key[2] = "asdfweghmfhk";
//    key[0] = "yhjykgkgugulyluyhuluh";
//    key[3] = "weqrwezxsdfsdf";
//    key[4] = "aseqwerqwr";
//    key[5] = "aseqwersdfaqqwerzz";
//    key[6] = "122123asdaserqwerolxzc";
//    key[7] = "12sdf2123asdaserqwerolsdfaqxzc";
//    key[8] = "12sdf2123asdaserqwerolsdfaqxzcsafqewr12313";
//    key[9] = "12sdf2123asdaserqwerolsdfqwerqewsxczc";
////    dic.getSecondHashFunction(49, key);
////    dic.getFirstHashFunction(7, key);
//    dic.bulkInsert(10, key);
//    dic.print();
//    cout << "-----" << endl;
//    dic.insert("");
//    cout << "-----" << endl;
//    dic.print();
//}

void small_dict_test()
{

    /* Small dictionary test as given in the provided test module. */
    cout << "!!!Small dictionary test starts!!!" << endl;

    // Initialize the dictionary.
    Dictionary small_dict;

    // BulkInsert the keys into the dictionary.
    /* Expected results: hash functions used, sum of squares of number of keys, number of trials, 3pts, 1pt each*/
    string strs[] = {"Fred Astaire", "Lauren Bacall", "Brigitte Bardot", "John Belushi", "Ingmar Bergman"};
    int n = 5;
    small_dict.bulkInsert(n, strs);


    // Insert "Humphrey Bogart" into the dictionary.
    /* Expected results: whether collisions happened in second level, 1pt*/
    small_dict.insert("Humphrey Bogart");

    // Remove "Lauren Bacall" from the dictionary.
    /* Expected results: removal is successful, 1pt*/
    small_dict.remove("Lauren Bacall");

    // Find "Fred Astaire" in the dictionary.
    /* Expected results: print 1, finding is successful, buckets accessed during the process, 1pt*/
    cout << small_dict.find("Fred Astaire") << endl;

    // Find "Lauren Bacall" in the dictionary.
    /* Expected results: print 0, finding is unsuccessful, item doesn't exist, 1pt*/
    cout << small_dict.find("Lauren Bacall") << endl;
}

void large_dict_test()
{

    /* Large dictionary test. */
    cout << "!!!Large dictionary test starts!!!" << endl;

    // Initialize the dictionary.
    Dictionary large_dict;

    // BulkInsert the keys into the dictionary.
    /* Expected results: hash functions used, sum of squares of number of keys, number of trials, 3pts, 1pt each*/
    string strs[] = {"Emma Ember", "Olivia Rosalie", "Ava Journee", "Isabella Presley", "Sophia Amy",
                     "Mia Mckenzie", "Amelia Alaina", "Harper Brooke", "Evelyn Alana",
                     "Abigail Summer", "Emily Rachel", "Elizabeth Mya", "Mila Everleigh", "Ella Daniela",
                     "Avery Jocelyn", "Sofia Amara", "Camila Josie", "Aria Gracie", "Scarlett Callie", "Victoria Ayla",
                     "Madison Londyn", "Luna Elliana", "Grace Sienna", "Chloe Juliette", "Penelope Diana",
                     "Layla Lucia", "Riley Laila", "Zoey Sloane", "Nora London", "Lily Alexis", "Eleanor Teagan",
                     "Hannah Remi", "Lillian Elise", "Addison Harmony", "Aubrey Arabella", "Ellie Sara",
                     "Stella Genevieve", "Natalie Lauren", "Zoe Kimberly", "Leah ", "Hazel Daisy", "Violet Trinity",
                     "Aurora Eloise", "Savannah Jordyn", "Brooklyn Morgan", "Bella Finley",
                     "Claire Parker", "Skylar Lilly", "Lucy Aliyah", "Paisley Reese", "Everly Molly", "Anna Alina",
                     "Caroline Valerie", "Nova Cecilia", "Genesis Ariel", "Emilia Esther", "Kennedy Charlie",
                     "Samantha Juliana", "Maya Alyssa", "Willow Kayla", "Kinsley Anastasia", "Naomi Emersyn",
                     "Aaliyah Eden", "Elena Ryleigh", "Sarah Adalyn", "Ariana Emerson", "Allison Valeria",
                     "Gabriella Annabelle", "Alice Norah", "Madelyn Isabel", "Cora Iris", "Ruby Melody", "Eva Jasmine",
                     "Serenity Khloe", "Autumn Andrea", "Adeline Bailey", "Hailey Brianna", "Gianna Eliza",
                     "Valentina Amaya", "Isla Ashley", "Eliana Lyla", "Quinn Margaret", "Nevaeh Mary", "Ivy Alexandra",
                     "Sadie Kylie", "Piper Rose", "Lydia Faith", "Alexa Taylor", "Josephine Leilani", "Emery Arya",
                     "Julia Ximena", "Delilah Athena", "Arianna Maria", "Vivian Raelynn", "Kaylee Natalia",
                     "Sophie Isabelle", "Brielle Katherine", "Madeline Jade", "Peyton Aubree", "Rylee Liliana",
                     "Clara Adalynn", "Hadley Reagan", "Melanie Mackenzie", "Mackenzie Melanie", "Reagan Hadley",
                     "Adalynn Clara", "Liliana Rylee", "Aubree Peyton", "Jade Madeline", "Katherine Brielle",
                     "Isabelle Sophie", "Natalia Kaylee", "Raelynn Vivian", "Maria Arianna", "Athena Delilah",
                     "Ximena Julia", "Arya Emery", "Leilani Josephine", "Taylor Alexa", "Faith Lydia", "Rose Piper",
                     "Kylie Sadie", "Alexandra Ivy", "Mary Nevaeh", "Margaret Quinn", "Lyla Eliana", "Ashley Isla",
                     "Amaya Valentina", "Eliza Gianna", "Brianna Hailey", "Bailey Adeline", "Andrea Autumn",
                     "Khloe Serenity", "Jasmine Eva", "Melody Ruby", "Iris Cora", "Isabel Madelyn", "Norah Alice",
                     "Annabelle Gabriella", "Valeria Allison", "Emerson Ariana", "Adalyn Sarah", "Ryleigh Elena",
                     "Eden Aaliyah", "Emersyn Naomi", "Anastasia Kinsley", "Kayla Willow", "Alyssa Maya",
                     "Juliana Samantha", "Charlie Kennedy", "Esther Emilia", "Ariel Genesis", "Cecilia Nova",
                     "Valerie Caroline", "Alina Anna", "Molly Everly", "Reese Paisley", "Aliyah Lucy", "Lilly Skylar",
                     "Parker Claire", "Finley Bella", "Morgan Brooklyn", "Sydney Audrey", "Jordyn Savannah",
                     "Eloise Aurora", "Trinity Violet", "Daisy Hazel", " Leah", "Kimberly Zoe", "Lauren Natalie",
                     "Genevieve Stella", "Sara Ellie", "Arabella Aubrey", "Harmony Addison", "Elise Lillian",
                     "Remi Hannah", "Teagan Eleanor", "Alexis Lily", "London Nora", "Sloane Zoey", "Laila Riley",
                     "Lucia Layla", "Diana Penelope", "Juliette Chloe", "Sienna Grace", "Elliana Luna",
                     "Londyn Madison", "Callie Scarlett", "Gracie Aria", "Josie Camila", "Amara Sofia",
                     "Jocelyn Avery", "Daniela Ella", "Everleigh Mila", "Mya Elizabeth", "Rachel Emily",
                     "Summer Abigail", "Alana Evelyn", "Brooke Harper", "Alaina Amelia", "Mckenzie Mia",
                     "Catherine Charlotte", "Amy Sophia", "Presley Isabella", "Journee Ava", "Rosalie Olivia",
                     "Ember Emma"};
    int n = 207;
    large_dict.bulkInsert(n, strs);

    // Find "Lillian Elise" in the dictionary.
    /* Expected results: print 1, finding is successful, buckets accessed during the process, 1pt*/
    cout << large_dict.find("Lillian Elise") << endl;

    // Remove "Zexi Huang" from the dictionary.
    /* Expected results: removal is unsuccessful, item doesn't exist, 1pt*/
    large_dict.remove("Zexi Huang");

    // Insert "Sean Jaffe" into the dictionary.
    /* Expected results: whether collisions happened in second level, 1pt*/
    large_dict.insert("Sean Jaffe");

    // Find "Sean Jaffe" in the dictionary.
    /* Expected results: print 1, finding is successful, buckets accessed during the process, 1pt*/
    cout << large_dict.find("Sean Jaffe") << endl;

    // Remove "Brooklyn Morgan" from the dictionary.
    /* Expected results: removal is successful, 1pt*/
    large_dict.remove("Brooklyn Morgan");

    // Find "Lillian Elise" in the dictionary.
    /* Expected results: print 1, finding is successful, buckets accessed during the process, results should be the same as the first find, 1pt*/
    cout << large_dict.find("Lillian Elise") << endl;

    // Find "Brooklyn Morgan" from the dictionary.
    /* Expected results: print 0, finding is unsuccessful, 1pt*/
    cout << large_dict.find("Brooklyn Morgan") << endl;

    // Remove "Lillian Elise" from the dictionary.
    /* Expected results: removal is successful, 1pt*/
    large_dict.remove("Lillian Elise");

    // Insert "Lillian Elise" into the dictionary.
    /* Expected results: whether collisions happened in second level, 1pt*/
    large_dict.insert("Lillian Elise");

    // Find "Lillian Elise" in the dictionary.
    /* Expected results: print 1, finding is successful, buckets accessed during the process, results should be the same as the first find, 1pt*/
    cout << large_dict.find("Lillian Elise") << endl;
}

int main()
{
    small_dict_test();
    large_dict_test();

    return 0;
}

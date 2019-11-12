#include <string>
using namespace std;

class Dictionary {
public:
    // Insert an input set of n keys to the dictionary. This method should print out the following information:
    // 1. The hash functions comprising the perfect hash (both levels)
    // 2. The sum of squares of the number of keys mapped to each bin of the first level hash function, and
    // 3. The number of trials needed to generate each hash function.
    void bulkInsert(int n, string *keys);

    // Insert a key to the dictionary.
    // Print out whether the insertion caused a collision in the second level hash.
    // Handle collision with separate chaining.
    void insert(string key);

    // Remove a key from the dictionary, if it exists.
    void remove(string key);

    // Return whether a key is found in the dictionary.
    // Print the buckets (both first and second level) accessed during the operation.
    bool find(string key);
};

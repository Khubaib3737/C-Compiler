/*
    This class hold all custom data structures that are being used in this entire project.
    Plus helper functions
*/


#pragma once
#include <iostream> // 
#include <cstring> // for strcmp
using namespace std;

// Global access
extern constexpr int ScannerStackSize = 500;



// Custom Pair class to hold two values

template <typename K, typename V>
struct Pair {
    K first;
    V second;

    explicit Pair() = default;

    Pair(const K& k, const V& v) : first(k), second(v) {}
};


// Custom Map class to hold key-value pairs
template <typename K, typename V, int MAX_SIZE>
class CustomMap {
private:
    Pair<K, V> pairs[MAX_SIZE];
    int size;

public:
    CustomMap() : size(0), pairs() {}

    void insert(const K& key, const V& value)
    {
        if (size < MAX_SIZE)
        {
            pairs[size++] = Pair<K, V>(key, value);
        }
        else {
            cerr << "Map is full. Cannot insert more elements." << endl;
        }
    }

    V get(const K& key) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (strcmp(pairs[i].first, key) == 0) {
                return pairs[i].second;
            }
        }
        return ""; // Return default empty string if key not found
    }

    bool find(const K& key) const
    {
        for (int i = 0; i < size; ++i) {
            if (strcmp(pairs[i].first, key) == 0) {
                return true; // Key found
            }
        }
        return false; // Key not found
    }

    int getSize() const
    {
        return size;
    }

    Pair<K, V>& operator[](int index)
    {
        if (index < 0 || index >= size) {
            cerr << "Index out of bounds." << endl;
            // Return a default pair if index is out of bounds
            static Pair<K, V> default_pair;
            return default_pair;
        }
        return pairs[index];
    }

    // Function to get all keys stored in the map
    void getKeys(K* keys) const
    {
        int current_index = 0;

        for (int i = 0; i < size; ++i) {
            bool found = false;
            for (int j = 0; j < current_index; ++j)
            {

                if (strcmp(keys[j], pairs[i].first) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                keys[current_index++] = pairs[i].first;
            }
        }
    }

    // Function to count the number of elements with a specific key
    int count(const K& key) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (strcmp(pairs[i].first, key) == 0) {
                return 1; // Key found, return 1
            }
        }
        return 0; // Key not found, return 0
    }
};



// Custom function to check if a character is an alphabet letter
bool my_isalpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Custom function to check if a character is alphanumeric
bool my_isalnum(char c) {
    return my_isalpha(c) || (c >= '0' && c <= '9');
}

// Custom function to check if a character is a whitespace character
bool my_isspace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

// Custom function to check if a character is a punctuation character
bool my_ispunct(char c)
{
    // Define a list of punctuation characters


    // add more punctuations here. 
    const char punctuations[] = ".,;:!?\"'()[]{}<>-=+*&|^%~`\\/";

    for (int i = 0; punctuations[i] != '\0'; ++i)
    {
        if (c == punctuations[i]) {
            return true;
        }
    }
    return false;
}

bool my_isdigit(char c)
{
    return c >= '0' && c <= '9';
}




#define _StackCheck static_assert(ScannerStackSize <= 500,  "MAX_SIZE must be less than or equal to 500.");
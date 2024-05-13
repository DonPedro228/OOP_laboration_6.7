#include <iostream>
#include <algorithm> 
#include <vector>
#include "Array.h"

using namespace std;

template<class T>
struct symmetric_difference {
    bool operator()(const T& a, const T& b) const {
        return a != b;
    }
};

template<class InputIterator1, class InputIterator2, class OutputIterator>
static int set_xor(InputIterator1 first_a, InputIterator1 last_a,
    InputIterator2 first_b, InputIterator2 last_b,
    OutputIterator result) {
    int count = 0;
    while (first_a != last_a && first_b != last_b) {
        if (*first_a != *first_b) {
            *result = *first_a;
            ++first_a;
        }
        else {
            ++first_a;
            ++first_b;
            continue;
        }
        ++result;
        ++count;
    }
    while (first_a != last_a) {
        *result = *first_a;
        ++first_a;
        ++result;
        ++count;
    }
    while (first_b != last_b) {
        *result = *first_b;
        ++first_b;
        ++result;
        ++count;
    }
    return count;
}

template<class InputIterator1, class InputIterator2, class OutputIterator, class Functor>
static int set_xor_if(InputIterator1 first_a, InputIterator1 last_a,
    InputIterator2 first_b, InputIterator2 last_b,
    OutputIterator result, Functor comp) {
    int count = 0;
    while (first_a != last_a && first_b != last_b) {
        if (comp(*first_a, *first_b)) {
            *result = *first_a;
            ++first_a;
        }
        else if (comp(*first_b, *first_a)) {
            *result = *first_b;
            ++first_b;
        }
        else {
            ++first_a;
            ++first_b;
            continue;
        }
        ++result;
        ++count;
    }
    while (first_a != last_a) {
        *result = *first_a;
        ++first_a;
        ++result;
        ++count;
    }
    while (first_b != last_b) {
        *result = *first_b;
        ++first_b;
        ++result;
        ++count;
    }
    return count;
}

int main() {
    int n;
    cout << "Enter the size of the arrays: ";
    cin >> n;

    Array a = Array(n);
    Array::iterator l = const_cast<Array::iterator>(a.begin());
    cout << "Enter values for the array a:\n";
    for (int j = 0; j < n; j++, l++) {
        Array::value_type val;
        cin >> val;
        *l = val;
    }
    sort(a.begin(), a.end());

    a.sumAverage(a.begin(), n);
    cout << "Array with sum and average: ";
    cout << a << endl;

    a.square_min(a.begin(), n);
    cout << "Array with min square: ";
    cout << a << endl;


    Array b = Array(n);
    l = const_cast<Array::iterator>(b.begin());
    cout << "Enter values for the array b:\n";
    for (int j = 0; j < n; j++, l++) {
        Array::value_type val;
        cin >> val;
        *l = val;
    }
    sort(b.begin(), b.end());

    b.sumAverage(b.begin(), n);
    cout << "Array with sum and average: ";
    cout << b << endl;

    b.square_min(b.begin(), n);
    cout << "Array with min square: ";
    cout << b << endl;

    vector<Array::value_type> result;

    set_xor(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));

    cout << "Result of symmetric difference: ";
    for (auto val : result) {
        cout << val << " ";
    }
    cout << endl;

    Array::symmetric_difference<Array::value_type> sym_diff;
    result.clear();
    set_xor_if(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result), sym_diff);

    cout << "Result of symmetric difference (with custom functor): ";
    for (auto val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

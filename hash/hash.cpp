// hash.cpp


#include "hash.h"
#include <cstddef>
#include <cmath>
#include <string>


const int MOD = 1000003;

int hash(int n) {
    return n % MOD;
}


int hash(const std::string&) {

}

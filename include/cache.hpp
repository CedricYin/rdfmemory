#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include "common.hpp"

#define SIZE 2147483648

using namespace std;

class Cache {
public:
    static Cache& instance() {
        static Cache cache;
        return cache;
    }



public:
    vector<string> p_vec { };
    vector<string> s_vec { };
    vector<vector<string>> o_vec { };

    bitset<SIZE> s_bits { };
    vector<bitset<SIZE>> o_bits { };

    vector<vector<Point>> space { };
    vector<string> time { };

    int got_space { 0 };
    Point space_wait { };

    bool got_time { false };
    vector<string> o_vec_wait { };
private:
    Cache() = default;
    ~Cache() = default;
    Cache(const Cache& cache) = delete;
    Cache& operator=(const Cache& cache) = delete;
    Cache(Cache&& cache) = delete;
};
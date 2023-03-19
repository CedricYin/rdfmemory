#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>
#include "cache.hpp"

using namespace std;

struct Triple {
    string s { "" };
    string p { "" };
    string o { "" };
};

struct Point {
    string lon { -1 };
    string lat { -1 };
    string alt { -1 };
};

vector<Triple> read_datas(string filepath) {
    ifstream fin { filepath };
    vector<Triple> tri_vec { };
    if (!fin) {
        cerr << "error: open file failed" << endl;
        return { };
    }
    string tmp { };
    while (getline(fin, tmp)) {
        Triple tri { };
        istringstream iss { tmp };
        string t { };
        for (int i = 0; i < 3; ++i) {
            getline(iss, t, ' ');
            if (i == 0) {
                tri.s = t;
            } else if (i == 1) {
                tri.p = t;
            } else {
                tri.o = t;
            }
        }
        tri_vec.push_back(tri);
    }
    return tri_vec;
}    

bool is_contain(vector<string>& vec, string& s) {
    for (auto& v : vec) {
        if (v == s) {
            return true;
        }
    }
    return false;
}

void insert_object(string obj) {
    auto& cache { Cache::instance() };
    if (cache.got_time) {  // 如果时间更新过，就加入
        int index { cache.time.size() - 1 };
        for (auto o : cache.o_vec_wait) {
            cache.o_vec[index].push_back(o);
        }
        cache.o_vec[index].push_back(obj);
        cache.got_time = false;
        cache.o_vec_wait.clear();
    } else {  // 否则，缓存起来，等待时间更新时再加入
        cache.o_vec_wait.push_back(obj);
    }
}

void insert_object(Point obj) {
    auto& cache { Cache::instance() };
    if (cache.got_time) {  // 如果时间更新过，就加入
        int index { cache.time.size() - 1 };
        cache.space[index].push_back(obj);
        cache.got_time = false;
    }
}

void insert_space(const string& pre, string obj) {
    auto& cache { Cache::instance() };
    if (++cache.got_space == 3) {
        cache.got_space = 0;
        if (pre == "longitude") {
            cache.space_wait.lon = obj;
        } else if (pre == "latitude") {
            cache.space_wait.lat = obj;
        } else {
            cache.space_wait.alt = obj;
        }
        insert_object(cache.space_wait);
    } else {
        if (pre == "longitude") {
            cache.space_wait.lon = obj;
        } else if (pre == "latitude") {
            cache.space_wait.lat = obj;
        } else {
            cache.space_wait.alt = obj;
        }
    }
}

void deal_object(const string& pre, string obj) {
    auto& cache { Cache::instance() };
    if (pre == "longitude") {
        insert_space("longitude", obj);
    } else if (pre == "latitude") {
        insert_space("latitude", obj);
    } else if (pre == "altitude") {
        insert_space("altitude", obj);
    } else if (pre == "time") {
        cache.got_time = true;
        cache.time.push_back(obj);
    } else {
        insert_object(obj);
    }
}

int process_datas(string file_path) {
    auto tri_vec { read_datas(file_path) };
    Cache& cache { Cache::instance() };

    for (auto& t : tri_vec) {
        bool is_contain_p = true;
        bool is_contain_s = true;
        if (!is_contain(cache.p_vec, t.p)) {
            cache.p_vec.push_back(t.p);
            is_contain_p = false;
        }
        if (!is_contain(cache.s_vec, t.s)) {
            cache.s_vec.push_back(t.s);
            is_contain_s = false;
        }
        deal_object(t.p, t.o);
    }
    return 0;
}

int process_query(string query) {

}
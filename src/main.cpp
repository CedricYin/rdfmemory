#include <iostream>
#include "common.hpp"

using namespace std;

int main() {
    while (true) {
        // 输入
        // 格式1：query:
        // 格式2：datas：
        string input;
        cin >> input;
        string input_type = input.substr(0, 5);
        string input_info = input.substr(6);
        if (input_type == "datas") {
            if (process_datas(input_info) != 0) {
                cerr << "precess_data error" << endl;
                continue;
            }
        } else if (input_type == "query") {
            if (process_query(input_info) != 0) {
                cerr << "query_data error" << endl;
                continue;
            }
        } else {
            cerr << "Usage: query:<query info> or datas:<filepath>" << endl;
            continue; 
        }
    }

    return 0;
}
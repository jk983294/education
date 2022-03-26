#include <data.h>
#include <math_random.h>
#include <unistd.h>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void help() {
    std::cout << "Program options:" << std::endl;
    std::cout << "  -h                                    list help" << std::endl;
    std::cout << "  -m arg (=\"10\")                          max value" << std::endl;
    std::cout << "  -r arg (=\"10\")                          result max value" << std::endl;
    std::cout << "  -b arg (=\"10\")                          batch" << std::endl;
    std::cout << "  -n arg (=\"false\")                 allow negative" << std::endl;
    std::cout << "  -p arg (=\"false\")                 product only" << std::endl;
    cout << "usage:\n";
    cout << "plus -m 20 -r 40 -n" << endl;
}

int main(int argc, char** argv) {
    int max_value = 10, result_max_value = 10;
    size_t batch = 10;
    bool negative = false;
    bool product_only = false;

    int opt;
    while ((opt = getopt(argc, argv, "hnpm:b:r:")) != -1) {
        switch (opt) {
            case 'n':
                negative = true;
                break;
            case 'p':
                product_only = true;
                break;
            case 'm':
                max_value = std::stoi(optarg);
                break;
            case 'r':
                result_max_value = std::stoi(optarg);
                break;
            case 'b':
                batch = std::stoul(optarg);
                break;
            case 'h':
                help();
            default:
                return 0;
        }
    }

    ornate::MyRandom myRandom(0, max_value);
    vector<PlusEntry> vec;
    std::set<PlusEntry> entries;
    while (vec.size() < batch) {
        PlusEntry entry;
        entry.x = myRandom.random_int();
        entry.y = myRandom.random_int();
        entry.type = static_cast<OpType>(myRandom.random_int(0, 1));
        if (product_only) entry.type = OpType::Prod;
        if (entry.calc()) continue;
        if (!negative && entry.result < 0) continue;
        if (std::abs(entry.result) > result_max_value) continue;
        if (entries.find(entry) != entries.end()) continue;

        entries.insert(entry);
        vec.push_back(entry);
    }

    cout << "question:\n";
    for (auto& entry : vec) {
        cout << entry.get_question_expr() << endl;
    }
    cout << "press 'y' to get answer:\n";
    char ch;
    while (true) {
        cin >> ch;
        if (ch == 'y') {
            cout << "answer:\n";
            for (auto& entry : vec) {
                cout << entry.get_answer_expr() << endl;
            }
            break;
        } else if (ch == 'q')
            break;
    }

    return 0;
}

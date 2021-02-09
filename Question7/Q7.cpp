#include <vector>
#include <iostream>
#include <fstream>
#include<string>
using namespace std;

vector<int> fromIndexToCord(const vector<int>& dimensionLength, int index) {
    int dimensionSum = dimensionLength[0];
    auto res = vector<int>();
    res.push_back(index % dimensionSum);
    for (auto i=0; i<dimensionLength.size()-2; ++i) {
        const auto lastDimensionSum = dimensionSum;
        dimensionSum *= dimensionLength[i+1];
        res.push_back(index % dimensionSum / lastDimensionSum);
    }
    res.push_back(index / dimensionSum);
    return res;
}

int fromCordToIndex(const vector<int>& dimensionLength, const vector<int>& cord) {
    int sum = cord[0];
    int dimensionSum = dimensionLength[0];
    for(int i = 0; i < dimensionLength.size() - 1; ++i) {
        sum += dimensionSum * cord[i+1];
        dimensionSum *= dimensionLength[i+1];
    }
    return sum;
}

int main() {
    // 7.1 b)
    auto cordFile = ifstream("input_coordinates_7_1.txt");
    auto out = ofstream("output_index_7_1.txt");
    char buffer[32];
    // drop x1, x2 row
    cordFile.getline(buffer, 32);
    vector<int> dimension{50, 57};
    out << "index\n";
    while (true) {
        cordFile.getline(buffer, 32, '\n');
        if (buffer[0] == '\0') break;
        size_t pos;
        auto x = stoi(buffer, &pos);
        auto y = stoi(buffer + pos);
        out << fromCordToIndex(dimension, {x, y}) << endl;
    }

    auto indexFile = ifstream("input_index_7_1.txt");
    out = ofstream("output_coordinates_7_1.txt");
    // drop index row
    indexFile.getline(buffer, 32);
    out << "x1\tx2\n";
    while (true) {
        indexFile.getline(buffer, 32, '\n');
        if (buffer[0] == '\0') break;
        auto index = stoi(buffer);
        auto&& cord = fromIndexToCord(dimension, index);
        out << cord[0] << "\t" << cord[1] << endl;
    }

    // 7.2 b)
    cordFile = ifstream("input_coordinates_7_2.txt");
    out = ofstream("output_index_7_2.txt");
    // drop x1, x2... row
    cordFile.getline(buffer, 32);
    dimension = {4,8,5,9,6,7};
    out << "index\n";
    while (true) {
        cordFile.getline(buffer, 32, '\n');
        if (buffer[0] == '\0') break;
        size_t pos = 0;
        auto cord = vector<int>{};
        for (auto _: dimension) {
            size_t tmp = 0;
            cord.emplace_back(stoi(buffer + pos, &tmp));
            pos += tmp;
        }
        out << fromCordToIndex(dimension, cord) << endl;
    }

    indexFile = ifstream("input_index_7_2.txt");
    out = ofstream("output_coordinates_7_2.txt");
    // drop index row
    indexFile.getline(buffer, 32);
    out << "x1\tx2\tx3\tx4\tx5\tx6\n";
    while (true) {
        indexFile.getline(buffer, 32, '\n');
        if (buffer[0] == '\0') break;
        auto index = stoi(buffer);
        auto&& cord = fromIndexToCord(dimension, index);
        for (auto i = 0; i < cord.size() - 1; ++i) {
            out << cord[i] << '\t';
        }
        out << cord[cord.size()-1] << endl;
    }
}
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::ofstream out("./output_question_1.txt");

void solution(unsigned long m, unsigned long n, unsigned long sum) {
    // First, the final operations sequence will has
    // exactly n-1 Rs and m-1 Ds.
    // It's not hard to prove that with given matrix,
    // minimum summed number is m * (m + 1) / 2 + n -1,
    // which correspond to a operations sequence of:
    // RRR...RRRDDD...DDD
    // Then, when we change a "RD" sequence in operations to DR,
    // the changed sequence is still valid and the sum will increase 1.
    // If we do such change to first "RD" sequence in above sequence n - 1 times,
    // the operations will look like:
    // DRRR...RRRDDD...DDD
    // Using this pattern, following algorithm is effective:
    unsigned long minSum = m * (m + 1) / 2 + n - 1;
    auto remain = sum - minSum;
    unsigned long prefixDNum = remain / (n - 1);
    remain %= (n - 1);
    // In some cases, it's impossible to form a option sequence to exceed
    // such a total sum.
    if (prefixDNum > m - 1 || (prefixDNum == m - 1 && remain > 0)) {
        out << "invalid";
        return;
    }
    // Till here, remain difference with expected sum are less than n - 1.
    // We do the same operations, but only remain times.
    // from DD...DDRR...RRDD..DD
    // to DD...DDRR..RRDRR..RRDD..DD
    auto totalRNum = n - 1;
    auto requiredRNumAfterSingleD = remain;
    auto RNumBeforeSingleD = totalRNum - requiredRNumAfterSingleD;
    auto trailDNum = m - 2 - prefixDNum;
    for (auto i = 0; i < prefixDNum; ++i) {
        out << "D";
    }
    for (auto i = 0; i < RNumBeforeSingleD; ++i) {
        out << "R";
    }
    out << "D";
    for (auto i = 0; i < requiredRNumAfterSingleD; ++i) {
        out << "R";
    }
    for (auto i = 0; i < trailDNum; ++i) {
        out << "D";
    }
}

int main() {
    // case (a)
    unsigned long m = 9, n = 9;
    auto sumList = vector<unsigned long>{ 65, 72, 90, 110 };
    for (auto sum: sumList) {
        out << sum << " ";
        solution(m, n, sum);
        out << endl;
    }
    out << endl;
    // case (b)
    m = 90000, n = 100000, sumList = vector<unsigned long>{ 5994891682 };
    for (auto sum: sumList) {
        out << sum << " ";
        solution(m, n, sum);
        out << endl;
    }
    return 0;
}


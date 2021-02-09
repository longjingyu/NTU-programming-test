#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<char>> solve(int L, vector<pair<char, int>> beads) {
    uint8_t separation = 0;
    uint8_t minDeltaSeparation = 0;
    int minDelta = numeric_limits<int>::max();
    const uint8_t separationMax = (1 << beads.size()) - 1;
    for(;separation < separationMax; ++separation) {
        auto tmp = separation;
        auto sum0 = 0, sum1 = 0;
        for(auto & bead : beads) {
            ((tmp & 1) ? sum1 : sum0) += bead.second;
            tmp >>= 1;
        }
        if (abs(sum0 - sum1) < abs(minDelta)) {
            minDelta = sum0 - sum1;
            minDeltaSeparation = separation;
        }
    }
    vector<int> moreTeamIndex, lessTeamIndex;
    const auto moreTeam = minDelta < 0 ? 1 : 0;
    const auto switchAfterNewLine = (L & 1) == 0;
    for (auto i=0;i<beads.size();++i) {
        ((minDeltaSeparation & 1) == moreTeam ? moreTeamIndex : lessTeamIndex).push_back(i);
        minDeltaSeparation >>= 1;
    }
    bool isLess = switchAfterNewLine;
    auto moreTeamIter = moreTeamIndex.begin();
    auto lessTeamIter = lessTeamIndex.begin();
    auto moreTeamEachColorReserve = abs(minDelta) / moreTeamIndex.size();
    const auto firstRoundTimes = ((L * L / 2) - (abs(minDelta) / 2)) * 2;
    auto result = vector<vector<char>>{};
    int cnt = 0;
    for (; cnt < firstRoundTimes; ++cnt, isLess = !isLess) {
        if (cnt % L == 0) {
            if (switchAfterNewLine) {
                isLess = !isLess;
            }
            result.emplace_back();
        }
        if (!isLess) {
            while(beads[*moreTeamIter].second <= moreTeamEachColorReserve) {
                ++moreTeamIter;
                if (moreTeamIter == moreTeamIndex.end()) {
                    moreTeamIter = moreTeamIndex.begin();
                }
            }
            beads[*moreTeamIter].second--;
            result[result.size()-1].emplace_back(beads[*moreTeamIter].first);
            ++moreTeamIter;
            if (moreTeamIter == moreTeamIndex.end()) {
                moreTeamIter = moreTeamIndex.begin();
            }
        } else {
            while(beads[*lessTeamIter].second == 0) {
                ++lessTeamIter;
                if (lessTeamIter == lessTeamIndex.end()) {
                    lessTeamIter = lessTeamIndex.begin();
                }
            }
            beads[*lessTeamIter].second--;
            result[result.size()-1].emplace_back(beads[*lessTeamIter].first);
            ++lessTeamIter;
            if (lessTeamIter == lessTeamIndex.end()) {
                lessTeamIter = lessTeamIndex.begin();
            }
        }
    }
    for (;cnt < L * L; ++cnt) {
        const auto currentRow = cnt / L;
        const auto currentCol = cnt % L;
        while (true) {
            const auto currentBead = beads[*moreTeamIter];
            if (currentBead.second != 0 &&
                currentCol > 0 && currentBead.first != result[currentRow][currentCol-1] &&
                currentBead.first != result[currentRow-1][currentCol]) {
                break;
            }
            ++moreTeamIter;
            if (moreTeamIter == moreTeamIndex.end()) {
                moreTeamIter = moreTeamIndex.begin();
            }
        }
        result[result.size()-1].push_back(beads[*moreTeamIter].first);
        beads[*moreTeamIter].second--;
    }
    return result;
}

int main() {
    // 5.1
    auto out = ofstream(".\\output_question_5_1.txt");
    auto beads0 = vector<pair<char, int>> {
            {'R', 12},
            {'B', 13},
    };
    auto&& r0 = solve(5, beads0);
    for (auto& row: r0) {
        for(auto& i: row) {
            out << i;
        }
        out << endl;
    }
    //5.2
    out = ofstream(".\\output_question_5_2.txt");
    auto beads1 = vector<pair<char, int>>{
            {'R', 139},
            {'B', 1451},
            {'G', 977},
            {'W', 1072},
            {'Y', 457}
    };
    auto&& r1 = solve(64, beads1);
    for (auto& row: r1) {
        for(auto& i: row) {
            out << i;
        }
        out << endl;
    }
    return 0;
}
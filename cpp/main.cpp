/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/last-stone-weight/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

/*
    You are given an array of integers stones where 
    stones[i] is the weight of the ith stone.

    We are playing a game with the stones.
    On each turn, we choose the heaviest two stones and smash them together.
    Suppose the heaviest two stones have weights x and y with x <= y.
    The result of this smash is:

        If x == y, both stones are destroyed, and
        If x != y, the stone of weight x is destroyed,
        and the stone of weight y has new weight y - x.
    
    At the end of the game, there is at most one stone left.
    Return the weight of the last remaining stone.
    If there are no stones left, return 0.

    Constraints:

        * 1 <= stones.length <= 30
        * 1 <= stones[i] <= 1000

    Solution #1:

    Load all stones into a max heap.
    While there is more than one value on the heap,
    pop two values and smash them.  Push the resulting stone
    of the smash (if any) back on the heap.
    Return the last remaining value on the heap, if there is
    one, else return zero.

    Time = O(n+30*(log2(n)/2+log2(n)/2+log2(n)/2)
         => O(n+30*2*log2(n)/2)
         => O(n+log2(n))
         n = initial population size (stones.size())
         log2(n) = heap push() and pop()
    
    Space = O(n)  [heap size]
*/
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int> heap{stones.begin(), stones.end()};

        while (1 < heap.size()) {
            auto const x = heap.top();
            heap.pop();
            auto const y = heap.top();
            heap.pop();
            if (x != y) {
                heap.push(std::abs(y - x));
            }
        }

        return heap.empty() ? 0 : heap.top();
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<int> stones{2,7,4,1,8,1};
    int expected = 1;
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto result =  Solution{}.lastStoneWeight(stones);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

/*
    End of "main.cpp"
*/

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) {
            vector<vector<int>> empty;
            return empty;
        }
        
        set<vector<int>> s;
        for(vector<int>::iterator it1 = nums.begin(); it1 != nums.end(); ++it1) {
            for(vector<int>::iterator it2 = nums.begin(); it2 != nums.end(); ++it2) {
                for(vector<int>::iterator it3 = nums.begin(); it3 != nums.end(); ++it3) {
                    if (it1 == it2 || it1 == it3 || it2 == it3) {
                        continue;
                            
                    }
                    if (*it1 + *it2 + *it3 == 0) {
                        vector<int> tmp = {*it1, *it2, *it3};
                        sort(tmp.begin(), tmp.end(), less_equal<int>()); 
                        s.insert(tmp);
                    }
                }
            }
        }
        
        vector<vector<int>> v(s.begin(), s.end());
        return v;
    }
};

int main() {
    Solution *p = new Solution;
    vector<int> num = {-1,0,1,2,-1,-4};
    vector<vector<int>> a = p->threeSum(num);
    return 0;
}
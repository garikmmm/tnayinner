class Solution {
public:
    double myPow(double x, int n) {
        n = INT_MIN == n ? n + 2 : n;
        double pow = recursion(x, abs(n));
        return n >=0 ? pow : 1 / pow;
    }
    
    double recursion(double x, int n) {
        if (x == 0) {
            return 0;
        }
        if (x == 1) {
            return 1;
        }
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return x;
        }
        if (n == 2) {
            return x * x;
        }
        
        int halfN = (int) (n / 2);
        double pow = recursion(x * x, halfN);
        if (n % 2 == 1) {
            pow = pow * x;
        }
        return pow;
    }
};

int main() {
    Solution *p = new Solution;
    int pow = p->myPow(5, 5);
    return 0;
}
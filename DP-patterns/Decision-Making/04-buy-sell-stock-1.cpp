// Atmost 1 transaction
// selling at the ith day, when should i buy for max profit?
// buying has to be done [0 ... i - 1]
// for max profit, buying price = min(price[0] .. price[i])

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int res = 0, min_till_now = INT_MAX;

        for (int i = 0; i < prices.size(); ++i)
        {
            min_till_now = min(min_till_now, prices[i]);
            res = max(res, prices[i] - min_till_now);
        }

        return res;
    }
};
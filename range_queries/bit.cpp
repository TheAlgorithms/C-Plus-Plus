// Binary Indexed Tree.
#include <iostream>

using namespace std;

class Bit
{
    int n;
    vector<int> bit;
    inline int offset(int x)
    {
        return (x & (-x));
    }

    public:

        Bit(vector<int>& arr)
	{
            n = arr.size();
            bit.assign(n + 1, 0);
            for (int i = 0; i < n; ++i)
	    {
                update(i, arr[i]);
            }
        }
    Bit(int x)
    {
        n = x;
        bit.assign(n + 1, 0);
    }

    void update(int id, int val)
    {
        // Add val at id
        id++;
        while (id <= n)
	{
            bit[id] += val;
            id += offset(id);
        }
    }

    int sum(int id)
    {
        // Get prefix sum upto id.
        id++;
        int res = 0;
        while (id > 0)
	{
            res += bit[id];
            id -= offset(id);
        }
        return res;
    }

    int sum_range(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
};

int main()
{
    int n = 5;
    vector<int> arr = { 1, 2, 3, 4, 5 };
    Bit x(arr);

    assert(x.sum_range(0, 0) == 1);
    assert(x.sum_range(0, 1) == 3);
    assert(x.sum_range(0, 2) == 6);
    x.update(0, 6);
    assert(x.sum_range(0, 0) == 6);
    assert(x.sum_range(0, 1) == 8);
    assert(x.sum_range(0, 2) == 11);
	return 0;
}

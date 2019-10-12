typedef int Value;

struct SegmentTree
{	
	static const int MAXN = 1e5 + 10;
	int n;
	int TYPE;
	vector<Value> st;
	vector<Value> a;
	SegmentTree(int num, string type) : n(num), st(4*num + 10), a(num + 10) {
		if(type == "SUM") TYPE = 1;
		if(type == "MIN") TYPE = 2;
		if(type == "MAX") TYPE = 3;
		if(type == "GCD") TYPE = 4;
	}

	inline Value nullval()
	{
		if(TYPE == 1) return 0;
		if(TYPE == 2) return inf;
		if(TYPE == 3) return -inf;
		if(TYPE == 4) return 0;
		return 0;
	}

	inline Value merge(Value x, Value y)
	{
		if(TYPE == 1) return x + y;
		if(TYPE == 2) return min(x, y);
		if(TYPE == 3) return max(x, y);
		if(TYPE == 4) return __gcd(x, y);
		return 0;
	}

	void build(int id, int l, int r)
	{
		if(l == r)
		{
			st[id] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		st[id] = merge(st[id << 1], st[id << 1 | 1]);
	}

	void update(int id, int l, int r, int pos, Value val, bool increment = false)
	{
		if(l == r)
		{
			if(increment) st[id] += val;
			else st[id] = val;
			return;
		}
		int mid = (l + r) >> 1;
		if(pos <= mid)
		{
			update(id << 1, l, mid, pos, val, increment);
		}
		else
		{
			update(id << 1 | 1, mid + 1, r, pos, val, increment);
		}
		st[id] = merge(st[id << 1], st[id << 1 | 1]);
	}

	Value query(int id, int l, int r, int s, int e)
	{
		if(s > r or e < l)
		{
			return nullval();
		}
		if(l >= s and r <= e)
		{
			return st[id];
		}
		int mid = (l + r) >> 1;
		Value q1 = query(id << 1, l, mid, s, e);
		Value q2 = query(id << 1 | 1, mid + 1, r, s, e);
		return merge(q1, q2);
	}

	void build()
	{
		build(1, 1, n);
	}

	void update(int pos, Value val, bool increment = false)
	{
		update(1, 1, n, pos, val, increment);
	}

	Value query(int s, int e)
	{
		return query(1, 1, n, s, e);
	}
};


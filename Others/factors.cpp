
	//	Time	O(sqrt(a))
	//	Space	O(num_facts(a)*1.5)


std::vector<int> Factors;
void all_factors(int a){
	Factors.resize(0);
	std::vector<int> v;
	for (int i = 1; i < sqrt(a); ++i)
	{
		if (a%i==0)
		{
			if (a/i!=i)
			{
				v.push_back(a/i);
			}
			Factors.push_back(a);
		}
	}
}

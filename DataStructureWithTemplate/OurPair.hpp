#ifndef OUR_PAIR_H
#define OUR_PAIR_H

template <typename T1, typename T2>
// T1 and T2 are semiregular or regular or totally ordered

class OurPair
{
	public:
    	T1 first;
        T2 second;

	//semiregular
    OurPair(const T1& x, const T2& y) : first(x), second(y) {}

	OurPair() {}

	~OurPair() {}
    
	OurPair<T1,T2>& operator=(const OurPair<T1,T2>& x) {
		first = x.first;
        second = x.second;
		return *this;
	}

	//regular
	friend
	bool operator==(const OurPair<T1,T2>& x, const OurPair<T1,T2>& y){
		return x.first == y.first && x.second == y.second;
	}

	friend
    bool operator!=(const OurPair<T1,T2>& x, const OurPair<T1,T2> y){
                return !(x == y);
	}

	//totally ordered
	friend
    bool operator<(const OurPair<T1,T2> x, const OurPair<T1,T2> y){
       return x.first < y.first && x.second < y.second;
	}

	friend
    bool operator>(const OurPair<T1,T2> x, const OurPair<T1,T2> y){
        return y < x;
	}

	friend
    bool operator<=(const OurPair<T1,T2> x, const OurPair<T1,T2> y){
        return !(y < x);
	}

	friend
    bool operator>=(const OurPair<T1,T2> x, const OurPair<T1,T2> y){
        return !(x < y);
	}

	friend
	void print(const OurPair<T1,T2> x){
		std::cout << x.first << ' ' << x.second << std::endl;
	}

};




#endif  

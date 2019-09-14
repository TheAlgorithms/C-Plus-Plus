#ifndef SINGLE_H
#define SINGLE_H

template <typename T>
// T is semiregular or regular or totally ordered

class Single
{
	public:
    T value;

	//conversions 
	explicit Single(const T& x) : value(x) {}

	//semiregular
	Single(const Single& x) : value(x.value) {}

	Single() {}

	~Single() {}

	Single& operator=(const Single& x) {
		value = x.value;
		return *this;
	}

	//regular
	friend
	bool operator==(const Single& x, const Single& y){
		return x.value == y.value;
	}

	friend
    bool operator!=(const Single& x, const Single& y){
                return !(x == y);
	}

	//totally ordered
	friend
    bool operator<(const Single& x, const Single& y){
       return x.value < y.value;
	}

	friend
    bool operator>(const Single& x, const Single& y){
        return y < x;
	}

	friend
    bool operator<=(const Single& x, const Single& y){
        return !(y < x);
	}

	friend
    bool operator>=(const Single& x, const Single& y){
        return !(x < y);
	}

	friend
	void print(const Single& x){
		std::cout << x.value << std::endl;
	}

};




#endif  
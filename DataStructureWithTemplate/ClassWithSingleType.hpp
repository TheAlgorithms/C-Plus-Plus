#ifndef SINGLE_TYPE_H
#define SINGLE_TYPE_H

template <typename T>
// T is semiregular or regular or totally ordered

class SingleType
{
	public:
    	T value;

	//conversions 
	explicit SingleType(const T& x) : value(x) {}

	//semiregular
	SingleType(const SingleType& x) : value(x.value) {}

	SingleType() {}

	~SingleType() {}

	SingleType& operator=(const SingleType& x) {
		value = x.value;
		return *this;
	}

	//regular
	friend
	bool operator==(const SingleType& x, const SingleType& y){
		return x.value == y.value;
	}

	friend
    bool operator!=(const SingleType& x, const SingleType& y){
                return !(x == y);
	}

	//totally ordered
	friend
    bool operator<(const SingleType& x, const SingleType& y){
       return x.value < y.value;
	}

	friend
    bool operator>(const SingleType& x, const SingleType& y){
        return y < x;
	}

	friend
    bool operator<=(const SingleType& x, const SingleType& y){
        return !(y < x);
	}

	friend
    bool operator>=(const SingleType& x, const SingleType& y){
        return !(x < y);
	}

	friend
	void print(const SingleType& x){
		std::cout << x.value << std::endl;
	}

};




#endif  

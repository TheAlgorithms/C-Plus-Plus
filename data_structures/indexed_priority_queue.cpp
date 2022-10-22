/**
 * @file
 * @brief This is an implementation of an min indexed priority queue,
 * which, unlike a regular priority queue, has key value pairs, which 
 * can be looked up in O(1), just like a hashmap. lower priority numbers
 * refer to higher priority.
 * @details
 * As mentioned in the brief, an indexed priority queue operates on 
 * the basis of a hashmap, providing its benefit of having O(1) searching
 * and log(N) modification/removal of ANY key in the queue (not only the front)
 * but also the benefits of a priority queue for polling min values in 
 * logarithmic time or having its heap properties. The keys in this 
 * implementation are the unique identifiers or stored values of the 
 * queue, whilst the values refer to the comparable that will be used
 * to prioritise different items. 
 * refer to william fiset's video for a more detailed explanation:
 * https://youtu.be/jND_WJ8r7FE
 * @author [ron0studios](https://github.com/ron0studios)
 */


#include <vector>          /// for std::vector
#include <utility>        /// for std::pair
#include <unordered_map> /// for std::unordered_map
#include <cmath>        /// for std::floor
#include <string>       /// for std::string
#include <cassert>      /// for assert


/**
 * @brief This is the class used to instantiate the indexed priority queue
 * @tparam T1 this is the identifier value for the queue, and is what will be
 * stored in the data-structure. Please make sure this is a HASHABLE type!
 * @tparam T2 this is the priority value for the queue, used to prioritise
 * certain items over other. Please make sure this is both HASHABLE and 
 * COMPARABLE!
 */
template <class T1 = int, class T2 = int>
class IPQ
{
	private:
		std::unordered_map<T1,T2> val; ///< key : val
		std::unordered_map<T1,int> pm; ///< key : heap index
		std::unordered_map<int,T1> im; ///< heap index : key
		int size = 0; ///< the size of the heap
		
	public:
						
		/**
		 * @brief Constructor for IPQ
		 * @param keyval this is a vector of key value pairs used initially (optional)
		 */
        explicit IPQ(std::vector<std::pair<T1, T2>> keyval =
                         std::vector<std::pair<T1, T2>>()) {
            for(auto const &i : keyval){
				insert(i.first, i.second);
			}
        }

        /**
		 * @brief check if the queue contains a certain key
		 * @param key the key to check for
	     */
		bool contains(T1 key)
		{
            if (pm.count(key)) {  // c++11
                return true;
            }
            return false;
		}

		/**
		 * @brief inserts a key-value pair into the heap
		 * @param key the key to insert
		 * @param value the key's associated priority
	     */
		void insert(T1 key, T2 value)
		{
			// add node to bottom right of heap
			val[key] = value;
			pm[key] = size;
			im[size] = key;

			//swim
			swim(size);
			size++;
		}

		/**
		 * @brief peeks the front of the priority queue
		 * @returns a key value pair of T1 and T2
	     */
		std::pair<T1,T2> peek()
		{
			std::pair<T1,T2> x = std::make_pair(im[0], val[im[0]]);
			return x;
		}

		/**
		 * @brief removes the front element of the priority queue
		 * @returns a key value pair of the front element before popping
	     */
		std::pair<T1,T2> pop()
		{
			std::pair<T1,T2> x = std::make_pair(im[0], val[im[0]]);
			remove(im[0]); // O(logn)
			return x;
		}

		/**
		 * @brief removes a given key of the priority queue
		 * @param key the key to remove
	     */
		void remove(T1 key)
		{
			if(!contains(key)) return;

			int pos = pm[key];
			swap(pos,size-1);
			size--;

			val.erase(key);
			pm.erase(key);
			im.erase(size);

			sink(pos);
			swim(pos);
		}

		/**
		 * @brief returns the number of elements in the IPQ
	     */
		int getSize()
		{
			return size;
		}

	private:
		
		/**
		 * @brief swaps two key value pairs in the heap
		 * @param i the heap index of the first pair
		 * @param j the heap index ot the second pair
	     */
		void swap(int i, int j)
		{
			pm[im[j]] = i;
			pm[im[i]] = j;
			T1 tmp = im[i];
			im[i] = im[j];
			im[j] = tmp;
		}
		
		/**
		 * @brief An algorithm to set a misplaced item in a heap
		 * to its correct place by swapping with children.
		 * @param node the heap index to sink
	     */
		void sink(int node) 
		{
			while(true)
			{
				// children of a heap are represented as such
				int left = (2*node)+1; 
				int right = (2*node)+2;
                int smallest = 0;

                if (left >= size) {
                    smallest = right;
                } else if (right >= size) {
                    smallest = left;
                } else {
                    smallest = (val[im[left]] < val[im[right]]) ? left : right;
                }

                if (left >= size && right >= size) {
                    break;
                }

                if (val[im[smallest]] >= val[im[node]]) {
                    break;
                }

                swap(smallest,node);
				node = smallest;

			}
		}

		/**
		 * @brief An algorithm to set a misplaced item in a heap
		 * to its correct place by swapping with parents.
		 * @param node the heap index to swim
	     */
		void swim(int node) 
		{
			int i = std::floor((node-1)/2);
			while(i >= 0 && val[im[node]] < val[im[i]])
			{
				swap(i,node);
				node = i;
				i = std::floor((node-1)/2);
			}
		}
};

static void test() {
	// test round A (basic insertion)
	IPQ<int,int> ipqA;
	ipqA.insert(30,0);
	ipqA.insert(29,10);
	ipqA.insert(290,1);
	ipqA.insert(5,2);

	std::vector<std::pair<int,int>> heapA;
	while(ipqA.getSize())
	{
		auto x = ipqA.pop();
		heapA.push_back(x);
	}

	std::vector<std::pair<int,int>> expectedA = {
		{30,0},
		{290,1},
		{5,2},
		{29,10}
	};

	assert(heapA == expectedA);

	// test round B (insertion, deletion and template params)
	IPQ<std::string,int> ipqB;
	ipqB.insert("F#",0);
	ipqB.insert("",0);
	ipqB.insert("Ron0Studios",10);
	ipqB.insert("c++",1);
	ipqB.insert("python",3);
	ipqB.remove("random");
	ipqB.remove("c++");

	std::vector<std::pair<std::string,int>> heapB;
	while(ipqB.getSize())
	{
		auto x = ipqB.pop();
		heapB.push_back(x);
	}

	std::vector<std::pair<std::string,int>> expectedB = {
		{"F#",0},
		{"",0},
		{"python",3},
		{"Ron0Studios",10}
	};

	assert(heapB == expectedB);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test();  // run self-test implementations
    return 0;
}

non_recursive_merge_sort: non_recursive_merge_sort.cpp
	g++ -std=c++17 -o non_recursive_merge_sort non_recursive_merge_sort.cpp
.PHONY: test
.PHONY: doc
.PHONY: clean
test: non_recursive_merge_sort
	./non_recursive_merge_sort
doc: doxy.txt
	doxygen doxy.txt
clean:
	rm -fr non_recursive_merge_sort html

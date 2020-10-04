#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct process {
	unsigned pid;
	unsigned at;
	unsigned bt;
	unsigned ct;
};

void find_completion_time(std::vector<process> &proc) {
	unsigned count = proc.size();
	unsigned end = 0;
	unsigned time = 0;
	unsigned max_at = std::max_element(
			proc.begin(), proc.end(),
			[] (const process &a, const process &b) -> bool {
			return a.at < b.at;
			})->at + 1;
	while(end < count) {
		unsigned min_at = max_at;
		int idx = -1;
		for(auto &p: proc)
			if (!p.ct && min_at > p.at) {
				min_at = p.at;
				idx = p.pid;
			}
		if (time < min_at)
			time = min_at;
		time += proc[idx].bt;
		proc[idx].ct = time;
		end++;
	}
}

void find_avg_time(std::vector<process> &proc) {
	find_completion_time(proc);

	float ta{0};
	float w{0};

	std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
	for (auto &p: proc) {
		unsigned p_ta = p.ct - p.at;
		unsigned p_w = p_ta - p.bt;
		std::cout << p.pid << '\t' << p.at << '\t'
			<< p.bt << '\t' << p.ct << '\t'
			<< p_ta << '\t' << p_w << '\n';
		ta += p_ta;
		w += p_w;
	}

	ta /= proc.size();
	w /= proc.size();

	std::cout << std::endl;
	std::cout << "Average Waiting Time: " << w << '\n' 
		<< "Average Turn-Around Time: " << ta << '\n';
}

int main() {
	std::vector<process> proc = {
		{0, 5, 2, 0},
		{1, 5, 3, 0},
		{2, 1, 4, 0},
		{3, 2, 2, 0},
		{4, 1, 2, 0},
		{5, 1, 1, 0}
	};

	find_avg_time(proc);

	std::vector<process> test = {
		{0, 5, 2, 12},
		{1, 5, 3, 15},
		{2, 1, 4, 5},
		{3, 2, 2, 10},
		{4, 1, 2, 7},
		{5, 1, 1, 8}
	};

	assert(std::equal(proc.begin(), proc.end(), test.begin(),
				[](const auto &a, const auto &b) {
				return a.ct == b.ct;
				}));

	return 0;
}

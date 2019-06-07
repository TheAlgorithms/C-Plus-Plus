#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cstring>
#include<stack>
#include<queue>
#include<cmath>
using namespace std;

class Knight
{
private:
	int chess_size;
	pair<int, int> start_point;
	pair<int, int> end_point;
	int count;
	int state;
	int **chess;
public:
	Knight(const char * fname)
	{
		count = 0;
		state = 0;
		string line;
		string start_info[10];
		string end_info[10];
		int i = 0;
		ifstream knight(fname);
		if (knight.fail())
		{
			cout << "failed to open file" << endl;
			return;
		}
		getline(knight, line);
		chess_size = stoi(line);

		getline(knight, line);
		char temp[10];
		strcpy(temp, line.c_str());
		char * fline = strtok(temp, " ");
		while (fline != nullptr)
		{
			start_info[i] = string(fline);
			fline = strtok(nullptr, " ");
			i++;
		}
		start_point = make_pair(stoi(start_info[0]), stoi(start_info[1]));

		getline(knight, line);
		char temp2[10];
		strcpy(temp2, line.c_str());
		char * fline2 = strtok(temp2, " ");
		i = 0;
		while (fline2 != nullptr)
		{
			end_info[i] = string(fline2);
			fline2 = strtok(nullptr, " ");
			i++;
		}
		end_point = make_pair(stoi(end_info[0]), stoi(end_info[1]));

		knight.close();
		chess = new int *[chess_size];
		for (int i = 0; i < chess_size; i++)
		{
			chess[i] = new int[chess_size];			//if knight had benn traveled then 1 otherwise 0
			memset(chess[i], 0, sizeof(int)*chess_size);
		}
	}

	void move(pair<int, int> point)
	{
		pair<int, int> cur_point = point;
		queue<pair<int, int>> order;
		chess[cur_point.first][cur_point.second] = 1;
		order.push(cur_point);
		int k;
		int drow[8] = { -2,-1,1,2,-2,-1,2,1 };
		int dcol[8] = { -1,-2,-2,-1,1,2,1,2 };
		pair<int, int> new_point;

		while (!order.empty())
		{
			int qsize = order.size();
			for (int i = 0; i < qsize ;i++)
			{
				cur_point = order.front();
				chess[cur_point.first][cur_point.second] = 1;
				order.pop();
				if (cur_point.first == end_point.first && cur_point.second == end_point.second)
				{
					//cout << count;
					return ;
				}

				for (k = 0; k < 8; k++)
				{
					new_point = make_pair(cur_point.first + drow[k], cur_point.second + dcol[k]);
					if (promise1(new_point) == 1 && promise2(new_point) == 1)
						order.push(new_point);
				}
			}
			count++;
		}
		if (cur_point.first != end_point.first && cur_point.second != end_point.second)
		{
			count = -1;
			//cout << count;
		}
			
	}

	void find_route(void)
	{
		move(start_point);
	}

	int promise1(pair<int, int> check)		//exclude knight traves over the chess matrix
	{
		if ((check.first >= 0 && check.first <= chess_size - 1) && (check.second >= 0 && check.second <= chess_size - 1))
			return 1;
		else
			return 0;
	}

	int promise2(pair<int, int> check)		
	{
		if (chess[check.first][check.second] == 0)
			return 1;
		else
			return 0;
	}

	void write(const char * fname)
	{
		FILE * fp = fopen(fname, "w");
		//cout << count;
		fprintf(fp,"%d",count);
		fclose(fp);
	}

};

int main(int argc, char **argv)
{
	Knight kor(argv[1]);
	kor.find_route();
	kor.write(argv[2]);
	return 0;

}

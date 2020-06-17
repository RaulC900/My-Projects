#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

class Game {

 public:

	void solve() {
		ReadFile();
		PrintOut(play_game());
	}

 private:

	int N;
	vector<int> v;

	void ReadFile() {

		ifstream fin("p1.in");
		fin >> N;

		for (int i = 1, e; i <= N; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	void merge(std::vector<int> &vector, std::vector<int> &L, std::vector<int> &R) {

	    std::vector<int>::iterator v = vector.begin();
	    std::vector<int>::iterator left = L.begin();
	    std::vector<int>::iterator right = R.begin();

		while(left != L.end() && right != R.end()) {

			if (*left >= *right) {

				*v = *left;
				left++;

			} else {

				*v = *right;
				right++;
			}

			v++;
		}

		while (left != L.end()) {

			*v = *left;
			v++;
			left++;
		}

		while (right != R.end()) {

			*v = *right;
			v++;
			right++;
		}
	}

	void mergeSort(std::vector<int> &vector) {

		if(vector.size() == 1) return;

		else {

			const unsigned int length = vector.size();

			const int low = floor((double)length/2);

			std::vector<int> Left(&vector[0], &vector[low]);
			std::vector<int> Right(&vector[low], &vector[length]);

			mergeSort(Left);
			mergeSort(Right);
			merge(vector, Left, Right);
		}
	}

	int play_game() {

		int diff = 0;
		int i;

		mergeSort(v);

		for(i = 0; i < N; i++) {


			if(i % 2 == 0) {
				diff += v[i];
			
			} else {
				diff -= v[i];
			}


		}
		return diff;

	}

	void PrintOut(int result) {
		ofstream fout("p1.out");
		fout << result;
		fout.close();
	}
};

int main()
{

	Game g;
	g.solve();
	return 0;

}
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

class Game {
 public:
	void solve() {
		ReadFile();
		PrintOut(play_game2());
	}

 private:
	int N;
	int K;
	vector<int> v;

	void ReadFile() {
		ifstream fin("p2.in");
		fin >> N;
		fin >> K;
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

	int play_game2() {

		int diff = 0;
		int i;
		int nr = 0;

		mergeSort(v);

		if(v[0] != v[1]) {
			for(i = 1; i < N - nr; i++) {
				if(v[i] == v[i+1]){
					i = i + 1;
				} else {
					v.erase(v.begin() + i);
					nr++;
					i--;
					if(nr == K)
						break;
				}
			}
		} else {
			for(i = 3; i < N - nr; i++) {
				if(v[i] == v[i+1]){
					i = i + 1;
				} else {
					v.erase(v.begin() + i);
					nr++;
					i--;
					if(nr == K)
						break;
				}
			}
		}
		N = N - K;

		for (i = 0; i < N; i++) {

			if(i % 2 == 0) {
				diff += v[i];
			} else {
				diff -= v[i];
			}

		}
		return diff;

	}

	void PrintOut(int result) {
		ofstream fout("p2.out");
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
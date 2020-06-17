#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

struct Scores {
	long long tuzgu;
	long long ritza;
};

class Game {

 public:

	void solve() {
		ReadFile();
		PrintOut(play_game3());
	}

 private:
 	
	int N;
	int K;
	vector<int> v;

	void ReadFile() {

		ifstream fin("p3.in");
		fin >> N;

		for (int i = 1, e; i <= N; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	long play_game3() {

		int i, j, k;
		long long scor_tuzgu = 0;
		long long scor_ritza = 0;

		Scores *dp[N];

		for(i = 0; i < N; i++) 
			dp[i] = (Scores*)malloc(N * sizeof(Scores)); 

		for(i = 0; i < N; i++){ //pe diagonala principala avem

            dp[i][i].tuzgu = v[i]; //subsecvente de 1 nr
            dp[i][i].ritza = 0; //scorul respectiv fiind (v[i],0)
        }
        
        for(i = 2; i <= N; i++){

            for(j = 0; j <= N - i; j++){

                k = j + i - 1; // indicele ultimului nr din subsecv

                // avem o subsecventa 0, i
                // calculam suma alegand un nr de la capete, 0 sau i
                // daca e 0, suma va fi v[0] + suma ritzei pe subsecv
                // 1, i
                if(v[k] + dp[j][k-1].ritza > dp[j+1][k].ritza + v[j]){
                	// formula este dp[j][k] = max(dp[j+1][k].ritza + v[j], 
                	// dp[j][k-1].ritza + v[k])
                    dp[j][k].tuzgu = v[k] + dp[j][k-1].ritza;
                    dp[j][k].ritza = dp[j][k-1].tuzgu;

                }else{

                    dp[j][k].tuzgu = v[j] + dp[j+1][k].ritza;
                    dp[j][k].ritza = dp[j+1][k].tuzgu;
                }
                // Formula: dp[j][k].ritza = dp[j+1][k].tuzgu || dp[j][k-1]
            }
		}

		scor_tuzgu = dp[0][N-1].tuzgu;
		scor_ritza = dp[0][N-1].ritza;

		for (i = 0; i < N; ++i)
			free(dp[i]);

		return scor_tuzgu - scor_ritza;
	}

	void PrintOut(int result) {
		ofstream fout("p3.out");
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

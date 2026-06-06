#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

int LOWER_BOUND = 100;
int UPPER_BOUND = 9000;

using namespace std;

int get_fraction_numbers(vector<int> &numbers, string file_name)
{
    ifstream file(file_name);
    if(!file.is_open()){
	cerr << "Не корректный файл на входе." << endl;
	return 0;
    }
    int temp;
    cin.rdbuf(file.rdbuf());
    for(int i = 0; i <= UPPER_BOUND; i++){
	cin >> temp;
	if(i >= LOWER_BOUND)
	    numbers.push_back(temp);
    }
    return 1;
}  
  
int observe_frequencies(vector<int> &numbers, map<int, int> &observed)
{
    for(int i = 0; i < numbers.size(); i++){
	if(observed.find(numbers[i]) == observed.end()){
	    observed.insert({numbers[i], 1});
	} else {
	    observed[numbers[i]] += 1;
	}
    }
    return 1;
}

void write_data(vector<float> distances, string file_name)
{
    ofstream file(file_name);
    for(int i = 0; i < distances.size(); i++){
	file << distances[i] << endl;
    }
    file.close();
}

float ks_distance(map<int, int> &observed, int window_size)
{
    float F_emp = 0, F_theor = 0;
    float max_diff = 0;
    int n = 1;
    while(true){
        float p_theor = log2(1.0 + 1.0 / (n * (n + 2.0)));
        float p_emp = observed.count(n) ? (float)observed[n] / window_size : 0;
        
        F_emp += p_emp;
        F_theor += p_theor;
        
        float diff = fabs(F_emp - F_theor);
        if(diff > max_diff) max_diff = diff;
        
        if(F_theor > 0.999) break;
        n++;
    }
    return max_diff;
}

float lambda(map<int, int> &observed, int window_size)
{
    float max_diff = 0;
    int max_n = observed.rbegin()->first;
    float p_theor = 0;
    float p_emp = 0;
    float diff;

    for (int n = 1; n < max_n; n++)
    {
        p_theor += log2(1.0 + 1.0 / (n * (n + 2.0)));
        p_emp += observed.count(n) ? (float)observed[n] / window_size : 0;
        diff = fabs(p_emp - p_theor);

        if(diff > max_diff) max_diff = diff;
    }

    return max_diff;
}

void calculate_distances(vector<int> &numbers, string file_name,
			 map<int, int> &observed, vector<float> &lambdas)
{
    for(int i = 1; i < UPPER_BOUND - LOWER_BOUND; i++){
	vector<int> sub(numbers.begin(), numbers.begin() + i);
	observed.clear();
	observe_frequencies(sub, observed);
	lambdas.push_back(lambda(observed, LOWER_BOUND + i));
    }
}

void fit_power(vector<float>& y, string name) {
    double S_X = 0, S_Y = 0, S_XX = 0, S_XY = 0;
    int N = 0;
    for (int i = 0; i < y.size(); i++) {
        if (y[i] <= 0) continue;
        double x = i + 1;
        double X = log(x);
        double Y = log(y[i]);
        S_X += X;
        S_Y += Y;
        S_XX += X * X;
        S_XY += X * Y;
        N++;
    }
    double B = (N * S_XY - S_X * S_Y) / (N * S_XX - S_X * S_X);
    double C = (S_Y - B * S_X) / N;
    double A = exp(C);
    cout << name << ": y = " << A << " * x^" << B << endl;
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        vector<int> nums;
        map<int, int> obs;
        //vector<float> lmb;
        string name = argv[i];
	cout << name << "..." << endl;
        name = name.substr(name.find_last_of('/') + 1);
        name = name.substr(0, name.find_last_of('.'));
        get_fraction_numbers(nums, argv[i]);
        //calculate_distances(nums, argv[i], obs, lmb);
	observe_frequencies(nums, obs);   
	float lmb = lambda(obs, nums.size());
        cout << name << ": lambda = " << lmb << endl;
	cout << "  -> готово" << endl;
    }
}

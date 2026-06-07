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
	if(i > LOWER_BOUND)
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

float lambda(map<int, int> &observed, int window_size)
{
    float max_diff = 0;
    int max_n = observed.rbegin()->first;
    float p_theor = 0;
    float p_emp = 0;
    float diff;

    for (int n = 1; n <= max_n; n++)
    {
        p_theor += log2(1.0 + 1.0 / (n * (n + 2.0)));
        p_emp += observed.count(n) ? (float)observed[n] / window_size : 0;
        diff = fabs(p_emp - p_theor);

        if(diff > max_diff) max_diff = diff;
    }

    return max_diff;
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        vector<int> nums;
        map<int, int> obs;
        string name = argv[i];
	    cout << name << "..." << endl;
        name = name.substr(name.find_last_of('/') + 1);
        name = name.substr(0, name.find_last_of('.'));
        get_fraction_numbers(nums, argv[i]);
	    observe_frequencies(nums, obs);   
	    float lmb = lambda(obs, nums.size());
        cout << "count: " << nums.size() << endl;
        cout << name << ": lambda = " << lmb << endl;
	    cout << "  -> готово" << endl;
    }
}

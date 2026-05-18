#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>

int LOWER_BOUND;
int UPPER_BOUND;

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

void calculate_gauss_kuzmin(map<int, float> &theoretical, map<int, int> &observed)
{
    for(const auto& [key, value] : observed){
	theoretical[key] = log2(1.0 + 1.0 / (key * (key + 2.0))) * (UPPER_BOUND - LOWER_BOUND);
    }
}

void write_data(map<int, float> &theoretical, map<int, int> &observed, string file_name)
{
    ofstream file(file_name);
    for(const auto& [key, value] : observed){
	file << key << " " << observed[key] << " " << theoretical[key] << endl;
    }
    file.close();
}

int main(int argc, char **argv)
{
    vector<int> fraction_numbers;
    map<int, float> theoretical_frequencies;
    map<int, int> observed_frequencies;
    LOWER_BOUND = stoi(argv[2]);
    UPPER_BOUND = stoi(argv[3]);
    get_fraction_numbers(fraction_numbers, argv[1]);
    observe_frequencies(fraction_numbers, observed_frequencies);
    calculate_gauss_kuzmin(theoretical_frequencies, observed_frequencies);
    write_data(theoretical_frequencies, observed_frequencies, "distribution.dat");
}  

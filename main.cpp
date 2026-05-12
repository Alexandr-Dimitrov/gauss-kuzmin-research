#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#define LOWER_BOUND 100
#define UPPER_BOUND 1000

using namespace std;

int get_fraction_numbers(vector<int> &numbers, string file_name)
{
    ifstream file(file_name);
    if(!file.is_open()){
	cerr << "Cannot open file" << endl;
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

void print_map(map<int, int>& m)
{
    for(const auto& [key, value] : m){
        cout << '[' << key << "] = " << value << "; " << endl;
    }
}

int main(int argc, char **argv)
{
    vector<int> fraction_numbers;
    map<int, int> observed_frequencies;
    get_fraction_numbers(fraction_numbers, argv[1]);
    observe_frequencies(fraction_numbers, observed_frequencies);
    print_map(observed_frequencies);
}  

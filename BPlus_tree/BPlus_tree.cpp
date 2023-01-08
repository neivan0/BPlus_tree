#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;
#include "BPTree.h"
int size(ifstream& file) {
	int k = 0;
	char c;
	while (file.get(c)) k++;
	return k;
}
bool compare(string path1, string path2) {
	ifstream fin1(path1, ios::binary);
	ifstream fin2(path2, ios::binary);
	char ch1, ch2;
	bool result = true;
	while (fin1.get(ch1) && fin2.get(ch2))
	{
		//cout << ch1 << " " << ch2<<endl;
		if (ch1 != ch2)
		{
			//cout << ch1 << " " << ch2 << endl;
			result = false;
			//break;
		}

	}
	//cout << size(fin1);
	if (result && (size(fin1) == size(fin2))) return true;
	else
		//cout << size(fin1) << " " << size(fin2);
		return false;
	//if (fin1.get()||fin2.get()) result = false;
	fin1.close();
	fin2.close();


}

int main() {
	//cout.precision(2);
	//cout << 0.1414114 << endl;
	string command;

	int test_numb = 0;
	int degree = 3;
	string path;
	double end_time;
	double start_time;
	double time = 0;
	//cout << "Enter degree of tree:" << endl;

	//system("cls");
	//cout << "Enter one of the commands in the following format:" << endl;
	//cout << "     - insert_{number}" << endl;
	//cout << "     - search_{number}" << endl;
	//cout << "     - delete_{number}" << endl;
	//cout << "     - print" << endl;
	//cout << "     - clear" << endl;


	//system("cls");

	while (1) {

		test_numb++;
		path = "tests/" + to_string(test_numb) + "/out.txt";
		ifstream in("tests/" + to_string(test_numb) + "/in.txt");
		ofstream out("tests/" + to_string(test_numb) + "/answ.txt");

		in >> degree;

		BPlusTree<int> bpt(degree);
		if (test_numb == 1) cout << "INSERTION" << endl;
		else if (test_numb == 3) cout << "DELETION" << endl;
		if (!in.is_open()) break;
		//start_time = (double)clock() / CLOCKS_PER_SEC;
		auto start = high_resolution_clock::now();
		//cout << (float)clock()/ CLOCKS_PER_SEC << endl;
		while (1) {
			string str; int k;
			in >> command;

			str = command.substr(0, command.find('_'));

			k = atoi((command.substr(command.find('_') + 1, command.size())).c_str());

			//cout << str;

			//break;

			if (str == "insert") {
				bpt.insert(k);
			}
			else if (str == "search") {
				cout << bpt.search(k) << endl;
			}
			else if (str == "delete") {
				bpt.remove(k);
			}
			else if (str == "print") {
				bpt.print_in_file(out, bpt.getroot());
				//bpt.bpt_print();
			}
			else if (str == "clear") {
				bpt.bpt_clear();
			}
			else if (str == "end") {
				break;
			}
			else cout << "Unknown command" << endl;

			//if ()
			//time += (end_time - start_time);
		}
		auto end = high_resolution_clock::now();
		auto time = duration_cast<microseconds>(end - start);

		in.close();
		out.close();

		if (compare("tests/" + to_string(test_numb) + "/answ.txt", "tests/" + to_string(test_numb) + "/out.txt")) cout << test_numb << "|OK|" << (double)time.count() / 1000 << 'ms' << endl;
		else cout << test_numb << "|WA" << endl;
	}
	//if (test_numb == 4) break;

}

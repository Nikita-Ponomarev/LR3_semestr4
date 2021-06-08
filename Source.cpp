#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Header.h"
using namespace std;
int main() {
	try
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "rus");
		fstream in_file;
		in_file.open("in.txt");
		int str_count = 0;
		string tmp_str;
		while (!in_file.eof()) {
			getline(in_file, tmp_str);
			str_count++;
		}
		in_file.close();
		in_file.open("in.txt");
		string** inp = new string * [str_count];
		for (int i = 0; i < str_count; i++) {
			inp[i] = new string[4];
			for (int j = 0; j < 3; j++) {
				getline(in_file, tmp_str, ';');
				if (tmp_str != "N/A")
					inp[i][j] = tmp_str;
				else
					inp[i][j] = "-1";
			}
			getline(in_file, tmp_str);
			if (tmp_str != "N/A")
				inp[i][3] = tmp_str;
			else
				inp[i][3] = "-1";
		}
		in_file.close();
		list<string> towns;
		for (int i = 0; i < str_count; i++) {
			if (!isDouble(towns, inp[i][0]))
				towns.push(inp[i][0]);
			if (!isDouble(towns, inp[i][1]))
				towns.push(inp[i][1]);
		}
		list<City>** town_name = new list<City>*[towns.getSize()];
		for (int i = 0; i < towns.getSize(); i++) {
			City* tmp = new City(towns[i], 0);
			list<City>* tmp2 = new list<City>;
			tmp2->push(*tmp);
			town_name[i] = tmp2;
		}
		for (int i = 0; i < str_count; i++) {
			int j = 0;
			if (inp[i][2] != "-1") {
				while (inp[i][0] != (*town_name[j])[0].town)
					j++;
				City* tmp = new City(inp[i][1], stoi(inp[i][2]));
				(*town_name[j]).push(*tmp);
			}
			j = 0;
			if (inp[i][3] != "-1") {
				while (inp[i][1] != (*town_name[j])[0].town)
					j++;
				City* tmp = new City(inp[i][0], stoi(inp[i][3]));
				(*town_name[j]).push(*tmp);
			}
		}
		for (int i = 0; i < towns.getSize(); i++) {
			(*town_name[i]).sort();
		}
		string from, to;
		cout << "Enter departure city: ";
		cin >> from;
		cout << "Enter arrival city: ";
		cin >> to;
		int max = 2147483647;
		ProcessCity* tmp_town = new ProcessCity[towns.getSize()];
		string* indexes = new string[towns.getSize()];
		for (int i = 0; i < towns.getSize(); i++) {
			indexes[i] = (*town_name[i])[0].town;
			tmp_town[i].town = (*town_name[i])[0].town;
			tmp_town[i].isVisited = false;
			tmp_town[i].distance = max;
			if ((*town_name[i])[0].town == from)
				tmp_town[i].distance = 0;
		}
		while (!allVisited(tmp_town, towns.getSize())) {
			int cur_ind = minDistance(tmp_town, towns.getSize());
			for (int i = 1; i < (*town_name[cur_ind]).getSize(); i++) {
				if (tmp_town[getIndex(indexes, (*town_name[cur_ind])[i].town)].isVisited == false &&
					tmp_town[cur_ind].distance + (*town_name[cur_ind])[i].Cost <
					tmp_town[getIndex(indexes, (*town_name[cur_ind])[i].town)].distance) {

					tmp_town[getIndex(indexes, (*town_name[cur_ind])[i].town)].distance =
						tmp_town[cur_ind].distance + (*town_name[cur_ind])[i].Cost;
				}
				else
					continue;
			}
			tmp_town[cur_ind].isVisited = true;
		}
		int* sizee = new int[towns.getSize()];
		int start = getIndex(indexes, from);
		int end = getIndex(indexes, to);
		sizee[0] = end;
		int k = 1;
		int cost = tmp_town[end].distance;
		while (end != start) {
			for (int i = 0; i < towns.getSize(); i++) {
				if (isConnected(indexes, town_name, i, end) != -1) {
					int temp = cost - isConnected(indexes, town_name, i, end);
					if (temp == tmp_town[i].distance) {
						cost = temp;
						end = i;
						sizee[k] = i;
						k++;
					}
				}
			}
		}
		for (int i = k - 1; i > 0; i--)
			cout << indexes[sizee[i]] << " -> ";
		cout << indexes[sizee[0]];
		end = getIndex(indexes, to);
		cout << endl;
		cout << "Minimum flight price: " << tmp_town[end].distance << '\n';
	}
	catch (exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}
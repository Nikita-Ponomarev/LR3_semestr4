#pragma once
#include <string>
#include <stdexcept>
using namespace std;
template<class T>
class list {
private:
	class nodeList;
	nodeList* Head;
	int Size;
public:
	list();
	~list();
	T pop();
	T pop(int);
	void push(T value);
	int getSize();
	void sort();
	string getString();
	const T operator[](const int index) const;
};
class City {
public:
	string town;
	int Cost;
	City(string nameP, int costP)
	{
		town = nameP;
		Cost = costP;
	}
};
class ProcessCity
{
public:
	string town;
	int distance;
	bool isVisited;
	ProcessCity()
	{

	}
	ProcessCity(string nameP)
	{
		town = nameP;
	}
};
bool isDouble(list<string>& arr, string str) {
	for (int i = 0; i < arr.getSize(); i++) {
		string a = arr[i];
		if (arr[i] == str)
			return true;
	}
	return false;
}
bool allVisited(ProcessCity* pCity, int count) {
	for (int i = 0; i < count; i++) {
		if (pCity[i].isVisited == false)
			return false;
	}
	return true;
}
int minDistance(ProcessCity* pCity, int count) {
	int index = -1;
	int min = 2147483647;
	for (int i = 0; i < count; i++) {
		if (pCity[i].distance < min && pCity[i].isVisited == false) {
			min = pCity[i].distance;
			index = i;
		}
	}
	return index;
}
int getIndex(string* arr, string str) {
	for (int i = 0; i < arr->size(); i++) {
		if (arr[i] == str)
			return i;
	}
	return -1;
}
int isConnected(string* indexes, list<City>** town_name, int begin, int end) {
	for (int i = 0; i < town_name[begin]->getSize(); i++)
		if (getIndex(indexes, (*town_name[begin])[i].town) == end)
			return (*town_name[begin])[i].Cost;
	return -1;
}
template <class T>
class list<T>::nodeList {
private:
	T Value;
	nodeList* Next;
public:
	nodeList() : Next(nullptr) {};
	nodeList(T value, nodeList* next) :
		Value(value), Next(next) {}
	T getValue() {
		return Value;
	}
	void setValue(T value) {
		Value = value;
	}
	nodeList* getNext() {
		return Next;
	}
	void setNext(nodeList* next) {
		Next = next;
	}
};
template <class T>
list<T>::list()
{
	Head = nullptr;
	Size = 0;
}
template<class T>
list<T>::~list()
{
	while (Size > 0)
		this->pop();
}
template <class T>
T list<T>::pop() 
{
	if (Size == 0)
		throw;
	if (Size == 1) {
		T tempNextVal = Head->getValue();
		delete Head;
		Head = nullptr;
		this->Size = 0;
		return tempNextVal;
	}
	nodeList* temp = Head;
	while (temp->getNext()->getNext() != nullptr) temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	delete temp->getNext();
	Size--;
	temp->setNext(nullptr);
	return tempNextVal;
}
template <class T>
T list<T>::pop(int index) {
	if (Size == 1 || Size == 0 || index == Size - 1) {
		return this->pop();
	}
	if (index == 0) {
		nodeList* temp = Head->getNext();
		T tempvalue = Head->getValue();
		Head = temp;
		Size--;
		return tempvalue;
	}
	nodeList* temp = Head;
	for (int i = 0; i < index - 1; i++)
		temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	nodeList* tempNext = temp->getNext()->getNext();
	Size--;
	temp->setNext(tempNext);
	return tempNextVal;
}
template <class T>
void list<T>::push(T value) {
	if (Size == 0) {
		Head = new nodeList(value, nullptr);
		Size++;
		return;
	}
	nodeList* temp = Head;
	while (temp->getNext() != nullptr) temp = temp->getNext();
	temp->setNext(new nodeList(value, nullptr));
	Size++;
	return;
}
template <class T>
int list<T>::getSize()
{
	return Size;
}
template <class T>
void list<T>::sort() {
	if (Size == 1 || Size == 0)
		return;
	nodeList* temp = Head;
	bool in_file = false;
	for (int i = 0; i < Size - 1; i++) {
		temp = Head;
		in_file = false;
		for (int j = 0; j < Size - 1 - i; j++) {
			if ((temp->getValue()).Cost > (temp->getNext()->getValue()).Cost) {
				T tempVal = temp->getValue();
				temp->setValue(temp->getNext()->getValue());
				temp->getNext()->setValue(tempVal);
				in_file = true;
			}
			temp = temp->getNext();
		}
		if (!in_file)
			return;
	}
}
template <class T>
const T list<T>::operator[](const int index) const {
	nodeList* it = Head;
	if (index < 0 || index > Size)
		throw;
	for (int i = 0; i < index; i++) {
		it = it->getNext();
	}
	return it->getValue();
}
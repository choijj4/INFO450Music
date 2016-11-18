// info450music.cpp : Defines the entry point for the console application.
//

// 450music.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
using namespace std;

//list node Class
class node
{
	char track[25];
	char artist[25];
	node *next;
public:
	node();
	node(char a[], char t[]);
	void setNode(char artist[], char track[]);
	friend class linkedList;
};

node::node()
{
	strcpy_s(track, " ");
	strcpy_s(artist, " ");
	next = NULL;
}

node::node(char a[], char t[])
{
	strcpy_s(track, t);
	strcpy_s(artist, a);
	next = NULL;
}

void node::setNode(char t[], char a[])
{
	strcpy_s(track, t);
	strcpy_s(artist, a);
	next = NULL;
}


//Linked List Class
class linkedList
{
	char filename[50];
	node *head;
	node *tail;
public:
	linkedList();
	void userLoop();
	void setFilename(char f[]);
	void readFile();
	void addNodeToEnd(node *nptr);
	int insertAfter(node *ptr, char i[]);
	void addNodeToHead(node *nptr);
	void skiptrack(int t);
	void playtrack();
	int removeNode(char i[]);
	void showList();

};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}
void linkedList::userLoop()
{
	node *ptr;
	ptr = head;
	int answer = 0;
	while (answer != 9)
	{
		cout << "artist: " << ptr->artist << ", " << " song: " << ptr->track << endl;
		cout << "what do you want to do?" << endl;
		cout << "[1] play" << endl;
		cout << "[2] skip" << endl;
		cout << "[3] delete" << endl;
		cout << "[4] quit" << endl;
		cin >> answer;
		cin.clear();
		cin.ignore();
		if (answer == 1)
		{
			cout << "playing: " << ptr->artist << ", " << ptr->track << endl;
			cin;
			cin.clear();
			cin.ignore();
		}
		else if (answer == 2)
		{
			int skip = 0;
			cout << "How many skips?" << endl;
			cin >> skip;
			skip -= 1;
			cin.clear();
			cin.ignore();

			for (int i = 0; i < skip; i++)
			{
				ptr = ptr->next;
			}
		}
		else if (answer == 3)
		{
			removeNode(ptr->artist);
		}
		else if (answer == 4)
		{
			cout << "goodbye" << endl;
			return;
		}
		else
		{
			cout << "error" << endl;
		}
		if (ptr->next == NULL)
		{
			ptr = head;
		}
		else
		{
			ptr = ptr->next;
		}
	}
}

void linkedList::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void linkedList::readFile()//NOT SURE IF THIS WORKS, ASK ABOUT FILENAMES
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		node *ptr;
		char artist[20];
		char track[20];

		infile.getline(artist, 20, ',');
		if (strlen(artist))
		{
			infile.getline(track, 20, ',');
			ptr = new node();
			ptr->setNode(artist, track);
			addNodeToEnd(ptr);
		}
	}
}

void linkedList::addNodeToEnd(node *ptr)
{
	// if list is empty
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void linkedList::addNodeToHead(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int linkedList::insertAfter(node *z, char i[])
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (strcmp(ptr->artist, i) == 0)// we found the node to insert after
		{
			z->next = ptr->next;
			ptr->next = z;
			if (tail == ptr) // repoint tail if we added to end
				tail = z;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}


int linkedList::removeNode(char i[])
{
	node *ptr = head;
	if (ptr == NULL) // empty list
	{
		return -1;
	}
	//if node is at the head
	if (head->artist == i)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
		{
			head = head->next;
		}
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (ptr->next)->artist == i)
		{
			if (tail == ptr->next)
			{
				tail = ptr;
			}
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}
//look at this
void linkedList::skiptrack(int t)
{
	node *ptr;
	ptr = head;
	for (int i = 0; i < t; i++)
	{
		ptr = ptr->next;
	}
}
void linkedList::playtrack()
{
	node *ptr;
	ptr = head;
	if (ptr == NULL)
	{
		cout << "track not available" << endl;
		return;
	}
	else
	{
		cout << "playing track" << ptr->artist << ", " << ptr->track << endl;
		cout << endl;
	}
}

void linkedList::showList()
{
	node *ptr;
	ptr = head;
	cout << "****  List Contents *****" << endl;
	if (ptr == NULL)
	{
		cout << "list is empty " << endl;
		return;
	}
	cout << "(head is " << head->artist << " tail is " << tail->artist << ")" << endl;
	while (ptr != NULL)
	{
		cout << "data is " << ptr->artist << ", " << ptr->track << endl;
		ptr = ptr->next;
	}
}
int main()
{
	char file[50];
	linkedList *mylist = new linkedList();
	cout << "please enter full path filename" << endl;
	cin >> file;
	cin.clear();
	cin.ignore();
	mylist->setFilename(file);
	mylist->readFile();
	//mylist->userLoop();
	// test if list is empty
	if (mylist->removeNode("Drake"))
		cout << "failed to remove" << endl;
	node *newnode = new node("Drake", "Controlla");
	mylist->addNodeToEnd(newnode);
	mylist->showList();
	mylist->addNodeToEnd(new node("Kendrick Lamar", "Levitate"));
	mylist->showList();
	mylist->addNodeToEnd(new node("Justin Bieber", "Where Are U Now"));
	mylist->showList();
	mylist->addNodeToHead(new node("Diplo", "Cold Water"));
	mylist->showList();
	mylist->insertAfter(new node("Adventure Club", "Gold"), "Drake");
	mylist->showList();

	mylist->userLoop();
	return 0;
}
#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <iostream>
 
using namespace std;

template <typename Keytype, typename Valtype>
void quick_sort(Keytype* key, Valtype* val, int start, int end) {
	if (start >= end)
		return;

	int i = start + 1;
	int j = end;

	while (i <= j) {
		while (i <= end && key[i] <= key[start])
			i++;
		while (j > start && key[j] >= key[start])
			j--;

		if (i > j) {
			Keytype temp1 = key[j];
			key[j] = key[start];
			key[start] = temp1;

			Valtype temp2 = val[j];
			val[j] = val[start];
			val[start] = temp2;
		}
		else {
			Keytype temp1 = key[i];
			key[i] = key[j];
			key[j] = temp1;

			Valtype temp2 = val[i];
			val[i] = val[j];
			val[j] = temp2;
		}
	}

	quick_sort(key, val, start, j - 1);
	quick_sort(key, val, j + 1, end);
}

long int random()
{
	return ((long int)rand() << 16) | ((long int)rand());
}

int main()
{
	typedef Entry<int, float> EntryType;

	SearchTree<EntryType> st;
	AVLTree<EntryType> avl;

	int nElem = 1000;

	int* key = new int[nElem] { 0 };
	float* val = new float[nElem] { 0 };
	bool* check = new bool[nElem + 1] { 0 };
	int ran;

	std::srand(std::time(0)); // use current time as seed for random generator


	// initialize
	for (int i = 0; i < nElem; i++)
	{	
		while (1) {
			ran = (std::rand() % nElem) + 1;
			if (!check[ran]) {
				key[i] = ran;
				check[ran] = true;
				break;
			}
		}
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	clock_t tm;
	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("BST Insert %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st.find(key[i]);
	}
	tm = clock() - tm;
	printf("BST Find %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("AVL Insert %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl.find(key[i]);
	}
	tm = clock() - tm;
	printf("AVL Find %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	std::cout << "---------------------------" << std::endl;

	SearchTree<EntryType> st2;
	AVLTree<EntryType> avl2;

	quick_sort(key, val, 0, nElem);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st2.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("BST Insert %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st2.find(key[i]);
	}
	tm = clock() - tm;
	printf("BST Find %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl2.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("AVL Insert %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl2.find(key[i]);
	}
	tm = clock() - tm;
	printf("AVL Find %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);
	
	std::cout << "---------------------------" << std::endl;

	SearchTree<EntryType> st3;
	AVLTree<EntryType> avl3;

	nElem = 10000;

	key = new int[nElem] { 0 };
	val = new float[nElem] { 0 };
	check = new bool[nElem + 1] { 0 };

	for (int i = 0; i < nElem; i++)
	{
		while (1) {
			ran = (std::rand() % nElem) + 1;
			if (!check[ran]) {
				key[i] = ran;
				check[ran] = true;
				break;
			}
		}
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st3.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("BST Insert %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st3.find(key[i]);
	}
	tm = clock() - tm;
	printf("BST Find %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl3.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("AVL Insert %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl3.find(key[i]);
	}
	tm = clock() - tm;
	printf("AVL Find %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	std::cout << "---------------------------" << std::endl;

	SearchTree<EntryType> st4;
	AVLTree<EntryType> avl4;

	quick_sort(key, val, 0, nElem);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st4.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("BST Insert %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st4.find(key[i]);
	}
	tm = clock() - tm;
	printf("BST Find %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl4.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("AVL Insert %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl4.find(key[i]);
	}
	tm = clock() - tm;
	printf("AVL Find %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);
	
	std::cout << "---------------------------" << std::endl;

	SearchTree<EntryType> st5;
	AVLTree<EntryType> avl5;

	nElem = 100000;

	key = new int[nElem] { 0 };
	val = new float[nElem] { 0 };
	check = new bool[nElem + 1] { 0 };

	for (int i = 0; i < nElem; i++)
	{
		while (1) {
			ran = (random() % nElem) + 1;
			if (!check[ran]) {
				key[i] = ran;
				check[ran] = true;
				break;
			}
		}
		val[i] = (float)std::rand() / RAND_MAX * 20000;
	}

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st5.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("BST Insert %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st5.find(key[i]);
	}
	tm = clock() - tm;
	printf("BST Find %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl5.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("AVL Insert %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl5.find(key[i]);
	}
	tm = clock() - tm;
	printf("AVL Find %d Random order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	std::cout << "---------------------------" << std::endl;

	SearchTree<EntryType> st6;
	AVLTree<EntryType> avl6;

	quick_sort(key, val, 0, nElem);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st6.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("BST Insert %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		st6.find(key[i]);
	}
	tm = clock() - tm;
	printf("BST Find %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl6.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf("AVL Insert %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	tm = clock();
	for (int i = 0; i < nElem; i++)
	{
		avl6.find(key[i]);
	}
	tm = clock() - tm;
	printf("AVL Find %d Skewed order elements: %f\n", nElem, ((float)tm) / (float)CLOCKS_PER_SEC);

	return 0;
}

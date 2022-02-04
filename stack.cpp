#include <cassert>
#include <iostream>
#include <math.h>

template<class type>
class Stack
{
public:
	// Default constructor 
	Stack(){
		capacity = 10;
		top = -1;
		array = new type[capacity];
	};

	// Destructor
	~Stack();

	// Return top element of stack
	type& Top();
	
	void Push(const type& item);
	
	void Pop();
	
	bool IsEmpty() const;

	void Print() {
		for(int i=0; i<=top; i++) std::cout << array[i] << std::endl;
	};
	
	int Size() { return top+1; }
	
private:
	// Data
	type *array;
	int capacity;
	int top;
};

template<class type>
Stack<type>::~Stack()
{
	delete[] array;
}

template<class type>
type& Stack<type>::Top()
{
	if (IsEmpty())
		throw("Error: Stack is empty");

	return array[top];
}

template<class type>
void Stack<type>::Push(const type& item)
{
	if (Size() == capacity) {
		capacity *= 2;
		type* temp = new type[capacity];
		for (int i = 0; i <= top; i++)
			temp[i] = array[i];
		delete[] array;
		array = temp;
	}

	array[++top] = item;
}

template<class type>
void Stack<type>::Pop()
{
	if (IsEmpty())
		throw("Error: Stack is empty");

	top--;
}

template<class type>
bool Stack<type>::IsEmpty() const
{
	if (top != -1)
		return false;

	return true;
}

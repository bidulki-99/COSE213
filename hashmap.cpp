#include <iostream>

// Map element
template <class KeyType, class ValType>
class MapElem
{
public:
	typedef KeyType ktype;
	typedef ValType vtype;
	
	KeyType key;
	ValType val;
	
	MapElem* link = NULL;
};

bool inline operator==(std::string a, std::string b)
{
	if((a).compare(b) == 0) return true;
	return false;
}

//
// Hash Map data structure
//
template <class HashMapElemType> 
class HashMap
{
public:
	typedef typename HashMapElemType::ktype KeyType;
	typedef typename HashMapElemType::vtype ValType;
	
	// constructor
	HashMap(unsigned int c = 1000);
	
	// destructor
	~HashMap();
	
	// Modify below functions
	int size() { return mapsize; };
	
	bool isEmpty() { return (mapsize == 0); };
	
	// ToDo
	HashMapElemType* find(const KeyType k);
	
	void insert(const KeyType k, const ValType v);
		
	bool remove(const KeyType k);
	
	unsigned int hashfunction(const KeyType k);
	
	void print();
	
private:
	// Hash Table
	HashMapElemType** ht;
	
	unsigned int mapsize, capacity, divisor;
};

//
// - Implementation -
//

// constructor
template <class HashMapElemType>
HashMap<HashMapElemType>::HashMap(unsigned int c) 
{
    mapsize = 0;
    capacity = c;
    int max = 1;

    int* erat = new int[c + 1]();
    erat[1] = 1;
    for (int i = 2; i * i <= c; i++) {
        if (!erat[i])
            for (int j = i + i; j <= c; j += i)
                erat[j] = 1;
    }

    for (int i = c; i >= 2; i--) {
        if (!erat[i]) {
            max = i;
            break;
        }
    }

    divisor = max;
    delete[] erat;

    ht = new HashMapElemType*[capacity];
    for (int i = 0; i < capacity; i++) {
        ht[i] = NULL;
    }
}

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
    for (int i = 0; i < divisor; i++) {
        HashMapElemType* p;

        while (ht[i]->link != NULL) {
            p = ht[i];
            ht[i] = ht[i]->link;
            delete p;
            p = NULL;
        }
    }

    delete[] ht;
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{
    int hval = hashfunction(k);
    HashMapElemType* p = ht[hval];
    while (p != NULL) {
        if (p->key == k)
            return p;
        p = p->link;
    }

    return NULL;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
    int hval = hashfunction(k);
    HashMapElemType* p = NULL;

    if (ht[hval] == NULL) {
        p = new HashMapElemType;
        p->key = k;
        p->val = v;
        p->link = NULL;
        ht[hval] = p;
        mapsize++;
        return;
    }

    if (ht[hval]->key == k) {
        ht[hval]->val = v;
        return;
    }

    else {
        p = ht[hval];
        while (p->link != NULL) {
            p = p->link;

            if (p->key == k) {
                p->val = v;
                return;
            }
        }

        p->link = new HashMapElemType;
        p = p->link;
        p->key = k;
        p->val = v;
        p->link = NULL;
    }

   mapsize++;
}

template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
    int hval = hashfunction(k);

    if (ht[hval] == NULL || find(k) == NULL)
        return false;

    else if (find(k) != NULL && ht[hval]->link == NULL) {
        delete ht[hval];
        ht[hval] = NULL;
        mapsize--;
        return true;
    }

    else if (find(k) != NULL) {
        HashMapElemType* p1 = ht[hval];

        if (p1->key == k) {
            HashMapElemType* del = p1;
            p1 = p1->link;
            delete del;
            del = NULL;
            ht[hval] = p1;
            mapsize--;
            return true;
        }
        
        HashMapElemType* p2 = p1->link;
        while (p2 != NULL) {
            if (p2->key == k) {
                p1->link = p2->link;
                delete p2;
                p2 = NULL;
                mapsize--;
                return true;
            }

            p1 = p2;
            p2 = p2->link;
        }
    }
}

template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
   int hval = 0;
   for (int i = 0; i < k.length(); i++) {
      if (k[i]) {
         hval += int(k[i]) << 8 * (i % 4);
      }
   }
   return hval % divisor;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()
{
   for (int i = 0; i < capacity; i++) {
      HashMapElemType* p = ht[i];
      if (p != NULL) {
         std::cout << "Key: " << p->key << " Value: " << p->val << std::endl;
         while (p->link != NULL) {
            p = p->link;
            std::cout << "Key: " << p->key << " Value: " << p->val << std::endl;
         }
      }
   }
}


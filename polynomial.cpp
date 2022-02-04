#include <typeinfo>
#include <iostream>
#include <math.h>


class Polynomial;

class Term {
	friend class Polynomial;

private:
	float coef;
	int exp;
};

class Polynomial
{
public:
	// Default constructor p(x) = 0
	Polynomial()
	{
		capacity = 10;
		terms = 0;
		termArray = new Term[capacity];
	};

	// Copy constructor
	Polynomial(const Polynomial& source);

	// Destructor
	~Polynomial();

	// Assignment operator
	Polynomial& operator = (const Polynomial& source);

	// Sum of *this and source polynomials
	Polynomial operator+(const Polynomial& source);

	// Subtract of source polynomials from *this
	Polynomial operator-(const Polynomial& source);

	// Product of *this and source polynomials
	Polynomial operator*(const Polynomial& source);

	// Compute derivative of the current polynomial
	Polynomial Derivative();

	// Return true if left polynomial is identical to right polynomial
	bool operator==(const Polynomial& right);

	// Evaluate polynomial *this at x and return the result
	float Eval(float x);

	// Create a new term. If the term exists, overwrite its coefficient.
	void CreateTerm(const float coef, const int exp);


	// Print polynomial
	void Print()
	{
		if (terms == 0) std::cout << "0" << std::endl;
		else
		{
			for (int i = 0; i < terms; i++)
			{
				float c = termArray[i].coef;
				int e = termArray[i].exp;

				if (c > 0 && i > 0)
				{
					std::cout << "+";
				}

				std::cout << c;
				if (e > 0) std::cout << "x^" << e;
			}
			std::cout << std::endl;
		}
	}

	int Capacity() const { return capacity; }
	int Terms() const { return terms; }
	Term& GetTerm(int x) const { return termArray[x]; }

private:
	Term* termArray;
	int capacity; // max # of terms in this polynomial
	int terms;	  // current # of terms in this polynomial
};

//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	capacity = terms = source.terms;
	termArray = new Term[capacity];
	for (int i = 0; i < terms; i++) {
		termArray[i].coef = source.termArray[i].coef;
		termArray[i].exp = source.termArray[i].exp;
	}
}

// Destructor
Polynomial::~Polynomial()
{
	delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	if (this == &source)
		return *this;
	
	delete[] termArray;
	termArray = new Term[source.terms];
	terms = source.terms;

	for (int i = 0; i < terms; i++) {
		this->termArray[i].exp = source.termArray[i].exp;
		this->termArray[i].coef = source.termArray[i].coef;
	}

	return *this;
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator + (const Polynomial& source)
{
	Polynomial c;
	float coef;
	int a = 0, b = 0;
	while ((a < terms) && (b < source.terms)) {
		if (termArray[a].exp == source.termArray[b].exp) {
			coef = termArray[a].coef + source.termArray[b].coef;
			if (coef) c.CreateTerm(coef, termArray[a].exp);
			a++; b++;
		}

		else if (termArray[a].exp < source.termArray[b].exp) {
			c.CreateTerm(source.termArray[b].coef, source.termArray[b].exp);
			b++;
		}

		else {
			c.CreateTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}
	}

	for (; a < terms; a++)
		c.CreateTerm(termArray[a].coef, termArray[a].exp);
	for (; b < source.terms; b++)
		c.CreateTerm(source.termArray[b].coef, source.termArray[b].exp);

	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;
	float coef;
	int a = 0, b = 0;

	while ((a < terms) && (b < source.terms)) {
		if (termArray[a].exp == source.termArray[b].exp) {
			coef = termArray[a].coef - source.termArray[b].coef;
			if (coef) c.CreateTerm(coef, termArray[a].exp);
			a++; b++;
		}

		else if (termArray[a].exp < source.termArray[b].exp) {
			c.CreateTerm(source.termArray[b].coef * (-1), source.termArray[b].exp);
			b++;
		}

		else {
			c.CreateTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}
	}

	for (; a < terms; a++) 
		c.CreateTerm(termArray[a].coef, termArray[a].exp);

	for (; b < source.terms; b++)
		c.CreateTerm(source.termArray[b].coef * (-1), source.termArray[b].exp);

	return c;
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;

	for (int a = 0; a < terms; a++) {
		for (int b = 0; b < source.terms; b++) {
			int temp = -1;
			float coef = termArray[a].coef * source.termArray[b].coef;
			int exp = termArray[a].exp + source.termArray[b].exp;

			for (int i = 0; i < c.terms; i++)
				if (c.termArray[i].exp == exp)
					temp = i;

			if (temp == -1)
				c.CreateTerm(coef, exp);
			else
				c.termArray[temp].coef += coef;
		}
	}
	
	Polynomial d;
	for (int i = 0; i < c.terms; i++) {
		if (c.termArray[i].coef)
			d.CreateTerm(c.termArray[i].coef, c.termArray[i].exp);
	}
	return d;
}

bool Polynomial::operator == (const Polynomial& right)
{
	bool ret = 1;

	if (terms != right.terms)
		return 0;

	for (int i = 0; i < terms; i++)
		if ((termArray[i].coef != right.termArray[i].coef) || (termArray[i].exp != right.termArray[i].exp))
			return 0;

	return ret;
}

float Polynomial::Eval(float x)
{
	float ret = 0;

	for (int i = 0; i < terms; i++) {
		ret += (float)pow(x, termArray[i].exp) * termArray[i].coef;
	}

	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;

	for (int i = 0; i < terms; i++)
		if (termArray[i].exp != 0)
			c.CreateTerm(termArray[i].coef * termArray[i].exp, termArray[i].exp - 1);

	return c;
}

void Polynomial::CreateTerm(const float coef, const int exp)
{
	if (terms == capacity) {
		capacity *= 2;
		Term* x = new Term[capacity];
		for (int i = 0; i < terms; i++)
			x[i] = termArray[i];
		delete[] termArray;
		termArray = x;
	}

	bool check = 1;
	for (int i = 0; i < terms; i++) {
		if (exp == termArray[i].exp) {
			check = 0;
			if (coef) {
				termArray[i].coef = coef;
				termArray[i].exp = exp;
			}

			else {
				while (i < terms) {
					termArray[i].coef = termArray[i + 1].coef;
					termArray[i].exp = termArray[i++ + 1].exp;
				}
				terms--;
				break;
			}
		}
	}
	
	if (check && coef) {
		termArray[terms].coef = coef;
		termArray[terms++].exp = exp;
	}

	for (int i = 0; i < terms; i++) {
		for (int j = i + 1; j < terms; j++) {
			if (termArray[i].exp < termArray[j].exp) {
				int temp1 = termArray[i].exp;
				termArray[i].exp = termArray[j].exp;
				termArray[j].exp = temp1;

				float temp2 = termArray[i].coef;
				termArray[i].coef = termArray[j].coef;
				termArray[j].coef = temp2;
			}
		}
	}
}

int main()
{
	Polynomial f, g;

	f.CreateTerm(-4, 3);
	f.CreateTerm(2.3, 2);
	f.CreateTerm(-3, 0);

	std::cout << "f = ";
	f.Print();

	g.CreateTerm(3, 4);
	g.CreateTerm(-8, 0);
	g.CreateTerm(-4, 3);

	std::cout << "g = ";
	g.Print();

	g.CreateTerm(5, 2);
	std::cout << "g (creating a new term) = ";
	g.Print();

	// copy constructor test
	std::cout << "h (created from f) = ";
	Polynomial h = f;
	h.Print();

	// assignment operator test
	std::cout << "h (assigned from g) = ";
	h = g;
	h.Print();

	// Add test
	std::cout << "f + g = ";
	h = f + g;
	h.Print();

	// Subtract test
	std::cout << "f - g = ";
	h = f - g;
	h.Print();

	Polynomial a;
	a.CreateTerm(2, 2);
	a.CreateTerm(1, 0);

	Polynomial b;
	b.CreateTerm(2, 2);
	b.CreateTerm(1, 1);
	b.CreateTerm(1, 0);

	std::cout << "a - b = ";
	h = a - b;
	h.Print();

	std::cout << "f * g = ";
	h = f * g;
	h.Print();
	std::cout << "h(0) is " << h.Eval(0) << std::endl;
	std::cout << "h(1) is " << h.Eval(1) << std::endl;

	Polynomial aa;
	std::cout << "0 * f = ";
	h = aa * f;
	h.Print();

	Polynomial ff;
	ff.CreateTerm(-2, 0);
	std::cout << "-2 * f = ";
	h = ff * f;
	h.Print();

	// Equal test
	if (f == g)
		std::cout << "f and g are same" << std::endl;
	else
		std::cout << "f and g are different" << std::endl;

	Polynomial i = h;
	if (h == i)
		std::cout << "h and i are same" << std::endl;
	else
		std::cout << "h and i are different" << std::endl;

	Polynomial k;
	k.CreateTerm(24, 0);
	k.CreateTerm(-12, 1);
	std::cout << "k = ";
	k.Print();
	k = f - k;
	std::cout << "f - k = ";
	k.Print();
	k = k - f;
	std::cout << "k - f = ";
	k.Print();
	k = k + f;
	std::cout << "k + f = ";
	k.Print();
	k = f + k;
	std::cout << "f + k = ";
	k.Print();
	if (f == k)
		std::cout << "f and k are same" << std::endl;
	else
		std::cout << "f and k are different" << std::endl;

	// Eval test
	std::cout << "f(3.5) is " << f.Eval(3.5) << std::endl;

	Polynomial j;
	j.CreateTerm(1, 0);

	// Derivative test
	i = f.Derivative();
	j = j.Derivative();
	std::cout << "Derivative of f = ";
	i.Print();
	std::cout << "Derivative of j = ";
	j.Print();

	Polynomial xx;
	xx.CreateTerm(6, 6);
	xx.CreateTerm(5, 5);
	xx.CreateTerm(4, 4);
	xx.CreateTerm(3, 3);
	xx.CreateTerm(2, 2);
	xx.CreateTerm(1, 1);
	xx.CreateTerm(10, 0);

	Polynomial yy;
	yy.CreateTerm(4, 4);
	yy.CreateTerm(3, 3);
	yy.CreateTerm(2, 2);
	yy.CreateTerm(1, 1);
	yy.CreateTerm(5, 0);

	std::cout << "xx = ";
	xx.Print();

	std::cout << "yy = ";
	yy.Print();

	std::cout << "xx (assigned from yy) = ";
	xx = yy;
	xx.Print();

	Polynomial y(xx);
	std::cout << "y (copied from xx) = ";
	y.Print();

	y.CreateTerm(-5, 5);
	std::cout << "current y = ";
	y.Print();

	Polynomial bb;
	bb.CreateTerm(1, 3);
	bb.CreateTerm(1, 1);

	Polynomial cc;
	cc.CreateTerm(1, 3);
	cc.CreateTerm(-1, 1);
	h = bb * cc;
	std::cout << "bb * cc = ";
	h.Print();

	bb = bb * cc;
	std::cout << "bb * cc = ";
	bb.Print();
	bb = bb * cc;
	std::cout << "bb * cc = ";
	bb.Print();

	bb.CreateTerm(-99, 3);
	std::cout << "current bb = ";
	bb.Print();
	
	Polynomial ee;
	ee.CreateTerm(1, 1);
	ee.CreateTerm(2, 2);

	Polynomial dd(ee);
	dd.CreateTerm(-1, 0);

	std::cout << "dd = ";
	dd.Print();
	std::cout << "ee = ";
	ee.Print();
	if (f == k)
		std::cout << "dd and ee are same" << std::endl;
	else
		std::cout << "dd and ee are different" << std::endl;

	Polynomial gg;
	gg.CreateTerm(0, 0);
	gg.CreateTerm(0, 1);
	std::cout << "gg = ";
	gg.Print();

	f.CreateTerm(0, 3);
	std::cout << "f = ";
	f.Print();

	Polynomial q;
	for (int i = 0; i < 100; i++)
		q.CreateTerm(i, i);

	q.CreateTerm(10000, 0);

	std::cout << "q = ";
	q.Print();

	Polynomial qq = q.Derivative();
	std::cout << "Derivative of q = ";
	qq.Print();

	std::cout << "q * q = ";
	q = q * q;
	q.Print();

	std::cout << "f - gg = ";
	q = f - gg;
	q.Print();
  
	return 0;
}

#include <iostream>
#include <cmath>
using namespace std;
class node
{
private:
	int data;
	node *next;
public:
	node()
	{
		data = 0;
		next = nullptr;
	}
	node(int d)
	{
		data = d;
		next = nullptr;
	}
	int getData() { return data; }
	void setData(int d) { data = d; }
	node * getNext() { return next; }
	void setNext(node * n) { next = n; }
	friend class linkedlist;
};
class linkedlist
{
private:
	node * head;
public:
	linkedlist()
	{
		head = nullptr;
	}
	linkedlist(int d)
	{
		head = new node(d);
	}
	void printall();
	void addfront(int item);
	void addend(int item);
	void add(int item, int pos);
	int count();
	double av();
	bool isempty();
	linkedlist rev(linkedlist l, int c);
	node * gethead() { return head; }
};
void linkedlist::printall()
{
	node *p = head;
	while (p != NULL)
	{
		cout << p->data << "\t";
		 p=p->next;
	}
}
void linkedlist::addfront(int item)
{
	node *temp = new node(item);
	
	if (head == nullptr)
	{
		head = temp;
	}
	else
	{
		temp->next = head;
		head = temp;
	}
}
void linkedlist::addend(int item)
{
	if (head == nullptr)
	{
		addfront(item);
	}
	else
	{
		node *p=head;
		while (p->next != nullptr)
		{
			p=p->next;
		}
		node *n = new node(item);
		p->next = n;

	}
}
void linkedlist::add(int item, int pos)
{
	if (pos == 1)
		addfront(item);
	else{
		node *temp1 = new node(item);
		node *temp = head;
		if (head == nullptr)
		{
			addfront(item);
		}
		else
		{
			for (int i = 0; i < pos - 2; i++)
			{
				temp = temp->next;
				if (temp == nullptr)
				{
					addend(item);
					return;
				}

			}
			temp1->next = temp->next;
			temp->next = temp1;
		}

	}
}
int linkedlist::count()
{
	int count = 0;
	node *p = head;
	if (p == nullptr)
		return 0;
	while (p->next != nullptr)
	{
		p = p->next;
		count++;
	}
	return count+1;

}
double linkedlist::av()
{
	double count = 0; double sum = 0;
	node *p = head;
	if (p == nullptr)
		return 0;
	sum = p->data;
	while (p->next != nullptr)
	{
		p = p->next;
		sum = sum + p->data;
		count++;
	}
	return sum/(count+1);

}
bool linkedlist::isempty()
{
	if (head == nullptr)
		return true;
	else
		return false;
}
linkedlist linkedlist:: rev(linkedlist l, int c)
{ 
	linkedlist rev;
	node *p = head;
	if (p == nullptr)
		return rev;
	for (int j = 0; j < c; j++)
	{
		node *p = head;
		for (int i = 0; i < c - j-1; i++)
		{

			p = p->next;

		}
		
		rev.add(p->data, j + 1);
		
	}
	return rev;
}
class poly
{
private:
	linkedlist coef;
public:
	poly()
	{
		linkedlist coef;
	}
	poly(double arr[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			coef.addend(arr[i]);
		}
	}
	double evaluate(double x);
	node * gethead() { return coef.gethead(); }
	void printpoly(){ coef.printall(); }
	int countpoly(){ return coef.count(); }
	poly differ();
};
poly poly::differ()
{
	node *p = coef.gethead(); int deg = coef.count() - 1; double *arr;
	arr = new double[deg + 1]; int i = 0; int mul;
	if (p == nullptr)
	{
		arr[0] = 0; deg = 1; poly result(arr, deg); return result;
	}
	while (p != nullptr)
	{
		mul = p->getData();
		arr[i] = mul * (deg - i);
		p = p->getNext(); i++;
	}
	poly result(arr, deg); return result;
}
double poly::evaluate(double x)
{
	double sum = 0; node *p = coef.gethead(); int deg = coef.count()-1; 
	if (p == nullptr)
	{
		return sum;
	}
	while (p != nullptr)
	{
		sum = sum + (p->getData()*(pow(x,deg)));
		deg--;
		p = p->getNext();
	}
	return sum;
}
poly multi(poly poly1, poly poly2,int size1,int size2)
{
	int deg = (size1 - 1) + (size2 - 1)+1;
	double *arr;
	arr = new double[deg + 1];
	node *p1 = poly1.gethead(); node *p2 = poly2.gethead();
	if (p1 == nullptr || p2 == nullptr)
	{
		arr[0] = 0; deg = 1; poly result(arr, deg); return result;
	}
	double mul;
	for (int j = 0; j< deg; j++)
	{
		arr[j] = 0;
	}
	int i = 0; int j = 0;
	while (p1 != nullptr)
	{
		mul = p1->getData();
		while (p2 != nullptr)
		{ 
			
			arr[i + j] = arr[i + j]+ (mul * p2->getData());
			p2 = p2->getNext();
			i++;
		}
		
			p2 = poly2.gethead();
			p1 = p1->getNext();
			
			i = 0; j++;
		
	}
	poly result(arr, deg); return result;
}
int main()
{
	double arr[3] = { 1, 1, 1 };
	poly poly1(arr,3); poly result = poly1.differ();
	result.printpoly(); 
	cout <<endl;
	return 0;

}
#include<iostream>
#include<string.h>
#include"Node.h"
using namespace std;
template <class ElemType>
class Linkstack
{
protected:
	Node<ElemType>* top;
	int count;
public:
	Linkstack();
	~Linkstack();
	int Length() const;
	bool Empty() const;
	void Clear();
	bool Push(const ElemType &e);
	bool Top( ElemType &e) const;
	bool Pop(ElemType &e);
	bool Pop();
    ElemType GetTop(ElemType &e) const;
};
template<class ElemType>
Linkstack<ElemType>::Linkstack() {
    top = NULL;
    count = 0;
}
template<class ElemType>
Linkstack<ElemType>::~Linkstack() {
    Clear();
}
template<class ElemType>
int Linkstack<ElemType>::Length() const {
    return count;
}
template<class ElemType>
bool Linkstack<ElemType>::Empty() const {
    return count == 0;
}
template<class ElemType>
void Linkstack<ElemType>::Clear() {
    for (; !Empty();) {
        Pop();
    }
}
template<class ElemType>
bool Linkstack<ElemType>::Push(const ElemType& e) {
    Node<ElemType>* newTop = new Node<ElemType>(e, top);
    if (newTop == NULL) {//¶¯Ì¬ÄÚ´æºÄ¾¡
        return false;
    }
    else {
        top = newTop;
        count++;
        return true;
    }
}
template<class ElemType>
bool Linkstack<ElemType>::Top(ElemType& e) const {
    if (Empty()) {//Õ»Îª¿Õ
        return false;
    }
    else {
        e = top->data;
        return true;
    }
}
template<class ElemType>
bool Linkstack<ElemType>::Pop(ElemType& e) {
    if (Empty()) {//Õ»Îª¿Õ
        return false;
    }
    else {
        Node<ElemType>* oldTop = top;
        e = oldTop->data;
        top = oldTop->next;
        delete oldTop;
        count--;
        return true;
    }
}
template<class ElemType>
bool Linkstack<ElemType>::Pop() {
    if (Empty()) {//Õ»Îª¿Õ
        return false;
    }
    else {
        Node<ElemType>* oldTop = top;
        top = oldTop->next;
        delete oldTop;
        count--;
        return true;
    }
}
template<class ElemType>
ElemType Linkstack<ElemType>::GetTop(ElemType& e) const {
    if (Empty()) {//Õ»Îª¿Õ
        return false;
    }
    else {
        e = top->data;
        return e;
    }
}
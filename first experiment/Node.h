template<class ElemType>
class Node {
public:
    ElemType data;
    Node<ElemType>* next;
    Node();
    Node(const ElemType& e, Node<ElemType>* link = NULL);
};
template<class ElemType>
Node<ElemType>::Node() {
    next = NULL;
}
template<class ElemType>
Node<ElemType>::Node(const ElemType& e, Node<ElemType>* link) {
    data = e;
    next = link;
}
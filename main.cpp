#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int FEMALE = 0;
const int MALE = 1;

class Person {
public:
    int age;
    int gender;
    string name;

    Person(int age, int gender, const string &name) : age(age), gender(gender), name(name) {}
};

class Student : public Person {
public:
    Student(int age, int gender, const string &name) : Person(age, gender, name) {}
};

class Teacher : public Person {
public:
    Teacher(int age, int gender, const string &name) : Person(age, gender, name) {}
};

/*节点类*/
class Node {
private:
    Node *prev;
    Node *next;
    int index;
    Person *data;
public:
    Node() : prev(nullptr), next(nullptr), index(-1), data(nullptr) {}

    Node(int index) : prev(nullptr), next(nullptr), index(index), data(nullptr) {}

    Node(int index, Person *data) : prev(nullptr), next(nullptr), index(index), data(data) {}

    Node(Person *data) : prev(nullptr), next(nullptr), index(-1), data(data) {}

    Person *getData() {
        return data;
    }

    void setData(Person *data) {
        this->data = data;
    }

    int getIndex() {
        return index;
    }

    void setIndex(int index) {
        this->index = index;
    }

    Node *getPrev() {
        return prev;
    }

    void setPrev(Node *pre) {
        this->prev = pre;
    }

    Node *getNext() {
        return next;
    }

    void setNext(Node *next) {
        this->next = next;
    }


};

/*链表类*/
class CList {
private:
    int count;
    Node *head;
    Node *tail;

public:
    CList() : head(new Node(0)), tail(new Node(1)), count(0) {
        cout << "CList structure" << endl;
        head->setNext(tail);
        tail->setPrev(head);
    }

    bool isEmpty() {
        return count == 0;
    }

    int getCount() {
        return count;
    }

    void setCount(int count) {
        this->count = count;
    }

    Node *getHead() {
        return head;
    }

    void setHead(Node *head) {
        this->head = head;
    }

    Node *getTail() {
        return tail;
    }

    void setTail(Node *tail) {
        this->tail = tail;
    }

    void removeHead();

    void removeTail();

    void addHead(Node *node);

    void addTail(Node *node);

    void removeAll();

    void showAll();

    Node *getAt(int index);

    void setAt(int index, Node *node);

    void removeAt(int indxe);
};

void CList::removeHead() {
    if (isEmpty()) {
        return;
    } else {
        //连接
        Node *tmp = head->getNext();
        head->setNext(tmp->getNext());
        tmp->getNext()->setPrev(head);
        //下标修正
        count--;
        Node *ptr = tmp;
        while (ptr->getNext() != nullptr) {
            ptr = ptr->getNext();
            ptr->setIndex(ptr->getIndex() - 1);
        }

        free(tmp);
    }
}

void CList::removeTail() {
    if (isEmpty()) {
        return;
    } else {
        //连接
        Node *tmp = tail->getPrev();
        tail->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(tail);
        //下标修正
        tail->setIndex(count--);

        free(tmp);
    }
}

void CList::addHead(Node *node) {
    //连接
    node->setPrev(head);
    node->setNext(head->getNext());
    head->getNext()->setPrev(node);
    head->setNext(node);
    //修改下标
    node->setIndex(1);
    count++;
    Node *ptr = node;
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() + 1);
    }
}

void CList::addTail(Node *node) {
    //连接
    node->setNext(tail);
    node->setPrev(tail->getPrev());
    tail->getPrev()->setNext(node);
    tail->setPrev(node);
    //修改下标
    node->setIndex(++count);
    tail->setIndex(count + 1);
}

void CList::removeAll() {
    Node *ptr = head->getNext(), *tmp;
    while (ptr->getNext() != nullptr) {
        tmp = ptr;
        ptr = ptr->getNext();
        free(tmp);
    }
    //重新初始化
    count = 0;
    head->setNext(tail);
    tail->setPrev(head);
    tail->setIndex(1);
}

void CList::showAll() {
    if (isEmpty()) {
        cout << "没有数据" << endl;
    } else {
        cout << right << setw(10) << "序号" << setw(10) << "姓名" << endl;
        Node *ptr = head->getNext();
        while (ptr->getNext() != nullptr) {
            cout << right << setw(10) << ptr->getIndex() << setw(10) << ptr->getData()->name << endl;
            ptr = ptr->getNext();
        }
    }
}

Node *CList::getAt(int index) {
    //下标范围检查
    if(index < 1 || index > count){
        cout << "查询失败" << endl;
        return nullptr;
    }

    Node *ptr = head->getNext();
    while (ptr->getNext() != nullptr) {
        if (ptr->getIndex() == index) {
            return ptr;
        }
        ptr = ptr->getNext();
    }
    cout << "查询失败" << endl;
    return nullptr;
}

void CList::setAt(int index, Node *node) {
    Node *ptr = getAt(index);
    ptr->getPrev()->setNext(node);
    node->setPrev(ptr->getPrev());
    ptr->getNext()->setPrev(node);
    node->setNext(ptr->getNext());
    free(ptr);
    node->setIndex(index);
}

class Stack : public CList {

};

class Queue : public CList {

};

int main() {
    CList list;
    Node *n1 = new Node(new Person(10, MALE, "GddG"));
    Node *n2 = new Node(new Person(10, MALE, "GG"));
    Node *n3 = new Node(new Person(10, MALE, "ssGG"));
    Node *n4 = new Node(new Person(10, MALE, "24GG"));
    Node *n5 = new Node(new Person(10, MALE, "554G"));
    list.showAll();
    list.addHead(n1);
    list.showAll();
    list.addHead(n2);
    list.showAll();
    list.addTail(n3);
    list.showAll();
    list.addTail(n4);
    list.showAll();

    list.setAt(2, n5);

    list.showAll();

    cout << list.getAt(2)->getIndex() << list.getAt(2)->getData()->name << endl;

    list.removeAll();
    list.showAll();

    list.getAt(2);

    list.removeHead();
    list.showAll();
    list.removeTail();
    list.showAll();
    list.removeTail();
    list.showAll();
    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>

/*
 *2、功能需求
用双向链表实现，需要满足如下要求。
1)	链表元素中要有指针指向动态分配的内存空间，练习析构函数的操作规则；
2)	链表应该至少有两个类，Node类和List类， Node类的构造和析构函数负责结点本身的初始化和空间回收，List类负责整个链表的管理工作，其构造和析构函数负责整个链表的初始化和回收；
3)	从List类派生出Stack和Queue，并使其具有自身的操作特性，练习派生类的概念；
4)	从List类派生出Set类，负责集合操作的实现；
5)	具有差“—”，并”+”union，交and三种操作，其中前两个是运算符的重载，第三个并非运算符的重载
6)	理解并、交、差操作并不影响参与操作的集合，实现并交差操作
 * 成员函数设计
1)	构造函数：
a)	CList：构建空链表 √
2)	获得头/尾指针
a)	GetHead：返回头元素指针 √
b)	GetTail：返回尾元素指针 √
3)	链表元素操作
a)	RemoveHead ：移除第一个元素 √
b)	RemoveTail ：移除最后一个元素 √
c)	AddHead ：在表头添加元素或者链表.  函数重载 todo
d)	AddTail ：在表尾添加元素或者链表.    函数重载 todo
e)	RemoveAll ： 移除所有元素 √
f)	Operator+（）	运算符重载函数 todo
4)	遍历操作
a)	GetNext 返回下一个元素的位置 √
b)	GetPrev 返回前一个元素位置 √
5)	检索/修改操作
a)	GetAt 返回指定下标的元素 √
b)	SetAt 设定指定下标值的元素值 √
c)	RemoveAt 移除指定下标值的元素 √
6)	插入操作
a)	InsertBefore：在指定位置前插入元素 todo
b)	InsertAfter：在指定位置后插入元素 todo
7)	查询操作
a)	Find：返回等于指定值的元素的位置 todo
b)	FindIndex：返回等于指定下标的元素的位置 todo
8)	状态测试
a)	GetCount：返回链表长度 √
b)	IsEmpty：判断链表是否为空 √
*/

using namespace std;

const int FEMALE = 0;
const int MALE = 1;

class Person {
public:
    int age;
    int gender;
    string name;

    Person(int age, int gender, const string &name) : age(age), gender(gender), name(name) {}

    bool operator==(const Person &person);
};

bool Person::operator==(const Person &person) {
    return (age == person.age && gender == person.gender && name == person.name);
}

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

    ~CList();

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

    void removeAt(int index);
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
    Node *copy = new Node(*node);
    //连接
    copy->setPrev(head);
    copy->setNext(head->getNext());
    head->getNext()->setPrev(copy);
    head->setNext(copy);
    //修改下标
    copy->setIndex(1);
    count++;
    Node *ptr = copy;
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() + 1);
    }
}

void CList::addTail(Node *node) {
    Node *copy = new Node(*node);
    //连接
    copy->setNext(tail);
    copy->setPrev(tail->getPrev());
    tail->getPrev()->setNext(copy);
    tail->setPrev(copy);
    //修改下标
    copy->setIndex(++count);
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
    if (index < 1 || index > count) {
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
    //获取对应节点
    Node *ptr = getAt(index);
    if (ptr == nullptr) return;

    ptr->getPrev()->setNext(node);
    node->setPrev(ptr->getPrev());
    ptr->getNext()->setPrev(node);
    node->setNext(ptr->getNext());
    free(ptr);
    node->setIndex(index);
}

void CList::removeAt(int index) {
    //获取对应节点
    Node *ptr = getAt(index);
    if (ptr == nullptr) return;

    Node *tmp = ptr;
    ptr->getPrev()->setNext(ptr->getNext());
    ptr->getNext()->setPrev(ptr->getPrev());
    //修正index
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() - 1);
    }
    //释放节点
    free(tmp);
    count--;
}

CList::~CList() {
    removeAll();
    free(head);
    free(tail);
}

/*栈类*/
class Stack : public CList {
public:
    void push(Node *node);

    Node *pop();

    Node *top();
};

void Stack::push(Node *node) {
    addTail(node);
}

Node *Stack::pop() {
    if (isEmpty()) {
        return nullptr;
    } else {
        //连接
        Node *tail = getTail();
        Node *tmp = tail->getPrev();
        tail->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(tail);
        //下标修正
        tail->setIndex(getCount());
        setCount(getCount() - 1);
        return tmp;
    }
}

Node *Stack::top() {
    return getTail();
}

/*队列类*/
class Queue : public CList {
public:
    void enQueue(Node *node);

    Node *deQueue();
};

void Queue::enQueue(Node *node) {
    addTail(node);
}

Node *Queue::deQueue() {
    if (isEmpty()) {
        return nullptr;
    } else {
        //连接
        Node *head = getHead();
        Node *tmp = head->getNext();
        head->setNext(tmp->getNext());
        tmp->getNext()->setPrev(head);
        //下标修正
//        count--;
        setCount(getCount() - 1);
        Node *ptr = tmp;
        while (ptr->getNext() != nullptr) {
            ptr = ptr->getNext();
            ptr->setIndex(ptr->getIndex() - 1);
        }

        return tmp;
    }
}

/*集合类*/
class Set : public CList {
public:
    Set &operator-(Set &set);//差

    Set &operator+(Set &set);//并

    Set &operator&&(Set &set);//and
};

Set &Set::operator-(Set &set) {
    Set *result = (new Set);

    return *result;
}

Set &Set::operator+(Set &set) {
    Set *result = (new Set);
    //添加当前对象所有节点
    Node *ptr1 = getHead()->getNext();
    while (ptr1->getNext() != nullptr) {
        Node *tmp = new Node(*ptr1);
        result->addTail(tmp);
        ptr1 = ptr1->getNext();
    }
    //添加set对象所有节点
    Node *ptr2 = set.getHead()->getNext();
    while (ptr2->getNext() != nullptr) {
        Node *tmp = new Node(*ptr2);
        result->addTail(tmp);
        ptr2 = ptr2->getNext();
    }
    //排重
    Node *ptr = result->getHead()->getNext();
    while (ptr->getNext() != nullptr) {
        Node *tar = ptr->getNext();
        while (tar->getNext() != nullptr) {
            if (ptr->getData() == tar->getData()) {
                int index = tar->getIndex();
                result->removeAt(index);
                tar = result->getAt(index);
                if (tar == nullptr) break;
                continue;
            }
            tar = tar->getNext();
        }
        ptr = ptr->getNext();
    }
    return *result;
}

Set &Set::operator&&(Set &set) {
    Set *result = (new Set);
    //添加当前对象所有节点
    Node *ptr1 = getHead()->getNext();
    while (ptr1->getNext() != nullptr) {
        Node *ptr2 = set.getHead()->getNext();
        while (ptr2->getNext() != nullptr) {
            Node *tmp = new Node(*ptr2);
            if (ptr1->getData() == ptr2->getData()) {
                Node *tmp = new Node(*ptr1);
                result->addTail(tmp);
            }
            ptr2 = ptr2->getNext();
        }
        ptr1 = ptr1->getNext();
    }
    return *result;
}

int main() {
    /*CList list;
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

    list.removeAt(2);
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
    list.showAll();*/
    Node *n1 = new Node(new Person(10, MALE, "GddG"));
    Node *n2 = new Node(new Person(10, MALE, "GG"));
    Node *n3 = new Node(new Person(10, MALE, "ssGG"));
    Node *n4 = new Node(new Person(10, MALE, "24GG"));
    Node *n5 = new Node(new Person(10, MALE, "554G"));

    Set set1, set2, set3;
    set1.addTail(n1);
    set1.addTail(n2);
    set1.showAll();
    set2.addTail(n1);
    set2.addTail(n3);
    set2.showAll();
    set3 = set1 + set2;
    set3.showAll();
    set3 = set1 and set2;
    set3.showAll();
    set1.showAll();
    set2.showAll();

//    cout << set1.getCount() << endl;
//    set1.removeAt(1);
//    set1.showAll();
//    cout << set1.getCount() << endl;
    return 0;
}
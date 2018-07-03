#include <iostream>
#include <string>
#include <iomanip>

/*
 *2����������
��˫������ʵ�֣���Ҫ��������Ҫ��
1)	����Ԫ����Ҫ��ָ��ָ��̬������ڴ�ռ䣬��ϰ���������Ĳ������򣻡�
2)	����Ӧ�������������࣬Node���List�࣬ Node��Ĺ�����������������㱾��ĳ�ʼ���Ϳռ���գ�List�ฺ����������Ĺ��������乹�����������������������ĳ�ʼ���ͻ��գ� ��
3)	��List��������Stack��Queue����ʹ���������Ĳ������ԣ���ϰ������ĸ�� ��
4)	��List��������Set�࣬���𼯺ϲ�����ʵ�֣� ��
5)	���в����������+��union����and���ֲ���������ǰ����������������أ���������������������� ��
6)	��Ⲣ���������������Ӱ���������ļ��ϣ�ʵ�ֲ�������� ��
 * ��Ա�������
1)	���캯����
a)	CList������������ ��
2)	���ͷ/βָ��
a)	GetHead������ͷԪ��ָ�� ��
b)	GetTail������βԪ��ָ�� ��
3)	����Ԫ�ز���
a)	RemoveHead ���Ƴ���һ��Ԫ�� ��
b)	RemoveTail ���Ƴ����һ��Ԫ�� ��
c)	AddHead ���ڱ�ͷ���Ԫ�ػ�������.  �������� ��
d)	AddTail ���ڱ�β���Ԫ�ػ�������.    �������� ��
e)	RemoveAll �� �Ƴ�����Ԫ�� ��
f)	Operator+����	��������غ��� ��
4)	��������
a)	GetNext ������һ��Ԫ�ص�λ�� ��
b)	GetPrev ����ǰһ��Ԫ��λ�� ��
5)	����/�޸Ĳ���
a)	GetAt ����ָ���±��Ԫ�� ��
b)	SetAt �趨ָ���±�ֵ��Ԫ��ֵ ��
c)	RemoveAt �Ƴ�ָ���±�ֵ��Ԫ�� ��
6)	�������
a)	InsertBefore����ָ��λ��ǰ����Ԫ�� ��
b)	InsertAfter����ָ��λ�ú����Ԫ�� ��
7)	��ѯ����
a)	Find�����ص���ָ��ֵ��Ԫ�ص�λ�� ��
b)	FindIndex�����ص���ָ���±��Ԫ�ص�λ�� ��
8)	״̬����
a)	GetCount������������ ��
b)	IsEmpty���ж������Ƿ�Ϊ�� ��
*/

using namespace std;

const int FEMALE = 0;
const int MALE = 1;

const int TEACHER = 0;
const int STUDENT = 1;

class Person {
public:
    int age;
    int gender;
    string name;

    Person(int age, int gender, const string &name) : age(age), gender(gender), name(name) {}

    bool operator==(const Person &person);

    virtual int whoIAm() {
        return 0;
    }
};

bool Person::operator==(const Person &person) {
    return (age == person.age && gender == person.gender && name == person.name);
}

class Student : public Person {
public:
    Student(int age, int gender, const string &name) : Person(age, gender, name) {}

    int whoIAm() override {
        return STUDENT;
    }
};

class Teacher : public Person {
public:
    Teacher(int age, int gender, const string &name) : Person(age, gender, name) {}

    int whoIAm() override {
        return TEACHER;
    }
};

/*�ڵ���*/
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

/*������*/
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

    void addHead(Person *person);

    void addTail(Node *node);

    void addTail(Person *person);

    void removeAll();

    void showAll();

    Node *getAt(int index);

    void setAt(int index, Node *node);

    void removeAt(int index);

    void addData();

    void insertBefore(Node *node, int index);

    void insertAfter(Node *node, int index);

    Node *find(string name);

    Node *findIndex(int index);
};

Node *CList::find(string name) {
    Node *ptr = head->getNext();
    while (ptr->getNext() != nullptr) {
        if (ptr->getData()->name == name) {
            return ptr;
        }
        ptr = ptr->getNext();
    }
    return nullptr;
}

Node *CList::findIndex(int index) {
    return getAt(index);
}


void CList::addData() {
    int sel, age, gender;
    string name;
    cout << "��������ѡ����� [��ʦ0/ѧ��1] ����:";
    cin >> sel;
    cout << "����������:";
    cin >> name;
    cout << "�������Ա� [Ů0/��1]:";
    cin >> gender;
    cout << "����������:";
    cin >> age;
    if (sel == TEACHER) {
        addTail(new Teacher(age, gender, name));
    } else if (sel == STUDENT) {
        addTail(new Student(age, gender, name));
    }
}

void CList::removeHead() {
    if (isEmpty()) {
        return;
    } else {
        //����
        Node *tmp = head->getNext();
        head->setNext(tmp->getNext());
        tmp->getNext()->setPrev(head);
        //�±�����
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
        //����
        Node *tmp = tail->getPrev();
        tail->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(tail);
        //�±�����
        tail->setIndex(count--);

        free(tmp);
    }
}

void CList::addHead(Node *node) {
    Node *copy = new Node(*node);
    //����
    copy->setPrev(head);
    copy->setNext(head->getNext());
    head->getNext()->setPrev(copy);
    head->setNext(copy);
    //�޸��±�
    copy->setIndex(1);
    count++;
    Node *ptr = copy;
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() + 1);
    }
}

void CList::addHead(Person *person) {
    addHead(new Node(person));
}

void CList::addTail(Node *node) {
    Node *copy = new Node(*node);
    //����
    copy->setNext(tail);
    copy->setPrev(tail->getPrev());
    tail->getPrev()->setNext(copy);
    tail->setPrev(copy);
    //�޸��±�
    copy->setIndex(++count);
    tail->setIndex(count + 1);
}

void CList::addTail(Person *person) {
    addTail(new Node(person));
}

void CList::insertBefore(Node *node, int index) {
    Node *copy = new Node(*node);
    Node *tar = getAt(index);
    //����
    copy->setPrev(tar->getPrev());
    copy->setNext(tar);
    tar->getPrev()->setNext(copy);
    tar->setPrev(copy);
    //�޸��±�
    copy->setIndex(index);
    count++;
    Node *ptr = copy;
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() + 1);
    }
}

void CList::insertAfter(Node *node, int index) {
    Node *copy = new Node(*node);
    Node *tar = getAt(index);
    //����
    copy->setPrev(tar);
    copy->setNext(tar->getNext());
    tar->getNext()->setPrev(copy);
    tar->setNext(copy);
    //�޸��±�
    copy->setIndex(index + 1);
    count++;
    Node *ptr = copy;
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() + 1);
    }
}

void CList::removeAll() {
    Node *ptr = head->getNext(), *tmp;
    while (ptr->getNext() != nullptr) {
        tmp = ptr;
        ptr = ptr->getNext();
        free(tmp);
    }
    //���³�ʼ��
    count = 0;
    head->setNext(tail);
    tail->setPrev(head);
    tail->setIndex(1);
}

void CList::showAll() {
    if (isEmpty()) {
        cout << "û������" << endl;
    } else {
        cout << right << setw(10) << "���" << setw(10) << "����" << setw(10) << "����" << setw(10) << "����" << setw(10)
             << "�Ա�" << endl;
        Node *ptr = head->getNext();
        while (ptr->getNext() != nullptr) {
            Person *data = ptr->getData();
            cout << right << setw(10) << ptr->getIndex() << setw(10) << (data->whoIAm() ? "ѧ��" : "��ʦ") << setw(10)
                 << data->name << setw(10) << data->age << setw(10) << (data->gender ? "��" : "Ů") << endl;
            ptr = ptr->getNext();
        }
    }
}

Node *CList::getAt(int index) {
    //�±귶Χ���
    if (index < 1 || index > count) {
        cout << "��ѯʧ��" << endl;
        return nullptr;
    }

    Node *ptr = head->getNext();
    while (ptr->getNext() != nullptr) {
        if (ptr->getIndex() == index) {
            return ptr;
        }
        ptr = ptr->getNext();
    }
    cout << "��ѯʧ��" << endl;
    return nullptr;
}

void CList::setAt(int index, Node *node) {
    //��ȡ��Ӧ�ڵ�
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
    //��ȡ��Ӧ�ڵ�
    Node *ptr = getAt(index);
    if (ptr == nullptr) return;

    Node *tmp = ptr;
    ptr->getPrev()->setNext(ptr->getNext());
    ptr->getNext()->setPrev(ptr->getPrev());
    //����index
    while (ptr->getNext() != nullptr) {
        ptr = ptr->getNext();
        ptr->setIndex(ptr->getIndex() - 1);
    }
    //�ͷŽڵ�
    free(tmp);
    count--;
}

CList::~CList() {
    removeAll();
    free(head);
    free(tail);
    cout << "CList destructure completed!" << endl;
}

/*ջ��*/
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
        //����
        Node *tail = getTail();
        Node *tmp = tail->getPrev();
        tail->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(tail);
        //�±�����
        tail->setIndex(getCount());
        setCount(getCount() - 1);
        return tmp;
    }
}

Node *Stack::top() {
    return getTail();
}

/*������*/
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
        //����
        Node *head = getHead();
        Node *tmp = head->getNext();
        head->setNext(tmp->getNext());
        tmp->getNext()->setPrev(head);
        //�±�����
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

/*������*/
class Set : public CList {
public:
    Set &operator-(Set &set);//��

    Set &operator+(Set &set);//��

    Set &operator&&(Set &set);//and

};

Set &Set::operator-(Set &set) {
    Set *result = (new Set);
    Node *ptr1 = getHead()->getNext(), *ptr2;
    while (ptr1->getNext() != nullptr) {
        bool flag = true;
        ptr2 = set.getHead()->getNext();
        while (ptr2->getNext() != nullptr) {
            Node *tmp = new Node(*ptr2);
            if (ptr1->getData() == ptr2->getData()) {
                flag = false;
            }
            ptr2 = ptr2->getNext();
        }
        if (flag) {
            Node *tmp = new Node(*ptr1);
            result->addTail(tmp);
        }
        ptr1 = ptr1->getNext();
    }
    return *result;
}

Set &Set::operator+(Set &set) {
    Set *result = (new Set);
    //��ӵ�ǰ�������нڵ�
    Node *ptr1 = getHead()->getNext();
    while (ptr1->getNext() != nullptr) {
        Node *tmp = new Node(*ptr1);
        result->addTail(tmp);
        ptr1 = ptr1->getNext();
    }
    //���set�������нڵ�
    Node *ptr2 = set.getHead()->getNext();
    while (ptr2->getNext() != nullptr) {
        Node *tmp = new Node(*ptr2);
        result->addTail(tmp);
        ptr2 = ptr2->getNext();
    }
    //����
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
    //�����ͬ���ݵĽڵ�
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

int show_function() {
    int selection;
    cout << "��ʦѧ����Ϣ��¼ϵͳ" << endl;
    cout << "1.������Ϣ��¼" << endl;
    cout << "2.��ʾ������Ϣ" << endl;
    cout << "3.ɾ��һ����¼" << endl;
    cout << "3.������������¼" << endl;
    cout << "0.������������" << endl;

    cin >> selection;
    return selection;
}

int main() {
/*    Node *n1 = new Node(new Person(10, MALE, "GddG"));
    Node *n2 = new Node(new Person(10, MALE, "GG"));
    Node *n3 = new Node(new Person(10, MALE, "ssGG"));
    Node *n4 = new Node(new Person(10, MALE, "24GG"));
    Node *n5 = new Node(new Person(10, MALE, "554G"));

    CList *list = new CList;
    list->addTail(n1);
    list->addTail(n2);
    list->addTail(n3);
    list->showAll();
    list->insertAfter(n4, 2);
    list->showAll();
    list->insertBefore(n5, 2);
    list->showAll();*/
/*    Set set1, set2, set3;
    set1.addTail(n1);
    set1.addTail(n2);
    set1.addTail(n4);
    set1.addTail(n5);
    set1.showAll();
    set2.addTail(n1);
    set2.addTail(n3);
    set2.showAll();
    cout << "������" << endl;
    set3 = set1 + set2;
    set3.showAll();
    cout << "������" << endl;
    set3 = set1 and set2;
    set3.showAll();
    cout << "�����" << endl;
    set3 = set1 - set2;
    set3.showAll();*/
    CList *list = new CList;
    int selection = show_function();
    string name;
    Node *tmp;
    Person *data;
    while (selection != 0) {
        switch (selection) {
            case 1:
                list->addData();
                break;
            case 2:
                list->showAll();
                break;
            case 3:
                cout << "����������:";
                cin >> name;
                tmp = list->find(name);
                if (tmp == nullptr) { break; }
                data = tmp->getData();
                cout << right << setw(10) << tmp->getIndex() << setw(10) << (data->whoIAm() ? "ѧ��" : "��ʦ") << setw(10)
                     << data->name << setw(10) << data->age << setw(10) << (data->gender ? "��" : "Ů") << endl;
                break;
            case 4:

                break;
            default:
                selection = show_function();
                break;
        }
        selection = show_function();
    }
    return 0;
}
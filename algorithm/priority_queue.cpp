#include <iostream>

#define MAX_SIZE 31

using namespace std;

typedef struct _pqNode { // prior queue node structure
	double key;  // key of elemnet
    string name; // name of element
} pqNode;

typedef struct _priorityQueue {
    pqNode *node;
    int totalSize; // size of total heap
    int usedSize; // size of elements(new index)
} priorityQueue;

class PQ {
    
    private :
        priorityQueue *pq;
        int minHeapify(int current);
        void swap(int index1, int index2);
        
    public : 
        PQ() { 
            pq = new priorityQueue;
            pq->totalSize = MAX_SIZE;
            pq->usedSize = 1;
            pq->node = new pqNode[pq->totalSize];
        }
        ~PQ() { 
            delete[] pq->node;
            delete pq;
        }
        void enQueue(double key, string name); // Insert an element
        void deQueue(); // Delete an element
        int getParent(int index);
        int getLeft(int index);
        int getRight(int index);
        void decrease(int index, double key);
        int isEmpty();
        void printQueue();

};

int PQ::minHeapify(int current) {
    int parent = getParent(current);

    while(current > 1 && pq->node[current].key < pq->node[parent].key) {    // 현재 인덱스가 1보다 크고, 현재 인덱스의 우선순위가 부모의 우선순위 보다 클 때 반복
        swap(current, parent);

        current = parent;   // current에 parent값을 저장
        parent = getParent(current);    // 변경된 current의 parent 값을 parent변수의 저장. 
    }
    return 0;
}

void PQ::swap(int index1, int index2) {
    pqNode temp;
    temp = pq->node[index1];
    pq->node[index1] = pq->node[index2];
    pq->node[index2] = temp;
}

void PQ::enQueue(double key, string name) {
    int current = pq->usedSize; // current에 현재 새로 입력될 index를 저장.

    if(pq->usedSize == pq->totalSize) {
        cout << "Queue is full!" << endl;
        return;
    }

    pq->node[current].key = key;
    pq->node[current].name = name;

    minHeapify(current);
    pq->usedSize++;     // Increase +1 usedSize(current element counts + next element)
    
    cout << "New element [" << pq->node[current].name << ", " << pq->node[current].key << "] is inserted." << endl;
}

void PQ::deQueue() {
    if(isEmpty()) {
        cout << "Queue is Empty!" << endl;
        return;
    }
    int parent = 1, left = 1, right = 1;    //  root element의 index가 1이므로 parent = 1로 설정.
    pqNode temp = pq->node[1];      // root element를 temp에 저장.

    pq->usedSize--;         // Decrease -1(next element)
    swap(1, pq->usedSize);  // root와 마지막 인덱스 swap
    
    left = getLeft(1);      //  root의 left child 불러오기
    right = getRight(1);    //  root의 right child 불러오기

    while(1) {                  // 정렬될 때까지 반복
        int selectedChild = 1;  // selectedChild초기화 선언
        
        if(left >= pq->usedSize) { break; }                     //  마지막 index가 left(2) 보다 작거나 같으면 break
        if(right >= pq->usedSize) { selectedChild = left; }     //  마지막 index가 right(3) 보다 작거나 같으면 selectedChild = left
        else {
            if(pq->node[left].key > pq->node[right].key)    //  right가 left보다 작으면 selectedChild = right
                selectedChild = right;
            else
                selectedChild = left;
        }

        if(pq->node[selectedChild].key < pq->node[parent].key) {    // selectedChild의 key가 parent보다 작으면 스왑
            swap(parent, selectedChild);
            parent = selectedChild;
        }
        else { break; }

        left = getLeft(parent);
        right = getRight(parent);
    }
    cout << "[" << temp.name << ", " << temp.key << "] is deleted." << endl;
}

int PQ::getParent(int index) { return (int)(index / 2 ); }

int PQ::getLeft(int index) { return index * 2; }

int PQ::getRight(int index) { return (index * 2) + 1; }

void PQ::decrease(int index, double key) {
    if(key > pq->node[index].key) {
        cout << "New key is bigger than current key" << endl;
        return;
    }

    int parent = getParent(index);
    pqNode temp = pq->node[index];

    pq->node[index].key = key;  //  key 값 변경

    minHeapify(index);

    cout << "[" << temp.name << ", " << temp.key << "] is changed to [" << pq->node[index].name << ", " << pq->node[index].key << "]." << endl;
}

int PQ::isEmpty() {
    return (pq->usedSize == 1);
}
void PQ::printQueue() {
    for(int i = 1; i < pq->usedSize; i++) {
        cout << "[" << pq->node[i].name << ", " << pq->node[i].key << "] ";
    }
    cout << "\n";
}

int main() {
    PQ *pQueue = new PQ();
    double score;
    char cmd;
    string name;

    while(1) {

        cout << "*********** MENU ***********" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue." << endl;
        cout << "C : Decrease key of element in queue." << endl;
        cout << "P : Print out all element in queue." << endl;
        cout << "Q : Quit.\n" << endl;
        cout << "Choose menu: ";

        cin >> cmd;
        
        if(cmd == 'I' || cmd == 'i'){
            
            cout << "Enter name of element: ";
            cin >> name;
            cout << "Enter key value of element: ";
            cin >> score;

            pQueue->enQueue(score, name);
            
        } else if(cmd == 'D' || cmd == 'd') {

            pQueue->deQueue();

        } else if(cmd == 'C' || cmd == 'c') {

            if(pQueue->isEmpty()) {
                cout << "Queue is empty!\n\n" << endl;
                continue;
            }

            int index;

            pQueue->printQueue();   // Index를 고르기 전 확인 할 수 있게 Print
            cout << "========================================================" << endl;
            cout << "Enter index of element: ";
            cin >> index;
            cout << "Enter new key value: ";
            cin >> score;

            pQueue->decrease(index, score);

        } else if(cmd == 'P' || cmd == 'p') {

            if(pQueue->isEmpty()) {
                cout << "Queue is empty!\n\n" << endl;
                continue;
            }

            pQueue->printQueue();

        }
        else if(cmd == 'Q')
            break;
        else {
            cout << "Incorrect inputs!\n\n";
            continue;
        }
        
        cout <<"\n\n";

    }
    delete pQueue; //destuctor 호출

  return 0;
} 

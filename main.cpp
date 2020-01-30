#include "Sorting.h"
#include "Searching.h"

#include "ListSingly.h"
#include "ListDoubly.h"
#include "StackArray.h"
#include "StackList.h"
#include "QueueArray.h"
#include "QueueList.h"
#include "Heap.h"
#include "BSTree.h"

#include "PtrUnique.h"
#include "PtrShared.h"

int main()
{
    int choice{0};
    std::cin >> choice;

    switch (choice)
    {
    case 0:  TestSorting();    break;
    case 1:  TestSearching();  break;
    case 2:  TestListSingly(); break;
    case 3:  TestListDoubly(); break;
    case 4:  TestStackArray(); break;
    case 5:  TestStackList();  break;
    case 6:  TestQueueAray();  break;
    case 7:  TestQueueList();  break;
    case 8:  TestHeap();       break;
    case 9:  TestBSTree();     break;
    case 10: TestPtrUnique();  break;
    case 11: TestPtrShared();  break;
    }

    return 0;
}

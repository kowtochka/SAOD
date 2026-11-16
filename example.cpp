#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

struct record1
{
    char name[30];
    short int num;
    char job[22];
    char birthday[10];
};
struct list
{
    list *next;
    record1 data;
} *p;
struct queue
{
    list *head;
    list *tail;
};
struct tree
{
    record1 data;
    tree *left = nullptr;
    tree *right = nullptr;
    int bal = 0;
    int weight = 0;
    list *copy = nullptr;
};
struct node
{
    record1 data;
    int weight;
};

record1 mas[4000] = {0};
record1 *arr[4000];

int less(const record1 &file1, const record1 &file2)
{
    if (file1.num < file2.num)
        return 1;
    else if (file1.num > file2.num)
        return 0;
    else
    {
        int cmp = strcmp(file1.name, file2.name);
        if (cmp < 0)
            return 1;
        if (cmp > 0)
            return 0;
    }
    return 0;
}

void QuickSort2(int L, int R)
{
    while (L < R)
    {
        record1 x = *arr[L];
        int i = L;
        int j = R;

        while (i <= j)
        {
            for (; less(*arr[i], x); i++)
                ;
            for (; less(x, *arr[j]); j--)
                ;

            if (i <= j)
            {
                record1 *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        if (j - L < R - i)
        {
            if (L < j)
                QuickSort2(L, j);
            L = i;
        }
        else
        {
            if (i < R)
                QuickSort2(i, R);
            R = j;
        }
    }
}

void binarySearch(record1 **arr, int n, int x, queue &q)
{
    while (q.head != NULL)
    {
        list *temp = q.head;
        q.head = q.head->next;
        delete temp;
    }
    q.tail = NULL;

    int L = 0;
    int R = n - 1;
    int firstIdx = -1;

    while (L <= R)
    {
        int m = (L + R) / 2;
        if (arr[m]->num == x)
        {
            firstIdx = m;
            R = m - 1;
        }
        else if (arr[m]->num < x)
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    }

    if (firstIdx != -1)
    {
        int i = firstIdx;
        while (i < n && arr[i]->num == x)
        {
            list *node = new list;
            node->data = *arr[i];
            node->next = NULL;

            if (q.tail == NULL)
            {
                q.head = node;
                q.tail = node;
            }
            else
            {
                q.tail->next = node;
                q.tail = node;
            }
            i++;
        }
    }
}

void printArray(record1 **records, int n)
{
    if (n <= 0)
        return;
    int totalPages = (n + 19) / 20;
    int page = 0;
    char command;
    do
    {
        printf("\nPage %d / %d\n", page + 1, totalPages);
        int start = page * 20;
        int end = (start + 20 < n) ? (start + 20) : n;
        for (int i = start; i < end; i++)
        {
            printf("%4d) %25s %5d %20s %s\n", i + 1, records[i]->name, records[i]->num, records[i]->job, records[i]->birthday);
        }
        printf("\n[N] Next | [P] Prev | [Q] Quit to menu: ");
        scanf(" %c", &command);
        if ((command == 'n' || command == 'N') && page < totalPages - 1)
            page++;
        else if ((command == 'p' || command == 'P') && page > 0)
            page--;

    } while (command != 'q' && command != 'Q');
    printf("\n");
}

void bubble_sort(node *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (A[j].weight < A[j - 1].weight)
            {
                node temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
            }
        }
    }
}

int TreeAdd(node data, tree **root)
{
    tree **p = root;
    while (*p != nullptr)
    {
        int cmp = strcmp(data.data.job, (*p)->data.job);
        if (cmp < 0)
            p = &((*p)->left);
        else if (cmp > 0)
            p = &((*p)->right);
        else
        {
            list *newNode = new list;
            newNode->data = data.data;
            newNode->next = nullptr;

            if ((*p)->copy == nullptr)
            {
                (*p)->copy = newNode;
            }
            else
            {
                list *curr = (*p)->copy;
                while (curr->next != nullptr)
                {
                    curr = curr->next;
                }
                curr->next = newNode;
            }
            return 0;
        }
    }

    *p = new tree();
    (*p)->data = data.data;
    (*p)->weight = data.weight;
    (*p)->right = nullptr;
    (*p)->left = nullptr;
    (*p)->copy = nullptr;
    return 1;
}

void A1(tree **p, node *data, int n)
{
    bubble_sort(data, n);
    for (int i = n - 1; i >= 0; i--)
    {
        TreeAdd(data[i], p);
    }
}

void LRr(tree *rt, int &i)
{
    if (rt == NULL)
    {
        return;
    }
    LRr(rt->left, i);
    i++;
    printf("%d) %s %d %s %s\n", i, rt->data.name, rt->data.num, rt->data.job, rt->data.birthday);
    for (list *curr = rt->copy; curr != nullptr; curr = curr->next)
    {
        i++;
        printf("%d) %s %d %s %s\n", i, curr->data.name, curr->data.num, curr->data.job, curr->data.birthday);
    }
    LRr(rt->right, i);
}
void search(tree *rt, const char *data, int &foundCount)
{
    if (rt == nullptr)
        return;

    int cmp = strcmp(data, rt->data.job);

    if (cmp == 0)
    {
        printf("%25s %5d %20s %s\n", rt->data.name, rt->data.num, rt->data.job, rt->data.birthday);
        foundCount++;

        for (list *curr = rt->copy; curr != nullptr; curr = curr->next)
        {
            printf("%25s %5d %20s %s\n", curr->data.name, curr->data.num, curr->data.job, curr->data.birthday);
            foundCount++;
        }
    }
    else if (cmp < 0)
    {
        search(rt->left, data, foundCount);
    }
    else
    {
        search(rt->right, data, foundCount);
    }
}
void trimRight(char *str)
{
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }
}

int main()
{
    for (int i = 0; i < 4000; i++)
    {
        arr[i] = &mas[i];
    }
    record1 *origArr[4000];
    for (int i = 0; i < 4000; i++)
    {
        arr[i] = &mas[i];
        origArr[i] = &mas[i];
    }
    FILE *fp = fopen("testBase2.dat", "rb");
    if (!fp)
    {
        printf("cannot open file\n");
        return 1;
    }

    int n = (int)fread(mas, sizeof(record1), 4000, fp);
    fclose(fp);

    QuickSort2(0, n - 1);
    queue searchQueue = {NULL, NULL};
    while (1)
    {
        printf("1.Print original array\n");
        printf("2.Print sorted array\n");
        printf("3.Binary search\n");
        printf("4.Exit\n");
        int k;
        scanf(" %d", &k);
        switch (k)
        {
        case 1:
        {
            printArray(origArr, n);
            break;
        }
        case 2:
        {
            printArray(arr, n);
            break;
        }
        case 3:
        {
            int x;
            printf("Enter num to search: ");
            scanf("%d", &x);
            binarySearch(arr, n, x, searchQueue);
            if (searchQueue.head == NULL)
            {
                printf("\nNothing found.\n\n");
                break;
            }
            int count = 0;
            for (list *curr = searchQueue.head; curr != NULL; curr = curr->next)
                count++;
            list **found = new list *[count];
            list *curr = searchQueue.head;
            for (int i = 0; i < count; i++)
            {
                found[i] = curr;
                curr = curr->next;
            }
            int totalPages = (count + 20 - 1) / 20;
            int page = 0;
            char command;
            do
            {
                printf("\nPage %d / %d\n", page + 1, totalPages);
                int start = page * 20;
                int end;
                if (start + 20 < count)
                {
                    end = start + 20;
                }
                else
                {
                    end = count;
                }
                for (int i = start; i < end; i++)
                {
                    record1 rec = found[i]->data;
                    printf("%d) %s %d %s %s\n", i + 1, rec.name, rec.num, rec.job, rec.birthday);
                }
                printf("\n[n] Next | [p] Prev | [t] Tree |[q] Quit: ");
                scanf(" %c", &command);
                switch (command)
                {
                case 'n':
                    if (page < totalPages - 1)
                        page++;
                    break;
                case 'p':
                    if (page > 0)
                        page--;
                    break;
                }
            } while (command != 'q' && command != 't');

            if (command == 't')
            {
                node *f = new node[count];
                int j = 0;
                for (list *i = searchQueue.head; i != nullptr; i = i->next)
                {
                    f[j].weight = rand() % 100;
                    f[j].data = i->data;
                    trimRight(f[j].data.job);
                    trimRight(f[j].data.name);
                    j++;
                }

                tree *l = nullptr;
                A1(&l, f, count);

                printf("\n\nEnter the profession to search: ");

                while (getchar() != '\n')
                    ;

                char find[100] = {0};
                fgets(find, sizeof(find), stdin);

                find[strcspn(find, "\n")] = 0;
                trimRight(find);

                printf("\n--- Search Results in Tree ---\n");
                int foundCount = 0;
                search(l, find, foundCount);

                if (foundCount == 0)
                {
                    printf("Nothing found for profession: '%s'\n", find);
                }
                else
                {
                    printf("\nTotal found: %d people\n", foundCount);
                }
                printf("------------------------------\n");

                delete[] f;
            }
            break;
        }
        case 4:
        {
            return 0;
        }
        default:
        {
            printf("choose another option\n");
            break;
        }
        }
    }
    return 0;
}
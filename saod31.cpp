#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
struct tree
{
    int data;
    tree *left;
    tree *right;
    int bal = 0;
    int weight = 0;
};
struct node
{
    int data;
    int weight;
};
void Rlr(tree *rt);
void LRr(tree *rt);
void LrR(tree *rt);
int size(tree *rt);
int sum(tree *rt);
int Height(tree *rt);
int SumLenWay(tree *rt, int l);
void Rlr(tree *rt)
{
    if (rt == NULL)
    {
        return;
    }

    printf("%d \n", rt->data);
    Rlr(rt->left);
    Rlr(rt->right);
}
void shuffle_array(node *arr, int n)
{
    srand(time(0));
    for (int i = n - 1; i > 0; --i)
    {
        int j = rand() % n;
        std::swap(arr[i], arr[j]);
    }
}

void fill_rand(node *A, int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        A[i].data = i;
        A[i].weight = rand() % 51;
    }
    // shuffle_array(A, n);
}
void LRr(tree *rt)
{
    if (rt == NULL)
    {

        return;
    }
    LRr(rt->left);
    printf("%d ", rt->data);
    LRr(rt->right);
}
void LrR(tree *rt)
{
    if (rt == NULL)
        return;
    LrR(rt->left);
    LrR(rt->right);
    printf("%d \n", rt->data);
}
int size(tree *rt)
{
    int n = 0;
    if (rt == nullptr)
        n = 0;
    else
    {
        n = 1 + size(rt->left) + size(rt->right);
    }
    return n;
}
int sum(tree *rt)
{
    int n = 0;
    if (rt == nullptr)
        n = 0;
    else
    {
        n = rt->data + sum(rt->left) + sum(rt->right);
    }
    return n;
}
int Height(tree *rt)
{
    int n = 0;
    if (rt == nullptr)
        n = 0;
    else
    {
        n = 1 + std::max((Height(rt->left)), Height(rt->right));
    }
    return n;
}
int SumLenWay(tree *rt, int l)
{
    int n = 0;
    if (rt == nullptr)
        n = 0;
    else
    {
        n = l + SumLenWay(rt->left, l + 1) + SumLenWay(rt->right, l + 1);
    }
    return n;
}
int getTotalWeight(tree *p)
{
    if (p == NULL)
        return 0;
    return p->weight + getTotalWeight(p->left) + getTotalWeight(p->right);
}

double getWeightedSum(tree *p, int level)
{
    if (p == NULL)
        return 0.0;
    double current = (double)p->weight * level;
    return current + getWeightedSum(p->left, level + 1) + getWeightedSum(p->right, level + 1);
}

double getAvgWeightedHeight(tree *p)
{
    if (p == NULL)
        return 0.0;
    double totalW = getTotalWeight(p);
    if (totalW == 0)
        return 0.0;
    double weightedSum = getWeightedSum(p, 1);
    return weightedSum / totalW;
}
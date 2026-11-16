#include "saod31.cpp"

int TreeAdd(node data, tree **root)
{
    tree **p = root;
    while (*p != nullptr)
    {
        if (data.data < (*p)->data)
            p = &((*p)->left);
        else if (data.data > (*p)->data)
            p = &((*p)->right);
        else
            return 0;
    }
    if (*p == nullptr)
    {
        *p = new tree();
        (*p)->data = data.data;
        (*p)->weight = data.weight;
        (*p)->right = nullptr;
        (*p)->left = nullptr;
    }
    return 1;
}

void AW(int n, int **mat, node *arr)
{
    for (int i = 0; i < n + 1; i++)
    {
        mat[i][i] = 0;
        for (int j = i + 1; j < n + 1; j++)
        {
            mat[i][j] = mat[i][j - 1] + arr[j - 1].weight;
        }
    }
}

void APAR(int **aw, int **ap, int **ar, int n)
{
    int min, m, x, j;
    for (int i = 0; i < n; i++)
    {
        j = i + 1;
        ap[i][j] = aw[i][j];
        ar[i][j] = j;
    }
    for (int h = 2; h <= n; h++)
    {
        for (int i = 0; i <= n - h; i++)
        {
            j = i + h;
            m = ar[i][j - 1];
            min = ap[i][m - 1] + ap[m][j];
            for (int k = m + 1; k <= ar[i + 1][j]; k++)
            {
                x = ap[i][k - 1] + ap[k][j];
                if (x < min)
                {
                    m = k;
                    min = x;
                }
            }
            ap[i][j] = min + aw[i][j];
            ar[i][j] = m;
        }
    }
}

void DOP(int L, int R, int **ar, tree **p, node *A)
{
    if (L < R)
    {
        int k = ar[L][R];
        TreeAdd(A[k - 1], p);
        DOP(L, k - 1, ar, p, A);
        DOP(k, R, ar, p, A);
    }
}
void matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    tree *p = nullptr;
    node *ARR = new node[100];
    node *ARR1 = new node[10];
    fill_rand(ARR, 100);
    fill_rand(ARR1, 10);
    printf("\n");
    int **aw{new int *[101]{}};
    int **ap{new int *[101]{}};
    int **ar{new int *[101]{}};
    for (unsigned i{}; i < 101; i++)
    {
        aw[i] = new int[101]{};
        ap[i] = new int[101]{};
        ar[i] = new int[101]{};
    }
    int **aw1{new int *[11]{}};
    int **ap1{new int *[11]{}};
    int **ar1{new int *[11]{}};
    for (unsigned i{}; i < 11; i++)
    {
        aw1[i] = new int[11]{};
        ap1[i] = new int[11]{};
        ar1[i] = new int[11]{};
    }
    AW(100, aw, ARR);
    APAR(aw, ap, ar, 100);
    AW(10, aw1, ARR1);
    APAR(aw1, ap1, ar1, 10);
    printf("\n\n\n\n");
    matrix(aw1, 11);
    printf("\n\n\n\n");
    matrix(ap1, 11);
    printf("\n\n\n\n");
    matrix(ar1, 11);
    printf("\n\n\n\n");
    DOP(0, 100, ar, &p, ARR);
    LRr(p);
    printf("\n\n\n\n");
    printf("////////|///////////////////////////////////|\n");
    printf("| n=100 |  Size  |   SUM  | Height | Avg.   |\n");
    printf("|       |        |        |        | weight |\n");
    printf("////////|////////|////////|/////////////////|\n");
    printf("|  DOP  |%8d|%8d|%8d|%.6f| %.6f\n", size(p), sum(p), Height(p), getAvgWeightedHeight(p), double(ap[0][100]) / aw[0][100]);
    printf("|///////|////////|////////|////////|////////|\n");
    printf("\n");
    return 0;
}
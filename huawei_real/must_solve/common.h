#define MAX_INT 2147483647

#define swap(a, i, j)     \
    do                    \
    {                     \
        int tmp = a[(i)]; \
        a[(i)] = a[(j)];  \
        a[(j)] = tmp;     \
    } while (0);

#define SHOW(a, n)                   \
    for (int q = 0; q < (n); ++q)    \
    {                                \
        printf("%2d ", int((a)[q])); \
    }                                \
    cout << endl;

#define SHOW_M(a, n, m)                     \
    for (int q = 0; q < (n); ++q)           \
    {                                       \
        for (int p = 0; p < (m); ++p)       \
        {                                   \
            printf("%3d ", int((a)[q][p])); \
        }                                   \
        cout << endl;                       \
    }
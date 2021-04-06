#include <bits/stdc++.h>
using namespace std;
const int MAX_Q = 3e5 + 9, MOD = 1e9 + 7;

int query_start_row[MAX_Q], query_end_row[MAX_Q];
int query_from[MAX_Q], query_to[MAX_Q];
char row_strings[MAX_Q][22];

int mat[MAX_Q][22][22];

int main()
{
    // read input
    int N, Q, top_row = 0, bottom_row = 0, query_counter = 0;
    cin >> N >> Q;
    while (Q--)
    {
        char cmd[10];
        scanf("%s", cmd);
        if (cmd[0] == 'a')
            scanf("%s", row_strings[bottom_row++]);
        else if (cmd[0] == 'r')
            top_row++;
        else
        {
            query_start_row[query_counter] = top_row, query_end_row[query_counter] = bottom_row - 1;
            scanf("%d %d", &query_from[query_counter], &query_to[query_counter]);
            query_from[query_counter]--;
            query_to[query_counter]--;
            query_counter++;
        }
    }

    // compute queries
    for (int k = 0; k < query_counter; )
    {
        
        int first_query = k;
        // find the last query that has a window that contains the first query's bottom row
        for (; k < query_counter; k++)
        {
            if (query_start_row[k] > query_end_row[first_query]) break;
        }
        int last_query = k - 1;


        int window_top = query_start_row[first_query];
        int window_bottom = query_end_row[last_query];
        int cut = query_start_row[last_query];

        for (int a = 0; a < N; a++)
        {
            for (int b = 0; b < N; b++)
            {
                mat[cut][a][b] = (a == b);
            }
        }

        // build lower half
        for (int j = cut; j < window_bottom; j++)
        {
            for (int a = 0; a < N; a++)
            {
                for (int b = 0; b < N; b++)
                    mat[j + 1][b][a] = 0;
                for (int x = -1; x <= 1; x++)
                {
                    int e = a + x;
                    if (e < 0 || e >= N) continue;
                    if (row_strings[j + 1][a] == row_strings[j][e])
                    {
                        for (int b = 0; b < N; b++)
                        {
                            mat[j + 1][b][a] += mat[j][b][e];
                            mat[j + 1][b][a] %= MOD;
                        }
                    }
                }
            }
        }

        // build upper half
        for (int j = cut; j > window_top; j--)
        {
            for (int a = 0; a < N; a++)
            {
                for (int b = 0; b < N; b++)
                    mat[j - 1][b][a] = 0;
                for (int x = -1; x <= 1; x++)
                {
                    int e = a + x;
                    if (e < 0 || e >= N) continue;
                    if (row_strings[j - 1][a] == row_strings[j][e])
                    {
                        for (int b = 0; b < N; b++)
                        {
                            mat[j - 1][b][a] += mat[j][b][e];
                            mat[j - 1][b][a] %= MOD;
                        }
                    }
                }
            }
        }

        for (int i = first_query; i <= last_query; i++)
        {
            int ans = 0;
            int a = query_from[i], b = query_to[i];
            int x = query_start_row[i], y = query_end_row[i];
            for (int j = 0; j < N; j++)
            {
                ans += 1LL * mat[x][j][a] * mat[y][j][b] % MOD;
                ans %= MOD;
            }
            printf("%d\n", ans);
        }
    }
}

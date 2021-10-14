#include <stdio.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#define n 4  //選択肢の数 (1~5)

//条件を満たすならば 1, 他は0

int is_hansha(int r[n][n]) {
    rep(x, n) if (!r[x][x]) return 0;
    return 1;
}

int is_kanbi(int r[n][n]) {
    rep(x, n) rep(y, n) {
        if (x == y) continue;
        if (r[x][y] == 0 && r[y][x] == 0) return 0;
    }
    return 1;
}

int is_suii(int r[n][n]) {
    rep(x, n) rep(y, n)
        rep(z, n) if (r[x][y] && r[y][z]) if (!r[x][z]) return 0;
    return 1;
}

int is_hantaishou(int r[n][n]) {
    rep(x, n) rep(y, n) if (r[x][y] && r[y][x]) if (x != y) return 0;
    return 1;
}

int is_hitaishou(int r[n][n]) {
    rep(x, n) rep(y, n) if (r[x][y]) if (r[y][x]) return 0;
    return 1;
}

int is_taishou(int r[n][n]) {
    rep(x, n) rep(y, n) if (r[x][y]) if (!r[y][x]) return 0;
    return 1;
}

int main(void) {
    int ans = 0;
    rep(i, 1 << (n * n)) {
        int R[n][n] = {0};
        rep(j, n) rep(k, n) R[j][k] = (i >> (j * n + k)) % 2;

        if (!is_hansha(R)) continue;
        if (!is_kanbi(R)) continue;
        if (!is_suii(R)) continue;
        //  if (is_hantaishou(R)) continue;
        //	if (!is_hitaishou(R))continue;
        //	if (!is_taishou(R))continue;

        ans++;
        printf("%d.\n", ans);
        rep(j, n) {
            rep(k, n - 1) printf("%d, ", R[j][k]);
            printf("%d\n", R[j][n - 1]);
        }
        printf("\n");
    }
        printf("\n%d / %d\n", ans, 1 << (n * n));
        return 0;
}
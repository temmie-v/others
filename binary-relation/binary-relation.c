#include <stdio.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define n 4  // number of choices (up to 5)

int is_hansha(int r[n][n]) {
    rep(x, n) if (!r[x][x]) return 0;
    return 1;
}

int is_kanbi(int r[n][n]) {
    rep(x, n) rep(y, n) if (x != y && !r[x][y] && !r[y][x]) return 0;
    return 1;
}

int is_suii(int r[n][n]) {
    rep(x, n) rep(y, n) rep(z, n) if (r[x][y] && r[y][z] && !r[x][z]) return 0;
    return 1;
}

int is_hantaishou(int r[n][n]) {
    rep(x, n) rep(y, n) if (r[x][y] && r[y][x] && x != y) return 0;
    return 1;
}

int is_hitaishou(int r[n][n]) {
    rep(x, n) rep(y, n) if (r[x][y] && r[y][x]) return 0;
    return 1;
}

int is_taishou(int r[n][n]) {
    rep(x, n) rep(y, n) if (r[x][y] && !r[y][x]) return 0;
    return 1;
}

void solve(int op[6]) {
    int ans = 0;
    rep(i, 1 << (n * n)) {
        int r[n][n] = {0};
        rep(j, n) rep(k, n) r[j][k] = (i >> (j * n + k)) % 2;
        if (!(op[0] ^ is_hansha(r))) continue;
        if (!(op[1] ^ is_kanbi(r))) continue;
        if (!(op[2] ^ is_suii(r))) continue;
        if (!(op[3] ^ is_hantaishou(r))) continue;
        if (!(op[4] ^ is_hitaishou(r))) continue;
        if (!(op[5] ^ is_taishou(r))) continue;
        ans++;
        printf("%d.\n", ans);
        rep(j, n) rep(k, n) printf(k - n + 1 ? "%d, " : "%d\n", r[j][k]);
        printf("\n");
    }
    printf("\nResult : %d / %d", ans, 1 << (n * n));
}

int main(void) {
    char options[6][11] = {"hansha",     "kanbi",     "suii",
                           "hantaishou", "hitaishou", "taishou"},
         buf[20];
    int req[6];
    printf("answer in one letter: 'y'(yes), 'n'(no), or 'u'(unspecified)\n");
    rep(i, 6) {
        printf("the binary relation should be %s : ", options[i]);
        scanf("%s", buf);
        req[i] = (buf[0] == 'y' ? 0 : (buf[0] == 'n' ? 1 : 2));
    }
    solve(req);
    return 0;
}
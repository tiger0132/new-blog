#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>

const int N = 1e6 + 61;
void SA(int n, int *s, int *sa, int *ht) {
	static int rk[N], v[N], tmp[N], m = 1e6;
	for (int i = 1; i <= n; i++) rk[i] = s[i], v[i] = i;
	for (int i = 1; i <= n; i++) tmp[rk[v[i]]]++;
	for (int i = 1; i <= m; i++) tmp[i] += tmp[i - 1];
	for (int i = n; i >= 1; i--) sa[tmp[rk[v[i]]]--] = v[i];
	for (int k = 1, p; k <= n && p < n; k <<= 1) {
		p = 0;
		for (int i = n - k + 1; i <= n; i++) v[++p] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k) v[++p] = sa[i] - k;
		memset(tmp, 0, sizeof tmp);
		for (int i = 1; i <= n; i++) tmp[rk[v[i]]]++;
		for (int i = 1; i <= m; i++) tmp[i] += tmp[i - 1];
		for (int i = n; i >= 1; i--) sa[tmp[rk[v[i]]]--] = v[i], v[i] = 0;
		std::swap(rk, v), rk[sa[1]] = 1, p = 1;
		for (int i = 2; i <= n; i++) rk[sa[i]] = (v[sa[i]] == v[sa[i - 1]] && v[sa[i] + k] == v[sa[i - 1] + k]) ? p : ++p;
		m = p;
	}
	for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	int lb = 0;
	for (int i = 1; i <= n; i++) {
		if (!rk[i]) continue;
		lb = std::max(0, lb - 1);
		for (int j = sa[rk[i] - 1]; lb + i <= n && lb + j <= n && s[lb + i] == s[lb + j];) lb++;
		ht[rk[i]] = lb;
	}
}

int n, k, l, r, ans, s[N], sa[N], ht[N];
std::deque<int> q;
int main() {
	scanf("%d%d", &n, &k), k--;
	for (int i = 1; i <= n; i++) scanf("%d", s + i);
	SA(n, s, sa, ht);
	for (int i = 1; i <= n; i++) {
		while (!q.empty() && q.back() <= i - k) q.pop_back();
		while (!q.empty() && ht[q.front()] >= ht[i]) q.pop_front();
		q.push_front(i);
		if (i >= k && !q.empty()) ans = std::max(ans, ht[q.back()]);
	}
	printf("%d", ans);
}
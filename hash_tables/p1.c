#include "../utils.h"

#define SLEN 6

bool snowflake_areidentical(int s1[], int s2[]) {
	bool equal = array_isequal(s1, s2, SLEN);
	if (equal) return 1;

	int found = false;
	for (int i=0; i<SLEN; i++) {
		for (int n=0; n<SLEN; n++) {
			bool is_equallhs = array_isequalwrap(s1, s2, SLEN, n, false);
			bool is_equalrhs = array_isequalwrap(s1, s2, SLEN, n, true);
			if (is_equallhs || is_equalrhs) {
				found = true;
				break;
			}
		}
	}
	return found;
}

void solution(int arr[][SLEN], int len) {
	for (int i=0; i<len; i++) {
		for (int j=i+1; j<len; j++) {
			if (snowflake_areidentical(arr[i], arr[j])) {
				puts("Twin snowflakes found.");
				return;
			}
		}
	}
	puts("No two snowflakes are alike.");
}

/* keep in mind the stack size!~! */
static int arr[100000][SLEN];
int main() {
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; i++) {
		for (int j=0; j<SLEN; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
 	solution(arr, n);
	return 0;
}

/* Program too slow!! */
#include "../utils.h"

#define SLEN 6
#define MAX_COUNT 100000

typedef struct SF_Node {
	int data[SLEN];
	struct SF_Node *next;
} SF_Node;

// Crude way to reduce comparison of snowflakes
int hash(int arr[]) {
	int sum = 0;
	for (int i=0; i<SLEN; i++) {
		sum += arr[i];
	}
	return sum % MAX_COUNT;
}

bool snowflake_areidentical(SF_Node *s1, SF_Node *s2) {

	int *a = s1->data;
	int *b = s2->data;

	int found = false;
	for (int i=0; i<SLEN; i++) {
		for (int n=0; n<SLEN; n++) {
			bool is_equallhs = array_isequalwrap(a, b, SLEN, n, false);
			bool is_equalrhs = array_isequalwrap(a, b, SLEN, n, true);
			if (is_equallhs || is_equalrhs) {
				found = true;
				break;
			}
		}
	}
	return found;
}

void solution(SF_Node *arr[]) {
	SF_Node *n_i, *n_j;

	for (int i=0; i<MAX_COUNT; i++) {
		n_i = arr[i];
		if (n_i == NULL) continue;

		for (; n_i->next != NULL; n_i = n_i->next) {
			for (n_j = n_i->next; n_j != NULL; n_j = n_j->next) {

				if (snowflake_areidentical(n_i, n_j)) {
					puts("Twin snowflakes found.");
					return;
				}
			}
		}
	}
	puts("No two snowflakes are alike.");
}

static SF_Node *snowflakes[MAX_COUNT] = {NULL};
int main() {
	SF_Node *ptr;

	int n, idx;
	scanf("%d", &n);

	for (int i=0; i<n; i++) {
		ptr = malloc(sizeof(SF_Node));

		for (int j=0; j<SLEN; j++) {
			scanf("%d", &ptr->data[j]);
		}

		idx = hash(ptr->data);
		ptr->next = snowflakes[idx];
		snowflakes[idx] = ptr;
	}
	solution(snowflakes);
	// not gonna deallocate :P
	return 0;
}

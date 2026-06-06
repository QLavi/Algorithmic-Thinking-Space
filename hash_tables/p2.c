#include "../utils.h"

typedef struct string {
    char *data;
    size_t len;
} string;

#define MAX_CHARS 1024
char string_pool[MAX_CHARS];
size_t used = 0;

string string_create(char *data, size_t len, bool do_alloc) {
    string s;

    if (do_alloc) {
        if (used + len > MAX_CHARS) {
            printf("[ERROR]: cannot allocate more strings.\n");
            exit(1);
        }
        s.data = string_pool + used;

        for (size_t i=0; i<len; i++) {
            s.data[i] = data[i];
        }
    } else {
        s.data = data;
    }

    s.len = len;

    if (do_alloc) {
        used += len;
    }
    return s;
}

bool string_isequal(string a, string b, size_t cmp_len) {
    if (cmp_len > a.len || cmp_len > b.len) {
        return false;
    }
    for (size_t i=0; i<cmp_len; i++) {
        if (a.data[i] != b.data[i]) {
            return false;
        }
    }
    return true;
}

bool string_issubstr(string str, string sub) {
    if (str.len < sub.len) return false;
    bool found = false;
    string tmp_str;
    for (size_t i=0; i<str.len - sub.len + 1; i++) {
        tmp_str.data = str.data + i;
        tmp_str.len = sub.len;
        if (string_isequal(tmp_str, sub, sub.len)) {
            found = true;
        }
    }
    return found;
}

string string_concat(string a, string b) {
    if (used + a.len + b.len > MAX_CHARS) {
        printf("[ERROR] cannot allocate more strings.\n");
        exit(1);
    }
    char *data = string_pool + used;

    size_t i = 0;
    for (; i<a.len; i++) {
        data[i] = a.data[i];
    }
    for (; i<a.len + b.len; i++) {
        data[i] = b.data[i - a.len];
    }
    used += a.len + b.len;
    return string_create(data, a.len + b.len, false);
}

void string_print(string s) {
    for (size_t i=0; i<s.len; i++) {
        printf("%c", s.data[i]);
    }
    putchar('\n');
}

#define MAX_STRS 128
static string compounds[MAX_STRS];
size_t count = 0;

void solution(string strs[], size_t N) {
    for (size_t curr = 0; curr < N; curr++) {
        
        for (size_t s1 = 0; s1 < N; s1++) {
            if (s1 == curr) continue;

            for (size_t s2 = s1+1; s2 < N; s2++) {
                if (s2 == curr) continue;

                string a = string_concat(strs[s1], strs[s2]);
                string b = string_concat(strs[s2], strs[s1]);
                
                if (
                    string_issubstr(strs[curr], a) ||
                    string_issubstr(strs[curr], b)) {
                        compounds[count++] = strs[curr];
                    }

            }
        }
    }

    for (size_t i=0; i<count; i++) {
        string_print(compounds[i]);
    }
}

#define MAX_INPUT_STRS 128
static string input_strings[MAX_INPUT_STRS];
int main() {
    char curr_str[64];
    size_t N;
    scanf("%ld", &N);
    for (size_t i=0; i<N; i++) {
        scanf("%s", curr_str);
        input_strings[i] = string_create(curr_str, strlen(curr_str), true);
    }
    solution(input_strings, N);
    return 0;
}
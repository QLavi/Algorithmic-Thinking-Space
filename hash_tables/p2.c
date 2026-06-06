/*
Idea:
    We break the word into two parts as shown in the following example
    c reate
    cr eate
    cre ate
    crea te
    creat e

    These two parts are then checked if they are present in the hash table containing
    all the words.
*/

#include "../utils.h"

typedef struct string {
    char *data;
    size_t hash;
    size_t len;
} string;

#define MAX_CHARS 1024
char string_pool[MAX_CHARS];
size_t used = 0;

size_t string_hash(char *s, size_t len) {
    size_t hash = 2166136261u;
    for (size_t i=0; i<len; i++) {
        hash ^= (size_t)s[i];
        hash *= 16777619;
    }

    return hash;
}

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
    s.hash = string_hash(s.data, len);
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


typedef struct Word_Node {
    string s;
    struct Word_Node *next;
} Word_Node;

#define MAX_ENTRIES 1024
static Word_Node *hash_table[MAX_ENTRIES] = {NULL};


bool hashtable_in(string s) {
    size_t idx = s.hash % MAX_ENTRIES;
    for(Word_Node *p=hash_table[idx]; p != NULL; p = p->next) {
        if (string_isequal(s, p->s, s.len)) {
            return true;
        }
    }

    return false;
}

void solution() {
    string a, b;
    for (size_t i=0; i<MAX_ENTRIES; i++) {
        Word_Node *p = hash_table[i];
        if (p == NULL) continue;

        for (size_t j=1; j<=p->s.len; j++) {
            size_t lhs_len = j;
            size_t rhs_len = p->s.len - j;

            a.data = p->s.data;
            a.len = lhs_len;
            a.hash = string_hash(a.data, a.len);
            // string_print(a);

            b.data = lhs_len + p->s.data;
            b.len = rhs_len;
            b.hash = string_hash(b.data, b.len);
            // string_print(b);

            if (hashtable_in(a) && hashtable_in(b)) {
                string_print(p->s);
            }
           
        }
    }
}

int main() {
    size_t N;
    scanf("%ld", &N);

    char curr_str[MAX_CHARS];

    for (size_t i=0; i<N; i++) {
        scanf("%s", curr_str);
        size_t len = strlen(curr_str);
        string s = string_create(curr_str, len, true);

        Word_Node *n = malloc(sizeof(Word_Node));
        n->s = s;
        n->next = hash_table[s.hash % MAX_ENTRIES];
        hash_table[s.hash % MAX_ENTRIES] = n;
    }
    solution();
    return 0;
}
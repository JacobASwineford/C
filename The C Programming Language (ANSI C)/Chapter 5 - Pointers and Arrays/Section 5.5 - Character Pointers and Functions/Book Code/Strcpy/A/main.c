void strcpy(char*, char*);
void strcpy2(char*, char*);
void strcpy3(char*, char*);
void strcpy4(char*, char*);

int main() {

    return 0;
}

/* strcpy: copy t into s; array subscript version */
void strcpy(char *s, char *t) {
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

/* strcpy: copy t into s; pointer version. modified name for compilation. */
void strcpy2(char *s, char *t) {
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

/* strcpy: copy t into s; pointer version 2. modified name for compilation. */
void strcpy3(char *s, char *t) {
    while ((*s++ = *t++) != '\0');
}


/* strcpy: copy t into s; pointer version 3. modified name for compilation. */
void strcpy4(char *s, char *t) {
    while (*s++ = *t++);
}





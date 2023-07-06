int strlen(char*);

int main() {

    return 0;
}

/* strlen: return length of string s */
int strlen(char *s) {
    int n;

    for (n = 0; *s != '/0'; s++)
        n++;
    return n;
}

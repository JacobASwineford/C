#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main() {
	FILE* fp;
	char buff[255];
	void* methods[2];
	
	fp = fopen("readme.txt", "r");
	if (fgets(buff, 255, fp)) {
		printf("%s\n", buff);
		char* tok = strtok(buff, ":");
		while (tok) {
			printf("%s\n", tok);
			tok = strtok(NULL, " ");
		}
	} else {
	}
	
	
	
	
	fclose(fp);
	return 0;
}
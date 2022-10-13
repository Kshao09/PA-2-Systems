#include"find.h"
#define MAX_LINES 1000
#define MAX_LEN 1000
char*lineptr[MAX_LINES];
int results[MAX_LINES];
char* strstr_fully_matched(char* haystack, char* needle){
	char* rv;
	char padded_needle[strlen(needle) + 3];
	padded_needle[0] = ' ';
	strcpy(padded_needle + 1, needle);
	padded_needle[strlen(needle) + 1] = ' ';
	padded_needle[strlen(needle) + 2] = '\0';
	if(!strncmp(haystack, padded_needle + 1, strlen(needle) + 1))
		return haystack;
	if((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;
	padded_needle[strlen(needle) + 1] = '\0';
	if((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;
}
int getline2(char s[], int lim){
	int c, i;
	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n';i++)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}
int readlines(char** lineptr, int maxlines){
	int len, nlines;
	char*p, line[MAX_LEN];
	
	nlines = 0;
	while((len = getline2(line, MAX_LEN)) > 0)
		if(nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else{
			if(line[len - 1] == '\n')
				line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}
int main(int argc, char** argv) {
    int except = 0;//0 or 1
	int sorted = 0;//0 or 1
	int reversed = 0;//0 or 1
	int partial = 0;//0 or 1
	int numbered = 0;//0 or 1
	int first_occurrence = 0;//0 or 1
	int matched = 0;//0 or 1
	char* pattern = "in";
	//....
	//handle command line arguments...
	//similar to #41 of Chapter 5 partII.pptx
	int nlines = readlines(lineptr, MAX_LINES);//similar, but not the same as the slide #23 of Chapter 5 partII.pptx
	int no_of_results = 0;
	for(int i = 0; i < nlines;i++)
		printf("\n%s\n", lineptr[i]);
	for(int i = 0; i < nlines;i++){
		if(matched){
			if((strstr_fully_matched(lineptr[i], pattern) != NULL) != except)
				results[no_of_results++] = i;
		}else{
			if((strstr(lineptr[i], pattern) != NULL) != except)
				results[no_of_results++] = i;
		}
	}
	print_results(pattern, matched, first_occurrence, numbered, sorted, partial, reversed, no_of_results);
    return 0;
}

#include "find.h"

int ignore_white_space(char* str){
    int count = 0;
    int len_str = strlen(str);
    for(int i =0; i <len_str; i++){
        if (str[i] != ' ')
            count++;
    }
    return count;
}
int white_space(char* str){
    int count = 0;
    int len_str = strlen(str);
    for(int i =0; i <len_str; i++){
        if (str[i] == ' ')
            count++;
    }
    return count;
}
void reverse(char* v[], int no_of_results) {
  char *temp;
  int i, j;
  for(i=0,j= no_of_results -1; i<j; i++, j--){
    temp = v[i];
    v[i]= v[j];
    v[j]= temp;
  }
}

void swap(char* v[], int i, int j) {
	char* temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void quickSort(char* v[], int left, int right) {
	int i, last;
	void swap(char* v[], int i, int j);

	if (left >= right)
		return;

	swap(v, left, last);
	quickSort(v, left, last - 1);
	quickSort(v, last + 1, right);
}

void print_results(char* pattern, int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed,int case_ignore, int no_of_results){
    char** sentences = (char**)malloc(no_of_results*sizeof(char*));
    for(int i = 0; i < no_of_results; i++){
        sentences[i] = strdup(lineptr[results[i]]);
    }
    if(sorted){
        quickSort(sentences,0,no_of_results-1);
    }else if (reversed){
        reverse(sentences, no_of_results);
    }
    for(int i = 0; i < no_of_results; i++) {
        if (numbered)
            printf("@%d. ", results[i] + 1);
        if (first_occurrence) {
            if (matched) {
                if(case_ignore){
                    char* haystack_lower = str_tolower(sentences[i]);
                    char* needle_lower = str_tolower(pattern);
                    printf("@%ld. ", strstr_fully_matched(haystack_lower, needle_lower) - haystack_lower);
                }else
                    printf("@%ld. ", strstr_fully_matched(sentences[i], pattern) - sentences[i]);
            }else
                if (case_ignore){
                    char* haystack_lower = str_tolower(sentences[i]);
                    char* needle_lower = str_tolower(pattern);
                    printf("@%ld. ", strstr(haystack_lower, needle_lower) - haystack_lower);
                }else
                    printf("@%ld. ", strstr(sentences[i], pattern) - sentences[i]);
        }
        if(partial){
            long index;
            char* word = sentences[i];
            int word_len = ignore_white_space(word);
            int needle_len = strlen(pattern);
            if (matched) {
                if(case_ignore){
                    char* haystack_lower = str_tolower(sentences[i]);
                    index = strstr_fully_matched(haystack_lower,str_tolower(pattern)) - haystack_lower;
                }else{
                    index = strstr_fully_matched(sentences[i],pattern) - sentences[i];
                }
            }else{
                if(case_ignore){
                    char* haystack_lower = str_tolower(sentences[i]);
                    index = strstr(haystack_lower,str_tolower(pattern)) - haystack_lower;
                }else{
                    index = strstr(sentences[i],pattern) - sentences[i];
                }
            }
            if (index < 10 && word_len > 15)
                printf("%.*s %s...%.*s\n",10, word, pattern,5, word + (word_len-5));
            else if (index > word_len-5 && word_len > 15)
                printf("%.*s...%s %.*s\n",10, word, pattern,5, word + (word_len + white_space(word)-5));
            else if(word_len < (needle_len + 15))
                printf("%s\n",sentences[i]);
            else
                printf("%.*s...%s...%.*s\n", 10,word, pattern,5, word + (word_len + white_space(word)-5));
        }else
            printf("%s\n", sentences[i]);
    }
}

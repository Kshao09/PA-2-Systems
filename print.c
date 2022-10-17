#include "find.h"

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

void print_results(char* pattern, int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed, int ignore_case, int no_of_results) {
	char** sentences = (char**) malloc(no_of_results * sizeof(char*));
	
	for (int i = 0; i < no_of_results; i++) {
		sentences[i] = strdup(lineptr[results[i]]);
	}
	if(sorted){
    quickSort(sentences, 0, no_of_results -1); //calling qsort on sentences
  } else if (reversed) {
      reverse(sentences, no_of_results*sizeof(char)); //reverse on sentences
  }
	printf("\n\n");
	
	for (int i = 0; i < no_of_results; i++) {
		if (numbered) {
			printf("%d. ", results[i] + 1); 
		}
		
		if (first_occurrence) {
			if (matched) {
				printf("@%d: ", strstr_fully_matched(sentences[i], pattern) - sentences[i]);
			} else
				printf("@%d: ", strstr(sentences[i], pattern) - sentences[i]);
		}
		
		if (partial) {
		    char* lastWord = strcpy(lastWord, lineptr[results[strlen(lineptr[results[i]])-5]]);
		    char* firstWord = strcpy(firstWord, lineptr[results[10]]);
		    
		    if (strstr_fully_matched(lineptr[results[i]], pattern)) {
		        printf("%s %s...%s\n",firstWord, pattern, lastWord);
		    } else {
		        printf("%s...%s...%s\n", firstWord, pattern, lastWord);
		    }
		}
		printf("%s\n", sentences[i]);
	}
}

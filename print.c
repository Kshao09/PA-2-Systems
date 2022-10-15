#include "find.h"

void reverse(char* v[], int no_of_results) {
	char* temp;
	int end = no_of_results-1;
	for (int start = 0; start < end; start++) {
	    temp = v[start];
	    v[start] = v[end];
	    v[end] = temp;
	    end--;
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
	
	swap(v, left, (left + right)/2);
	last = left;

	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	quickSort(v, left, last - 1);
	quickSort(v, last + 1, right);
}

void print_results(char* pattern, int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed, int ignore_case, int no_of_results) {
	char** sentences = (char**) malloc(no_of_results * sizeof(char*));
	
	for (int i = 0; i < no_of_results; i++) {
		sentences[i] = strdup(lineptr[results[i]]);
	}
	
	if (sorted) {
		quickSort(sentences, 0, no_of_results - 1);
	}else if (reversed) {
		reverse(sentences, no_of_results);
	}

	printf("\n\n");
	
	for (int i = 0; i < no_of_results; i++) {
		if (numbered)
			printf("%d. ", results[i] + 1); 
		if (first_occurrence)
			if (matched)
				printf("@%d: ", strstr_fully_matched(sentences[i], pattern) - sentences[i]);
			else
				printf("@%d: ", strstr(sentences[i], pattern) - sentences[i]);
		
		printf("%s\n", sentences[i]);
	}
}

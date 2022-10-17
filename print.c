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
		
		if(partial) {
                int index;
                char word = sentences[i];
                int word_len = strlen(word);
                int length_of_pattern = strlen(pattern);

                if (matched) {
                    if (ignore_case) {
                        char toLow = str_tolower(sentences[i]);
                        index = (int) (strstr_fully_matched(toLow, str_tolower(pattern)) - toLow);
                    } else {
                        index = (int) (strstr_fully_matched(sentences[i], pattern) - sentences[i]);
                    }
                } else {
                    if (ignore_case) {
                        char *toLowTwo = str_tolower(sentences[i]);
                        index = (int) (strstr(toLowTwo, str_tolower(pattern)) - toLowTwo);
                    } else {
                        index = (int) (strstr(sentences[i], pattern) - sentences[i]);

                    }
                }

				if (word_len <= length_of_pattern + 15) {
                    printf("%s\n", sentences[i]);
                } else if (index < 10) {
                    printf("%.s %s...%.s\n", 10, word, pattern, 5, word + (word_len - 5));
                } else if (matched && index + length_of_pattern >= word_len - 5 && index > 10) {
                    printf("%.s...%s %.s\n", 10, word, pattern, 5, word + (word_len - 5));
                }
                else if (index + length_of_pattern-1 >= word_len - 5 && index > 10) {
                    printf("%.s...%s %.s\n", 10, word, pattern, 5, word + (word_len - 5));
                }
                else{
                    printf("%.s...%s...%.s\n", 10, word, pattern, 5, word +(word-5));
                }

            } if(!partial) {
                printf("%s\n", sentences[i]);
            }
		printf("%s\n", sentences[i]);
	}
}

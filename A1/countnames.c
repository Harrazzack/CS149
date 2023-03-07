/**
 * Description: Take in a txt file full of names seperated by new lines as input and output the count of each unique name in the txt file. 
 * Author names: Haroon Razzack and Vincent Nguyen
 * Author emails: haroon.razzack@sjsu.edu and Vincent.Nguyen@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023 
 **/
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 30
#define MAX_NUM_NAMES 100

int main(int argc, char *argv[]) {
  // check if input arguments are correct 
  if (argc != 2) {
    fprintf(stderr, "Usage: countnames <filename>\n");
    return 1;
  }

  // Open the input file
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Error: could not open file %s\n", argv[1]);
    return 1;
  }

  // Initialize an array to store the names and their counts
  char names[MAX_NUM_NAMES][MAX_NAME_LENGTH+1];
  int counts[MAX_NUM_NAMES] = {0};
  int num_names = 0;

  // Read the names from the file and count their occurrences
  char line[MAX_NAME_LENGTH+2];  // +2 for the newline and null terminator
  int line_num = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
    line_num++; // counting line number 
    if (line[0] == '\n') {
      fprintf(stderr, "Warning - Line %d is empty.\n", line_num);
      continue;
    }
    // Remove the trailing newline character
    line[strcspn(line, "\n")] = '\0';
    // Search for the name in the array
    int i, match_index = -1;
    for (i = 0; i < num_names; i++) {
      if (strcmp(names[i], line) == 0) {
        match_index = i;
        break;
      }
    }
    // Update the counts
    if (match_index == -1) {
      if (num_names == MAX_NUM_NAMES) {
        fprintf(stderr, "Error: too many names (max=%d)\n", MAX_NUM_NAMES);
        fclose(fp);
        return 1;
      }
      // Add the name to the array
      strcpy(names[num_names], line);
      counts[num_names] = 1;
      num_names++;
    } else {
      counts[match_index]++;
    }
  }

  // Print the counts
  int i;
  for (i = 0; i < num_names; i++) {
    printf("%s: %d\n", names[i], counts[i]);
  }

  fclose(fp); //remember to close the file
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 256

int stauts(char** buf, Options* opt){
        int line = 0;
        char temp;
        // char *fileName;
        // strcpy(fileName, argv[1]);    
        if(fp != NULL){

            while(fscanf(fp, "%c", &temp) != EOF){
                if(temp == '\n'){
                    line++;
                }
            }
            rewind(fp);
         printf("NUmber of lines: %d\n", line);
        // printf("%s\n", fileName);
        }
        return 0;
}

char** read_init_buffer(FILE* fp, int n) {
    // Allocate initial memory for storing lines (2D array)
    int initial_lines = 10;  // Start with space for 10 lines
    char** buffer = (char**)malloc(initial_lines * sizeof(char*));
    
    if (buffer == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    int line_count = 0;

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        // Remove the newline character, if present
        line[strcspn(line, "\n")] = '\0';

        // Allocate memory for each line
        buffer[line_count] = (char*)malloc((strlen(line) + 1) * sizeof(char));  // +1 for the null terminator

        if (buffer[line_count] == NULL) {
            printf("Memory allocation failed for line %d!\n", line_count);
            // Free already allocated memory and return NULL in case of error
            for (int i = 0; i < line_count; i++) {
                free(buffer[i]);
            }
            free(buffer);
            return NULL;
        }

        // Copy the line into the allocated space
        strcpy(buffer[line_count], line);
        line_count++;

        // Check if we need to reallocate memory for more lines
        if (line_count >= initial_lines) {
            initial_lines *= 2;  // Double the number of lines we can store
            buffer = (char**)realloc(buffer, initial_lines * sizeof(char*));
            
            if (buffer == NULL) {
                printf("Memory reallocation failed!\n");
                return NULL;
            }
        }
    }

    // Reallocate to fit the exact number of lines if needed
    buffer = (char**)realloc(buffer, ++line_count * sizeof(char*));


    return buffer;
}

typedef enum cmd {FORMAT_ERROR = -2, UNKOWN_CMD_ERROR = -1, PRINT = 0, DEL, SAVE, STAT, CHANGE, INS, QUIT, HELP} CMD;

CMD get_cmd(char prompt){
    if(prompt = 's'){
        return STAT;
    }
}


int main(int argc, char *argv[]){

        int (*exec_cmd[])(char**) = {stauts};
        char prompt = '*';

        // open file and change prompt
        // FILE *fp = process_cmd_args(argc, argv, &prompt);
        FILE *fp = fopen(argv[1], "rt");

        int line = 0;
        char temp;
        char *fileName;
        strcpy(fileName, argv[1]);    
        if(fp != NULL){

            while(fscanf(fp, "%c", &temp) != EOF){
                if(temp == '\n'){
                    line++;
                }
            }
            rewind(fp);
        //  printf("%d\n", line);
        // printf("%s\n", fileName);
  
        } else {
            printf("Error! can not find the file.\n");
            exit(1);
        }

        

        char** buffer = read_init_buffer(fp, line);
        if (buffer == NULL) {
            printf("Failed to read file into buffer!\n");
            return 1;
        }

        
        printf("File Content:\n");
        for (int i = 0; buffer[i] != NULL; i++) {
            printf("%d", i);
            printf("%s\n", buffer[i]);
            free(buffer[i]);  // Free memory for each line after printing
        }
        free(buffer[2]);
        int ret = 0;


        // read command and execute
        // while(ret >= 0){
        //         CMD cmd = get_cmd(prompt);
        //         ret = (exec_cmd[cmd])(buffer);
        //         if(ret > 0){
        //                 printf("%s\n", msg[ret]);
        //         }
        // }



        fclose(fp);
        free(buffer);

        return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <dirent.h>

int CD(char **args);

char *builtin_str[] = {"cd"};

int (*builtin_func[]) (char **) = {&CD};

int CD(char **args)
{
  if (args[1] == NULL)
    fprintf(stderr, "Shell error: \"cd\" needs an extra argument: \n");
  else {
    if (chdir(args[1]) != 0) {
      perror("Shell");}
    }
  return 1;
}

bool Wildcard_compare(const char *pattern, const char *candidate, int p, int c)
{
  if (pattern[p] == '\0') {
    return candidate[c] == '\0';}
  if (pattern[p] != '?' && pattern[p] != candidate[c])
    return false;
  else
    return Wildcard_compare(pattern, candidate, p+1, c+1);
}

int Wildcard_expansion(char *str)
{
  DIR *dir;
  struct dirent *entry;
  dir = opendir(".");
  if (dir == NULL) {
    printf("Failed to open directory.\n");
    return 1;
  }
  while ((entry = readdir(dir)) != NULL) {
    if(entry->d_type != DT_DIR) {
      for (int k = 0; str[k] != '\0' ; k++){
      	if (str[k] == '\n'){
      		str[k] = '\0';
      		break;}
      	}
	if (Wildcard_compare(str,entry->d_name,0,0)){
		printf("%s\n", entry->d_name);}
	else{
	}   
    }
  }
  return 0;
}

int Processed(char **parsed)
{
    pid_t pid = fork();
    if (pid == -1) {
        printf("\nFailed to fork() child process");
        return -1;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("Invalid Command\n");}
            exit(0);}
      else {
            wait(NULL); 
            return 1; }
}

int Built_in_commands(char **args)
{
  int i;
  if (args[0] == NULL) {
    return 1;
  }
  for (i = 0; i < 2; i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return Processed(args);
}

char **Parse_Args(char *str)
{
    int buffer_size = 64;
    int i = 0;
    char *arg;
    char **args = malloc(buffer_size * sizeof(char*));
    arg = strtok(str, " \t\r\n\a");
    while (arg != NULL) {
        args[i] = arg;
        i++;
        arg = strtok(NULL, " \t\r\n\a");
    }
    args[i] = NULL;   
    return args;
}

char *Take_Input(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us

  if (getline(&line, &bufsize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We recieved an EOF
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }
  return line;
}

void Shell_Prompt()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("Sharjeel-Anas: %s $", cwd);
}

int main(int argc, char **argv)
{
  char *str;
  char *wild;
  char **args;
  int status;
  int wildcard;
  do {
    Shell_Prompt();
    str = Take_Input();
    	int i,j,ctr;
	char newString[10][10];
	j=0; ctr=0;
  	for(i=0;i<=(strlen(str));i++){
        if(str[i]==' '|| str[i]=='\0'){
            newString[ctr][j]='\0';
            ctr++;
            j=0;}
        else{
            newString[ctr][j]=str[i];
            j++;}
    }
    wild = newString[1];
    int found = 0;
    for(int i =0; wild[i] != '\0';i++){
  	if (wild[i] == '?')
  		found = 1;
    }
    if (found == 1)
    	wildcard = Wildcard_expansion(wild);	
    else{
    	args = Parse_Args(str);
    	status = Built_in_commands(args);
    }
  } while (status);
  return EXIT_SUCCESS;
}

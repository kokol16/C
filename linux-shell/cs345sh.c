/* @Author : George Kokolakis csd4254*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
size_t Size = 1024;
typedef struct Pipes_redir
{
  char *symbols[1024]; //keeps information about symbols > || | ||| tha we found

} * pipes_redir;
struct redirections
{
  int found_write;          //if we found ||
  int found_read;           //if we found |
  int redir_position;       //position of current redirection
  int found_wrt_end;        //if we found |||
  int redir_pos_with_pipes; // redirection's position when we have pipes too
};

struct redirections_info
{
  int redirections_counted;
  char *last_file[1024];    //last file for each redirection symbol
  int read_write;           //found read and write redirection
  char *last_command[1024]; //last command to be executed among redirections*/
  int index_commands;
  int multiple_redir;              // if we have found multiple rediretions
  int last_redir_pos;              //the position of the last redirection*/
  char *command_before_read[1024]; /* the command before read( | ) redirection sumbol*/
};

/* this function handles the case when we have a combination of || and | */
void read_write_redirections(struct redirections_info red_info[]);

/* this function handles the case when we have a combination of ||| and | */

void read_write_end_redirections(struct redirections_info red_info[]);

/* this function handles the case when we have a combination of || and ||| */

void write_write_end_redirections(struct redirections_info red_info[]);

/* this function handles the case when we have a combination of || and | and ||| */

void all_redirections(struct redirections_info red_info[]);

/* 
  this method finds the arguments for every pipe that we have */
int create_pipe_arguments(char *arg_list[], int i, int pipe_position[], int pipe_index, int index, char bin[])
{
  //strcpy(bin, "/bin/");

  int k = 0;

  //begin where the previous pipe where
  int first_arg;
  int end_str;

  if (i == 0)
  {
    k = 0;
    end_str = pipe_position[i];
  }
  else if (i == pipe_index)
  {
    k = pipe_position[i - 1] + 1;
    end_str = index - 1;
    //printf("index is %d\n", index);
  }
  else
  {
    k = pipe_position[i - 1] + 1;
    end_str = pipe_position[i];
  }

  //printf("i is : %d \n",i);
  //printf("pipe postition is  : %d \n", pipe_position[i]);

  //printf("start string is : %d \n", k);
  //printf("end string is : %d \n", end_str);

  int arg_index = 0;
  while (k <= end_str)
  {
    //printf("arg k is : %s\n",arg_list[k]);
    //strcpy(arg_list[arg_index], arg_list[k]);
    arg_list[arg_index] = arg_list[k];

    arg_index++;
    k++;
  }

  arg_list[arg_index] = NULL;
  return arg_index;
  //k++;
}

/* This function tokenizes the input*/

int string_tokenizer(char *arg_list[], int pipe_position[], int *pipe_index, int *found_pipe, int *found_redir, int *redirections, int redir_position[], struct redirections redir[], struct redirections_info redirection_info[], char *all_args[], pipes_redir p_r)
{
  char input[Size];
  char *ptr;
  int in_red[3];
  int symbols_index = 0;
  redirection_info[0].last_file[0] = NULL;
  redirection_info[1].last_file[0] = NULL;
  redirection_info[2].last_file[0] = NULL;
  redirection_info[0].redirections_counted = 0;
  redirection_info[1].redirections_counted = 0;
  redirection_info[2].redirections_counted = 0;
  fgets(input, Size, stdin);

  if (input[strlen(input) - 1] == '\n')
  {
    // printf("im here\n");
    input[strlen(input) - 1] = '\0';
  }
  int last_command_index = 0;
  int index = 0;
  // printf("%s",input);
  int counter = 0;
  int redir_index = 0;
  int redir_counter = 0;
  int in_redir = 0;
  ptr = strtok(input, " ");
  while (ptr != NULL)
  {
    in_red[1] = 0;
    in_red[2] = 0;

    in_red[0] = 0;

    //  in_redir = 0;
    if (*ptr == '>')
    {

      p_r->symbols[symbols_index++] = ptr;
      // printf("counter -1 is : %d \n ", counter - 1);
      pipe_position[*pipe_index] = counter - 1; //find where every pipe is on the string input
      *pipe_index = *pipe_index + 1;
      *found_pipe = 1;
      counter--;
      redir[redir_index].redir_pos_with_pipes = redir[redir_index].redir_pos_with_pipes + 1;
    }
    else if (strcmp(ptr, "|||") == 0 || *ptr == '|' || strcmp(ptr, "||") == 0)
    {
      in_redir = 1;
      p_r->symbols[symbols_index++] = ptr;

      //last_command_index = 0;
      if (strcmp(ptr, "||") == 0)
      {
        in_red[1] = 0;
        in_red[2] = 0;

        in_red[0] = 1;
        redir[redir_index].found_write = 1;
        redir[redir_index].redir_position = redir_counter - 1;

        redirection_info[0].redirections_counted++;
        redirection_info[0].last_redir_pos = counter;
      }
      else if (strcmp(ptr, "|") == 0)
      {

        in_red[0] = 0;
        in_red[2] = 0;

        in_red[1] = 1;

        redir[redir_index].found_read = 1;
        redir[redir_index].redir_position = redir_counter - 1;
        redirection_info[1].redirections_counted++;
        redirection_info[1].last_redir_pos = counter;
      }
      else
      {
        //        printf("ptr : %s\n", ptr);

        in_red[0] = 0;
        in_red[1] = 0;

        in_red[2] = 1;

        redir[redir_index].found_wrt_end = 1;
        redir[redir_index].redir_position = redir_counter - 1;
        redirection_info[2].redirections_counted++;
        redirection_info[2].last_redir_pos = counter;
      }
      redir_index++;

      redir_position[*redirections] = counter - 1; //find where every pipe is on the string input
      *redirections = *redirections + 1;
      *found_redir = 1;
      redir_counter--;
      redir[redir_index].redir_pos_with_pipes = redir[redir_index - 1].redir_pos_with_pipes;
    }
    else
    {

      if (in_redir == 0)
      {
        redirection_info[0].last_command[last_command_index] = ptr;
        //printf("im puting %s\n", ptr);
        redirection_info[1].last_command[last_command_index] = ptr;
        redirection_info[2].last_command[last_command_index] = ptr;
        last_command_index++;
      }

      arg_list[index] = ptr;
      //fprintf(stderr,"arg is %s\n",arg_list[index]);
      all_args[index] = ptr;
      index++;
      //printf("arg : %d is : %s\n",index-1,  arg_list[index-1] );
    }
    if (redirection_info[1].redirections_counted <= 0)
    {
      redirection_info[1].command_before_read[0] = ptr;
      redirection_info[1].command_before_read[1] = NULL;
    }
    if (redirection_info[0].redirections_counted > 0 && redirection_info[0].redirections_counted > 0)
    {
      redirection_info[0].read_write = 1;
    }

    //  printf("%s\n",arg_list[index-1]);
    //  strcpy(arg_list[index],ptr);
    counter++;
    redir_counter++;
    ptr = strtok(NULL, " ");
    if (in_red[0] == 1 && ptr != NULL)
    {

      redirection_info[0].last_file[0] = ptr;
    }
    if (in_red[1] == 1 && ptr != NULL)
    {

      redirection_info[1].last_file[0] = ptr;
    }
    if (in_red[2] == 1 && ptr != NULL)
    {

      redirection_info[2].last_file[0] = ptr;
    }
  }
  if ((redirection_info[2].redirections_counted > 0 && redirection_info[1].redirections_counted > 0) || (redirection_info[2].redirections_counted > 0 && redirection_info[0].redirections_counted > 0) || (redirection_info[1].redirections_counted > 0 && redirection_info[0].redirections_counted > 0))
  {
    redirection_info[0].multiple_redir = 1;
  }
  arg_list[index] = NULL;
  redirection_info[0].last_command[last_command_index] = NULL;
  redirection_info[1].last_command[last_command_index] = NULL;
  redirection_info[2].last_command[last_command_index] = NULL;
  redirection_info[0].index_commands = last_command_index;
  redirection_info[1].index_commands = last_command_index;
  redirection_info[2].index_commands = last_command_index;
  //printf("last command index is %d\n", last_command_index);
  p_r->symbols[symbols_index] = NULL;

  return index;
}

/* this functions runs the shell */
void RunShell(int argc, char *argv[], char *envp[]);

/* This function handle the ctl c signal*/
void sigint_handler(int signo)
{

  return;
  //exit(1); // send an INT signal
}

/* this code is about ctrl h , make v erase mode on */

/*
struct termios orig_termios;

void disableRawMode()
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}*/

/*
void catch_ctrlh(void)
{
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  atexit(disableRawMode);

  raw.c_lflag |=ICANON;
  raw.c_cc[VERASE]=0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

}*/

int main(int argc, char *argv[], char *envp[])
{
  //cath_ctrlh();
  signal(SIGINT, sigint_handler);

  RunShell(argc, argv, envp);
}

void print_prompt()
{
  char dir[Size];

  getcwd(dir, sizeof(dir));
  printf("[cs345sh]");
  printf("[%s]", getlogin());
  printf("[%s]", dir);
  printf("$ ");
}

void RunShell(int argc, char *argv[], char *envp[])
{

  int status;
  int pipefiledisc[1][2];
  pid_t pid;
  char bin[Size];
  int index = 0;
  char *arg_list[Size];
  char *all_args[Size];

  int found_pipe = 0;
  int pipe_position[Size];
  int pipe_index = 0;
  int found_redir;
  int redirections;
  int redir_position[Size];
  strcpy(bin, "/bin/");
  int i = 0;

  while (1)
  {

    struct redirections red[1024];
    struct redirections_info red_info[3];
    pipes_redir p_r = malloc(sizeof(struct Pipes_redir));

    red[0].redir_pos_with_pipes = 0;
    red[1].redir_pos_with_pipes = 0;
    red[2].redir_pos_with_pipes = 0;

    pipe_index = 0; //this variable shows how many pipes we have
    index = 0;      //this variable count the words (pipes are not included)
    found_pipe = 0; //this variables tells us if the user inserted a pipe
    found_redir = 0;
    redirections = 0;

    print_prompt();

    int index = string_tokenizer(arg_list, pipe_position, &pipe_index, &found_pipe, &found_redir, &redirections, redir_position, red, red_info, all_args, p_r);

    //printf("pipe index is : %d\n",pipe_index);
    //intializing the pipes

    //printf("index is :%d\n",index);
    if (found_pipe == 1)
    {
      int fd;
      for (i = 0; i <= pipe_index; i++)
      {
        pipe(pipefiledisc[i]);
      }
      int tmp_index = 0;
      /*
      fprintf(stderr, "%s\n", p_r->symbols[tmp_index]);
      fprintf(stderr, "%s\n", p_r->symbols[tmp_index + 1]);
      fprintf(stderr, "%s\n", p_r->symbols[tmp_index + 2]);
      fprintf(stderr, "%s\n", p_r->symbols[tmp_index + 3]);
*/

      int found_redir = 0;
      int i = 0;
      for (i = 0; i <= pipe_index; i++) //for every pipe we found
      {
        pid = fork();
        if (pid == 0)
        {
          int red_read = 0;
          int red_write = 0;

          int counted_strings = create_pipe_arguments(arg_list, i, pipe_position, pipe_index, index, bin);

          //the arguments for the current pipe are on arg_list
          //check code

          int l;

          for (l = 0; l <= pipe_index; l++)
          {
            if ((l != i + 1) && (l != i))
            {
              close(pipefiledisc[l][0]);
              close(pipefiledisc[l][1]);
            }
          }

          if (p_r->symbols[i] != NULL && strcmp(p_r->symbols[i], "|") == 0)
          {
            // fprintf(stderr, "i is %d\n", i);
            // fprintf(stderr, "im in \n");
            red_read = 1;
            int tmp_index = i;
            if ((fd = open(red_info[1].last_file[0], O_RDONLY)) == -1)
            {
              //perror(args[idx + 1]);
              exit(EXIT_FAILURE);
            }
            dup2(fd, 0);
            close(fd);
            arg_list[counted_strings - 1] = NULL;

            while (p_r->symbols[tmp_index + 1] != NULL && strcmp(p_r->symbols[tmp_index + 1], ">") != 0 && strcmp(p_r->symbols[tmp_index + 1], "<") != 0)
            {

              if (strcmp(p_r->symbols[tmp_index + 1], "||") == 0)
              {
                //fprintf(stderr, "im in2 \n");

                red_write = 1;
                int fd2;
                if ((fd2 = creat(red_info[0].last_file[0], 0644)) == -1)
                {
                  exit(EXIT_FAILURE);
                }
                dup2(fd2, 1);
                close(fd2);
              }
              tmp_index++;
              arg_list[counted_strings - 2] = NULL;
            }
          }
          else if (p_r->symbols[i] != NULL && strcmp(p_r->symbols[i], "||") == 0)
          {
            //printf("inn\n");
            red_write = 1;
            int fd2;
            if ((fd2 = creat(red_info[0].last_file[0], 0644)) == -1)
            {
              exit(EXIT_FAILURE);
            }
            dup2(fd2, 1);
            close(fd2);
            arg_list[counted_strings - 1] = NULL;
            int tmp_index = i;

            while (p_r->symbols[tmp_index + 1] != NULL && strcmp(p_r->symbols[tmp_index + 1], ">") != 0 && strcmp(p_r->symbols[tmp_index + 1], "<") != 0)
            {
              // fprintf(stderr, "in too\n");
              red_read = 1;
              if ((fd = open(red_info[1].last_file[0], O_RDONLY)) == -1)
              {
                exit(EXIT_FAILURE);
              }
              dup2(fd, 0);
              close(fd);
              tmp_index++;
              arg_list[counted_strings - 2] = NULL;
            }
          }

          //fprintf(stderr, "aaa\n");

          if (i != pipe_index && red_write == 0)
          {
            if (dup2(pipefiledisc[i + 1][1], 1) < 0) //writes to
            {
              fprintf(stderr, "error in write \n");
            }
          }

          if (i > 0 && red_read == 0)
          {
            if (dup2(pipefiledisc[i][0], 0) < 0) //read's from
            {
              perror("dup2");
            }
          }

          /* fprintf(stderr, "arg1 is : %s\n", arg_list[0]);
          fprintf(stderr, "arg2 is : %s\n", arg_list[1]);
          fprintf(stderr, "arg3 is : %s\n", arg_list[2]);
*/
          execvp(arg_list[0], arg_list);

          perror("execve"); /* execve() returns only on error */
          int errcode = errno;
          exit(errcode);
        }
        else
        {

          //close filedisc

          //parent closes fildescriptors too

          close(pipefiledisc[i][0]);
          if (i != pipe_index)
          {
            close(pipefiledisc[i + 1][1]);
          }

          wait(NULL);
        }
      }
    }
    else if (found_redir == 1)
    {
      // fprintf(stderr, "in redir \n");

      if (red_info[0].multiple_redir == 1)
      {
        //fprintf(stderr, "in multple_redir \n");

        red_info[0].last_file[1] = NULL;
        red_info[1].last_file[1] = NULL;
        red_info[2].last_file[1] = NULL;

        //fprintf(stderr, "file is %s\n",red_info[2].last_file[0]);
        if (red_info[0].last_file[0] != NULL && red_info[1].last_file[0] != NULL && red_info[2].last_file[0] == NULL) //read write
        {
          // fprintf(stderr, "im in read write case\n");
          read_write_redirections(red_info);
        }
        else if (red_info[0].last_file[0] != NULL && red_info[2].last_file[0] != NULL && red_info[1].last_file[0] == NULL) //write at the end , write
        {
          write_write_end_redirections(red_info);
        }
        else if (red_info[1].last_file[0] != NULL && red_info[2].last_file[0] != NULL && red_info[0].last_file[0] == NULL) //read ,write at the end
        {
          //fprintf(stderr, "im in read write_end case\n");

          read_write_end_redirections(red_info);
        }
        else if (red_info[1].last_file[0] != NULL && red_info[2].last_file[0] != NULL && red_info[0].last_file[0] != NULL) //read ,write at the end , write
        {
          all_redirections(red_info);
        }
      }
      else
      {
        //fprintf(stderr, "im in simple redir case \n");
        //just one redirection
        if (red_info[0].last_file[0] != NULL) //write only
        {
          //fprintf(stderr, "only write\n");
          int fd;
          int index = 1;
          pid_t pid;
          pid = fork();
          if (pid == 0)
          {

            while (arg_list[index] != NULL)
            {
              if ((fd = creat(arg_list[index], 0644)) == -1)
              {
              }
              index++;
            }
            dup2(fd, 1);
            close(fd);
            if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
            {
              perror("execvp");
            }
          }
          else
          {
            wait(NULL);
          }
        }
        else if (red_info[1].last_file[0] != NULL) //read only
        {
          //fprintf(stderr, "only read\n");
          int fd;
          int index = 1;
          pid_t pid;
          pid = fork();
          if (pid == 0)
          {

            while (arg_list[index] != NULL)
            {
              /* fprintf(stderr, "files :\n");
              fprintf(stderr, "%s\n",arg_list[index]);
              fprintf(stderr,"last command is %s\n",red_info[0].last_command[0]);
            */
              if ((fd = open(arg_list[index], O_RDONLY)) == -1)
              {
                exit(EXIT_FAILURE);
              }
              index++;
            }
            dup2(fd, 0);
            close(fd);
            if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
            {
              perror("execvp");
            }
          }
          else
          {
            wait(NULL);
          }
        }

        else // write end only
        {
          // fprintf(stderr, "only write end \n");
          int fd2;
          int index = 1;
          pid_t pid;
          pid = fork();
          if (pid == 0)
          {

            while (arg_list[index] != NULL)
            {
              FILE *fp = fopen(arg_list[index], "a");
              fd2 = fileno(fp);

              index++;
            }
            dup2(fd2, 1);
            close(fd2);
            if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
            {
              perror("execvp");
            }
          }
          else
          {
            wait(NULL);
          }
        }
      }
    }

    else //case without pipes
    {

      if (strcmp(arg_list[0], "cd") == 0)
      {

        char dir_path[Size];

        strcpy(dir_path, arg_list[1]);
        chdir(dir_path);
      }
      else if (strcmp(arg_list[0], "exit") == 0)
      {
        kill(0, SIGKILL);
      }
      else//simple commands
      {
        pid = fork();

        if (pid == 0) //child run
        {

          execvp(arg_list[0], arg_list);
        }
        else //we are in parent
        {

          waitpid(-1, &status, 0);
        }
      }
    }
  }
}
void all_redirections(struct redirections_info red_info[])
{
  pid_t pid;
  int fd;
  int status;
  int fd_read;
  int j;
  /*
  for (j = 0; j <= red_info[0].index_commands; j++)
  {
    fprintf(stderr, "%s\n", red_info[0].last_command[j]);
  }*/

  pid = fork();
  if (pid == 0)
  {
    if (red_info[0].last_redir_pos > red_info[2].last_redir_pos)
    {
      //fprintf(stderr, " im in || \n");

      //      printf("write to || file \n");
      if ((fd = creat(red_info[0].last_file[0], 0644)) == -1)
      {
      }
      dup2(fd, 1);
      close(fd);
    }
    else
    {
      //fprintf(stderr, " im in |||\n ");

      FILE *fp = fopen(red_info[2].last_file[0], "a");
      int fd2 = fileno(fp);
      dup2(fd2, 1);
      close(fd2);
    }

    if ((fd_read = open(red_info[1].last_file[0], O_RDONLY)) == -1)
    {
      exit(EXIT_FAILURE);
    }
    dup2(fd_read, 0);
    close(fd_read);

    if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
    {
      perror("execvp");
    }
  }
  else
  {
    waitpid(-1, &status, 0);
  }
}

void read_write_redirections(struct redirections_info red_info[])
{
  pid_t pid;
  int fd;
  int status;
  //fprintf(stderr, " we have multiple redirections\n");
  //fprintf(stderr, "last command is :\n");
  int j;
  /*
  for (j = 0; j <= red_info[0].index_commands; j++)
  {
    fprintf(stderr, "%s\n", red_info[0].last_command[j]);
  }*/
  //fprintf(stderr, "last input file : %s\n", red_info[1].last_file[0]);
  //fprintf(stderr, "last output file : %s\n", red_info[0].last_file[0]);
  int fd2;
  pid = fork();
  if (pid == 0)
  {

    if ((fd = open(red_info[1].last_file[0], O_RDONLY)) == -1)
    {
      exit(EXIT_FAILURE);
    }
    if ((fd2 = creat(red_info[0].last_file[0], 0644)) == -1)
    {
      exit(EXIT_FAILURE);
    }
    dup2(fd, 0);
    dup2(fd2, 1);
    close(fd2);

    close(fd);

    if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
    {
      perror("execvp");
    }
  }
  else
  {
    waitpid(-1, &status, 0);
  }
}

void read_write_end_redirections(struct redirections_info red_info[])
{

  pid_t pid;
  int fd;
  int status;
  //fprintf(stderr, " we have multiple redirections\n");
  //fprintf(stderr, "last command is :\n");
  int j;
  /*for (j = 0; j <= red_info[0].index_commands; j++)
  {
    fprintf(stderr, "%s\n", red_info[0].last_command[j]);
  }
  fprintf(stderr, "last input file : %s\n", red_info[1].last_file[0]);
  fprintf(stderr, "last output file : %s\n", red_info[0].last_file[0]);
  */
  int fd2;
  pid = fork();
  if (pid == 0)
  {

    if ((fd = open(red_info[1].last_file[0], O_RDONLY)) == -1)
    {
      exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(red_info[2].last_file[0], "a");
    fd2 = fileno(fp);
    dup2(fd, 0);
    dup2(fd2, 1);
    close(fd);
    close(fd2);

    if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
    {
      perror("execvp");
    }
  }
  else
  {
    waitpid(-1, &status, 0);
  }
}

void write_write_end_redirections(struct redirections_info red_info[])
{
  pid_t pid;
  int fd;
  int status;
  int j;
  /*for (j = 0; j <= red_info[0].index_commands; j++)
  {
    fprintf(stderr, "%s\n", red_info[0].last_command[j]);
  }*/

  pid = fork();

  if (pid == 0)
  {
    if (red_info[0].last_redir_pos > red_info[2].last_redir_pos)
    {
      //fprintf(stderr, " im in || \n");

      if ((fd = creat(red_info[0].last_file[0], 0644)) == -1)
      {
      }
      dup2(fd, 1);
      close(fd);
    }
    else
    {
      //fprintf(stderr, " im in |||\n ");

      FILE *fp = fopen(red_info[2].last_file[0], "a");
      int fd2 = fileno(fp);
      dup2(fd2, 1);
      close(fd2);
    }

    if (execvp(red_info[0].last_command[0], red_info[0].last_command) == -1)
    {
      perror("execvp");
    }
  }
  else
  {
    waitpid(-1, &status, 0);
  }
}

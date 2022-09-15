#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char * copy_input(char *user_supplied_string) {
  int i, dst_index;
  char *dst_buf = (char*)malloc(4*sizeof(char) * MAX_SIZE);
  if ( MAX_SIZE <= strlen(user_supplied_string) ){
    exit(1);
  }
  dst_index = 0;
  for ( i = 0; i < strlen(user_supplied_string); i++ ){
    if( '&' == user_supplied_string[i] ){
      dst_buf[dst_index++] = '&';
      dst_buf[dst_index++] = 'a';
      dst_buf[dst_index++] = 'm';
      dst_buf[dst_index++] = 'p';
      dst_buf[dst_index++] = ';';
    }
    else if ('<' == user_supplied_string[i] ){
      dst_buf[dst_index++] = '&';
      dst_buf[dst_index++] = 'l';
      dst_buf[dst_index++] = 't';
    }
    else dst_buf[dst_index++] = user_supplied_string[i];
  }
  return dst_buf;
}

int main() {
  char buffer[100];
  printf("Please enter a string: ");
  scanf("%100s", buffer);
  printf("%s", copy_input(buffer));
}
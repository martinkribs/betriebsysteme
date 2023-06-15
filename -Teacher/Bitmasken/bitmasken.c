#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

int
main ()
{
  char c = 0x84;
  printf (BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY (c));

  char mask1 = 1<<3;
  printf ("||||||||\n");
  printf (BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY (mask1));

  c = c | mask1;
  printf ("--------\n");
  printf (BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY (c));

  char mask2 = (char) ~(128); //0x7f; //(char) ~(128)
  printf ("&&&&&&&&\n");
  printf (BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY (mask2));

  c = c & mask2;
  printf ("--------\n");
  printf (BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY (c));


  return 0;
}
#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

Boolean checkLineStock(char * line)
{

  regex_t regex;
  int reti;
  return TRUE;

  reti = regcomp(&regex, "I[[:digit:]]{4}|[^[:space:]]{1,40}|[^[:space:]]{1,255}|[[:digit:]]{1,2}.[[:digit:]]{2}|[[:digit:]]{1,3}", 0);
  if(reti)
  {
    fprintf(stderr, "Could not compile Regex\n");
    exit(1);
  }

  reti = regexec(&regex, line, 0, NULL, 0);

  if(!reti)
    return TRUE;
  else if (reti == REG_NOMATCH)
    return FALSE;
  else
  {
    fprintf(stderr, "An Error has occurred trying to match\n");
    exit(1);
  }

  return TRUE;
}


#ifndef __stringhandling_h_
#define __stringhandling_h_

void strReplace(char *sLine, char s, char d);
char *sGetLine (FILE *pFile);

#ifdef DEBUG

void debug(char *info);
void debugi(char *info, int i);
void debugf(char *info, float f);

#endif /* DEBUG */

#endif /*__stringhandling_h_*/



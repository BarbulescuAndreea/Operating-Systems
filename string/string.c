/* SPDX-License-Identifier: BSD-3-Clause */

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *copy = destination;
	while(*source != '\0'){
		*destination=*source;
		source+=1;
		destination+=1;
	}
	*destination = '\0';
	return copy;
}

char *strncpy(char *destination, const char *source, size_t len)
{ 
   size_t index = 0;
   char *copy = destination;
   while(index < len){
      index++;
      *destination++ = *source++;
   }
   return copy;
}

char *strcat(char *destination, const char *source)
{
	strcpy(destination+strlen(destination), source);
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
    char *copy = destination+strlen(destination);

    while(*source && len--)
        *copy++ = *source++;
 
    *copy = '\0';
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while((*str1 != '\0' && *str2 != '\0') && *str1 == *str2)
	{
		str1+=1;
		str2+=1;
	}
	
	return *str1 - *str2;
}


int strncmp(const char *str1, const char *str2, size_t len)
{
	while((*str1 != '\0' && *str2 != '\0') && *str1 == *str2 && len != 0)
        {
		len--;
		if(len != 0){
                	str1+=1;
                	str2+=1;
		}
        }
        return *str1 - *str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	while(*str != (char)c){
		if(*str++ == '\0')
			return NULL;
	}
	return (char*)str;
}

char *strrchr(const char *str, int c)
{
	/*ultima aparitie a lui c in str*/
	const char *lastAp = NULL;
	while(*str != '\0'){
		if(*str == (char)c)
			lastAp = str;
		*str++;
	}
	return (char*)lastAp;
}

char *strstr(const char *str1, const char *str2)
{
    while(*str1 != '\0') {
        if(strncmp(str1, str2, strlen(str2)) == 0)
            return (char*)str1;
        *str1++;
    }
	return NULL;
}

char *strrstr(const char *str1, const char *str2)
{
    const char *lastAp = NULL;
    while(*str1 != '\0') {
        if(strncmp(str1, str2, strlen(str2)) == 0)
            lastAp = str1;
        *str1++;
    }
	return (char*)lastAp;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	for(size_t i = 0; i < num; i++){
		((char *)destination)[i] = ((char *)source)[i];
	}
}

void *memmove(void *destination, const void *source, size_t num)
{
	uint8_t* start = (uint8_t*) source;
	uint8_t* to = (uint8_t*) destination;
	
	if(num == 0)
		return destination;

	if(start == to)
		return destination;
	
	if(to - start < (int)num && to > start) {
		int i = num - 1;
		while (i >= 0) {
			to[i] = start[i];
			i--;
		}
		return destination;
	}else if(start - to < (int)num && start > to){
		size_t i = 0;
		while (i < num) {
			to[i] = start[i];
			i++;
		}
		return destination;
	}
	memcpy(destination, source, num);
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *toString1 = ptr1, *toString2 = ptr2;
	while(num > 0){
		if(*toString1 != *toString2){
			if(*toString1 < *toString2){
				return -1;
			}else{
				return 1;
			}
			break;
		}
		toString1++;
		toString2++;
		num-=1;
	}
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	 unsigned char *helpPointer = source;
    for(size_t index = 0; index < num; index++) {
        helpPointer[index] = (unsigned char)value;
    }
    return source;
}

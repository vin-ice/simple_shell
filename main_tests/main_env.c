#include "test.h"

char *_strncpy(char *dest, char *src, int n)
{
	int byteCount;
	for (byteCount = 0; byteCount < n && src[byteCount] != '\0'; byteCount++)
		dest[byteCount] = src[byteCount];
	for (; byteCount < n; byteCount++)
		dest[byteCount] = '\0';
	return (dest);
}

char *_strcat(char *str1, char *str2)
{
    printf("====main_env.c->_strcat=====\n");
	int len, count, j;
	char *str;

	len = strlen(str1) + strlen(str2);
	str = malloc(sizeof (char) * len + 1);
	if (str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_strncpy(str, str1, strlen(str1));
    strcat(str, str2);
	return (str);
}
/**
 * main - driver function for tests on _env.c
 * Return - 0 or 1
 */
int main(void)
{      
    char *token, **paths, *path, cmd []={"ls"} ;

    *paths = _getenv("PATH");
    token = strtok(*paths, ":");
    for (;token != NULL;)
    {
        path = _strcat(token, "/");
        printf("%s\n", token);
        path = _strcat(path, cmd);
        printf("path: %s\n", path);
        token = strtok(NULL, ":");
    }
    free(*paths);
    return (0);
}
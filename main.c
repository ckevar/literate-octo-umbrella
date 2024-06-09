#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>

#define panic(emsg)	fprintf(stderr, "[ERROR]: " emsg);\
					return 1

enum {
	USER_PORT = 1,
	USER_LOG_FILE,
	USER_IN_COUNT,
};

int port;
void terminator(int sig) {
	close(port);
}

uint8_t main(int argc, char *argv[]) {
	FILE *fout;
	struct pollfd pfd;
	int ready;
	ssize_t	size;
	char buf[256];

	if(argc < USER_IN_COUNT) {
		panic("please specify the port\r\n");
	}
	signal(SIGINT, terminator);
	
	fout = fopen(argv[USER_LOG_FILE], "w+");
	if(fout == NULL) {
		panic("Couldn't open outputfile\r\n");
	}

	port = open(argv[USER_PORT], O_RDONLY);
	if(port == -1) {
		panic("Couldn't open port\r\n");
	}
	pfd.fd = port;
	pfd.events = POLLIN;

	while(1) {
		ready = poll(&pfd, 1, -1);

		if(ready == -1)
			break;

		if(pfd.revents & POLLIN) {
			size = read(pfd.fd, buf, sizeof(buf));
			if (size == -1)
				break;
			fprintf(stderr, "\tread %zd bytes\n", size);
			fprintf(fout, "%.*s", (int)size, buf);
		} else {
			if(close(pfd.fd) == -1) {
				panic("Error closing");
			}
		}
			
	}

	close(pfd.fd);
	panic("Polling error\r\n");

	return 0;
}

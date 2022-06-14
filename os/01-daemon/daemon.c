#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int lockfile(int fd) {
	struct flock fl;
	
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	return fcntl(fd, F_SETLK, &fl);
}

void err_quit(const char * str) {
	perror(str);
	exit(1);
}

void daemonize(const char *cmd) {
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	umask(0);

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
		err_quit("can't get rlimit");
	} 

	if ((pid = fork()) < 0) {
		err_quit("fork error");
	} else if (pid != 0) {
		exit(0);
	}
	setsid();

	if (chdir("/") < 0) {
		err_quit("can't chdir");
	}

	if (rl.rlim_max == RLIM_INFINITY) {
		rl.rlim_max = 1024;
	}
	for (i = 0; i < rl.rlim_max; ++i) {
		close(i);
	}

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "file in file descriptors");
	}
}

int already_running(void) {
	int fd; 
	char buf[16];

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if (fd < 0) {
		syslog(LOG_ERR, "can't open %s, %s", LOCKFILE, strerror(errno));
		exit(1);
	}

	if (lockfile(fd) < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			close(fd);
			return 1;
		}
		syslog(LOG_ERR, "can't set block on %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf) + 1);
	return 0;
}

int main() {
	daemonize("HEHE");
	if (already_running()) {
		syslog(LOG_ERR, "Daemon already running");
		return 0;
	}

	for (int i = 0; i < 20; ++i) {
		sleep(1);
		syslog(LOG_ERR, "DAEMON IS WRITING");
	}
	return 0;
}

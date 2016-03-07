// System call prototypes

#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#include "typedefs.h"

void  _exit(int _status				);
int   access(const char *_path, int _amode		);
uint  alarm(unsigned int _seconds		);
int   chdir(const char *_path			);
int   chown(const char *_path, uid_t _owner, gid_t _group);
int   close(int _fd				);
char* ctermid(char *_s				);
char* cuserid(char *_s				);
int   dup(int _fd					);
int   dup2(int _fd, int _fd2			);
int   execl(const char *_path, const char *_arg, ...);
int   execle(const char *_path, const char *_arg, ...);
int   execlp(const char *_file, const char *arg, ...);
int   execv(const char *_path, char *const _argv[]	);
int   execve(const char *_path, char *const _argv[], 
						char *const _envp[]);
int execvp(const char *_file, char *const _argv[]);
pid_t fork(void					);
long fpathconf(int _fd, int _name		);
char *getcwd(char *_buf, size_t _size		);
gid_t getegid(void				);
uid_t geteuid(void				);
gid_t getgid(void				);
int   getgroups(int _gidsetsize, gid_t _grouplist[]);
char* getlogin(void				);
pid_t getpgrp(void				);
pid_t getpid(void				);
pid_t getppid(void				);
uid_t getuid(void				);
int   isatty(int _fd				);
int   link(const char *_existing, const char *_new	);
off_t lseek(int _fd, off_t _offset, int _whence	);
long  pathconf(const char *_path, int _name	);
int   pause(void					);
int     pipe(int _fildes[2]				);
ssize_t read(int _fd, void *_buf, size_t _n	);
int     rmdir(const char *_path			);
int   setgid(gid_t _gid				);
int   setpgid(pid_t _pid, pid_t _pgid		);
pid_t setsid(void				);
int   setuid(uid_t _uid				);
uint  sleep(unsigned int _seconds		);
long  sysconf(int _name				);
pid_t tcgetpgrp(int _fd				);
int tcsetpgrp(int _fd, pid_t _pgrp_id		);
char *ttyname(int _fd				);
int unlink(const char *_path			);
ssize_t write(int _fd, const void *_buf, size_t _n);

int brk(char *_addr				);
int chroot(const char *_name			);
int mknod(const char *_name, mode_t _mode, dev_t _addr);
int mknod4(const char *_name, mode_t _mode, dev_t _addr,
	    long _size						);
char *mktemp(char *_template			);
int mount(char *_spec, char *_name, int _flag	);
long ptrace(int _req, pid_t _pid, long _addr, long _data);
char *sbrk(int _incr				);
int sync(void					);
int umount(const char *_name			);
int reboot(int _how, ...				);
int gethostname(char *_hostname, size_t _len	);
int getdomainname(char *_domain, size_t _len	);
int ttyslot(void					);
int fttyslot(int _fd				);
char *crypt(const char *_key, const char *_salt	);

#endif // _SYSCALLS_H

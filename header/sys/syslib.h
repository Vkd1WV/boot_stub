/* Prototypes for system library functions. */

#ifndef _SYSLIB_H
#define _SYSLIB_H

/* Minix user+system library. */
void printk   (char *_fmt   , ...                              );
int  sendrec  (int _src_dest, message *_m_ptr                  );
int  _taskcall(int _who     , int _syscallnr , message *_msgptr);

/* Minix system library. */
int _receive(int _src , message *_m_ptr);
int _send   (int _dest, message *_m_ptr);

int sys_abort (int _how, ...);
int sys_adjmap(
	int _proc, struct mem_map *_ptr,
	vir_clicks _data_clicks, vir_clicks _sp
);
int sys_copy(
	int _src_proc, int _src_seg, phys_bytes _src_vir, 
	int _dst_proc, int _dst_seg, phys_bytes _dst_vir,
	phys_bytes _bytes
);
int sys_exec(int _proc, char *_ptr, int _traced, char *_aout,vir_bytes _initpc);
int sys_execmap(int _proc, struct mem_map *_ptr   );
int sys_fork   (int _parent, int _child, int _pid, phys_clicks _shadow		);
int sys_fresh (
	int _proc, struct mem_map *_ptr,
	phys_clicks _dc, phys_clicks *_basep,
	phys_clicks *_sizep
);

int sys_getsp    (int _proc, vir_bytes *_newsp                            );
int sys_newmap   (int _proc, struct mem_map *_ptr                         );
int sys_getmap   (int _proc, struct mem_map *_ptr                         );
int sys_sendsig  (int _proc, struct sigmsg *_ptr                          );
int sys_oldsig   (int _proc, int _sig           , sighandler_t _sighandler);
int sys_endsig   (int _proc                                               );

int sys_sigreturn(int _proc, vir_bytes _scp, int _flags	);
int sys_trace    (int _req, int _procnr, long _addr, long *_data_p);
int sys_xit(
	int _parent, int _proc,
	phys_clicks *_basep, phys_clicks *_sizep
);
int sys_kill (int _proc, int _sig		);
int sys_times(int _proc, clock_t _ptr[5]);

#endif /* _SYSLIB_H */

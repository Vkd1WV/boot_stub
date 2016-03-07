/* Function prototypes. */

#ifndef PROTO_H
#define PROTO_H

/* Struct declarations. */
struct dpeth;
struct proc;
struct tty;

/* at_wini.c, bios_wini.c, esdi_wini.c, ps_wini.c, xt_wini.c, wini.c */
void winchester_task     (void			);
void at_winchester_task  (void			);
void bios_winchester_task(void			);
void esdi_winchester_task(void			);
void ps_winchester_task  (void			);
void xt_winchester_task  (void			);

/* aha_scsi.c */
void aha_scsi_task(void				);

/* clock.c */
void    clock_task   (void);
void    clock_stop   (void);
clock_t get_uptime   (void);
void    syn_alrm_task(void);

/* dmp.c */
void map_dmp(void				);
void p_dmp  (void				);
void reg_dmp(struct proc *rp	);

/* dp8390.c */
void dp8390_task(void				);
void dp_dump    (void				);
void dp8390_stop(void				);

/* main.c, stmain.c */
void main (void                );
void panic(const char *s, int n);

/* mcd.c */
void mcd_task(void				);

/* memory.c */
void mem_task(void				);

/* misc.c */
int env_parse(char *env, char *fmt, int field,
			long *param, long min, long max	);

/* printer.c, stprint.c */
void printer_task(void				);

/* proc.c */
void interrupt     (int task                                             );
int  lock_mini_send(struct proc *caller_ptr, int dest    , message *m_ptr);
void lock_pick_proc(void                                                 );
void lock_ready    (struct proc *rp                                      );
void lock_sched    (                   void                              );
void lock_unready  (struct proc *rp                                      );
int  sys_call      (int function           , int src_dest, message *m_ptr);
void unhold        (void                                                 );

/* rs232.c */
void rs_init(struct tty *tp			);

/* sb16_dsp.c */
void dsp_task(void				);

/* sb16_mixer.c */
void mixer_task(void				);

/* system.c */
void cause_sig(int proc_nr, int sig_nr		);
void inform(void					);
phys_bytes numap(int proc_nr, vir_bytes vir_addr, 
		vir_bytes bytes				);
void sys_task(void				);
phys_bytes umap(struct proc *rp, int seg, vir_bytes vir_addr,
		vir_bytes bytes				);

/* tty.c */
void handle_events(struct tty *tp		);
void sigchar(struct tty *tp, int sig		);
void tty_task(void				);
int in_process(struct tty *tp, char *buf, int count);
void out_process(struct tty *tp, char *bstart, char *bpos,
				char *bend, int *icount, int *ocount);
void tty_wakeup(clock_t now			);
void tty_reply(int code, int replyee, int proc_nr,
							int status);
void tty_devnop(struct tty *tp			);

/* library */
void *memcpy(void *_s1, const void *_s2, size_t _n);

#if (CHIP == INTEL)

/* clock.c */
void     milli_start  (struct milli_state *msp	);
unsigned milli_elapsed(struct milli_state *msp	);
void     milli_delay  (unsigned millisec		);

/* console.c */
void cons_stop(void				);
void putk(int c					);
void scr_init(struct tty *tp			);
void toggle_scroll(void				);
int  con_loadfont(phys_bytes user_phys		);
void select_console(int cons_line		);

/* cstart.c */
void cstart(
	uint16_t cs     , uint16_t ds,
	uint16_t mcs    , uint16_t mds,
	uint16_t parmoff, uint16_t parmsize
);
char* k_getenv(char *name			);

/* exception.c */
void exception(unsigned vec_nr			);

/* i8259.c */
irq_handler_t get_irq_handler(int irq		);
void put_irq_handler(int irq, irq_handler_t handler);
void intr_init(int mine				);

/* keyboard.c */
void kb_init(struct tty *tp			);
int kbd_loadmap(phys_bytes user_phys		);
void wreboot(int how				);

/* klib*.s */
void       bios13   (void                            );
phys_bytes check_mem(phys_bytes base, phys_bytes size);
void cp_mess(
	int src               , phys_clicks src_clicks,
	vir_bytes   src_offset, phys_clicks dst_clicks,
	vir_bytes   dst_offset
);
int   in_byte       (port_t port );
int   in_word       (port_t port );
void  lock          (void        );
void  unlock        (void        );
void  enable_irq    (unsigned irq);
int   disable_irq   (unsigned irq);
uint16_t mem_rdw       (segm_t segm, vir_bytes offset);
void out_byte       (port_t port, int value       );
void out_word       (port_t port, int value       );
void phys_copy      (phys_bytes source, phys_bytes dest, phys_bytes count    );
void port_read      (unsigned port, phys_bytes destination, unsigned bytcount);
void port_read_byte (unsigned port, phys_bytes destination, unsigned bytcount);
void port_write     (unsigned port, phys_bytes source, unsigned bytcount     );
void port_write_byte(unsigned port, phys_bytes source, unsigned bytcount     );
void reset          (void);
void vid_vid_copy   (unsigned src, unsigned dst, unsigned count);
void mem_vid_copy   (uint16_t *src  , unsigned dst, unsigned count);
void level0         (void (*func)(void) );
void monitor        (void               );

/* misc.c */
void mem_init(void);

/* mpx*.s */
void idle_task(void);
void restart  (void);

/* The following are never called from C (pure asm procs). */

/* Exception handlers (real or protected mode), in numerical order. */
void int00(void), divide_error         (void);
void int01(void), single_step_exception(void);
void int02(void), nmi                  (void);
void int03(void), breakpoint_exception (void);
void int04(void), overflow             (void);
void int05(void), bounds_check         (void);
void int06(void), inval_opcode         (void);
void int07(void), copr_not_available   (void);
void              double_fault         (void);
void              copr_seg_overrun     (void);
void              inval_tss            (void);
void              segment_not_present  (void);
void              stack_exception      (void);
void              general_protection   (void);
void              page_fault           (void);
void              copr_error           (void);

/* Hardware interrupt handlers. */
void hwint00(void);
void hwint01(void);
void hwint02(void);
void hwint03(void);
void hwint04(void);
void hwint05(void);
void hwint06(void);
void hwint07(void);
void hwint08(void);
void hwint09(void);
void hwint10(void);
void hwint11(void);
void hwint12(void);
void hwint13(void);
void hwint14(void);
void hwint15(void);

/* Software interrupt handlers, in numerical order. */
void trp        (void);
void s_call (void) , p_s_call (void );
void level0_call(void);

/* ne2000.c */
int ne_probe(struct dpeth *dep			);

/* printer.c */
void pr_restart(void				);

/* protect.c */
void prot_init(void				);
void init_codeseg(struct segdesc_s *segdp, phys_bytes base,
		phys_bytes size, int privilege			);
void init_dataseg(struct segdesc_s *segdp, phys_bytes base,
		phys_bytes size, int privilege			);
phys_bytes seg2phys(uint16_t seg			);
void enable_iop(struct proc *pp			);

/* pty.c */
void do_pty(struct tty *tp, message *m_ptr	);
void pty_init(struct tty *tp			);

/* system.c */
void alloc_segments(struct proc *rp		);

/* wdeth.c */
int wdeth_probe(struct dpeth *dep		);

#endif /* (CHIP == INTEL) */

#if (CHIP == M68000)

/* cstart.c */
void cstart(char *parmoff, size_t parmsize	);

/* stfloppy.c */
void fd_timer(void				);

/* stmain.c */
void none     (void                );
void rupt     (void                );
void trap     (void                );
void checksp  (void                );
void aciaint  (void                );
void fake_int (const char *s, int t);
void timint   (int t               );
void mdiint   (void                );
void iob      (int t               );
void idle_task(void                );

/* rs232.c */
void siaint(int type				);

/* stcon.c */
void func_key(void				);
void dump(void					);
void putk(int c					);

/* stdma.c */
void dmagrab(int p, dmaint_t func		);
void dmafree(int p				);
void dmaint (void					);
void dmaaddr(phys_bytes ad			);
int  dmardat(int mode, int delay			);
void dmawdat(int mode, int data, int delay	);
void dmawcmd(int data, unsigned mode		);
void dmacomm(int mode, int data, int delay	);
int  dmastat(int mode, int delay			);

/* stdskclk.c */
int do_xbms(phys_bytes address, int count, int rw, int minor) );
 
/* stkbd.c */
void kbdint(void					);
void kb_timer(void				);
int kb_read(int minor, char **bufindirect	);
void kb_init(int minor				);

/* stshadow.c */
void mkshadow(struct proc *p, phys_clicks c2	);
void rmshadow(struct proc *p, phys_clicks *basep,
		phys_clicks *sizep				);
void unshadow(struct proc *p			);
 
/* stvdu.c */
void flush(struct tty *tp			);
void console(struct tty *tp			);
void out_char(struct tty *tp, int c		);
void scr_init(int minor				);
void vduswitch(struct tty *tp			);
void vdusetup(unsigned int vres, char *vram,
			    unsigned short *vrgb		);
void vbl(void					);
int vdu_loadfont(message *m_ptr			);

/* stwini.c */
int wini_open(message *mp			);
int wini_rdwt(message *mp			);
int wini_hvrdwt(message *mp			);
int wini_transfer(int rw, int pnr, int minor,
		long pos, int count, vir_bytes vadr		);
int wini_ioctl(message *mp			);
int wini_close(message *mp			);

/* stacsi.c */
int acsi_cmd(int drive,  unsigned char *cmd, int cmdlen,
		phys_bytes address, phys_bytes data_len,  int rw);

/* stscsi.c */
void scsi_task(void				);
void scsidmaint(void				);
void scsiint(void				);
int scsi_cmd(int drive,  unsigned char *cmd, int cmdlen,
		phys_bytes address, phys_bytes data_len,  int rw);

/* klib68k.s */
void flipclicks(phys_clicks c1, phys_clicks c2, phys_clicks n) );
void copyclicks(phys_clicks src, phys_clicks dest,
		phys_clicks nclicks				);
void zeroclicks(phys_clicks dest, phys_clicks nclicks);
void phys_copy(phys_bytes src, phys_bytes dest, phys_bytes n) );

/* stdskclks.s */
int rd1byte(void					);
int wr1byte(int					);
long getsupra(void				);
long geticd(void					);

/* mpx.s */
int lock(void					);
void unlock(void					);
void restore(int oldsr				);
void reboot(void					);
int test_and_set(char *flag			);
unsigned long get_mem_size(char *start_addr	);

/* stprint.c */
#ifdef DEBOUT
void prtc(int c					);
#endif

#ifdef FPP
/* fpp.c */
void fppinit(void				);
void fpp_new_state(struct proc *rp		);
void fpp_save(struct proc *rp, struct cpu_state *p);
struct cpu_state  *fpp_restore(struct proc *rp	);

/* fpps.s */
void _fppsave(struct state_frame *p		);
void _fppsavereg(struct fpp_model *p		);
void _fpprestore(struct state_frame *p		);
void _fpprestreg(struct fpp_model *p		);
#endif

#if (SHADOWING == 0)
/* pmmu.c */
_PROTOTYPE(void pmmuinit (void				);
_PROTOTYPE(void pmmu_init_proc (struct proc *rp 		);
_PROTOTYPE(void pmmu_restore (struct proc *rp 		);
_PROTOTYPE(void pmmu_delete (struct proc *rp 		);
_PROTOTYPE(void pmmu_flush (struct proc *rp 			);
#endif

#endif /* (CHIP == M68000) */

#endif /* PROTO_H */

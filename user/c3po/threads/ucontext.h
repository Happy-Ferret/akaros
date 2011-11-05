#ifndef UCONTEXT_H
#define UCONTEXT_H

#include <stdint.h>
#include <ros/arch/trapframe.h>
#include <threadlib_internal.h>
struct u_context {
	struct user_trapframe utf;
    void *tls_desc;
	thread_t *thread;
}; 

struct u_context* create_context(thread_t *t, void *entry_pt, void *stack_top);
void save_context(struct u_context *uc);
void restore_context(struct u_context *uc);
void destroy_context(struct u_context *uc);
void print_context(struct u_context *uc);

#endif

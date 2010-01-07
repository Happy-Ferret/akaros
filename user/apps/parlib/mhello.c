#include <parlib.h>
#include <ros/mman.h>
#include <ros/resource.h>
#include <stdio.h>
#include <hart.h>

// ghetto udelay, put in a lib somewhere and export the tsc freq
#include <arch/arch.h>
void udelay(uint64_t usec, uint64_t tsc_freq)
{
	uint64_t start, end, now;

	start = read_tsc();
    end = start + (tsc_freq * usec) / 1000000;
	if (end == 0) printf("This is terribly wrong \n");
	do {
        cpu_relax();
        now = read_tsc();
	} while (now < end || (now > start && end < start));
	return;
}

__thread int temp;

int main(int argc, char** argv)
{

	uint32_t vcoreid;
	error_t retval;

	if ((vcoreid = hart_self())) {
		printf("Should never see me! (from vcore %d)\n", vcoreid);
	} else { // core 0
		temp = 0xdeadbeef;
		printf("Hello from vcore %d with temp addr = %p and temp = %p\n",
		       vcoreid, &temp, temp);
		printf("Multi-Goodbye, world, from PID: %d!\n", sys_getpid());
		//retval = sys_resource_req(RES_CORES, 2, 0);
		retval = hart_request(2);
		//debug("retval = %d\n", retval);
	}
	printf("Vcore %d Done!\n", vcoreid);
	while (1);
	return 0;
}

void hart_entry(void)
{
	uint32_t vcoreid = hart_self();
	temp = 0xcafebabe;
	printf("Hello from hart_entry in vcore %d with temp addr %p and temp %p\n",
	       vcoreid, &temp, temp);
	while(1);
}

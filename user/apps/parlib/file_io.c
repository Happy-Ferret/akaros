#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	printf("Welcome to the ROS newlib test suite!\nEnter at you're own risk....\n");

	printf("Size of stat struct: %u\n", sizeof(struct stat));

	int fd = open("./test/matrix", O_RDWR, 0);
	char buf[100];
	int read_amt = read(fd, buf, 100);
	printf("FD: %d\n", fd);
	printf("read_amt: %d\n", read_amt);
	printf("read: %s\n", buf);

	char buf2[] = "NANWAN!\n";

	int fd = open("./test/nanwan", O_RDWR | O_CREAT, 
	              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	
	lseek(fd, 0, SEEK_END);	

	int write_amt = write(fd, buf2, sizeof(buf2) -1);
        printf("write_amt: %d\n", write_amt);        
	printf("wrote: %s\n", buf2);

	unlink ("./test/nanwan_link");


	link("./test/nanwan", "./test/nanwan_link");
	unlink("./test/to_delete");


	return 0;
}

#include<linux/linkage.h>
#include<linux/time.h>
#include<linux/kernel.h>
#include<linux/unistd.h>
#include<linux/sched.h>


asmlinkage long sys_bernardo_pla (int pantherid)
{

	printk("sys_bernardo_pla called from process %ld with panther ID %ld.\n", current->pid, pantherid);
	
	/* Time System Call Code here*/
	struct timeval now;
	struct tm tm_val;
	
	do_gettimeofday(&now);
	time_to_tm(now.tv_sec, 0, &tm_val);

	printk("The current time is: %d:%d:%d %d/%d/%d", tm_val.tm_hour - 5, tm_val.tm_min, tm_val.tm_sec, tm_val.tm_mon + 1, tm_val.tm_mday, tm_val.tm_year + 1900);

	return 0;
}

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/errno.h>
#include<linux/uaccess.h>
#include<linux/types.h>


MODULE_LICENSE("GPL");

extern int wkey_queu[2];
extern int wkey_len;

int get_scan_code_from_buffer(int *scan_code)
{
	if(atomic_read(&wkey_len) == 1)
	{
		*scan_code = atomic_read(&wkey_queu[0]);
		atomic_dec(&wkey_len);
		return 1;
	}
	return 0;
}

int wkey_open(struct inode *p_inode, struct file *p_file)
{
	return 0;
}

ssize_t wkey_read(struct file *p_file, char *buff, size_t size,loff_t *off)
{
	int status;
	int scan_code;
	status = get_scan_code_from_buffer(&scan_code);
	if(status){
		status = copy_to_user(buff,(char*)&scan_code,sizeof(scan_code));
		if(status !=0){
			printk("[wkey_device]----> failed to copy to user\n");
			return -1;
		}
		return sizeof(scan_code);
	}
	return 0;
}

int wkey_close(struct inode *p_inode, struct file *p_file)
{
	return 0;
}

struct file_operations wkey_op={
	open:wkey_open,
	read:wkey_read,
	release:wkey_close,
};

int wkey_init(void)
{
	printk("Hello world\n");
	if(register_chrdev(224,"wkey_dev",&wkey_op)!=0)
		printk("failed to register wkey\n");
	return 0;
}

void wkey_exit(void)
{
	unregister_chrdev(224,"wkey_dev") ;
	printk("Bye world\n");
}

module_init(wkey_init);
module_exit(wkey_exit);


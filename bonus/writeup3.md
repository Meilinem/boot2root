# Boot exploit

During boot, we can press `shift` to access the bios, it brings up the boot menu in
single-user mode which allow us to choose a boot mode and pass `init=/bin/bash` as
kernel parameters.


### Step 1:
- Hold shift during boot

### Step 2:
- Live init=/bin/bash


```
root@BornToSecHackMe:/# id    
uid=0(root) gid=0(root) groups=0(root)
```

Docs:

https://wiki.archlinux.org/index.php/Reset_lost_root_password

https://askubuntu.com/questions/92556/how-do-i-boot-into-a-root-shell

https://www.vultr.com/docs/reset-the-root-password-on-debian

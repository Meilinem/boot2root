void	sig_handler(int sig)
{
	printf("So you think you can stop the bomb with ctr-c, do you?\n");
	sleep(3);
	printf("Well...");
	fflush(stdout);
	sleep(1);
	printf("OK. :-)\n");
	exit(10);
}

void	initialize_bomb(void)
{
	signal(2, sig_handler);
}

uint32_t phase_defused (void) {
    int32_t var_68h;
    int32_t var_54h;
    int32_t var_50h;
    if (*(obj.num_input_strings) == 6) {
        ebx = ebp - 0x50;
        eax = sscanf (0x804b770, "%d %s", ebp - 0x54);
        if (eax == 2) {
            eax = strings_not_equal (ebx, "austinpowers");
            if (eax != 0) {
                goto label_0;
            }
            printf ("Curses, you've found the secret phase!\n");
            printf ("But finding it and solving it are quite different...\n");
            secret_phase ();
        }
label_0:
        printf ("Congratulations! You've defused the bomb!\n");
    }
    ebx = *((ebp - 0x68));
    return eax;
}

uint32_t read_six_numbers (int32_t arg_8h, int32_t arg_ch) {
    ecx = *((ebp + 8));
    edx = *((ebp + 0xc));
    eax = edx + 0x14;
    eax = edx + 0x10;
    eax = edx + 0xc;
    eax = edx + 8;
    eax = edx + 4;
    eax = sscanf (ecx, "%d %d %d %d %d %d", edx);
    if (eax <= 5) {
        explode_bomb ();
    }
    return eax;
}

uint32_t phase_2 (int32_t arg_8h) {
    int32_t var_28h;
    uint32_t var_18h;
    edx = *((ebp + 8));
    read_six_numbers (edx, ebp - 0x18);
    if (*((ebp - 0x18)) != 1) {
        explode_bomb ();
    }
    ebx = 1;
    esi = ebp - 0x18;
    do {
        eax = ebx + 1;
        eax *= *((esi + ebx*4 - 4));
        if (*((esi + ebx*4)) != eax) {
            explode_bomb ();
        }
        ebx++;
    } while (ebx <= 5);
    esp = ebp - 0x28;
    return eax;
}


uint32_t phase_3 (int32_t arg_8h) {
    int32_t var_18h;
    uint32_t var_ch;
    uint32_t var_5h;
    uint32_t var_4h;
    edx = *((ebp + 8));
    eax = ebp - 4;
    eax = ebp - 5;
    eax = sscanf (edx, "%d %c %d", ebp - 0xc);
    if (eax <= 2) {
        explode_bomb ();
    }
    if (*((ebp - 0xc)) <= 7) {
        eax = *((ebp - 0xc));
        /* switch table (8 cases) at 0x80497e8 */
        bl = 0x71;
        if (*((ebp - 4)) == 0x309) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x62;
        if (*((ebp - 4)) == 0xd6) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x62;
        if (*((ebp - 4)) == 0x2f3) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x6b;
        if (*((ebp - 4)) == 0xfb) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x6f;
        if (*((ebp - 4)) == 0xa0) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x74;
        if (*((ebp - 4)) == 0x1ca) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x76;
        if (*((ebp - 4)) == 0x30c) {
            goto label_0;
        }
        explode_bomb ();
        bl = 0x62;
        if (*((ebp - 4)) == 0x20c) {
            goto label_0;
        }
        explode_bomb ();
    }
    bl = 0x78;
    explode_bomb ();
label_0:
    if (bl != *((ebp - 5))) {
        explode_bomb ();
    }
    ebx = *((ebp - 0x18));
    return eax;
}

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
    eax += esi;
    goto label_2;
label_1:
    eax = 1;
label_2:
    esp = ebp - 0x18;
    return eax;
}

uint32_t phase_4 (char * s) {
    int32_t var_4h;
    edx = *((ebp + 8));
    eax = sscanf (edx, 0x8049808, ebp - 4);
    if (eax == 1) {
        if (*((ebp - 4)) > 0) {
            goto label_0;
        }
    }
    explode_bomb ();
label_0:
    eax = *((ebp - 4));
    eax = func4 (eax);
    if (eax != 0x37) {
        explode_bomb ();
    }
    return eax;
}

uint32_t phase_5 (int32_t arg_8h) {
    int32_t var_18h;
    int32_t var_8h;
    int32_t var_2h;
    ebx = *((ebp + 8));
    eax = string_length (ebx);
    if (eax != 6) {
        explode_bomb ();
    }
    edx = 0;
    ecx = ebp - 8;
    esi = "isrveawhobpnutfg";
    do {
        al = *((edx + ebx));
        al &= 0xf;
        eax = (int32_t) al;
        al = *((eax + esi));
        *((edx + ecx)) = al;
        edx++;
    } while (edx <= 5);
    *((ebp - 2)) = 0;
    eax = strings_not_equal (ebp - 8, "giants");
    if (eax != 0) {
        explode_bomb ();
    }
    esp = ebp - 0x18;
    return eax;
}

uint32_t phase_6 (int32_t arg_8h) {
    int32_t var_58h;
    int32_t var_3ch;
    int32_t var_38h;
    int32_t var_34h;
    int32_t var_30h;
    int32_t var_18h;
    edx = *((ebp + 8));
    *((ebp - 0x34)) = 0x804b26c;
    read_six_numbers (edx, ebp - 0x18);
    edi = 0;
label_0:
    eax = ebp - 0x18;
    eax = *((eax + edi*4));
    eax--;
    if (eax > 5) {
        explode_bomb ();
    }
    ebx = edi + 1;
    if (ebx > 5) {
        goto label_2;
    }
    eax = edi*4;
    *((ebp - 0x38)) = eax;
    esi = ebp - 0x18;
    do {
        edx = *((ebp - 0x38));
        eax = *((edx + esi));
        if (eax == *((esi + ebx*4))) {
            explode_bomb ();
        }
        ebx++;
    } while (ebx <= 5);
label_2:
    edi++;
    if (edi <= 5) {
        goto label_0;
    }
    edi = 0;
    ecx = ebp - 0x18;
    eax = ebp - 0x30;
    *((ebp - 0x3c)) = eax;
label_1:
    esi = *((ebp - 0x34));
    ebx = 1;
    eax = edi*4;
    edx = eax;
    if (ebx >= *((eax + ecx))) {
        goto label_3;
    }
    eax = *((edx + ecx));
    do {
        esi = *((esi + 8));
        ebx++;
    } while (ebx < eax);
label_3:
    edx = *((ebp - 0x3c));
    *((edx + edi*4)) = esi;
    edi++;
    if (edi <= 5) {
        goto label_1;
    }
    esi = *((ebp - 0x30));
    *((ebp - 0x34)) = esi;
    edi = 1;
    edx = ebp - 0x30;
    do {
        eax = *((edx + edi*4));
        *((esi + 8)) = eax;
        esi = eax;
        edi++;
    } while (edi <= 5);
    *((esi + 8)) = 0;
    esi = *((ebp - 0x34));
    edi = 0;
    do {
        edx = *((esi + 8));
        eax = *(esi);
        if (eax < *(edx)) {
            explode_bomb ();
        }
        esi = *((esi + 8));
        edi++;
    } while (edi <= 4);
    esp = ebp - 0x58;
    return eax;
}

uint32_t read_line (void) {
    int32_t var_18h;
    eax = skip (edi);
    if (eax == 0) {
        eax = infile;
        if (eax != *(obj.stdin)) {
            eax = getenv ("GRADE_BOMB");
            if (eax != 0) {
                exit (0);
            }
            eax = stdin;
            *(obj.infile) = eax;
            eax = skip ();
            if (eax != 0) {
                goto label_0;
            }
        }
        printf ("Error: Premature EOF on stdin\n");
        explode_bomb ();
    }
label_0:
    eax = num_input_strings;
    eax *= 5;
    eax <<= 4;
    edi = eax + obj_input_strings;
    al = 0;
    ecx = 0xffffffff;
    __asm ("repne scasb al, byte es:[edi]");
    eax = ecx;
    eax = ~eax;
    edi = eax - 1;
    if (edi == 0x4f) {
        printf ("Error: Input line too long\n");
        explode_bomb ();
    }
    eax = num_input_strings;
    eax *= 5;
    eax <<= 4;
    *((edi + eax + 0x804b67f)) = 0;
    eax += obj.input_strings;
    *(obj.num_input_strings)++;
    edi = *((ebp - 0x18));
    return eax;
}


int main(int ac, char **av)
{
	if (ac == 1)
		infile = stdin;
	else if (ac == 2)
	{
		infile = fopen(av[1], "r");
		if (infile == 0)
		{
			printf("%s: Error: Couldn't open %s\n", av[0], av[1]); 
			exit(8);
		}
	}
	else
	{
		printf("%s: Error: Couldn't open %s\n", av[0], av[1]); 
		exit(8);
	}
	initialize_bomb();
	printf("Welcome this is my little bomb !!!! You have 6 stages with\n");
	printf("only one life good luck !! Have a nice day!\n");
	// adc esp, 0x20 ??
	read_line();
	phase_1();
	phase_defused();
	printf("Phase 1 defused. How about the next one?\n");
	read_line();
	phase_2();
	phase_defused();
	printf("That's number 2. Keep going!\n");
	read_line();
	phase_3();
	printf("Halfway there!\n");
	phase_defused();
	read_line();
	phase_4();
	phase_defused();
	printf("So you got that one. Try this one.\n");
	read_line();
	phase_5();
	phase_defused();
	printf("Good work!  On to the next...\n");
	phase_6();
	phase_defused();
	return (0);
}

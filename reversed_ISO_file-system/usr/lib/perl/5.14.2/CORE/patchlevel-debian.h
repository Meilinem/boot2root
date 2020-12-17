	,"DEBPKG:debian/arm_thread_stress_timeout - http://bugs.debian.org/501970 Raise the timeout of ext/threads/shared/t/stress.t to accommodate slower build hosts"
	,"DEBPKG:debian/cpan_definstalldirs - Provide a sensible INSTALLDIRS default for modules installed from CPAN."
	,"DEBPKG:debian/db_file_ver - http://bugs.debian.org/340047 Remove overly restrictive DB_File version check."
	,"DEBPKG:debian/doc_info - Replace generic man(1) instructions with Debian-specific information."
	,"DEBPKG:debian/enc2xs_inc - http://bugs.debian.org/290336 Tweak enc2xs to follow symlinks and ignore missing @INC directories."
	,"DEBPKG:debian/errno_ver - http://bugs.debian.org/343351 Remove Errno version check due to upgrade problems with long-running processes."
	,"DEBPKG:debian/libperl_embed_doc - http://bugs.debian.org/186778 Note that libperl-dev package is required for embedded linking"
	,"DEBPKG:fixes/respect_umask - Respect umask during installation"
	,"DEBPKG:debian/writable_site_dirs - Set umask approproately for site install directories"
	,"DEBPKG:debian/extutils_set_libperl_path - EU:MM: Set location of libperl.a to /usr/lib"
	,"DEBPKG:debian/no_packlist_perllocal - Don't install .packlist or perllocal.pod for perl or vendor"
	,"DEBPKG:debian/prefix_changes - Fiddle with *PREFIX and variables written to the makefile"
	,"DEBPKG:debian/fakeroot - Postpone LD_LIBRARY_PATH evaluation to the binary targets."
	,"DEBPKG:debian/instmodsh_doc - Debian policy doesn't install .packlist files for core or vendor."
	,"DEBPKG:debian/ld_run_path - Remove standard libs from LD_RUN_PATH as per Debian policy."
	,"DEBPKG:debian/libnet_config_path - Set location of libnet.cfg to /etc/perl/Net as /usr may not be writable."
	,"DEBPKG:debian/m68k_thread_stress - http://bugs.debian.org/517938 http://bugs.debian.org/495826 Disable some threads tests on m68k for now due to missing TLS."
	,"DEBPKG:debian/mod_paths - Tweak @INC ordering for Debian"
	,"DEBPKG:debian/module_build_man_extensions - http://bugs.debian.org/479460 Adjust Module::Build manual page extensions for the Debian Perl policy"
	,"DEBPKG:debian/prune_libs - http://bugs.debian.org/128355 Prune the list of libraries wanted to what we actually need."
	,"DEBPKG:fixes/net_smtp_docs - [rt.cpan.org #36038] http://bugs.debian.org/100195 Document the Net::SMTP 'Port' option"
	,"DEBPKG:debian/perlivp - http://bugs.debian.org/510895 Make perlivp skip include directories in /usr/local"
	,"DEBPKG:debian/disable-zlib-bundling - Disable zlib bundling in Compress::Raw::Zlib"
	,"DEBPKG:debian/cpanplus_definstalldirs - http://bugs.debian.org/533707 Configure CPANPLUS to use the site directories by default."
	,"DEBPKG:debian/cpanplus_config_path - Save local versions of CPANPLUS::Config::System into /etc/perl."
	,"DEBPKG:debian/deprecate-with-apt - http://bugs.debian.org/580034 Point users to Debian packages of deprecated core modules"
	,"DEBPKG:fixes/hurd-ccflags - [a190e64] http://bugs.debian.org/587901 [perl #92244] Make hints/gnu.sh append to $ccflags rather than overriding them"
	,"DEBPKG:debian/squelch-locale-warnings - http://bugs.debian.org/508764 Squelch locale warnings in Debian package maintainer scripts"
	,"DEBPKG:debian/skip-upstream-git-tests - Skip tests specific to the upstream Git repository"
	,"DEBPKG:fixes/extutils-cbuilder-cflags - [011e8fb] http://bugs.debian.org/624460 [perl #89478] Append CFLAGS and LDFLAGS to their Config.pm counterparts in EU::CBuilder"
	,"DEBPKG:fixes/module-build-home-directory - http://bugs.debian.org/624850 [rt.cpan.org #67893] Fix failing tilde test when run under a UID without a passwd entry"
	,"DEBPKG:debian/patchlevel - http://bugs.debian.org/567489 List packaged patches for 5.14.2-6ubuntu2.4 in patchlevel.h"
	,"DEBPKG:fixes/h2ph-multiarch - [e7ec705] http://bugs.debian.org/625808 [perl #90122] Make h2ph correctly search gcc include directories"
	,"DEBPKG:fixes/index-tainting - [3b36395] http://bugs.debian.org/291450 [perl #64804] RT 64804: tainting with index() of a constant"
	,"DEBPKG:debian/skip-kfreebsd-crash - http://bugs.debian.org/628493 [perl #96272] Skip a crashing test case in t/op/threads.t on GNU/kFreeBSD"
	,"DEBPKG:fixes/document_makemaker_ccflags - http://bugs.debian.org/628522 [rt.cpan.org #68613] Document that CCFLAGS should include $Config{ccflags}"
	,"DEBPKG:fixes/sys-syslog-socket-timeout-kfreebsd.patch - http://bugs.debian.org/627821 [rt.cpan.org #69997] Use a socket timeout on GNU/kFreeBSD to catch ICMP port unreachable messages"
	,"DEBPKG:fixes/hurd-hints - http://bugs.debian.org/636609 Improve general GNU hints, needed for GNU/Hurd."
	,"DEBPKG:fixes/pod_fixes - [7698aed] http://bugs.debian.org/637816 Fix typos in several pod/perl*.pod files"
	,"DEBPKG:debian/find_html2text - http://bugs.debian.org/640479 Configure CPAN::Distribution with correct name of html2text"
	,"DEBPKG:fixes/digest_eval_hole - http://bugs.debian.org/644108 Close the eval \"require $module\" security hole in Digest->new($algorithm)"
	,"DEBPKG:fixes/hurd-ndbm - [f0d0a20] [perl #102680] http://bugs.debian.org/645989 Add GNU/Hurd hints for NDBM_File"
	,"DEBPKG:fixes/sysconf.t-posix - [8040185] [perl #102888] http://bugs.debian.org/646016 Fix hang in ext/POSIX/t/sysconf.t on GNU/Hurd"
	,"DEBPKG:fixes/hurd-largefile - [1fda587] [perl #103014] http://bugs.debian.org/645790 enable LFS on GNU/Hurd"
	,"DEBPKG:debian/hurd_test_todo_syslog - http://bugs.debian.org/650093 Disable failing GNU/Hurd tests in cpan/Sys-Syslog/t/syslog.t"
	,"DEBPKG:fixes/hurd_skip_itimer_virtual - [rt.cpan.org #72754] http://bugs.debian.org/650094 Skip interval timer tests in Time::HiRes on GNU/Hurd"
	,"DEBPKG:debian/hurd_test_skip_socketpair - http://bugs.debian.org/650186 Disable failing GNU/Hurd tests ext/Socket/t/socketpair.t"
	,"DEBPKG:debian/hurd_test_skip_sigdispatch - http://bugs.debian.org/650188 Disable failing GNU/Hurd tests op/sigdispatch.t"
	,"DEBPKG:debian/hurd_test_skip_stack - http://bugs.debian.org/650175 Disable failing GNU/Hurd tests dist/threads/t/stack.t"
	,"DEBPKG:debian/hurd_test_skip_recv - http://bugs.debian.org/650095 Disable failing GNU/Hurd tests cpan/autodie/t/recv.t"
	,"DEBPKG:debian/hurd_test_skip_libc - http://bugs.debian.org/650097 Disable failing GNU/Hurd tests dist/threads/t/libc.t"
	,"DEBPKG:debian/hurd_test_skip_pipe - http://bugs.debian.org/650187 Disable failing GNU/Hurd tests io/pipe.t"
	,"DEBPKG:debian/hurd_test_skip_io_pipe - http://bugs.debian.org/650096 Disable failing GNU/Hurd tests dist/IO/t/io_pipe.t"
	,"DEBPKG:fixes/CVE-2012-5195 - avoid calling memset with a negative count"
	,"DEBPKG:fixes/CVE-2012-5526 - [PATCH 1/4] CR escaping for P3P header"
	,"DEBPKG:CVE-2013-1667.patch - [PATCH] Prevent premature hsplit() calls, and only trigger REHASH after hsplit()"
	,"DEBPKG:CVE-2012-6329.patch - http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=695224 [1735f6f] fix arbitrary command execution via _compile function in Maketext.pm"

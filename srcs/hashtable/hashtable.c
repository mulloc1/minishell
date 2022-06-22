#include "hashtable.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

//int main(void)
//{
//    t_hashtable *table;
//    
//    table = hashtable_create();
//    hashtable_insert(table, ft_strdup("TERM_SESSION_ID"), ft_strdup("w0t0p1:7735EF5A-5EA6-4538-BBD4-77AF7C43E104"));
//    hashtable_remove(table, "TERM_SESSION_ID");
//    printf("%s=%s\n", "TERM_SESSION_ID", hashtable_search(table, "TERM_SESSION_ID"));
//
//    hashtable_insert(table, ft_strdup("SSH_AUTH_SOCK"), ft_strdup("/private/tmp/com.apple.launchd.zJLa4Mxc5h/Listeners"));
//    hashtable_remove(table, "SSH_AUTH_SOCK");
//    printf("%s=%s\n", "SSH_AUTH_SOCK", hashtable_search(table, "SSH_AUTH_SOCK"));
//    
//    hashtable_insert(table, ft_strdup("LC_TERMINAL_VERSION"), ft_strdup("3.3.7"));
//    hashtable_remove(table, "LC_TERMINAL_VERSION");
//    printf("%s=%s\n", "LC_TERMINAL_VERSION", hashtable_search(table, "LC_TERMINAL_VERSION"));
//    
//    hashtable_insert(table, ft_strdup("COLORFGBG"), ft_strdup("7;0"));
//    hashtable_remove(table, "COLORFGBG");
//    printf("%s=%s\n", "COLORFGBG", hashtable_search(table, "COLORFGBG"));
//
//    hashtable_insert(table, ft_strdup("ITERM_PROFILE"), ft_strdup("Default"));
//    hashtable_remove(table, "ITERM_PROFILE");
//    printf("%s=%s\n", "ITERM_PROFILE", hashtable_search(table, "ITERM_PROFILE"));
//
//    hashtable_insert(table, ft_strdup("XPC_FLAGS"), ft_strdup("0x0"));
//    hashtable_remove(table, "XPC_FLAGS");
//    printf("%s=%s\n", "XPC_FLAGS", hashtable_search(table, "XPC_FLAGS"));
//
//    hashtable_insert(table, ft_strdup("LANG"), ft_strdup("en_US.UTF-8"));
//    hashtable_remove(table, "LANG");
//    printf("%s=%s\n", "LANG", hashtable_search(table, "LANG"));
//
//    hashtable_insert(table, ft_strdup("PWD"), ft_strdup("/Users/jaebae/backup/srcs/hashtable"));
//    hashtable_remove(table, "PWD");
//    printf("%s=%s\n", "PWD", hashtable_search(table, "PWD"));
//
//    hashtable_insert(table, ft_strdup("SHELL"), ft_strdup("/bin/zsh"));
//    hashtable_remove(table, "SHELL");
//    printf("%s=%s\n", "SHELL", hashtable_search(table, "SHELL"));
//
//    hashtable_insert(table, ft_strdup("SECURITYSESSIONID"), ft_strdup("186a5"));
//    hashtable_remove(table, "SECURITYSESSIONID");
//    printf("%s=%s\n", "SECURITYSESSIONID", hashtable_search(table, "SECURITYSESSIONID"));
//
//    hashtable_insert(table, ft_strdup("TERM_PROGRAM_VERSION"), ft_strdup("3.3.7"));
//    hashtable_remove(table, "TERM_PROGRAM_VERSION");
//    printf("%s=%s\n", "TERM_PROGRAM_VERSION", hashtable_search(table, "TERM_PROGRAM_VERSION"));
//
//    hashtable_insert(table, ft_strdup("TERM_PROGRAM"), ft_strdup("iTerm.app"));
//    hashtable_remove(table, "TERM_PROGRAM");
//    printf("%s=%s\n", "TERM_PROGRAM", hashtable_search(table, "TERM_PROGRAM"));
//
//    hashtable_insert(table, ft_strdup("PATH"), ft_strdup("/Users/jaebae/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"));
//    hashtable_remove(table, "PATH");
//    printf("%s=%s\n", "PATH", hashtable_search(table, "PATH"));
//
//    hashtable_insert(table, ft_strdup("LC_TERMINAL"), ft_strdup("iTerm2"));
//    hashtable_remove(table, "LC_TERMINAL");
//    printf("%s=%s\n", "LC_TERMINAL", hashtable_search(table, "LC_TERMINAL"));
//
//    hashtable_insert(table, ft_strdup("COLORTERM"), ft_strdup("truecolor"));
//    hashtable_remove(table, "COLORTERM");
//    printf("%s=%s\n", "COLORTERM", hashtable_search(table, "COLORTERM"));
//
//    hashtable_insert(table, ft_strdup("COMMAND_MODE"), ft_strdup("unix2003"));
//    hashtable_remove(table, "COMMAND_MODE");
//    printf("%s=%s\n", "COMMAND_MODE", hashtable_search(table, "COMMAND_MODE"));
//
//    hashtable_insert(table, ft_strdup("TERM"), ft_strdup("xterm-256color"));
//    hashtable_remove(table, "TERM");
//    printf("%s=%s\n", "TERM", hashtable_search(table, "TERM"));
//
//    hashtable_insert(table, ft_strdup("HOME"), ft_strdup("/Users/jaebae"));
//    hashtable_remove(table, "HOME");
//    printf("%s=%s\n", "HOME", hashtable_search(table, "HOME"));
//
//    hashtable_insert(table, ft_strdup("TMPDIR"), ft_strdup("/var/folders/zz/zyxvpxvq6csfxvn_n000cmx800357_/T/"));
//    hashtable_remove(table, "TMPDIR");
//    printf("%s=%s\n", "TMPDIR", hashtable_search(table, "TMPDIR"));
//
//    hashtable_insert(table, ft_strdup("USER"), ft_strdup("jaebae"));
//    hashtable_remove(table, "USER");
//    printf("%s=%s\n", "USER", hashtable_search(table, "USER"));
//
//    hashtable_insert(table, ft_strdup("XPC_SERVICE_NAME"), ft_strdup("0"));
//    hashtable_remove(table, "XPC_SERVICE_NAME");
//    printf("%s=%s\n", "XPC_SERVICE_NAME", hashtable_search(table, "XPC_SERVICE_NAME"));
//
//    hashtable_insert(table, ft_strdup("LOGNAME"), ft_strdup("jaebae"));
//    hashtable_remove(table, "LOGNAME");
//    printf("%s=%s\n", "LOGNAME", hashtable_search(table, "LOGNAME"));
//
//    hashtable_insert(table, ft_strdup("LaunchInstanceID"), ft_strdup("22CDBC20-D0D3-46C3-A342-EFBD04400400"));
//    hashtable_remove(table, "LaunchInstanceID");
//    printf("%s=%s\n", "LaunchInstanceID", hashtable_search(table, "LaunchInstanceID"));
//
//    hashtable_insert(table, ft_strdup("__CF_USER_TEXT_ENCODING"), ft_strdup("0x194EA:0x3:0x33"));
//    hashtable_remove(table, "__CF_USER_TEXT_ENCODING");
//    printf("%s=%s\n", "__CF_USER_TEXT_ENCODING", hashtable_search(table, "__CF_USER_TEXT_ENCODING"));
//
//    hashtable_insert(table, ft_strdup("ITERM_SESSION_ID"), ft_strdup("w0t0p4:1F2523D7-AE1D-4066-9D90-6223A946F9BF"));
//    hashtable_remove(table, "ITERM_SESSION_ID");
//    printf("%s=%s\n", "ITERM_SESSION_ID", hashtable_search(table, "ITERM_SESSION_ID"));
//
//    hashtable_insert(table, ft_strdup("SHLVL"), ft_strdup("1"));
//    hashtable_remove(table, "SHLVL");
//    printf("%s=%s\n", "SHLVL", hashtable_search(table, "SHLVL"));
//
//    hashtable_insert(table, ft_strdup("OLDPWD"), ft_strdup("/Users/jaebae/backup"));
//    hashtable_remove(table, "OLDPWD");
//    printf("%s=%s\n", "OLDPWD", hashtable_search(table, "OLDPWD"));
//
//    hashtable_insert(table, ft_strdup("MAIL"), ft_strdup("jaebae@student.42seoul.kr"));
//    hashtable_remove(table, "MAIL");
//    printf("%s=%s\n", "MAIL", hashtable_search(table, "MAIL"));
//
//    hashtable_insert(table, ft_strdup("_"), ft_strdup("/usr/bin/env"));
//    hashtable_remove(table, "_");
//    hashtable_remove(table, "_");
//    printf("%s=%s\n", "_", hashtable_search(table, "_"));
//
//    return (0);
//}
//
////int main(void)
////{
////    for (int i = 100; i < 101; i++)
////    {
////        printf("=================================================== %d\n", i);
////        printf("%s : %llu\n", "SECURITYSESSIONID", hashcode_making("SECURITYSESSIONID") % i);
////        printf("%s : %llu\n", "USER", hashcode_making("USER") % i);
////        printf("%s : %llu\n", "COMMAND_MODE", hashcode_making("COMMAND_MODE") % i);
////        printf("%s : %llu\n", "PATH", hashcode_making("PATH") % i);
////        printf("%s : %llu\n", "HOME", hashcode_making("HOME") % i);
////        printf("%s : %llu\n", "SHELL", hashcode_making("SHELL") % i);
////        printf("%s : %llu\n", "LaunchInstanceID", hashcode_making("LaunchInstanceID") % i);
////        printf("%s : %llu\n", "__CF_USER_TEXT_ENCODING", hashcode_making("__CF_USER_TEXT_ENCODING") % i);
////        printf("%s : %llu\n", "XPC_SERVICE_NAME", hashcode_making("XPC_SERVICE_NAME") % i);
////        printf("%s : %llu\n", "SSH_AUTH_SOCK", hashcode_making("SSH_AUTH_SOCK") % i);
////        printf("%s : %llu\n", "XPC_FLAGS", hashcode_making("XPC_FLAGS") % i);
////        printf("%s : %llu\n", "LOGNAME", hashcode_making("LOGNAME") % i);
////        printf("%s : %llu\n", "TMPDIR", hashcode_making("TMPDIR") % i);
////        printf("%s : %llu\n", "PWD", hashcode_making("PWD") % i);
////        printf("%s : %llu\n", "ITERM_PROFILE", hashcode_making("ITERM_PROFILE") % i);
////        printf("%s : %llu\n", "MAIL", hashcode_making("MAIL") % i);
////        printf("%s : %llu\n", "LANG", hashcode_making("LANG") % i);
////        printf("%s : %llu\n", "LC_TERMINAL_VERSION", hashcode_making("LC_TERMINAL_VERSION") % i);
////        printf("%s : %llu\n", "TERM", hashcode_making("TERM") % i);
////        printf("%s : %llu\n", "SHLVL", hashcode_making("SHLVL") % i);
////        printf("%s : %llu\n", "TERM_PROGRAM_VERSION", hashcode_making("TERM_PROGRAM_VERSION") % i);
////        printf("%s : %llu\n", "TERM_SESSION_ID", hashcode_making("TERM_SESSION_ID") % i);
////        printf("%s : %llu\n", "COLORTERM", hashcode_making("COLORTERM") % i);
////        printf("%s : %llu\n", "OLDPWD", hashcode_making("OLDPWD") % i);
////        printf("%s : %llu\n", "ITERM_SESSION_ID", hashcode_making("ITERM_SESSION_ID") % i);
////        printf("%s : %llu\n", "LC_TERMINAL", hashcode_making("LC_TERMINAL") % i);
////        printf("%s : %llu\n", "TERM_PROGRAM", hashcode_making("TERM_PROGRAM") % i);
////        printf("%s : %llu\n", "COLORFGBG", hashcode_making("COLORFGBG") % i);
////        printf("%s : %llu\n", "_", hashcode_making("_") % i);
////        printf("===================================================\n");
////    }
////    printf("%s\n", getenv("PATH"));
////}

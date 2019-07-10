#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <asm/types.h>
#include <sys/socket.h>  
#include <linux/netlink.h>

char *mmcblk[4] = {
    "mmcblk0p1",
    "mmcblk0p2",
    "mmcblk0p3",
    "mmcblk0p4",
    };


void MonitorNetlinkUevent()
{
    int sockfd;
    struct sockaddr_nl sa;
    int len;
    char buf[4096];
    struct iovec iov;
    struct msghdr msg;
    int i;

    memset(&sa,0,sizeof(sa));
    sa.nl_family=AF_NETLINK;
    sa.nl_groups=NETLINK_KOBJECT_UEVENT;
    sa.nl_pid = 0;//getpid(); both is ok
    memset(&msg,0,sizeof(msg));
    iov.iov_base=(void *)buf;
    iov.iov_len=sizeof(buf);
    msg.msg_name=(void *)&sa;
    msg.msg_namelen=sizeof(sa);
    msg.msg_iov=&iov;
    msg.msg_iovlen=1;

    sockfd=socket(AF_NETLINK,SOCK_RAW,NETLINK_KOBJECT_UEVENT);
    if(sockfd==-1)
        printf("socket creating failed:%s\n",strerror(errno));
    if(bind(sockfd,(struct sockaddr *)&sa,sizeof(sa))==-1)
        printf("bind error:%s\n",strerror(errno));


    while(1)
    {
        len=recvmsg(sockfd,&msg,0);
        if(len<0)
            printf("receive error\n");
        else if(len<32||len>sizeof(buf))
            printf("invalid message");
        for(i=0;i<len;i++)
        {
            if(*(buf+i)=='\0')
                buf[i]='\n';
        }
        printf("received %d bytes\n%s\n",len,buf);
    }
}



int startWith(const char *first, const char *secnd)
{
    size_t len_f = strlen(first);
    size_t len_s = strlen(secnd);
    return len_f > len_s ? false : strncmp(first, secnd, len_f) == 0;
}


char * findString(const char *string)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (strstr(string, mmcblk[i]))
            return mmcblk[i];
    }
    return 0;
}


int main(int argc,char **argv)
{
    // MonitorNetlinkUevent();
    char f[] = "add@";
    char s[] = "add@/devices/platform/fe320000.dwmmc/mmc_host/mmc0/mmc0:aaaa/block/mmcblk0/mmcblk0p4ACTION=addDEVPATH=/devices/platform/fe320000.dwmmc/mmc_host/mmc0/mmc0:aaaa/block/mmcblk0";

    // startWith(f, s);

    char *p = findString(s);
    if (p)
        printf("%s\n", p);

    return 0;
}

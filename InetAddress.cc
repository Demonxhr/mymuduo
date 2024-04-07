#include "InetAddress.h"

#include <string.h>

#include <iostream>

InetAdress::InetAdress(uint16_t port,std::string ip)
{
    bzero(&addr_,sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

std::string InetAdress::toIp() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET,&addr_.sin_addr,buf,sizeof buf);
    return buf;
}
std::string InetAdress::toIpPort() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET,&addr_.sin_addr,buf,sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf+end,":%u",port);    //%u 无符号10进制整数
    return buf;
}
uint16_t InetAdress::toPort() const
{
    return ntohs(addr_.sin_port);
}

int main()
{
    InetAdress addr(8080);
    std::cout << addr.toIpPort() << std::endl;
}
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
 
#include <iostream>
#include <sstream>
 
using namespace std;
 
int main()
{
    //加载SSL错误信息 
    SSL_load_error_strings();
    //添加SSL的加密/HASH算法 
    SSLeay_add_ssl_algorithms();
    //客户端，服务端选择SSLv23_server_method() 
    const SSL_METHOD *meth = SSLv23_client_method();
    //建立新的SSL上下文 
    SSL_CTX* ctx = SSL_CTX_new(meth);
    if(ctx == NULL)
    {
        ERR_print_errors_fp(stderr);
        cout<<"SSL_CTX_new error !";
        return -1;
    }

    int client = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(client == -1)
    {
        cout<<"socket error !";
        return -1;
    }
	
    string host = "www.baidu.com";
    uint16_t port = 443;

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET, "182.61.200.7", &sin.sin_addr);

    if(connect(client,(sockaddr*)&sin,sizeof(sin)) == -1)
    {
        cout<<"connect error 1";
        return -1;
    }

    //建立SSL 
    int ret;
    SSL*ssl = SSL_new(ctx);
    if(ssl == NULL)
    {
        cout<<"SSL NEW error";
        return -1;
    }
    //将SSL与TCP SOCKET 连接 
    SSL_set_fd(ssl,client);
    //SSL连接 
    ret = SSL_connect(ssl);
    if(ret == -1)
    {
        cout<<"SSL ACCEPT error ";
        return -1;
    }

    stringstream stream;
    stream << "GET https://"<<host<<" HTTP/1.0\r\n";
    stream << "Accept: */*\r\n";
    //stream << "Accept-Encoding: gzip, deflate, br\r\n";//不要编码，否则还得多一个解码的步骤
    stream << "Accept-Language: zh-Hans-CN, zh-Hans; q=0.8, en-US; q=0.5, en; q=0.3\r\n";
    stream << "Connection: Keep-Alive\r\n";
    stream << "Host: " << host << "\r\n";
    stream << "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36 Edge/17.17134\r\n";
    stream << "\r\n";

    string s = stream.str();
    const char *sendData = s.c_str();
    ret = SSL_write(ssl,sendData,strlen(sendData));
    if(ret == -1)
    {
        cout<<"SSL write error !";
        return -1;
    }
    char *rec = new char[1024*1024];
    int start = 0;
    while((ret = SSL_read(ssl,rec+start,1024))>0)
    {
        start += ret;
    }
    rec[start] = 0;
    cout<<rec;

    //关闭SSL套接字 
    SSL_shutdown(ssl);
    //释放SSL套接字 
    SSL_free(ssl);
    //释放SSL会话环境 
    SSL_CTX_free(ctx);

    close(client);
    return 0;
}


/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "csapp.h"

int main(int argc, char **argv) 
{
    int clientfd, port;
    char *host, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    /*while (Fgets(buf, MAXLINE, stdin) != NULL) {
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }*/
    FILE *fp = fopen("images.png","rb");
        if(fp==NULL)
        {
            printf("File open error");
            return 1;   
        }  

    // fseek(fp, 0, SEEK_END);
    // int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //sending image file
    while(1)
    {
        /* First read file in chunks of 256 bytes */
        //printf("%d\n",size );
        unsigned char buff[256];

        int nread = fread(buff,1,256,fp);
        printf("File read :%d bytes\n", nread);        

        /* If read was success, send data. */
        if(nread > 0)
        {
            //printf("Sending \n");
            write(clientfd, buff, nread);
        }

        /*
         * There is something tricky going on with read .. 
         * Either there was error, or we reached end of file.
         */
        if (nread < (256))
        {
            if (feof(fp))
                printf("End of file\n");
            if (ferror(fp))
                printf("Error reading\n");
            break;
        }


    }

    //receive file from server
    int bytesReceived = 0; 
    char recvBuff[256]; 

    



    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */

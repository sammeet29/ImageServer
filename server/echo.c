/*
 * echo - read and echo text lines until client closes connection
 */
/* $begin echo */
#include "csapp.h"
char imageRcvd = 1;

void echo(int connfd) 
{
    size_t n;
    int bytesReceived = 0; 
    char recvBuff[256]; 
    // rio_t rio;

 //    Rio_readinitb(&rio, connfd);
 //    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
	// printf("server received %d bytes\n", (int)n);
	// Rio_writen(connfd, buf, n);
 //    }
    FILE *fp;
    fp = fopen("image.png", "wb");

    if(NULL == fp)
    {
        printf("Error opening file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(connfd, recvBuff, 256)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
        
    }

    

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

    if (bytesReceived < 256)
    {
        if (feof(fp)){
            printf("End of file\n");
        	printf("File Receive completed\n");
        	imageRcvd =2;
        }
        // if (ferror(fp))
        //     printf("Error reading\n");
    }

    fclose(fp);


	


}
/* $end echo */


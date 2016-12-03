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
    rio_t rio;

    Rio_readinitb(&rio, connfd);
 //    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
	// printf("server received %d bytes\n", (int)n);
	// Rio_writen(connfd, buf, n);
 //    }
    int rx_fsize;
    Rio_readnb(&rio,&rx_fsize,sizeof(rx_fsize));
    //rx_fsize = atoi(recvBuff);
    printf("Size of file %d\n",rx_fsize );

    FILE *fp;
    fp = fopen("image.png", "wb");

    if(NULL == fp)
    {
        printf("Error opening file");
        return;
    }

    // fseek(fp, 0, SEEK_END);
    // int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int recData = 256;

    /* Receive data in chunks of 256 bytes untill rx_fsize data is received*/
    // while((bytesReceived = read(connfd, recvBuff, 256)) > 0)
    while(((bytesReceived = Rio_readnb(&rio,recvBuff,recData))>0) && rx_fsize>0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
        rx_fsize -= bytesReceived;
        printf("remaining bytes :%d\n",rx_fsize);
        if (rx_fsize<256)	//if remaining bytes is less than 256, read only remaining bytes of data
        	recData = rx_fsize;
    }

    fclose(fp);
    printf("File received\n");

    /****************************Send file back to client************************/

    
    FILE *fp2;
    fp2 = fopen("image.png", "rb");

    if(NULL == fp2)
    {
        printf("Error opening file");
        return;
    }

    fseek(fp2, 0, SEEK_END);
    int tx_size = ftell(fp2);
    printf("tx_size = %d\n",tx_size);
    fseek(fp2, 0, SEEK_SET);

    //send the size of image
    Rio_writen(connfd, &tx_size, sizeof(tx_size));

    fseek(fp2, 0, SEEK_SET);

    //sending back image file to client
    while(1)
    {
        /* First read file in chunks of 256 bytes */
        //printf("%d\n",size );
        unsigned char buff[256];

        int nread = fread(buff,1,256,fp2);
        printf("File read :%d bytes\n", nread);        

        /* If read was success, send data. */
        if(nread > 0)
        {
            printf("Sending back\n");
            
            Rio_writen(connfd, buff, nread);
        }

        /*
         * There is something tricky going on with read .. 
         * Either there was error, or we reached end of file.
         */
        if (nread < (256))
        {
            if (feof(fp2))
                printf("End of file\n");
            if (ferror(fp2))
                printf("Error reading\n");
            break;
        }

        
    }
    fclose(fp2);


    // if(bytesReceived < 0)
    // {
    //     printf("\n Read Error \n");
    // }

    // if (bytesReceived < 256)
    // {
    // 	printf("bytesReceived<256\n");
    //     if (feof(fp)){
    //         printf("End of file\n");
    //     // 	printf("File Receive completed\n");
    //     // 	//imageRcvd =2;
    //     }
    //     if (ferror(fp))
    //         printf("Error reading\n");
    // }


}
/* $end echo */


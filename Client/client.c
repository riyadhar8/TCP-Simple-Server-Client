#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h> 
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

char *reverse_string(char *string1) {
    
    int len = strlen(string1);

    int left = 0;
    int right = len - 1;
    
    for(int i = left; i < right; i++) {
        char tmp = string1[i];
        string1[i] = string1[right];
        string1[right] = tmp;
        right--;
    }

    return string1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Please enter both the IP Address and the Port Number.\n");
        printf("Client Exiting.\n");
        exit(1);
    }

    printf("Client Entering.\n");

    char *ip = argv[1];
    printf("IP Address of Server: %s\n", ip);

    int port = atoi(argv[2]);
    printf("Port Number of Server: %d\n", port);

    struct sockaddr_in servaddr;
    int sockfd;
    int connectfd;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("----- Error in creating a Socket.\n");
        exit(2);
    } else {
        printf("----- Socket created successfully.\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("----- Failed to Connect.\n");
        exit(3);
    } else {
        printf("----- Connected to Server.\n");
    }

    char sndLine[1024];
    memset(sndLine, 0, 1024);
    
    printf("Enter the line that has to be sent: ");
    fgets(sndLine, 1024, stdin);

    for(int i=0; i<1024; i++) {
        if (sndLine[i]=='\n') {
            sndLine[i] = '\0';
            break;
        }
    }

    //printf("%s", sndLine);

    if (write(sockfd, sndLine, strlen(sndLine)) < 0) {
        printf("----- Error while Sending to Server.\n");
        exit(4);
    } else {
        printf("----- Successfully sent to Server. Waiting for response.\n");
    }

    char recLine[1024];
    memset(recLine, 0, 1024);

    if (read(sockfd, recLine, 1024) < 1) {
        printf("----- Error in Receiving from Server.\n");
        exit(5);
    } else {
        printf("----- Line received, printing in reverse:\n");
        printf("%s\n", reverse_string(recLine));
    }

    printf("Client Exiting! Bye.\n");

    return 0;

}
#ifdef TEST
#define FNAME "test/hosts"
#elif PROD
#define FNAME "/etc/hosts"
#endif
#define MAX_TLD 63

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

    char tld[MAX_TLD];
    char* host;
    char* ip;
    switch (argc) {
        case 3:
            int append = 0;
            host = argv[1];
            ip = argv[2];
            break;
        case 4:
            if (argv[1] == "-a") {
                int append = 1;
                host = argv[2];
                ip = argv[3];
            } else {
                goto badargs;
            }
            break;
        default:
            goto badargs;
    }

    char* tldidx = strchr(host, '.');
    if (!tldidx) {
        fprintf(stderr, "please include a fully qualified domain name\n");
        goto badargs;
    }
    strncpy(tld, tldidx, MAX_TLD);
    char* new = (char*)malloc(strlen(host) + strlen(ip) + 3);
    sprintf(new, "%s\t%s\n", host, ip);

    FILE* hosts = fopen(FNAME, "r+");
    if (!hosts) {
        fprintf(stderr, "file open failed\n");
        exit(1);
    }
    fseek(hosts, 0L, SEEK_END);
    int size = ftell(hosts) + sizeof(argv[1]) + sizeof(argv[2]) + 3;
    fseek(hosts, 0L, SEEK_SET);

    char* in = (char*)malloc(size);
    char* out = (char*)malloc(size);
    while (fgets(in, size - strlen(out), hosts)) {
        if (!strstr(in, tld) && strlen(in)) {
            strcat(out, in);
        }
        memset(in, 0, size);
    }
    strcat(out, new);

    fseek(hosts, 0L, SEEK_SET);
    ftruncate(fileno(hosts), 0);
    fflush(hosts);
    fputs(out, hosts);

    free(in);
    free(out);
    fclose(hosts);
    exit(0);

badargs:
    fprintf(stderr, "usage: hosts-update HOSTNAME IP\n");
    exit(1);
}

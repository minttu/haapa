#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "result.h"
#include "exec.h"

int _exec(char *cmd, Result *res) {
    int pipefd[2];
    if(pipe(pipefd)<0)
        return -1;
    pid_t pid = fork();
    if(pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        dup2(pipefd[1], 2);
        close(pipefd[1]);
        execl("/bin/sh", "/bin/sh/", "-c", cmd, NULL);
        /* exec failed */
        exit(127);
    }
    else {
        close(pipefd[1]);
        res->string[read(pipefd[0],res->string, sizeof(res->string))] = 0;
        close(pipefd[0]);
        return 0;
    }
    /* never reached */
    return 0;
}

Result *exec(char *cmd) {
    int val;
    Result *res = init_res();
    val = _exec(cmd, res);
    res->error = val;
    return res;
}

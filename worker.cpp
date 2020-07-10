#include <iostream>
#include <unistd.h>
#include <zmq.h>

int main()
{
    std::cout << "Job worker" << std::endl;

    void *ctx = zmq_ctx_new();
    void *worker_pull = zmq_socket(ctx, ZMQ_PULL); // creates a pull socket
    zmq_connect(worker_pull, "tcp://localhost:5565");
    void *worker_push = zmq_socket(ctx, ZMQ_PUSH);
    zmq_connect(worker_push, "tcp://localhost:5566");

    for (;;)
    {
        char buffer[4] = {0}; // 0 - 100 + '\0'
        zmq_recv(worker_pull, buffer, 4, 0);
        int ms = std::stoi(buffer);

        std::cout << "Sleeping for " << ms
                  << "microseconds." << std::endl;

        usleep(ms * 1000);

        zmq_send(worker_push, "job done", 8, 0);
    }

    return 0;
}

#include <iostream>
#include <unistd.h>
#include <zmq.h>
#include <ctime>
#include <chrono>

int main()
{
    std::cout << "Job output" << std::endl;

    void *ctx = zmq_ctx_new(); // create context
    void *output = zmq_socket(ctx, ZMQ_PULL); // create pull socket
    zmq_bind(output, "tcp://*:5566");

    // recv signal to indicate that jobs are coming
    char job[10] = {0};
    zmq_recv(output, job, 10, 0);
    auto start = std::chrono::system_clock::now();
    int jobs = std::stoi(job);
    for (int i = 0; i < jobs; ++i)
    {
        char buffer[10] = {0};
        zmq_recv(output, buffer, 10, 0);

        std::cout << buffer << std::endl;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Actual elapsed time (ms): "
              << elapsed.count() * 1000
              << std::endl;

    getchar();

    return 0;
}



#include <iostream>
#include <unistd.h>
#include <zmq.h>
#include <time.h>

int main()
{
    std::cout << "Job dispatcher" << std::endl;

    void *ctx = zmq_ctx_new(); // create context
    void *dispatcher = zmq_socket(ctx, ZMQ_PUSH); // creates a push socket
    zmq_bind(dispatcher, "tcp://*:5565"); // bind it
    void *output = zmq_socket(ctx, ZMQ_PUSH);
    zmq_connect(output, "tcp://localhost:5566");

    std::cout << "Press enter once all workers are ready.";
    getchar();

    int jobs = 100;
    // send signal to output that N jobs are coming
    std::string job = std::to_string(jobs);
    zmq_send(output, job.c_str(), job.length(), 0);

    int task = 0;
    int total_time = 0;
    srand(time(0));
    for (int i = 0; i < jobs; ++i)
    {
        std::string msg;
        int ms = rand() % 100;
        total_time += ms;
        msg = std::to_string(ms);

        zmq_send(dispatcher, msg.c_str(), msg.length(), 0);
    }

    std::cout << "Expected time it takes to complete the jobs (ms): "
              << total_time
              << std::endl;

    getchar();

    return 0;
}



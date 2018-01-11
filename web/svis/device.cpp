/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>
#include <ctime>
#include <chrono>
#include <thread>

#include <string>
#include <cmath>

#define log_printf(fmt, args...) do { \
    fprintf(stderr, "%s:%d, " fmt "\n", __FUNCTION__, __LINE__, ##args); \
} while (0)

using namespace std::chrono_literals;
//using namespace std::literals::chrono_literals;

using namespace std;

uint16_t TCP_PORT = 5000;

int client_fd;
int socket_fd;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int startServer()
{
    struct sockaddr_in serv_addr;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        throw runtime_error("socket() failed");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(TCP_PORT);

    if (::bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        throw runtime_error("bind() failed");
    }

    listen(socket_fd,5);
    log_printf("server started at port %d", TCP_PORT);

    return 0;
}

int waitForConnection()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_fd = accept(socket_fd, (struct sockaddr *) &client_addr,
                       &client_addr_len);
    if (client_fd < 0) {
        throw runtime_error("accept() failed");
    }
    log_printf("client connected.");
    return 0;
}

struct sample
{
    float v[3];
    uint64_t timestamp;
};

string get_json(sample s)
{
    string json = "{";
    json += "\"v\": [";
    for (int i=0; i<3; i++) {
        json += to_string(s.v[i]);
        if (i < 2) {
            json += ", ";
        } else {
            json += "], ";
        }
    }
    json += "\"timestamp\": " + to_string(s.timestamp);
    json += "}";
    return json;
}

void send_data(const string& str)
{
    int rc;
    log_printf("%s", str.c_str());

    rc = write(client_fd, (str + "\n").c_str(), str.size()+1);
    if (rc < 0) {
        log_printf("ERROR in write() rc = %d", rc);
    }
}

int main(int argc, char *argv[])
{
    char buffer[256];
    int n;
    int rc;

    log_printf("hello");

    startServer();

    waitForConnection();

    sample s = {
        .v = {0, 0, 0},
        .timestamp = 123455577
    };

    float update_rate = 60;

    for (int i=0; i<10000; i++) {

        s.v[1] += 0.1;

        send_data(get_json(s));

        std::this_thread::sleep_for(chrono::duration<float>(1/update_rate));
    }
    log_printf("closing server");
done:
    close(client_fd);
    close(socket_fd);
    return 0;
}

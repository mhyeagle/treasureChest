#include <iostream>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <sys/socket.h>
#include <string>
#include <string.h>

using namespace std;

void eventcb(struct bufferevent *bev, short events, void *ptr) {
    if (events & BEV_EVENT_CONNECTED) {
        //start reading
        cout << "we should start reading or writing here." << endl;
    } else if (events & BEV_EVENT_ERROR) {
        cout << "an error occured while connect." << endl;
    }
}

int main() {
    struct event_base *base;
    struct bufferevent *bev;
    struct sockaddr_in sin;

    base = event_base_new();

    memset(&sin, 0, sizeof(sin));
    sin.sin_addr.s_addr = htonl(0x7f000001);
    sin.sin_port = htons(8080);

    bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, NULL, NULL, eventcb, NULL);

    if (bufferevent_socket_connect(bev, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        //Error starting connection
        bufferevent_free(bev);
        return -1;
    }

    event_base_dispatch(base);

    return 0;
}

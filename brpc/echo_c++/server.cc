// Author: Miao,Hongyuan
// Date: Fri Jan  5 14:50:49 CST 2018
// brpc server demo

#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>
#include "echo.pb.h"

using namespace std;

DEFINE_int32(port, 8000, "");
DEFINE_bool(echo_attachment, true, "");
DEFINE_int32(idle_timeout_s, -1, "");
DEFINE_int32(logoff_ms, 2000, "");

namespace example {
class EchoServerImpl : public EchoService {
public:
    EchoServerImpl() {};
    virtual ~EchoServerImpl() {};
    virtual void Echo(google::protobuf::RpcController* cntl_base,
                        const EchoRequest* request,
                        EchoResponse* response, 
                        google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);

        brpc::Controller* cntl = 
            static_cast<brpc::Controller*>(cntl_base);

        cout << "request log id: " << cntl->log_id() << endl;
        cout << "remote side: " << cntl->remote_side() << endl;
        cout << "local side: " << cntl->local_side() << endl;
        cout << "request message: " << request->message() << endl;
        if (!cntl->request_attachment().empty()) {
            cout << "request attachment: " << cntl->request_attachment() << endl;
        }

        response->set_message(request->message());

        if (FLAGS_echo_attachment) {
            cntl->response_attachment().append(cntl->request_attachment());
        }
    }
};
} // namespace example

int main(int argc, char** argv) {
    google::ParseCommandLineFlags(&argc, &argv, true);

    brpc::Server server;

    example::EchoServerImpl echo_server_impl;

    if (server.AddService(&echo_server_impl, 
                          brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        cerr << "failed to add service." << endl;
        return -1;
    }

    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(FLAGS_port, &options) != 0) {
        cerr << "failed to start server." << endl;
        return -1;
    }

    server.RunUntilAskedToQuit();

    return 0;
}


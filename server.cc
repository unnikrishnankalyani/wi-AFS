#include <string>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <iostream>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <grpcpp/grpcpp.h>
#include "afs.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using afs::AFS;
using afs::CreateReq;
using afs::CreateRes;


class AfsServiceImplementation final : public AFS:: Service{
    Status afs_CREATE(
        ServerContext* context,
        const CreateReq* request,
        CreateRes* reply
    ) override { //returns a status by default
        std::string server_path;
        translatePath(request->path(),server_path)
        int fd = open(server_path, O_CREAT, S_IRWXU | S_IRWXG); // fixing flags and modes for create
        if(fd == -1){
            reply->set_ack(-1);
        }
        else{
            reply->set_ack(1);
            close(fd);
        }
        return Status::OK;
    }
};

void RunAfsServer(std::string ipadd) {
    //create port on localhost 5000
    std::string address(ipadd+":5000");
    AfsServiceImplementation service;

    ServerBuilder afsServer; //server name

    afsServer.AddListeningPort(address, grpc::InsecureServerCredentials());
    afsServer.RegisterService(&service);

    std::unique_ptr<Server> server(afsServer.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}


int main(int argc, char** argv) {
    std::string ipadd = "0.0.0.0";

    RunAfsServer(ipadd);
    
    return 0;
}
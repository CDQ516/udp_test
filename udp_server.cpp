//g++ -g udp_server.cpp -o udp_server -lboost_system
//
 
#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
 
using namespace std;
using namespace boost::asio;
 
int main(){
    try{
        cout << "udp server start ......" << endl;
        io_service ios;
 
        ip::udp::socket sock(ios, ip::udp::endpoint(ip::udp::v4(), 6699));
		int cnt = 0;
        while(true){
            char buf[1];
            ip::udp::endpoint ep;
            boost::system::error_code ec;
            sock.receive_from(buffer(buf), ep, 0, ec);
			cout << "recv from " << ep.address() << endl;
            if(ec && ec!=error::message_size){
                throw boost::system::system_error(ec);
            }
			
            cout << "send to " << ep.address() << endl;
			vector<vector<float>> pos = {{M_PI / 2.0, 0, 0, 0.75, 0, 0.3}, {M_PI / 2.0, 0, 0, 0, 0, 0.5}, {M_PI / 2.0, 0, M_PI / 2.0, 0, 0.5, 0.25}};
            sock.send_to(buffer(pos[cnt++]), ep);
			cnt = cnt > 2 ? 2 : cnt;
        }
    }
    catch(std::exception& e){
        cout << e.what() << endl;
    }
    return 0;
}

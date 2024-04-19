#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
 
using namespace std;
using namespace boost::asio;
 
int main(){
    try{
        cout << "udp client start ......" << endl;
        io_service ios;
		ip::udp::endpoint send_ep(ip::address::from_string("192.168.123.235"),6699);
 
        ip::udp::socket sock(ios);
		sock.open(ip::udp::v4());
	char buf[1];
	cout << "send request to " << send_ep.address() << endl;
	sock.send_to(buffer(buf),send_ep);       

        vector<float> pos = (6,0);
		ip::udp::endpoint recv_ep;
		sock.receive_from(buffer(pos), recv_ep);
		cout << "receive pose from " << recv_ep.address() << endl;
    }
    catch(std::exception& e){
        cout << e.what() << endl;
    }
    return 0;
}

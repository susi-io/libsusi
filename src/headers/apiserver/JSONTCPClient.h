/*
 * Copyright (c) 2014, webvariants GmbH, http://www.webvariants.de
 *
 * This file is released under the terms of the MIT license. You can find the
 * complete text in the attached LICENSE file or online at:
 *
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * @author: Tino Rusch (tino.rusch@webvariants.de)
 */

#ifndef __JSONTCPCLIENT__
#define __JSONTCPCLIENT__

#include "apiserver/TCPClient.h"
#include "apiserver/JSONStreamCollector.h"
#include "util/Any.h"

namespace Susi {
namespace Api {

class JSONTCPClient : public TCPClient {
public:
	JSONTCPClient(std::string host, unsigned short port) : TCPClient{host, port} {}
protected:
	virtual void onMessage(Susi::Util::Any & message) = 0;
	JSONStreamCollector collector{[this](std::string & msg){
		auto message = Susi::Util::Any::fromString(msg);
		this->onMessage(message);
	}};
	virtual void onData(std::string & data) override {
		collector.collect(data);
	}

	void send(Susi::Util::Any & message){
		std::string msg = message.toString();
		TCPClient::send(msg);
	}
};

}	
}


#endif // __JSONTCPCLIENT__
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

#ifndef __APISERVER__
#define __APISERVER__

#include <memory>
#include "events/global.h"
#include <functional>

namespace Susi {
namespace Api {

class ApiServer {
protected:
	std::map<std::string,std::function<void(Susi::Util::Any&)>> senders;
	std::map<std::string,std::map<std::string,long>> subscriptions;
	std::map<std::string,std::map<long,Susi::Events::EventPtr>> eventsToAck;
	
	void handleRegisterConsumer(std::string & id, Susi::Util::Any & packet);
	void handleRegisterProcessor(std::string & id, Susi::Util::Any & packet);
	void handleUnregister(std::string & id, Susi::Util::Any & packet);
	void handlePublish(std::string & id, Susi::Util::Any & packet);
	void handleAck(std::string & id, Susi::Util::Any & packet);

	void sendOk(std::string & id);
	void sendFail(std::string & id,std::string error = "");
	
	void send(std::string & id, Susi::Util::Any & msg){
		auto & sender = senders[id];
		if(sender)sender(msg);
	}

public:
	inline void registerSender(std::string id , std::function<void(Susi::Util::Any&)> sender){
		senders[id] = sender;
	}
	void onConnect(std::string & id);
	void onMessage(std::string & id, Susi::Util::Any & packet);
	void onClose(std::string & id);
};

}
}

#endif // __APISERVER__

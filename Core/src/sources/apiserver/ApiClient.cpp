#include "apiserver/ApiClient.h"

void Susi::Api::ApiClient::publish( Susi::Events::EventPtr event, Susi::Events::Consumer finishCallback ) {
    finishCallbacks[event->getID()] = finishCallback;
    sendPublish( *event );
    delete event.release();
}

long Susi::Api::ApiClient::subscribe( std::string topic, Susi::Events::Processor processor , char authlevel, std::string name) {
    sendRegisterProcessor( topic,authlevel,name );
    return Susi::Events::Manager::subscribe( topic,processor,authlevel,name );
}

long Susi::Api::ApiClient::subscribe( std::string topic, Susi::Events::Consumer consumer , char authlevel, std::string name) {
    sendRegisterConsumer( topic,authlevel,name );
    return Susi::Events::Manager::subscribe( topic,consumer,authlevel,name );
}


void Susi::Api::ApiClient::onConsumerEvent( Susi::Events::Event & event ) {
    auto evt = createEvent( event.getTopic() );
    *evt = event;
    Susi::Events::Manager::publish( std::move( evt ) );
}

void Susi::Api::ApiClient::onProcessorEvent( Susi::Events::Event & event ) {
    auto evt = createEvent( event.getTopic() );
    *evt = event;
    Susi::Events::Manager::publish( std::move( evt ),[this]( Susi::Events::SharedEventPtr event ) {
        //std::cout<<"finished in client, acking to susi!"<<std::endl;
        sendAck( *event );
        //std::cout<<"sended ack"<<std::endl;
    } );
}

void Susi::Api::ApiClient::onAck( Susi::Events::Event & event ) {
    auto evt = std::make_shared<Susi::Events::Event>( event );
    auto callback = finishCallbacks[evt->getID()];
    if( callback ) {
        callback( evt );
    }
}
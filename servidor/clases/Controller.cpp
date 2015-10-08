#include <iostream>
#include "Controller.h"
#include "StreamResponse.h"
#include <string>
#include <sstream>
#include <vector>


using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

namespace Mongoose
{

    Controller::Controller() 
        : sessions(NULL), server(NULL), prefix("")
    {
    }

    void Controller::setup()
    {
    }

    void Controller::setServer(Server *server_)
    {
        server = server_;
    }

    void Controller::webSocketReady(WebSocket *websocket)
    {
    }

    void Controller::webSocketData(WebSocket *websocket, string data)
    {
    }
    
    Controller::~Controller()
    {
        map<string, RequestHandlerBase *>::iterator it;

        for (it=routes.begin(); it!=routes.end(); it++) {
            delete (*it).second;
        }

        routes.clear();
    }
            
    bool Controller::handles(string method, string url)
    { 
        string key = method + ":" + url;
        std::vector<std::string> urlSplited = split(url, '/');

        if(urlSplited.size() == 3)
        {
        	return true;
        }


        return (routes.find(key) != routes.end());
    }

    Response *Controller::process(Request &request)
    {
        Response *response = NULL;

#ifdef ENABLE_REGEX_URL
        map<string, RequestHandlerBase *>::iterator it; 
        for (it=routes.begin(); it!=routes.end(); it++) {
            if (request.match(it->first)){
              response = it->second->process(request);
              break;
            }   
        }   
#else
        std::vector<std::string> urlSplited = split(request.getUrl(), '/');
        if(urlSplited.size() == 3){
        	int indexId = request.getUrl().find_last_of("/");
        	string urlWithoutId = request.getUrl().substr(0,indexId + 1);

        	string key = request.getMethod() + ":" + urlWithoutId;
			if (routesWithId.find(key) != routesWithId.end()) {
				response = routesWithId[key]->process(request);
			}
        }else{
			string key = request.getMethod() + ":" + request.getUrl();
			if (routes.find(key) != routes.end()) {
				response = routes[key]->process(request);
			}
        }
#endif
        
        return response;
    }
            
    void Controller::preProcess(Request &request, Response &response)
    {
    }
            
    void Controller::postProcess(Request &request, Response &response)
    {
    }

    Response *Controller::handleRequest(Request &request)
    {
        Response *response = process(request);

        if (response != NULL) {
            postProcess(request, *response);
        }

        return response;
    }

    void Controller::setPrefix(string prefix_)
    {
        prefix = prefix_;
    }
            
    void Controller::registerRoute(string httpMethod, string route, RequestHandlerBase *handler)
    {
        string key = httpMethod + ":" + prefix + route;
        routes[key] = handler;
        urls.push_back(prefix + route);
    }

    void Controller::registerRouteWithId(string httpMethod, string route, RequestHandlerBase *handler)
        {
            string key = httpMethod + ":" + prefix + route;
            routesWithId[key] = handler;
            urls.push_back(prefix + route);
        }

    void Controller::dumpRoutes()
    {
        map<string, RequestHandlerBase *>::iterator it;

        for (it=routes.begin(); it!=routes.end(); it++) {
            cout << (*it).first << endl;
        }

    }

    Response *Controller::serverInternalError(string message)
    {
        StreamResponse *response = new StreamResponse;

        response->setCode(HTTP_SERVER_ERROR);
        *response << "[500] Server internal error: " << message;

        return response;
    }

    vector<string> Controller::getUrls()
    {
        return urls;
    }

    Session &Controller::getSession(Request &request, Response &response)
    {
        return sessions->get(request, response);
    }

    void Controller::setSessions(Sessions *sessions_)
    {
        sessions = sessions_;
    }
    void Controller::setManejadorDB(ManejadorDB* manejador ){
    	manejadorDB = manejador;
    }
}

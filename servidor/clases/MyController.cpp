/*
 * MyController.cpp
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#include "MyController.h"
namespace Mongoose
{
MyController::MyController() {
	// TODO Auto-generated constructor stub

}

MyController::~MyController() {
	// TODO Auto-generated destructor stub
}

void MyController::hello(Request &request, StreamResponse &response)
{
	response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
}

void MyController::setup()
{
	addRoute("GET", "/hello", MyController, hello);
}
}

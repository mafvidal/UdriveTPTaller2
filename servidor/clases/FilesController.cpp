/*
 * FilesController.cpp
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */
#include "FilesController.h"

namespace Mongoose
{
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

FilesController::FilesController() {
	// TODO Auto-generated constructor stub

}

FilesController::~FilesController() {
	// TODO Auto-generated destructor stub
}

void FilesController::getFiles(Request &request, StreamResponse &response)
{
	response << "{ file 1, file 2, file 3}" << endl;
}
void FilesController::getFile(Request &request, StreamResponse &response)
{
	std::vector<std::string> urlSplited = split(request.getUrl(), '/');
	response << "{file: "+ urlSplited[2] +"}" << endl;
}
void FilesController::addFile(Request &request, StreamResponse &response)
{
	response << "{ archivo agregado}" << endl;
}
void FilesController::updateFile(Request &request, StreamResponse &response)
{
	std::vector<std::string> urlSplited = split(request.getUrl(), '/');
		response << "{file: "+ urlSplited[2] +" modificado}" << endl;
}
void FilesController::deleteFile(Request &request, StreamResponse &response)
{
	std::vector<std::string> urlSplited = split(request.getUrl(), '/');
		response << "{file: "+ urlSplited[2] +"eliminado }" << endl;
}
void FilesController::setup()
{
	string id;
	addRoute("GET","/files",FilesController, getFiles);
	addRouteWithId("GET","/files/",FilesController, getFile);
	addRoute("POST","/files",FilesController, addFile);
	addRoute("PUT","/files/",FilesController, updateFile);
	addRoute("DELETE","/files/",FilesController, deleteFile);


}
}

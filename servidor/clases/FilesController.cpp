/*
 * FilesController.cpp
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#include "FilesController.h"

namespace Mongoose
{
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
//void FilesController::getFile(Request &request, StreamResponse &response,int id)
//{
//	response << id << endl;
//}
void FilesController::setup()
{
	string id;
	addRoute("GET","/files",FilesController, getFiles)
	//addRoute("GET","/files/",FilesController, getFile)

}
}

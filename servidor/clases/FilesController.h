/*
 * FilesController.h
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#ifndef FILESCONTROLLER_H_
#define FILESCONTROLLER_H_

#include "WebController.h"

namespace Mongoose
{
class FilesController : public WebController
{
	public:
		FilesController();
		FilesController(ManejadorDB* manejadorDB);
		virtual ~FilesController();
		void getFiles(Request &request, StreamResponse &response);
		void getFile(Request &request, StreamResponse &response);
		void addFile(Request &request, StreamResponse &response);
		void updateFile(Request &request, StreamResponse &response);
		void deleteFile(Request &request, StreamResponse &response);
		void setup();

};

}
#endif /* FILESCONTROLLER_H_ */

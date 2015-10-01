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
		virtual ~FilesController();
		void getFiles(Request &request, StreamResponse &response);
		void getFile(Request &request, StreamResponse &response,int id);
		void setup();

};
}
#endif /* FILESCONTROLLER_H_ */

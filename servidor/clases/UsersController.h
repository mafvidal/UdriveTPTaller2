/*
 * UsersController.h
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#ifndef USERSCONTROLLER_H_
#define USERSCONTROLLER_H_
#include "WebController.h"

namespace Mongoose
{
	class UsersController : public WebController{
	public:
		UsersController();
		virtual ~UsersController();

		void setup();
		void addUser(Request &request, StreamResponse &response);
	};
}
#endif /* USERSCONTROLLER_H_ */
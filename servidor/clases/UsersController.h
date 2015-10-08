/*
 * UsersController.h
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#ifndef USERSCONTROLLER_H_
#define USERSCONTROLLER_H_
#include "WebController.h"
#include "ManejadorDB.h"


namespace Mongoose
{
	class UsersController : public WebController{
	private:
		ManejadorDB* manejadorDB;

	public:
		UsersController();
		UsersController(ManejadorDB* manejadorDB);
		virtual ~UsersController();

		void setup();
		void addUser(Request &request, StreamResponse &response);
		void CheckearBaseDeDatos(string ubicacion);
	};
}
#endif /* USERSCONTROLLER_H_ */

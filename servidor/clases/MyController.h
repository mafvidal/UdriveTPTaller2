/*
 * MyController.h
 *
 *  Created on: Sep 29, 2015
 *      Author: facusan
 */

#ifndef MYCONTROLLER_H_
#define MYCONTROLLER_H_

#include "WebController.h"

using namespace std;

namespace Mongoose
{
	class MyController : public WebController
	{
		public:
			MyController();
			virtual ~MyController();
			void hello(Request &request, StreamResponse &response);
			void setup();
	};
}
#endif /* MYCONTROLLER_H_ */

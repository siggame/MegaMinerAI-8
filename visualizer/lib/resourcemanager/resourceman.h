#ifndef RESOURCEMAN_H
#define RESOURCEMAN_H

#include "../singleton.h"
#include "resource.h"
#include "../manager/manager.h"
#include <map>
#include <string>
#include <vector>

/** @todo merge this into the options manager... maybe **/

typedef std::string ResID_t;

class ResourceMan : protected Manager <ResID_t,Resource*>
{
	public:
		/** Default constructor */
		ResourceMan();
		/** Default destructor */
		virtual ~ResourceMan();

        static Resource * reference(const std::string & rName, const std::string & referencer);
        static bool release(const std::string & rName, const std::string & referencer);

		template<class T, ResourceType RT>
		static bool reg(const ResID_t & rName, const T & value);
		static bool reg(const ResID_t & rName, const std::string & filename);
		static bool del(const ResID_t & rName);

		static bool loadResourceFile(const ResID_t & filename);
		static bool saveResourceFile(const ResID_t & filename);

		static bool exists(const ResID_t & rName);

		static std::vector<std::string> listResourceNames();

		static bool destroy();

	protected:
	private:

		ResourceType findFileType(const std::string & filename);

};

#endif // RESOURCEMAN_H

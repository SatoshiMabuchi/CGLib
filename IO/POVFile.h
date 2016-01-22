#ifndef __CRYSTAL_IO_POV_FILE_H__
#define __CRYSTAL_IO_POV_FILE_H__

#include "../Graphics/Surface.h"

namespace Crystal {
	namespace IO {

class POVFile
{
public:
	bool writeScene(const std::string& file, const Graphics::Surface<float>& surface);

	bool writeInc(const std::string& file, const Graphics::Surface<float>& surface);
private:

};
	}
}

#endif
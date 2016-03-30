#ifndef __CRYSTAL_GRAPHICS_DRAWABLE_ID_H__
#define __CRYSTAL_GRAPHICS_DRAWABLE_ID_H__

namespace Crystal {
	namespace Graphics {
		template<typename>
		class ColorRGBA;

class DrawableID
{
public:
	explicit DrawableID(const unsigned int id) :
		id(id)
	{}

	//DrawableID(const unsigned int groupId, const unsigned int elementId);

	ColorRGBA<float> toColor() const;

	unsigned int toUInt() const { return id; }

	bool equals(const DrawableID& rhs) const {
		return this->id == rhs.id;
	}

	bool operator==(const DrawableID& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const DrawableID& rhs) const {
		return !equals(rhs);
	}


private:
	const unsigned int id;
};

	}
}

#endif
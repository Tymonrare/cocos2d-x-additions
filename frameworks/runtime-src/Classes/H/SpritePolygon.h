#include <H/Source.h>
#include "renderer/CCTrianglesCommand.h"

namespace gm{
class SpritePolygonTool
{
public:
	/// @param textureSize size of target texture
	/// @param density count of triangles
	static PolygonInfo getGridPolygon(const Size &textureSize, const Size &density);

	static void setDebugDraw(Sprite *sprite, bool enabled);
private:
	static TrianglesCommand::Triangles triangulateGrid(const std::vector<Point> &points, const Size &density);

	static void calculateUV(const Size &textureSize, const Rect& rect, V3F_C4B_T2F* verts, ssize_t count);

	/// @param textureSize size of target texture
	/// @param density count of triangles
	static std::vector<Point> makePointsGrid(const Size &textureSize, const Size &density);
};

class FlexSprite : public Sprite
{
	public: 
		    static FlexSprite* create(const std::string& filename, const Size &density);

		    PolygonInfo *getPolyginInfoDirect();
	private:
		    bool initWithFile(const std::string& filename, const Size &density);
};
}

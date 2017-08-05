#include <H/SpritePolygon.h>

using namespace gm;

PolygonInfo SpritePolygonTool::getGridPolygon(const Size &textureSize, const Size &density){
	auto tri = triangulateGrid(makePointsGrid(textureSize, density), density);
	calculateUV(textureSize, Rect(0,0, textureSize.width, textureSize.height), tri.verts, tri.vertCount);
	PolygonInfo ret;
	ret.triangles = tri;
	return ret;
}

std::vector<Point> SpritePolygonTool::makePointsGrid(const Size &textureSize, const Size &density){
	std::vector<Point> points;

	//density is count of triangles. Points coint is triangles +1
	for(int yi = 0;yi <= density.height;yi++) for(int xi = 0;xi <= density.width;xi++){
		Point p;

		p.x = textureSize.width/density.width*xi;
		p.y = textureSize.height/density.height*yi;
		points.push_back(p);
	}
	return points;
}

TrianglesCommand::Triangles SpritePolygonTool::triangulateGrid(const std::vector<Point> &points, const Size &density){
	std::vector<V3F_C4B_T2F> verts;
	std::vector<unsigned short> indices;

	log("create poly with %zu points", points.size());

	for(auto i : points){
		auto v3  = Vec3(i.x, i.y, 0);
		auto c4b = Color4B::WHITE;
                auto t2f = Tex2F(0,0); // don't worry about tex coords now, we calculate that later
                V3F_C4B_T2F vert = {v3,c4b,t2f};
		verts.push_back(vert);
	}

	int till = points.size() - (density.width + 2);
	log("create %d polygons", (till-1)*2);
	for(int yi = 0;yi < density.height;yi++) for(int xi = 0;xi < density.width;xi++){
		int i = yi*density.width + yi + xi;
		//first, "top" triangle
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + density.width + 2);

		//second, "bottom" triangle
		indices.push_back(i);
		indices.push_back(i + density.width + 1);
		indices.push_back(i + density.width + 2);
	}


	// now that we know the size of verts and indices we can create the buffers
	V3F_C4B_T2F* vertsBuf = new (std::nothrow) V3F_C4B_T2F[verts.size()];
	memcpy(vertsBuf, verts.data(), verts.size() * sizeof(V3F_C4B_T2F));

	unsigned short* indicesBuf = new (std::nothrow) unsigned short[indices.size()];
	memcpy(indicesBuf, indices.data(), indices.size() * sizeof(short));

	// Triangles should really use std::vector and not arrays for verts and indices.
	// Then the above memcpy would not be necessary
	TrianglesCommand::Triangles triangles = { vertsBuf, indicesBuf, static_cast<int>(verts.size()), static_cast<int>(indices.size()) };
	return triangles;
}

void SpritePolygonTool::setDebugDraw(Sprite *sprite, bool enabled){
	auto childNode = sprite->getChildByName("polygonDrawDebugNode");
	if(!enabled){
		if(childNode) childNode->removeFromParent();
		return;
	}

	DrawNode *spDrawNode;
	if(!childNode){
		spDrawNode = DrawNode::create();
		spDrawNode->setOpacity(100);
		sprite->addChild(spDrawNode, 0, "polygonDrawDebugNode");
	}
	else spDrawNode = static_cast<DrawNode*>(childNode);

	const auto& polygoninfo = sprite->getPolygonInfo();
	spDrawNode->clear();
	const auto count = polygoninfo.triangles.indexCount/3;
	const auto indices = polygoninfo.triangles.indices;
	const auto verts = polygoninfo.triangles.verts;
	for(ssize_t i = 0; i < count; i++)
	{
		//draw 3 lines
		Vec3 from = verts[indices[i*3]].vertices;
		Vec3 to = verts[indices[i*3+1]].vertices;
		spDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);

		from = verts[indices[i*3+1]].vertices;
		to = verts[indices[i*3+2]].vertices;
		spDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);

		from = verts[indices[i*3+2]].vertices;
		to = verts[indices[i*3]].vertices;
		spDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::GREEN);
	}

}

void SpritePolygonTool::calculateUV(const Size &textureSize, const Rect& rect, V3F_C4B_T2F* verts, ssize_t count)
{
    /*
     whole texture UV coordination
     0,0                  1,0
     +---------------------+
     |                     |0.1
     |                     |0.2
     |     +--------+      |0.3
     |     |texRect |      |0.4
     |     |        |      |0.5
     |     |        |      |0.6
     |     +--------+      |0.7
     |                     |0.8
     |                     |0.9
     +---------------------+
     0,1                  1,1
     */

    CCASSERT(_width && _height, "please specify width and height for this AutoPolygon instance");
    float texWidth  = textureSize.width;
    float texHeight = textureSize.height;
    float _scaleFactor = 1;

    auto end = &verts[count];
    for(auto i = verts; i != end; ++i)
    {
        // for every point, offset with the center point
        float u = (i->vertices.x*_scaleFactor + rect.origin.x) / texWidth;
        float v = (rect.origin.y+rect.size.height - i->vertices.y*_scaleFactor) / texHeight;
        i->texCoords.u = u;
        i->texCoords.v = v;
    }
}

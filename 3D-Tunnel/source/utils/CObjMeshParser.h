////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CObjMeshParsers.h
 * \author  Hua Fei Yu 0951402
 * \date    Nov 5, 2011
 * \brief  	Obj mesh loader based work by The OpenGL OBJ Loader open source proj
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef COBJMESHPARSER_H_
#define COBJMESHPARSER_H_

// Headers
#include <string>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "gl/gl.h"
#include "dcMath.h"
#include "tokens/CFace.h"


class CMesh;

using std::vector;

class CObjMeshParser
{
	public:
        static void parse(boost::shared_ptr<CMesh>& mesh, std::string file_name);

        static const int INDEX_OFFSET;
	private:
        static void skipLine(std::istream& is);
        static bool skipCommentLine(std::istream& is);
        static bool processLine(boost::shared_ptr<CMesh>& mesh, std::istream& is);
        static void generateBuffers(boost::shared_ptr<CMesh>& mesh);
        static vector<Vec3f> vertex_buffer;
        static vector<Vec3f> normal_buffer;
        static vector<Vec2f> texture_buffer;
        static vector<CFace>   face_buffer;

};

#endif /* COBJMESHPARSER_H_ */

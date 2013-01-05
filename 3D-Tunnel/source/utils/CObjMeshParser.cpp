////////////////////////////////////////////////////////////////////////////////
/**
 * \file    CObjMeshParsers.cpp
 * \author  Hua Fei Yu 0951402
 * \date    Nov 5, 2011
 * \brief
 */
////////////////////////////////////////////////////////////////////////////////
// Headers
#include "CObjMeshParser.h"
#include <fstream>
#include <string>
#include <iostream>

#include "mytypes.h"
#include "tokens/CMesh.h"
#include "graphics/dcVBO.h"


using namespace std;
using boost::shared_ptr;

const int CObjMeshParser::INDEX_OFFSET = 1;
vector<Vec3f>   CObjMeshParser::vertex_buffer; // Make local variables later
vector<Vec3f>   CObjMeshParser::normal_buffer;
vector<Vec2f>   CObjMeshParser::texture_buffer;
vector<CFace>   CObjMeshParser::face_buffer;

void CObjMeshParser::parse(boost::shared_ptr<CMesh>& mesh, std::string file_name)
{
    vertex_buffer.clear();
    normal_buffer.clear();
    texture_buffer.clear();
    face_buffer.clear();
    ifstream ifs(file_name.c_str(), ios::in|ios::ate);
    if(!ifs) { cout << "\nError reading file\n"; ifs.close(); return; }

    dcVBO::init();

    const int file_size = ifs.tellg();

    ifs.seekg(0, ios::beg);
    if (file_size==0) if(!ifs) { cout << "\nFile Empty\n"; ifs.close(); return; }

//    mesh->clear();
    while(skipCommentLine(ifs))
    {
        if (!processLine(mesh, ifs)) { break; }
    }

    ifs.close();

    generateBuffers(mesh);
}

void CObjMeshParser::generateBuffers(boost::shared_ptr<CMesh>& mesh)
{
    GLuint vertex_array_sz      = face_buffer.size()*3;
    GLuint normal_array_sz       = face_buffer.size()*3;
    GLuint texture_array_sz     = face_buffer.size()*3;
    Vec3f* vertex_array         = new Vec3f[face_buffer.size()*3];
    Vec3f* normal_array         = new Vec3f[face_buffer.size()*3];
    Vec2f* texture_array        = new Vec2f[face_buffer.size()*3];
//    GLfloat texture_array[face_buffer.size() * 3];

    // Build the list of verticies. Verticies are repeated use indicies in future?
    for (uint i=0; i<face_buffer.size(); ++i)
    {
        for (uint j=0; j<3; ++j) // 3 Verticies per triangle
        {
            vertex_array[i*3+j]                 = vertex_buffer[face_buffer[i].v[j]];
            if (normal_buffer.size()!=0)        // If normals were specificed in the obj file
            {
                normal_array[i*3+j]             = normal_buffer[face_buffer[i].vn[j]];
            }
            if (texture_buffer.size()!=0)
            { texture_array[i*3+j] = texture_buffer[face_buffer[i].vt[j]]; }

        }
    }
    mesh->setArrays(vertex_array, vertex_array_sz, normal_array, normal_array_sz, texture_array, texture_array_sz);
    mesh->generate();
}



void CObjMeshParser::skipLine(istream& is)
{
    char next;
	is >> std::noskipws;
    while( (is >> next) && ('\n' != next) );
}

bool CObjMeshParser::skipCommentLine(istream& is)
{
	char next;
	while (is >> std::skipws >> next)
    {
		is.putback(next);
		if ('#' == next)
			skipLine(is);
		else
			return true;
    }
    return false;
}

bool CObjMeshParser::processLine(shared_ptr<CMesh>& mesh, istream& is)
{
	string ele_id;
	float x, y, z;
	CFace           temp_face;

	if (!(is >> ele_id))
		return false;

//	if ("mtllib" == ele_id) {
//		string strFileName;
//		is >> strFileName;
//		parseMtlLib(strFileName);
//	}
//	else if ("usemtl" == ele_id) {
//		string strMtlName;
//		is >> strMtlName;
//		map<string, SMaterial>::iterator it = m_materialMap.find(strMtlName);
//		if (it != m_materialMap.end())
//			mesh->setMaterial((*it).second);
//		else
//			CLogger::get() << "  * Material not found in current mtllib :\"" << strMtlName << "\". Ignoring material.\n";
//	}
	if ("v" == ele_id)
	{	//	vertex data
		is >> x >> y >> z;
        vertex_buffer.push_back(Vec3f(x, y, z));
	}
	else if ("vt" == ele_id)
	{	// texture data
		is >> x >> y;
		is.clear();                           // is z (i.e. w) is not available, have to clear error flag.
		texture_buffer.push_back(Vec2f(x, y));
	}
	else if ("vn" == ele_id)
	{	// normal data
		is >> x >> y >> z;
		if(!is.good()) {                     // in case it is -1#IND00
			x = y = z = 0.0;
			is.clear();
			skipLine(is);
		}
		normal_buffer.push_back(Vec3f(x, y, z));
	}
	else if ("f" == ele_id)
	{	//	face data
								//	face treatment
								//  Note: obviously this technique only works for convex polygons with ten verts or less.
		int vi[10];                               // vertex indices.
		int ni[10] = { -1, -1, -1, -1, };         // normal indices.
		int ti[10] = { -1, -1, -1, -1, };         // tex indices.
		int i = 0;
		for (char c; i<10; ++i) {
			if(!mesh->hasTextureCoords() && !mesh->hasNormals())
				is >> vi[i];
			else if(!mesh->hasTextureCoords())
				is >> vi[i] >> c >> c >> ni[i];
			else if(!mesh->hasNormals())
				is >> vi[i] >> c >> ti[i];
			else
				is >> vi[i] >> c >> ti[i] >> c >>  ni[i];

			if(!is.good())
				break;
		}
		//	Create the polygon face
		CFace face;
		for (int k=0; k < i; ++k)
		{
		    face.v[k] = vi[k]-INDEX_OFFSET;
		    face.vn[k] = ni[k]-INDEX_OFFSET;
		    face.vt[k] = ti[k]-INDEX_OFFSET;
		}
		face_buffer.push_back(face);

		is.clear();
	}
	else
		skipLine(is);
	return true;
}

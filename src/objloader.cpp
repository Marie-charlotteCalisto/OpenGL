#include <iostream>

#include "objloader.hh"

// From https://github.com/opengl-tutorials/ogl/blob/master/common/objloader.cpp
bool loadOBJ(
    const char * path,
    std::vector<Mesh> &meshes
){

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_GenNormals);
    if( !scene) {
        fprintf( stderr, importer.GetErrorString());
        getchar();
        return false;
    }
    for (int meshNo = 0; meshNo < scene->mNumMeshes; meshNo++) {
        const aiMesh* assimpMesh = scene->mMeshes[meshNo];
        {
            Mesh mesh;
            // Fill position, normal and texture coordinate of vertices
            mesh.vertices.reserve(assimpMesh->mNumVertices);
            mesh.normals.reserve(assimpMesh->mNumVertices);
            mesh.uvCoord.reserve(assimpMesh->mNumVertices);

            for(unsigned int i=0; i < assimpMesh->mNumVertices; i++){
                aiVector3D pos = assimpMesh->mVertices[i];
                mesh.vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));

                aiVector3D n = assimpMesh->mNormals[i];
                mesh.normals.push_back(glm::vec3(n.x, n.y, n.z));

                if (assimpMesh->mTextureCoords[0])
                {
                    aiVector3D UVW = assimpMesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
                    mesh.uvCoord.push_back(glm::vec2(UVW.x, UVW.y));

                }
            }
            meshes.push_back(mesh);
        }

    }

    /*
     * Not used currently
    // Fill face indices
    indices.reserve(3*mesh->mNumFaces);
    for (unsigned int i=0; i<mesh->mNumFaces; i++){
        // Assume the model has only triangles.
        indices.push_back(mesh->mFaces[i].mIndices[0]);
        indices.push_back(mesh->mFaces[i].mIndices[1]);
        indices.push_back(mesh->mFaces[i].mIndices[2]);
    }
    */

    // The "scene" pointer will be deleted automatically by "importer"
    return true;
}

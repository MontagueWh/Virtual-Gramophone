/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== camera.h ==================
static const unsigned char temp_binary_data_0[] =
"/*\n"
"---------------------------------------------------------------------------\n"
"Open Asset Import Library (assimp)\n"
"---------------------------------------------------------------------------\n"
"\n"
"Copyright (c) 2006-2025, assimp team\n"
"\n"
"All rights reserved.\n"
"\n"
"Redistribution and use of this software in source and binary forms,\n"
"with or without modification, are permitted provided that the following\n"
"conditions are met:\n"
"\n"
"* Redistributions of source code must retain the above\n"
"  copyright notice, this list of conditions and the\n"
"  following disclaimer.\n"
"\n"
"* Redistributions in binary form must reproduce the above\n"
"  copyright notice, this list of conditions and the\n"
"  following disclaimer in the documentation and/or other\n"
"  materials provided with the distribution.\n"
"\n"
"* Neither the name of the assimp team, nor the names of its\n"
"  contributors may be used to endorse or promote products\n"
"  derived from this software without specific prior\n"
"  written permission of the assimp team.\n"
"\n"
"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n"
"\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n"
"LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n"
"A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\n"
"OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\n"
"SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n"
"LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\n"
"DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\n"
"THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n"
"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n"
"OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
"---------------------------------------------------------------------------\n"
"*/\n"
"\n"
"/** @file camera.h\n"
" *  @brief Defines the aiCamera data structure\n"
" */\n"
"\n"
"#pragma once\n"
"#ifndef AI_CAMERA_H_INC\n"
"#define AI_CAMERA_H_INC\n"
"\n"
"#ifdef __GNUC__\n"
"#pragma GCC system_header\n"
"#endif\n"
"\n"
"#include \"types.h\"\n"
"\n"
"#ifdef __cplusplus\n"
"extern \"C\" {\n"
"#endif\n"
"\n"
"// ---------------------------------------------------------------------------\n"
"/** Helper structure to describe a virtual camera.\n"
" *\n"
" * Cameras have a representation in the node graph and can be animated.\n"
" * An important aspect is that the camera itself is also part of the\n"
" * scene-graph. This means, any values such as the look-at vector are not\n"
" * *absolute*, they're <b>relative</b> to the coordinate system defined\n"
" * by the node which corresponds to the camera. This allows for camera\n"
" * animations. For static cameras parameters like the 'look-at' or 'up' vectors\n"
" * are usually specified directly in aiCamera, but beware, they could also\n"
" * be encoded in the node transformation. The following (pseudo)code sample\n"
" * shows how to do it: <br><br>\n"
" * @code\n"
" * // Get the camera matrix for a camera at a specific time\n"
" * // if the node hierarchy for the camera does not contain\n"
" * // at least one animated node this is a static computation\n"
" * get-camera-matrix (node sceneRoot, camera cam) : matrix\n"
" * {\n"
" *    node   cnd = find-node-for-camera(cam)\n"
" *    matrix cmt = identity()\n"
" *\n"
" *    // as usual - get the absolute camera transformation for this frame\n"
" *    for each node nd in hierarchy from sceneRoot to cnd\n"
" *      matrix cur\n"
" *      if (is-animated(nd))\n"
" *         cur = eval-animation(nd)\n"
" *      else cur = nd->mTransformation;\n"
" *      cmt = mult-matrices( cmt, cur )\n"
" *    end for\n"
" *\n"
" *    // now multiply with the camera's own local transform\n"
" *    cam = mult-matrices (cam, get-camera-matrix(cmt) )\n"
" * }\n"
" * @endcode\n"
" *\n"
" * @note some file formats (such as 3DS, ASE) export a \"target point\" -\n"
" * the point the camera is looking at (it can even be animated). Assimp\n"
" * writes the target point as a subnode of the camera's main node,\n"
" * called \"<camName>.Target\". However this is just additional information\n"
" * then the transformation tracks of the camera main node make the\n"
" * camera already look in the right direction.\n"
" *\n"
"*/\n"
"struct aiCamera {\n"
"    /** The name of the camera.\n"
"     *\n"
"     *  There must be a node in the scenegraph with the same name.\n"
"     *  This node specifies the position of the camera in the scene\n"
"     *  hierarchy and can be animated.\n"
"     */\n"
"    C_STRUCT aiString mName;\n"
"\n"
"    /** Position of the camera relative to the coordinate space\n"
"     *  defined by the corresponding node.\n"
"     *\n"
"     *  The default value is 0|0|0.\n"
"     */\n"
"    C_STRUCT aiVector3D mPosition;\n"
"\n"
"    /** 'Up' - vector of the camera coordinate system relative to\n"
"     *  the coordinate space defined by the corresponding node.\n"
"     *\n"
"     *  The 'right' vector of the camera coordinate system is\n"
"     *  the cross product of  the up and lookAt vectors.\n"
"     *  The default value is 0|1|0. The vector\n"
"     *  may be normalized, but it needn't.\n"
"     */\n"
"    C_STRUCT aiVector3D mUp;\n"
"\n"
"    /** 'LookAt' - vector of the camera coordinate system relative to\n"
"     *  the coordinate space defined by the corresponding node.\n"
"     *\n"
"     *  This is the viewing direction of the user.\n"
"     *  The default value is 0|0|1. The vector\n"
"     *  may be normalized, but it needn't.\n"
"     */\n"
"    C_STRUCT aiVector3D mLookAt;\n"
"\n"
"    /** Horizontal field of view angle, in radians.\n"
"     *\n"
"     *  The field of view angle is the angle between the center\n"
"     *  line of the screen and the left or right border.\n"
"     *  The default value is 1/4PI.\n"
"     */\n"
"    float mHorizontalFOV;\n"
"\n"
"    /** Distance of the near clipping plane from the camera.\n"
"     *\n"
"     * The value may not be 0.f (for arithmetic reasons to prevent\n"
"     * a division through zero). The default value is 0.1f.\n"
"     */\n"
"    float mClipPlaneNear;\n"
"\n"
"    /** Distance of the far clipping plane from the camera.\n"
"     *\n"
"     * The far clipping plane must, of course, be further away than the\n"
"     * near clipping plane. The default value is 1000.f. The ratio\n"
"     * between the near and the far plane should not be too\n"
"     * large (between 1000-10000 should be ok) to avoid floating-point\n"
"     * inaccuracies which could lead to z-fighting.\n"
"     */\n"
"    float mClipPlaneFar;\n"
"\n"
"    /** Screen aspect ratio.\n"
"     *\n"
"     * This is the ration between the width and the height of the\n"
"     * screen. Typical values are 4/3, 1/2 or 1/1. This value is\n"
"     * 0 if the aspect ratio is not defined in the source file.\n"
"     * 0 is also the default value.\n"
"     */\n"
"    float mAspect;\n"
"\n"
"    /** Half horizontal orthographic width, in scene units.\n"
"     *\n"
"     *  The orthographic width specifies the half width of the\n"
"     *  orthographic view box. If non-zero the camera is\n"
"     *  orthographic and the mAspect should define to the\n"
"     *  ratio between the orthographic width and height\n"
"     *  and mHorizontalFOV should be set to 0.\n"
"     *  The default value is 0 (not orthographic).\n"
"     */\n"
"    float mOrthographicWidth;\n"
"#ifdef __cplusplus\n"
"\n"
"    aiCamera() AI_NO_EXCEPT\n"
"            : mUp(0.f, 1.f, 0.f),\n"
"              mLookAt(0.f, 0.f, 1.f),\n"
"              mHorizontalFOV(0.25f * (float)AI_MATH_PI),\n"
"              mClipPlaneNear(0.1f),\n"
"              mClipPlaneFar(1000.f),\n"
"              mAspect(0.f),\n"
"              mOrthographicWidth(0.f) {}\n"
"\n"
"    /** @brief Get a *right-handed* camera matrix from me\n"
"     *  @param out Camera matrix to be filled\n"
"     */\n"
"    void GetCameraMatrix(aiMatrix4x4 &out) const {\n"
"        /** todo: test ... should work, but i'm not absolutely sure */\n"
"\n"
"        /** We don't know whether these vectors are already normalized ...*/\n"
"        aiVector3D zaxis = mLookAt;\n"
"        zaxis.Normalize();\n"
"        aiVector3D yaxis = mUp;\n"
"        yaxis.Normalize();\n"
"        aiVector3D xaxis = mUp ^ mLookAt;\n"
"        xaxis.Normalize();\n"
"\n"
"        out.a4 = -(xaxis * mPosition);\n"
"        out.b4 = -(yaxis * mPosition);\n"
"        out.c4 = -(zaxis * mPosition);\n"
"\n"
"        out.a1 = xaxis.x;\n"
"        out.a2 = xaxis.y;\n"
"        out.a3 = xaxis.z;\n"
"\n"
"        out.b1 = yaxis.x;\n"
"        out.b2 = yaxis.y;\n"
"        out.b3 = yaxis.z;\n"
"\n"
"        out.c1 = zaxis.x;\n"
"        out.c2 = zaxis.y;\n"
"        out.c3 = zaxis.z;\n"
"\n"
"        out.d1 = out.d2 = out.d3 = 0.f;\n"
"        out.d4 = 1.f;\n"
"    }\n"
"\n"
"#endif\n"
"};\n"
"\n"
"#ifdef __cplusplus\n"
"}\n"
"#endif\n"
"\n"
"#endif // AI_CAMERA_H_INC\n";

const char* camera_h = (const char*) temp_binary_data_0;

//================== Importer.hpp ==================
static const unsigned char temp_binary_data_1[] =
"/*\n"
"---------------------------------------------------------------------------\n"
"Open Asset Import Library (assimp)\n"
"---------------------------------------------------------------------------\n"
"\n"
"Copyright (c) 2006-2025, assimp team\n"
"\n"
"All rights reserved.\n"
"\n"
"Redistribution and use of this software in source and binary forms,\n"
"with or without modification, are permitted provided that the following\n"
"conditions are met:\n"
"\n"
"* Redistributions of source code must retain the above\n"
"  copyright notice, this list of conditions and the\n"
"  following disclaimer.\n"
"\n"
"* Redistributions in binary form must reproduce the above\n"
"  copyright notice, this list of conditions and the\n"
"  following disclaimer in the documentation and/or other\n"
"  materials provided with the distribution.\n"
"\n"
"* Neither the name of the assimp team, nor the names of its\n"
"  contributors may be used to endorse or promote products\n"
"  derived from this software without specific prior\n"
"  written permission of the assimp team.\n"
"\n"
"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n"
"\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n"
"LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n"
"A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\n"
"OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\n"
"SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n"
"LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\n"
"DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\n"
"THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n"
"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n"
"OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
"---------------------------------------------------------------------------\n"
"*/\n"
"\n"
"/** @file  Importer.hpp\n"
" *  @brief Defines the C++-API to the Open Asset Import Library.\n"
" */\n"
"#pragma once\n"
"#ifndef AI_ASSIMP_HPP_INC\n"
"#define AI_ASSIMP_HPP_INC\n"
"\n"
"#ifdef __GNUC__\n"
"#pragma GCC system_header\n"
"#endif\n"
"\n"
"#ifndef __cplusplus\n"
"#error This header requires C++ to be used. Use assimp.h for plain C.\n"
"#endif // __cplusplus\n"
"\n"
"// Public ASSIMP data structures\n"
"#include <assimp/types.h>\n"
"\n"
"#include <exception>\n"
"\n"
"namespace Assimp {\n"
"// =======================================================================\n"
"// Public interface to Assimp\n"
"class Importer;\n"
"class IOStream;\n"
"class IOSystem;\n"
"class ProgressHandler;\n"
"\n"
"// =======================================================================\n"
"// Plugin development\n"
"//\n"
"// Include the following headers for the declarations:\n"
"// BaseImporter.h\n"
"// BaseProcess.h\n"
"class BaseImporter;\n"
"class BaseProcess;\n"
"class SharedPostProcessInfo;\n"
"class BatchLoader;\n"
"\n"
"// =======================================================================\n"
"// Holy stuff, only for members of the high council of the Jedi.\n"
"class ImporterPimpl;\n"
"} // namespace Assimp\n"
"\n"
"#define AI_PROPERTY_WAS_NOT_EXISTING 0xffffffff\n"
"\n"
"struct aiScene;\n"
"\n"
"// importerdesc.h\n"
"struct aiImporterDesc;\n"
"\n"
"/** @namespace Assimp Assimp's CPP-API and all internal APIs */\n"
"namespace Assimp {\n"
"\n"
"// ----------------------------------------------------------------------------------\n"
"/** CPP-API: The Importer class forms an C++ interface to the functionality of the\n"
"*   Open Asset Import Library.\n"
"*\n"
"* Create an object of this class and call ReadFile() to import a file.\n"
"* If the import succeeds, the function returns a pointer to the imported data.\n"
"* The data remains property of the object, it is intended to be accessed\n"
"* read-only. The imported data will be destroyed along with the Importer\n"
"* object. If the import fails, ReadFile() returns a nullptr pointer. In this\n"
"* case you can retrieve a human-readable error description be calling\n"
"* GetErrorString(). You can call ReadFile() multiple times with a single Importer\n"
"* instance. Actually, constructing Importer objects involves quite many\n"
"* allocations and may take some time, so it's better to reuse them as often as\n"
"* possible.\n"
"*\n"
"* If you need the Importer to do custom file handling to access the files,\n"
"* implement IOSystem and IOStream and supply an instance of your custom\n"
"* IOSystem implementation by calling SetIOHandler() before calling ReadFile().\n"
"* If you do not assign a custom IO handler, a default handler using the\n"
"* standard C++ IO logic will be used.\n"
"*\n"
"* @note One Importer instance is not thread-safe. If you use multiple\n"
"* threads for loading, each thread should maintain its own Importer instance.\n"
"*/\n"
"class ASSIMP_API Importer {\n"
"public:\n"
"    /**\n"
"     *  @brief The upper limit for hints.\n"
"     */\n"
"    static const unsigned int MaxLenHint = 200;\n"
"\n"
"public:\n"
"    // -------------------------------------------------------------------\n"
"    /** Constructor. Creates an empty importer object.\n"
"     *\n"
"     * Call ReadFile() to start the import process. The configuration\n"
"     * property table is initially empty.\n"
"     */\n"
"    Importer();\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Copy constructor.\n"
"     *\n"
"     * This copies the configuration properties of another Importer.\n"
"     * If this Importer owns a scene it won't be copied.\n"
"     * Call ReadFile() to start the import process.\n"
"     */\n"
"    Importer(const Importer &other) = delete;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Assignment operator has been deleted\n"
"     */\n"
"    Importer &operator=(const Importer &) = delete;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Destructor. The object kept ownership of the imported data,\n"
"     * which now will be destroyed along with the object.\n"
"     */\n"
"    ~Importer();\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Registers a new loader.\n"
"     *\n"
"     * @param pImp Importer to be added. The Importer instance takes\n"
"     *   ownership of the pointer, so it will be automatically deleted\n"
"     *   with the Importer instance.\n"
"     * @return AI_SUCCESS if the loader has been added. The registration\n"
"     *   fails if there is already a loader for a specific file extension.\n"
"     */\n"
"    aiReturn RegisterLoader(BaseImporter *pImp);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Unregisters a loader.\n"
"     *\n"
"     * @param pImp Importer to be unregistered.\n"
"     * @return AI_SUCCESS if the loader has been removed. The function\n"
"     *   fails if the loader is currently in use (this could happen\n"
"     *   if the #Importer instance is used by more than one thread) or\n"
"     *   if it has not yet been registered.\n"
"     */\n"
"    aiReturn UnregisterLoader(BaseImporter *pImp);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Registers a new post-process step.\n"
"     *\n"
"     * At the moment, there's a small limitation: new post processing\n"
"     * steps are added to end of the list, or in other words, executed\n"
"     * last, after all built-in steps.\n"
"     * @param pImp Post-process step to be added. The Importer instance\n"
"     *   takes ownership of the pointer, so it will be automatically\n"
"     *   deleted with the Importer instance.\n"
"     * @return AI_SUCCESS if the step has been added correctly.\n"
"     */\n"
"    aiReturn RegisterPPStep(BaseProcess *pImp);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Unregisters a post-process step.\n"
"     *\n"
"     * @param pImp Step to be unregistered.\n"
"     * @return AI_SUCCESS if the step has been removed. The function\n"
"     *   fails if the step is currently in use (this could happen\n"
"     *   if the #Importer instance is used by more than one thread) or\n"
"     *   if it has not yet been registered.\n"
"     */\n"
"    aiReturn UnregisterPPStep(BaseProcess *pImp);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Set an integer configuration property.\n"
"     * @param szName Name of the property. All supported properties\n"
"     *   are defined in the aiConfig.g header (all constants share the\n"
"     *   prefix AI_CONFIG_XXX and are simple strings).\n"
"     * @param iValue New value of the property\n"
"     * @return true if the property was set before. The new value replaces\n"
"     *   the previous value in this case.\n"
"     * @note Property of different types (float, int, string ..) are kept\n"
"     *   on different stacks, so calling SetPropertyInteger() for a\n"
"     *   floating-point property has no effect - the loader will call\n"
"     *   GetPropertyFloat() to read the property, but it won't be there.\n"
"     */\n"
"    bool SetPropertyInteger(const char *szName, int iValue);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Set a boolean configuration property. Boolean properties\n"
"     *  are stored on the integer stack internally so it's possible\n"
"     *  to set them via #SetPropertyBool and query them with\n"
"     *  #GetPropertyBool and vice versa.\n"
"     * @see SetPropertyInteger()\n"
"     */\n"
"    bool SetPropertyBool(const char *szName, bool value) {\n"
"        return SetPropertyInteger(szName, value);\n"
"    }\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Set a floating-point configuration property.\n"
"     * @see SetPropertyInteger()\n"
"     */\n"
"    bool SetPropertyFloat(const char *szName, ai_real fValue);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Set a string configuration property.\n"
"     * @see SetPropertyInteger()\n"
"     */\n"
"    bool SetPropertyString(const char *szName, const std::string &sValue);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Set a matrix configuration property.\n"
"     * @see SetPropertyInteger()\n"
"     */\n"
"    bool SetPropertyMatrix(const char *szName, const aiMatrix4x4 &sValue);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Set a pointer configuration property.\n"
"     * @see SetPropertyInteger()\n"
"     */\n"
"    bool SetPropertyPointer(const char *szName, void *sValue);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a configuration property.\n"
"     * @param szName Name of the property. All supported properties\n"
"     *   are defined in the aiConfig.g header (all constants share the\n"
"     *   prefix AI_CONFIG_XXX).\n"
"     * @param iErrorReturn Value that is returned if the property\n"
"     *   is not found.\n"
"     * @return Current value of the property\n"
"     * @note Property of different types (float, int, string ..) are kept\n"
"     *   on different lists, so calling SetPropertyInteger() for a\n"
"     *   floating-point property has no effect - the loader will call\n"
"     *   GetPropertyFloat() to read the property, but it won't be there.\n"
"     */\n"
"    int GetPropertyInteger(const char *szName,\n"
"            int iErrorReturn = 0xffffffff) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a boolean configuration property. Boolean properties\n"
"     *  are stored on the integer stack internally so it's possible\n"
"     *  to set them via #SetPropertyBool and query them with\n"
"     *  #GetPropertyBool and vice versa.\n"
"     * @see GetPropertyInteger()\n"
"     */\n"
"    bool GetPropertyBool(const char *szName, bool bErrorReturn = false) const {\n"
"        return GetPropertyInteger(szName, bErrorReturn) != 0;\n"
"    }\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a floating-point configuration property\n"
"     * @see GetPropertyInteger()\n"
"     */\n"
"    ai_real GetPropertyFloat(const char *szName,\n"
"            ai_real fErrorReturn = 10e10) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a string configuration property\n"
"     *\n"
"     *  The return value remains valid until the property is modified.\n"
"     * @see GetPropertyInteger()\n"
"     */\n"
"    std::string GetPropertyString(const char *szName,\n"
"            const std::string &sErrorReturn = std::string()) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a matrix configuration property\n"
"     *\n"
"     *  The return value remains valid until the property is modified.\n"
"     * @see GetPropertyInteger()\n"
"     */\n"
"    aiMatrix4x4 GetPropertyMatrix(const char *szName,\n"
"            const aiMatrix4x4 &sErrorReturn = aiMatrix4x4()) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a pointer configuration property\n"
"     *\n"
"     *  The return value remains valid until the property is modified.\n"
"     * @see GetPropertyInteger()\n"
"     */\n"
"    void* GetPropertyPointer(const char *szName,\n"
"        void *sErrorReturn = nullptr) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Supplies a custom IO handler to the importer to use to open and\n"
"     * access files. If you need the importer to use custom IO logic to\n"
"     * access the files, you need to provide a custom implementation of\n"
"     * IOSystem and IOFile to the importer. Then create an instance of\n"
"     * your custom IOSystem implementation and supply it by this function.\n"
"     *\n"
"     * The Importer takes ownership of the object and will destroy it\n"
"     * afterwards. The previously assigned handler will be deleted.\n"
"     * Pass nullptr to take again ownership of your IOSystem and reset Assimp\n"
"     * to use its default implementation.\n"
"     *\n"
"     * @param pIOHandler The IO handler to be used in all file accesses\n"
"     *   of the Importer.\n"
"     */\n"
"    void SetIOHandler(IOSystem *pIOHandler);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Retrieves the IO handler that is currently set.\n"
"     * You can use #IsDefaultIOHandler() to check whether the returned\n"
"     * interface is the default IO handler provided by ASSIMP. The default\n"
"     * handler is active as long the application doesn't supply its own\n"
"     * custom IO handler via #SetIOHandler().\n"
"     * @return A valid IOSystem interface, never nullptr.\n"
"     */\n"
"    IOSystem *GetIOHandler() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Checks whether a default IO handler is active\n"
"     * A default handler is active as long the application doesn't\n"
"     * supply its own custom IO handler via #SetIOHandler().\n"
"     * @return true by default\n"
"     */\n"
"    bool IsDefaultIOHandler() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Supplies a custom progress handler to the importer. This\n"
"     *  interface exposes an #Update() callback, which is called\n"
"     *  more or less periodically (please don't sue us if it\n"
"     *  isn't as periodically as you'd like it to have ...).\n"
"     *  This can be used to implement progress bars and loading\n"
"     *  timeouts.\n"
"     *  @param pHandler Progress callback interface. Pass nullptr to\n"
"     *    disable progress reporting.\n"
"     *  @note Progress handlers can be used to abort the loading\n"
"     *    at almost any time.*/\n"
"    void SetProgressHandler(ProgressHandler *pHandler);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Retrieves the progress handler that is currently set.\n"
"     * You can use #IsDefaultProgressHandler() to check whether the returned\n"
"     * interface is the default handler provided by ASSIMP. The default\n"
"     * handler is active as long the application doesn't supply its own\n"
"     * custom handler via #SetProgressHandler().\n"
"     * @return A valid ProgressHandler interface, never nullptr.\n"
"     */\n"
"    ProgressHandler *GetProgressHandler() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Checks whether a default progress handler is active\n"
"     * A default handler is active as long the application doesn't\n"
"     * supply its own custom progress handler via #SetProgressHandler().\n"
"     * @return true by default\n"
"     */\n"
"    bool IsDefaultProgressHandler() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** @brief Check whether a given set of post-processing flags\n"
"     *  is supported.\n"
"     *\n"
"     *  Some flags are mutually exclusive, others are probably\n"
"     *  not available because your excluded them from your\n"
"     *  Assimp builds. Calling this function is recommended if\n"
"     *  you're unsure.\n"
"     *\n"
"     *  @param pFlags Bitwise combination of the aiPostProcess flags.\n"
"     *  @return true if this flag combination is fine.\n"
"     */\n"
"    bool ValidateFlags(unsigned int pFlags) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Reads the given file and returns its contents if successful.\n"
"     *\n"
"     * If the call succeeds, the contents of the file are returned as a\n"
"     * pointer to an aiScene object. The returned data is intended to be\n"
"     * read-only, the importer object keeps ownership of the data and will\n"
"     * destroy it upon destruction. If the import fails, nullptr is returned.\n"
"     * A human-readable error description can be retrieved by calling\n"
"     * GetErrorString(). The previous scene will be deleted during this call.\n"
"     * @param pFile Path and filename to the file to be imported.\n"
"     * @param pFlags Optional post processing steps to be executed after\n"
"     *   a successful import. Provide a bitwise combination of the\n"
"     *   #aiPostProcessSteps flags. If you wish to inspect the imported\n"
"     *   scene first in order to fine-tune your post-processing setup,\n"
"     *   consider to use #ApplyPostProcessing().\n"
"     * @return A pointer to the imported data, nullptr if the import failed.\n"
"     *   The pointer to the scene remains in possession of the Importer\n"
"     *   instance. Use GetOrphanedScene() to take ownership of it.\n"
"     *\n"
"     * @note Assimp is able to determine the file format of a file\n"
"     * automatically.\n"
"     */\n"
"    const aiScene *ReadFile(\n"
"            const char *pFile,\n"
"            unsigned int pFlags);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Reads the given file from a memory buffer and returns its\n"
"     *  contents if successful.\n"
"     *\n"
"     * If the call succeeds, the contents of the file are returned as a\n"
"     * pointer to an aiScene object. The returned data is intended to be\n"
"     * read-only, the importer object keeps ownership of the data and will\n"
"     * destroy it upon destruction. If the import fails, nullptr is returned.\n"
"     * A human-readable error description can be retrieved by calling\n"
"     * GetErrorString(). The previous scene will be deleted during this call.\n"
"     * Calling this method doesn't affect the active IOSystem.\n"
"     * @param pBuffer Pointer to the file data\n"
"     * @param pLength Length of pBuffer, in bytes\n"
"     * @param pFlags Optional post processing steps to be executed after\n"
"     *   a successful import. Provide a bitwise combination of the\n"
"     *   #aiPostProcessSteps flags. If you wish to inspect the imported\n"
"     *   scene first in order to fine-tune your post-processing setup,\n"
"     *   consider to use #ApplyPostProcessing().\n"
"     * @param pHint An additional hint to the library. If this is a non\n"
"     *   empty string, the library looks for a loader to support\n"
"     *   the file extension specified by pHint and passes the file to\n"
"     *   the first matching loader. If this loader is unable to completely\n"
"     *   the request, the library continues and tries to determine the\n"
"     *   file format on its own, a task that may or may not be successful.\n"
"     *   Check the return value, and you'll know ...\n"
"     * @return A pointer to the imported data, nullptr if the import failed.\n"
"     *   The pointer to the scene remains in possession of the Importer\n"
"     *   instance. Use GetOrphanedScene() to take ownership of it.\n"
"     *\n"
"     * @note This is a straightforward way to decode models from memory\n"
"     * buffers, but it doesn't handle model formats that spread their\n"
"     * data across multiple files or even directories. Examples include\n"
"     * OBJ or MD3, which outsource parts of their material info into\n"
"     * external scripts. If you need full functionality, provide\n"
"     * a custom IOSystem to make Assimp find these files and use\n"
"     * the regular ReadFile() API.\n"
"     */\n"
"    const aiScene *ReadFileFromMemory(\n"
"            const void *pBuffer,\n"
"            size_t pLength,\n"
"            unsigned int pFlags,\n"
"            const char *pHint = \"\");\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Apply post-processing to an already-imported scene.\n"
"     *\n"
"     *  This is strictly equivalent to calling #ReadFile() with the same\n"
"     *  flags. However, you can use this separate function to inspect\n"
"     *  the imported scene first to fine-tune your post-processing setup.\n"
"     *  @param pFlags Provide a bitwise combination of the\n"
"     *   #aiPostProcessSteps flags.\n"
"     *  @return A pointer to the post-processed data. This is still the\n"
"     *   same as the pointer returned by #ReadFile(). However, if\n"
"     *   post-processing fails, the scene could now be nullptr.\n"
"     *   That's quite a rare case, post processing steps are not really\n"
"     *   designed to 'fail'. To be exact, the #aiProcess_ValidateDS\n"
"     *   flag is currently the only post processing step which can actually\n"
"     *   cause the scene to be reset to nullptr.\n"
"     *\n"
"     *  @note The method does nothing if no scene is currently bound\n"
"     *    to the #Importer instance.  */\n"
"    const aiScene *ApplyPostProcessing(unsigned int pFlags);\n"
"\n"
"    const aiScene *ApplyCustomizedPostProcessing(BaseProcess *rootProcess, bool requestValidation);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** @brief Reads the given file and returns its contents if successful.\n"
"     *\n"
"     * This function is provided for backward compatibility.\n"
"     * See the const char* version for detailed docs.\n"
"     * @see ReadFile(const char*, pFlags)  */\n"
"    const aiScene *ReadFile(\n"
"            const std::string &pFile,\n"
"            unsigned int pFlags);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Frees the current scene.\n"
"     *\n"
"     *  The function does nothing if no scene has previously been\n"
"     *  read via ReadFile(). FreeScene() is called automatically by the\n"
"     *  destructor and ReadFile() itself.  */\n"
"    void FreeScene();\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Returns an error description of an error that occurred in ReadFile().\n"
"     *\n"
"     * Returns an empty string if no error occurred.\n"
"     * @return A description of the last error, an empty string if no\n"
"     *   error occurred. The string is never nullptr.\n"
"     *\n"
"     * @note The returned function remains valid until one of the\n"
"     * following methods is called: #ReadFile(), #FreeScene(). */\n"
"    const char *GetErrorString() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Returns an exception if one occurred during import.\n"
"     *\n"
"     * @return The last exception which occurred.\n"
"     *\n"
"     * @note The returned value remains valid until one of the\n"
"     * following methods is called: #ReadFile(), #FreeScene(). */\n"
"    const std::exception_ptr& GetException() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Returns the scene loaded by the last successful call to ReadFile()\n"
"     *\n"
"     * @return Current scene or nullptr if there is currently no scene loaded */\n"
"    const aiScene *GetScene() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Returns the scene loaded by the last successful call to ReadFile()\n"
"     *  and releases the scene from the ownership of the Importer\n"
"     *  instance. The application is now responsible for deleting the\n"
"     *  scene. Any further calls to GetScene() or GetOrphanedScene()\n"
"     *  will return nullptr - until a new scene has been loaded via ReadFile().\n"
"     *\n"
"     * @return Current scene or nullptr if there is currently no scene loaded\n"
"     * @note Use this method with maximal caution, and only if you have to.\n"
"     *   By design, aiScene's are exclusively maintained, allocated and\n"
"     *   deallocated by Assimp and no one else. The reasoning behind this\n"
"     *   is the golden rule that deallocations should always be done\n"
"     *   by the module that did the original allocation because heaps\n"
"     *   are not necessarily shared. GetOrphanedScene() enforces you\n"
"     *   to delete the returned scene by yourself, but this will only\n"
"     *   be fine if and only if you're using the same heap as assimp.\n"
"     *   On Windows, it's typically fine provided everything is linked\n"
"     *   against the multithreaded-dll version of the runtime library.\n"
"     *   It will work as well for static linkage with Assimp.*/\n"
"    aiScene *GetOrphanedScene();\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Returns whether a given file extension is supported by ASSIMP.\n"
"     *\n"
"     * @param szExtension Extension to be checked.\n"
"     *   Must include a trailing dot '.'. Example: \".3ds\", \".md3\".\n"
"     *   Cases-insensitive.\n"
"     * @return true if the extension is supported, false otherwise */\n"
"    bool IsExtensionSupported(const char *szExtension) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** @brief Returns whether a given file extension is supported by ASSIMP.\n"
"     *\n"
"     * This function is provided for backward compatibility.\n"
"     * See the const char* version for detailed and up-to-date docs.\n"
"     * @see IsExtensionSupported(const char*) */\n"
"    inline bool IsExtensionSupported(const std::string &szExtension) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get a full list of all file extensions supported by ASSIMP.\n"
"     *\n"
"     * If a file extension is contained in the list this does of course not\n"
"     * mean that ASSIMP is able to load all files with this extension ---\n"
"     * it simply means there is an importer loaded which claims to handle\n"
"     * files with this file extension.\n"
"     * @param szOut String to receive the extension list.\n"
"     *   Format of the list: \"*.3ds;*.obj;*.dae\". This is useful for\n"
"     *   use with the WinAPI call GetOpenFileName(Ex). */\n"
"    void GetExtensionList(aiString &szOut) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** @brief Get a full list of all file extensions supported by ASSIMP.\n"
"     *\n"
"     * This function is provided for backward compatibility.\n"
"     * See the aiString version for detailed and up-to-date docs.\n"
"     * @see GetExtensionList(aiString&)*/\n"
"    inline void GetExtensionList(std::string &szOut) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get the number of importers currently registered with Assimp. */\n"
"    size_t GetImporterCount() const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Get meta data for the importer corresponding to a specific index..\n"
"    *\n"
"    *  For the declaration of #aiImporterDesc, include <assimp/importerdesc.h>.\n"
"    *  @param index Index to query, must be within [0,GetImporterCount())\n"
"    *  @return Importer meta data structure, nullptr if the index does not\n"
"    *     exist or if the importer doesn't offer meta information (\n"
"    *     importers may do this at the cost of being hated by their peers).*/\n"
"    const aiImporterDesc *GetImporterInfo(size_t index) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Find the importer corresponding to a specific index.\n"
"    *\n"
"    *  @param index Index to query, must be within [0,GetImporterCount())\n"
"    *  @return Importer instance. nullptr if the index does not\n"
"    *     exist. */\n"
"    BaseImporter *GetImporter(size_t index) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Find the importer corresponding to a specific file extension.\n"
"    *\n"
"    *  This is quite similar to #IsExtensionSupported except a\n"
"    *  BaseImporter instance is returned.\n"
"    *  @param szExtension Extension to check for. The following formats\n"
"    *    are recognized (BAH being the file extension): \"BAH\" (comparison\n"
"    *    is case-insensitive), \".bah\", \"*.bah\" (wild card and dot\n"
"    *    characters at the beginning of the extension are skipped).\n"
"    *  @return nullptr if no importer is found*/\n"
"    BaseImporter *GetImporter(const char *szExtension) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Find the importer index corresponding to a specific file extension.\n"
"    *\n"
"    *  @param szExtension Extension to check for. The following formats\n"
"    *    are recognized (BAH being the file extension): \"BAH\" (comparison\n"
"    *    is case-insensitive), \".bah\", \"*.bah\" (wild card and dot\n"
"    *    characters at the beginning of the extension are skipped).\n"
"    *  @return (size_t)-1 if no importer is found */\n"
"    size_t GetImporterIndex(const char *szExtension) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Returns the storage allocated by ASSIMP to hold the scene data\n"
"     * in memory.\n"
"     *\n"
"     * This refers to the currently loaded file, see #ReadFile().\n"
"     * @param in Data structure to be filled.\n"
"     * @note The returned memory statistics refer to the actual\n"
"     *   size of the use data of the aiScene. Heap-related overhead\n"
"     *   is (naturally) not included.*/\n"
"    void GetMemoryRequirements(aiMemoryInfo &in) const;\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Enables \"extra verbose\" mode.\n"
"     *\n"
"     * 'Extra verbose' means the data structure is validated after *every*\n"
"     * single post processing step to make sure everyone modifies the data\n"
"     * structure in a well-defined manner. This is a debug feature and not\n"
"     * intended for use in production environments. */\n"
"    void SetExtraVerbose(bool bDo);\n"
"\n"
"    // -------------------------------------------------------------------\n"
"    /** Private, do not use. */\n"
"    ImporterPimpl *Pimpl() { return pimpl; }\n"
"    const ImporterPimpl *Pimpl() const { return pimpl; }\n"
"\n"
"protected:\n"
"    // Just because we don't want you to know how we're hacking around.\n"
"    ImporterPimpl *pimpl;\n"
"}; //! class Importer\n"
"\n"
"// ----------------------------------------------------------------------------\n"
"// For compatibility, the interface of some functions taking a std::string was\n"
"// changed to const char* to avoid crashes between binary incompatible STL\n"
"// versions. This code her is inlined,  so it shouldn't cause any problems.\n"
"// ----------------------------------------------------------------------------\n"
"\n"
"// ----------------------------------------------------------------------------\n"
"AI_FORCE_INLINE const aiScene *Importer::ReadFile(const std::string &pFile, unsigned int pFlags) {\n"
"    return ReadFile(pFile.c_str(), pFlags);\n"
"}\n"
"// ----------------------------------------------------------------------------\n"
"AI_FORCE_INLINE void Importer::GetExtensionList(std::string &szOut) const {\n"
"    aiString s;\n"
"    GetExtensionList(s);\n"
"    szOut = s.data;\n"
"}\n"
"// ----------------------------------------------------------------------------\n"
"AI_FORCE_INLINE bool Importer::IsExtensionSupported(const std::string &szExtension) const {\n"
"    return IsExtensionSupported(szExtension.c_str());\n"
"}\n"
"\n"
"} // namespace Assimp\n"
"\n"
"#endif // AI_ASSIMP_HPP_INC\n";

const char* Importer_hpp = (const char*) temp_binary_data_1;

//================== mesh.h ==================
static const unsigned char temp_binary_data_2[] =
{ 47,42,10,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,79,112,101,110,
32,65,115,115,101,116,32,73,109,112,111,114,116,32,76,105,98,114,97,114,121,32,40,97,115,115,105,109,112,41,10,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,10,67,111,112,121,114,105,103,104,116,32,40,99,41,32,50,48,48,54,45,50,48,50,53,44,32,97,115,115,105,109,112,32,116,101,97,109,10,10,65,108,108,32,114,105,103,104,
116,115,32,114,101,115,101,114,118,101,100,46,10,10,82,101,100,105,115,116,114,105,98,117,116,105,111,110,32,97,110,100,32,117,115,101,32,111,102,32,116,104,105,115,32,115,111,102,116,119,97,114,101,32,105,110,32,115,111,117,114,99,101,32,97,110,100,
32,98,105,110,97,114,121,32,102,111,114,109,115,44,10,119,105,116,104,32,111,114,32,119,105,116,104,111,117,116,32,109,111,100,105,102,105,99,97,116,105,111,110,44,32,97,114,101,32,112,101,114,109,105,116,116,101,100,32,112,114,111,118,105,100,101,100,
32,116,104,97,116,32,116,104,101,32,102,111,108,108,111,119,105,110,103,10,99,111,110,100,105,116,105,111,110,115,32,97,114,101,32,109,101,116,58,10,10,42,32,82,101,100,105,115,116,114,105,98,117,116,105,111,110,115,32,111,102,32,115,111,117,114,99,101,
32,99,111,100,101,32,109,117,115,116,32,114,101,116,97,105,110,32,116,104,101,32,97,98,111,118,101,10,32,32,99,111,112,121,114,105,103,104,116,32,110,111,116,105,99,101,44,32,116,104,105,115,32,108,105,115,116,32,111,102,32,99,111,110,100,105,116,105,
111,110,115,32,97,110,100,32,116,104,101,10,32,32,102,111,108,108,111,119,105,110,103,32,100,105,115,99,108,97,105,109,101,114,46,10,10,42,32,82,101,100,105,115,116,114,105,98,117,116,105,111,110,115,32,105,110,32,98,105,110,97,114,121,32,102,111,114,
109,32,109,117,115,116,32,114,101,112,114,111,100,117,99,101,32,116,104,101,32,97,98,111,118,101,10,32,32,99,111,112,121,114,105,103,104,116,32,110,111,116,105,99,101,44,32,116,104,105,115,32,108,105,115,116,32,111,102,32,99,111,110,100,105,116,105,111,
110,115,32,97,110,100,32,116,104,101,10,32,32,102,111,108,108,111,119,105,110,103,32,100,105,115,99,108,97,105,109,101,114,32,105,110,32,116,104,101,32,100,111,99,117,109,101,110,116,97,116,105,111,110,32,97,110,100,47,111,114,32,111,116,104,101,114,
10,32,32,109,97,116,101,114,105,97,108,115,32,112,114,111,118,105,100,101,100,32,119,105,116,104,32,116,104,101,32,100,105,115,116,114,105,98,117,116,105,111,110,46,10,10,42,32,78,101,105,116,104,101,114,32,116,104,101,32,110,97,109,101,32,111,102,32,
116,104,101,32,97,115,115,105,109,112,32,116,101,97,109,44,32,110,111,114,32,116,104,101,32,110,97,109,101,115,32,111,102,32,105,116,115,10,32,32,99,111,110,116,114,105,98,117,116,111,114,115,32,109,97,121,32,98,101,32,117,115,101,100,32,116,111,32,101,
110,100,111,114,115,101,32,111,114,32,112,114,111,109,111,116,101,32,112,114,111,100,117,99,116,115,10,32,32,100,101,114,105,118,101,100,32,102,114,111,109,32,116,104,105,115,32,115,111,102,116,119,97,114,101,32,119,105,116,104,111,117,116,32,115,112,
101,99,105,102,105,99,32,112,114,105,111,114,10,32,32,119,114,105,116,116,101,110,32,112,101,114,109,105,115,115,105,111,110,32,111,102,32,116,104,101,32,97,115,115,105,109,112,32,116,101,97,109,46,10,10,84,72,73,83,32,83,79,70,84,87,65,82,69,32,73,83,
32,80,82,79,86,73,68,69,68,32,66,89,32,84,72,69,32,67,79,80,89,82,73,71,72,84,32,72,79,76,68,69,82,83,32,65,78,68,32,67,79,78,84,82,73,66,85,84,79,82,83,10,34,65,83,32,73,83,34,32,65,78,68,32,65,78,89,32,69,88,80,82,69,83,83,32,79,82,32,73,77,80,76,73,
69,68,32,87,65,82,82,65,78,84,73,69,83,44,32,73,78,67,76,85,68,73,78,71,44,32,66,85,84,32,78,79,84,10,76,73,77,73,84,69,68,32,84,79,44,32,84,72,69,32,73,77,80,76,73,69,68,32,87,65,82,82,65,78,84,73,69,83,32,79,70,32,77,69,82,67,72,65,78,84,65,66,73,76,
73,84,89,32,65,78,68,32,70,73,84,78,69,83,83,32,70,79,82,10,65,32,80,65,82,84,73,67,85,76,65,82,32,80,85,82,80,79,83,69,32,65,82,69,32,68,73,83,67,76,65,73,77,69,68,46,32,73,78,32,78,79,32,69,86,69,78,84,32,83,72,65,76,76,32,84,72,69,32,67,79,80,89,82,
73,71,72,84,10,79,87,78,69,82,32,79,82,32,67,79,78,84,82,73,66,85,84,79,82,83,32,66,69,32,76,73,65,66,76,69,32,70,79,82,32,65,78,89,32,68,73,82,69,67,84,44,32,73,78,68,73,82,69,67,84,44,32,73,78,67,73,68,69,78,84,65,76,44,10,83,80,69,67,73,65,76,44,32,
69,88,69,77,80,76,65,82,89,44,32,79,82,32,67,79,78,83,69,81,85,69,78,84,73,65,76,32,68,65,77,65,71,69,83,32,40,73,78,67,76,85,68,73,78,71,44,32,66,85,84,32,78,79,84,10,76,73,77,73,84,69,68,32,84,79,44,32,80,82,79,67,85,82,69,77,69,78,84,32,79,70,32,83,
85,66,83,84,73,84,85,84,69,32,71,79,79,68,83,32,79,82,32,83,69,82,86,73,67,69,83,59,32,76,79,83,83,32,79,70,32,85,83,69,44,10,68,65,84,65,44,32,79,82,32,80,82,79,70,73,84,83,59,32,79,82,32,66,85,83,73,78,69,83,83,32,73,78,84,69,82,82,85,80,84,73,79,78,
41,32,72,79,87,69,86,69,82,32,67,65,85,83,69,68,32,65,78,68,32,79,78,32,65,78,89,10,84,72,69,79,82,89,32,79,70,32,76,73,65,66,73,76,73,84,89,44,32,87,72,69,84,72,69,82,32,73,78,32,67,79,78,84,82,65,67,84,44,32,83,84,82,73,67,84,32,76,73,65,66,73,76,73,
84,89,44,32,79,82,32,84,79,82,84,10,40,73,78,67,76,85,68,73,78,71,32,78,69,71,76,73,71,69,78,67,69,32,79,82,32,79,84,72,69,82,87,73,83,69,41,32,65,82,73,83,73,78,71,32,73,78,32,65,78,89,32,87,65,89,32,79,85,84,32,79,70,32,84,72,69,32,85,83,69,10,79,70,
32,84,72,73,83,32,83,79,70,84,87,65,82,69,44,32,69,86,69,78,32,73,70,32,65,68,86,73,83,69,68,32,79,70,32,84,72,69,32,80,79,83,83,73,66,73,76,73,84,89,32,79,70,32,83,85,67,72,32,68,65,77,65,71,69,46,10,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,42,47,10,10,47,42,42,32,64,102,105,108,101,32,109,101,115,104,46,104,10,32,
42,32,32,64,98,114,105,101,102,32,68,101,99,108,97,114,101,115,32,116,104,101,32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,115,32,105,110,32,119,104,105,99,104,32,116,104,101,32,105,109,112,111,114,116,101,100,32,103,101,111,109,101,116,114,
121,32,105,115,10,32,32,32,32,114,101,116,117,114,110,101,100,32,98,121,32,65,83,83,73,77,80,58,32,97,105,77,101,115,104,44,32,97,105,70,97,99,101,32,97,110,100,32,97,105,66,111,110,101,32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,115,46,10,
32,42,47,10,35,112,114,97,103,109,97,32,111,110,99,101,10,35,105,102,110,100,101,102,32,65,73,95,77,69,83,72,95,72,95,73,78,67,10,35,100,101,102,105,110,101,32,65,73,95,77,69,83,72,95,72,95,73,78,67,10,10,35,105,102,100,101,102,32,95,95,71,78,85,67,95,
95,10,35,112,114,97,103,109,97,32,71,67,67,32,115,121,115,116,101,109,95,104,101,97,100,101,114,10,35,101,110,100,105,102,10,10,35,105,102,32,100,101,102,105,110,101,100,40,95,77,83,67,95,86,69,82,41,32,38,38,32,95,77,83,67,95,86,69,82,32,60,32,49,57,
48,48,10,35,112,114,97,103,109,97,32,119,97,114,110,105,110,103,40,100,105,115,97,98,108,101,32,58,32,52,51,53,49,41,10,35,101,110,100,105,102,32,47,47,32,95,77,83,67,95,86,69,82,10,10,35,105,110,99,108,117,100,101,32,60,97,115,115,105,109,112,47,97,
97,98,98,46,104,62,10,35,105,110,99,108,117,100,101,32,60,97,115,115,105,109,112,47,116,121,112,101,115,46,104,62,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,35,105,110,99,108,117,100,101,32,60,117,110,111,114,100,101,
114,101,100,95,115,101,116,62,10,10,101,120,116,101,114,110,32,34,67,34,32,123,10,35,101,110,100,105,102,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,47,32,76,105,109,105,116,115,46,32,84,104,101,115,101,32,118,97,108,117,101,115,32,97,114,101,32,114,101,113,117,105,114,101,100,32,116,111,32,109,97,116,
99,104,32,116,104,101,32,115,101,116,116,105,110,103,115,32,65,115,115,105,109,112,32,119,97,115,10,47,47,32,99,111,109,112,105,108,101,100,32,97,103,97,105,110,115,116,46,32,84,104,101,114,101,102,111,114,101,44,32,100,111,32,110,111,116,32,114,101,
100,101,102,105,110,101,32,116,104,101,109,32,117,110,108,101,115,115,32,121,111,117,32,98,117,105,108,100,32,116,104,101,10,47,47,32,108,105,98,114,97,114,121,32,102,114,111,109,32,115,111,117,114,99,101,32,117,115,105,110,103,32,116,104,101,32,115,
97,109,101,32,100,101,102,105,110,105,116,105,111,110,115,46,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,10,47,42,42,32,64,100,101,102,32,65,73,95,77,65,88,95,70,65,67,69,95,73,78,68,73,67,69,83,10,32,42,32,32,77,97,120,105,109,117,109,32,110,117,109,98,101,114,32,111,102,32,105,110,100,105,99,101,115,32,
112,101,114,32,102,97,99,101,32,40,112,111,108,121,103,111,110,41,46,32,42,47,10,10,35,105,102,110,100,101,102,32,65,73,95,77,65,88,95,70,65,67,69,95,73,78,68,73,67,69,83,10,35,100,101,102,105,110,101,32,65,73,95,77,65,88,95,70,65,67,69,95,73,78,68,73,
67,69,83,32,48,120,55,102,102,102,10,35,101,110,100,105,102,10,10,47,42,42,32,64,100,101,102,32,65,73,95,77,65,88,95,66,79,78,69,95,87,69,73,71,72,84,83,10,32,42,32,32,77,97,120,105,109,117,109,32,110,117,109,98,101,114,32,111,102,32,105,110,100,105,
99,101,115,32,112,101,114,32,102,97,99,101,32,40,112,111,108,121,103,111,110,41,46,32,42,47,10,10,35,105,102,110,100,101,102,32,65,73,95,77,65,88,95,66,79,78,69,95,87,69,73,71,72,84,83,10,35,100,101,102,105,110,101,32,65,73,95,77,65,88,95,66,79,78,69,
95,87,69,73,71,72,84,83,32,48,120,55,102,102,102,102,102,102,102,10,35,101,110,100,105,102,10,10,47,42,42,32,64,100,101,102,32,65,73,95,77,65,88,95,86,69,82,84,73,67,69,83,10,32,42,32,32,77,97,120,105,109,117,109,32,110,117,109,98,101,114,32,111,102,
32,118,101,114,116,105,99,101,115,32,112,101,114,32,109,101,115,104,46,32,32,42,47,10,10,35,105,102,110,100,101,102,32,65,73,95,77,65,88,95,86,69,82,84,73,67,69,83,10,35,100,101,102,105,110,101,32,65,73,95,77,65,88,95,86,69,82,84,73,67,69,83,32,48,120,
55,102,102,102,102,102,102,102,10,35,101,110,100,105,102,10,10,47,42,42,32,64,100,101,102,32,65,73,95,77,65,88,95,70,65,67,69,83,10,32,42,32,32,77,97,120,105,109,117,109,32,110,117,109,98,101,114,32,111,102,32,102,97,99,101,115,32,112,101,114,32,109,
101,115,104,46,32,42,47,10,10,35,105,102,110,100,101,102,32,65,73,95,77,65,88,95,70,65,67,69,83,10,35,100,101,102,105,110,101,32,65,73,95,77,65,88,95,70,65,67,69,83,32,48,120,55,102,102,102,102,102,102,102,10,35,101,110,100,105,102,10,10,47,42,42,32,
64,100,101,102,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,10,32,42,32,32,83,117,112,112,111,114,116,101,100,32,110,117,109,98,101,114,32,111,102,32,118,101,114,116,101,120,32,99,111,108,111,114,32,115,101,116,
115,32,112,101,114,32,109,101,115,104,46,32,42,47,10,10,35,105,102,110,100,101,102,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,10,35,100,101,102,105,110,101,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,
67,79,76,79,82,95,83,69,84,83,32,48,120,56,10,35,101,110,100,105,102,32,47,47,32,33,33,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,10,10,47,42,42,32,64,100,101,102,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,
70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,10,32,42,32,32,83,117,112,112,111,114,116,101,100,32,110,117,109,98,101,114,32,111,102,32,116,101,120,116,117,114,101,32,99,111,111,114,100,32,115,101,116,115,32,40,85,86,40,87,41,32,99,104,97,110,110,101,
108,115,41,32,112,101,114,32,109,101,115,104,32,42,47,10,10,35,105,102,110,100,101,102,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,10,35,100,101,102,105,110,101,32,65,73,95,77,65,88,95,78,85,77,66,69,82,
95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,32,48,120,56,10,35,101,110,100,105,102,32,47,47,32,33,33,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,42,10,32,42,32,64,98,114,105,101,102,32,65,32,115,105,
110,103,108,101,32,102,97,99,101,32,105,110,32,97,32,109,101,115,104,44,32,114,101,102,101,114,114,105,110,103,32,116,111,32,109,117,108,116,105,112,108,101,32,118,101,114,116,105,99,101,115,46,10,32,42,10,32,42,32,73,102,32,109,78,117,109,73,110,100,
105,99,101,115,32,105,115,32,51,44,32,119,101,32,99,97,108,108,32,116,104,101,32,102,97,99,101,32,39,116,114,105,97,110,103,108,101,39,44,32,102,111,114,32,109,78,117,109,73,110,100,105,99,101,115,32,62,32,51,10,32,42,32,105,116,39,115,32,99,97,108,108,
101,100,32,39,112,111,108,121,103,111,110,39,32,40,104,101,121,44,32,116,104,97,116,39,115,32,106,117,115,116,32,97,32,100,101,102,105,110,105,116,105,111,110,33,41,46,10,32,42,32,60,98,114,62,10,32,42,32,97,105,77,101,115,104,58,58,109,80,114,105,109,
105,116,105,118,101,84,121,112,101,115,32,99,97,110,32,98,101,32,113,117,101,114,105,101,100,32,116,111,32,113,117,105,99,107,108,121,32,101,120,97,109,105,110,101,32,119,104,105,99,104,32,116,121,112,101,115,32,111,102,10,32,42,32,112,114,105,109,105,
116,105,118,101,32,97,114,101,32,97,99,116,117,97,108,108,121,32,112,114,101,115,101,110,116,32,105,110,32,97,32,109,101,115,104,46,32,84,104,101,32,35,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,101,32,102,108,97,103,10,32,
42,32,101,120,101,99,117,116,101,115,32,97,32,115,112,101,99,105,97,108,32,112,111,115,116,45,112,114,111,99,101,115,115,105,110,103,32,97,108,103,111,114,105,116,104,109,32,119,104,105,99,104,32,115,112,108,105,116,115,32,109,101,115,104,101,115,32,
119,105,116,104,10,32,42,32,42,100,105,102,102,101,114,101,110,116,42,32,112,114,105,109,105,116,105,118,101,32,116,121,112,101,115,32,109,105,120,101,100,32,117,112,32,40,101,46,103,46,32,108,105,110,101,115,32,97,110,100,32,116,114,105,97,110,103,108,
101,115,41,32,105,110,32,115,101,118,101,114,97,108,10,32,42,32,39,99,108,101,97,110,39,32,115,117,98,45,109,101,115,104,101,115,46,32,70,117,114,116,104,101,114,109,111,114,101,32,116,104,101,114,101,32,105,115,32,97,32,99,111,110,102,105,103,117,114,
97,116,105,111,110,32,111,112,116,105,111,110,32,40,10,32,42,32,35,65,73,95,67,79,78,70,73,71,95,80,80,95,83,66,80,95,82,69,77,79,86,69,41,32,116,111,32,102,111,114,99,101,32,35,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,
101,32,116,111,32,114,101,109,111,118,101,10,32,42,32,115,112,101,99,105,102,105,99,32,107,105,110,100,115,32,111,102,32,112,114,105,109,105,116,105,118,101,115,32,102,114,111,109,32,116,104,101,32,105,109,112,111,114,116,101,100,32,115,99,101,110,101,
44,32,99,111,109,112,108,101,116,101,108,121,32,97,110,100,32,102,111,114,101,118,101,114,46,10,32,42,32,73,110,32,109,97,110,121,32,99,97,115,101,115,32,121,111,117,39,108,108,32,112,114,111,98,97,98,108,121,32,119,97,110,116,32,116,111,32,115,101,116,
32,116,104,105,115,32,115,101,116,116,105,110,103,32,116,111,10,32,42,32,64,99,111,100,101,10,32,42,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,76,73,78,69,124,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,80,79,73,78,
84,10,32,42,32,64,101,110,100,99,111,100,101,10,32,42,32,84,111,103,101,116,104,101,114,32,119,105,116,104,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,32,102,108,97,103,32,121,111,117,32,99,97,110,
32,116,104,101,110,32,98,101,32,115,117,114,101,32,116,104,97,116,10,32,42,32,35,97,105,70,97,99,101,58,58,109,78,117,109,73,110,100,105,99,101,115,32,105,115,32,97,108,119,97,121,115,32,51,46,10,32,42,32,64,110,111,116,101,32,84,97,107,101,32,97,32,
108,111,111,107,32,97,116,32,116,104,101,32,64,108,105,110,107,32,100,97,116,97,32,68,97,116,97,32,83,116,114,117,99,116,117,114,101,115,32,112,97,103,101,32,64,101,110,100,108,105,110,107,32,102,111,114,10,32,42,32,109,111,114,101,32,105,110,102,111,
114,109,97,116,105,111,110,32,111,110,32,116,104,101,32,108,97,121,111,117,116,32,97,110,100,32,119,105,110,100,105,110,103,32,111,114,100,101,114,32,111,102,32,97,32,102,97,99,101,46,10,32,42,47,10,115,116,114,117,99,116,32,97,105,70,97,99,101,32,123,
10,32,32,32,32,47,47,33,32,78,117,109,98,101,114,32,111,102,32,105,110,100,105,99,101,115,32,100,101,102,105,110,105,110,103,32,116,104,105,115,32,102,97,99,101,46,10,32,32,32,32,47,47,33,32,84,104,101,32,109,97,120,105,109,117,109,32,118,97,108,117,
101,32,102,111,114,32,116,104,105,115,32,109,101,109,98,101,114,32,105,115,32,35,65,73,95,77,65,88,95,70,65,67,69,95,73,78,68,73,67,69,83,46,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,73,110,100,105,99,101,115,59,
10,10,32,32,32,32,47,47,33,32,80,111,105,110,116,101,114,32,116,111,32,116,104,101,32,105,110,100,105,99,101,115,32,97,114,114,97,121,46,32,83,105,122,101,32,111,102,32,116,104,101,32,97,114,114,97,121,32,105,115,32,103,105,118,101,110,32,105,110,32,
110,117,109,73,110,100,105,99,101,115,46,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,42,109,73,110,100,105,99,101,115,59,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,10,32,32,32,32,47,47,33,32,64,98,
114,105,101,102,32,68,101,102,97,117,108,116,32,99,111,110,115,116,114,117,99,116,111,114,46,10,32,32,32,32,97,105,70,97,99,101,40,41,32,65,73,95,78,79,95,69,88,67,69,80,84,10,32,32,32,32,32,32,32,32,32,32,32,32,58,32,109,78,117,109,73,110,100,105,99,
101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,73,110,100,105,99,101,115,40,110,117,108,108,112,116,114,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,
105,101,102,32,68,101,102,97,117,108,116,32,100,101,115,116,114,117,99,116,111,114,46,32,68,101,108,101,116,101,32,116,104,101,32,105,110,100,101,120,32,97,114,114,97,121,10,32,32,32,32,126,97,105,70,97,99,101,40,41,32,123,10,32,32,32,32,32,32,32,32,
100,101,108,101,116,101,91,93,32,109,73,110,100,105,99,101,115,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,111,112,121,32,99,111,110,115,116,114,117,99,116,111,114,46,32,67,111,112,121,32,116,104,101,32,105,110,100,
101,120,32,97,114,114,97,121,10,32,32,32,32,97,105,70,97,99,101,40,99,111,110,115,116,32,97,105,70,97,99,101,32,38,111,41,32,58,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,73,110,100,105,99,101,115,40,48,41,44,32,109,73,110,100,105,99,101,115,
40,110,117,108,108,112,116,114,41,32,123,10,32,32,32,32,32,32,32,32,42,116,104,105,115,32,61,32,111,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,65,115,115,105,103,110,109,101,110,116,32,111,112,101,114,97,116,111,114,
46,32,67,111,112,121,32,116,104,101,32,105,110,100,101,120,32,97,114,114,97,121,10,32,32,32,32,97,105,70,97,99,101,32,38,111,112,101,114,97,116,111,114,61,40,99,111,110,115,116,32,97,105,70,97,99,101,32,38,111,41,32,123,10,32,32,32,32,32,32,32,32,105,
102,32,40,38,111,32,61,61,32,116,104,105,115,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,42,116,104,105,115,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,73,110,100,
105,99,101,115,59,10,32,32,32,32,32,32,32,32,109,78,117,109,73,110,100,105,99,101,115,32,61,32,111,46,109,78,117,109,73,110,100,105,99,101,115,59,10,32,32,32,32,32,32,32,32,105,102,32,40,109,78,117,109,73,110,100,105,99,101,115,41,32,123,10,32,32,32,
32,32,32,32,32,32,32,32,32,109,73,110,100,105,99,101,115,32,61,32,110,101,119,32,117,110,115,105,103,110,101,100,32,105,110,116,91,109,78,117,109,73,110,100,105,99,101,115,93,59,10,32,32,32,32,32,32,32,32,32,32,32,32,58,58,109,101,109,99,112,121,40,109,
73,110,100,105,99,101,115,44,32,111,46,109,73,110,100,105,99,101,115,44,32,109,78,117,109,73,110,100,105,99,101,115,32,42,32,115,105,122,101,111,102,40,117,110,115,105,103,110,101,100,32,105,110,116,41,41,59,10,32,32,32,32,32,32,32,32,125,32,101,108,
115,101,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,109,73,110,100,105,99,101,115,32,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,42,116,104,105,115,59,10,32,32,32,32,125,
10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,111,109,112,97,114,105,115,111,110,32,111,112,101,114,97,116,111,114,46,32,67,104,101,99,107,115,32,119,104,101,116,104,101,114,32,116,104,101,32,105,110,100,101,120,32,97,114,114,97,121,32,111,
102,32,116,119,111,32,102,97,99,101,115,32,105,115,32,105,100,101,110,116,105,99,97,108,46,10,32,32,32,32,98,111,111,108,32,111,112,101,114,97,116,111,114,61,61,40,99,111,110,115,116,32,97,105,70,97,99,101,32,38,111,41,32,99,111,110,115,116,32,123,10,
32,32,32,32,32,32,32,32,105,102,32,40,109,73,110,100,105,99,101,115,32,61,61,32,111,46,109,73,110,100,105,99,101,115,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,116,114,117,101,59,10,32,32,32,32,32,32,32,32,125,10,10,32,
32,32,32,32,32,32,32,105,102,32,40,110,117,108,108,112,116,114,32,33,61,32,109,73,110,100,105,99,101,115,32,38,38,32,109,78,117,109,73,110,100,105,99,101,115,32,33,61,32,111,46,109,78,117,109,73,110,100,105,99,101,115,41,32,123,10,32,32,32,32,32,32,32,
32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,105,102,32,40,110,117,108,108,112,116,114,32,61,61,32,109,73,110,100,105,99,101,115,41,32,123,10,32,32,32,32,32,32,32,32,32,32,
32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,110,116,32,105,32,61,32,48,59,32,105,32,60,32,116,104,105,115,45,62,109,78,117,
109,73,110,100,105,99,101,115,59,32,43,43,105,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,105,102,32,40,109,73,110,100,105,99,101,115,91,105,93,32,33,61,32,111,46,109,73,110,100,105,99,101,115,91,105,93,41,32,123,10,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,116,114,117,101,59,10,32,32,32,32,125,10,10,32,32,32,
32,47,47,33,32,64,98,114,105,101,102,32,73,110,118,101,114,115,101,32,99,111,109,112,97,114,105,115,111,110,32,111,112,101,114,97,116,111,114,46,32,67,104,101,99,107,115,32,119,104,101,116,104,101,114,32,116,104,101,32,105,110,100,101,120,10,32,32,32,
32,47,47,33,32,97,114,114,97,121,32,111,102,32,116,119,111,32,102,97,99,101,115,32,105,115,32,78,79,84,32,105,100,101,110,116,105,99,97,108,10,32,32,32,32,98,111,111,108,32,111,112,101,114,97,116,111,114,33,61,40,99,111,110,115,116,32,97,105,70,97,99,
101,32,38,111,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,33,40,42,116,104,105,115,32,61,61,32,111,41,59,10,32,32,32,32,125,10,35,101,110,100,105,102,32,47,47,32,95,95,99,112,108,117,115,112,108,117,115,10,125,
59,32,47,47,32,115,116,114,117,99,116,32,97,105,70,97,99,101,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,42,32,64,98,114,105,101,102,32,65,32,115,105,110,103,108,101,32,105,110,102,108,117,101,110,99,101,32,111,102,32,97,32,98,111,110,101,32,111,110,32,97,32,118,101,114,116,101,120,46,10,32,42,
47,10,115,116,114,117,99,116,32,97,105,86,101,114,116,101,120,87,101,105,103,104,116,32,123,10,32,32,32,32,47,47,33,32,73,110,100,101,120,32,111,102,32,116,104,101,32,118,101,114,116,101,120,32,119,104,105,99,104,32,105,115,32,105,110,102,108,117,101,
110,99,101,100,32,98,121,32,116,104,101,32,98,111,110,101,46,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,86,101,114,116,101,120,73,100,59,10,10,32,32,32,32,47,47,33,32,84,104,101,32,115,116,114,101,110,103,116,104,32,111,102,
32,116,104,101,32,105,110,102,108,117,101,110,99,101,32,105,110,32,116,104,101,32,114,97,110,103,101,32,40,48,46,46,46,49,41,46,10,32,32,32,32,47,47,33,32,84,104,101,32,105,110,102,108,117,101,110,99,101,32,102,114,111,109,32,97,108,108,32,98,111,110,
101,115,32,97,116,32,111,110,101,32,118,101,114,116,101,120,32,97,109,111,117,110,116,115,32,116,111,32,49,46,10,32,32,32,32,97,105,95,114,101,97,108,32,109,87,101,105,103,104,116,59,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,
115,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,68,101,102,97,117,108,116,32,99,111,110,115,116,114,117,99,116,111,114,10,32,32,32,32,97,105,86,101,114,116,101,120,87,101,105,103,104,116,40,41,32,65,73,95,78,79,95,69,88,67,69,80,84,10,32,32,
32,32,32,32,32,32,32,32,32,32,58,32,109,86,101,114,116,101,120,73,100,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,40,48,46,48,102,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,
125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,73,110,105,116,105,97,108,105,122,97,116,105,111,110,32,102,114,111,109,32,97,32,103,105,118,101,110,32,105,110,100,101,120,32,97,110,100,32,118,101,114,116,101,120,32,119,101,105,103,104,116,
32,102,97,99,116,111,114,10,32,32,32,32,47,47,33,32,92,112,97,114,97,109,32,112,73,68,32,73,68,10,32,32,32,32,47,47,33,32,92,112,97,114,97,109,32,112,87,101,105,103,104,116,32,86,101,114,116,101,120,32,119,101,105,103,104,116,32,102,97,99,116,111,114,
10,32,32,32,32,97,105,86,101,114,116,101,120,87,101,105,103,104,116,40,117,110,115,105,103,110,101,100,32,105,110,116,32,112,73,68,44,32,102,108,111,97,116,32,112,87,101,105,103,104,116,41,32,58,10,32,32,32,32,32,32,32,32,32,32,32,32,109,86,101,114,116,
101,120,73,100,40,112,73,68,41,44,32,109,87,101,105,103,104,116,40,112,87,101,105,103,104,116,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,10,32,32,32,32,98,111,111,108,32,111,112,101,114,97,116,111,114,61,61,
40,99,111,110,115,116,32,97,105,86,101,114,116,101,120,87,101,105,103,104,116,32,38,114,104,115,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,40,109,86,101,114,116,101,120,73,100,32,61,61,32,114,104,115,46,109,
86,101,114,116,101,120,73,100,32,38,38,32,109,87,101,105,103,104,116,32,61,61,32,114,104,115,46,109,87,101,105,103,104,116,41,59,10,32,32,32,32,125,10,10,32,32,32,32,98,111,111,108,32,111,112,101,114,97,116,111,114,33,61,40,99,111,110,115,116,32,97,105,
86,101,114,116,101,120,87,101,105,103,104,116,32,38,114,104,115,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,40,42,116,104,105,115,32,61,61,32,114,104,115,41,59,10,32,32,32,32,125,10,10,35,101,110,100,105,102,
32,47,47,32,95,95,99,112,108,117,115,112,108,117,115,10,125,59,10,10,47,47,32,70,111,114,119,97,114,100,32,100,101,99,108,97,114,101,32,97,105,78,111,100,101,32,40,112,111,105,110,116,101,114,32,117,115,101,32,111,110,108,121,41,10,115,116,114,117,99,
116,32,97,105,78,111,100,101,59,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,10,47,42,42,32,64,98,114,105,101,102,32,65,32,115,105,110,103,108,101,32,98,111,110,101,32,111,102,32,97,32,109,101,115,104,46,10,32,42,10,32,42,32,32,65,32,98,111,110,101,32,104,97,115,32,97,32,110,97,109,101,32,98,121,32,119,104,
105,99,104,32,105,116,32,99,97,110,32,98,101,32,102,111,117,110,100,32,105,110,32,116,104,101,32,102,114,97,109,101,32,104,105,101,114,97,114,99,104,121,32,97,110,100,32,98,121,10,32,42,32,32,119,104,105,99,104,32,105,116,32,99,97,110,32,98,101,32,97,
100,100,114,101,115,115,101,100,32,98,121,32,97,110,105,109,97,116,105,111,110,115,46,32,73,110,32,97,100,100,105,116,105,111,110,32,105,116,32,104,97,115,32,97,32,110,117,109,98,101,114,32,111,102,10,32,42,32,32,105,110,102,108,117,101,110,99,101,115,
32,111,110,32,118,101,114,116,105,99,101,115,44,32,97,110,100,32,97,32,109,97,116,114,105,120,32,114,101,108,97,116,105,110,103,32,116,104,101,32,109,101,115,104,32,112,111,115,105,116,105,111,110,32,116,111,32,116,104,101,10,32,42,32,32,112,111,115,
105,116,105,111,110,32,111,102,32,116,104,101,32,98,111,110,101,32,97,116,32,116,104,101,32,116,105,109,101,32,111,102,32,98,105,110,100,105,110,103,46,10,32,42,47,10,115,116,114,117,99,116,32,97,105,66,111,110,101,32,123,10,32,32,32,32,47,42,42,10,32,
32,32,32,32,42,32,84,104,101,32,110,97,109,101,32,111,102,32,116,104,101,32,98,111,110,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,83,116,114,105,110,103,32,109,78,97,109,101,59,10,10,32,32,32,32,47,42,42,10,32,32,
32,32,32,42,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,118,101,114,116,105,99,101,115,32,97,102,102,101,99,116,101,100,32,98,121,32,116,104,105,115,32,98,111,110,101,46,10,32,32,32,32,32,42,32,84,104,101,32,109,97,120,105,109,117,109,32,118,
97,108,117,101,32,102,111,114,32,116,104,105,115,32,109,101,109,98,101,114,32,105,115,32,35,65,73,95,77,65,88,95,66,79,78,69,95,87,69,73,71,72,84,83,46,10,32,32,32,32,32,42,47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,
109,87,101,105,103,104,116,115,59,10,10,35,105,102,110,100,101,102,32,65,83,83,73,77,80,95,66,85,73,76,68,95,78,79,95,65,82,77,65,84,85,82,69,80,79,80,85,76,65,84,69,95,80,82,79,67,69,83,83,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,101,32,
98,111,110,101,32,97,114,109,97,116,117,114,101,32,110,111,100,101,32,45,32,117,115,101,100,32,102,111,114,32,115,107,101,108,101,116,111,110,32,99,111,110,118,101,114,115,105,111,110,10,32,32,32,32,32,42,32,121,111,117,32,109,117,115,116,32,101,110,
97,98,108,101,32,97,105,80,114,111,99,101,115,115,95,80,111,112,117,108,97,116,101,65,114,109,97,116,117,114,101,68,97,116,97,32,116,111,32,112,111,112,117,108,97,116,101,32,116,104,105,115,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,
84,32,97,105,78,111,100,101,32,42,109,65,114,109,97,116,117,114,101,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,101,32,98,111,110,101,32,110,111,100,101,32,105,110,32,116,104,101,32,115,99,101,110,101,32,45,32,117,115,101,100,32,102,
111,114,32,115,107,101,108,101,116,111,110,32,99,111,110,118,101,114,115,105,111,110,10,32,32,32,32,32,42,32,121,111,117,32,109,117,115,116,32,101,110,97,98,108,101,32,97,105,80,114,111,99,101,115,115,95,80,111,112,117,108,97,116,101,65,114,109,97,116,
117,114,101,68,97,116,97,32,116,111,32,112,111,112,117,108,97,116,101,32,116,104,105,115,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,78,111,100,101,32,42,109,78,111,100,101,59,10,10,35,101,110,100,105,102,10,32,32,32,32,47,
42,42,10,32,32,32,32,32,42,32,84,104,101,32,105,110,102,108,117,101,110,99,101,32,119,101,105,103,104,116,115,32,111,102,32,116,104,105,115,32,98,111,110,101,44,32,98,121,32,118,101,114,116,101,120,32,105,110,100,101,120,46,10,32,32,32,32,32,42,47,10,
32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,114,116,101,120,87,101,105,103,104,116,32,42,109,87,101,105,103,104,116,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,77,97,116,114,105,120,32,116,104,97,116,32,116,114,97,110,115,102,111,
114,109,115,32,102,114,111,109,32,109,101,115,104,32,115,112,97,99,101,32,116,111,32,98,111,110,101,32,115,112,97,99,101,32,105,110,32,98,105,110,100,32,112,111,115,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,109,97,116,114,
105,120,32,100,101,115,99,114,105,98,101,115,32,116,104,101,32,112,111,115,105,116,105,111,110,32,111,102,32,116,104,101,32,109,101,115,104,10,32,32,32,32,32,42,32,105,110,32,116,104,101,32,108,111,99,97,108,32,115,112,97,99,101,32,111,102,32,116,104,
105,115,32,98,111,110,101,32,119,104,101,110,32,116,104,101,32,115,107,101,108,101,116,111,110,32,119,97,115,32,98,111,117,110,100,46,10,32,32,32,32,32,42,32,84,104,117,115,32,105,116,32,99,97,110,32,98,101,32,117,115,101,100,32,100,105,114,101,99,116,
108,121,32,116,111,32,100,101,116,101,114,109,105,110,101,32,97,32,100,101,115,105,114,101,100,32,118,101,114,116,101,120,32,112,111,115,105,116,105,111,110,44,10,32,32,32,32,32,42,32,103,105,118,101,110,32,116,104,101,32,119,111,114,108,100,45,115,112,
97,99,101,32,116,114,97,110,115,102,111,114,109,32,111,102,32,116,104,101,32,98,111,110,101,32,119,104,101,110,32,97,110,105,109,97,116,101,100,44,10,32,32,32,32,32,42,32,97,110,100,32,116,104,101,32,112,111,115,105,116,105,111,110,32,111,102,32,116,
104,101,32,118,101,114,116,101,120,32,105,110,32,109,101,115,104,32,115,112,97,99,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,73,116,32,105,115,32,115,111,109,101,116,105,109,101,115,32,99,97,108,108,101,100,32,97,110,32,105,110,118,101,114,115,
101,45,98,105,110,100,32,109,97,116,114,105,120,44,10,32,32,32,32,32,42,32,111,114,32,105,110,118,101,114,115,101,32,98,105,110,100,32,112,111,115,101,32,109,97,116,114,105,120,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,
77,97,116,114,105,120,52,120,52,32,109,79,102,102,115,101,116,77,97,116,114,105,120,59,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,10,32,32,32,32,47,47,47,9,64,98,114,105,101,102,32,32,68,101,102,97,117,108,116,32,99,111,
110,115,116,114,117,99,116,111,114,10,32,32,32,32,97,105,66,111,110,101,40,41,32,65,73,95,78,79,95,69,88,67,69,80,84,10,32,32,32,32,32,32,32,32,32,32,32,32,58,32,109,78,97,109,101,40,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,87,
101,105,103,104,116,115,40,48,41,44,10,35,105,102,110,100,101,102,32,65,83,83,73,77,80,95,66,85,73,76,68,95,78,79,95,65,82,77,65,84,85,82,69,80,79,80,85,76,65,84,69,95,80,82,79,67,69,83,83,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,65,114,109,97,
116,117,114,101,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,78,111,100,101,40,110,117,108,108,112,116,114,41,44,10,35,101,110,100,105,102,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,
115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,79,102,102,115,101,116,77,97,116,114,105,120,40,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,10,32,32,32,32,47,47,47,
32,64,98,114,105,101,102,32,32,67,111,112,121,32,99,111,110,115,116,114,117,99,116,111,114,10,32,32,32,32,97,105,66,111,110,101,40,99,111,110,115,116,32,97,105,66,111,110,101,32,38,111,116,104,101,114,41,32,58,10,32,32,32,32,32,32,32,32,32,32,32,32,109,
78,97,109,101,40,111,116,104,101,114,46,109,78,97,109,101,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,87,101,105,103,104,116,115,40,111,116,104,101,114,46,109,78,117,109,87,101,105,103,104,116,115,41,44,10,35,105,102,110,100,101,102,32,
65,83,83,73,77,80,95,66,85,73,76,68,95,78,79,95,65,82,77,65,84,85,82,69,80,79,80,85,76,65,84,69,95,80,82,79,67,69,83,83,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,65,114,109,97,116,117,114,101,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,109,78,111,100,101,40,110,117,108,108,112,116,114,41,44,10,35,101,110,100,105,102,10,32,32,32,32,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,
32,32,109,79,102,102,115,101,116,77,97,116,114,105,120,40,111,116,104,101,114,46,109,79,102,102,115,101,116,77,97,116,114,105,120,41,32,123,10,32,32,32,32,32,32,32,32,99,111,112,121,86,101,114,116,101,120,87,101,105,103,104,116,115,40,111,116,104,101,
114,41,59,10,32,32,32,32,125,10,10,32,32,32,32,118,111,105,100,32,99,111,112,121,86,101,114,116,101,120,87,101,105,103,104,116,115,40,32,99,111,110,115,116,32,97,105,66,111,110,101,32,38,111,116,104,101,114,32,41,32,123,10,32,32,32,32,32,32,32,32,105,
102,32,40,111,116,104,101,114,46,109,87,101,105,103,104,116,115,32,61,61,32,110,117,108,108,112,116,114,32,124,124,32,111,116,104,101,114,46,109,78,117,109,87,101,105,103,104,116,115,32,61,61,32,48,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,109,
87,101,105,103,104,116,115,32,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,87,101,105,103,104,116,115,32,61,32,48,59,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,59,10,32,32,32,32,32,32,
32,32,125,10,10,32,32,32,32,32,32,32,32,109,78,117,109,87,101,105,103,104,116,115,32,61,32,111,116,104,101,114,46,109,78,117,109,87,101,105,103,104,116,115,59,10,32,32,32,32,32,32,32,32,105,102,32,40,109,87,101,105,103,104,116,115,41,32,123,10,32,32,
32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,87,101,105,103,104,116,115,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,115,32,61,32,110,101,119,32,97,105,86,101,114,116,101,120,87,101,
105,103,104,116,91,109,78,117,109,87,101,105,103,104,116,115,93,59,10,32,32,32,32,32,32,32,32,58,58,109,101,109,99,112,121,40,109,87,101,105,103,104,116,115,44,32,111,116,104,101,114,46,109,87,101,105,103,104,116,115,44,32,109,78,117,109,87,101,105,103,
104,116,115,32,42,32,115,105,122,101,111,102,40,97,105,86,101,114,116,101,120,87,101,105,103,104,116,41,41,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,65,115,115,105,103,110,109,101,110,116,32,111,112,101,114,97,116,111,
114,10,32,32,32,32,97,105,66,111,110,101,32,38,111,112,101,114,97,116,111,114,32,61,32,40,99,111,110,115,116,32,97,105,66,111,110,101,32,38,111,116,104,101,114,41,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,116,104,105,115,32,61,61,32,38,111,116,
104,101,114,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,42,116,104,105,115,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,109,78,97,109,101,32,61,32,111,116,104,101,114,46,109,78,97,109,101,59,10,32,32,
32,32,32,32,32,32,109,78,117,109,87,101,105,103,104,116,115,32,61,32,111,116,104,101,114,46,109,78,117,109,87,101,105,103,104,116,115,59,10,32,32,32,32,32,32,32,32,109,79,102,102,115,101,116,77,97,116,114,105,120,32,61,32,111,116,104,101,114,46,109,79,
102,102,115,101,116,77,97,116,114,105,120,59,10,32,32,32,32,32,32,32,32,99,111,112,121,86,101,114,116,101,120,87,101,105,103,104,116,115,40,111,116,104,101,114,41,59,10,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,42,116,104,105,115,59,10,32,
32,32,32,125,10,10,32,32,32,32,47,47,47,32,64,98,114,105,101,102,32,67,111,109,112,97,114,101,32,111,112,101,114,97,116,111,114,46,10,32,32,32,32,98,111,111,108,32,111,112,101,114,97,116,111,114,61,61,40,99,111,110,115,116,32,97,105,66,111,110,101,32,
38,114,104,115,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,109,78,97,109,101,32,33,61,32,114,104,115,46,109,78,97,109,101,32,124,124,32,109,78,117,109,87,101,105,103,104,116,115,32,33,61,32,114,104,115,46,109,78,117,109,87,
101,105,103,104,116,115,32,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,102,111,114,32,40,115,105,122,101,95,116,32,105,32,61,32,48,59,32,
105,32,60,32,109,78,117,109,87,101,105,103,104,116,115,59,32,43,43,105,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,105,102,32,40,109,87,101,105,103,104,116,115,91,105,93,32,33,61,32,114,104,115,46,109,87,101,105,103,104,116,115,91,105,93,41,32,123,
10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,116,114,117,101,59,
10,32,32,32,32,125,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,68,101,115,116,114,117,99,116,111,114,32,45,32,100,101,108,101,116,101,115,32,116,104,101,32,97,114,114,97,121,32,111,102,32,118,101,114,116,101,120,32,119,101,105,103,104,116,115,
10,32,32,32,32,126,97,105,66,111,110,101,40,41,32,123,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,87,101,105,103,104,116,115,59,10,32,32,32,32,125,10,35,101,110,100,105,102,32,47,47,32,95,95,99,112,108,117,115,112,108,117,115,10,125,
59,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,
42,32,64,98,114,105,101,102,32,69,110,117,109,101,114,97,116,101,115,32,116,104,101,32,116,121,112,101,115,32,111,102,32,103,101,111,109,101,116,114,105,99,32,112,114,105,109,105,116,105,118,101,115,32,115,117,112,112,111,114,116,101,100,32,98,121,32,
65,115,115,105,109,112,46,10,32,42,10,32,42,32,32,64,115,101,101,32,97,105,70,97,99,101,32,70,97,99,101,32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,10,32,42,32,32,64,115,101,101,32,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,
80,84,121,112,101,32,80,101,114,45,112,114,105,109,105,116,105,118,101,32,115,111,114,116,105,110,103,32,111,102,32,109,101,115,104,101,115,10,32,42,32,32,64,115,101,101,32,97,105,80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,
32,65,117,116,111,109,97,116,105,99,32,116,114,105,97,110,103,117,108,97,116,105,111,110,10,32,42,32,32,64,115,101,101,32,65,73,95,67,79,78,70,73,71,95,80,80,95,83,66,80,95,82,69,77,79,86,69,32,82,101,109,111,118,97,108,32,111,102,32,115,112,101,99,105,
102,105,99,32,112,114,105,109,105,116,105,118,101,32,116,121,112,101,115,46,10,32,42,47,10,101,110,117,109,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,32,123,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,65,
32,112,111,105,110,116,32,112,114,105,109,105,116,105,118,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,106,117,115,116,32,97,32,115,105,110,103,108,101,32,118,101,114,116,101,120,32,105,110,32,116,104,101,32,118,105,
114,116,117,97,108,32,119,111,114,108,100,44,10,32,32,32,32,32,42,32,35,97,105,70,97,99,101,32,99,111,110,116,97,105,110,115,32,106,117,115,116,32,111,110,101,32,105,110,100,101,120,32,102,111,114,32,115,117,99,104,32,97,32,112,114,105,109,105,116,105,
118,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,80,79,73,78,84,32,61,32,48,120,49,44,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,65,32,108,105,110,101,32,112,
114,105,109,105,116,105,118,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,97,32,108,105,110,101,32,100,101,102,105,110,101,100,32,116,104,114,111,117,103,104,32,97,32,115,116,97,114,116,32,97,110,100,32,97,110,32,101,
110,100,32,112,111,115,105,116,105,111,110,46,10,32,32,32,32,32,42,32,35,97,105,70,97,99,101,32,99,111,110,116,97,105,110,115,32,101,120,97,99,116,108,121,32,116,119,111,32,105,110,100,105,99,101,115,32,102,111,114,32,115,117,99,104,32,97,32,112,114,
105,109,105,116,105,118,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,76,73,78,69,32,61,32,48,120,50,44,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,65,32,116,
114,105,97,110,103,117,108,97,114,32,112,114,105,109,105,116,105,118,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,116,114,105,97,110,103,108,101,32,99,111,110,115,105,115,116,115,32,111,102,32,116,104,114,101,101,32,105,110,100,105,99,101,
115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,84,82,73,65,78,71,76,69,32,61,32,48,120,52,44,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,65,32,104,105,103,104,
101,114,45,108,101,118,101,108,32,112,111,108,121,103,111,110,32,119,105,116,104,32,109,111,114,101,32,116,104,97,110,32,51,32,101,100,103,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,116,114,105,97,110,103,108,101,32,105,115,32,97,32,
112,111,108,121,103,111,110,44,32,98,117,116,32,112,111,108,121,103,111,110,32,105,110,32,116,104,105,115,32,99,111,110,116,101,120,116,32,109,101,97,110,115,10,32,32,32,32,32,42,32,34,97,108,108,32,112,111,108,121,103,111,110,115,32,116,104,97,116,32,
97,114,101,32,110,111,116,32,116,114,105,97,110,103,108,101,115,34,46,32,84,104,101,32,34,84,114,105,97,110,103,117,108,97,116,101,34,45,83,116,101,112,10,32,32,32,32,32,42,32,105,115,32,112,114,111,118,105,100,101,100,32,102,111,114,32,121,111,117,114,
32,99,111,110,118,101,110,105,101,110,99,101,44,32,105,116,32,115,112,108,105,116,115,32,97,108,108,32,112,111,108,121,103,111,110,115,32,105,110,10,32,32,32,32,32,42,32,116,114,105,97,110,103,108,101,115,32,40,119,104,105,99,104,32,97,114,101,32,109,
117,99,104,32,101,97,115,105,101,114,32,116,111,32,104,97,110,100,108,101,41,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,80,79,76,89,71,79,78,32,61,32,48,120,56,44,10,10,32,32,32,32,47,42,42,10,
32,32,32,32,32,42,32,64,98,114,105,101,102,32,65,32,102,108,97,103,32,116,111,32,100,101,116,101,114,109,105,110,101,32,119,104,101,116,104,101,114,32,116,104,105,115,32,116,114,105,97,110,103,108,101,115,32,111,110,108,121,32,109,101,115,104,32,105,
115,32,78,71,79,78,32,101,110,99,111,100,101,100,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,78,71,79,78,32,101,110,99,111,100,105,110,103,32,105,115,32,97,32,115,112,101,99,105,97,108,32,101,110,99,111,100,105,110,103,32,116,104,97,116,32,116,101,
108,108,115,32,119,104,101,116,104,101,114,32,50,32,111,114,32,109,111,114,101,32,99,111,110,115,101,99,117,116,105,118,101,32,116,114,105,97,110,103,108,101,115,10,32,32,32,32,32,42,32,115,104,111,117,108,100,32,98,101,32,99,111,110,115,105,100,101,
114,101,100,32,97,115,32,97,32,116,114,105,97,110,103,108,101,32,102,97,110,46,32,84,104,105,115,32,105,115,32,105,100,101,110,116,105,102,105,101,100,32,98,121,32,108,111,111,107,105,110,103,32,97,116,32,116,104,101,32,102,105,114,115,116,32,118,101,
114,116,101,120,32,105,110,100,101,120,46,10,32,32,32,32,32,42,32,50,32,99,111,110,115,101,99,117,116,105,118,101,32,116,114,105,97,110,103,108,101,115,32,119,105,116,104,32,116,104,101,32,115,97,109,101,32,49,115,116,32,118,101,114,116,101,120,32,105,
110,100,101,120,32,97,114,101,32,112,97,114,116,32,111,102,32,116,104,101,32,115,97,109,101,10,32,32,32,32,32,42,32,78,71,79,78,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,116,32,116,104,101,32,109,111,109,101,110,116,44,32,111,110,108,121,32,
113,117,97,100,115,32,40,99,111,110,99,97,118,101,32,111,114,32,99,111,110,118,101,120,41,32,97,114,101,32,115,117,112,112,111,114,116,101,100,44,32,109,101,97,110,105,110,103,32,116,104,97,116,32,112,111,108,121,103,111,110,115,32,97,114,101,32,39,115,
101,101,110,39,32,97,115,10,32,32,32,32,32,42,32,116,114,105,97,110,103,108,101,115,44,32,97,115,32,117,115,117,97,108,32,97,102,116,101,114,32,97,32,116,114,105,97,110,103,117,108,97,116,105,111,110,32,112,97,115,115,46,10,32,32,32,32,32,42,10,32,32,
32,32,32,42,32,84,111,32,103,101,116,32,97,110,32,78,71,79,78,32,101,110,99,111,100,101,100,32,109,101,115,104,44,32,112,108,101,97,115,101,32,117,115,101,32,116,104,101,32,97,105,80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,
32,112,111,115,116,32,112,114,111,99,101,115,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,64,115,101,101,32,97,105,80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,10,32,32,32,32,32,42,32,64,108,105,110,107,32,104,116,116,
112,115,58,47,47,103,105,116,104,117,98,46,99,111,109,47,75,104,114,111,110,111,115,71,114,111,117,112,47,103,108,84,70,47,112,117,108,108,47,49,54,50,48,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,
95,78,71,79,78,69,110,99,111,100,105,110,103,70,108,97,103,32,61,32,48,120,49,48,44,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,105,115,32,118,97,108,117,101,32,105,115,32,110,111,116,32,117,115,101,100,46,32,73,116,32,105,115,32,106,117,
115,116,32,104,101,114,101,32,116,111,32,102,111,114,99,101,32,116,104,101,10,32,32,32,32,32,42,32,99,111,109,112,105,108,101,114,32,116,111,32,109,97,112,32,116,104,105,115,32,101,110,117,109,32,116,111,32,97,32,51,50,32,66,105,116,32,105,110,116,101,
103,101,114,46,10,32,32,32,32,32,42,47,10,35,105,102,110,100,101,102,32,83,87,73,71,10,32,32,32,32,95,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,70,111,114,99,101,51,50,66,105,116,32,61,32,73,78,84,95,77,65,88,10,35,101,110,100,105,102,
10,125,59,32,47,47,33,32,101,110,117,109,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,10,10,47,47,32,71,101,116,32,116,104,101,32,35,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,32,102,108,97,103,32,102,111,114,32,97,32,115,
112,101,99,105,102,105,99,32,110,117,109,98,101,114,32,111,102,32,102,97,99,101,32,105,110,100,105,99,101,115,10,35,100,101,102,105,110,101,32,65,73,95,80,82,73,77,73,84,73,86,69,95,84,89,80,69,95,70,79,82,95,78,95,73,78,68,73,67,69,83,40,110,41,32,92,
10,32,32,32,32,40,40,110,41,32,62,32,51,32,63,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,80,79,76,89,71,79,78,32,58,32,40,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,41,40,49,117,32,60,60,32,40,40,110,41,45,49,41,41,41,
10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,42,
32,64,98,114,105,101,102,32,65,110,32,65,110,105,109,77,101,115,104,32,105,115,32,97,110,32,97,116,116,97,99,104,109,101,110,116,32,116,111,32,97,110,32,35,97,105,77,101,115,104,32,115,116,111,114,101,115,32,112,101,114,45,118,101,114,116,101,120,10,
32,42,32,32,97,110,105,109,97,116,105,111,110,115,32,102,111,114,32,97,32,112,97,114,116,105,99,117,108,97,114,32,102,114,97,109,101,46,10,32,42,10,32,42,32,32,89,111,117,32,109,97,121,32,116,104,105,110,107,32,111,102,32,97,110,32,35,97,105,65,110,105,
109,77,101,115,104,32,97,115,32,97,32,96,112,97,116,99,104,96,32,102,111,114,32,116,104,101,32,104,111,115,116,32,109,101,115,104,44,32,119,104,105,99,104,10,32,42,32,32,114,101,112,108,97,99,101,115,32,111,110,108,121,32,99,101,114,116,97,105,110,32,
118,101,114,116,101,120,32,100,97,116,97,32,115,116,114,101,97,109,115,32,97,116,32,97,32,112,97,114,116,105,99,117,108,97,114,32,116,105,109,101,46,10,32,42,32,32,69,97,99,104,32,109,101,115,104,32,115,116,111,114,101,115,32,110,32,97,116,116,97,99,
104,101,100,32,97,116,116,97,99,104,101,100,32,109,101,115,104,101,115,32,40,35,97,105,77,101,115,104,58,58,109,65,110,105,109,77,101,115,104,101,115,41,46,10,32,42,32,32,84,104,101,32,97,99,116,117,97,108,32,114,101,108,97,116,105,111,110,115,104,105,
112,32,98,101,116,119,101,101,110,32,116,104,101,32,116,105,109,101,32,108,105,110,101,32,97,110,100,32,97,110,105,109,32,109,101,115,104,101,115,32,105,115,10,32,42,32,32,101,115,116,97,98,108,105,115,104,101,100,32,98,121,32,35,97,105,77,101,115,104,
65,110,105,109,44,32,119,104,105,99,104,32,114,101,102,101,114,101,110,99,101,115,32,115,105,110,103,117,108,97,114,32,109,101,115,104,32,97,116,116,97,99,104,109,101,110,116,115,10,32,42,32,32,98,121,32,116,104,101,105,114,32,73,68,32,97,110,100,32,
98,105,110,100,115,32,116,104,101,109,32,116,111,32,97,32,116,105,109,101,32,111,102,102,115,101,116,46,10,42,47,10,115,116,114,117,99,116,32,97,105,65,110,105,109,77,101,115,104,32,123,10,32,32,32,32,47,42,42,65,110,105,109,32,77,101,115,104,32,110,
97,109,101,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,83,116,114,105,110,103,32,109,78,97,109,101,59,10,10,32,32,32,32,47,42,42,32,82,101,112,108,97,99,101,109,101,110,116,32,102,111,114,32,97,105,77,101,115,104,58,58,109,86,101,114,116,
105,99,101,115,46,32,73,102,32,116,104,105,115,32,97,114,114,97,121,32,105,115,32,110,111,110,45,110,117,108,108,112,116,114,44,10,32,32,32,32,32,42,32,32,105,116,32,42,109,117,115,116,42,32,99,111,110,116,97,105,110,32,109,78,117,109,86,101,114,116,
105,99,101,115,32,101,110,116,114,105,101,115,46,32,84,104,101,32,99,111,114,114,101,115,112,111,110,100,105,110,103,10,32,32,32,32,32,42,32,32,97,114,114,97,121,32,105,110,32,116,104,101,32,104,111,115,116,32,109,101,115,104,32,109,117,115,116,32,98,
101,32,110,111,110,45,110,117,108,108,112,116,114,32,97,115,32,119,101,108,108,32,45,32,97,110,105,109,97,116,105,111,110,10,32,32,32,32,32,42,32,32,109,101,115,104,101,115,32,109,97,121,32,110,101,105,116,104,101,114,32,97,100,100,32,111,114,32,110,
111,114,32,114,101,109,111,118,101,32,118,101,114,116,101,120,32,99,111,109,112,111,110,101,110,116,115,32,40,105,102,10,32,32,32,32,32,42,32,32,97,32,114,101,112,108,97,99,101,109,101,110,116,32,97,114,114,97,121,32,105,115,32,110,117,108,108,112,116,
114,32,97,110,100,32,116,104,101,32,99,111,114,114,101,115,112,111,110,100,105,110,103,32,115,111,117,114,99,101,10,32,32,32,32,32,42,32,32,97,114,114,97,121,32,105,115,32,110,111,116,44,32,116,104,101,32,115,111,117,114,99,101,32,100,97,116,97,32,105,
115,32,116,97,107,101,110,32,105,110,115,116,101,97,100,41,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,86,101,114,116,105,99,101,115,59,10,10,32,32,32,32,47,42,42,32,82,101,112,108,97,99,101,109,101,110,
116,32,102,111,114,32,97,105,77,101,115,104,58,58,109,78,111,114,109,97,108,115,46,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,78,111,114,109,97,108,115,59,10,10,32,32,32,32,47,42,42,32,82,101,112,
108,97,99,101,109,101,110,116,32,102,111,114,32,97,105,77,101,115,104,58,58,109,84,97,110,103,101,110,116,115,46,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,84,97,110,103,101,110,116,115,59,10,10,32,
32,32,32,47,42,42,32,82,101,112,108,97,99,101,109,101,110,116,32,102,111,114,32,97,105,77,101,115,104,58,58,109,66,105,116,97,110,103,101,110,116,115,46,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,66,
105,116,97,110,103,101,110,116,115,59,10,10,32,32,32,32,47,42,42,32,82,101,112,108,97,99,101,109,101,110,116,32,102,111,114,32,97,105,77,101,115,104,58,58,109,67,111,108,111,114,115,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,67,111,108,
111,114,52,68,32,42,109,67,111,108,111,114,115,91,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,93,59,10,10,32,32,32,32,47,42,42,32,82,101,112,108,97,99,101,109,101,110,116,32,102,111,114,32,97,105,77,101,115,104,58,
58,109,84,101,120,116,117,114,101,67,111,111,114,100,115,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,
70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,93,59,10,10,32,32,32,32,47,42,42,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,118,101,114,116,105,99,101,115,32,105,110,32,116,104,101,32,97,105,65,110,105,109,77,101,115,104,44,32,97,110,100,32,116,
104,117,115,32,116,104,101,32,108,101,110,103,116,104,32,111,102,32,97,108,108,10,32,32,32,32,32,42,32,116,104,101,32,109,101,109,98,101,114,32,97,114,114,97,121,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,104,97,115,32,97,108,
119,97,121,115,32,116,104,101,32,115,97,109,101,32,118,97,108,117,101,32,97,115,32,116,104,101,32,109,78,117,109,86,101,114,116,105,99,101,115,32,112,114,111,112,101,114,116,121,32,105,110,32,116,104,101,10,32,32,32,32,32,42,32,99,111,114,114,101,115,
112,111,110,100,105,110,103,32,97,105,77,101,115,104,46,32,73,116,32,105,115,32,100,117,112,108,105,99,97,116,101,100,32,104,101,114,101,32,109,101,114,101,108,121,32,116,111,32,109,97,107,101,32,116,104,101,32,108,101,110,103,116,104,10,32,32,32,32,
32,42,32,111,102,32,116,104,101,32,109,101,109,98,101,114,32,97,114,114,97,121,115,32,97,99,99,101,115,115,105,98,108,101,32,101,118,101,110,32,105,102,32,116,104,101,32,97,105,77,101,115,104,32,105,115,32,110,111,116,32,107,110,111,119,110,44,32,101,
46,103,46,10,32,32,32,32,32,42,32,102,114,111,109,32,108,97,110,103,117,97,103,101,32,98,105,110,100,105,110,103,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,86,101,114,116,105,99,101,
115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,87,101,105,103,104,116,32,111,102,32,116,104,101,32,65,110,105,109,77,101,115,104,46,10,32,32,32,32,32,42,47,10,32,32,32,32,102,108,111,97,116,32,109,87,101,105,103,104,116,59,10,10,35,105,102,
100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,32,32,32,32,47,47,47,32,64,98,114,105,101,102,32,32,84,104,101,32,99,108,97,115,115,32,99,111,110,115,116,114,117,99,116,111,114,46,10,32,32,32,32,97,105,65,110,105,109,77,101,115,104,40,41,32,
65,73,95,78,79,95,69,88,67,69,80,84,32,58,10,32,32,32,32,32,32,32,32,32,32,32,32,109,86,101,114,116,105,99,101,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,111,114,109,97,108,115,40,110,117,108,108,112,116,114,
41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,84,97,110,103,101,110,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,66,105,116,97,110,103,101,110,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,
32,32,32,32,32,32,32,109,67,111,108,111,114,115,32,123,110,117,108,108,112,116,114,125,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,123,110,117,108,108,112,116,114,125,44,10,32,32,32,32,32,32,32,32,32,
32,32,32,109,78,117,109,86,101,114,116,105,99,101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,40,48,46,48,102,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,10,32,32,32,32,
47,47,47,32,64,98,114,105,101,102,32,84,104,101,32,99,108,97,115,115,32,100,101,115,116,114,117,99,116,111,114,46,10,32,32,32,32,126,97,105,65,110,105,109,77,101,115,104,40,41,32,123,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,86,
101,114,116,105,99,101,115,59,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,78,111,114,109,97,108,115,59,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,84,97,110,103,101,110,116,115,59,10,32,32,32,32,32,32,32,32,100,
101,108,101,116,101,91,93,32,109,66,105,116,97,110,103,101,110,116,115,59,10,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,
95,84,69,88,84,85,82,69,67,79,79,82,68,83,59,32,97,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,97,93,59,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,
32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,59,32,97,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,
32,32,100,101,108,101,116,101,91,93,32,109,67,111,108,111,114,115,91,97,93,59,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,125,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,
114,32,116,104,101,32,97,110,105,109,45,109,101,115,104,32,111,118,101,114,114,105,100,101,115,32,116,104,101,32,118,101,114,116,101,120,32,112,111,115,105,116,105,111,110,115,10,32,32,32,32,32,42,32,32,32,32,32,32,32,32,32,111,102,32,105,116,115,32,
104,111,115,116,32,109,101,115,104,46,10,32,32,32,32,32,42,32,32,64,114,101,116,117,114,110,32,116,114,117,101,32,105,102,32,112,111,115,105,116,105,111,110,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,
46,10,32,32,32,32,32,42,47,10,32,32,32,32,98,111,111,108,32,72,97,115,80,111,115,105,116,105,111,110,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,86,101,114,116,105,99,101,115,32,33,61,32,110,117,108,
108,112,116,114,59,10,32,32,32,32,125,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,97,110,105,109,45,109,101,115,104,32,111,118,101,114,114,105,100,101,
115,32,116,104,101,32,118,101,114,116,101,120,32,110,111,114,109,97,108,115,10,32,32,32,32,32,42,32,32,32,32,32,32,32,32,32,111,102,32,105,116,115,32,104,111,115,116,32,109,101,115,104,10,32,32,32,32,32,42,32,32,64,114,101,116,117,114,110,32,116,114,
117,101,32,105,102,32,110,111,114,109,97,108,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,32,42,47,10,32,32,32,32,98,111,111,108,32,72,97,115,78,111,114,109,97,108,115,40,41,32,99,111,
110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,78,111,114,109,97,108,115,32,33,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,125,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,67,104,
101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,97,110,105,109,45,109,101,115,104,32,111,118,101,114,114,105,100,101,115,32,116,104,101,32,118,101,114,116,101,120,32,116,97,110,103,101,110,116,115,10,32,32,32,32,32,42,32,32,32,32,32,32,32,
32,32,97,110,100,32,98,105,116,97,110,103,101,110,116,115,32,111,102,32,105,116,115,32,104,111,115,116,32,109,101,115,104,46,32,65,115,32,102,111,114,32,97,105,77,101,115,104,44,10,32,32,32,32,32,42,32,32,32,32,32,32,32,32,32,116,97,110,103,101,110,116,
115,32,97,110,100,32,98,105,116,97,110,103,101,110,116,115,32,97,108,119,97,121,115,32,103,111,32,116,111,103,101,116,104,101,114,46,10,32,32,32,32,32,42,32,32,64,114,101,116,117,114,110,32,116,114,117,101,32,105,102,32,116,97,110,103,101,110,116,115,
32,97,110,100,32,98,105,45,116,97,110,103,101,110,116,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,32,42,47,10,32,32,32,32,98,111,111,108,32,72,97,115,84,97,110,103,101,110,116,115,
65,110,100,66,105,116,97,110,103,101,110,116,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,84,97,110,103,101,110,116,115,32,33,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,125,10,10,32,32,32,32,
47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,97,110,105,109,32,109,101,115,104,32,111,118,101,114,114,105,100,101,115,32,97,32,112,97,114,116,105,99,117,108,97,114,10,
32,32,32,32,32,42,32,32,32,32,32,32,32,32,32,115,101,116,32,111,102,32,118,101,114,116,101,120,32,99,111,108,111,114,115,32,111,110,32,104,105,115,32,104,111,115,116,32,109,101,115,104,46,10,32,32,32,32,32,42,32,32,64,112,97,114,97,109,32,112,73,110,
100,101,120,32,48,60,105,110,100,101,120,60,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,10,32,32,32,32,32,42,32,32,64,114,101,116,117,114,110,32,116,114,117,101,32,105,102,32,118,101,114,116,101,120,32,99,111,108,
111,114,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,32,42,47,10,10,32,32,32,32,98,111,111,108,32,72,97,115,86,101,114,116,101,120,67,111,108,111,114,115,40,117,110,115,105,103,110,
101,100,32,105,110,116,32,112,73,110,100,101,120,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,112,73,110,100,101,120,32,62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,
32,63,32,102,97,108,115,101,32,58,32,109,67,111,108,111,114,115,91,112,73,110,100,101,120,93,32,33,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,125,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,67,104,101,99,107,
32,119,104,101,116,104,101,114,32,116,104,101,32,97,110,105,109,32,109,101,115,104,32,111,118,101,114,114,105,100,101,115,32,97,32,112,97,114,116,105,99,117,108,97,114,10,32,32,32,32,32,42,32,32,32,32,32,32,32,32,115,101,116,32,111,102,32,116,101,120,
116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,111,110,32,104,105,115,32,104,111,115,116,32,109,101,115,104,46,10,32,32,32,32,32,42,32,32,64,112,97,114,97,109,32,112,73,110,100,101,120,32,48,60,105,110,100,101,120,60,65,73,95,77,65,88,
95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,10,32,32,32,32,32,42,32,32,64,114,101,116,117,114,110,32,116,114,117,101,32,105,102,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,97,114,101,32,115,
116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,32,42,47,10,32,32,32,32,98,111,111,108,32,72,97,115,84,101,120,116,117,114,101,67,111,111,114,100,115,40,117,110,115,105,103,110,101,100,32,105,110,116,32,112,73,
110,100,101,120,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,112,73,110,100,101,120,32,62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,32,63,32,102,97,108,115,
101,32,58,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,112,73,110,100,101,120,93,32,33,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,125,10,10,35,101,110,100,105,102,10,125,59,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,42,32,64,98,114,105,101,102,32,69,110,117,109,101,114,97,
116,101,115,32,116,104,101,32,109,101,116,104,111,100,115,32,111,102,32,109,101,115,104,32,109,111,114,112,104,105,110,103,32,115,117,112,112,111,114,116,101,100,32,98,121,32,65,115,115,105,109,112,46,10,32,42,47,10,101,110,117,109,32,97,105,77,111,114,
112,104,105,110,103,77,101,116,104,111,100,32,123,10,32,32,32,32,47,42,42,32,77,111,114,112,104,105,110,103,32,109,101,116,104,111,100,32,116,111,32,98,101,32,100,101,116,101,114,109,105,110,101,100,32,42,47,10,32,32,32,32,97,105,77,111,114,112,104,105,
110,103,77,101,116,104,111,100,95,85,78,75,78,79,87,78,32,61,32,48,120,48,44,10,10,32,32,32,32,47,42,42,32,73,110,116,101,114,112,111,108,97,116,105,111,110,32,98,101,116,119,101,101,110,32,109,111,114,112,104,32,116,97,114,103,101,116,115,32,42,47,10,
32,32,32,32,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,95,86,69,82,84,69,88,95,66,76,69,78,68,32,61,32,48,120,49,44,10,10,32,32,32,32,47,42,42,32,78,111,114,109,97,108,105,122,101,100,32,109,111,114,112,104,105,110,103,32,98,101,116,
119,101,101,110,32,109,111,114,112,104,32,116,97,114,103,101,116,115,32,32,42,47,10,32,32,32,32,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,95,77,79,82,80,72,95,78,79,82,77,65,76,73,90,69,68,32,61,32,48,120,50,44,10,10,32,32,32,32,47,
42,42,32,82,101,108,97,116,105,118,101,32,109,111,114,112,104,105,110,103,32,98,101,116,119,101,101,110,32,109,111,114,112,104,32,116,97,114,103,101,116,115,32,32,42,47,10,32,32,32,32,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,95,77,
79,82,80,72,95,82,69,76,65,84,73,86,69,32,61,32,48,120,51,44,10,10,47,42,42,32,84,104,105,115,32,118,97,108,117,101,32,105,115,32,110,111,116,32,117,115,101,100,46,32,73,116,32,105,115,32,106,117,115,116,32,104,101,114,101,32,116,111,32,102,111,114,99,
101,32,116,104,101,10,32,32,32,32,32,42,32,32,99,111,109,112,105,108,101,114,32,116,111,32,109,97,112,32,116,104,105,115,32,101,110,117,109,32,116,111,32,97,32,51,50,32,66,105,116,32,105,110,116,101,103,101,114,46,10,32,32,32,32,32,42,47,10,35,105,102,
110,100,101,102,32,83,87,73,71,10,32,32,32,32,95,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,95,70,111,114,99,101,51,50,66,105,116,32,61,32,73,78,84,95,77,65,88,10,35,101,110,100,105,102,10,125,59,32,47,47,33,32,101,110,117,109,32,97,
105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,42,32,64,98,114,105,101,102,32,65,32,109,101,115,104,32,114,101,112,114,101,115,101,110,116,115,32,97,32,103,101,111,109,101,116,114,121,32,111,114,32,109,111,100,101,108,32,119,105,116,104,32,
97,32,115,105,110,103,108,101,32,109,97,116,101,114,105,97,108,46,10,32,42,10,32,42,32,73,116,32,117,115,117,97,108,108,121,32,99,111,110,115,105,115,116,115,32,111,102,32,97,32,110,117,109,98,101,114,32,111,102,32,118,101,114,116,105,99,101,115,32,97,
110,100,32,97,32,115,101,114,105,101,115,32,111,102,32,112,114,105,109,105,116,105,118,101,115,47,102,97,99,101,115,10,32,42,32,114,101,102,101,114,101,110,99,105,110,103,32,116,104,101,32,118,101,114,116,105,99,101,115,46,32,73,110,32,97,100,100,105,
116,105,111,110,32,116,104,101,114,101,32,109,105,103,104,116,32,98,101,32,97,32,115,101,114,105,101,115,32,111,102,32,98,111,110,101,115,44,32,101,97,99,104,10,32,42,32,111,102,32,116,104,101,109,32,97,100,100,114,101,115,115,105,110,103,32,97,32,110,
117,109,98,101,114,32,111,102,32,118,101,114,116,105,99,101,115,32,119,105,116,104,32,97,32,99,101,114,116,97,105,110,32,119,101,105,103,104,116,46,32,86,101,114,116,101,120,32,100,97,116,97,10,32,42,32,105,115,32,112,114,101,115,101,110,116,101,100,
32,105,110,32,99,104,97,110,110,101,108,115,32,119,105,116,104,32,101,97,99,104,32,99,104,97,110,110,101,108,32,99,111,110,116,97,105,110,105,110,103,32,97,32,115,105,110,103,108,101,32,112,101,114,45,118,101,114,116,101,120,10,32,42,32,105,110,102,111,
114,109,97,116,105,111,110,32,115,117,99,104,32,97,115,32,97,32,115,101,116,32,111,102,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,111,114,32,97,32,110,111,114,109,97,108,32,118,101,99,116,111,114,46,10,32,42,32,73,
102,32,97,32,100,97,116,97,32,112,111,105,110,116,101,114,32,105,115,32,110,111,110,45,110,117,108,108,44,32,116,104,101,32,99,111,114,114,101,115,112,111,110,100,105,110,103,32,100,97,116,97,32,115,116,114,101,97,109,32,105,115,32,112,114,101,115,101,
110,116,46,10,32,42,32,70,114,111,109,32,67,43,43,45,112,114,111,103,114,97,109,115,32,121,111,117,32,99,97,110,32,97,108,115,111,32,117,115,101,32,116,104,101,32,99,111,109,102,111,114,116,32,102,117,110,99,116,105,111,110,115,32,72,97,115,42,40,41,
32,116,111,10,32,42,32,116,101,115,116,32,102,111,114,32,116,104,101,32,112,114,101,115,101,110,99,101,32,111,102,32,118,97,114,105,111,117,115,32,100,97,116,97,32,115,116,114,101,97,109,115,46,10,32,42,10,32,42,32,65,32,77,101,115,104,32,117,115,101,
115,32,111,110,108,121,32,97,32,115,105,110,103,108,101,32,109,97,116,101,114,105,97,108,32,119,104,105,99,104,32,105,115,32,114,101,102,101,114,101,110,99,101,100,32,98,121,32,97,32,109,97,116,101,114,105,97,108,32,73,68,46,10,32,42,32,64,110,111,116,
101,32,84,104,101,32,109,80,111,115,105,116,105,111,110,115,32,109,101,109,98,101,114,32,105,115,32,117,115,117,97,108,108,121,32,110,111,116,32,111,112,116,105,111,110,97,108,46,32,72,111,119,101,118,101,114,44,32,118,101,114,116,101,120,32,112,111,
115,105,116,105,111,110,115,10,32,42,32,42,99,111,117,108,100,42,32,98,101,32,109,105,115,115,105,110,103,32,105,102,32,116,104,101,32,35,65,73,95,83,67,69,78,69,95,70,76,65,71,83,95,73,78,67,79,77,80,76,69,84,69,32,102,108,97,103,32,105,115,32,115,101,
116,32,105,110,10,32,42,32,64,99,111,100,101,10,32,42,32,97,105,83,99,101,110,101,58,58,109,70,108,97,103,115,10,32,42,32,64,101,110,100,99,111,100,101,10,32,42,47,10,115,116,114,117,99,116,32,97,105,77,101,115,104,32,123,10,32,32,32,32,47,42,42,10,32,
32,32,32,32,42,32,66,105,116,119,105,115,101,32,99,111,109,98,105,110,97,116,105,111,110,32,111,102,32,116,104,101,32,109,101,109,98,101,114,115,32,111,102,32,116,104,101,32,35,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,32,101,110,117,109,
46,10,32,32,32,32,32,42,32,84,104,105,115,32,115,112,101,99,105,102,105,101,115,32,119,104,105,99,104,32,116,121,112,101,115,32,111,102,32,112,114,105,109,105,116,105,118,101,115,32,97,114,101,32,112,114,101,115,101,110,116,32,105,110,32,116,104,101,
32,109,101,115,104,46,10,32,32,32,32,32,42,32,84,104,101,32,34,83,111,114,116,66,121,80,114,105,109,105,116,105,118,101,84,121,112,101,34,45,83,116,101,112,32,99,97,110,32,98,101,32,117,115,101,100,32,116,111,32,109,97,107,101,32,115,117,114,101,32,116,
104,101,10,32,32,32,32,32,42,32,111,117,116,112,117,116,32,109,101,115,104,101,115,32,99,111,110,115,105,115,116,32,111,102,32,111,110,101,32,112,114,105,109,105,116,105,118,101,32,116,121,112,101,32,101,97,99,104,46,10,32,32,32,32,32,42,47,10,32,32,
32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,80,114,105,109,105,116,105,118,101,84,121,112,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,118,101,114,116,105,99,101,115,
32,105,110,32,116,104,105,115,32,109,101,115,104,46,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,97,108,115,111,32,116,104,101,32,115,105,122,101,32,111,102,32,97,108,108,32,111,102,32,116,104,101,32,112,101,114,45,118,101,114,116,101,120,32,
100,97,116,97,32,97,114,114,97,121,115,46,10,32,32,32,32,32,42,32,84,104,101,32,109,97,120,105,109,117,109,32,118,97,108,117,101,32,102,111,114,32,116,104,105,115,32,109,101,109,98,101,114,32,105,115,32,35,65,73,95,77,65,88,95,86,69,82,84,73,67,69,83,
46,10,32,32,32,32,32,42,47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,86,101,114,116,105,99,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,112,114,
105,109,105,116,105,118,101,115,32,40,116,114,105,97,110,103,108,101,115,44,32,112,111,108,121,103,111,110,115,44,32,108,105,110,101,115,41,32,105,110,32,116,104,105,115,32,32,109,101,115,104,46,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,97,
108,115,111,32,116,104,101,32,115,105,122,101,32,111,102,32,116,104,101,32,109,70,97,99,101,115,32,97,114,114,97,121,46,10,32,32,32,32,32,42,32,84,104,101,32,109,97,120,105,109,117,109,32,118,97,108,117,101,32,102,111,114,32,116,104,105,115,32,109,101,
109,98,101,114,32,105,115,32,35,65,73,95,77,65,88,95,70,65,67,69,83,46,10,32,32,32,32,32,42,47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,70,97,99,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,
114,105,101,102,32,86,101,114,116,101,120,32,112,111,115,105,116,105,111,110,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,97,114,114,97,121,32,105,115,32,97,108,119,97,121,115,32,112,114,101,115,101,110,116,32,105,110,32,97,32,
109,101,115,104,46,32,84,104,101,32,97,114,114,97,121,32,105,115,10,32,32,32,32,32,42,32,109,78,117,109,86,101,114,116,105,99,101,115,32,105,110,32,115,105,122,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,
116,111,114,51,68,32,42,109,86,101,114,116,105,99,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,86,101,114,116,101,120,32,110,111,114,109,97,108,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,101,32,
97,114,114,97,121,32,99,111,110,116,97,105,110,115,32,110,111,114,109,97,108,105,122,101,100,32,118,101,99,116,111,114,115,44,32,110,117,108,108,112,116,114,32,105,102,32,110,111,116,32,112,114,101,115,101,110,116,46,10,32,32,32,32,32,42,32,84,104,101,
32,97,114,114,97,121,32,105,115,32,109,78,117,109,86,101,114,116,105,99,101,115,32,105,110,32,115,105,122,101,46,32,78,111,114,109,97,108,115,32,97,114,101,32,117,110,100,101,102,105,110,101,100,32,102,111,114,10,32,32,32,32,32,42,32,112,111,105,110,
116,32,97,110,100,32,108,105,110,101,32,112,114,105,109,105,116,105,118,101,115,46,32,65,32,109,101,115,104,32,99,111,110,115,105,115,116,105,110,103,32,111,102,32,112,111,105,110,116,115,32,97,110,100,10,32,32,32,32,32,42,32,108,105,110,101,115,32,111,
110,108,121,32,109,97,121,32,110,111,116,32,104,97,118,101,32,110,111,114,109,97,108,32,118,101,99,116,111,114,115,46,32,77,101,115,104,101,115,32,119,105,116,104,32,109,105,120,101,100,10,32,32,32,32,32,42,32,112,114,105,109,105,116,105,118,101,32,116,
121,112,101,115,32,40,105,46,101,46,32,108,105,110,101,115,32,97,110,100,32,116,114,105,97,110,103,108,101,115,41,32,109,97,121,32,104,97,118,101,32,110,111,114,109,97,108,115,44,10,32,32,32,32,32,42,32,98,117,116,32,116,104,101,32,110,111,114,109,97,
108,115,32,102,111,114,32,118,101,114,116,105,99,101,115,32,116,104,97,116,32,97,114,101,32,111,110,108,121,32,114,101,102,101,114,101,110,99,101,100,32,98,121,10,32,32,32,32,32,42,32,112,111,105,110,116,32,111,114,32,108,105,110,101,32,112,114,105,109,
105,116,105,118,101,115,32,97,114,101,32,117,110,100,101,102,105,110,101,100,32,97,110,100,32,115,101,116,32,116,111,32,81,78,97,78,32,40,87,65,82,78,58,10,32,32,32,32,32,42,32,113,78,97,78,32,99,111,109,112,97,114,101,115,32,116,111,32,105,110,101,113,
117,97,108,32,116,111,32,42,101,118,101,114,121,116,104,105,110,103,42,44,32,101,118,101,110,32,116,111,32,113,78,97,78,32,105,116,115,101,108,102,46,10,32,32,32,32,32,42,32,85,115,105,110,103,32,99,111,100,101,32,108,105,107,101,32,116,104,105,115,32,
116,111,32,99,104,101,99,107,32,119,104,101,116,104,101,114,32,97,32,102,105,101,108,100,32,105,115,32,113,110,97,110,32,105,115,58,10,32,32,32,32,32,42,32,64,99,111,100,101,10,32,32,32,32,32,42,32,35,100,101,102,105,110,101,32,73,83,95,81,78,65,78,40,
102,41,32,40,102,32,33,61,32,102,41,10,32,32,32,32,32,42,32,64,101,110,100,99,111,100,101,10,32,32,32,32,32,42,32,115,116,105,108,108,32,100,97,110,103,101,114,111,117,115,32,98,101,99,97,117,115,101,32,101,118,101,110,32,49,46,102,32,61,61,32,49,46,
102,32,99,111,117,108,100,32,101,118,97,108,117,97,116,101,32,116,111,32,102,97,108,115,101,33,32,40,10,32,32,32,32,32,42,32,114,101,109,101,109,98,101,114,32,116,104,101,32,115,117,98,116,108,101,116,105,101,115,32,111,102,32,73,69,69,69,55,53,52,32,
97,114,116,105,116,104,109,101,116,105,99,115,41,46,32,85,115,101,32,115,116,117,102,102,32,108,105,107,101,10,32,32,32,32,32,42,32,64,99,32,102,112,99,108,97,115,115,105,102,121,32,105,110,115,116,101,97,100,46,10,32,32,32,32,32,42,32,64,110,111,116,
101,32,78,111,114,109,97,108,32,118,101,99,116,111,114,115,32,99,111,109,112,117,116,101,100,32,98,121,32,65,115,115,105,109,112,32,97,114,101,32,97,108,119,97,121,115,32,117,110,105,116,45,108,101,110,103,116,104,46,10,32,32,32,32,32,42,32,72,111,119,
101,118,101,114,44,32,116,104,105,115,32,110,101,101,100,110,39,116,32,97,112,112,108,121,32,102,111,114,32,110,111,114,109,97,108,115,32,116,104,97,116,32,104,97,118,101,32,98,101,101,110,32,116,97,107,101,110,10,32,32,32,32,32,42,32,100,105,114,101,
99,116,108,121,32,102,114,111,109,32,116,104,101,32,109,111,100,101,108,32,102,105,108,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,78,111,114,109,97,108,115,59,10,10,32,32,32,32,
47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,86,101,114,116,101,120,32,116,97,110,103,101,110,116,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,101,32,116,97,110,103,101,110,116,32,111,102,32,97,32,118,101,114,116,101,120,32,
112,111,105,110,116,115,32,105,110,32,116,104,101,32,100,105,114,101,99,116,105,111,110,32,111,102,32,116,104,101,32,112,111,115,105,116,105,118,101,10,32,32,32,32,32,42,32,88,32,116,101,120,116,117,114,101,32,97,120,105,115,46,32,84,104,101,32,97,114,
114,97,121,32,99,111,110,116,97,105,110,115,32,110,111,114,109,97,108,105,122,101,100,32,118,101,99,116,111,114,115,44,32,110,117,108,108,112,116,114,32,105,102,10,32,32,32,32,32,42,32,110,111,116,32,112,114,101,115,101,110,116,46,32,84,104,101,32,97,
114,114,97,121,32,105,115,32,109,78,117,109,86,101,114,116,105,99,101,115,32,105,110,32,115,105,122,101,46,32,65,32,109,101,115,104,32,99,111,110,115,105,115,116,105,110,103,10,32,32,32,32,32,42,32,111,102,32,112,111,105,110,116,115,32,97,110,100,32,
108,105,110,101,115,32,111,110,108,121,32,109,97,121,32,110,111,116,32,104,97,118,101,32,110,111,114,109,97,108,32,118,101,99,116,111,114,115,46,32,77,101,115,104,101,115,32,119,105,116,104,10,32,32,32,32,32,42,32,109,105,120,101,100,32,112,114,105,109,
105,116,105,118,101,32,116,121,112,101,115,32,40,105,46,101,46,32,108,105,110,101,115,32,97,110,100,32,116,114,105,97,110,103,108,101,115,41,32,109,97,121,32,104,97,118,101,10,32,32,32,32,32,42,32,110,111,114,109,97,108,115,44,32,98,117,116,32,116,104,
101,32,110,111,114,109,97,108,115,32,102,111,114,32,118,101,114,116,105,99,101,115,32,116,104,97,116,32,97,114,101,32,111,110,108,121,32,114,101,102,101,114,101,110,99,101,100,32,98,121,10,32,32,32,32,32,42,32,112,111,105,110,116,32,111,114,32,108,105,
110,101,32,112,114,105,109,105,116,105,118,101,115,32,97,114,101,32,117,110,100,101,102,105,110,101,100,32,97,110,100,32,115,101,116,32,116,111,32,113,78,97,78,46,32,32,83,101,101,10,32,32,32,32,32,42,32,116,104,101,32,35,109,78,111,114,109,97,108,115,
32,109,101,109,98,101,114,32,102,111,114,32,97,32,100,101,116,97,105,108,101,100,32,100,105,115,99,117,115,115,105,111,110,32,111,102,32,113,78,97,78,115,46,10,32,32,32,32,32,42,32,64,110,111,116,101,32,73,102,32,116,104,101,32,109,101,115,104,32,99,
111,110,116,97,105,110,115,32,116,97,110,103,101,110,116,115,44,32,105,116,32,97,117,116,111,109,97,116,105,99,97,108,108,121,32,97,108,115,111,10,32,32,32,32,32,42,32,99,111,110,116,97,105,110,115,32,98,105,116,97,110,103,101,110,116,115,46,10,32,32,
32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,84,97,110,103,101,110,116,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,86,101,114,116,101,120,32,98,105,116,97,
110,103,101,110,116,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,101,32,98,105,116,97,110,103,101,110,116,32,111,102,32,97,32,118,101,114,116,101,120,32,112,111,105,110,116,115,32,105,110,32,116,104,101,32,100,105,114,101,99,116,105,111,
110,32,111,102,32,116,104,101,32,112,111,115,105,116,105,118,101,10,32,32,32,32,32,42,32,89,32,116,101,120,116,117,114,101,32,97,120,105,115,46,32,84,104,101,32,97,114,114,97,121,32,99,111,110,116,97,105,110,115,32,110,111,114,109,97,108,105,122,101,
100,32,118,101,99,116,111,114,115,44,32,110,117,108,108,112,116,114,32,105,102,32,110,111,116,10,32,32,32,32,32,42,32,112,114,101,115,101,110,116,46,32,84,104,101,32,97,114,114,97,121,32,105,115,32,109,78,117,109,86,101,114,116,105,99,101,115,32,105,
110,32,115,105,122,101,46,10,32,32,32,32,32,42,32,64,110,111,116,101,32,73,102,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,116,97,110,103,101,110,116,115,44,32,105,116,32,97,117,116,111,109,97,116,105,99,97,108,108,121,32,97,
108,115,111,32,99,111,110,116,97,105,110,115,10,32,32,32,32,32,42,32,98,105,116,97,110,103,101,110,116,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,99,116,111,114,51,68,32,42,109,66,105,116,97,110,103,101,110,
116,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,86,101,114,116,101,120,32,99,111,108,111,114,32,115,101,116,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,109,101,115,104,32,109,97,121,32,99,111,110,116,
97,105,110,32,48,32,116,111,32,35,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,32,118,101,114,116,101,120,10,32,32,32,32,32,42,32,99,111,108,111,114,115,32,112,101,114,32,118,101,114,116,101,120,46,32,110,117,108,108,
112,116,114,32,105,102,32,110,111,116,32,112,114,101,115,101,110,116,46,32,69,97,99,104,32,97,114,114,97,121,32,105,115,10,32,32,32,32,32,42,32,109,78,117,109,86,101,114,116,105,99,101,115,32,105,110,32,115,105,122,101,32,105,102,32,112,114,101,115,101,
110,116,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,67,111,108,111,114,52,68,32,42,109,67,111,108,111,114,115,91,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,93,59,10,10,32,32,32,32,
47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,86,101,114,116,101,120,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,44,32,97,108,115,111,32,107,110,111,119,110,32,97,115,32,85,86,32,99,104,97,110,110,101,108,115,
46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,109,101,115,104,32,109,97,121,32,99,111,110,116,97,105,110,32,48,32,116,111,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,32,99,104,97,110,110,101,108,
115,32,112,101,114,10,32,32,32,32,32,42,32,118,101,114,116,101,120,46,32,85,115,101,100,32,97,110,100,32,117,110,117,115,101,100,32,40,110,117,108,108,112,116,114,41,32,99,104,97,110,110,101,108,115,32,109,97,121,32,103,111,32,105,110,32,97,110,121,32,
111,114,100,101,114,46,10,32,32,32,32,32,42,32,84,104,101,32,97,114,114,97,121,32,105,115,32,109,78,117,109,86,101,114,116,105,99,101,115,32,105,110,32,115,105,122,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,
99,116,111,114,51,68,32,42,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,93,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,
32,83,112,101,99,105,102,105,101,115,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,99,111,109,112,111,110,101,110,116,115,32,102,111,114,32,97,32,103,105,118,101,110,32,85,86,32,99,104,97,110,110,101,108,46,10,32,32,32,32,32,42,10,32,32,32,32,
32,42,32,85,112,32,116,111,32,116,104,114,101,101,32,99,104,97,110,110,101,108,115,32,97,114,101,32,115,117,112,112,111,114,116,101,100,32,40,85,86,87,44,32,102,111,114,32,97,99,99,101,115,115,105,110,103,32,118,111,108,117,109,101,10,32,32,32,32,32,
42,32,111,114,32,99,117,98,101,32,109,97,112,115,41,46,32,73,102,32,116,104,101,32,118,97,108,117,101,32,105,115,32,50,32,102,111,114,32,97,32,103,105,118,101,110,32,99,104,97,110,110,101,108,32,110,44,32,116,104,101,10,32,32,32,32,32,42,32,99,111,109,
112,111,110,101,110,116,32,112,46,122,32,111,102,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,110,93,91,112,93,32,105,115,32,115,101,116,32,116,111,32,48,46,48,102,46,10,32,32,32,32,32,42,32,73,102,32,116,104,101,32,118,97,108,117,101,
32,105,115,32,49,32,102,111,114,32,97,32,103,105,118,101,110,32,99,104,97,110,110,101,108,44,32,112,46,121,32,105,115,32,115,101,116,32,116,111,32,48,46,48,102,44,32,116,111,111,46,10,32,32,32,32,32,42,32,64,110,111,116,101,32,52,68,32,99,111,111,114,
100,105,110,97,116,101,115,32,97,114,101,32,110,111,116,32,115,117,112,112,111,114,116,101,100,10,32,32,32,32,32,42,47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,85,86,67,111,109,112,111,110,101,110,116,115,91,65,
73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,93,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,84,104,101,32,102,97,99,101,115,32,116,104,101,32,109,101,115,104,32,105,115,32,99,
111,110,115,116,114,117,99,116,101,100,32,102,114,111,109,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,69,97,99,104,32,102,97,99,101,32,114,101,102,101,114,115,32,116,111,32,97,32,110,117,109,98,101,114,32,111,102,32,118,101,114,116,105,99,101,115,
32,98,121,32,116,104,101,105,114,32,105,110,100,105,99,101,115,46,10,32,32,32,32,32,42,32,84,104,105,115,32,97,114,114,97,121,32,105,115,32,97,108,119,97,121,115,32,112,114,101,115,101,110,116,32,105,110,32,97,32,109,101,115,104,44,32,105,116,115,32,
115,105,122,101,32,105,115,32,103,105,118,101,110,10,32,32,32,32,32,42,32,32,105,110,32,109,78,117,109,70,97,99,101,115,46,32,73,102,32,116,104,101,32,35,65,73,95,83,67,69,78,69,95,70,76,65,71,83,95,78,79,78,95,86,69,82,66,79,83,69,95,70,79,82,77,65,
84,10,32,32,32,32,32,42,32,105,115,32,78,79,84,32,115,101,116,32,101,97,99,104,32,102,97,99,101,32,114,101,102,101,114,101,110,99,101,115,32,97,110,32,117,110,105,113,117,101,32,115,101,116,32,111,102,32,118,101,114,116,105,99,101,115,46,10,32,32,32,
32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,70,97,99,101,32,42,109,70,97,99,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,42,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,98,111,110,101,115,32,116,104,105,115,32,109,101,
115,104,32,99,111,110,116,97,105,110,115,46,32,67,97,110,32,98,101,32,48,44,32,105,110,32,119,104,105,99,104,32,99,97,115,101,32,116,104,101,32,109,66,111,110,101,115,32,97,114,114,97,121,32,105,115,32,110,117,108,108,112,116,114,46,10,32,32,32,32,42,
47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,66,111,110,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,84,104,101,32,98,111,110,101,115,32,111,102,32,116,104,105,115,32,109,
101,115,104,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,98,111,110,101,32,99,111,110,115,105,115,116,115,32,111,102,32,97,32,110,97,109,101,32,98,121,32,119,104,105,99,104,32,105,116,32,99,97,110,32,98,101,32,102,111,117,110,100,32,105,110,
32,116,104,101,10,32,32,32,32,32,42,32,102,114,97,109,101,32,104,105,101,114,97,114,99,104,121,32,97,110,100,32,97,32,115,101,116,32,111,102,32,118,101,114,116,101,120,32,119,101,105,103,104,116,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,
84,82,85,67,84,32,97,105,66,111,110,101,32,42,42,109,66,111,110,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,64,98,114,105,101,102,32,84,104,101,32,109,97,116,101,114,105,97,108,32,117,115,101,100,32,98,121,32,116,104,105,115,32,109,
101,115,104,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,109,101,115,104,32,117,115,101,115,32,111,110,108,121,32,97,32,115,105,110,103,108,101,32,109,97,116,101,114,105,97,108,46,32,73,102,32,97,110,32,105,109,112,111,114,116,101,100,32,109,
111,100,101,108,32,117,115,101,115,10,32,32,32,32,32,42,32,109,117,108,116,105,112,108,101,32,109,97,116,101,114,105,97,108,115,44,32,116,104,101,32,105,109,112,111,114,116,32,115,112,108,105,116,115,32,117,112,32,116,104,101,32,109,101,115,104,46,32,
85,115,101,32,116,104,105,115,32,118,97,108,117,101,10,32,32,32,32,32,42,32,97,115,32,105,110,100,101,120,32,105,110,116,111,32,116,104,101,32,115,99,101,110,101,39,115,32,109,97,116,101,114,105,97,108,32,108,105,115,116,46,10,32,32,32,32,32,42,47,10,
32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,77,97,116,101,114,105,97,108,73,110,100,101,120,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,78,97,109,101,32,111,102,32,116,104,101,32,109,101,115,104,46,32,77,101,115,104,
101,115,32,99,97,110,32,98,101,32,110,97,109,101,100,44,32,98,117,116,32,116,104,105,115,32,105,115,32,110,111,116,32,97,10,32,32,32,32,32,42,32,32,114,101,113,117,105,114,101,109,101,110,116,32,97,110,100,32,108,101,97,118,105,110,103,32,116,104,105,
115,32,102,105,101,108,100,32,101,109,112,116,121,32,105,115,32,116,111,116,97,108,108,121,32,102,105,110,101,46,10,32,32,32,32,32,42,32,32,84,104,101,114,101,32,97,114,101,32,109,97,105,110,108,121,32,116,104,114,101,101,32,117,115,101,115,32,102,111,
114,32,109,101,115,104,32,110,97,109,101,115,58,10,32,32,32,32,32,42,32,32,32,45,32,115,111,109,101,32,102,111,114,109,97,116,115,32,110,97,109,101,32,110,111,100,101,115,32,97,110,100,32,109,101,115,104,101,115,32,105,110,100,101,112,101,110,100,101,
110,116,108,121,46,10,32,32,32,32,32,42,32,32,32,45,32,105,109,112,111,114,116,101,114,115,32,116,101,110,100,32,116,111,32,115,112,108,105,116,32,109,101,115,104,101,115,32,117,112,32,116,111,32,109,101,101,116,32,116,104,101,10,32,32,32,32,32,42,32,
32,32,32,32,32,111,110,101,45,109,97,116,101,114,105,97,108,45,112,101,114,45,109,101,115,104,32,114,101,113,117,105,114,101,109,101,110,116,46,32,65,115,115,105,103,110,105,110,103,10,32,32,32,32,32,42,32,32,32,32,32,32,116,104,101,32,115,97,109,101,
32,40,100,117,109,109,121,41,32,110,97,109,101,32,116,111,32,101,97,99,104,32,111,102,32,116,104,101,32,114,101,115,117,108,116,32,109,101,115,104,101,115,10,32,32,32,32,32,42,32,32,32,32,32,32,97,105,100,115,32,116,104,101,32,99,97,108,108,101,114,32,
97,116,32,114,101,99,111,118,101,114,105,110,103,32,116,104,101,32,111,114,105,103,105,110,97,108,32,109,101,115,104,10,32,32,32,32,32,42,32,32,32,32,32,32,112,97,114,116,105,116,105,111,110,105,110,103,46,10,32,32,32,32,32,42,32,32,32,45,32,86,101,114,
116,101,120,32,97,110,105,109,97,116,105,111,110,115,32,114,101,102,101,114,32,116,111,32,109,101,115,104,101,115,32,98,121,32,116,104,101,105,114,32,110,97,109,101,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,83,116,
114,105,110,103,32,109,78,97,109,101,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,97,116,116,97,99,104,109,101,110,116,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,32,67,117,114,114,101,
110,116,108,121,32,107,110,111,119,110,32,116,111,32,119,111,114,107,32,119,105,116,104,32,108,111,97,100,101,114,115,58,10,32,32,32,32,32,42,32,45,32,67,111,108,108,97,100,97,10,32,32,32,32,32,42,32,45,32,103,108,116,102,10,32,32,32,32,32,42,47,10,32,
32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,65,110,105,109,77,101,115,104,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,65,116,116,97,99,104,109,101,110,116,32,109,101,115,104,101,115,32,102,111,114,32,116,
104,105,115,32,109,101,115,104,44,32,102,111,114,32,118,101,114,116,101,120,45,98,97,115,101,100,32,97,110,105,109,97,116,105,111,110,46,10,32,32,32,32,32,42,32,65,116,116,97,99,104,109,101,110,116,32,109,101,115,104,101,115,32,99,97,114,114,121,32,114,
101,112,108,97,99,101,109,101,110,116,32,100,97,116,97,32,102,111,114,32,115,111,109,101,32,111,102,32,116,104,101,10,32,32,32,32,32,42,32,109,101,115,104,39,101,115,32,118,101,114,116,101,120,32,99,111,109,112,111,110,101,110,116,115,32,40,117,115,117,
97,108,108,121,32,112,111,115,105,116,105,111,110,115,44,32,110,111,114,109,97,108,115,41,46,10,32,32,32,32,32,42,32,67,117,114,114,101,110,116,108,121,32,107,110,111,119,110,32,116,111,32,119,111,114,107,32,119,105,116,104,32,108,111,97,100,101,114,
115,58,10,32,32,32,32,32,42,32,45,32,67,111,108,108,97,100,97,10,32,32,32,32,32,42,32,45,32,103,108,116,102,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,65,110,105,109,77,101,115,104,32,42,42,109,65,110,105,109,77,101,115,
104,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,77,101,116,104,111,100,32,111,102,32,109,111,114,112,104,105,110,103,32,119,104,101,110,32,97,110,105,109,45,109,101,115,104,101,115,32,97,114,101,32,115,112,101,99,105,102,105,101,
100,46,10,32,32,32,32,32,42,32,32,64,115,101,101,32,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,32,116,111,32,108,101,97,114,110,32,109,111,114,101,32,97,98,111,117,116,32,116,104,101,32,112,114,111,118,105,100,101,100,32,109,111,114,
112,104,105,110,103,32,116,97,114,103,101,116,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,101,110,117,109,32,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,32,109,77,101,116,104,111,100,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,
42,32,32,84,104,101,32,98,111,117,110,100,105,110,103,32,98,111,120,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,65,65,66,66,32,109,65,65,66,66,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,86,101,114,116,101,120,
32,85,86,32,115,116,114,101,97,109,32,110,97,109,101,115,46,32,80,111,105,110,116,101,114,32,116,111,32,97,114,114,97,121,32,111,102,32,115,105,122,101,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,10,32,
32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,83,116,114,105,110,103,32,42,42,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,59,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,
10,32,32,32,32,47,47,33,32,84,104,101,32,100,101,102,97,117,108,116,32,99,108,97,115,115,32,99,111,110,115,116,114,117,99,116,111,114,46,10,32,32,32,32,97,105,77,101,115,104,40,41,32,65,73,95,78,79,95,69,88,67,69,80,84,10,32,32,32,32,32,32,32,32,32,32,
32,32,58,32,109,80,114,105,109,105,116,105,118,101,84,121,112,101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,86,101,114,116,105,99,101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,70,97,
99,101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,86,101,114,116,105,99,101,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,78,111,114,109,97,108,115,40,110,117,108,108,112,116,114,41,44,
10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,84,97,110,103,101,110,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,66,105,116,97,110,103,101,110,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,109,67,111,108,111,114,115,123,110,117,108,108,112,116,114,125,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,123,110,117,108,108,112,116,114,125,44,10,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,109,78,117,109,85,86,67,111,109,112,111,110,101,110,116,115,123,48,125,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,70,97,99,101,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
109,78,117,109,66,111,110,101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,66,111,110,101,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,77,97,116,101,114,105,97,108,73,110,100,101,120,40,
48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,65,110,105,109,77,101,115,104,101,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,65,110,105,109,77,101,115,104,101,115,40,110,117,108,108,112,116,114,41,44,10,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,109,77,101,116,104,111,100,40,97,105,77,111,114,112,104,105,110,103,77,101,116,104,111,100,95,85,78,75,78,79,87,78,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,109,65,65,66,66,40,41,44,10,32,32,32,32,32,32,32,
32,32,32,32,32,32,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,40,110,117,108,108,112,116,114,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,
101,102,32,84,104,101,32,99,108,97,115,115,32,100,101,115,116,114,117,99,116,111,114,46,10,32,32,32,32,126,97,105,77,101,115,104,40,41,32,123,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,86,101,114,116,105,99,101,115,59,10,32,32,32,
32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,78,111,114,109,97,108,115,59,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,84,97,110,103,101,110,116,115,59,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,66,105,116,
97,110,103,101,110,116,115,59,10,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,59,
32,97,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,97,93,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,105,102,32,40,109,84,101,120,
116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,
70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,59,32,97,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,97,93,59,10,32,32,32,32,32,
32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,102,111,114,32,40,
117,110,115,105,103,110,101,100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,59,32,97,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,
91,93,32,109,67,111,108,111,114,115,91,97,93,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,47,47,32,68,79,32,78,79,84,32,82,69,77,79,86,69,32,84,72,73,83,32,65,68,68,73,84,73,79,78,65,76,32,67,72,69,67,75,10,32,32,32,32,32,32,32,32,
105,102,32,40,109,78,117,109,66,111,110,101,115,32,38,38,32,109,66,111,110,101,115,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,115,116,100,58,58,117,110,111,114,100,101,114,101,100,95,115,101,116,60,99,111,110,115,116,32,97,105,66,111,110,101,32,
42,62,32,98,111,110,101,115,59,10,32,32,32,32,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,109,78,117,109,66,111,110,101,115,59,32,97,43,43,41,32,123,10,32,32,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,105,102,32,40,109,66,111,110,101,115,91,97,93,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,98,111,110,101,115,46,105,110,115,101,114,116,40,109,66,111,110,101,115,91,97,93,41,59,10,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,32,32,32,32,102,111,114,32,40,99,111,110,115,116,32,97,105,66,111,110,101,32,42,98,111,110,101,58,32,98,111,110,101,115,41,32,123,10,32,32,32,
32,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,32,98,111,110,101,59,10,32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,66,111,110,101,115,59,10,32,32,32,32,32,32,32,32,
125,10,10,32,32,32,32,32,32,32,32,105,102,32,40,109,78,117,109,65,110,105,109,77,101,115,104,101,115,32,38,38,32,109,65,110,105,109,77,101,115,104,101,115,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,
100,32,105,110,116,32,97,32,61,32,48,59,32,97,32,60,32,109,78,117,109,65,110,105,109,77,101,115,104,101,115,59,32,97,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,32,109,65,110,105,109,77,101,115,104,101,115,
91,97,93,59,10,32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,65,110,105,109,77,101,115,104,101,115,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,100,101,108,101,116,
101,91,93,32,109,70,97,99,101,115,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,112,111,115,105,116,
105,111,110,115,46,32,80,114,111,118,105,100,101,100,32,110,111,32,115,112,101,99,105,97,108,10,32,32,32,32,47,47,33,32,32,32,32,32,32,32,32,115,99,101,110,101,32,102,108,97,103,115,32,97,114,101,32,115,101,116,44,32,116,104,105,115,32,119,105,108,108,
32,97,108,119,97,121,115,32,98,101,32,116,114,117,101,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,112,111,115,105,116,105,111,110,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,
102,32,110,111,116,46,10,32,32,32,32,98,111,111,108,32,72,97,115,80,111,115,105,116,105,111,110,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,86,101,114,116,105,99,101,115,32,33,61,32,110,117,108,108,
112,116,114,32,38,38,32,109,78,117,109,86,101,114,116,105,99,101,115,32,62,32,48,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,111,
110,116,97,105,110,115,32,102,97,99,101,115,46,32,73,102,32,110,111,32,115,112,101,99,105,97,108,32,115,99,101,110,101,32,102,108,97,103,115,10,32,32,32,32,47,47,33,32,32,32,32,32,32,32,32,97,114,101,32,115,101,116,32,116,104,105,115,32,115,104,111,117,
108,100,32,97,108,119,97,121,115,32,114,101,116,117,114,110,32,116,114,117,101,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,102,97,99,101,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,
32,105,102,32,110,111,116,46,10,32,32,32,32,98,111,111,108,32,72,97,115,70,97,99,101,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,70,97,99,101,115,32,33,61,32,110,117,108,108,112,116,114,32,38,38,32,
109,78,117,109,70,97,99,101,115,32,62,32,48,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,110,111,114,
109,97,108,32,118,101,99,116,111,114,115,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,110,111,114,109,97,108,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,
46,10,32,32,32,32,98,111,111,108,32,72,97,115,78,111,114,109,97,108,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,78,111,114,109,97,108,115,32,33,61,32,110,117,108,108,112,116,114,32,38,38,32,109,78,
117,109,86,101,114,116,105,99,101,115,32,62,32,48,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,116,
97,110,103,101,110,116,32,97,110,100,32,98,105,116,97,110,103,101,110,116,32,118,101,99,116,111,114,115,46,10,32,32,32,32,47,47,33,10,32,32,32,32,47,47,33,32,73,116,32,105,115,32,110,111,116,32,112,111,115,115,105,98,108,101,32,116,104,97,116,32,105,
116,32,99,111,110,116,97,105,110,115,32,116,97,110,103,101,110,116,115,32,97,110,100,32,110,111,32,98,105,116,97,110,103,101,110,116,115,10,32,32,32,32,47,47,33,32,40,111,114,32,116,104,101,32,111,116,104,101,114,32,119,97,121,32,114,111,117,110,100,
41,46,32,84,104,101,32,101,120,105,115,116,101,110,99,101,32,111,102,32,111,110,101,32,111,102,32,116,104,101,109,10,32,32,32,32,47,47,33,32,105,109,112,108,105,101,115,32,116,104,97,116,32,116,104,101,32,115,101,99,111,110,100,32,105,115,32,116,104,
101,114,101,44,32,116,111,111,46,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,116,97,110,103,101,110,116,115,32,97,110,100,32,98,105,45,116,97,110,103,101,110,116,115,32,97,114,101,32,115,116,111,114,101,100,
44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,98,111,111,108,32,72,97,115,84,97,110,103,101,110,116,115,65,110,100,66,105,116,97,110,103,101,110,116,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,
117,114,110,32,109,84,97,110,103,101,110,116,115,32,33,61,32,110,117,108,108,112,116,114,32,38,38,32,109,66,105,116,97,110,103,101,110,116,115,32,33,61,32,110,117,108,108,112,116,114,32,38,38,32,109,78,117,109,86,101,114,116,105,99,101,115,32,62,32,48,
59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,97,32,118,101,114,116,101,120,32,99,111,108,111,114,32,
115,101,116,10,32,32,32,32,47,47,33,32,64,112,97,114,97,109,32,105,110,100,101,120,32,32,32,32,73,110,100,101,120,32,111,102,32,116,104,101,32,118,101,114,116,101,120,32,99,111,108,111,114,32,115,101,116,10,32,32,32,32,47,47,33,32,64,114,101,116,117,
114,110,32,116,114,117,101,44,32,105,102,32,118,101,114,116,101,120,32,99,111,108,111,114,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,98,111,111,108,32,72,97,115,86,101,114,116,101,
120,67,111,108,111,114,115,40,117,110,115,105,103,110,101,100,32,105,110,116,32,105,110,100,101,120,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,105,110,100,101,120,32,62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,
70,95,67,79,76,79,82,95,83,69,84,83,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,67,111,108,111,114,115,91,105,
110,100,101,120,93,32,33,61,32,110,117,108,108,112,116,114,32,38,38,32,109,78,117,109,86,101,114,116,105,99,101,115,32,62,32,48,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,
114,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,97,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,115,101,116,10,32,32,32,32,47,47,33,32,64,112,97,114,97,109,32,105,110,100,101,120,32,32,32,32,73,
110,100,101,120,32,111,102,32,116,104,101,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,115,101,116,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,116,101,120,116,117,114,101,
32,99,111,111,114,100,105,110,97,116,101,115,32,97,114,101,32,115,116,111,114,101,100,44,32,102,97,108,115,101,32,105,102,32,110,111,116,46,10,32,32,32,32,98,111,111,108,32,72,97,115,84,101,120,116,117,114,101,67,111,111,114,100,115,40,117,110,115,105,
103,110,101,100,32,105,110,116,32,105,110,100,101,120,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,105,110,100,101,120,32,62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,41,
32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,40,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,105,110,100,
101,120,93,32,33,61,32,110,117,108,108,112,116,114,32,38,38,32,109,78,117,109,86,101,114,116,105,99,101,115,32,62,32,48,41,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,71,101,116,32,116,104,101,32,110,117,109,98,101,114,
32,111,102,32,85,86,32,99,104,97,110,110,101,108,115,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,46,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,115,116,111,114,101,
100,32,117,118,45,99,104,97,110,110,101,108,115,46,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,71,101,116,78,117,109,85,86,67,104,97,110,110,101,108,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,117,110,115,105,
103,110,101,100,32,105,110,116,32,110,40,48,41,59,10,32,32,32,32,32,32,32,32,102,111,114,32,40,117,110,115,105,103,110,101,100,32,105,32,61,32,48,59,32,105,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,
83,59,32,105,43,43,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,105,102,32,40,109,84,101,120,116,117,114,101,67,111,111,114,100,115,91,105,93,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,43,43,110,59,10,32,32,32,32,32,32,32,32,32,
32,32,32,125,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,110,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,71,101,116,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,118,
101,114,116,101,120,32,99,111,108,111,114,32,99,104,97,110,110,101,108,115,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,46,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,84,104,101,32,110,117,109,98,101,114,32,111,102,
32,115,116,111,114,101,100,32,99,111,108,111,114,32,99,104,97,110,110,101,108,115,46,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,71,101,116,78,117,109,67,111,108,111,114,67,104,97,110,110,101,108,115,40,41,32,99,111,110,115,116,32,
123,10,32,32,32,32,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,110,40,48,41,59,10,32,32,32,32,32,32,32,32,119,104,105,108,101,32,40,110,32,60,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,67,79,76,79,82,95,83,69,84,83,32,38,
38,32,109,67,111,108,111,114,115,91,110,93,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,43,43,110,59,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,110,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,
114,105,101,102,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,111,110,116,97,105,110,115,32,98,111,110,101,115,46,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,
98,111,110,101,115,32,97,114,101,32,115,116,111,114,101,100,46,10,32,32,32,32,98,111,111,108,32,72,97,115,66,111,110,101,115,40,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,66,111,110,101,115,32,33,61,32,110,
117,108,108,112,116,114,32,38,38,32,109,78,117,109,66,111,110,101,115,32,62,32,48,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,32,67,104,101,99,107,32,119,104,101,116,104,101,114,32,116,104,101,32,109,101,115,104,32,99,
111,110,116,97,105,110,115,32,97,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,115,101,116,32,110,97,109,101,10,32,32,32,32,47,47,33,32,64,112,97,114,97,109,32,112,73,110,100,101,120,32,73,110,100,101,120,32,111,102,32,116,
104,101,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,115,101,116,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,116,114,117,101,44,32,105,102,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,
116,101,115,32,102,111,114,32,116,104,101,32,105,110,100,101,120,32,101,120,105,115,116,115,46,10,32,32,32,32,98,111,111,108,32,72,97,115,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,40,117,110,115,105,103,110,101,100,32,105,110,116,
32,112,73,110,100,101,120,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,32,61,61,32,110,117,108,108,112,116,114,32,124,124,32,112,73,110,100,101,120,32,
62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,102,97,108,115,101,59,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,
32,114,101,116,117,114,110,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,112,73,110,100,101,120,93,32,33,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,32,
83,101,116,32,97,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,115,101,116,32,110,97,109,101,10,32,32,32,32,47,47,33,32,64,112,97,114,97,109,32,112,73,110,100,101,120,32,73,110,100,101,120,32,111,102,32,116,104,101,32,116,
101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,115,101,116,10,32,32,32,32,47,47,33,32,64,112,97,114,97,109,32,116,101,120,67,111,111,114,100,115,78,97,109,101,32,110,97,109,101,32,111,102,32,116,104,101,32,116,101,120,116,117,
114,101,32,99,111,111,114,100,105,110,97,116,101,32,115,101,116,10,32,32,32,32,118,111,105,100,32,83,101,116,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,40,117,110,115,105,103,110,101,100,32,105,110,116,32,112,73,110,100,101,120,44,
32,99,111,110,115,116,32,97,105,83,116,114,105,110,103,32,38,116,101,120,67,111,111,114,100,115,78,97,109,101,41,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,112,73,110,100,101,120,32,62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,
69,88,84,85,82,69,67,79,79,82,68,83,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,105,102,32,40,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,
101,115,32,61,61,32,110,117,108,108,112,116,114,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,47,47,32,67,111,110,115,116,114,117,99,116,32,97,110,100,32,110,117,108,108,45,105,110,105,116,32,97,114,114,97,121,10,32,32,32,32,32,32,32,32,32,32,32,32,
109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,32,61,32,110,101,119,32,97,105,83,116,114,105,110,103,32,42,91,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,93,59,10,32,32,32,32,32,32,
32,32,32,32,32,32,102,111,114,32,40,115,105,122,101,95,116,32,105,61,48,59,32,105,60,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,59,32,43,43,105,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,105,93,32,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,105,102,32,40,116,101,120,
67,111,111,114,100,115,78,97,109,101,46,108,101,110,103,116,104,32,61,61,32,48,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,100,101,108,101,116,101,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,112,73,110,100,101,120,
93,59,10,32,32,32,32,32,32,32,32,32,32,32,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,112,73,110,100,101,120,93,32,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,59,
10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,105,102,32,40,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,112,73,110,100,101,120,93,32,61,61,32,110,117,108,108,112,116,114,41,32,123,10,32,32,32,32,32,32,32,
32,32,32,32,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,112,73,110,100,101,120,93,32,61,32,110,101,119,32,97,105,83,116,114,105,110,103,40,116,101,120,67,111,111,114,100,115,78,97,109,101,41,59,10,32,32,32,32,32,32,32,
32,32,32,32,32,114,101,116,117,114,110,59,10,32,32,32,32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,42,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,112,73,110,100,101,120,93,32,61,32,116,101,120,67,111,111,114,100,115,
78,97,109,101,59,10,32,32,32,32,125,10,10,32,32,32,32,47,47,33,32,64,98,114,105,101,102,32,32,71,101,116,32,97,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,115,101,116,32,110,97,109,101,10,32,32,32,32,47,47,33,32,64,112,
97,114,97,109,32,32,112,73,110,100,101,120,32,73,110,100,101,120,32,111,102,32,116,104,101,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,115,101,116,10,32,32,32,32,47,47,33,32,64,114,101,116,117,114,110,32,84,104,101,
32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,110,97,109,101,46,10,32,32,32,32,99,111,110,115,116,32,97,105,83,116,114,105,110,103,32,42,71,101,116,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,40,117,110,
115,105,103,110,101,100,32,105,110,116,32,105,110,100,101,120,41,32,99,111,110,115,116,32,123,10,32,32,32,32,32,32,32,32,105,102,32,40,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,32,61,61,32,110,117,108,108,112,116,114,32,
124,124,32,105,110,100,101,120,32,62,61,32,65,73,95,77,65,88,95,78,85,77,66,69,82,95,79,70,95,84,69,88,84,85,82,69,67,79,79,82,68,83,41,32,123,10,32,32,32,32,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,110,117,108,108,112,116,114,59,10,32,32,32,
32,32,32,32,32,125,10,10,32,32,32,32,32,32,32,32,114,101,116,117,114,110,32,109,84,101,120,116,117,114,101,67,111,111,114,100,115,78,97,109,101,115,91,105,110,100,101,120,93,59,10,32,32,32,32,125,10,10,35,101,110,100,105,102,32,47,47,32,95,95,99,112,
108,117,115,112,108,117,115,10,125,59,10,10,47,42,42,10,32,42,32,64,98,114,105,101,102,32,32,65,32,115,107,101,108,101,116,111,110,32,98,111,110,101,32,114,101,112,114,101,115,101,110,116,115,32,97,32,115,105,110,103,108,101,32,98,111,110,101,32,105,
115,32,97,32,115,107,101,108,101,116,111,110,32,115,116,114,117,99,116,117,114,101,46,10,32,42,10,32,42,32,83,107,101,108,101,116,111,110,45,65,110,105,109,97,116,105,111,110,115,32,99,97,110,32,98,101,32,114,101,112,114,101,115,101,110,116,101,100,32,
118,105,97,32,97,32,115,107,101,108,101,116,111,110,32,115,116,114,117,99,116,44,32,119,104,105,99,104,32,100,101,115,99,114,105,98,101,115,10,32,42,32,97,32,104,105,101,114,97,114,99,104,105,99,97,108,32,116,114,101,101,32,97,115,115,101,109,98,108,
101,100,32,102,114,111,109,32,115,107,101,108,101,116,111,110,32,98,111,110,101,115,46,32,65,32,98,111,110,101,32,105,115,32,108,105,110,107,101,100,32,116,111,32,97,32,109,101,115,104,46,10,32,42,32,84,104,101,32,98,111,110,101,32,107,110,111,119,115,
32,105,116,115,32,112,97,114,101,110,116,32,98,111,110,101,46,32,73,102,32,116,104,101,114,101,32,105,115,32,110,111,32,112,97,114,101,110,116,32,98,111,110,101,32,116,104,101,32,112,97,114,101,110,116,32,105,100,32,105,115,10,32,42,32,109,97,114,107,
101,100,32,119,105,116,104,32,45,49,46,10,32,42,32,84,104,101,32,115,107,101,108,101,116,111,110,45,98,111,110,101,32,115,116,111,114,101,115,32,97,32,112,111,105,110,116,101,114,32,116,111,32,105,116,115,32,117,115,101,100,32,97,114,109,97,116,117,114,
101,46,32,73,102,32,116,104,101,114,101,32,105,115,32,110,111,10,32,42,32,97,114,109,97,116,117,114,101,32,116,104,105,115,32,118,97,108,117,101,32,105,102,32,115,101,116,32,116,111,32,110,117,108,108,112,116,114,46,10,32,42,32,65,32,115,107,101,108,
101,116,111,110,32,98,111,110,101,32,115,116,111,114,101,115,32,105,116,115,32,111,102,102,115,101,116,45,109,97,116,114,105,120,44,32,119,104,105,99,104,32,105,115,32,116,104,101,32,97,98,115,111,108,117,116,101,32,116,114,97,110,115,102,111,114,109,
97,116,105,111,110,10,32,42,32,102,111,114,32,116,104,101,32,98,111,110,101,46,32,84,104,101,32,98,111,110,101,32,115,116,111,114,101,115,32,116,104,101,32,108,111,99,97,108,101,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,32,116,111,32,105,
116,115,32,112,97,114,101,110,116,32,97,115,32,119,101,108,108,46,10,32,42,32,89,111,117,32,99,97,110,32,99,111,109,112,117,116,101,32,116,104,101,32,111,102,102,115,101,116,32,109,97,116,114,105,120,32,98,121,32,109,117,108,116,105,112,108,121,105,110,
103,32,116,104,101,32,104,105,101,114,97,114,99,104,121,32,108,105,107,101,58,10,32,42,32,84,114,101,101,58,32,115,49,32,45,62,32,115,50,32,45,62,32,115,51,10,32,42,32,79,102,102,115,101,116,45,77,97,116,114,105,120,32,115,51,32,61,32,108,111,99,97,108,
101,45,115,51,32,42,32,108,111,99,97,108,101,45,115,50,32,42,32,108,111,99,97,108,101,45,115,49,10,32,42,47,10,115,116,114,117,99,116,32,97,105,83,107,101,108,101,116,111,110,66,111,110,101,32,123,10,32,32,32,32,47,47,47,32,84,104,101,32,112,97,114,101,
110,116,32,98,111,110,101,32,105,110,100,101,120,44,32,105,115,32,45,49,32,111,110,101,32,105,102,32,116,104,105,115,32,98,111,110,101,32,114,101,112,114,101,115,101,110,116,115,32,116,104,101,32,114,111,111,116,32,98,111,110,101,46,10,32,32,32,32,105,
110,116,32,109,80,97,114,101,110,116,59,10,10,10,35,105,102,110,100,101,102,32,65,83,83,73,77,80,95,66,85,73,76,68,95,78,79,95,65,82,77,65,84,85,82,69,80,79,80,85,76,65,84,69,95,80,82,79,67,69,83,83,10,32,32,32,32,47,47,47,32,64,98,114,105,101,102,32,
84,104,101,32,98,111,110,101,32,97,114,109,97,116,117,114,101,32,110,111,100,101,32,45,32,117,115,101,100,32,102,111,114,32,115,107,101,108,101,116,111,110,32,99,111,110,118,101,114,115,105,111,110,10,32,32,32,32,47,47,47,32,121,111,117,32,109,117,115,
116,32,101,110,97,98,108,101,32,97,105,80,114,111,99,101,115,115,95,80,111,112,117,108,97,116,101,65,114,109,97,116,117,114,101,68,97,116,97,32,116,111,32,112,111,112,117,108,97,116,101,32,116,104,105,115,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,
105,78,111,100,101,32,42,109,65,114,109,97,116,117,114,101,59,10,10,32,32,32,32,47,47,47,32,64,98,114,105,101,102,32,84,104,101,32,98,111,110,101,32,110,111,100,101,32,105,110,32,116,104,101,32,115,99,101,110,101,32,45,32,117,115,101,100,32,102,111,114,
32,115,107,101,108,101,116,111,110,32,99,111,110,118,101,114,115,105,111,110,10,32,32,32,32,47,47,47,32,121,111,117,32,109,117,115,116,32,101,110,97,98,108,101,32,97,105,80,114,111,99,101,115,115,95,80,111,112,117,108,97,116,101,65,114,109,97,116,117,
114,101,68,97,116,97,32,116,111,32,112,111,112,117,108,97,116,101,32,116,104,105,115,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,78,111,100,101,32,42,109,78,111,100,101,59,10,10,35,101,110,100,105,102,10,32,32,32,32,47,47,47,32,64,98,114,105,101,
102,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,119,101,105,103,104,116,115,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,117,109,110,87,101,105,103,104,116,115,59,10,10,32,32,32,32,47,47,47,32,84,104,101,32,109,101,
115,104,32,105,110,100,101,120,44,32,119,104,105,99,104,32,119,105,108,108,32,103,101,116,32,105,110,102,108,117,101,110,99,101,100,32,98,121,32,116,104,101,32,119,101,105,103,104,116,46,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,77,101,115,104,
32,42,109,77,101,115,104,73,100,59,10,10,32,32,32,32,47,47,47,32,84,104,101,32,105,110,102,108,117,101,110,99,101,32,119,101,105,103,104,116,115,32,111,102,32,116,104,105,115,32,98,111,110,101,44,32,98,121,32,118,101,114,116,101,120,32,105,110,100,101,
120,46,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,86,101,114,116,101,120,87,101,105,103,104,116,32,42,109,87,101,105,103,104,116,115,59,10,10,32,32,32,32,47,42,42,32,77,97,116,114,105,120,32,116,104,97,116,32,116,114,97,110,115,102,111,114,109,
115,32,102,114,111,109,32,98,111,110,101,32,115,112,97,99,101,32,116,111,32,109,101,115,104,32,115,112,97,99,101,32,105,110,32,98,105,110,100,32,112,111,115,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,109,97,116,114,105,120,
32,100,101,115,99,114,105,98,101,115,32,116,104,101,32,112,111,115,105,116,105,111,110,32,111,102,32,116,104,101,32,109,101,115,104,10,32,32,32,32,32,42,32,105,110,32,116,104,101,32,108,111,99,97,108,32,115,112,97,99,101,32,111,102,32,116,104,105,115,
32,98,111,110,101,32,119,104,101,110,32,116,104,101,32,115,107,101,108,101,116,111,110,32,119,97,115,32,98,111,117,110,100,46,10,32,32,32,32,32,42,32,84,104,117,115,32,105,116,32,99,97,110,32,98,101,32,117,115,101,100,32,100,105,114,101,99,116,108,121,
32,116,111,32,100,101,116,101,114,109,105,110,101,32,97,32,100,101,115,105,114,101,100,32,118,101,114,116,101,120,32,112,111,115,105,116,105,111,110,44,10,32,32,32,32,32,42,32,103,105,118,101,110,32,116,104,101,32,119,111,114,108,100,45,115,112,97,99,
101,32,116,114,97,110,115,102,111,114,109,32,111,102,32,116,104,101,32,98,111,110,101,32,119,104,101,110,32,97,110,105,109,97,116,101,100,44,10,32,32,32,32,32,42,32,97,110,100,32,116,104,101,32,112,111,115,105,116,105,111,110,32,111,102,32,116,104,101,
32,118,101,114,116,101,120,32,105,110,32,109,101,115,104,32,115,112,97,99,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,73,116,32,105,115,32,115,111,109,101,116,105,109,101,115,32,99,97,108,108,101,100,32,97,110,32,105,110,118,101,114,115,101,45,
98,105,110,100,32,109,97,116,114,105,120,44,10,32,32,32,32,32,42,32,111,114,32,105,110,118,101,114,115,101,32,98,105,110,100,32,112,111,115,101,32,109,97,116,114,105,120,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,77,97,
116,114,105,120,52,120,52,32,109,79,102,102,115,101,116,77,97,116,114,105,120,59,10,10,32,32,32,32,47,47,47,32,77,97,116,114,105,120,32,116,104,97,116,32,116,114,97,110,115,102,111,114,109,115,32,116,104,101,32,108,111,99,97,108,101,32,98,111,110,101,
32,105,110,32,98,105,110,100,32,112,111,115,101,46,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,77,97,116,114,105,120,52,120,52,32,109,76,111,99,97,108,77,97,116,114,105,120,59,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,
115,10,32,32,32,32,47,47,47,9,64,98,114,105,101,102,32,84,104,101,32,99,108,97,115,115,32,99,111,110,115,116,114,117,99,116,111,114,46,10,32,32,32,32,97,105,83,107,101,108,101,116,111,110,66,111,110,101,40,41,32,58,10,32,32,32,32,32,32,32,32,32,32,32,
32,109,80,97,114,101,110,116,40,45,49,41,44,10,35,105,102,110,100,101,102,32,65,83,83,73,77,80,95,66,85,73,76,68,95,78,79,95,65,82,77,65,84,85,82,69,80,79,80,85,76,65,84,69,95,80,82,79,67,69,83,83,10,32,32,32,32,32,32,32,32,32,32,32,32,109,65,114,109,
97,116,117,114,101,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,111,100,101,40,110,117,108,108,112,116,114,41,44,10,35,101,110,100,105,102,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,110,87,101,105,103,
104,116,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,77,101,115,104,73,100,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,
32,32,32,32,32,32,32,109,79,102,102,115,101,116,77,97,116,114,105,120,40,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,76,111,99,97,108,77,97,116,114,105,120,40,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,
10,32,32,32,32,47,47,47,32,64,98,114,105,101,102,32,84,104,101,32,99,108,97,115,115,32,99,111,110,115,116,114,117,99,116,111,114,32,119,105,116,104,32,105,116,115,32,112,97,114,101,110,116,10,32,32,32,32,47,47,47,32,64,112,97,114,97,109,32,32,112,97,
114,101,110,116,32,32,32,32,32,32,84,104,101,32,112,97,114,101,110,116,32,110,111,100,101,32,105,110,100,101,120,46,10,32,32,32,32,97,105,83,107,101,108,101,116,111,110,66,111,110,101,40,117,110,115,105,103,110,101,100,32,105,110,116,32,112,97,114,101,
110,116,41,32,58,10,32,32,32,32,32,32,32,32,32,32,32,32,109,80,97,114,101,110,116,40,112,97,114,101,110,116,41,44,10,35,105,102,110,100,101,102,32,65,83,83,73,77,80,95,66,85,73,76,68,95,78,79,95,65,82,77,65,84,85,82,69,80,79,80,85,76,65,84,69,95,80,82,
79,67,69,83,83,10,32,32,32,32,32,32,32,32,32,32,32,32,109,65,114,109,97,116,117,114,101,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,78,111,100,101,40,110,117,108,108,112,116,114,41,44,10,35,101,110,100,105,102,10,32,
32,32,32,32,32,32,32,32,32,32,32,109,78,117,109,110,87,101,105,103,104,116,115,40,48,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,77,101,115,104,73,100,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,87,101,105,103,
104,116,115,40,110,117,108,108,112,116,114,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,79,102,102,115,101,116,77,97,116,114,105,120,40,41,44,10,32,32,32,32,32,32,32,32,32,32,32,32,109,76,111,99,97,108,77,97,116,114,105,120,40,41,32,123,10,32,32,
32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,32,32,32,32,47,47,47,32,64,98,114,105,101,102,32,84,104,101,32,99,108,97,115,115,32,100,101,115,116,114,117,99,116,111,114,46,10,32,32,32,32,126,97,105,83,107,101,108,101,116,111,110,
66,111,110,101,40,41,32,123,10,32,32,32,32,32,32,32,32,100,101,108,101,116,101,91,93,32,109,87,101,105,103,104,116,115,59,10,32,32,32,32,32,32,32,32,109,87,101,105,103,104,116,115,32,61,32,110,117,108,108,112,116,114,59,10,32,32,32,32,125,10,35,101,110,
100,105,102,32,47,47,32,95,95,99,112,108,117,115,112,108,117,115,10,125,59,10,47,42,42,10,32,42,32,64,98,114,105,101,102,32,65,32,115,107,101,108,101,116,111,110,32,114,101,112,114,101,115,101,110,116,115,32,116,104,101,32,98,111,110,101,32,104,105,101,
114,97,114,99,104,121,32,111,102,32,97,110,32,97,110,105,109,97,116,105,111,110,46,10,32,42,10,32,42,32,83,107,101,108,101,116,111,110,32,97,110,105,109,97,116,105,111,110,115,32,99,97,110,32,98,101,32,100,101,115,99,114,105,98,101,100,32,97,115,32,97,
32,116,114,101,101,32,111,102,32,98,111,110,101,115,58,10,32,42,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,114,111,111,116,10,32,42,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,10,32,42,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,32,32,32,110,111,100,101,49,10,32,42,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,92,10,32,42,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,110,111,100,101,51,32,32,110,111,100,101,52,10,32,42,32,73,102,32,121,111,117,32,
119,97,110,116,32,116,111,32,99,97,108,99,117,108,97,116,101,32,116,104,101,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,32,111,102,32,110,111,100,101,32,116,104,114,101,101,32,121,111,117,32,110,101,101,100,32,116,111,32,99,111,109,112,117,
116,101,32,116,104,101,10,32,42,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,32,104,105,101,114,97,114,99,104,121,32,102,111,114,32,116,104,101,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,32,99,104,97,105,110,32,111,102,32,110,
111,100,101,51,58,10,32,42,32,114,111,111,116,45,62,110,111,100,101,49,45,62,110,111,100,101,51,10,32,42,32,69,97,99,104,32,110,111,100,101,32,105,115,32,114,101,112,114,101,115,101,110,116,101,100,32,97,115,32,97,32,115,107,101,108,101,116,111,110,32,
105,110,115,116,97,110,99,101,46,10,32,42,47,10,115,116,114,117,99,116,32,97,105,83,107,101,108,101,116,111,110,32,123,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,84,104,101,32,110,97,109,101,32,111,102,32,116,104,101,
32,115,107,101,108,101,116,111,110,32,105,110,115,116,97,110,99,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,83,116,114,105,110,103,32,109,78,97,109,101,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,
114,105,101,102,32,32,84,104,101,32,110,117,109,98,101,114,32,111,102,32,98,111,110,101,115,32,105,110,32,116,104,101,32,115,107,101,108,101,116,111,110,46,10,32,32,32,32,32,42,47,10,32,32,32,32,117,110,115,105,103,110,101,100,32,105,110,116,32,109,78,
117,109,66,111,110,101,115,59,10,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,32,64,98,114,105,101,102,32,84,104,101,32,98,111,110,101,32,105,110,115,116,97,110,99,101,32,105,110,32,116,104,101,32,115,107,101,108,101,116,111,110,46,10,32,32,32,32,
32,42,47,10,32,32,32,32,67,95,83,84,82,85,67,84,32,97,105,83,107,101,108,101,116,111,110,66,111,110,101,32,42,42,109,66,111,110,101,115,59,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,32,32,32,32,47,42,42,10,32,32,32,32,
32,42,32,32,64,98,114,105,101,102,32,84,104,101,32,99,108,97,115,115,32,99,111,110,115,116,114,117,99,116,111,114,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,83,107,101,108,101,116,111,110,40,41,32,65,73,95,78,79,95,69,88,67,69,80,84,32,58,32,109,
78,97,109,101,40,41,44,32,109,78,117,109,66,111,110,101,115,40,48,41,44,32,109,66,111,110,101,115,40,110,117,108,108,112,116,114,41,32,123,10,32,32,32,32,32,32,32,32,47,47,32,101,109,112,116,121,10,32,32,32,32,125,10,10,32,32,32,32,47,42,42,10,32,32,
32,32,32,42,32,32,64,98,114,105,101,102,32,32,84,104,101,32,99,108,97,115,115,32,100,101,115,116,114,117,99,116,111,114,46,10,32,32,32,32,32,42,47,10,32,32,32,32,126,97,105,83,107,101,108,101,116,111,110,40,41,32,123,10,32,32,32,32,32,32,32,32,100,101,
108,101,116,101,91,93,32,109,66,111,110,101,115,59,10,32,32,32,32,125,10,35,101,110,100,105,102,32,47,47,32,95,95,99,112,108,117,115,112,108,117,115,10,125,59,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,125,10,35,101,110,
100,105,102,32,47,47,33,32,101,120,116,101,114,110,32,34,67,34,10,10,35,101,110,100,105,102,32,47,47,32,65,73,95,77,69,83,72,95,72,95,73,78,67,10,10,0,0 };

const char* mesh_h = (const char*) temp_binary_data_2;

//================== postprocess.h ==================
static const unsigned char temp_binary_data_3[] =
{ 47,42,10,79,112,101,110,32,65,115,115,101,116,32,73,109,112,111,114,116,32,76,105,98,114,97,114,121,32,40,97,115,115,105,109,112,41,10,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,10,67,111,112,121,114,105,103,104,116,32,40,99,41,32,50,48,48,54,45,50,48,50,53,44,32,97,115,115,105,109,112,32,116,101,97,109,10,10,65,108,108,32,114,105,
103,104,116,115,32,114,101,115,101,114,118,101,100,46,10,10,82,101,100,105,115,116,114,105,98,117,116,105,111,110,32,97,110,100,32,117,115,101,32,111,102,32,116,104,105,115,32,115,111,102,116,119,97,114,101,32,105,110,32,115,111,117,114,99,101,32,97,
110,100,32,98,105,110,97,114,121,32,102,111,114,109,115,44,10,119,105,116,104,32,111,114,32,119,105,116,104,111,117,116,32,109,111,100,105,102,105,99,97,116,105,111,110,44,32,97,114,101,32,112,101,114,109,105,116,116,101,100,32,112,114,111,118,105,100,
101,100,32,116,104,97,116,32,116,104,101,10,102,111,108,108,111,119,105,110,103,32,99,111,110,100,105,116,105,111,110,115,32,97,114,101,32,109,101,116,58,10,10,42,32,82,101,100,105,115,116,114,105,98,117,116,105,111,110,115,32,111,102,32,115,111,117,
114,99,101,32,99,111,100,101,32,109,117,115,116,32,114,101,116,97,105,110,32,116,104,101,32,97,98,111,118,101,10,32,32,99,111,112,121,114,105,103,104,116,32,110,111,116,105,99,101,44,32,116,104,105,115,32,108,105,115,116,32,111,102,32,99,111,110,100,
105,116,105,111,110,115,32,97,110,100,32,116,104,101,10,32,32,102,111,108,108,111,119,105,110,103,32,100,105,115,99,108,97,105,109,101,114,46,10,10,42,32,82,101,100,105,115,116,114,105,98,117,116,105,111,110,115,32,105,110,32,98,105,110,97,114,121,32,
102,111,114,109,32,109,117,115,116,32,114,101,112,114,111,100,117,99,101,32,116,104,101,32,97,98,111,118,101,10,32,32,99,111,112,121,114,105,103,104,116,32,110,111,116,105,99,101,44,32,116,104,105,115,32,108,105,115,116,32,111,102,32,99,111,110,100,105,
116,105,111,110,115,32,97,110,100,32,116,104,101,10,32,32,102,111,108,108,111,119,105,110,103,32,100,105,115,99,108,97,105,109,101,114,32,105,110,32,116,104,101,32,100,111,99,117,109,101,110,116,97,116,105,111,110,32,97,110,100,47,111,114,32,111,116,
104,101,114,10,32,32,109,97,116,101,114,105,97,108,115,32,112,114,111,118,105,100,101,100,32,119,105,116,104,32,116,104,101,32,100,105,115,116,114,105,98,117,116,105,111,110,46,10,10,42,32,78,101,105,116,104,101,114,32,116,104,101,32,110,97,109,101,32,
111,102,32,116,104,101,32,97,115,115,105,109,112,32,116,101,97,109,44,32,110,111,114,32,116,104,101,32,110,97,109,101,115,32,111,102,32,105,116,115,10,32,32,99,111,110,116,114,105,98,117,116,111,114,115,32,109,97,121,32,98,101,32,117,115,101,100,32,116,
111,32,101,110,100,111,114,115,101,32,111,114,32,112,114,111,109,111,116,101,32,112,114,111,100,117,99,116,115,10,32,32,100,101,114,105,118,101,100,32,102,114,111,109,32,116,104,105,115,32,115,111,102,116,119,97,114,101,32,119,105,116,104,111,117,116,
32,115,112,101,99,105,102,105,99,32,112,114,105,111,114,10,32,32,119,114,105,116,116,101,110,32,112,101,114,109,105,115,115,105,111,110,32,111,102,32,116,104,101,32,97,115,115,105,109,112,32,116,101,97,109,46,10,10,84,72,73,83,32,83,79,70,84,87,65,82,
69,32,73,83,32,80,82,79,86,73,68,69,68,32,66,89,32,84,72,69,32,67,79,80,89,82,73,71,72,84,32,72,79,76,68,69,82,83,32,65,78,68,32,67,79,78,84,82,73,66,85,84,79,82,83,10,34,65,83,32,73,83,34,32,65,78,68,32,65,78,89,32,69,88,80,82,69,83,83,32,79,82,32,73,
77,80,76,73,69,68,32,87,65,82,82,65,78,84,73,69,83,44,32,73,78,67,76,85,68,73,78,71,44,32,66,85,84,32,78,79,84,10,76,73,77,73,84,69,68,32,84,79,44,32,84,72,69,32,73,77,80,76,73,69,68,32,87,65,82,82,65,78,84,73,69,83,32,79,70,32,77,69,82,67,72,65,78,84,
65,66,73,76,73,84,89,32,65,78,68,32,70,73,84,78,69,83,83,32,70,79,82,10,65,32,80,65,82,84,73,67,85,76,65,82,32,80,85,82,80,79,83,69,32,65,82,69,32,68,73,83,67,76,65,73,77,69,68,46,32,73,78,32,78,79,32,69,86,69,78,84,32,83,72,65,76,76,32,84,72,69,32,67,
79,80,89,82,73,71,72,84,10,79,87,78,69,82,32,79,82,32,67,79,78,84,82,73,66,85,84,79,82,83,32,66,69,32,76,73,65,66,76,69,32,70,79,82,32,65,78,89,32,68,73,82,69,67,84,44,32,73,78,68,73,82,69,67,84,44,32,73,78,67,73,68,69,78,84,65,76,44,10,83,80,69,67,73,
65,76,44,32,69,88,69,77,80,76,65,82,89,44,32,79,82,32,67,79,78,83,69,81,85,69,78,84,73,65,76,32,68,65,77,65,71,69,83,32,40,73,78,67,76,85,68,73,78,71,44,32,66,85,84,32,78,79,84,10,76,73,77,73,84,69,68,32,84,79,44,32,80,82,79,67,85,82,69,77,69,78,84,32,
79,70,32,83,85,66,83,84,73,84,85,84,69,32,71,79,79,68,83,32,79,82,32,83,69,82,86,73,67,69,83,59,32,76,79,83,83,32,79,70,32,85,83,69,44,10,68,65,84,65,44,32,79,82,32,80,82,79,70,73,84,83,59,32,79,82,32,66,85,83,73,78,69,83,83,32,73,78,84,69,82,82,85,80,
84,73,79,78,41,32,72,79,87,69,86,69,82,32,67,65,85,83,69,68,32,65,78,68,32,79,78,32,65,78,89,10,84,72,69,79,82,89,32,79,70,32,76,73,65,66,73,76,73,84,89,44,32,87,72,69,84,72,69,82,32,73,78,32,67,79,78,84,82,65,67,84,44,32,83,84,82,73,67,84,32,76,73,65,
66,73,76,73,84,89,44,32,79,82,32,84,79,82,84,10,40,73,78,67,76,85,68,73,78,71,32,78,69,71,76,73,71,69,78,67,69,32,79,82,32,79,84,72,69,82,87,73,83,69,41,32,65,82,73,83,73,78,71,32,73,78,32,65,78,89,32,87,65,89,32,79,85,84,32,79,70,32,84,72,69,32,85,83,
69,10,79,70,32,84,72,73,83,32,83,79,70,84,87,65,82,69,44,32,69,86,69,78,32,73,70,32,65,68,86,73,83,69,68,32,79,70,32,84,72,69,32,80,79,83,83,73,66,73,76,73,84,89,32,79,70,32,83,85,67,72,32,68,65,77,65,71,69,46,10,10,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,42,47,10,10,47,42,42,32,64,102,105,108,101,32,112,111,115,116,112,114,111,
99,101,115,115,46,104,10,32,42,32,32,64,98,114,105,101,102,32,68,101,102,105,110,105,116,105,111,110,115,32,102,111,114,32,105,109,112,111,114,116,32,112,111,115,116,32,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,115,10,32,42,47,10,35,112,
114,97,103,109,97,32,111,110,99,101,10,35,105,102,110,100,101,102,32,65,73,95,80,79,83,84,80,82,79,67,69,83,83,95,72,95,73,78,67,10,35,100,101,102,105,110,101,32,65,73,95,80,79,83,84,80,82,79,67,69,83,83,95,72,95,73,78,67,10,10,35,105,110,99,108,117,
100,101,32,60,97,115,115,105,109,112,47,116,121,112,101,115,46,104,62,10,10,35,105,102,100,101,102,32,95,95,71,78,85,67,95,95,10,35,32,32,32,112,114,97,103,109,97,32,71,67,67,32,115,121,115,116,101,109,95,104,101,97,100,101,114,10,35,101,110,100,105,
102,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,101,120,116,101,114,110,32,34,67,34,32,123,10,35,101,110,100,105,102,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,42,32,64,101,110,117,109,32,32,97,105,80,111,115,116,80,114,111,99,101,115,115,
83,116,101,112,115,10,32,42,32,32,64,98,114,105,101,102,32,68,101,102,105,110,101,115,32,116,104,101,32,102,108,97,103,115,32,102,111,114,32,97,108,108,32,112,111,115,115,105,98,108,101,32,112,111,115,116,32,112,114,111,99,101,115,115,105,110,103,32,
115,116,101,112,115,46,10,32,42,10,32,42,32,32,64,110,111,116,101,32,83,111,109,101,32,115,116,101,112,115,32,97,114,101,32,105,110,102,108,117,101,110,99,101,100,32,98,121,32,112,114,111,112,101,114,116,105,101,115,32,115,101,116,32,111,110,32,116,104,
101,32,65,115,115,105,109,112,58,58,73,109,112,111,114,116,101,114,32,105,116,115,101,108,102,10,32,42,10,32,42,32,32,64,115,101,101,32,65,115,115,105,109,112,58,58,73,109,112,111,114,116,101,114,58,58,82,101,97,100,70,105,108,101,40,41,10,32,42,32,32,
64,115,101,101,32,65,115,115,105,109,112,58,58,73,109,112,111,114,116,101,114,58,58,83,101,116,80,114,111,112,101,114,116,121,73,110,116,101,103,101,114,40,41,10,32,42,32,32,64,115,101,101,32,97,105,73,109,112,111,114,116,70,105,108,101,10,32,42,32,32,
64,115,101,101,32,97,105,73,109,112,111,114,116,70,105,108,101,69,120,10,32,42,47,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,101,110,117,109,32,97,105,80,111,115,116,80,114,111,99,101,115,115,83,116,101,112,115,10,123,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,67,97,108,99,117,108,97,116,
101,115,32,116,104,101,32,116,97,110,103,101,110,116,115,32,97,110,100,32,98,105,116,97,110,103,101,110,116,115,32,102,111,114,32,116,104,101,32,105,109,112,111,114,116,101,100,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,
68,111,101,115,32,110,111,116,104,105,110,103,32,105,102,32,97,32,109,101,115,104,32,100,111,101,115,32,110,111,116,32,104,97,118,101,32,110,111,114,109,97,108,115,46,32,89,111,117,32,109,105,103,104,116,32,119,97,110,116,32,116,104,105,115,32,112,111,
115,116,10,32,32,32,32,32,42,32,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,116,111,32,98,101,32,101,120,101,99,117,116,101,100,32,105,102,32,121,111,117,32,112,108,97,110,32,116,111,32,117,115,101,32,116,97,110,103,101,110,116,32,115,
112,97,99,101,32,99,97,108,99,117,108,97,116,105,111,110,115,10,32,32,32,32,32,42,32,115,117,99,104,32,97,115,32,110,111,114,109,97,108,32,109,97,112,112,105,110,103,32,32,97,112,112,108,105,101,100,32,116,111,32,116,104,101,32,109,101,115,104,101,115,
46,32,84,104,101,114,101,39,115,32,97,110,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,44,10,32,32,32,32,32,42,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,67,84,95,77,65,88,95,83,77,79,79,84,72,73,78,71,95,65,78,
71,76,69,60,47,116,116,62,44,32,119,104,105,99,104,32,97,108,108,111,119,115,32,121,111,117,32,116,111,32,115,112,101,99,105,102,121,10,32,32,32,32,32,42,32,97,32,109,97,120,105,109,117,109,32,115,109,111,111,116,104,105,110,103,32,97,110,103,108,101,
32,102,111,114,32,116,104,101,32,97,108,103,111,114,105,116,104,109,46,32,72,111,119,101,118,101,114,44,32,117,115,117,97,108,108,121,32,121,111,117,39,108,108,10,32,32,32,32,32,42,32,119,97,110,116,32,116,111,32,108,101,97,118,101,32,105,116,32,97,116,
32,116,104,101,32,100,101,102,97,117,108,116,32,118,97,108,117,101,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,67,97,108,99,84,97,110,103,101,110,116,83,112,97,99,101,32,61,32,48,120,49,44,10,10,32,32,32,32,47,47,32,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,
114,62,73,100,101,110,116,105,102,105,101,115,32,97,110,100,32,106,111,105,110,115,32,105,100,101,110,116,105,99,97,108,32,118,101,114,116,101,120,32,100,97,116,97,32,115,101,116,115,32,119,105,116,104,105,110,32,97,108,108,10,32,32,32,32,32,42,32,32,
105,109,112,111,114,116,101,100,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,102,116,101,114,32,116,104,105,115,32,115,116,101,112,32,105,115,32,114,117,110,44,32,101,97,99,104,32,109,101,115,104,32,99,111,110,116,97,
105,110,115,32,117,110,105,113,117,101,32,118,101,114,116,105,99,101,115,44,10,32,32,32,32,32,42,32,115,111,32,97,32,118,101,114,116,101,120,32,109,97,121,32,98,101,32,117,115,101,100,32,98,121,32,109,117,108,116,105,112,108,101,32,102,97,99,101,115,
46,32,89,111,117,32,117,115,117,97,108,108,121,32,119,97,110,116,10,32,32,32,32,32,42,32,116,111,32,117,115,101,32,116,104,105,115,32,112,111,115,116,32,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,46,32,73,102,32,121,111,117,114,32,97,112,
112,108,105,99,97,116,105,111,110,32,100,101,97,108,115,32,119,105,116,104,10,32,32,32,32,32,42,32,105,110,100,101,120,101,100,32,103,101,111,109,101,116,114,121,44,32,116,104,105,115,32,115,116,101,112,32,105,115,32,99,111,109,112,117,108,115,111,114,
121,32,111,114,32,121,111,117,39,108,108,32,106,117,115,116,32,119,97,115,116,101,32,114,101,110,100,101,114,105,110,103,10,32,32,32,32,32,42,32,116,105,109,101,46,32,60,98,62,73,102,32,116,104,105,115,32,102,108,97,103,32,105,115,32,110,111,116,32,115,
112,101,99,105,102,105,101,100,60,47,98,62,44,32,110,111,32,118,101,114,116,105,99,101,115,32,97,114,101,32,114,101,102,101,114,101,110,99,101,100,32,98,121,10,32,32,32,32,32,42,32,109,111,114,101,32,116,104,97,110,32,111,110,101,32,102,97,99,101,32,
97,110,100,32,60,98,62,110,111,32,105,110,100,101,120,32,98,117,102,102,101,114,32,105,115,32,114,101,113,117,105,114,101,100,60,47,98,62,32,102,111,114,32,114,101,110,100,101,114,105,110,103,46,10,32,32,32,32,32,42,32,85,110,108,101,115,115,32,116,104,
101,32,105,109,112,111,114,116,101,114,32,40,108,105,107,101,32,112,108,121,41,32,104,97,100,32,116,111,32,115,112,108,105,116,32,118,101,114,116,105,99,101,115,46,32,84,104,101,110,32,121,111,117,32,110,101,101,100,32,111,110,101,32,114,101,103,97,114,
100,108,101,115,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,101,114,116,105,99,101,115,32,61,32,48,120,50,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,67,111,110,118,101,
114,116,115,32,97,108,108,32,116,104,101,32,105,109,112,111,114,116,101,100,32,100,97,116,97,32,116,111,32,97,32,108,101,102,116,45,104,97,110,100,101,100,32,99,111,111,114,100,105,110,97,116,101,32,115,112,97,99,101,46,10,32,32,32,32,32,42,10,32,32,
32,32,32,42,32,66,121,32,100,101,102,97,117,108,116,32,116,104,101,32,100,97,116,97,32,105,115,32,114,101,116,117,114,110,101,100,32,105,110,32,97,32,114,105,103,104,116,45,104,97,110,100,101,100,32,99,111,111,114,100,105,110,97,116,101,32,115,112,97,
99,101,32,40,119,104,105,99,104,10,32,32,32,32,32,42,32,79,112,101,110,71,76,32,112,114,101,102,101,114,115,41,46,32,73,110,32,116,104,105,115,32,115,112,97,99,101,44,32,43,88,32,112,111,105,110,116,115,32,116,111,32,116,104,101,32,114,105,103,104,116,
44,10,32,32,32,32,32,42,32,43,90,32,112,111,105,110,116,115,32,116,111,119,97,114,100,115,32,116,104,101,32,118,105,101,119,101,114,44,32,97,110,100,32,43,89,32,112,111,105,110,116,115,32,117,112,119,97,114,100,115,46,32,73,110,32,116,104,101,32,68,105,
114,101,99,116,88,10,32,32,32,32,32,42,32,99,111,111,114,100,105,110,97,116,101,32,115,112,97,99,101,32,43,88,32,112,111,105,110,116,115,32,116,111,32,116,104,101,32,114,105,103,104,116,44,32,43,89,32,112,111,105,110,116,115,32,117,112,119,97,114,100,
115,44,32,97,110,100,32,43,90,32,112,111,105,110,116,115,10,32,32,32,32,32,42,32,97,119,97,121,32,102,114,111,109,32,116,104,101,32,118,105,101,119,101,114,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,89,111,117,39,108,108,32,112,114,111,98,97,98,
108,121,32,119,97,110,116,32,116,111,32,99,111,110,115,105,100,101,114,32,116,104,105,115,32,102,108,97,103,32,105,102,32,121,111,117,32,117,115,101,32,68,105,114,101,99,116,51,68,32,102,111,114,10,32,32,32,32,32,42,32,114,101,110,100,101,114,105,110,
103,46,32,84,104,101,32,35,97,105,80,114,111,99,101,115,115,95,67,111,110,118,101,114,116,84,111,76,101,102,116,72,97,110,100,101,100,32,102,108,97,103,32,115,117,112,101,114,115,101,100,101,115,32,116,104,105,115,10,32,32,32,32,32,42,32,115,101,116,
116,105,110,103,32,97,110,100,32,98,117,110,100,108,101,115,32,97,108,108,32,99,111,110,118,101,114,115,105,111,110,115,32,116,121,112,105,99,97,108,108,121,32,114,101,113,117,105,114,101,100,32,102,111,114,32,68,51,68,45,98,97,115,101,100,10,32,32,32,
32,32,42,32,97,112,112,108,105,99,97,116,105,111,110,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,77,97,107,101,76,101,102,116,72,97,110,100,101,100,32,61,32,48,120,52,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,114,
105,97,110,103,117,108,97,116,101,115,32,97,108,108,32,102,97,99,101,115,32,111,102,32,97,108,108,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,66,121,32,100,101,102,97,117,108,116,32,116,104,101,32,105,109,112,111,114,116,
101,100,32,109,101,115,104,32,100,97,116,97,32,109,105,103,104,116,32,99,111,110,116,97,105,110,32,102,97,99,101,115,32,119,105,116,104,32,109,111,114,101,32,116,104,97,110,32,51,10,32,32,32,32,32,42,32,105,110,100,105,99,101,115,46,32,70,111,114,32,
114,101,110,100,101,114,105,110,103,32,121,111,117,39,108,108,32,117,115,117,97,108,108,121,32,119,97,110,116,32,97,108,108,32,102,97,99,101,115,32,116,111,32,98,101,32,116,114,105,97,110,103,108,101,115,46,10,32,32,32,32,32,42,32,84,104,105,115,32,112,
111,115,116,32,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,115,112,108,105,116,115,32,117,112,32,102,97,99,101,115,32,119,105,116,104,32,109,111,114,101,32,116,104,97,110,32,51,32,105,110,100,105,99,101,115,32,105,110,116,111,10,32,32,
32,32,32,42,32,116,114,105,97,110,103,108,101,115,46,32,76,105,110,101,32,97,110,100,32,112,111,105,110,116,32,112,114,105,109,105,116,105,118,101,115,32,97,114,101,32,42,110,111,116,42,32,109,111,100,105,102,105,101,100,33,32,73,102,32,121,111,117,32,
119,97,110,116,10,32,32,32,32,32,42,32,39,116,114,105,97,110,103,108,101,115,32,111,110,108,121,39,32,119,105,116,104,32,110,111,32,111,116,104,101,114,32,107,105,110,100,115,32,111,102,32,112,114,105,109,105,116,105,118,101,115,44,32,116,114,121,32,
116,104,101,32,102,111,108,108,111,119,105,110,103,10,32,32,32,32,32,42,32,115,111,108,117,116,105,111,110,58,10,32,32,32,32,32,42,32,60,117,108,62,10,32,32,32,32,32,42,32,60,108,105,62,83,112,101,99,105,102,121,32,98,111,116,104,32,35,97,105,80,114,
111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,32,97,110,100,32,35,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,101,32,60,47,108,105,62,10,32,32,32,32,32,42,32,60,108,105,62,73,103,110,111,114,101,32,97,108,
108,32,112,111,105,110,116,32,97,110,100,32,108,105,110,101,32,109,101,115,104,101,115,32,119,104,101,110,32,121,111,117,32,112,114,111,99,101,115,115,32,97,115,115,105,109,112,39,115,32,111,117,116,112,117,116,60,47,108,105,62,10,32,32,32,32,32,42,32,
60,47,117,108,62,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,32,61,32,48,120,56,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,82,101,109,111,118,101,115,32,115,111,109,101,32,112,97,114,
116,115,32,111,102,32,116,104,101,32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,32,40,97,110,105,109,97,116,105,111,110,115,44,32,109,97,116,101,114,105,97,108,115,44,10,32,32,32,32,32,42,32,32,108,105,103,104,116,32,115,111,117,114,99,101,115,
44,32,99,97,109,101,114,97,115,44,32,116,101,120,116,117,114,101,115,44,32,118,101,114,116,101,120,32,99,111,109,112,111,110,101,110,116,115,41,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,101,32,32,99,111,109,112,111,110,101,110,116,115,32,
116,111,32,98,101,32,114,101,109,111,118,101,100,32,97,114,101,32,115,112,101,99,105,102,105,101,100,32,105,110,32,97,32,115,101,112,97,114,97,116,101,10,32,32,32,32,32,42,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,44,32,60,
116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,82,86,67,95,70,76,65,71,83,60,47,116,116,62,46,32,84,104,105,115,32,105,115,32,113,117,105,116,101,32,117,115,101,102,117,108,10,32,32,32,32,32,42,32,105,102,32,121,111,117,32,100,111,110,39,116,32,
110,101,101,100,32,97,108,108,32,112,97,114,116,115,32,111,102,32,116,104,101,32,111,117,116,112,117,116,32,115,116,114,117,99,116,117,114,101,46,32,86,101,114,116,101,120,32,99,111,108,111,114,115,10,32,32,32,32,32,42,32,97,114,101,32,114,97,114,101,
108,121,32,117,115,101,100,32,116,111,100,97,121,32,102,111,114,32,101,120,97,109,112,108,101,46,46,46,32,67,97,108,108,105,110,103,32,116,104,105,115,32,115,116,101,112,32,116,111,32,114,101,109,111,118,101,32,117,110,110,101,101,100,101,100,10,32,32,
32,32,32,42,32,100,97,116,97,32,102,114,111,109,32,116,104,101,32,112,105,112,101,108,105,110,101,32,97,115,32,101,97,114,108,121,32,97,115,32,112,111,115,115,105,98,108,101,32,114,101,115,117,108,116,115,32,105,110,32,105,110,99,114,101,97,115,101,100,
10,32,32,32,32,32,42,32,112,101,114,102,111,114,109,97,110,99,101,32,97,110,100,32,97,32,109,111,114,101,32,111,112,116,105,109,105,122,101,100,32,111,117,116,112,117,116,32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,46,10,32,32,32,32,32,42,
32,84,104,105,115,32,115,116,101,112,32,105,115,32,97,108,115,111,32,117,115,101,102,117,108,32,105,102,32,121,111,117,32,119,97,110,116,32,116,111,32,102,111,114,99,101,32,65,115,115,105,109,112,32,116,111,32,114,101,99,111,109,112,117,116,101,10,32,
32,32,32,32,42,32,110,111,114,109,97,108,115,32,111,114,32,116,97,110,103,101,110,116,115,46,32,84,104,101,32,99,111,114,114,101,115,112,111,110,100,105,110,103,32,115,116,101,112,115,32,100,111,110,39,116,32,114,101,99,111,109,112,117,116,101,32,116,
104,101,109,32,105,102,10,32,32,32,32,32,42,32,116,104,101,121,39,114,101,32,97,108,114,101,97,100,121,32,116,104,101,114,101,32,40,108,111,97,100,101,100,32,102,114,111,109,32,116,104,101,32,115,111,117,114,99,101,32,97,115,115,101,116,41,46,32,66,121,
32,117,115,105,110,103,32,116,104,105,115,10,32,32,32,32,32,42,32,115,116,101,112,32,121,111,117,32,99,97,110,32,109,97,107,101,32,115,117,114,101,32,116,104,101,121,32,97,114,101,32,78,79,84,32,116,104,101,114,101,46,10,32,32,32,32,32,42,10,32,32,32,
32,32,42,32,84,104,105,115,32,102,108,97,103,32,105,115,32,97,32,112,111,111,114,32,111,110,101,44,32,109,97,105,110,108,121,32,98,101,99,97,117,115,101,32,105,116,115,32,112,117,114,112,111,115,101,32,105,115,32,117,115,117,97,108,108,121,10,32,32,32,
32,32,42,32,109,105,115,117,110,100,101,114,115,116,111,111,100,46,32,67,111,110,115,105,100,101,114,32,116,104,101,32,102,111,108,108,111,119,105,110,103,32,99,97,115,101,58,32,97,32,51,68,32,109,111,100,101,108,32,104,97,115,32,98,101,101,110,32,101,
120,112,111,114,116,101,100,10,32,32,32,32,32,42,32,102,114,111,109,32,97,32,67,65,68,32,97,112,112,44,32,97,110,100,32,105,116,32,104,97,115,32,112,101,114,45,102,97,99,101,32,118,101,114,116,101,120,32,99,111,108,111,114,115,46,32,86,101,114,116,101,
120,32,112,111,115,105,116,105,111,110,115,32,99,97,110,39,116,32,98,101,10,32,32,32,32,32,42,32,115,104,97,114,101,100,44,32,116,104,117,115,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,
101,114,116,105,99,101,115,32,115,116,101,112,32,102,97,105,108,115,32,116,111,10,32,32,32,32,32,42,32,111,112,116,105,109,105,122,101,32,116,104,101,32,100,97,116,97,32,98,101,99,97,117,115,101,32,111,102,32,116,104,101,115,101,32,110,97,115,116,121,
32,108,105,116,116,108,101,32,118,101,114,116,101,120,32,99,111,108,111,114,115,46,10,32,32,32,32,32,42,32,77,111,115,116,32,97,112,112,115,32,100,111,110,39,116,32,101,118,101,110,32,112,114,111,99,101,115,115,32,116,104,101,109,44,32,115,111,32,105,
116,39,115,32,97,108,108,32,102,111,114,32,110,111,116,104,105,110,103,46,32,66,121,32,117,115,105,110,103,10,32,32,32,32,32,42,32,116,104,105,115,32,115,116,101,112,44,32,117,110,110,101,101,100,101,100,32,99,111,109,112,111,110,101,110,116,115,32,97,
114,101,32,101,120,99,108,117,100,101,100,32,97,115,32,101,97,114,108,121,32,97,115,32,112,111,115,115,105,98,108,101,10,32,32,32,32,32,42,32,116,104,117,115,32,111,112,101,110,105,110,103,32,109,111,114,101,32,114,111,111,109,32,102,111,114,32,105,110,
116,101,114,110,97,108,32,111,112,116,105,109,105,122,97,116,105,111,110,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,82,101,109,111,118,101,67,111,109,112,111,110,101,110,116,32,61,32,48,120,49,48,44,10,10,32,32,
32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,
42,42,32,60,104,114,62,71,101,110,101,114,97,116,101,115,32,110,111,114,109,97,108,115,32,102,111,114,32,97,108,108,32,102,97,99,101,115,32,111,102,32,97,108,108,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,
32,105,115,32,105,103,110,111,114,101,100,32,105,102,32,110,111,114,109,97,108,115,32,97,114,101,32,97,108,114,101,97,100,121,32,116,104,101,114,101,32,97,116,32,116,104,101,32,116,105,109,101,32,116,104,105,115,32,102,108,97,103,10,32,32,32,32,32,42,
32,105,115,32,101,118,97,108,117,97,116,101,100,46,32,77,111,100,101,108,32,105,109,112,111,114,116,101,114,115,32,116,114,121,32,116,111,32,108,111,97,100,32,116,104,101,109,32,102,114,111,109,32,116,104,101,32,115,111,117,114,99,101,32,102,105,108,
101,44,32,115,111,10,32,32,32,32,32,42,32,116,104,101,121,39,114,101,32,117,115,117,97,108,108,121,32,97,108,114,101,97,100,121,32,116,104,101,114,101,46,32,70,97,99,101,32,110,111,114,109,97,108,115,32,97,114,101,32,115,104,97,114,101,100,32,98,101,
116,119,101,101,110,32,97,108,108,32,112,111,105,110,116,115,10,32,32,32,32,32,42,32,111,102,32,97,32,115,105,110,103,108,101,32,102,97,99,101,44,32,115,111,32,97,32,115,105,110,103,108,101,32,112,111,105,110,116,32,99,97,110,32,104,97,118,101,32,109,
117,108,116,105,112,108,101,32,110,111,114,109,97,108,115,44,32,119,104,105,99,104,10,32,32,32,32,32,42,32,102,111,114,99,101,115,32,116,104,101,32,108,105,98,114,97,114,121,32,116,111,32,100,117,112,108,105,99,97,116,101,32,118,101,114,116,105,99,101,
115,32,105,110,32,115,111,109,101,32,99,97,115,101,115,46,10,32,32,32,32,32,42,32,35,97,105,80,114,111,99,101,115,115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,101,114,116,105,99,101,115,32,105,115,32,42,115,101,110,115,101,108,101,115,115,
42,32,116,104,101,110,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,102,108,97,103,32,109,97,121,32,110,111,116,32,98,101,32,115,112,101,99,105,102,105,101,100,32,116,111,103,101,116,104,101,114,32,119,105,116,104,32,35,97,105,80,
114,111,99,101,115,115,95,71,101,110,83,109,111,111,116,104,78,111,114,109,97,108,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,101,110,78,111,114,109,97,108,115,32,61,32,48,120,50,48,44,10,10,32,32,32,32,47,47,
32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,
104,114,62,71,101,110,101,114,97,116,101,115,32,115,109,111,111,116,104,32,110,111,114,109,97,108,115,32,102,111,114,32,97,108,108,32,118,101,114,116,105,99,101,115,32,105,110,32,116,104,101,32,109,101,115,104,46,10,32,32,32,32,42,10,32,32,32,32,42,32,
84,104,105,115,32,105,115,32,105,103,110,111,114,101,100,32,105,102,32,110,111,114,109,97,108,115,32,97,114,101,32,97,108,114,101,97,100,121,32,116,104,101,114,101,32,97,116,32,116,104,101,32,116,105,109,101,32,116,104,105,115,32,102,108,97,103,10,32,
32,32,32,42,32,105,115,32,101,118,97,108,117,97,116,101,100,46,32,77,111,100,101,108,32,105,109,112,111,114,116,101,114,115,32,116,114,121,32,116,111,32,108,111,97,100,32,116,104,101,109,32,102,114,111,109,32,116,104,101,32,115,111,117,114,99,101,32,
102,105,108,101,44,32,115,111,10,32,32,32,32,42,32,116,104,101,121,39,114,101,32,117,115,117,97,108,108,121,32,97,108,114,101,97,100,121,32,116,104,101,114,101,46,10,32,32,32,32,42,10,32,32,32,32,42,32,84,104,105,115,32,102,108,97,103,32,109,97,121,32,
110,111,116,32,98,101,32,115,112,101,99,105,102,105,101,100,32,116,111,103,101,116,104,101,114,32,119,105,116,104,10,32,32,32,32,42,32,35,97,105,80,114,111,99,101,115,115,95,71,101,110,78,111,114,109,97,108,115,46,32,84,104,101,114,101,39,115,32,97,32,
105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,44,10,32,32,32,32,42,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,71,83,78,95,77,65,88,95,83,77,79,79,84,72,73,78,71,95,65,78,71,76,69,60,47,116,116,62,32,119,104,105,99,
104,32,97,108,108,111,119,115,32,121,111,117,32,116,111,32,115,112,101,99,105,102,121,10,32,32,32,32,42,32,97,110,32,97,110,103,108,101,32,109,97,120,105,109,117,109,32,102,111,114,32,116,104,101,32,110,111,114,109,97,108,32,115,109,111,111,116,104,105,
110,103,32,97,108,103,111,114,105,116,104,109,46,32,78,111,114,109,97,108,115,32,101,120,99,101,101,100,105,110,103,10,32,32,32,32,42,32,116,104,105,115,32,108,105,109,105,116,32,97,114,101,32,110,111,116,32,115,109,111,111,116,104,101,100,44,32,114,
101,115,117,108,116,105,110,103,32,105,110,32,97,32,39,104,97,114,100,39,32,115,101,97,109,32,98,101,116,119,101,101,110,32,116,119,111,32,102,97,99,101,115,46,10,32,32,32,32,42,32,85,115,105,110,103,32,97,32,100,101,99,101,110,116,32,97,110,103,108,
101,32,104,101,114,101,32,40,101,46,103,46,32,56,48,32,100,101,103,114,101,101,115,41,32,114,101,115,117,108,116,115,32,105,110,32,118,101,114,121,32,103,111,111,100,32,118,105,115,117,97,108,10,32,32,32,32,42,32,97,112,112,101,97,114,97,110,99,101,46,
10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,101,110,83,109,111,111,116,104,78,111,114,109,97,108,115,32,61,32,48,120,52,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,83,112,108,105,116,115,32,108,97,114,103,101,32,109,101,
115,104,101,115,32,105,110,116,111,32,115,109,97,108,108,101,114,32,115,117,98,45,109,101,115,104,101,115,46,10,32,32,32,32,42,10,32,32,32,32,42,32,84,104,105,115,32,105,115,32,113,117,105,116,101,32,117,115,101,102,117,108,32,102,111,114,32,114,101,
97,108,45,116,105,109,101,32,114,101,110,100,101,114,105,110,103,44,32,119,104,101,114,101,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,116,114,105,97,110,103,108,101,115,10,32,32,32,32,42,32,119,104,105,99,104,32,99,97,110,32,98,101,32,109,
97,120,105,109,97,108,108,121,32,112,114,111,99,101,115,115,101,100,32,105,110,32,97,32,115,105,110,103,108,101,32,100,114,97,119,45,99,97,108,108,32,105,115,32,108,105,109,105,116,101,100,10,32,32,32,32,42,32,98,121,32,116,104,101,32,118,105,100,101,
111,32,100,114,105,118,101,114,47,104,97,114,100,119,97,114,101,46,32,84,104,101,32,109,97,120,105,109,117,109,32,118,101,114,116,101,120,32,98,117,102,102,101,114,32,105,115,32,117,115,117,97,108,108,121,32,108,105,109,105,116,101,100,10,32,32,32,32,
42,32,116,111,111,46,32,66,111,116,104,32,114,101,113,117,105,114,101,109,101,110,116,115,32,99,97,110,32,98,101,32,109,101,116,32,119,105,116,104,32,116,104,105,115,32,115,116,101,112,58,32,121,111,117,32,109,97,121,32,115,112,101,99,105,102,121,32,
98,111,116,104,32,97,10,32,32,32,32,42,32,116,114,105,97,110,103,108,101,32,97,110,100,32,118,101,114,116,101,120,32,108,105,109,105,116,32,102,111,114,32,97,32,115,105,110,103,108,101,32,109,101,115,104,46,10,32,32,32,32,42,10,32,32,32,32,42,32,84,104,
101,32,115,112,108,105,116,32,108,105,109,105,116,115,32,99,97,110,32,40,97,110,100,32,115,104,111,117,108,100,33,41,32,98,101,32,115,101,116,32,116,104,114,111,117,103,104,32,116,104,101,10,32,32,32,32,42,32,60,116,116,62,35,65,73,95,67,79,78,70,73,
71,95,80,80,95,83,76,77,95,86,69,82,84,69,88,95,76,73,77,73,84,60,47,116,116,62,32,97,110,100,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,83,76,77,95,84,82,73,65,78,71,76,69,95,76,73,77,73,84,60,47,116,116,62,10,32,32,32,32,42,32,105,109,
112,111,114,116,101,114,32,112,114,111,112,101,114,116,105,101,115,46,32,84,104,101,32,100,101,102,97,117,108,116,32,118,97,108,117,101,115,32,97,114,101,32,60,116,116,62,35,65,73,95,83,76,77,95,68,69,70,65,85,76,84,95,77,65,88,95,86,69,82,84,73,67,69,
83,60,47,116,116,62,32,97,110,100,10,32,32,32,32,42,32,60,116,116,62,35,65,73,95,83,76,77,95,68,69,70,65,85,76,84,95,77,65,88,95,84,82,73,65,78,71,76,69,83,60,47,116,116,62,46,10,32,32,32,32,42,10,32,32,32,32,42,32,78,111,116,101,32,116,104,97,116,32,
115,112,108,105,116,116,105,110,103,32,105,115,32,103,101,110,101,114,97,108,108,121,32,97,32,116,105,109,101,45,99,111,110,115,117,109,105,110,103,32,116,97,115,107,44,32,98,117,116,32,111,110,108,121,32,105,102,32,116,104,101,114,101,39,115,10,32,32,
32,32,42,32,115,111,109,101,116,104,105,110,103,32,116,111,32,115,112,108,105,116,46,32,84,104,101,32,117,115,101,32,111,102,32,116,104,105,115,32,115,116,101,112,32,105,115,32,114,101,99,111,109,109,101,110,100,101,100,32,102,111,114,32,109,111,115,
116,32,117,115,101,114,115,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,83,112,108,105,116,76,97,114,103,101,77,101,115,104,101,115,32,61,32,48,120,56,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,82,101,109,111,118,101,115,
32,116,104,101,32,110,111,100,101,32,103,114,97,112,104,32,97,110,100,32,112,114,101,45,116,114,97,110,115,102,111,114,109,115,32,97,108,108,32,118,101,114,116,105,99,101,115,32,119,105,116,104,10,32,32,32,32,42,32,116,104,101,32,108,111,99,97,108,32,
116,114,97,110,115,102,111,114,109,97,116,105,111,110,32,109,97,116,114,105,99,101,115,32,111,102,32,116,104,101,105,114,32,110,111,100,101,115,46,10,32,32,32,32,42,10,32,32,32,32,42,32,73,102,32,116,104,101,32,114,101,115,117,108,116,105,110,103,32,
115,99,101,110,101,32,99,97,110,32,98,101,32,114,101,100,117,99,101,100,32,116,111,32,97,32,115,105,110,103,108,101,32,109,101,115,104,44,32,119,105,116,104,32,97,32,115,105,110,103,108,101,10,32,32,32,32,42,32,109,97,116,101,114,105,97,108,44,32,110,
111,32,108,105,103,104,116,115,44,32,97,110,100,32,110,111,32,99,97,109,101,114,97,115,44,32,116,104,101,110,32,116,104,101,32,111,117,116,112,117,116,32,115,99,101,110,101,32,119,105,108,108,32,99,111,110,116,97,105,110,10,32,32,32,32,42,32,111,110,
108,121,32,97,32,114,111,111,116,32,110,111,100,101,32,40,119,105,116,104,32,110,111,32,99,104,105,108,100,114,101,110,41,32,116,104,97,116,32,114,101,102,101,114,101,110,99,101,115,32,116,104,101,32,115,105,110,103,108,101,32,109,101,115,104,46,10,32,
32,32,32,42,32,79,116,104,101,114,119,105,115,101,44,32,116,104,101,32,111,117,116,112,117,116,32,115,99,101,110,101,32,119,105,108,108,32,98,101,32,114,101,100,117,99,101,100,32,116,111,32,97,32,114,111,111,116,32,110,111,100,101,32,119,105,116,104,
32,97,32,115,105,110,103,108,101,10,32,32,32,32,42,32,108,101,118,101,108,32,111,102,32,99,104,105,108,100,32,110,111,100,101,115,44,32,101,97,99,104,32,111,110,101,32,114,101,102,101,114,101,110,99,105,110,103,32,111,110,101,32,109,101,115,104,44,32,
97,110,100,32,101,97,99,104,32,109,101,115,104,10,32,32,32,32,42,32,114,101,102,101,114,101,110,99,105,110,103,32,111,110,101,32,109,97,116,101,114,105,97,108,46,10,32,32,32,32,42,10,32,32,32,32,42,32,73,110,32,101,105,116,104,101,114,32,99,97,115,101,
44,32,102,111,114,32,114,101,110,100,101,114,105,110,103,44,32,121,111,117,32,99,97,110,10,32,32,32,32,42,32,115,105,109,112,108,121,32,114,101,110,100,101,114,32,97,108,108,32,109,101,115,104,101,115,32,105,110,32,111,114,100,101,114,32,45,32,121,111,
117,32,100,111,110,39,116,32,110,101,101,100,32,116,111,32,112,97,121,10,32,32,32,32,42,32,97,116,116,101,110,116,105,111,110,32,116,111,32,108,111,99,97,108,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,115,32,97,110,100,32,116,104,101,32,
110,111,100,101,32,104,105,101,114,97,114,99,104,121,46,10,32,32,32,32,42,32,65,110,105,109,97,116,105,111,110,115,32,97,114,101,32,114,101,109,111,118,101,100,32,100,117,114,105,110,103,32,116,104,105,115,32,115,116,101,112,46,10,32,32,32,32,42,32,84,
104,105,115,32,115,116,101,112,32,105,115,32,105,110,116,101,110,100,101,100,32,102,111,114,32,97,112,112,108,105,99,97,116,105,111,110,115,32,119,105,116,104,111,117,116,32,97,32,115,99,101,110,101,103,114,97,112,104,46,10,32,32,32,32,42,32,84,104,101,
32,115,116,101,112,32,67,65,78,32,99,97,117,115,101,32,115,111,109,101,32,112,114,111,98,108,101,109,115,58,32,105,102,32,101,46,103,46,32,97,32,109,101,115,104,32,111,102,32,116,104,101,32,97,115,115,101,116,10,32,32,32,32,42,32,99,111,110,116,97,105,
110,115,32,110,111,114,109,97,108,115,32,97,110,100,32,97,110,111,116,104,101,114,44,32,117,115,105,110,103,32,116,104,101,32,115,97,109,101,32,109,97,116,101,114,105,97,108,32,105,110,100,101,120,44,32,100,111,101,115,32,110,111,116,44,10,32,32,32,32,
42,32,116,104,101,121,32,119,105,108,108,32,98,101,32,98,114,111,117,103,104,116,32,116,111,103,101,116,104,101,114,44,32,98,117,116,32,116,104,101,32,102,105,114,115,116,32,109,101,115,104,101,115,39,115,32,112,97,114,116,32,111,102,10,32,32,32,32,42,
32,116,104,101,32,110,111,114,109,97,108,32,108,105,115,116,32,105,115,32,122,101,114,111,101,100,46,32,72,111,119,101,118,101,114,44,32,116,104,101,115,101,32,97,114,116,105,102,97,99,116,115,32,97,114,101,32,114,97,114,101,46,10,32,32,32,32,42,32,64,
110,111,116,101,32,84,104,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,80,84,86,95,78,79,82,77,65,76,73,90,69,60,47,116,116,62,32,99,111,110,102,105,103,117,114,97,116,105,111,110,32,112,114,111,112,101,114,116,121,10,32,32,32,32,42,
32,99,97,110,32,98,101,32,115,101,116,32,116,111,32,110,111,114,109,97,108,105,122,101,32,116,104,101,32,115,99,101,110,101,39,115,32,115,112,97,116,105,97,108,32,100,105,109,101,110,115,105,111,110,32,116,111,32,116,104,101,32,45,49,46,46,46,49,10,32,
32,32,32,42,32,114,97,110,103,101,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,80,114,101,84,114,97,110,115,102,111,114,109,86,101,114,116,105,99,101,115,32,61,32,48,120,49,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,76,
105,109,105,116,115,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,98,111,110,101,115,32,115,105,109,117,108,116,97,110,101,111,117,115,108,121,32,97,102,102,101,99,116,105,110,103,32,97,32,115,105,110,103,108,101,32,118,101,114,116,101,120,10,
32,32,32,32,42,32,32,116,111,32,97,32,109,97,120,105,109,117,109,32,118,97,108,117,101,46,10,32,32,32,32,42,10,32,32,32,32,42,32,73,102,32,97,110,121,32,118,101,114,116,101,120,32,105,115,32,97,102,102,101,99,116,101,100,32,98,121,32,109,111,114,101,
32,116,104,97,110,32,116,104,101,32,109,97,120,105,109,117,109,32,110,117,109,98,101,114,32,111,102,32,98,111,110,101,115,44,32,116,104,101,32,108,101,97,115,116,10,32,32,32,32,42,32,105,109,112,111,114,116,97,110,116,32,118,101,114,116,101,120,32,119,
101,105,103,104,116,115,32,97,114,101,32,114,101,109,111,118,101,100,32,97,110,100,32,116,104,101,32,114,101,109,97,105,110,105,110,103,32,118,101,114,116,101,120,32,119,101,105,103,104,116,115,32,97,114,101,10,32,32,32,32,42,32,114,101,110,111,114,109,
97,108,105,122,101,100,32,115,111,32,116,104,97,116,32,116,104,101,32,119,101,105,103,104,116,115,32,115,116,105,108,108,32,115,117,109,32,117,112,32,116,111,32,49,46,10,32,32,32,32,42,32,84,104,101,32,100,101,102,97,117,108,116,32,98,111,110,101,32,
119,101,105,103,104,116,32,108,105,109,105,116,32,105,115,32,52,32,40,100,101,102,105,110,101,100,32,97,115,32,60,116,116,62,35,65,73,95,76,77,87,95,77,65,88,95,87,69,73,71,72,84,83,60,47,116,116,62,32,105,110,10,32,32,32,32,42,32,99,111,110,102,105,
103,46,104,41,44,32,98,117,116,32,121,111,117,32,99,97,110,32,117,115,101,32,116,104,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,76,66,87,95,77,65,88,95,87,69,73,71,72,84,83,60,47,116,116,62,32,105,109,112,111,114,116,101,114,10,32,
32,32,32,42,32,112,114,111,112,101,114,116,121,32,116,111,32,115,117,112,112,108,121,32,121,111,117,114,32,111,119,110,32,108,105,109,105,116,32,116,111,32,116,104,101,32,112,111,115,116,32,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,46,
10,32,32,32,32,42,10,32,32,32,32,42,32,73,102,32,121,111,117,32,105,110,116,101,110,100,32,116,111,32,112,101,114,102,111,114,109,32,116,104,101,32,115,107,105,110,110,105,110,103,32,105,110,32,104,97,114,100,119,97,114,101,44,32,116,104,105,115,32,112,
111,115,116,32,112,114,111,99,101,115,115,105,110,103,10,32,32,32,32,42,32,115,116,101,112,32,109,105,103,104,116,32,98,101,32,111,102,32,105,110,116,101,114,101,115,116,32,116,111,32,121,111,117,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,
99,101,115,115,95,76,105,109,105,116,66,111,110,101,87,101,105,103,104,116,115,32,61,32,48,120,50,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,86,97,108,105,100,97,116,101,115,32,116,104,101,32,105,109,112,111,114,116,101,100,32,115,99,101,110,101,32,
100,97,116,97,32,115,116,114,117,99,116,117,114,101,46,10,32,32,32,32,32,42,32,84,104,105,115,32,109,97,107,101,115,32,115,117,114,101,32,116,104,97,116,32,97,108,108,32,105,110,100,105,99,101,115,32,97,114,101,32,118,97,108,105,100,44,32,97,108,108,
32,97,110,105,109,97,116,105,111,110,115,32,97,110,100,10,32,32,32,32,32,42,32,98,111,110,101,115,32,97,114,101,32,108,105,110,107,101,100,32,99,111,114,114,101,99,116,108,121,44,32,97,108,108,32,109,97,116,101,114,105,97,108,32,114,101,102,101,114,101,
110,99,101,115,32,97,114,101,32,99,111,114,114,101,99,116,32,46,46,32,101,116,99,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,73,116,32,105,115,32,114,101,99,111,109,109,101,110,100,101,100,32,116,104,97,116,32,121,111,117,32,99,97,112,116,117,114,
101,32,65,115,115,105,109,112,39,115,32,108,111,103,32,111,117,116,112,117,116,32,105,102,32,121,111,117,32,117,115,101,32,116,104,105,115,32,102,108,97,103,44,10,32,32,32,32,32,42,32,115,111,32,121,111,117,32,99,97,110,32,101,97,115,105,108,121,32,102,
105,110,100,32,111,117,116,32,119,104,97,116,39,115,32,119,114,111,110,103,32,105,102,32,97,32,102,105,108,101,32,102,97,105,108,115,32,116,104,101,10,32,32,32,32,32,42,32,118,97,108,105,100,97,116,105,111,110,46,32,84,104,101,32,118,97,108,105,100,97,
116,111,114,32,105,115,32,113,117,105,116,101,32,115,116,114,105,99,116,32,97,110,100,32,119,105,108,108,32,102,105,110,100,32,42,97,108,108,42,10,32,32,32,32,32,42,32,105,110,99,111,110,115,105,115,116,101,110,99,105,101,115,32,105,110,32,116,104,101,
32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,46,46,46,32,73,116,32,105,115,32,114,101,99,111,109,109,101,110,100,101,100,32,116,104,97,116,32,112,108,117,103,105,110,10,32,32,32,32,32,42,32,100,101,118,101,108,111,112,101,114,115,32,117,115,
101,32,105,116,32,116,111,32,100,101,98,117,103,32,116,104,101,105,114,32,108,111,97,100,101,114,115,46,32,84,104,101,114,101,32,97,114,101,32,116,119,111,32,116,121,112,101,115,32,111,102,10,32,32,32,32,32,42,32,118,97,108,105,100,97,116,105,111,110,
32,102,97,105,108,117,114,101,115,58,10,32,32,32,32,32,42,32,60,117,108,62,10,32,32,32,32,32,42,32,60,108,105,62,69,114,114,111,114,58,32,84,104,101,114,101,39,115,32,115,111,109,101,116,104,105,110,103,32,119,114,111,110,103,32,119,105,116,104,32,116,
104,101,32,105,109,112,111,114,116,101,100,32,100,97,116,97,46,32,70,117,114,116,104,101,114,10,32,32,32,32,32,42,32,32,32,112,111,115,116,112,114,111,99,101,115,115,105,110,103,32,105,115,32,110,111,116,32,112,111,115,115,105,98,108,101,32,97,110,100,
32,116,104,101,32,100,97,116,97,32,105,115,32,110,111,116,32,117,115,97,98,108,101,32,97,116,32,97,108,108,46,10,32,32,32,32,32,42,32,32,32,84,104,101,32,105,109,112,111,114,116,32,102,97,105,108,115,46,32,35,73,109,112,111,114,116,101,114,58,58,71,101,
116,69,114,114,111,114,83,116,114,105,110,103,40,41,32,111,114,32,35,97,105,71,101,116,69,114,114,111,114,83,116,114,105,110,103,40,41,10,32,32,32,32,32,42,32,32,32,99,97,114,114,121,32,116,104,101,32,101,114,114,111,114,32,109,101,115,115,97,103,101,
32,97,114,111,117,110,100,46,60,47,108,105,62,10,32,32,32,32,32,42,32,60,108,105,62,87,97,114,110,105,110,103,58,32,84,104,101,114,101,32,97,114,101,32,115,111,109,101,32,109,105,110,111,114,32,105,115,115,117,101,115,32,40,101,46,103,46,32,49,48,48,
48,48,48,48,32,97,110,105,109,97,116,105,111,110,10,32,32,32,32,32,42,32,32,32,107,101,121,102,114,97,109,101,115,32,119,105,116,104,32,116,104,101,32,115,97,109,101,32,116,105,109,101,41,44,32,98,117,116,32,102,117,114,116,104,101,114,32,112,111,115,
116,112,114,111,99,101,115,115,105,110,103,32,97,110,100,32,117,115,101,10,32,32,32,32,32,42,32,32,32,111,102,32,116,104,101,32,100,97,116,97,32,115,116,114,117,99,116,117,114,101,32,105,115,32,115,116,105,108,108,32,115,97,102,101,46,32,87,97,114,110,
105,110,103,32,100,101,116,97,105,108,115,32,97,114,101,32,119,114,105,116,116,101,110,10,32,32,32,32,32,42,32,32,32,116,111,32,116,104,101,32,108,111,103,32,102,105,108,101,44,32,60,116,116,62,35,65,73,95,83,67,69,78,69,95,70,76,65,71,83,95,86,65,76,
73,68,65,84,73,79,78,95,87,65,82,78,73,78,71,60,47,116,116,62,32,105,115,32,115,101,116,10,32,32,32,32,32,42,32,32,32,105,110,32,35,97,105,83,99,101,110,101,58,58,109,70,108,97,103,115,60,47,108,105,62,10,32,32,32,32,32,42,32,60,47,117,108,62,10,32,32,
32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,112,111,115,116,45,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,105,115,32,110,111,116,32,116,105,109,101,45,99,111,110,115,117,109,105,110,103,46,32,73,116,115,32,117,115,101,32,105,
115,32,110,111,116,10,32,32,32,32,32,42,32,99,111,109,112,117,108,115,111,114,121,44,32,98,117,116,32,114,101,99,111,109,109,101,110,100,101,100,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,86,97,108,105,100,97,116,101,68,
97,116,97,83,116,114,117,99,116,117,114,101,32,61,32,48,120,52,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,82,101,111,114,100,101,114,115,32,116,114,105,97,110,103,108,101,115,32,102,111,114,32,98,101,116,116,101,114,32,118,101,114,116,101,120,32,99,
97,99,104,101,32,108,111,99,97,108,105,116,121,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,101,32,115,116,101,112,32,116,114,105,101,115,32,116,111,32,105,109,112,114,111,118,101,32,116,104,101,32,65,67,77,82,32,40,97,118,101,114,97,103,101,
32,112,111,115,116,45,116,114,97,110,115,102,111,114,109,32,118,101,114,116,101,120,32,99,97,99,104,101,10,32,32,32,32,32,42,32,109,105,115,115,32,114,97,116,105,111,41,32,102,111,114,32,97,108,108,32,109,101,115,104,101,115,46,32,84,104,101,32,105,109,
112,108,101,109,101,110,116,97,116,105,111,110,32,114,117,110,115,32,105,110,32,79,40,110,41,32,97,110,100,32,105,115,10,32,32,32,32,32,42,32,114,111,117,103,104,108,121,32,98,97,115,101,100,32,111,110,32,116,104,101,32,39,116,105,112,115,105,102,121,
39,32,97,108,103,111,114,105,116,104,109,32,40,115,101,101,32,60,97,32,104,114,101,102,61,34,10,32,32,32,32,32,42,32,104,116,116,112,58,47,47,119,119,119,46,99,115,46,112,114,105,110,99,101,116,111,110,46,101,100,117,47,103,102,120,47,112,117,98,115,
47,83,97,110,100,101,114,95,50,48,48,55,95,37,51,69,84,82,47,116,105,112,115,121,46,112,100,102,34,62,116,104,105,115,10,32,32,32,32,32,42,32,112,97,112,101,114,60,47,97,62,41,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,73,102,32,121,111,117,32,105,
110,116,101,110,100,32,116,111,32,114,101,110,100,101,114,32,104,117,103,101,32,109,111,100,101,108,115,32,105,110,32,104,97,114,100,119,97,114,101,44,32,116,104,105,115,32,115,116,101,112,32,109,105,103,104,116,10,32,32,32,32,32,42,32,98,101,32,111,
102,32,105,110,116,101,114,101,115,116,32,116,111,32,121,111,117,46,32,84,104,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,73,67,76,95,80,84,67,65,67,72,69,95,83,73,90,69,60,47,116,116,62,10,32,32,32,32,32,42,32,105,109,112,111,114,
116,101,114,32,112,114,111,112,101,114,116,121,32,99,97,110,32,98,101,32,117,115,101,100,32,116,111,32,102,105,110,101,45,116,117,110,101,32,116,104,101,32,99,97,99,104,101,32,111,112,116,105,109,105,122,97,116,105,111,110,46,10,32,32,32,32,32,42,47,
10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,73,109,112,114,111,118,101,67,97,99,104,101,76,111,99,97,108,105,116,121,32,61,32,48,120,56,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,83,101,97,114,99,104,101,115,32,102,111,114,32,114,101,100,117,
110,100,97,110,116,47,117,110,114,101,102,101,114,101,110,99,101,100,32,109,97,116,101,114,105,97,108,115,32,97,110,100,32,114,101,109,111,118,101,115,32,116,104,101,109,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,101,
115,112,101,99,105,97,108,108,121,32,117,115,101,102,117,108,32,105,110,32,99,111,109,98,105,110,97,116,105,111,110,32,119,105,116,104,32,116,104,101,10,32,32,32,32,32,42,32,35,97,105,80,114,111,99,101,115,115,95,80,114,101,84,114,97,110,115,102,111,
114,109,86,101,114,116,105,99,101,115,32,97,110,100,32,35,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,122,101,77,101,115,104,101,115,32,102,108,97,103,115,46,10,32,32,32,32,32,42,32,66,111,116,104,32,106,111,105,110,32,115,109,97,108,108,
32,109,101,115,104,101,115,32,119,105,116,104,32,101,113,117,97,108,32,99,104,97,114,97,99,116,101,114,105,115,116,105,99,115,44,32,98,117,116,32,116,104,101,121,32,99,97,110,39,116,32,100,111,10,32,32,32,32,32,42,32,116,104,101,105,114,32,119,111,114,
107,32,105,102,32,116,119,111,32,109,101,115,104,101,115,32,104,97,118,101,32,100,105,102,102,101,114,101,110,116,32,109,97,116,101,114,105,97,108,115,46,32,66,101,99,97,117,115,101,32,115,101,118,101,114,97,108,10,32,32,32,32,32,42,32,109,97,116,101,
114,105,97,108,32,115,101,116,116,105,110,103,115,32,97,114,101,32,108,111,115,116,32,100,117,114,105,110,103,32,65,115,115,105,109,112,39,115,32,105,109,112,111,114,116,32,102,105,108,116,101,114,115,44,10,32,32,32,32,32,42,32,40,97,110,100,32,98,101,
99,97,117,115,101,32,109,97,110,121,32,101,120,112,111,114,116,101,114,115,32,100,111,110,39,116,32,99,104,101,99,107,32,102,111,114,32,114,101,100,117,110,100,97,110,116,32,109,97,116,101,114,105,97,108,115,41,44,32,104,117,103,101,10,32,32,32,32,32,
42,32,109,111,100,101,108,115,32,111,102,116,101,110,32,104,97,118,101,32,109,97,116,101,114,105,97,108,115,32,119,104,105,99,104,32,97,114,101,32,97,114,101,32,100,101,102,105,110,101,100,32,115,101,118,101,114,97,108,32,116,105,109,101,115,32,119,105,
116,104,10,32,32,32,32,32,42,32,101,120,97,99,116,108,121,32,116,104,101,32,115,97,109,101,32,115,101,116,116,105,110,103,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,83,101,118,101,114,97,108,32,109,97,116,101,114,105,97,108,32,115,101,116,116,
105,110,103,115,32,110,111,116,32,99,111,110,116,114,105,98,117,116,105,110,103,32,116,111,32,116,104,101,32,102,105,110,97,108,32,97,112,112,101,97,114,97,110,99,101,32,111,102,10,32,32,32,32,32,42,32,97,32,115,117,114,102,97,99,101,32,97,114,101,32,
105,103,110,111,114,101,100,32,105,110,32,97,108,108,32,99,111,109,112,97,114,105,115,111,110,115,32,40,101,46,103,46,32,116,104,101,32,109,97,116,101,114,105,97,108,32,110,97,109,101,41,46,10,32,32,32,32,32,42,32,83,111,44,32,105,102,32,121,111,117,
39,114,101,32,112,97,115,115,105,110,103,32,97,100,100,105,116,105,111,110,97,108,32,105,110,102,111,114,109,97,116,105,111,110,32,116,104,114,111,117,103,104,32,116,104,101,10,32,32,32,32,32,42,32,99,111,110,116,101,110,116,32,112,105,112,101,108,105,
110,101,32,40,112,114,111,98,97,98,108,121,32,117,115,105,110,103,32,42,109,97,103,105,99,42,32,109,97,116,101,114,105,97,108,32,110,97,109,101,115,41,44,32,100,111,110,39,116,10,32,32,32,32,32,42,32,115,112,101,99,105,102,121,32,116,104,105,115,32,102,
108,97,103,46,32,65,108,116,101,114,110,97,116,105,118,101,108,121,32,116,97,107,101,32,97,32,108,111,111,107,32,97,116,32,116,104,101,10,32,32,32,32,32,42,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,82,82,77,95,69,88,67,76,85,68,69,95,
76,73,83,84,60,47,116,116,62,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,82,101,109,111,118,101,82,101,100,117,110,100,97,110,116,77,97,116,101,114,
105,97,108,115,32,61,32,48,120,49,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,116,114,105,101,115,32,116,111,32,100,101,116,101,114,109,105,110,101,32,119,104,105,99,104,32,109,101,115,104,101,115,32,104,97,118,
101,32,110,111,114,109,97,108,32,118,101,99,116,111,114,115,10,32,32,32,32,32,42,32,116,104,97,116,32,97,114,101,32,102,97,99,105,110,103,32,105,110,119,97,114,100,115,32,97,110,100,32,105,110,118,101,114,116,115,32,116,104,101,109,46,10,32,32,32,32,
32,42,10,32,32,32,32,32,42,32,84,104,101,32,97,108,103,111,114,105,116,104,109,32,105,115,32,115,105,109,112,108,101,32,98,117,116,32,101,102,102,101,99,116,105,118,101,58,10,32,32,32,32,32,42,32,116,104,101,32,98,111,117,110,100,105,110,103,32,98,111,
120,32,111,102,32,97,108,108,32,118,101,114,116,105,99,101,115,32,43,32,116,104,101,105,114,32,110,111,114,109,97,108,115,32,105,115,32,99,111,109,112,97,114,101,100,32,97,103,97,105,110,115,116,10,32,32,32,32,32,42,32,116,104,101,32,118,111,108,117,
109,101,32,111,102,32,116,104,101,32,98,111,117,110,100,105,110,103,32,98,111,120,32,111,102,32,97,108,108,32,118,101,114,116,105,99,101,115,32,119,105,116,104,111,117,116,32,116,104,101,105,114,32,110,111,114,109,97,108,115,46,10,32,32,32,32,32,42,32,
84,104,105,115,32,119,111,114,107,115,32,119,101,108,108,32,102,111,114,32,109,111,115,116,32,111,98,106,101,99,116,115,44,32,112,114,111,98,108,101,109,115,32,109,105,103,104,116,32,111,99,99,117,114,32,119,105,116,104,32,112,108,97,110,97,114,10,32,
32,32,32,32,42,32,115,117,114,102,97,99,101,115,46,32,72,111,119,101,118,101,114,44,32,116,104,101,32,115,116,101,112,32,116,114,105,101,115,32,116,111,32,102,105,108,116,101,114,32,115,117,99,104,32,99,97,115,101,115,46,10,32,32,32,32,32,42,32,84,104,
101,32,115,116,101,112,32,105,110,118,101,114,116,115,32,97,108,108,32,105,110,45,102,97,99,105,110,103,32,110,111,114,109,97,108,115,46,32,71,101,110,101,114,97,108,108,121,32,105,116,32,105,115,32,114,101,99,111,109,109,101,110,100,101,100,10,32,32,
32,32,32,42,32,116,111,32,101,110,97,98,108,101,32,116,104,105,115,32,115,116,101,112,44,32,97,108,116,104,111,117,103,104,32,116,104,101,32,114,101,115,117,108,116,32,105,115,32,110,111,116,32,97,108,119,97,121,115,32,99,111,114,114,101,99,116,46,10,
32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,105,120,73,110,102,97,99,105,110,103,78,111,114,109,97,108,115,32,61,32,48,120,50,48,48,48,44,10,10,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,32,84,104,105,115,32,115,116,101,112,
32,103,101,110,101,114,105,99,97,108,108,121,32,112,111,112,117,108,97,116,101,115,32,97,105,66,111,110,101,45,62,109,65,114,109,97,116,117,114,101,32,97,110,100,32,97,105,66,111,110,101,45,62,109,78,111,100,101,32,103,101,110,101,114,105,99,97,108,108,
121,10,32,32,32,32,32,42,32,84,104,101,32,112,111,105,110,116,32,111,102,32,116,104,101,115,101,32,105,115,32,105,116,32,115,97,118,101,115,32,121,111,117,32,108,97,116,101,114,32,104,97,118,105,110,103,32,116,111,32,99,97,108,99,117,108,97,116,101,32,
116,104,101,115,101,32,101,108,101,109,101,110,116,115,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,117,115,101,102,117,108,32,119,104,101,110,32,104,97,110,100,108,105,110,103,32,114,101,115,116,32,105,110,102,111,114,109,97,116,105,111,110,
32,111,114,32,115,107,105,110,32,105,110,102,111,114,109,97,116,105,111,110,10,32,32,32,32,32,42,32,73,102,32,121,111,117,32,104,97,118,101,32,109,117,108,116,105,112,108,101,32,97,114,109,97,116,117,114,101,115,32,111,110,32,121,111,117,114,32,109,111,
100,101,108,115,32,119,101,32,115,116,114,111,110,103,108,121,32,114,101,99,111,109,109,101,110,100,32,101,110,97,98,108,105,110,103,32,116,104,105,115,10,32,32,32,32,32,42,32,73,110,115,116,101,97,100,32,111,102,32,119,114,105,116,105,110,103,32,121,
111,117,114,32,111,119,110,32,109,117,108,116,105,45,114,111,111,116,44,32,109,117,108,116,105,45,97,114,109,97,116,117,114,101,32,108,111,111,107,117,112,115,32,119,101,32,104,97,118,101,32,100,111,110,101,32,116,104,101,10,32,32,32,32,32,42,32,104,
97,114,100,32,119,111,114,107,32,102,111,114,32,121,111,117,32,58,41,10,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,80,111,112,117,108,97,116,101,65,114,109,97,116,117,114,101,68,97,116,97,32,61,32,48,120,52,48,48,48,44,10,10,32,
32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,
47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,115,112,108,105,116,115,32,109,101,115,104,101,115,32,119,105,116,104,32,109,111,114,101,32,116,104,97,110,32,111,110,101,32,112,114,105,109,105,116,105,118,101,32,116,121,112,101,32,105,
110,10,32,32,32,32,32,42,32,32,104,111,109,111,103,101,110,101,111,117,115,32,115,117,98,45,109,101,115,104,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,84,104,101,32,115,116,101,112,32,105,115,32,101,120,101,99,117,116,101,100,32,97,102,
116,101,114,32,116,104,101,32,116,114,105,97,110,103,117,108,97,116,105,111,110,32,115,116,101,112,46,32,65,102,116,101,114,32,116,104,101,32,115,116,101,112,10,32,32,32,32,32,42,32,32,114,101,116,117,114,110,115,44,32,106,117,115,116,32,111,110,101,
32,98,105,116,32,105,115,32,115,101,116,32,105,110,32,97,105,77,101,115,104,58,58,109,80,114,105,109,105,116,105,118,101,84,121,112,101,115,46,32,84,104,105,115,32,105,115,10,32,32,32,32,32,42,32,32,101,115,112,101,99,105,97,108,108,121,32,117,115,101,
102,117,108,32,102,111,114,32,114,101,97,108,45,116,105,109,101,32,114,101,110,100,101,114,105,110,103,32,119,104,101,114,101,32,112,111,105,110,116,32,97,110,100,32,108,105,110,101,10,32,32,32,32,32,42,32,32,112,114,105,109,105,116,105,118,101,115,32,
97,114,101,32,111,102,116,101,110,32,105,103,110,111,114,101,100,32,111,114,32,114,101,110,100,101,114,101,100,32,115,101,112,97,114,97,116,101,108,121,46,10,32,32,32,32,32,42,32,32,89,111,117,32,99,97,110,32,117,115,101,32,116,104,101,32,60,116,116,
62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,83,66,80,95,82,69,77,79,86,69,60,47,116,116,62,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,32,116,111,10,32,32,32,32,32,42,32,32,115,112,101,99,105,102,121,32,119,104,105,99,104,32,
112,114,105,109,105,116,105,118,101,32,116,121,112,101,115,32,121,111,117,32,110,101,101,100,46,32,84,104,105,115,32,99,97,110,32,98,101,32,117,115,101,100,32,116,111,32,101,97,115,105,108,121,10,32,32,32,32,32,42,32,32,101,120,99,108,117,100,101,32,
108,105,110,101,115,32,97,110,100,32,112,111,105,110,116,115,44,32,119,104,105,99,104,32,97,114,101,32,114,97,114,101,108,121,32,117,115,101,100,44,32,102,114,111,109,32,116,104,101,32,105,109,112,111,114,116,46,10,32,32,32,32,42,47,10,32,32,32,32,97,
105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,101,32,61,32,48,120,56,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,115,101,97,114,99,104,101,115,32,97,108,108,32,109,101,115,104,101,115,32,
102,111,114,32,100,101,103,101,110,101,114,97,116,101,32,112,114,105,109,105,116,105,118,101,115,32,97,110,100,10,32,32,32,32,32,42,32,32,99,111,110,118,101,114,116,115,32,116,104,101,109,32,116,111,32,112,114,111,112,101,114,32,108,105,110,101,115,32,
111,114,32,112,111,105,110,116,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,65,32,102,97,99,101,32,105,115,32,39,100,101,103,101,110,101,114,97,116,101,39,32,105,102,32,111,110,101,32,111,114,32,109,111,114,101,32,111,102,32,105,116,115,32,112,
111,105,110,116,115,32,97,114,101,32,105,100,101,110,116,105,99,97,108,46,10,32,32,32,32,32,42,32,84,111,32,104,97,118,101,32,116,104,101,32,100,101,103,101,110,101,114,97,116,101,32,115,116,117,102,102,32,110,111,116,32,111,110,108,121,32,100,101,116,
101,99,116,101,100,32,97,110,100,32,99,111,108,108,97,112,115,101,100,32,98,117,116,10,32,32,32,32,32,42,32,114,101,109,111,118,101,100,44,32,116,114,121,32,111,110,101,32,111,102,32,116,104,101,32,102,111,108,108,111,119,105,110,103,32,112,114,111,99,
101,100,117,114,101,115,58,10,32,32,32,32,32,42,32,60,98,114,62,60,98,62,49,46,60,47,98,62,32,40,105,102,32,121,111,117,32,115,117,112,112,111,114,116,32,108,105,110,101,115,32,97,110,100,32,112,111,105,110,116,115,32,102,111,114,32,114,101,110,100,101,
114,105,110,103,32,98,117,116,32,100,111,110,39,116,10,32,32,32,32,32,42,32,32,32,32,119,97,110,116,32,116,104,101,32,100,101,103,101,110,101,114,97,116,101,115,41,60,98,114,62,10,32,32,32,32,32,42,32,60,117,108,62,10,32,32,32,32,32,42,32,32,32,60,108,
105,62,83,112,101,99,105,102,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,70,105,110,100,68,101,103,101,110,101,114,97,116,101,115,32,102,108,97,103,46,10,32,32,32,32,32,42,32,32,32,60,47,108,105,62,10,32,32,32,32,32,42,32,32,32,60,108,
105,62,83,101,116,32,116,104,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,70,68,95,82,69,77,79,86,69,60,47,116,116,62,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,32,116,111,10,32,32,32,32,32,42,32,32,32,32,
32,32,32,49,46,32,84,104,105,115,32,119,105,108,108,32,99,97,117,115,101,32,116,104,101,32,115,116,101,112,32,116,111,32,114,101,109,111,118,101,32,100,101,103,101,110,101,114,97,116,101,32,116,114,105,97,110,103,108,101,115,32,102,114,111,109,32,116,
104,101,10,32,32,32,32,32,42,32,32,32,32,32,32,32,105,109,112,111,114,116,32,97,115,32,115,111,111,110,32,97,115,32,116,104,101,121,39,114,101,32,100,101,116,101,99,116,101,100,46,32,84,104,101,121,32,119,111,110,39,116,32,112,97,115,115,32,97,110,121,
32,102,117,114,116,104,101,114,10,32,32,32,32,32,42,32,32,32,32,32,32,32,112,105,112,101,108,105,110,101,32,115,116,101,112,115,46,10,32,32,32,32,32,42,32,32,32,60,47,108,105,62,10,32,32,32,32,32,42,32,60,47,117,108,62,10,32,32,32,32,32,42,32,60,98,114,
62,60,98,62,50,46,60,47,98,62,40,105,102,32,121,111,117,32,100,111,110,39,116,32,115,117,112,112,111,114,116,32,108,105,110,101,115,32,97,110,100,32,112,111,105,110,116,115,32,97,116,32,97,108,108,41,60,98,114,62,10,32,32,32,32,32,42,32,60,117,108,62,
10,32,32,32,32,32,42,32,32,32,60,108,105,62,83,112,101,99,105,102,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,70,105,110,100,68,101,103,101,110,101,114,97,116,101,115,32,102,108,97,103,46,10,32,32,32,32,32,42,32,32,32,60,47,108,105,62,
10,32,32,32,32,32,42,32,32,32,60,108,105,62,83,112,101,99,105,102,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,101,32,102,108,97,103,46,32,84,104,105,115,32,109,111,118,101,115,32,108,105,110,101,32,
97,110,100,10,32,32,32,32,32,42,32,32,32,32,32,112,111,105,110,116,32,112,114,105,109,105,116,105,118,101,115,32,116,111,32,115,101,112,97,114,97,116,101,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,32,32,32,60,47,108,105,62,10,32,32,32,32,32,42,
32,32,32,60,108,105,62,83,101,116,32,116,104,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,83,66,80,95,82,69,77,79,86,69,60,47,116,116,62,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,32,116,111,10,32,32,32,32,
32,42,32,32,32,32,32,32,32,64,99,111,100,101,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,80,79,73,78,84,32,124,32,97,105,80,114,105,109,105,116,105,118,101,84,121,112,101,95,76,73,78,69,10,32,32,32,32,32,42,32,32,32,32,32,32,32,64,
101,110,100,99,111,100,101,32,116,111,32,99,97,117,115,101,32,83,111,114,116,66,121,80,84,121,112,101,32,116,111,32,114,101,106,101,99,116,32,112,111,105,110,116,10,32,32,32,32,32,42,32,32,32,32,32,32,32,97,110,100,32,108,105,110,101,32,109,101,115,104,
101,115,32,102,114,111,109,32,116,104,101,32,115,99,101,110,101,46,10,32,32,32,32,32,42,32,32,32,60,47,108,105,62,10,32,32,32,32,32,42,32,60,47,117,108,62,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,115,116,101,112,32,97,108,115,111,
32,114,101,109,111,118,101,115,32,118,101,114,121,32,115,109,97,108,108,32,116,114,105,97,110,103,108,101,115,32,119,105,116,104,32,97,32,115,117,114,102,97,99,101,32,97,114,101,97,32,115,109,97,108,108,101,114,10,32,32,32,32,32,42,32,116,104,97,110,
32,49,48,94,45,54,46,32,73,102,32,121,111,117,32,114,101,108,121,32,111,110,32,104,97,118,105,110,103,32,116,104,101,115,101,32,115,109,97,108,108,32,116,114,105,97,110,103,108,101,115,44,32,111,114,32,110,111,116,105,99,101,32,104,111,108,101,115,10,
32,32,32,32,32,42,32,105,110,32,121,111,117,114,32,109,111,100,101,108,44,32,115,101,116,32,116,104,101,32,112,114,111,112,101,114,116,121,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,70,68,95,67,72,69,67,75,65,82,69,65,60,47,116,116,62,
32,116,111,10,32,32,32,32,32,42,32,102,97,108,115,101,46,10,32,32,32,32,32,42,32,64,110,111,116,101,32,68,101,103,101,110,101,114,97,116,101,32,112,111,108,121,103,111,110,115,32,97,114,101,32,110,111,116,32,110,101,99,101,115,115,97,114,105,108,121,
32,101,118,105,108,32,97,110,100,32,116,104,97,116,39,115,32,119,104,121,10,32,32,32,32,32,42,32,116,104,101,121,39,114,101,32,110,111,116,32,114,101,109,111,118,101,100,32,98,121,32,100,101,102,97,117,108,116,46,32,84,104,101,114,101,32,97,114,101,32,
115,101,118,101,114,97,108,32,102,105,108,101,32,102,111,114,109,97,116,115,32,119,104,105,99,104,10,32,32,32,32,32,42,32,100,111,110,39,116,32,115,117,112,112,111,114,116,32,108,105,110,101,115,32,111,114,32,112,111,105,110,116,115,44,32,97,110,100,
32,115,111,109,101,32,101,120,112,111,114,116,101,114,115,32,98,121,112,97,115,115,32,116,104,101,10,32,32,32,32,32,42,32,102,111,114,109,97,116,32,115,112,101,99,105,102,105,99,97,116,105,111,110,32,97,110,100,32,119,114,105,116,101,32,116,104,101,109,
32,97,115,32,100,101,103,101,110,101,114,97,116,101,32,116,114,105,97,110,103,108,101,115,32,105,110,115,116,101,97,100,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,105,110,100,68,101,103,101,110,101,114,97,116,101,115,
32,61,32,48,120,49,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,115,101,97,114,99,104,101,115,32,97,108,108,32,109,101,115,104,101,115,32,102,111,114,32,105,110,118,97,108,105,100,32,100,97,116,97,44,32,115,
117,99,104,32,97,115,32,122,101,114,111,101,100,10,32,32,32,32,32,42,32,32,110,111,114,109,97,108,32,118,101,99,116,111,114,115,32,111,114,32,105,110,118,97,108,105,100,32,85,86,32,99,111,111,114,100,115,32,97,110,100,32,114,101,109,111,118,101,115,47,
102,105,120,101,115,32,116,104,101,109,46,32,84,104,105,115,32,105,115,10,32,32,32,32,32,42,32,32,105,110,116,101,110,100,101,100,32,116,111,32,103,101,116,32,114,105,100,32,111,102,32,115,111,109,101,32,99,111,109,109,111,110,32,101,120,112,111,114,
116,101,114,32,101,114,114,111,114,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,101,115,112,101,99,105,97,108,108,121,32,117,115,101,102,117,108,32,102,111,114,32,110,111,114,109,97,108,115,46,32,73,102,32,116,104,
101,121,32,97,114,101,32,105,110,118,97,108,105,100,44,32,97,110,100,10,32,32,32,32,32,42,32,116,104,101,32,115,116,101,112,32,114,101,99,111,103,110,105,122,101,115,32,116,104,105,115,44,32,116,104,101,121,32,119,105,108,108,32,98,101,32,114,101,109,
111,118,101,100,32,97,110,100,32,99,97,110,32,108,97,116,101,114,10,32,32,32,32,32,42,32,98,101,32,114,101,99,111,109,112,117,116,101,100,44,32,105,46,101,46,32,98,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,71,101,110,83,109,111,111,
116,104,78,111,114,109,97,108,115,32,102,108,97,103,46,60,98,114,62,10,32,32,32,32,32,42,32,84,104,101,32,115,116,101,112,32,119,105,108,108,32,97,108,115,111,32,114,101,109,111,118,101,32,109,101,115,104,101,115,32,116,104,97,116,32,97,114,101,32,105,
110,102,105,110,105,116,101,108,121,32,115,109,97,108,108,32,97,110,100,32,114,101,100,117,99,101,10,32,32,32,32,32,42,32,97,110,105,109,97,116,105,111,110,32,116,114,97,99,107,115,32,99,111,110,115,105,115,116,105,110,103,32,111,102,32,104,117,110,100,
114,101,100,115,32,105,102,32,114,101,100,117,110,100,97,110,116,32,107,101,121,115,32,116,111,32,97,32,115,105,110,103,108,101,10,32,32,32,32,32,42,32,107,101,121,46,32,84,104,101,32,60,116,116,62,65,73,95,67,79,78,70,73,71,95,80,80,95,70,73,68,95,65,
78,73,77,95,65,67,67,85,82,65,67,89,60,47,116,116,62,32,99,111,110,102,105,103,32,112,114,111,112,101,114,116,121,32,100,101,99,105,100,101,115,10,32,32,32,32,32,42,32,116,104,101,32,97,99,99,117,114,97,99,121,32,111,102,32,116,104,101,32,99,104,101,
99,107,32,102,111,114,32,100,117,112,108,105,99,97,116,101,32,97,110,105,109,97,116,105,111,110,32,116,114,97,99,107,115,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,105,110,100,73,110,118,97,108,105,100,68,97,116,97,
32,61,32,48,120,50,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,99,111,110,118,101,114,116,115,32,110,111,110,45,85,86,32,109,97,112,112,105,110,103,115,32,40,115,117,99,104,32,97,115,32,115,112,104,101,114,
105,99,97,108,32,111,114,10,32,32,32,32,32,42,32,32,99,121,108,105,110,100,114,105,99,97,108,32,109,97,112,112,105,110,103,41,32,116,111,32,112,114,111,112,101,114,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,99,104,97,110,
110,101,108,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,77,111,115,116,32,97,112,112,108,105,99,97,116,105,111,110,115,32,119,105,108,108,32,115,117,112,112,111,114,116,32,85,86,32,109,97,112,112,105,110,103,32,111,110,108,121,44,32,115,111,32,
121,111,117,32,119,105,108,108,10,32,32,32,32,32,42,32,112,114,111,98,97,98,108,121,32,119,97,110,116,32,116,111,32,115,112,101,99,105,102,121,32,116,104,105,115,32,115,116,101,112,32,105,110,32,101,118,101,114,121,32,99,97,115,101,46,32,78,111,116,101,
32,116,104,97,116,32,65,115,115,105,109,112,32,105,115,32,110,111,116,10,32,32,32,32,32,42,32,97,108,119,97,121,115,32,97,98,108,101,32,116,111,32,109,97,116,99,104,32,116,104,101,32,111,114,105,103,105,110,97,108,32,109,97,112,112,105,110,103,32,105,
109,112,108,101,109,101,110,116,97,116,105,111,110,32,111,102,32,116,104,101,10,32,32,32,32,32,42,32,51,68,32,97,112,112,32,119,104,105,99,104,32,112,114,111,100,117,99,101,100,32,97,32,109,111,100,101,108,32,112,101,114,102,101,99,116,108,121,46,32,
73,116,39,115,32,97,108,119,97,121,115,32,98,101,116,116,101,114,32,116,111,32,108,101,116,32,116,104,101,10,32,32,32,32,32,42,32,109,111,100,101,108,108,105,110,103,32,97,112,112,32,99,111,109,112,117,116,101,32,116,104,101,32,85,86,32,99,104,97,110,
110,101,108,115,32,45,32,51,100,115,32,109,97,120,44,32,77,97,121,97,44,32,66,108,101,110,100,101,114,44,10,32,32,32,32,32,42,32,76,105,103,104,116,87,97,118,101,44,32,97,110,100,32,77,111,100,111,32,100,111,32,116,104,105,115,32,102,111,114,32,101,120,
97,109,112,108,101,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,64,110,111,116,101,32,73,102,32,116,104,105,115,32,115,116,101,112,32,105,115,32,110,111,116,32,114,101,113,117,101,115,116,101,100,44,32,121,111,117,39,108,108,32,110,101,101,100,32,
116,111,32,112,114,111,99,101,115,115,32,116,104,101,10,32,32,32,32,32,42,32,60,116,116,62,35,65,73,95,77,65,84,75,69,89,95,77,65,80,80,73,78,71,60,47,116,116,62,32,109,97,116,101,114,105,97,108,32,112,114,111,112,101,114,116,121,32,105,110,32,111,114,
100,101,114,32,116,111,32,100,105,115,112,108,97,121,32,97,108,108,32,97,115,115,101,116,115,10,32,32,32,32,32,42,32,112,114,111,112,101,114,108,121,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,101,110,85,86,67,111,
111,114,100,115,32,61,32,48,120,52,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,97,112,112,108,105,101,115,32,112,101,114,45,116,101,120,116,117,114,101,32,85,86,32,116,114,97,110,115,102,111,114,109,97,116,
105,111,110,115,32,97,110,100,32,98,97,107,101,115,10,32,32,32,32,32,42,32,32,116,104,101,109,32,105,110,116,111,32,115,116,97,110,100,45,97,108,111,110,101,32,118,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,32,99,104,97,110,
110,101,108,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,85,86,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,115,32,97,114,101,32,115,112,101,99,105,102,105,101,100,32,112,101,114,45,116,101,120,116,117,114,101,32,45,32,115,101,101,
32,116,104,101,10,32,32,32,32,32,42,32,60,116,116,62,35,65,73,95,77,65,84,75,69,89,95,85,86,84,82,65,78,83,70,79,82,77,60,47,116,116,62,32,109,97,116,101,114,105,97,108,32,107,101,121,32,102,111,114,32,109,111,114,101,32,105,110,102,111,114,109,97,116,
105,111,110,46,10,32,32,32,32,32,42,32,84,104,105,115,32,115,116,101,112,32,112,114,111,99,101,115,115,101,115,32,97,108,108,32,116,101,120,116,117,114,101,115,32,119,105,116,104,10,32,32,32,32,32,42,32,116,114,97,110,115,102,111,114,109,101,100,32,105,
110,112,117,116,32,85,86,32,99,111,111,114,100,105,110,97,116,101,115,32,97,110,100,32,103,101,110,101,114,97,116,101,115,32,97,32,110,101,119,32,40,112,114,101,45,116,114,97,110,115,102,111,114,109,101,100,41,32,85,86,32,99,104,97,110,110,101,108,10,
32,32,32,32,32,42,32,119,104,105,99,104,32,114,101,112,108,97,99,101,115,32,116,104,101,32,111,108,100,32,99,104,97,110,110,101,108,46,32,77,111,115,116,32,97,112,112,108,105,99,97,116,105,111,110,115,32,119,111,110,39,116,32,115,117,112,112,111,114,
116,32,85,86,10,32,32,32,32,32,42,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,115,44,32,115,111,32,121,111,117,32,119,105,108,108,32,112,114,111,98,97,98,108,121,32,119,97,110,116,32,116,111,32,115,112,101,99,105,102,121,32,116,104,105,115,
32,115,116,101,112,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,64,110,111,116,101,32,85,86,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,115,32,97,114,101,32,117,115,117,97,108,108,121,32,105,109,112,108,101,109,101,110,116,101,100,32,
105,110,32,114,101,97,108,45,116,105,109,101,32,97,112,112,115,32,98,121,10,32,32,32,32,32,42,32,116,114,97,110,115,102,111,114,109,105,110,103,32,116,101,120,116,117,114,101,32,99,111,111,114,100,105,110,97,116,101,115,32,97,116,32,118,101,114,116,101,
120,32,115,104,97,100,101,114,32,115,116,97,103,101,32,119,105,116,104,32,97,32,51,120,51,10,32,32,32,32,32,42,32,40,104,111,109,111,103,101,110,101,111,117,115,41,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,32,109,97,116,114,105,120,46,
10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,84,114,97,110,115,102,111,114,109,85,86,67,111,111,114,100,115,32,61,32,48,120,56,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,115,101,
97,114,99,104,101,115,32,102,111,114,32,100,117,112,108,105,99,97,116,101,32,109,101,115,104,101,115,32,97,110,100,32,114,101,112,108,97,99,101,115,32,116,104,101,109,10,32,32,32,32,32,42,32,32,119,105,116,104,32,114,101,102,101,114,101,110,99,101,115,
32,116,111,32,116,104,101,32,102,105,114,115,116,32,109,101,115,104,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,84,104,105,115,32,115,116,101,112,32,116,97,107,101,115,32,97,32,119,104,105,108,101,44,32,115,111,32,100,111,110,39,116,32,117,115,
101,32,105,116,32,105,102,32,115,112,101,101,100,32,105,115,32,97,32,99,111,110,99,101,114,110,46,10,32,32,32,32,32,42,32,32,73,116,115,32,109,97,105,110,32,112,117,114,112,111,115,101,32,105,115,32,116,111,32,119,111,114,107,97,114,111,117,110,100,32,
116,104,101,32,102,97,99,116,32,116,104,97,116,32,109,97,110,121,32,101,120,112,111,114,116,10,32,32,32,32,32,42,32,32,102,105,108,101,32,102,111,114,109,97,116,115,32,100,111,110,39,116,32,115,117,112,112,111,114,116,32,105,110,115,116,97,110,99,101,
100,32,109,101,115,104,101,115,44,32,115,111,32,101,120,112,111,114,116,101,114,115,32,110,101,101,100,32,116,111,10,32,32,32,32,32,42,32,32,100,117,112,108,105,99,97,116,101,32,109,101,115,104,101,115,46,32,84,104,105,115,32,115,116,101,112,32,114,101,
109,111,118,101,115,32,116,104,101,32,100,117,112,108,105,99,97,116,101,115,32,97,103,97,105,110,46,32,80,108,101,97,115,101,10,32,32,32,32,32,42,32,32,110,111,116,101,32,116,104,97,116,32,65,115,115,105,109,112,32,100,111,101,115,32,110,111,116,32,99,
117,114,114,101,110,116,108,121,32,115,117,112,112,111,114,116,32,112,101,114,45,110,111,100,101,32,109,97,116,101,114,105,97,108,10,32,32,32,32,32,42,32,32,97,115,115,105,103,110,109,101,110,116,32,116,111,32,109,101,115,104,101,115,44,32,119,104,105,
99,104,32,109,101,97,110,115,32,116,104,97,116,32,105,100,101,110,116,105,99,97,108,32,109,101,115,104,101,115,32,119,105,116,104,10,32,32,32,32,32,42,32,32,100,105,102,102,101,114,101,110,116,32,109,97,116,101,114,105,97,108,115,32,97,114,101,32,99,
117,114,114,101,110,116,108,121,32,42,110,111,116,42,32,106,111,105,110,101,100,44,32,97,108,116,104,111,117,103,104,32,116,104,105,115,32,105,115,10,32,32,32,32,32,42,32,32,112,108,97,110,110,101,100,32,102,111,114,32,102,117,116,117,114,101,32,118,
101,114,115,105,111,110,115,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,105,110,100,73,110,115,116,97,110,99,101,115,32,61,32,48,120,49,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,65,32,112,111,115,116,45,
112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,116,111,32,114,101,100,117,99,101,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,109,101,115,104,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,84,104,105,115,32,119,105,
108,108,44,32,105,110,32,102,97,99,116,44,32,114,101,100,117,99,101,32,116,104,101,32,110,117,109,98,101,114,32,111,102,32,100,114,97,119,32,99,97,108,108,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,84,104,105,115,32,105,115,32,97,32,118,101,
114,121,32,101,102,102,101,99,116,105,118,101,32,111,112,116,105,109,105,122,97,116,105,111,110,32,97,110,100,32,105,115,32,114,101,99,111,109,109,101,110,100,101,100,32,116,111,32,98,101,32,117,115,101,100,10,32,32,32,32,32,42,32,32,116,111,103,101,
116,104,101,114,32,119,105,116,104,32,35,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,122,101,71,114,97,112,104,44,32,105,102,32,112,111,115,115,105,98,108,101,46,32,84,104,101,32,102,108,97,103,32,105,115,32,102,117,108,108,121,10,32,32,
32,32,32,42,32,32,99,111,109,112,97,116,105,98,108,101,32,119,105,116,104,32,98,111,116,104,32,35,97,105,80,114,111,99,101,115,115,95,83,112,108,105,116,76,97,114,103,101,77,101,115,104,101,115,32,97,110,100,32,35,97,105,80,114,111,99,101,115,115,95,
83,111,114,116,66,121,80,84,121,112,101,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,122,101,77,101,115,104,101,115,32,32,61,32,48,120,50,48,48,48,48,48,44,10,10,10,32,32,32,32,47,47,32,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,65,
32,112,111,115,116,45,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,116,111,32,111,112,116,105,109,105,122,101,32,116,104,101,32,115,99,101,110,101,32,104,105,101,114,97,114,99,104,121,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,
78,111,100,101,115,32,119,105,116,104,111,117,116,32,97,110,105,109,97,116,105,111,110,115,44,32,98,111,110,101,115,44,32,108,105,103,104,116,115,32,111,114,32,99,97,109,101,114,97,115,32,97,115,115,105,103,110,101,100,32,97,114,101,10,32,32,32,32,32,
42,32,32,99,111,108,108,97,112,115,101,100,32,97,110,100,32,106,111,105,110,101,100,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,78,111,100,101,32,110,97,109,101,115,32,99,97,110,32,98,101,32,108,111,115,116,32,100,117,114,105,110,103,32,116,104,
105,115,32,115,116,101,112,46,32,73,102,32,121,111,117,32,117,115,101,32,115,112,101,99,105,97,108,32,39,116,97,103,32,110,111,100,101,115,39,10,32,32,32,32,32,42,32,32,116,111,32,112,97,115,115,32,97,100,100,105,116,105,111,110,97,108,32,105,110,102,
111,114,109,97,116,105,111,110,32,116,104,114,111,117,103,104,32,121,111,117,114,32,99,111,110,116,101,110,116,32,112,105,112,101,108,105,110,101,44,32,117,115,101,32,116,104,101,10,32,32,32,32,32,42,32,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,
95,80,80,95,79,71,95,69,88,67,76,85,68,69,95,76,73,83,84,60,47,116,116,62,32,105,109,112,111,114,116,101,114,32,112,114,111,112,101,114,116,121,32,116,111,32,115,112,101,99,105,102,121,32,97,10,32,32,32,32,32,42,32,32,108,105,115,116,32,111,102,32,110,
111,100,101,32,110,97,109,101,115,32,121,111,117,32,119,97,110,116,32,116,111,32,98,101,32,107,101,112,116,46,32,78,111,100,101,115,32,109,97,116,99,104,105,110,103,32,111,110,101,32,111,102,32,116,104,101,32,110,97,109,101,115,10,32,32,32,32,32,42,32,
32,105,110,32,116,104,105,115,32,108,105,115,116,32,119,111,110,39,116,32,98,101,32,116,111,117,99,104,101,100,32,111,114,32,109,111,100,105,102,105,101,100,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,85,115,101,32,116,104,105,115,32,102,108,97,
103,32,119,105,116,104,32,99,97,117,116,105,111,110,46,32,77,111,115,116,32,115,105,109,112,108,101,32,102,105,108,101,115,32,119,105,108,108,32,98,101,32,99,111,108,108,97,112,115,101,100,32,116,111,32,97,10,32,32,32,32,32,42,32,32,115,105,110,103,108,
101,32,110,111,100,101,44,32,115,111,32,99,111,109,112,108,101,120,32,104,105,101,114,97,114,99,104,105,101,115,32,97,114,101,32,117,115,117,97,108,108,121,32,99,111,109,112,108,101,116,101,108,121,32,108,111,115,116,46,32,84,104,105,115,32,105,115,32,
110,111,116,10,32,32,32,32,32,42,32,32,117,115,101,102,117,108,32,102,111,114,32,101,100,105,116,111,114,32,101,110,118,105,114,111,110,109,101,110,116,115,44,32,98,117,116,32,112,114,111,98,97,98,108,121,32,97,32,118,101,114,121,32,101,102,102,101,99,
116,105,118,101,10,32,32,32,32,32,42,32,32,111,112,116,105,109,105,122,97,116,105,111,110,32,105,102,32,121,111,117,32,106,117,115,116,32,119,97,110,116,32,116,111,32,103,101,116,32,116,104,101,32,109,111,100,101,108,32,100,97,116,97,44,32,99,111,110,
118,101,114,116,32,105,116,32,116,111,32,121,111,117,114,10,32,32,32,32,32,42,32,32,111,119,110,32,102,111,114,109,97,116,44,32,97,110,100,32,114,101,110,100,101,114,32,105,116,32,97,115,32,102,97,115,116,32,97,115,32,112,111,115,115,105,98,108,101,46,
10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,84,104,105,115,32,102,108,97,103,32,105,115,32,100,101,115,105,103,110,101,100,32,116,111,32,98,101,32,117,115,101,100,32,119,105,116,104,32,35,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,
122,101,77,101,115,104,101,115,32,102,111,114,32,98,101,115,116,10,32,32,32,32,32,42,32,32,114,101,115,117,108,116,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,64,110,111,116,101,32,39,67,114,97,112,112,121,39,32,115,99,101,110,101,115,32,119,
105,116,104,32,116,104,111,117,115,97,110,100,115,32,111,102,32,101,120,116,114,101,109,101,108,121,32,115,109,97,108,108,32,109,101,115,104,101,115,32,112,97,99,107,101,100,10,32,32,32,32,32,42,32,32,105,110,32,100,101,101,112,108,121,32,110,101,115,
116,101,100,32,110,111,100,101,115,32,101,120,105,115,116,32,102,111,114,32,97,108,109,111,115,116,32,97,108,108,32,102,105,108,101,32,102,111,114,109,97,116,115,46,10,32,32,32,32,32,42,32,32,35,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,
105,122,101,77,101,115,104,101,115,32,105,110,32,99,111,109,98,105,110,97,116,105,111,110,32,119,105,116,104,32,35,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,122,101,71,114,97,112,104,10,32,32,32,32,32,42,32,32,117,115,117,97,108,108,
121,32,102,105,120,101,115,32,116,104,101,109,32,97,108,108,32,97,110,100,32,109,97,107,101,115,32,116,104,101,109,32,114,101,110,100,101,114,97,98,108,101,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,
105,122,101,71,114,97,112,104,32,32,61,32,48,120,52,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,102,108,105,112,115,32,97,108,108,32,85,86,32,99,111,111,114,100,105,110,97,116,101,115,32,97,108,111,110,
103,32,116,104,101,32,121,45,97,120,105,115,32,97,110,100,32,97,100,106,117,115,116,115,10,32,32,32,32,32,42,32,109,97,116,101,114,105,97,108,32,115,101,116,116,105,110,103,115,32,97,110,100,32,98,105,116,97,110,103,101,110,116,115,32,97,99,99,111,114,
100,105,110,103,108,121,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,60,98,62,79,117,116,112,117,116,32,85,86,32,99,111,111,114,100,105,110,97,116,101,32,115,121,115,116,101,109,58,60,47,98,62,10,32,32,32,32,32,42,32,64,99,111,100,101,10,32,32,32,
32,32,42,32,48,120,124,48,121,32,45,45,45,45,45,45,45,45,45,45,32,49,120,124,48,121,10,32,32,32,32,32,42,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,10,32,32,32,32,32,42,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,
10,32,32,32,32,32,42,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,10,32,32,32,32,32,42,32,48,120,124,49,121,32,45,45,45,45,45,45,45,45,45,45,32,49,120,124,49,121,10,32,32,32,32,32,42,32,64,101,110,100,99,111,100,101,10,32,32,32,32,32,
42,10,32,32,32,32,32,42,32,89,111,117,39,108,108,32,112,114,111,98,97,98,108,121,32,119,97,110,116,32,116,111,32,99,111,110,115,105,100,101,114,32,116,104,105,115,32,102,108,97,103,32,105,102,32,121,111,117,32,117,115,101,32,68,105,114,101,99,116,51,
68,32,102,111,114,10,32,32,32,32,32,42,32,114,101,110,100,101,114,105,110,103,46,32,84,104,101,32,35,97,105,80,114,111,99,101,115,115,95,67,111,110,118,101,114,116,84,111,76,101,102,116,72,97,110,100,101,100,32,102,108,97,103,32,115,117,112,101,114,115,
101,100,101,115,32,116,104,105,115,10,32,32,32,32,32,42,32,115,101,116,116,105,110,103,32,97,110,100,32,98,117,110,100,108,101,115,32,97,108,108,32,99,111,110,118,101,114,115,105,111,110,115,32,116,121,112,105,99,97,108,108,121,32,114,101,113,117,105,
114,101,100,32,102,111,114,32,68,51,68,45,98,97,115,101,100,10,32,32,32,32,32,42,32,97,112,112,108,105,99,97,116,105,111,110,115,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,108,105,112,85,86,115,32,61,32,48,120,56,48,
48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,97,100,106,117,115,116,115,32,116,104,101,32,111,117,116,112,117,116,32,102,97,99,101,32,119,105,110,100,105,110,103,32,111,114,100,101,114,32,116,111,32,98,101,32,
67,87,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,101,32,100,101,102,97,117,108,116,32,102,97,99,101,32,119,105,110,100,105,110,103,32,111,114,100,101,114,32,105,115,32,99,111,117,110,116,101,114,32,99,108,111,99,107,119,105,115,101,32,40,
67,67,87,41,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,60,98,62,79,117,116,112,117,116,32,102,97,99,101,32,111,114,100,101,114,58,60,47,98,62,10,32,32,32,32,32,42,32,64,99,111,100,101,10,32,32,32,32,32,42,32,32,32,32,32,32,32,120,50,10,32,32,32,
32,32,42,10,32,32,32,32,32,42,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,120,48,10,32,32,32,32,32,42,32,32,120,49,10,32,32,32,32,32,42,32,64,101,110,100,99,111,100,101,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,
111,99,101,115,115,95,70,108,105,112,87,105,110,100,105,110,103,79,114,100,101,114,32,32,61,32,48,120,49,48,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,115,112,108,105,116,115,32,109,101,115,104,101,115,32,
119,105,116,104,32,109,97,110,121,32,98,111,110,101,115,32,105,110,116,111,32,115,117,98,45,109,101,115,104,101,115,32,115,111,32,116,104,97,116,32,101,97,99,104,10,32,32,32,32,32,42,32,115,117,98,45,109,101,115,104,32,104,97,115,32,102,101,119,101,114,
32,111,114,32,97,115,32,109,97,110,121,32,98,111,110,101,115,32,97,115,32,97,32,103,105,118,101,110,32,108,105,109,105,116,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,83,112,108,105,116,66,121,66,111,110,101,67,111,117,
110,116,32,32,61,32,48,120,50,48,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,115,32,115,116,101,112,32,114,101,109,111,118,101,115,32,98,111,110,101,115,32,108,111,115,115,108,101,115,115,108,121,32,111,114,32,97,99,99,111,114,100,
105,110,103,32,116,111,32,115,111,109,101,32,116,104,114,101,115,104,111,108,100,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,73,110,32,115,111,109,101,32,99,97,115,101,115,32,40,105,46,101,46,32,102,111,114,109,97,116,115,32,116,104,97,116,32,
114,101,113,117,105,114,101,32,105,116,41,32,101,120,112,111,114,116,101,114,115,32,97,114,101,32,102,111,114,99,101,100,32,116,111,10,32,32,32,32,32,42,32,32,97,115,115,105,103,110,32,100,117,109,109,121,32,98,111,110,101,32,119,101,105,103,104,116,
115,32,116,111,32,111,116,104,101,114,119,105,115,101,32,115,116,97,116,105,99,32,109,101,115,104,101,115,32,97,115,115,105,103,110,101,100,32,116,111,10,32,32,32,32,32,42,32,32,97,110,105,109,97,116,101,100,32,109,101,115,104,101,115,46,32,70,117,108,
108,44,32,119,101,105,103,104,116,45,98,97,115,101,100,32,115,107,105,110,110,105,110,103,32,105,115,32,101,120,112,101,110,115,105,118,101,32,119,104,105,108,101,10,32,32,32,32,32,42,32,32,97,110,105,109,97,116,105,110,103,32,110,111,100,101,115,32,
105,115,32,101,120,116,114,101,109,101,108,121,32,99,104,101,97,112,44,32,115,111,32,116,104,105,115,32,115,116,101,112,32,105,115,32,111,102,102,101,114,101,100,32,116,111,32,99,108,101,97,110,32,117,112,10,32,32,32,32,32,42,32,32,116,104,101,32,100,
97,116,97,32,105,110,32,116,104,97,116,32,114,101,103,97,114,100,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,85,115,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,68,66,95,84,72,82,69,83,72,79,76,68,60,47,116,116,62,32,116,111,
32,99,111,110,116,114,111,108,32,116,104,105,115,46,10,32,32,32,32,32,42,32,32,85,115,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,80,80,95,68,66,95,65,76,76,95,79,82,95,78,79,78,69,60,47,116,116,62,32,105,102,32,121,111,117,32,119,97,110,116,
32,98,111,110,101,115,32,114,101,109,111,118,101,100,32,105,102,32,97,110,100,10,32,32,32,32,32,42,32,32,111,110,108,121,32,105,102,32,97,108,108,32,98,111,110,101,115,32,119,105,116,104,105,110,32,116,104,101,32,115,99,101,110,101,32,113,117,97,108,
105,102,121,32,102,111,114,32,114,101,109,111,118,97,108,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,68,101,98,111,110,101,32,32,61,32,48,120,52,48,48,48,48,48,48,44,10,10,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,84,104,105,
115,32,115,116,101,112,32,119,105,108,108,32,112,101,114,102,111,114,109,32,97,32,103,108,111,98,97,108,32,115,99,97,108,101,32,111,102,32,116,104,101,32,109,111,100,101,108,46,10,32,32,32,32,42,10,32,32,32,32,42,32,32,83,111,109,101,32,105,109,112,111,
114,116,101,114,115,32,97,114,101,32,112,114,111,118,105,100,105,110,103,32,97,32,109,101,99,104,97,110,105,115,109,32,116,111,32,100,101,102,105,110,101,32,97,32,115,99,97,108,105,110,103,32,117,110,105,116,32,102,111,114,32,116,104,101,10,32,32,32,
32,42,32,32,109,111,100,101,108,46,32,84,104,105,115,32,112,111,115,116,32,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,99,97,110,32,98,101,32,117,115,101,100,32,116,111,32,100,111,32,115,111,46,32,89,111,117,32,110,101,101,100,32,116,
111,32,103,101,116,32,116,104,101,10,32,32,32,32,42,32,32,103,108,111,98,97,108,32,115,99,97,108,105,110,103,32,102,114,111,109,32,121,111,117,114,32,105,109,112,111,114,116,101,114,32,115,101,116,116,105,110,103,115,32,108,105,107,101,32,105,110,32,
70,66,88,46,32,85,115,101,32,116,104,101,32,102,108,97,103,10,32,32,32,32,42,32,32,65,73,95,67,79,78,70,73,71,95,71,76,79,66,65,76,95,83,67,65,76,69,95,70,65,67,84,79,82,95,75,69,89,32,102,114,111,109,32,116,104,101,32,103,108,111,98,97,108,32,112,114,
111,112,101,114,116,121,32,116,97,98,108,101,32,116,111,32,99,111,110,102,105,103,117,114,101,32,116,104,105,115,46,10,32,32,32,32,42,10,32,32,32,32,42,32,32,85,115,101,32,60,116,116,62,35,65,73,95,67,79,78,70,73,71,95,71,76,79,66,65,76,95,83,67,65,76,
69,95,70,65,67,84,79,82,95,75,69,89,60,47,116,116,62,32,116,111,32,115,101,116,117,112,32,116,104,101,32,103,108,111,98,97,108,32,115,99,97,108,105,110,103,32,102,97,99,116,111,114,46,10,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,
95,71,108,111,98,97,108,83,99,97,108,101,32,61,32,48,120,56,48,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,65,32,112,111,115,116,112,114,111,99,101,115,115,105,110,103,32,115,116,101,112,32,116,111,32,101,109,98,101,100,32,111,102,32,116,101,
120,116,117,114,101,115,46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,32,84,104,105,115,32,119,105,108,108,32,114,101,109,111,118,101,32,101,120,116,101,114,110,97,108,32,100,97,116,97,32,100,101,112,101,110,100,101,110,99,105,101,115,32,102,111,114,
32,116,101,120,116,117,114,101,115,46,10,32,32,32,32,32,42,32,32,73,102,32,97,32,116,101,120,116,117,114,101,39,115,32,102,105,108,101,32,100,111,101,115,32,110,111,116,32,101,120,105,115,116,32,97,116,32,116,104,101,32,115,112,101,99,105,102,105,101,
100,32,112,97,116,104,10,32,32,32,32,32,42,32,32,40,100,117,101,44,32,102,111,114,32,105,110,115,116,97,110,99,101,44,32,116,111,32,97,110,32,97,98,115,111,108,117,116,101,32,112,97,116,104,32,103,101,110,101,114,97,116,101,100,32,111,110,32,97,110,111,
116,104,101,114,32,115,121,115,116,101,109,41,44,10,32,32,32,32,32,42,32,32,105,116,32,119,105,108,108,32,99,104,101,99,107,32,105,102,32,97,32,102,105,108,101,32,119,105,116,104,32,116,104,101,32,115,97,109,101,32,110,97,109,101,32,101,120,105,115,116,
115,32,97,116,32,116,104,101,32,114,111,111,116,32,102,111,108,100,101,114,10,32,32,32,32,32,42,32,32,111,102,32,116,104,101,32,105,109,112,111,114,116,101,100,32,109,111,100,101,108,46,32,65,110,100,32,105,102,32,115,111,44,32,105,116,32,117,115,101,
115,32,116,104,97,116,46,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,69,109,98,101,100,84,101,120,116,117,114,101,115,32,32,61,32,48,120,49,48,48,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,97,105,80,114,111,99,101,115,
115,95,71,101,110,69,110,116,105,116,121,77,101,115,104,101,115,32,61,32,48,120,49,48,48,48,48,48,44,10,32,32,32,32,47,47,32,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,122,101,65,110,105,109,97,116,105,111,110,115,32,61,32,48,120,50,48,
48,48,48,48,10,32,32,32,32,47,47,32,97,105,80,114,111,99,101,115,115,95,70,105,120,84,101,120,116,117,114,101,80,97,116,104,115,32,61,32,48,120,50,48,48,48,48,48,10,10,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,111,114,99,101,71,101,110,78,
111,114,109,97,108,115,32,61,32,48,120,50,48,48,48,48,48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,32,32,32,47,42,42,32,60,104,114,62,68,114,111,112,115,32,110,111,114,109,97,108,115,32,102,111,114,32,97,108,108,32,102,97,99,101,115,32,111,102,32,97,108,108,32,109,101,115,104,101,115,
46,10,32,32,32,32,32,42,10,32,32,32,32,32,42,32,84,104,105,115,32,105,115,32,105,103,110,111,114,101,100,32,105,102,32,110,111,32,110,111,114,109,97,108,115,32,97,114,101,32,112,114,101,115,101,110,116,46,10,32,32,32,32,32,42,32,70,97,99,101,32,110,111,
114,109,97,108,115,32,97,114,101,32,115,104,97,114,101,100,32,98,101,116,119,101,101,110,32,97,108,108,32,112,111,105,110,116,115,32,111,102,32,97,32,115,105,110,103,108,101,32,102,97,99,101,44,10,32,32,32,32,32,42,32,115,111,32,97,32,115,105,110,103,
108,101,32,112,111,105,110,116,32,99,97,110,32,104,97,118,101,32,109,117,108,116,105,112,108,101,32,110,111,114,109,97,108,115,44,32,119,104,105,99,104,10,32,32,32,32,32,42,32,102,111,114,99,101,115,32,116,104,101,32,108,105,98,114,97,114,121,32,116,
111,32,100,117,112,108,105,99,97,116,101,32,118,101,114,116,105,99,101,115,32,105,110,32,115,111,109,101,32,99,97,115,101,115,46,10,32,32,32,32,32,42,32,35,97,105,80,114,111,99,101,115,115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,101,114,
116,105,99,101,115,32,105,115,32,42,115,101,110,115,101,108,101,115,115,42,32,116,104,101,110,46,10,32,32,32,32,32,42,32,84,104,105,115,32,112,114,111,99,101,115,115,32,103,105,118,101,115,32,115,101,110,115,101,32,98,97,99,107,32,116,111,32,97,105,80,
114,111,99,101,115,115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,101,114,116,105,99,101,115,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,68,114,111,112,78,111,114,109,97,108,115,32,61,32,48,120,52,48,48,48,48,
48,48,48,44,10,10,32,32,32,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,10,32,32,32,32,47,42,42,10,32,32,32,32,32,42,47,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,101,110,66,111,117,110,100,105,110,103,66,111,120,101,115,32,61,32,48,120,56,48,48,48,48,48,48,48,10,125,59,10,10,10,47,47,32,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,47,42,
42,32,64,100,101,102,32,97,105,80,114,111,99,101,115,115,95,67,111,110,118,101,114,116,84,111,76,101,102,116,72,97,110,100,101,100,10,32,42,32,32,64,98,114,105,101,102,32,83,104,111,114,116,99,117,116,32,102,108,97,103,32,102,111,114,32,68,105,114,101,
99,116,51,68,45,98,97,115,101,100,32,97,112,112,108,105,99,97,116,105,111,110,115,46,10,32,42,10,32,42,32,32,83,117,112,101,114,115,101,100,101,115,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,77,97,107,101,76,101,102,116,72,97,110,100,101,
100,32,97,110,100,32,35,97,105,80,114,111,99,101,115,115,95,70,108,105,112,85,86,115,32,97,110,100,10,32,42,32,32,35,97,105,80,114,111,99,101,115,115,95,70,108,105,112,87,105,110,100,105,110,103,79,114,100,101,114,32,102,108,97,103,115,46,10,32,42,32,
32,84,104,101,32,111,117,116,112,117,116,32,100,97,116,97,32,109,97,116,99,104,101,115,32,68,105,114,101,99,116,51,68,39,115,32,99,111,110,118,101,110,116,105,111,110,115,58,32,108,101,102,116,45,104,97,110,100,101,100,32,103,101,111,109,101,116,114,
121,44,32,117,112,112,101,114,45,108,101,102,116,10,32,42,32,32,111,114,105,103,105,110,32,102,111,114,32,85,86,32,99,111,111,114,100,105,110,97,116,101,115,32,97,110,100,32,102,105,110,97,108,108,121,32,99,108,111,99,107,119,105,115,101,32,102,97,99,
101,32,111,114,100,101,114,44,32,115,117,105,116,97,98,108,101,32,102,111,114,32,67,67,87,32,99,117,108,108,105,110,103,46,10,32,42,10,32,42,32,32,64,100,101,112,114,101,99,97,116,101,100,10,32,42,47,10,35,100,101,102,105,110,101,32,97,105,80,114,111,
99,101,115,115,95,67,111,110,118,101,114,116,84,111,76,101,102,116,72,97,110,100,101,100,32,40,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,77,97,107,101,76,101,102,116,72,97,110,100,101,100,32,32,32,32,32,124,32,92,10,32,32,32,32,97,105,
80,114,111,99,101,115,115,95,70,108,105,112,85,86,115,32,32,32,32,32,32,32,32,32,32,32,32,124,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,108,105,112,87,105,110,100,105,110,103,79,114,100,101,114,32,32,32,124,32,92,10,32,32,32,32,48,32,
41,10,10,10,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,10,47,42,42,32,64,100,101,102,32,97,105,80,114,111,99,101,115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,82,101,97,108,116,105,109,101,95,70,97,115,116,10,32,42,32,32,64,98,114,105,101,102,32,68,101,102,97,117,108,
116,32,112,111,115,116,112,114,111,99,101,115,115,32,99,111,110,102,105,103,117,114,97,116,105,111,110,32,111,112,116,105,109,105,122,105,110,103,32,116,104,101,32,100,97,116,97,32,102,111,114,32,114,101,97,108,45,116,105,109,101,32,114,101,110,100,101,
114,105,110,103,46,10,32,42,10,32,42,32,32,65,112,112,108,105,99,97,116,105,111,110,115,32,119,111,117,108,100,32,119,97,110,116,32,116,111,32,117,115,101,32,116,104,105,115,32,112,114,101,115,101,116,32,116,111,32,108,111,97,100,32,109,111,100,101,108,
115,32,111,110,32,101,110,100,45,117,115,101,114,32,80,67,115,44,10,32,42,32,32,109,97,121,98,101,32,102,111,114,32,100,105,114,101,99,116,32,117,115,101,32,105,110,32,103,97,109,101,46,10,32,42,10,32,42,32,73,102,32,121,111,117,39,114,101,32,117,115,
105,110,103,32,68,105,114,101,99,116,88,44,32,100,111,110,39,116,32,102,111,114,103,101,116,32,116,111,32,99,111,109,98,105,110,101,32,116,104,105,115,32,118,97,108,117,101,32,119,105,116,104,10,32,42,32,116,104,101,32,35,97,105,80,114,111,99,101,115,
115,95,67,111,110,118,101,114,116,84,111,76,101,102,116,72,97,110,100,101,100,32,115,116,101,112,46,32,73,102,32,121,111,117,32,100,111,110,39,116,32,115,117,112,112,111,114,116,32,85,86,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,115,10,
32,42,32,105,110,32,121,111,117,114,32,97,112,112,108,105,99,97,116,105,111,110,32,97,112,112,108,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,84,114,97,110,115,102,111,114,109,85,86,67,111,111,114,100,115,32,115,116,101,112,44,32,116,
111,111,46,10,32,42,32,32,64,110,111,116,101,32,80,108,101,97,115,101,32,116,97,107,101,32,116,104,101,32,116,105,109,101,32,116,111,32,114,101,97,100,32,116,104,101,32,100,111,99,115,32,102,111,114,32,116,104,101,32,115,116,101,112,115,32,101,110,97,
98,108,101,100,32,98,121,32,116,104,105,115,32,112,114,101,115,101,116,46,10,32,42,32,32,83,111,109,101,32,111,102,32,116,104,101,109,32,111,102,102,101,114,32,102,117,114,116,104,101,114,32,99,111,110,102,105,103,117,114,97,98,108,101,32,112,114,111,
112,101,114,116,105,101,115,44,32,119,104,105,108,101,32,115,111,109,101,32,111,102,32,116,104,101,109,32,109,105,103,104,116,32,110,111,116,32,98,101,32,111,102,10,32,42,32,32,117,115,101,32,102,111,114,32,121,111,117,32,115,111,32,105,116,32,109,105,
103,104,116,32,98,101,32,98,101,116,116,101,114,32,116,111,32,110,111,116,32,115,112,101,99,105,102,121,32,116,104,101,109,46,10,32,42,47,10,35,100,101,102,105,110,101,32,97,105,80,114,111,99,101,115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,
82,101,97,108,116,105,109,101,95,70,97,115,116,32,40,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,67,97,108,99,84,97,110,103,101,110,116,83,112,97,99,101,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,
101,110,78,111,114,109,97,108,115,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,101,114,116,105,99,101,115,32,124,32,32,92,10,32,32,32,32,97,105,
80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,101,110,85,86,67,111,111,114,100,115,32,32,32,32,32,32,32,32,32,32,32,124,32,32,
92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,101,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,48,32,41,10,10,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,47,42,42,32,64,100,101,102,32,97,105,80,114,111,99,101,
115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,82,101,97,108,116,105,109,101,95,81,117,97,108,105,116,121,10,32,32,42,32,32,64,98,114,105,101,102,32,68,101,102,97,117,108,116,32,112,111,115,116,112,114,111,99,101,115,115,32,99,111,110,102,105,
103,117,114,97,116,105,111,110,32,111,112,116,105,109,105,122,105,110,103,32,116,104,101,32,100,97,116,97,32,102,111,114,32,114,101,97,108,45,116,105,109,101,32,114,101,110,100,101,114,105,110,103,46,10,32,32,42,10,32,32,42,32,32,85,110,108,105,107,101,
32,35,97,105,80,114,111,99,101,115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,82,101,97,108,116,105,109,101,95,70,97,115,116,44,32,116,104,105,115,32,99,111,110,102,105,103,117,114,97,116,105,111,110,10,32,32,42,32,32,112,101,114,102,111,114,
109,115,32,115,111,109,101,32,101,120,116,114,97,32,111,112,116,105,109,105,122,97,116,105,111,110,115,32,116,111,32,105,109,112,114,111,118,101,32,114,101,110,100,101,114,105,110,103,32,115,112,101,101,100,32,97,110,100,10,32,32,42,32,32,116,111,32,
109,105,110,105,109,105,122,101,32,109,101,109,111,114,121,32,117,115,97,103,101,46,32,73,116,32,99,111,117,108,100,32,98,101,32,97,32,103,111,111,100,32,99,104,111,105,99,101,32,102,111,114,32,97,32,108,101,118,101,108,32,101,100,105,116,111,114,10,
32,32,42,32,32,101,110,118,105,114,111,110,109,101,110,116,32,119,104,101,114,101,32,105,109,112,111,114,116,32,115,112,101,101,100,32,105,115,32,110,111,116,32,115,111,32,105,109,112,111,114,116,97,110,116,46,10,32,32,42,10,32,32,42,32,32,73,102,32,
121,111,117,39,114,101,32,117,115,105,110,103,32,68,105,114,101,99,116,88,44,32,100,111,110,39,116,32,102,111,114,103,101,116,32,116,111,32,99,111,109,98,105,110,101,32,116,104,105,115,32,118,97,108,117,101,32,119,105,116,104,10,32,32,42,32,32,116,104,
101,32,35,97,105,80,114,111,99,101,115,115,95,67,111,110,118,101,114,116,84,111,76,101,102,116,72,97,110,100,101,100,32,115,116,101,112,46,32,73,102,32,121,111,117,32,100,111,110,39,116,32,115,117,112,112,111,114,116,32,85,86,32,116,114,97,110,115,102,
111,114,109,97,116,105,111,110,115,10,32,32,42,32,32,105,110,32,121,111,117,114,32,97,112,112,108,105,99,97,116,105,111,110,32,97,112,112,108,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,84,114,97,110,115,102,111,114,109,85,86,67,111,
111,114,100,115,32,115,116,101,112,44,32,116,111,111,46,10,32,32,42,32,32,64,110,111,116,101,32,80,108,101,97,115,101,32,116,97,107,101,32,116,104,101,32,116,105,109,101,32,116,111,32,114,101,97,100,32,116,104,101,32,100,111,99,115,32,102,111,114,32,
116,104,101,32,115,116,101,112,115,32,101,110,97,98,108,101,100,32,98,121,32,116,104,105,115,32,112,114,101,115,101,116,46,10,32,32,42,32,32,83,111,109,101,32,111,102,32,116,104,101,109,32,111,102,102,101,114,32,102,117,114,116,104,101,114,32,99,111,
110,102,105,103,117,114,97,98,108,101,32,112,114,111,112,101,114,116,105,101,115,44,32,119,104,105,108,101,32,115,111,109,101,32,111,102,32,116,104,101,109,32,109,105,103,104,116,32,110,111,116,32,98,101,10,32,32,42,32,32,111,102,32,117,115,101,32,102,
111,114,32,121,111,117,32,115,111,32,105,116,32,109,105,103,104,116,32,98,101,32,98,101,116,116,101,114,32,116,111,32,110,111,116,32,115,112,101,99,105,102,121,32,116,104,101,109,46,10,32,32,42,47,10,35,100,101,102,105,110,101,32,97,105,80,114,111,99,
101,115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,82,101,97,108,116,105,109,101,95,81,117,97,108,105,116,121,32,40,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,67,97,108,99,84,97,110,103,101,110,116,83,112,97,99,101,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,71,101,110,83,109,111,111,116,104,78,111,114,109,97,108,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,
115,95,74,111,105,110,73,100,101,110,116,105,99,97,108,86,101,114,116,105,99,101,115,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,73,109,112,114,111,118,101,67,97,99,104,101,76,111,99,97,108,105,116,121,32,
32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,76,105,109,105,116,66,111,110,101,87,101,105,103,104,116,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,
115,95,82,101,109,111,118,101,82,101,100,117,110,100,97,110,116,77,97,116,101,114,105,97,108,115,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,83,112,108,105,116,76,97,114,103,101,77,101,115,104,101,115,32,32,32,32,
32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,84,114,105,97,110,103,117,108,97,116,101,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,
95,71,101,110,85,86,67,111,111,114,100,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,83,111,114,116,66,121,80,84,121,112,101,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,105,110,100,68,101,103,101,110,101,114,97,116,101,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,70,105,110,
100,73,110,118,97,108,105,100,68,97,116,97,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,48,32,41,10,10,32,47,47,32,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,
45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,10,32,47,42,42,32,64,100,101,102,32,97,105,80,114,111,99,101,115,115,80,114,101,115,101,116,95,84,
97,114,103,101,116,82,101,97,108,116,105,109,101,95,77,97,120,81,117,97,108,105,116,121,10,32,32,42,32,32,64,98,114,105,101,102,32,68,101,102,97,117,108,116,32,112,111,115,116,112,114,111,99,101,115,115,32,99,111,110,102,105,103,117,114,97,116,105,111,
110,32,111,112,116,105,109,105,122,105,110,103,32,116,104,101,32,100,97,116,97,32,102,111,114,32,114,101,97,108,45,116,105,109,101,32,114,101,110,100,101,114,105,110,103,46,10,32,32,42,10,32,32,42,32,32,84,104,105,115,32,112,114,101,115,101,116,32,101,
110,97,98,108,101,115,32,97,108,109,111,115,116,32,101,118,101,114,121,32,111,112,116,105,109,105,122,97,116,105,111,110,32,115,116,101,112,32,116,111,32,97,99,104,105,101,118,101,32,112,101,114,102,101,99,116,108,121,10,32,32,42,32,32,111,112,116,105,
109,105,122,101,100,32,100,97,116,97,46,32,73,116,39,115,32,121,111,117,114,32,99,104,111,105,99,101,32,102,111,114,32,108,101,118,101,108,32,101,100,105,116,111,114,32,101,110,118,105,114,111,110,109,101,110,116,115,32,119,104,101,114,101,32,105,109,
112,111,114,116,32,115,112,101,101,100,10,32,32,42,32,32,105,115,32,110,111,116,32,105,109,112,111,114,116,97,110,116,46,10,32,32,42,10,32,32,42,32,32,73,102,32,121,111,117,39,114,101,32,117,115,105,110,103,32,68,105,114,101,99,116,88,44,32,100,111,110,
39,116,32,102,111,114,103,101,116,32,116,111,32,99,111,109,98,105,110,101,32,116,104,105,115,32,118,97,108,117,101,32,119,105,116,104,10,32,32,42,32,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,67,111,110,118,101,114,116,84,111,76,101,102,
116,72,97,110,100,101,100,32,115,116,101,112,46,32,73,102,32,121,111,117,32,100,111,110,39,116,32,115,117,112,112,111,114,116,32,85,86,32,116,114,97,110,115,102,111,114,109,97,116,105,111,110,115,10,32,32,42,32,32,105,110,32,121,111,117,114,32,97,112,
112,108,105,99,97,116,105,111,110,44,32,97,112,112,108,121,32,116,104,101,32,35,97,105,80,114,111,99,101,115,115,95,84,114,97,110,115,102,111,114,109,85,86,67,111,111,114,100,115,32,115,116,101,112,44,32,116,111,111,46,10,32,32,42,32,32,64,110,111,116,
101,32,80,108,101,97,115,101,32,116,97,107,101,32,116,104,101,32,116,105,109,101,32,116,111,32,114,101,97,100,32,116,104,101,32,100,111,99,115,32,102,111,114,32,116,104,101,32,115,116,101,112,115,32,101,110,97,98,108,101,100,32,98,121,32,116,104,105,
115,32,112,114,101,115,101,116,46,10,32,32,42,32,32,83,111,109,101,32,111,102,32,116,104,101,109,32,111,102,102,101,114,32,102,117,114,116,104,101,114,32,99,111,110,102,105,103,117,114,97,98,108,101,32,112,114,111,112,101,114,116,105,101,115,44,32,119,
104,105,108,101,32,115,111,109,101,32,111,102,32,116,104,101,109,32,109,105,103,104,116,32,110,111,116,32,98,101,10,32,32,42,32,32,111,102,32,117,115,101,32,102,111,114,32,121,111,117,32,115,111,32,105,116,32,109,105,103,104,116,32,98,101,32,98,101,116,
116,101,114,32,116,111,32,110,111,116,32,115,112,101,99,105,102,121,32,116,104,101,109,46,10,32,32,42,47,10,35,100,101,102,105,110,101,32,97,105,80,114,111,99,101,115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,82,101,97,108,116,105,109,101,95,
77,97,120,81,117,97,108,105,116,121,32,40,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,80,114,101,115,101,116,95,84,97,114,103,101,116,82,101,97,108,116,105,109,101,95,81,117,97,108,105,116,121,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,
114,111,99,101,115,115,95,70,105,110,100,73,110,115,116,97,110,99,101,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,86,97,108,105,100,97,116,101,68,97,116,97,83,116,114,117,99,
116,117,114,101,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,97,105,80,114,111,99,101,115,115,95,79,112,116,105,109,105,122,101,77,101,115,104,101,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,92,10,32,32,32,32,48,32,41,
10,10,10,35,105,102,100,101,102,32,95,95,99,112,108,117,115,112,108,117,115,10,125,32,47,47,32,101,110,100,32,111,102,32,101,120,116,101,114,110,32,34,67,34,10,35,101,110,100,105,102,10,10,35,101,110,100,105,102,32,47,47,32,65,73,95,80,79,83,84,80,82,
79,67,69,83,83,95,72,95,73,78,67,10,0,0 };

const char* postprocess_h = (const char*) temp_binary_data_3;

//================== scene.h ==================
static const unsigned char temp_binary_data_4[] =
"/*\n"
"---------------------------------------------------------------------------\n"
"Open Asset Import Library (assimp)\n"
"---------------------------------------------------------------------------\n"
"\n"
"Copyright (c) 2006-2025, assimp team\n"
"\n"
"All rights reserved.\n"
"\n"
"Redistribution and use of this software in source and binary forms,\n"
"with or without modification, are permitted provided that the following\n"
"conditions are met:\n"
"\n"
"* Redistributions of source code must retain the above\n"
"  copyright notice, this list of conditions and the\n"
"  following disclaimer.\n"
"\n"
"* Redistributions in binary form must reproduce the above\n"
"  copyright notice, this list of conditions and the\n"
"  following disclaimer in the documentation and/or other\n"
"  materials provided with the distribution.\n"
"\n"
"* Neither the name of the assimp team, nor the names of its\n"
"  contributors may be used to endorse or promote products\n"
"  derived from this software without specific prior\n"
"  written permission of the assimp team.\n"
"\n"
"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n"
"\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n"
"LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n"
"A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT\n"
"OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,\n"
"SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT\n"
"LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,\n"
"DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY\n"
"THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\n"
"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n"
"OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
"---------------------------------------------------------------------------\n"
"*/\n"
"\n"
"/** @file scene.h\n"
" *  @brief Defines the data structures in which the imported scene is returned.\n"
" */\n"
"#pragma once\n"
"#ifndef AI_SCENE_H_INC\n"
"#define AI_SCENE_H_INC\n"
"\n"
"#ifdef __GNUC__\n"
"#   pragma GCC system_header\n"
"#endif\n"
"\n"
"#include <assimp/types.h>\n"
"#include <assimp/texture.h>\n"
"#include <assimp/mesh.h>\n"
"#include <assimp/light.h>\n"
"#include <assimp/camera.h>\n"
"#include <assimp/material.h>\n"
"#include <assimp/anim.h>\n"
"#include <assimp/metadata.h>\n"
"\n"
"#ifdef __cplusplus\n"
"#  include <cstdlib>\n"
"extern \"C\" {\n"
"#endif\n"
"\n"
"#ifdef __GNUC__\n"
"#pragma GCC diagnostic push\n"
"#pragma GCC diagnostic ignored \"-Wattributes\"\n"
"#endif\n"
"\n"
"// -------------------------------------------------------------------------------\n"
"/**\n"
" * A node in the imported hierarchy.\n"
" *\n"
" * Each node has name, a parent node (except for the root node),\n"
" * a transformation relative to its parent and possibly several child nodes.\n"
" * Simple file formats don't support hierarchical structures - for these formats\n"
" * the imported scene does consist of only a single root node without children.\n"
" */\n"
"// -------------------------------------------------------------------------------\n"
"struct ASSIMP_API aiNode {\n"
"    /** The name of the node.\n"
"     *\n"
"     * The name might be empty (length of zero) but all nodes which\n"
"     * need to be referenced by either bones or animations are named.\n"
"     * Multiple nodes may have the same name, except for nodes which are referenced\n"
"     * by bones (see #aiBone and #aiMesh::mBones). Their names *must* be unique.\n"
"     *\n"
"     * Cameras and lights reference a specific node by name - if there\n"
"     * are multiple nodes with this name, they are assigned to each of them.\n"
"     * <br>\n"
"     * There are no limitations with regard to the characters contained in\n"
"     * the name string as it is usually taken directly from the source file.\n"
"     *\n"
"     * Implementations should be able to handle tokens such as whitespace, tabs,\n"
"     * line feeds, quotation marks, ampersands etc.\n"
"     *\n"
"     * Sometimes assimp introduces new nodes not present in the source file\n"
"     * into the hierarchy (usually out of necessity because sometimes the\n"
"     * source hierarchy format is simply not compatible). Their names are\n"
"     * surrounded by @verbatim <> @endverbatim e.g.\n"
"     *  @verbatim<DummyRootNode> @endverbatim.\n"
"     */\n"
"    C_STRUCT aiString mName;\n"
"\n"
"    /** The transformation relative to the node's parent. */\n"
"    C_STRUCT aiMatrix4x4 mTransformation;\n"
"\n"
"    /** Parent node. nullptr if this node is the root node. */\n"
"    C_STRUCT aiNode* mParent;\n"
"\n"
"    /** The number of child nodes of this node. */\n"
"    unsigned int mNumChildren;\n"
"\n"
"    /** The child nodes of this node. nullptr if mNumChildren is 0. */\n"
"    C_STRUCT aiNode** mChildren;\n"
"\n"
"    /** The number of meshes of this node. */\n"
"    unsigned int mNumMeshes;\n"
"\n"
"    /** The meshes of this node. Each entry is an index into the\n"
"      * mesh list of the #aiScene.\n"
"      */\n"
"    unsigned int* mMeshes;\n"
"\n"
"    /** Metadata associated with this node or nullptr if there is no metadata.\n"
"      *  Whether any metadata is generated depends on the source file format. See the\n"
"      * @link importer_notes @endlink page for more information on every source file\n"
"      * format. Importers that don't document any metadata don't write any.\n"
"      */\n"
"    C_STRUCT aiMetadata* mMetaData;\n"
"\n"
"#ifdef __cplusplus\n"
"    /** Constructor */\n"
"    aiNode();\n"
"\n"
"    /** Construction from a specific name */\n"
"    explicit aiNode(const std::string& name);\n"
"\n"
"    /** Destructor */\n"
"    ~aiNode();\n"
"\n"
"    /**\n"
"     *  @brief Searches for a node with a specific name, beginning at this\n"
"     *  nodes. Normally you will call this method on the root node\n"
"     *  of the scene.\n"
"     *\n"
"     *  @param name Name to search for\n"
"     *  @return nullptr or a valid Node if the search was successful.\n"
"     */\n"
"    inline const aiNode* FindNode(const aiString& name) const {\n"
"        return FindNode(name.data);\n"
"    }\n"
"\n"
"    inline aiNode* FindNode(const aiString& name) {\n"
"        return FindNode(name.data);\n"
"    }\n"
"\n"
"    /**\n"
"     * @brief Will search for a node described by its name.\n"
"     * @param[in] name  The name for the node to look for.\n"
"     * @return Pointer showing to the node or nullptr if not found.\n"
"     */\n"
"    const aiNode* FindNode(const char* name) const;\n"
"    aiNode* FindNode(const char* name);\n"
"\n"
"    // ------------------------------------------------------------------------------------------------\n"
"    // Helper to find the node associated with a bone in the scene\n"
"    const aiNode *findBoneNode(const aiBone *bone) const {\n"
"        if (bone == nullptr) {\n"
"            return nullptr;\n"
"        }\n"
"\n"
"        if (mName == bone->mName) {\n"
"            return this;\n"
"        }\n"
"\n"
"        for (unsigned int i = 0; i < mNumChildren; ++i) {\n"
"            aiNode *aChild = mChildren[i];\n"
"            if (aChild == nullptr) {\n"
"                continue;\n"
"            }\n"
"\n"
"            const aiNode *foundFromChild = nullptr;\n"
"            foundFromChild = aChild->findBoneNode(bone);\n"
"            if (foundFromChild) {\n"
"                return foundFromChild;\n"
"            }\n"
"        }\n"
"\n"
"        return nullptr;\n"
"    }\n"
"\n"
"    /**\n"
"     * @brief   Will add new children.\n"
"     * @param   numChildren  Number of children to add.\n"
"     * @param   children     The array with pointers showing to the children.\n"
"     */\n"
"    void addChildren(unsigned int numChildren, aiNode **children);\n"
"#endif // __cplusplus\n"
"};\n"
"\n"
"#ifdef __GNUC__\n"
"#pragma GCC diagnostic pop\n"
"#endif\n"
"\n"
"// -------------------------------------------------------------------------------\n"
"/**\n"
" * Specifies that the scene data structure that was imported is not complete.\n"
" * This flag bypasses some internal validations and allows the import\n"
" * of animation skeletons, material libraries or camera animation paths\n"
" * using Assimp. Most applications won't support such data.\n"
" */\n"
"#define AI_SCENE_FLAGS_INCOMPLETE   0x1\n"
"\n"
"/**\n"
" * This flag is set by the validation postprocess-step (aiPostProcess_ValidateDS)\n"
" * if the validation is successful. In a validated scene you can be sure that\n"
" * any cross references in the data structure (e.g. vertex indices) are valid.\n"
" */\n"
"#define AI_SCENE_FLAGS_VALIDATED    0x2\n"
"\n"
"/**\n"
" * This flag is set by the validation postprocess-step (aiPostProcess_ValidateDS)\n"
" * if the validation is successful but some issues have been found.\n"
" * This can for example mean that a texture that does not exist is referenced\n"
" * by a material or that the bone weights for a vertex don't sum to 1.0 ... .\n"
" * In most cases you should still be able to use the import. This flag could\n"
" * be useful for applications which don't capture Assimp's log output.\n"
" */\n"
"#define AI_SCENE_FLAGS_VALIDATION_WARNING   0x4\n"
"\n"
"/**\n"
" * This flag is currently only set by the aiProcess_JoinIdenticalVertices step.\n"
" * It indicates that the vertices of the output meshes aren't in the internal\n"
" * verbose format anymore. In the verbose format all vertices are unique,\n"
" * no vertex is ever referenced by more than one face.\n"
" */\n"
"#define AI_SCENE_FLAGS_NON_VERBOSE_FORMAT   0x8\n"
"\n"
" /**\n"
" * Denotes pure height-map terrain data. Pure terrains usually consist of quads,\n"
" * sometimes triangles, in a regular grid. The x,y coordinates of all vertex\n"
" * positions refer to the x,y coordinates on the terrain height map, the z-axis\n"
" * stores the elevation at a specific point.\n"
" *\n"
" * TER (Terragen) and HMP (3D Game Studio) are height map formats.\n"
" * @note Assimp is probably not the best choice for loading *huge* terrains -\n"
" * fully triangulated data takes extremely much free store and should be avoided\n"
" * as long as possible (typically you'll do the triangulation when you actually\n"
" * need to render it).\n"
" */\n"
"#define AI_SCENE_FLAGS_TERRAIN 0x10\n"
"\n"
" /**\n"
" * Specifies that the scene data can be shared between structures. For example:\n"
" * one vertex in few faces. \\ref AI_SCENE_FLAGS_NON_VERBOSE_FORMAT can not be\n"
" * used for this because \\ref AI_SCENE_FLAGS_NON_VERBOSE_FORMAT has internal\n"
" * meaning about postprocessing steps.\n"
" */\n"
"#define AI_SCENE_FLAGS_ALLOW_SHARED\t\t\t0x20\n"
"\n"
"// -------------------------------------------------------------------------------\n"
"/** The root structure of the imported data.\n"
" *\n"
" *  Everything that was imported from the given file can be accessed from here.\n"
" *  Objects of this class are generally maintained and owned by Assimp, not\n"
" *  by the caller. You shouldn't want to instance it, nor should you ever try to\n"
" *  delete a given scene on your own.\n"
" */\n"
"// -------------------------------------------------------------------------------\n"
"struct ASSIMP_API aiScene {\n"
"    /** Any combination of the AI_SCENE_FLAGS_XXX flags. By default\n"
"    * this value is 0, no flags are set. Most applications will\n"
"    * want to reject all scenes with the AI_SCENE_FLAGS_INCOMPLETE\n"
"    * bit set.\n"
"    */\n"
"    unsigned int mFlags;\n"
"\n"
"    /** The root node of the hierarchy.\n"
"    *\n"
"    * There will always be at least the root node if the import\n"
"    * was successful (and no special flags have been set).\n"
"    * Presence of further nodes depends on the format and content\n"
"    * of the imported file.\n"
"    */\n"
"    C_STRUCT aiNode* mRootNode;\n"
"\n"
"    /** The number of meshes in the scene. */\n"
"    unsigned int mNumMeshes;\n"
"\n"
"    /** The array of meshes.\n"
"    *\n"
"    * Use the indices given in the aiNode structure to access\n"
"    * this array. The array is mNumMeshes in size. If the\n"
"    * AI_SCENE_FLAGS_INCOMPLETE flag is not set there will always\n"
"    * be at least ONE material.\n"
"    */\n"
"    C_STRUCT aiMesh** mMeshes;\n"
"\n"
"    /** The number of materials in the scene. */\n"
"    unsigned int mNumMaterials;\n"
"\n"
"    /** The array of materials.\n"
"    *\n"
"    * Use the index given in each aiMesh structure to access this\n"
"    * array. The array is mNumMaterials in size. If the\n"
"    * AI_SCENE_FLAGS_INCOMPLETE flag is not set there will always\n"
"    * be at least ONE material.\n"
"    */\n"
"    C_STRUCT aiMaterial** mMaterials;\n"
"\n"
"    /** The number of animations in the scene. */\n"
"    unsigned int mNumAnimations;\n"
"\n"
"    /** The array of animations.\n"
"    *\n"
"    * All animations imported from the given file are listed here.\n"
"    * The array is mNumAnimations in size.\n"
"    */\n"
"    C_STRUCT aiAnimation** mAnimations;\n"
"\n"
"    /** The number of textures embedded into the file */\n"
"    unsigned int mNumTextures;\n"
"\n"
"    /** The array of embedded textures.\n"
"    *\n"
"    * Not many file formats embed their textures into the file.\n"
"    * An example is Quake's MDL format (which is also used by\n"
"    * some GameStudio versions)\n"
"    */\n"
"    C_STRUCT aiTexture** mTextures;\n"
"\n"
"    /** The number of light sources in the scene. Light sources\n"
"    * are fully optional, in most cases this attribute will be 0\n"
"        */\n"
"    unsigned int mNumLights;\n"
"\n"
"    /** The array of light sources.\n"
"    *\n"
"    * All light sources imported from the given file are\n"
"    * listed here. The array is mNumLights in size.\n"
"    */\n"
"    C_STRUCT aiLight** mLights;\n"
"\n"
"    /** The number of cameras in the scene. Cameras\n"
"    * are fully optional, in most cases this attribute will be 0\n"
"        */\n"
"    unsigned int mNumCameras;\n"
"\n"
"    /** The array of cameras.\n"
"    *\n"
"    * All cameras imported from the given file are listed here.\n"
"    * The array is mNumCameras in size. The first camera in the\n"
"    * array (if existing) is the default camera view into\n"
"    * the scene.\n"
"    */\n"
"    C_STRUCT aiCamera** mCameras;\n"
"\n"
"    /**\n"
"     *  @brief  The global metadata assigned to the scene itself.\n"
"     *\n"
"     *  This data contains global metadata which belongs to the scene like\n"
"     *  unit-conversions, versions, vendors or other model-specific data. This\n"
"     *  can be used to store format-specific metadata as well.\n"
"     */\n"
"    C_STRUCT aiMetadata* mMetaData;\n"
"\n"
"    /** The name of the scene itself.\n"
"     */\n"
"    C_STRUCT aiString mName;\n"
"\n"
"    /**\n"
"     *\n"
"     */\n"
"    unsigned int mNumSkeletons;\n"
"\n"
"    /**\n"
"     *\n"
"     */\n"
"    C_STRUCT aiSkeleton **mSkeletons;\n"
"\n"
"#ifdef __cplusplus\n"
"\n"
"    //! Default constructor - set everything to 0/nullptr\n"
"    aiScene();\n"
"\n"
"    //! Destructor\n"
"    ~aiScene();\n"
"\n"
"    //! Check whether the scene contains meshes\n"
"    //! Unless no special scene flags are set this will always be true.\n"
"    inline bool HasMeshes() const {\n"
"        return mMeshes != nullptr && mNumMeshes > 0;\n"
"    }\n"
"\n"
"    //! Check whether the scene contains materials\n"
"    //! Unless no special scene flags are set this will always be true.\n"
"    inline bool HasMaterials() const {\n"
"        return mMaterials != nullptr && mNumMaterials > 0;\n"
"    }\n"
"\n"
"    //! Check whether the scene contains lights\n"
"    inline bool HasLights() const {\n"
"        return mLights != nullptr && mNumLights > 0;\n"
"    }\n"
"\n"
"    //! Check whether the scene contains textures\n"
"    inline bool HasTextures() const {\n"
"        return mTextures != nullptr && mNumTextures > 0;\n"
"    }\n"
"\n"
"    //! Check whether the scene contains cameras\n"
"    inline bool HasCameras() const {\n"
"        return mCameras != nullptr && mNumCameras > 0;\n"
"    }\n"
"\n"
"    //! Check whether the scene contains animations\n"
"    inline bool HasAnimations() const {\n"
"        return mAnimations != nullptr && mNumAnimations > 0;\n"
"    }\n"
"\n"
"    //! Check whether the scene contains skeletons\n"
"    inline bool HasSkeletons() const {\n"
"        return mSkeletons != nullptr && mNumSkeletons > 0;\n"
"    }\n"
"\n"
"    //! Returns a short filename from a full path\n"
"    static const char* GetShortFilename(const char* filename) {\n"
"        const char* lastSlash = strrchr(filename, '/');\n"
"        const char* lastBackSlash = strrchr(filename, '\\\\');\n"
"        if (lastSlash < lastBackSlash) {\n"
"            lastSlash = lastBackSlash;\n"
"        }\n"
"        const char* shortFilename = lastSlash != nullptr ? lastSlash + 1 : filename;\n"
"        return shortFilename;\n"
"    }\n"
"\n"
"    //! Returns an embedded texture\n"
"    const aiTexture* GetEmbeddedTexture(const char* filename) const {\n"
"        return GetEmbeddedTextureAndIndex(filename).first;\n"
"    }\n"
"\n"
"    //! Returns an embedded texture and its index\n"
"    std::pair<const aiTexture*, int> GetEmbeddedTextureAndIndex(const char* filename) const {\n"
"        if (nullptr==filename) {\n"
"            return std::make_pair(nullptr, -1);\n"
"        }\n"
"        // lookup using texture ID (if referenced like: \"*1\", \"*2\", etc.)\n"
"        if ('*' == *filename) {\n"
"            int index = std::atoi(filename + 1);\n"
"            if (0 > index || mNumTextures <= static_cast<unsigned>(index)) {\n"
"                return std::make_pair(nullptr, -1);\n"
"            }\n"
"            return std::make_pair(mTextures[index], index);\n"
"        }\n"
"        // lookup using filename\n"
"        const char* shortFilename = GetShortFilename(filename);\n"
"        if (nullptr == shortFilename) {\n"
"            return std::make_pair(nullptr, -1);\n"
"        }\n"
"\n"
"        for (unsigned int i = 0; i < mNumTextures; i++) {\n"
"            const char* shortTextureFilename = GetShortFilename(mTextures[i]->mFilename.C_Str());\n"
"            if (strcmp(shortTextureFilename, shortFilename) == 0) {\n"
"                return std::make_pair(mTextures[i], static_cast<int>(i));\n"
"            }\n"
"        }\n"
"        return std::make_pair(nullptr, -1);\n"
"    }\n"
"\n"
"    /**\n"
"     * @brief Will try to locate a bone described by its name.\n"
"     *\n"
"     * @param name  The name to look for.\n"
"     * @return The bone as a pointer.\n"
"     */\n"
"    inline aiBone *findBone(const aiString &name) const {\n"
"        for (size_t m = 0; m < mNumMeshes; m++) {\n"
"            aiMesh *mesh = mMeshes[m];\n"
"            if (mesh == nullptr) {\n"
"                continue;\n"
"            }\n"
"\n"
"            for (size_t b = 0; b < mesh->mNumBones; b++) {\n"
"                aiBone *bone = mesh->mBones[b];\n"
"                if (bone == nullptr) {\n"
"                    continue;\n"
"                }\n"
"                if (name == bone->mName) {\n"
"                    return bone;\n"
"                }\n"
"            }\n"
"        }\n"
"        return nullptr;\n"
"    }\n"
"\n"
"#endif // __cplusplus\n"
"\n"
"    /**  Internal data, do not touch */\n"
"#ifdef __cplusplus\n"
"    void* mPrivate;\n"
"#else\n"
"    char* mPrivate;\n"
"#endif\n"
"\n"
"};\n"
"\n"
"#ifdef __cplusplus\n"
"}\n"
"#endif //! extern \"C\"\n"
"\n"
"#endif // AI_SCENE_H_INC\n";

const char* scene_h = (const char*) temp_binary_data_4;

//================== Halfway Attack Loud.wav ==================
static const unsigned char temp_binary_data_5[] =
{ 82,73,70,70,10,13,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,82,11,0,0,149,1,157,4,160,7,147,10,143,13,110,16,81,19,27,22,213,24,107,27,250,29,96,32,184,34,248,36,29,39,40,41,37,43,247,44,166,46,65,48,
178,49,240,50,30,52,35,53,250,53,182,54,81,55,193,55,14,56,55,56,59,56,34,56,228,55,137,55,14,55,103,54,147,53,170,52,159,51,112,50,38,49,196,47,65,46,172,44,17,43,93,41,165,39,230,37,23,36,80,34,137,32,187,30,235,28,32,27,88,25,139,23,220,21,44,20,139,
18,232,16,93,15,209,13,96,12,240,10,153,9,75,8,13,7,216,5,188,4,164,3,165,2,162,1,170,0,182,255,207,254,239,253,16,253,66,252,120,251,175,250,250,249,74,249,158,248,251,247,89,247,179,246,16,246,118,245,211,244,48,244,158,243,10,243,123,242,242,241,109,
241,220,240,101,240,238,239,134,239,30,239,217,238,147,238,80,238,31,238,0,238,227,237,215,237,211,237,223,237,235,237,12,238,48,238,92,238,142,238,208,238,13,239,85,239,150,239,214,239,25,240,98,240,166,240,234,240,56,241,131,241,195,241,0,242,69,242,
135,242,192,242,2,243,76,243,130,243,179,243,245,243,29,244,59,244,93,244,115,244,124,244,131,244,130,244,109,244,88,244,52,244,255,243,204,243,152,243,80,243,2,243,158,242,53,242,187,241,78,241,212,240,81,240,197,239,55,239,167,238,37,238,144,237,6,
237,155,236,57,236,224,235,151,235,97,235,48,235,48,235,61,235,120,235,203,235,52,236,181,236,85,237,18,238,216,238,205,239,230,240,8,242,74,243,148,244,243,245,110,247,252,248,136,250,28,252,203,253,88,255,237,0,117,2,249,3,112,5,221,6,58,8,134,9,187,
10,221,11,233,12,239,13,208,14,142,15,68,16,198,16,46,17,122,17,190,17,196,17,203,17,166,17,116,17,21,17,180,16,54,16,176,15,14,15,98,14,164,13,229,12,16,12,60,11,113,10,153,9,199,8,6,8,63,7,118,6,182,5,255,4,74,4,168,3,31,3,159,2,50,2,224,1,154,1,113,
1,108,1,132,1,165,1,237,1,82,2,209,2,99,3,15,4,207,4,159,5,132,6,109,7,113,8,124,9,148,10,159,11,192,12,201,13,209,14,214,15,219,16,204,17,174,18,128,19,73,20,253,20,158,21,51,22,188,22,54,23,163,23,17,24,103,24,166,24,218,24,234,24,220,24,188,24,134,
24,45,24,202,23,81,23,181,22,15,22,91,21,120,20,130,19,124,18,97,17,37,16,219,14,112,13,235,11,77,10,162,8,225,6,37,5,65,3,83,1,98,255,101,253,94,251,110,249,114,247,113,245,116,243,117,241,117,239,132,237,161,235,193,233,239,231,44,230,105,228,186,226,
253,224,86,223,192,221,66,220,188,218,82,217,241,215,150,214,81,213,28,212,237,210,206,209,206,208,189,207,196,206,241,205,30,205,112,204,221,203,90,203,250,202,195,202,166,202,183,202,234,202,56,203,164,203,71,204,1,205,214,205,235,206,32,208,111,209,
251,210,162,212,106,214,105,216,134,218,190,220,54,223,200,225,112,228,69,231,57,234,47,237,69,240,119,243,165,246,239,249,56,253,133,0,223,3,64,7,144,10,214,13,29,17,69,20,101,23,127,26,113,29,72,32,14,35,165,37,28,40,132,42,200,44,215,46,226,48,190,
50,104,52,251,53,103,55,151,56,172,57,151,58,87,59,238,59,98,60,174,60,204,60,215,60,167,60,105,60,252,59,104,59,184,58,221,57,224,56,199,55,143,54,58,53,198,51,59,50,147,48,205,46,247,44,9,43,3,41,4,39,231,36,203,34,171,32,143,30,120,28,107,26,113,24,
114,22,139,20,176,18,222,16,38,15,119,13,209,11,68,10,206,8,84,7,235,5,140,4,55,3,251,1,198,0,181,255,159,254,164,253,171,252,196,251,232,250,29,250,81,249,153,248,227,247,48,247,134,246,238,245,89,245,213,244,80,244,198,243,72,243,198,242,81,242,207,
241,101,241,226,240,102,240,232,239,121,239,252,238,135,238,25,238,182,237,82,237,254,236,158,236,81,236,20,236,241,235,200,235,190,235,172,235,181,235,194,235,227,235,253,235,45,236,98,236,165,236,244,236,70,237,164,237,251,237,103,238,219,238,90,239,
205,239,82,240,215,240,81,241,206,241,87,242,212,242,73,243,195,243,51,244,166,244,6,245,114,245,200,245,43,246,113,246,180,246,237,246,24,247,39,247,57,247,46,247,19,247,247,246,203,246,132,246,58,246,222,245,96,245,222,244,89,244,188,243,24,243,108,
242,165,241,224,240,20,240,60,239,101,238,154,237,189,236,240,235,62,235,147,234,245,233,134,233,32,233,222,232,189,232,179,232,190,232,253,232,85,233,198,233,108,234,35,235,242,235,233,236,5,238,41,239,115,240,232,241,101,243,4,245,187,246,109,248,49,
250,254,251,206,253,145,255,104,1,52,3,250,4,188,6,95,8,248,9,142,11,12,13,99,14,177,15,231,16,244,17,243,18,203,19,119,20,7,21,119,21,181,21,220,21,236,21,200,21,137,21,61,21,205,20,52,20,140,19,208,18,255,17,28,17,58,16,71,15,76,14,77,13,60,12,40,11,
23,10,1,9,246,7,237,6,249,5,18,5,71,4,138,3,222,2,103,2,9,2,211,1,191,1,209,1,247,1,70,2,184,2,64,3,238,3,194,4,149,5,123,6,110,7,120,8,122,9,158,10,192,11,221,12,247,13,5,15,15,16,11,17,251,17,211,18,169,19,106,20,22,21,187,21,71,22,186,22,30,23,109,
23,175,23,210,23,226,23,209,23,192,23,125,23,47,23,201,22,75,22,166,21,2,21,83,20,120,19,148,18,147,17,120,16,75,15,17,14,167,12,45,11,155,9,232,7,34,6,71,4,89,2,85,0,90,254,54,252,25,250,1,248,231,245,190,243,160,241,133,239,90,237,85,235,70,233,74,
231,94,229,138,227,167,225,242,223,56,222,150,220,12,219,150,217,38,216,196,214,129,213,58,212,18,211,1,210,246,208,22,208,89,207,150,206,244,205,127,205,21,205,213,204,185,204,185,204,223,204,43,205,133,205,245,205,149,206,63,207,247,207,227,208,229,
209,253,210,70,212,173,213,41,215,218,216,162,218,136,220,153,222,194,224,244,226,90,229,194,231,51,234,198,236,111,239,30,242,237,244,220,247,200,250,208,253,233,0,251,3,28,7,59,10,86,13,95,16,108,19,83,22,38,25,238,27,138,30,20,33,140,35,226,37,24,
40,68,42,68,44,21,46,222,47,116,49,225,50,50,52,88,53,77,54,43,55,205,55,56,56,148,56,196,56,213,56,205,56,174,56,100,56,4,56,160,55,2,55,88,54,146,53,176,52,175,51,159,50,111,49,39,48,197,46,73,45,185,43,23,42,105,40,175,38,244,36,37,35,85,33,136,31,
174,29,210,27,8,26,63,24,121,22,198,20,18,19,101,17,190,15,38,14,128,12,224,10,74,9,196,7,70,6,206,4,89,3,245,1,160,0,96,255,42,254,254,252,222,251,193,250,189,249,174,248,190,247,206,246,242,245,21,245,80,244,143,243,222,242,54,242,147,241,7,241,125,
240,10,240,145,239,41,239,186,238,80,238,237,237,145,237,62,237,243,236,177,236,126,236,85,236,57,236,46,236,41,236,46,236,58,236,74,236,104,236,142,236,210,236,11,237,74,237,144,237,219,237,36,238,124,238,220,238,53,239,163,239,9,240,120,240,231,240,
91,241,208,241,63,242,177,242,22,243,137,243,243,243,102,244,193,244,51,245,139,245,240,245,61,246,156,246,223,246,56,247,122,247,199,247,3,248,66,248,120,248,161,248,187,248,193,248,174,248,158,248,126,248,80,248,16,248,192,247,107,247,252,246,127,246,
238,245,87,245,180,244,3,244,71,243,123,242,168,241,214,240,0,240,44,239,122,238,192,237,32,237,143,236,39,236,199,235,136,235,114,235,100,235,104,235,135,235,193,235,14,236,109,236,251,236,149,237,86,238,39,239,24,240,29,241,51,242,105,243,182,244,26,
246,140,247,21,249,170,250,56,252,209,253,103,255,251,0,137,2,25,4,155,5,13,7,145,8,240,9,61,11,125,12,163,13,179,14,162,15,135,16,63,17,226,17,85,18,164,18,218,18,232,18,215,18,162,18,99,18,254,17,138,17,3,17,108,16,196,15,13,15,67,14,116,13,148,12,
173,11,187,10,208,9,221,8,218,7,239,6,0,6,24,5,77,4,157,3,245,2,105,2,2,2,168,1,101,1,72,1,78,1,97,1,153,1,238,1,90,2,228,2,131,3,65,4,15,5,234,5,217,6,211,7,220,8,238,9,10,11,40,12,60,13,83,14,105,15,111,16,132,17,124,18,103,19,79,20,37,21,222,21,137,
22,47,23,180,23,21,24,104,24,147,24,156,24,148,24,111,24,30,24,204,23,78,23,175,22,6,22,67,21,94,20,107,19,95,18,61,17,250,15,157,14,36,13,144,11,231,9,28,8,86,6,111,4,111,2,101,0,92,254,59,252,31,250,0,248,218,245,182,243,176,241,162,239,147,237,177,
235,208,233,239,231,40,230,127,228,208,226,47,225,179,223,61,222,229,220,154,219,105,218,75,217,62,216,47,215,75,214,124,213,173,212,246,211,94,211,205,210,68,210,232,209,138,209,76,209,36,209,24,209,35,209,81,209,142,209,228,209,92,210,220,210,129,211,
62,212,41,213,21,214,51,215,106,216,194,217,52,219,194,220,99,222,31,224,4,226,252,227,25,230,70,232,143,234,247,236,120,239,9,242,181,244,129,247,89,250,71,253,82,0,75,3,92,6,105,9,114,12,114,15,111,18,77,21,47,24,2,27,195,29,101,32,9,35,137,37,234,
39,47,42,78,44,74,46,49,48,224,49,102,51,205,52,248,53,231,54,189,55,111,56,236,56,80,57,139,57,155,57,131,57,79,57,243,56,122,56,226,55,36,55,76,54,86,53,54,52,12,51,207,49,130,48,21,47,172,45,34,44,139,42,232,40,63,39,121,37,190,35,227,33,19,32,55,
30,94,28,119,26,167,24,202,22,232,20,24,19,66,17,103,15,150,13,210,11,4,10,55,8,127,6,189,4,14,3,113,1,220,255,85,254,221,252,111,251,20,250,201,248,136,247,92,246,70,245,70,244,93,243,146,242,202,241,31,241,151,240,19,240,158,239,75,239,8,239,200,238,
148,238,103,238,63,238,30,238,3,238,241,237,228,237,235,237,227,237,250,237,13,238,28,238,56,238,95,238,148,238,194,238,255,238,53,239,100,239,152,239,220,239,27,240,99,240,164,240,227,240,36,241,110,241,180,241,247,241,60,242,127,242,185,242,241,242,
38,243,102,243,131,243,167,243,196,243,221,243,237,243,1,244,24,244,45,244,73,244,92,244,106,244,129,244,143,244,158,244,178,244,206,244,232,244,252,244,21,245,32,245,55,245,73,245,86,245,103,245,112,245,115,245,113,245,111,245,81,245,47,245,7,245,216,
244,153,244,80,244,250,243,149,243,53,243,188,242,46,242,182,241,64,241,196,240,98,240,15,240,186,239,114,239,67,239,15,239,243,238,238,238,242,238,0,239,47,239,107,239,174,239,15,240,129,240,5,241,175,241,104,242,63,243,41,244,44,245,48,246,86,247,138,
248,188,249,3,251,86,252,162,253,238,254,81,0,167,1,254,2,75,4,156,5,223,6,37,8,70,9,103,10,122,11,130,12,109,13,70,14,13,15,171,15,63,16,194,16,35,17,107,17,156,17,184,17,185,17,170,17,141,17,90,17,25,17,186,16,77,16,208,15,63,15,139,14,220,13,31,13,
78,12,116,11,142,10,158,9,182,8,206,7,230,6,0,6,54,5,108,4,178,3,20,3,124,2,255,1,152,1,81,1,34,1,23,1,39,1,86,1,169,1,23,2,155,2,66,3,251,3,182,4,149,5,124,6,99,7,92,8,90,9,85,10,80,11,80,12,65,13,43,14,31,15,240,15,194,16,139,17,73,18,236,18,148,19,
26,20,134,20,244,20,58,21,107,21,135,21,139,21,92,21,37,21,212,20,78,20,195,19,24,19,75,18,94,17,112,16,83,15,44,14,228,12,132,11,6,10,123,8,195,6,6,5,58,3,78,1,104,255,115,253,123,251,124,249,136,247,144,245,152,243,185,241,219,239,255,237,54,236,116,
234,188,232,12,231,109,229,198,227,69,226,195,224,90,223,248,221,179,220,97,219,54,218,8,217,230,215,220,214,217,213,237,212,20,212,82,211,151,210,239,209,97,209,223,208,135,208,86,208,40,208,34,208,66,208,113,208,193,208,76,209,236,209,167,210,144,211,
151,212,196,213,20,215,124,216,255,217,176,219,105,221,62,223,70,225,96,227,156,229,245,231,113,234,255,236,179,239,135,242,88,245,96,248,89,251,136,254,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,
119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,
121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,
102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,
48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,
104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Halfway_Attack_Loud_wav = (const char*) temp_binary_data_5;

//================== Attack Initial Loud.wav ==================
static const unsigned char temp_binary_data_6[] =
{ 82,73,70,70,154,14,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,226,12,0,0,162,1,159,2,99,3,83,4,255,4,209,5,132,6,75,7,13,8,202,8,139,9,43,10,230,10,139,11,52,12,199,12,89,13,215,13,67,14,176,14,15,15,
112,15,208,15,38,16,103,16,178,16,250,16,67,17,150,17,211,17,7,18,49,18,69,18,77,18,86,18,91,18,71,18,48,18,18,18,238,17,187,17,143,17,88,17,14,17,199,16,106,16,14,16,164,15,52,15,185,14,62,14,191,13,64,13,193,12,63,12,174,11,48,11,160,10,16,10,110,9,
228,8,71,8,190,7,60,7,186,6,45,6,172,5,46,5,183,4,61,4,217,3,94,3,236,2,121,2,12,2,154,1,46,1,186,0,75,0,230,255,141,255,54,255,225,254,153,254,63,254,249,253,174,253,118,253,56,253,15,253,228,252,184,252,144,252,106,252,74,252,50,252,45,252,22,252,11,
252,247,251,226,251,195,251,168,251,151,251,128,251,102,251,84,251,60,251,34,251,2,251,240,250,217,250,190,250,160,250,155,250,130,250,120,250,108,250,102,250,87,250,82,250,76,250,62,250,59,250,36,250,23,250,0,250,239,249,209,249,177,249,150,249,108,
249,59,249,11,249,229,248,187,248,161,248,126,248,98,248,62,248,26,248,255,247,240,247,234,247,227,247,223,247,233,247,239,247,1,248,35,248,71,248,114,248,158,248,205,248,0,249,49,249,98,249,152,249,189,249,235,249,25,250,63,250,105,250,132,250,173,250,
203,250,237,250,5,251,41,251,63,251,93,251,118,251,148,251,161,251,171,251,192,251,207,251,220,251,234,251,246,251,5,252,16,252,38,252,50,252,68,252,78,252,74,252,89,252,105,252,126,252,146,252,173,252,209,252,235,252,15,253,69,253,129,253,190,253,254,
253,74,254,151,254,215,254,56,255,145,255,236,255,59,0,182,0,23,1,133,1,228,1,90,2,179,2,18,3,105,3,203,3,32,4,127,4,204,4,42,5,119,5,188,5,254,5,69,6,126,6,194,6,13,7,75,7,126,7,183,7,238,7,27,8,87,8,172,8,246,8,77,9,151,9,236,9,37,10,106,10,152,10,
204,10,238,10,9,11,16,11,28,11,38,11,55,11,67,11,78,11,88,11,92,11,97,11,93,11,91,11,73,11,48,11,5,11,237,10,196,10,160,10,111,10,63,10,254,9,194,9,141,9,72,9,3,9,181,8,104,8,7,8,169,7,68,7,222,6,114,6,250,5,136,5,9,5,132,4,10,4,147,3,29,3,164,2,43,2,
168,1,26,1,155,0,9,0,135,255,13,255,141,254,250,253,121,253,234,252,76,252,165,251,6,251,75,250,136,249,200,248,250,247,25,247,55,246,76,245,97,244,113,243,112,242,100,241,87,240,61,239,32,238,247,236,214,235,174,234,162,233,149,232,155,231,170,230,212,
229,248,228,70,228,164,227,10,227,128,226,251,225,127,225,25,225,203,224,147,224,117,224,114,224,123,224,145,224,215,224,50,225,164,225,41,226,196,226,108,227,36,228,212,228,157,229,111,230,87,231,67,232,71,233,91,234,118,235,160,236,207,237,255,238,
65,240,131,241,180,242,249,243,58,245,117,246,178,247,249,248,51,250,107,251,185,252,11,254,93,255,202,0,41,2,132,3,236,4,99,6,213,7,76,9,204,10,71,12,190,13,45,15,143,16,235,17,69,19,152,20,225,21,39,23,91,24,135,25,150,26,156,27,138,28,110,29,40,30,
218,30,106,31,231,31,77,32,165,32,221,32,246,32,6,33,1,33,224,32,185,32,135,32,60,32,230,31,121,31,8,31,143,30,9,30,128,29,241,28,97,28,214,27,66,27,193,26,32,26,124,25,215,24,60,24,169,23,12,23,129,22,238,21,82,21,182,20,26,20,129,19,233,18,78,18,166,
17,7,17,92,16,173,15,238,14,72,14,158,13,226,12,49,12,116,11,167,10,206,9,253,8,17,8,36,7,57,6,80,5,100,4,123,3,137,2,155,1,179,0,205,255,235,254,14,254,58,253,94,252,156,251,207,250,10,250,72,249,156,248,251,247,106,247,234,246,102,246,253,245,156,245,
53,245,237,244,170,244,116,244,68,244,42,244,16,244,12,244,16,244,35,244,41,244,65,244,82,244,104,244,140,244,169,244,185,244,195,244,221,244,241,244,25,245,49,245,88,245,116,245,143,245,173,245,208,245,239,245,254,245,14,246,22,246,19,246,14,246,21,
246,17,246,16,246,254,245,237,245,211,245,188,245,166,245,136,245,112,245,83,245,57,245,37,245,251,244,208,244,159,244,113,244,64,244,12,244,217,243,173,243,124,243,89,243,51,243,17,243,243,242,226,242,206,242,190,242,189,242,193,242,201,242,214,242,
244,242,16,243,55,243,95,243,151,243,202,243,4,244,73,244,145,244,232,244,67,245,168,245,32,246,165,246,36,247,166,247,46,248,167,248,43,249,168,249,63,250,205,250,95,251,234,251,121,252,20,253,158,253,49,254,203,254,78,255,213,255,90,0,243,0,122,1,7,
2,136,2,4,3,137,3,16,4,160,4,48,5,189,5,58,6,166,6,18,7,113,7,191,7,245,7,44,8,93,8,132,8,165,8,204,8,226,8,254,8,11,9,31,9,37,9,42,9,55,9,65,9,77,9,92,9,112,9,142,9,167,9,208,9,7,10,61,10,116,10,170,10,247,10,54,11,129,11,210,11,41,12,125,12,227,12,
72,13,161,13,238,13,64,14,115,14,163,14,187,14,222,14,224,14,207,14,163,14,110,14,60,14,246,13,167,13,85,13,3,13,178,12,95,12,12,12,182,11,87,11,250,10,164,10,89,10,4,10,171,9,85,9,249,8,150,8,70,8,234,7,160,7,74,7,6,7,191,6,118,6,29,6,197,5,111,5,13,
5,173,4,71,4,207,3,69,3,183,2,26,2,126,1,223,0,63,0,151,255,227,254,34,254,91,253,143,252,178,251,211,250,244,249,12,249,25,248,29,247,23,246,21,245,26,244,13,243,248,241,220,240,187,239,144,238,120,237,91,236,49,235,12,234,223,232,171,231,139,230,104,
229,70,228,36,227,17,226,5,225,2,224,21,223,41,222,75,221,138,220,207,219,40,219,156,218,19,218,158,217,67,217,1,217,206,216,189,216,201,216,230,216,34,217,115,217,234,217,119,218,36,219,229,219,204,220,217,221,242,222,43,224,127,225,216,226,90,228,250,
229,153,231,88,233,44,235,15,237,0,239,19,241,42,243,69,245,130,247,172,249,225,251,16,254,76,0,106,2,145,4,167,6,191,8,207,10,204,12,183,14,157,16,125,18,73,20,1,22,174,23,65,25,200,26,51,28,143,29,211,30,8,32,36,33,46,34,40,35,1,36,192,36,113,37,11,
38,166,38,45,39,155,39,251,39,80,40,135,40,185,40,220,40,254,40,4,41,27,41,18,41,237,40,179,40,104,40,11,40,167,39,29,39,118,38,194,37,254,36,28,36,44,35,64,34,64,33,51,32,22,31,245,29,218,28,186,27,151,26,105,25,67,24,15,23,232,21,184,20,135,19,101,
18,75,17,34,16,6,15,246,13,224,12,200,11,175,10,164,9,149,8,161,7,172,6,176,5,190,4,207,3,229,2,0,2,44,1,87,0,154,255,215,254,35,254,102,253,175,252,239,251,63,251,155,250,242,249,72,249,156,248,229,247,61,247,154,246,244,245,97,245,223,244,100,244,238,
243,130,243,28,243,170,242,79,242,241,241,147,241,67,241,253,240,175,240,112,240,61,240,26,240,15,240,7,240,24,240,47,240,90,240,134,240,195,240,10,241,73,241,140,241,206,241,23,242,72,242,147,242,189,242,234,242,0,243,28,243,33,243,36,243,25,243,9,243,
245,242,222,242,199,242,174,242,139,242,96,242,52,242,11,242,227,241,196,241,178,241,153,241,143,241,139,241,145,241,142,241,164,241,180,241,200,241,215,241,251,241,23,242,46,242,75,242,113,242,163,242,202,242,3,243,61,243,137,243,209,243,22,244,86,244,
163,244,239,244,59,245,146,245,242,245,79,246,175,246,11,247,104,247,205,247,56,248,173,248,27,249,135,249,239,249,78,250,178,250,5,251,92,251,179,251,9,252,97,252,190,252,23,253,103,253,187,253,17,254,105,254,191,254,23,255,121,255,210,255,48,0,127,
0,223,0,50,1,162,1,12,2,117,2,205,2,32,3,138,3,222,3,60,4,153,4,241,4,72,5,161,5,253,5,84,6,177,6,15,7,127,7,240,7,97,8,188,8,38,9,129,9,228,9,55,10,160,10,0,11,88,11,163,11,248,11,83,12,177,12,18,13,115,13,220,13,58,14,140,14,223,14,58,15,142,15,206,
15,7,16,56,16,89,16,104,16,120,16,126,16,122,16,106,16,85,16,51,16,13,16,213,15,148,15,87,15,26,15,205,14,128,14,54,14,227,13,140,13,33,13,201,12,101,12,16,12,171,11,68,11,225,10,104,10,222,9,92,9,228,8,100,8,228,7,95,7,219,6,72,6,176,5,38,5,150,4,13,
4,139,3,7,3,133,2,246,1,122,1,245,0,119,0,244,255,99,255,216,254,88,254,201,253,84,253,214,252,108,252,254,251,154,251,50,251,199,250,98,250,231,249,120,249,251,248,120,248,215,247,47,247,112,246,160,245,208,244,214,243,201,242,169,241,125,240,56,239,
239,237,154,236,43,235,184,233,62,232,181,230,43,229,171,227,34,226,162,224,49,223,201,221,114,220,67,219,29,218,22,217,63,216,112,215,200,214,67,214,223,213,144,213,126,213,121,213,153,213,241,213,117,214,13,215,215,215,219,216,230,217,31,219,121,220,
232,221,115,223,23,225,196,226,137,228,97,230,75,232,57,234,76,236,89,238,112,240,150,242,185,244,220,246,16,249,43,251,56,253,77,255,84,1,67,3,69,5,65,7,37,9,11,11,248,12,209,14,168,16,122,18,70,20,18,22,216,23,128,25,51,27,207,28,87,30,214,31,88,33,
196,34,37,36,134,37,205,38,4,40,31,41,35,42,5,43,220,43,130,44,35,45,152,45,240,45,19,46,30,46,250,45,193,45,107,45,239,44,84,44,177,43,231,42,17,42,45,41,52,40,50,39,46,38,38,37,6,36,241,34,219,33,179,32,159,31,143,30,128,29,105,28,86,27,45,26,19,25,
9,24,227,22,189,21,151,20,115,19,57,18,21,17,228,15,183,14,139,13,92,12,45,11,255,9,218,8,157,7,115,6,61,5,4,4,204,2,149,1,87,0,29,255,220,253,145,252,86,251,17,250,230,248,197,247,202,246,204,245,229,244,29,244,104,243,208,242,58,242,171,241,49,241,
186,240,87,240,3,240,188,239,115,239,61,239,24,239,245,238,227,238,217,238,204,238,204,238,208,238,208,238,217,238,217,238,222,238,221,238,242,238,4,239,45,239,99,239,152,239,197,239,1,240,58,240,114,240,187,240,9,241,77,241,157,241,231,241,48,242,127,
242,209,242,35,243,110,243,187,243,1,244,74,244,144,244,206,244,13,245,64,245,102,245,133,245,158,245,163,245,150,245,130,245,72,245,16,245,212,244,142,244,67,244,235,243,159,243,85,243,28,243,237,242,207,242,207,242,200,242,218,242,237,242,25,243,68,
243,141,243,219,243,62,244,185,244,73,245,246,245,173,246,120,247,64,248,14,249,218,249,164,250,99,251,19,252,185,252,81,253,205,253,67,254,179,254,35,255,130,255,224,255,44,0,127,0,192,0,6,1,61,1,110,1,137,1,161,1,167,1,173,1,163,1,142,1,106,1,70,1,
49,1,31,1,17,1,7,1,240,0,193,0,155,0,121,0,78,0,28,0,245,255,187,255,127,255,71,255,31,255,240,254,227,254,195,254,161,254,148,254,151,254,164,254,189,254,237,254,37,255,116,255,229,255,124,0,43,1,247,1,204,2,186,3,179,4,177,5,173,6,165,7,157,8,129,9,
93,10,47,11,9,12,197,12,115,13,21,14,190,14,86,15,228,15,111,16,226,16,79,17,161,17,235,17,36,18,77,18,102,18,106,18,126,18,142,18,149,18,137,18,121,18,95,18,63,18,27,18,229,17,168,17,81,17,243,16,134,16,20,16,161,15,26,15,150,14,17,14,145,13,12,13,124,
12,220,11,55,11,136,10,219,9,40,9,119,8,189,7,14,7,92,6,164,5,1,5,71,4,155,3,229,2,53,2,138,1,227,0,47,0,127,255,199,254,17,254,90,253,182,252,3,252,85,251,148,250,209,249,1,249,60,248,104,247,149,246,183,245,229,244,247,243,17,243,39,242,39,241,31,240,
0,239,212,237,155,236,77,235,238,233,122,232,243,230,90,229,204,227,59,226,165,224,15,223,151,221,30,220,174,218,84,217,243,215,158,214,107,213,85,212,86,211,120,210,181,209,15,209,162,208,91,208,65,208,99,208,183,208,39,209,214,209,157,210,150,211,186,
212,17,214,128,215,38,217,243,218,207,220,220,222,14,225,64,227,142,229,6,232,135,234,15,237,191,239,129,242,70,245,43,248,12,251,242,253,209,0,184,3,140,6,110,9,48,12,212,14,97,17,213,19,35,22,88,24,122,26,107,28,81,30,18,32,181,33,69,35,179,36,2,38,
64,39,98,40,117,41,98,42,66,43,242,43,155,44,42,45,150,45,236,45,52,46,99,46,133,46,169,46,177,46,161,46,136,46,82,46,11,46,182,45,73,45,196,44,44,44,117,43,162,42,191,41,202,40,190,39,178,38,151,37,108,36,55,35,5,34,192,32,125,31,49,30,230,28,156,27,
84,26,24,25,239,23,220,22,198,21,203,20,220,19,235,18,8,18,56,17,105,16,147,15,170,14,194,13,196,12,198,11,173,10,157,9,109,8,77,7,12,6,215,4,137,3,67,2,250,0,177,255,106,254,29,253,215,251,140,250,76,249,9,248,203,246,129,245,74,244,23,243,0,242,233,
240,238,239,4,239,53,238,123,237,229,236,101,236,248,235,176,235,109,235,59,235,35,235,26,235,12,235,14,235,29,235,61,235,111,235,169,235,240,235,80,236,193,236,42,237,170,237,35,238,153,238,13,239,142,239,13,240,146,240,25,241,159,241,26,242,174,242,
35,243,174,243,43,244,165,244,12,245,105,245,190,245,245,245,49,246,79,246,104,246,118,246,121,246,111,246,85,246,57,246,0,246,192,245,105,245,6,245,149,244,42,244,178,243,55,243,173,242,22,242,137,241,251,240,132,240,20,240,177,239,67,239,223,238,137,
238,58,238,249,237,215,237,194,237,210,237,253,237,65,238,154,238,22,239,175,239,91,240,36,241,255,241,234,242,221,243,231,244,19,246,67,247,139,248,226,249,49,251,127,252,204,253,20,255,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,
104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,
112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,
48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,
105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,
101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Attack_Initial_Loud_wav = (const char*) temp_binary_data_6;

//================== Decay Loud.wav ==================
static const unsigned char temp_binary_data_7[] =
{ 82,73,70,70,6,13,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,78,11,0,0,240,0,151,2,63,4,211,5,93,7,235,8,103,10,192,11,36,13,99,14,149,15,162,16,169,17,114,18,55,19,218,19,89,20,198,20,32,21,79,21,99,21,
79,21,42,21,217,20,114,20,225,19,58,19,120,18,155,17,157,16,151,15,131,14,94,13,59,12,18,11,240,9,208,8,181,7,150,6,150,5,170,4,213,3,28,3,143,2,36,2,225,1,199,1,218,1,13,2,102,2,220,2,114,3,26,4,215,4,162,5,105,6,73,7,57,8,47,9,23,10,14,11,252,11,237,
12,222,13,214,14,194,15,159,16,121,17,68,18,243,18,155,19,42,20,174,20,24,21,108,21,179,21,224,21,253,21,255,21,235,21,208,21,145,21,57,21,210,20,72,20,158,19,211,18,250,17,235,16,202,15,146,14,52,13,188,11,65,10,172,8,253,6,89,5,157,3,217,1,15,0,72,
254,112,252,159,250,222,248,21,247,96,245,174,243,251,241,92,240,211,238,81,237,219,235,111,234,17,233,192,231,115,230,29,229,201,227,111,226,7,225,161,223,57,222,185,220,71,219,209,217,91,216,226,214,122,213,18,212,194,210,137,209,61,208,2,207,232,205,
211,204,193,203,219,202,6,202,77,201,206,200,88,200,7,200,236,199,254,199,45,200,158,200,64,201,251,201,251,202,58,204,141,205,47,207,249,208,2,211,84,213,226,215,142,218,138,221,196,224,12,228,152,231,94,235,53,239,37,243,76,247,103,251,146,255,213,
3,26,8,87,12,171,16,213,20,230,24,241,28,209,32,147,36,54,40,161,43,219,46,233,49,199,52,77,55,204,57,247,59,219,61,146,63,9,65,46,66,31,67,217,67,70,68,132,68,142,68,85,68,248,67,114,67,168,66,202,65,208,64,162,63,84,62,241,60,116,59,225,57,85,56,151,
54,226,52,28,51,80,49,104,47,163,45,201,43,254,41,64,40,139,38,197,36,40,35,124,33,218,31,68,30,171,28,1,27,108,25,203,23,41,22,127,20,208,18,14,17,88,15,138,13,172,11,209,9,244,7,0,6,32,4,55,2,72,0,97,254,155,252,193,250,29,249,139,247,24,246,184,244,
127,243,77,242,57,241,84,240,122,239,191,238,11,238,106,237,225,236,110,236,245,235,136,235,45,235,212,234,118,234,39,234,217,233,131,233,60,233,244,232,187,232,143,232,106,232,73,232,65,232,57,232,56,232,62,232,69,232,81,232,105,232,141,232,171,232,
231,232,36,233,98,233,176,233,21,234,119,234,238,234,120,235,3,236,156,236,69,237,241,237,158,238,77,239,243,239,146,240,66,241,229,241,131,242,43,243,205,243,99,244,253,244,143,245,23,246,159,246,41,247,168,247,20,248,129,248,229,248,55,249,129,249,
190,249,241,249,17,250,45,250,51,250,51,250,25,250,237,249,163,249,78,249,235,248,123,248,245,247,86,247,179,246,3,246,70,245,151,244,233,243,63,243,141,242,235,241,74,241,164,240,20,240,132,239,253,238,121,238,9,238,148,237,63,237,2,237,220,236,201,
236,210,236,244,236,52,237,148,237,27,238,198,238,139,239,111,240,104,241,138,242,184,243,13,245,127,246,5,248,167,249,87,251,11,253,199,254,146,0,103,2,49,4,0,6,191,7,104,9,13,11,152,12,18,14,111,15,178,16,207,17,207,18,183,19,116,20,25,21,150,21,254,
21,65,22,108,22,116,22,89,22,30,22,179,21,36,21,127,20,174,19,190,18,187,17,143,16,84,15,2,14,172,12,67,11,236,9,164,8,92,7,34,6,5,5,243,3,245,2,21,2,89,1,192,0,88,0,20,0,248,255,254,255,60,0,155,0,39,1,207,1,146,2,114,3,100,4,105,5,126,6,161,7,203,8,
240,9,31,11,60,12,88,13,126,14,150,15,153,16,158,17,125,18,75,19,23,20,217,20,130,21,22,22,154,22,235,22,53,23,111,23,149,23,152,23,135,23,87,23,21,23,192,22,67,22,169,21,242,20,23,20,25,19,15,18,207,16,140,15,32,14,166,12,10,11,116,9,193,7,254,5,56,
4,97,2,134,0,178,254,217,252,0,251,43,249,92,247,134,245,209,243,30,242,104,240,195,238,59,237,169,235,53,234,194,232,91,231,245,229,160,228,45,227,199,225,95,224,221,222,103,221,245,219,112,218,240,216,130,215,6,214,135,212,29,211,183,209,93,208,22,
207,201,205,130,204,93,203,62,202,63,201,105,200,179,199,17,199,159,198,77,198,38,198,66,198,132,198,228,198,141,199,88,200,86,201,143,202,9,204,170,205,148,207,191,209,16,212,183,214,161,217,175,220,240,223,118,227,6,231,206,234,195,238,196,242,222,
246,31,251,77,255,132,3,198,7,8,12,47,16,112,20,138,24,134,28,127,32,76,36,239,39,124,43,196,46,213,49,191,52,111,55,207,57,8,60,246,61,147,63,1,65,52,66,13,67,194,67,67,68,114,68,119,68,76,68,226,67,77,67,152,66,167,65,147,64,106,63,9,62,146,60,23,59,
128,57,211,55,36,54,104,52,147,50,194,48,234,46,15,45,63,43,107,41,160,39,238,37,66,36,142,34,248,32,104,31,196,29,56,28,165,26,4,25,103,23,211,21,42,20,125,18,219,16,39,15,121,13,192,11,3,10,57,8,114,6,164,4,210,2,22,1,78,255,163,253,242,251,89,250,
208,248,103,247,9,246,200,244,157,243,135,242,136,241,173,240,221,239,32,239,109,238,215,237,59,237,187,236,57,236,197,235,104,235,255,234,153,234,67,234,242,233,152,233,77,233,13,233,204,232,163,232,136,232,105,232,87,232,70,232,52,232,40,232,46,232,
54,232,86,232,129,232,192,232,1,233,83,233,183,233,42,234,166,234,45,235,198,235,95,236,248,236,157,237,67,238,228,238,132,239,36,240,198,240,95,241,250,241,157,242,53,243,201,243,88,244,236,244,126,245,8,246,145,246,25,247,163,247,25,248,139,248,255,
248,106,249,198,249,33,250,95,250,155,250,187,250,221,250,224,250,210,250,171,250,102,250,14,250,162,249,15,249,120,248,209,247,11,247,74,246,117,245,168,244,211,243,12,243,75,242,133,241,212,240,23,240,104,239,196,238,46,238,156,237,39,237,187,236,99,
236,47,236,23,236,24,236,76,236,145,236,241,236,115,237,25,238,214,238,184,239,185,240,215,241,5,243,99,244,199,245,76,247,247,248,172,250,121,252,90,254,78,0,55,2,31,4,21,6,242,7,213,9,155,11,77,13,230,14,91,16,182,17,239,18,8,20,255,20,210,21,123,22,
249,22,89,23,144,23,164,23,149,23,93,23,252,22,125,22,213,21,247,20,251,19,229,18,184,17,96,16,1,15,140,13,23,12,152,10,28,9,162,7,50,6,209,4,129,3,78,2,36,1,32,0,57,255,117,254,217,253,113,253,51,253,30,253,61,253,140,253,9,254,163,254,104,255,84,0,
85,1,117,2,162,3,228,4,45,6,134,7,220,8,68,10,172,11,254,12,73,14,161,15,240,16,39,18,78,19,108,20,99,21,60,22,9,23,190,23,79,24,205,24,45,25,109,25,146,25,147,25,140,25,92,25,24,25,185,24,67,24,167,23,239,22,27,22,14,21,249,19,198,18,113,17,234,15,103,
14,187,12,253,10,52,9,102,7,130,5,171,3,194,1,200,255,225,253,245,251,6,250,30,248,73,246,104,244,155,242,226,240,30,239,119,237,235,235,97,234,232,232,119,231,255,229,149,228,61,227,205,225,110,224,5,223,144,221,15,220,166,218,47,217,187,215,86,214,
235,212,125,211,25,210,197,208,107,207,53,206,243,204,198,203,174,202,177,201,187,200,7,200,93,199,219,198,141,198,110,198,110,198,174,198,34,199,186,199,134,200,143,201,195,202,56,204,234,205,196,207,227,209,62,212,195,214,146,217,166,220,204,223,47,
227,189,230,106,234,54,238,59,242,71,246,103,250,169,254,212,2,15,7,90,11,149,15,190,19,226,23,230,27,194,31,153,35,64,39,178,42,10,46,33,49,251,51,166,54,27,57,66,59,58,61,252,62,107,64,167,65,172,66,99,67,240,67,55,68,67,68,26,68,192,67,42,67,118,66,
165,65,149,64,112,63,50,62,205,60,74,59,196,57,34,56,109,54,196,52,0,51,48,49,102,47,162,45,216,43,34,42,101,40,167,38,254,36,78,35,168,33,17,32,119,30,209,28,58,27,160,25,247,23,90,22,183,20,9,19,92,17,163,15,213,13,12,12,57,10,95,8,113,6,149,4,163,
2,192,0,226,254,14,253,72,251,157,249,2,248,132,246,34,245,219,243,173,242,152,241,151,240,180,239,240,238,57,238,140,237,251,236,115,236,0,236,163,235,80,235,252,234,183,234,111,234,60,234,10,234,207,233,157,233,117,233,69,233,22,233,241,232,213,232,
172,232,131,232,117,232,86,232,72,232,66,232,71,232,94,232,138,232,182,232,2,233,87,233,189,233,58,234,188,234,73,235,222,235,121,236,29,237,198,237,118,238,33,239,212,239,135,240,41,241,217,241,127,242,39,243,199,243,112,244,17,245,171,245,70,246,224,
246,99,247,237,247,114,248,236,248,98,249,211,249,64,250,153,250,233,250,26,251,78,251,108,251,113,251,100,251,65,251,11,251,170,250,72,250,199,249,50,249,143,248,232,247,56,247,128,246,191,245,251,244,54,244,101,243,159,242,214,241,29,241,96,240,170,
239,249,238,86,238,187,237,51,237,201,236,123,236,82,236,58,236,77,236,127,236,212,236,77,237,236,237,160,238,118,239,133,240,164,241,226,242,60,244,192,245,76,247,254,248,193,250,144,252,106,254,90,0,57,2,37,4,11,6,230,7,186,9,127,11,52,13,196,14,57,
16,147,17,195,18,213,19,195,20,143,21,42,22,168,22,1,23,50,23,62,23,39,23,238,22,144,22,2,22,81,21,118,20,121,19,92,18,35,17,207,15,108,14,11,13,142,11,19,10,162,8,59,7,212,5,115,4,51,3,245,1,211,0,211,255,219,254,14,254,88,253,224,252,125,252,88,252,
104,252,165,252,6,253,166,253,88,254,60,255,55,0,83,1,130,2,208,3,40,5,146,6,18,8,141,9,0,11,120,12,235,13,92,15,201,16,33,18,76,19,120,20,147,21,130,22,89,23,33,24,197,24,88,25,205,25,23,26,66,26,87,26,68,26,25,26,213,25,102,25,222,24,57,24,109,23,126,
22,123,21,75,20,249,18,151,17,17,16,116,14,201,12,253,10,45,9,79,7,97,5,89,3,109,1,114,255,110,253,123,251,139,249,148,247,168,245,205,243,244,241,39,240,114,238,200,236,32,235,147,233,255,231,136,230,24,229,170,227,69,226,215,224,95,223,237,221,127,
220,4,219,137,217,27,216,156,214,50,213,203,211,90,210,238,208,153,207,51,206,219,204,160,203,110,202,65,201,72,200,91,199,149,198,6,198,155,197,84,197,72,197,121,197,205,197,99,198,38,199,22,200,85,201,202,202,103,204,77,206,111,208,195,210,89,213,34,
216,19,219,63,222,170,225,37,229,202,232,149,236,119,240,114,244,140,248,169,252,207,0,21,5,75,9,125,13,177,17,202,21,208,25,205,29,149,33,60,37,200,40,27,44,49,47,42,50,239,52,95,55,171,57,191,59,135,61,32,63,139,64,170,65,150,66,81,67,194,67,254,67,
15,68,226,67,141,67,252,66,70,66,95,65,107,64,51,63,242,61,146,60,20,59,119,57,219,55,26,54,75,52,134,50,189,48,224,46,9,45,36,43,71,41,114,39,159,37,193,35,251,33,50,32,107,30,167,28,244,26,48,25,117,23,181,21,244,19,57,18,107,16,172,14,229,12,39,11,
93,9,149,7,200,5,250,3,44,2,110,0,165,254,241,252,74,251,174,249,38,248,184,246,91,245,24,244,249,242,237,241,246,240,24,240,70,239,146,238,243,237,107,237,239,236,152,236,63,236,251,235,194,235,145,235,101,235,74,235,50,235,19,235,248,234,222,234,185,
234,160,234,128,234,89,234,45,234,26,234,240,233,218,233,189,233,175,233,165,233,171,233,196,233,227,233,30,234,89,234,174,234,16,235,130,235,254,235,142,236,26,237,173,237,73,238,222,238,118,239,20,240,171,240,70,241,223,241,124,242,20,243,173,243,65,
244,231,244,112,245,5,246,139,246,17,247,137,247,250,247,116,248,220,248,54,249,149,249,230,249,32,250,83,250,133,250,149,250,161,250,166,250,148,250,94,250,41,250,202,249,98,249,228,248,90,248,179,247,15,247,99,246,161,245,227,244,41,244,103,243,159,
242,226,241,11,241,65,240,126,239,195,238,12,238,104,237,211,236,69,236,222,235,149,235,114,235,110,235,157,235,223,235,79,236,219,236,141,237,93,238,78,239,100,240,150,241,245,242,100,244,251,245,177,247,119,249,101,251,75,253,87,255,76,73,83,84,190,
0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,
110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,
70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,
104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,
49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,
46,55,54,46,49,48,48,0,0,0 };

const char* Decay_Loud_wav = (const char*) temp_binary_data_7;

//================== Halfway Release Loud.wav ==================
static const unsigned char temp_binary_data_8[] =
{ 82,73,70,70,234,7,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,50,6,0,0,253,1,183,4,112,7,103,10,77,13,78,16,73,19,76,22,67,25,51,28,53,31,13,34,227,36,148,39,36,42,126,44,184,46,186,48,131,50,42,52,142,
53,174,54,160,55,68,56,156,56,198,56,172,56,72,56,174,55,219,54,180,53,103,52,237,50,69,49,124,47,155,45,137,43,100,41,48,39,221,36,120,34,25,32,162,29,30,27,178,24,50,22,179,19,64,17,219,14,111,12,25,10,192,7,70,5,201,2,69,0,152,253,255,250,70,248,129,
245,160,242,207,239,221,236,255,233,33,231,71,228,124,225,211,222,68,220,239,217,217,215,9,214,123,212,121,211,223,210,180,210,23,211,237,211,30,213,200,214,213,216,50,219,228,221,218,224,249,227,59,231,167,234,17,238,132,241,224,244,12,248,17,251,230,
253,119,0,165,2,133,4,227,5,214,6,106,7,173,7,153,7,68,7,155,6,163,5,114,4,0,3,91,1,155,255,193,253,203,251,200,249,210,247,226,245,254,243,45,242,116,240,203,238,90,237,10,236,239,234,3,234,72,233,192,232,115,232,112,232,153,232,4,233,163,233,113,234,
117,235,155,236,237,237,85,239,231,240,114,242,13,244,150,245,17,247,108,248,196,249,4,251,34,252,45,253,19,254,213,254,118,255,8,0,124,0,223,0,41,1,88,1,114,1,148,1,175,1,207,1,254,1,35,2,74,2,145,2,223,2,56,3,152,3,237,3,42,4,100,4,137,4,151,4,164,
4,169,4,169,4,167,4,182,4,169,4,166,4,180,4,182,4,203,4,227,4,242,4,248,4,235,4,197,4,128,4,61,4,218,3,92,3,217,2,57,2,132,1,188,0,221,255,220,254,226,253,223,252,203,251,191,250,166,249,108,248,50,247,234,245,149,244,85,243,29,242,238,240,186,239,183,
238,180,237,233,236,74,236,233,235,190,235,236,235,55,236,211,236,181,237,207,238,15,240,157,241,73,243,32,245,46,247,106,249,178,251,37,254,165,0,40,3,196,5,107,8,3,11,172,13,76,16,212,18,83,21,210,23,40,26,106,28,134,30,133,32,89,34,31,36,171,37,19,
39,89,40,114,41,94,42,74,43,14,44,165,44,51,45,143,45,179,45,171,45,115,45,245,44,93,44,155,43,171,42,150,41,123,40,44,39,219,37,127,36,15,35,145,33,11,32,105,30,175,28,250,26,39,25,57,23,71,21,58,19,25,17,230,14,150,12,8,10,109,7,162,4,176,1,179,254,
182,251,153,248,131,245,128,242,124,239,142,236,192,233,6,231,120,228,40,226,15,224,55,222,194,220,150,219,218,218,152,218,215,218,140,219,185,220,67,222,21,224,57,226,164,228,59,231,16,234,255,236,250,239,245,242,247,245,212,248,150,251,32,254,109,0,
87,2,254,3,52,5,11,6,129,6,149,6,58,6,139,5,150,4,99,3,4,2,102,0,150,254,147,252,113,250,64,248,253,245,186,243,117,241,62,239,37,237,30,235,50,233,103,231,177,229,37,228,197,226,166,225,189,224,15,224,167,223,120,223,126,223,210,223,96,224,47,225,67,
226,148,227,20,229,191,230,139,232,113,234,114,236,148,238,181,240,216,242,250,244,250,246,234,248,197,250,135,252,42,254,162,255,252,0,58,2,117,3,133,4,123,5,71,6,251,6,141,7,42,8,184,8,36,9,118,9,172,9,183,9,184,9,172,9,133,9,92,9,29,9,193,8,81,8,194,
7,19,7,64,6,119,5,167,4,211,3,12,3,31,2,62,1,111,0,170,255,253,254,102,254,218,253,71,253,204,252,88,252,231,251,138,251,62,251,227,250,143,250,69,250,227,249,161,249,83,249,1,249,178,248,114,248,39,248,220,247,158,247,75,247,246,246,160,246,53,246,205,
245,116,245,21,245,211,244,193,244,189,244,229,244,44,245,164,245,61,246,28,247,51,248,131,249,38,251,234,252,201,254,213,0,9,3,71,5,182,7,45,10,157,12,4,15,103,17,171,19,247,21,54,24,79,26,99,28,94,30,46,32,208,33,94,35,162,36,200,37,212,38,174,39,107,
40,22,41,159,41,10,42,104,42,180,42,216,42,2,43,23,43,16,43,4,43,218,42,125,42,13,42,106,41,140,40,156,39,148,38,90,37,13,36,184,34,62,33,189,31,52,30,150,28,220,26,38,25,84,23,122,21,155,19,161,17,128,15,100,13,32,11,204,8,103,6,239,3,76,1,156,254,214,
251,241,248,32,246,80,243,134,240,205,237,55,235,170,232,72,230,21,228,11,226,54,224,191,222,129,221,156,220,15,220,219,219,255,219,135,220,104,221,139,222,243,223,129,225,57,227,13,229,250,230,248,232,250,234,241,236,208,238,143,240,38,242,137,243,191,
244,181,245,117,246,241,246,67,247,86,247,63,247,11,247,179,246,59,246,170,245,253,244,42,244,61,243,83,242,118,241,165,240,227,239,56,239,155,238,28,238,172,237,78,237,4,237,194,236,130,236,68,236,16,236,241,235,228,235,4,236,54,236,150,236,19,237,183,
237,120,238,103,239,123,240,165,241,246,242,100,244,213,245,84,247,210,248,74,250,199,251,63,253,147,254,201,255,219,0,206,1,167,2,120,3,28,4,144,4,210,4,210,4,168,4,102,4,20,4,156,3,1,3,69,2,110,1,163,0,228,255,42,255,133,254,215,253,59,253,152,252,
11,252,126,251,249,250,116,250,246,249,144,249,62,249,233,248,150,248,61,248,237,247,150,247,99,247,53,247,26,247,15,247,12,247,43,247,83,247,144,247,213,247,63,248,176,248,35,249,158,249,14,250,121,250,235,250,99,251,237,251,121,252,12,253,137,253,11,
254,130,254,246,254,78,255,177,255,0,0,78,0,158,0,234,0,43,1,105,1,169,1,230,1,61,2,150,2,4,3,135,3,49,4,237,4,215,5,229,6,20,8,118,9,240,10,134,12,44,14,224,15,133,17,44,19,214,20,100,22,245,23,110,25,220,26,24,28,77,29,87,30,88,31,51,32,1,33,165,33,
63,34,163,34,238,34,42,35,77,35,82,35,94,35,74,35,52,35,29,35,9,35,233,34,199,34,156,34,87,34,254,33,153,33,6,33,97,32,159,31,188,30,206,29,215,28,186,27,152,26,108,25,51,24,231,22,165,21,75,20,224,18,106,17,233,15,71,14,166,12,237,10,25,9,37,7,38,5,
242,2,182,0,88,254,233,251,125,249,19,247,155,244,55,242,226,239,154,237,105,235,115,233,130,231,215,229,81,228,6,227,243,225,51,225,178,224,112,224,129,224,209,224,85,225,31,226,25,227,63,228,146,229,13,231,164,232,74,234,242,235,127,237,235,238,47,
240,57,241,4,242,148,242,211,242,220,242,166,242,54,242,168,241,11,241,93,240,168,239,241,238,49,238,128,237,225,236,97,236,245,235,174,235,128,235,122,235,171,235,5,236,142,236,54,237,249,237,212,238,195,239,196,240,212,241,223,242,233,243,239,244,249,
245,247,246,238,247,220,248,181,249,142,250,97,251,53,252,248,252,189,253,117,254,39,255,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,
107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,
63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,
0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,
121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,
50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Halfway_Release_Loud_wav = (const char*) temp_binary_data_8;

//================== Release Initial Loud.wav ==================
static const unsigned char temp_binary_data_9[] =
{ 82,73,70,70,146,4,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,218,2,0,0,171,1,250,4,138,8,49,12,10,16,0,20,1,24,254,27,251,31,197,35,93,39,158,42,119,45,200,47,180,49,7,51,202,51,4,52,172,51,176,50,75,
49,86,47,241,44,42,42,13,39,182,35,91,32,254,28,158,25,84,22,54,19,50,16,104,13,228,10,132,8,92,6,109,4,163,2,4,1,164,255,68,254,243,252,187,251,124,250,43,249,213,247,83,246,166,244,222,242,238,240,183,238,120,236,22,234,168,231,54,229,189,226,64,224,
220,221,175,219,131,217,150,215,187,213,10,212,121,210,64,209,56,208,140,207,54,207,43,207,104,207,248,207,178,208,164,209,213,210,19,212,110,213,217,214,77,216,196,217,69,219,195,220,58,222,189,223,57,225,159,226,19,228,122,229,211,230,29,232,86,233,
127,234,165,235,217,236,2,238,73,239,130,240,197,241,6,243,106,244,205,245,75,247,217,248,104,250,10,252,183,253,114,255,54,1,254,2,203,4,148,6,87,8,6,10,180,11,113,13,43,15,220,16,148,18,68,20,244,21,176,23,100,25,28,27,193,28,56,30,115,31,135,32,101,
33,11,34,130,34,196,34,216,34,186,34,102,34,212,33,27,33,57,32,60,31,47,30,16,29,223,27,170,26,124,25,80,24,59,23,47,22,71,21,120,20,197,19,30,19,155,18,34,18,208,17,169,17,174,17,207,17,24,18,126,18,8,19,178,19,120,20,73,21,46,22,39,23,31,24,33,25,35,
26,9,27,210,27,111,28,189,28,192,28,116,28,187,27,163,26,37,25,90,23,44,21,186,18,241,15,219,12,161,9,50,6,182,2,48,255,189,251,99,248,49,245,61,242,135,239,61,237,78,235,205,233,189,232,28,232,240,231,53,232,239,232,15,234,162,235,153,237,232,239,127,
242,88,245,63,248,95,251,114,254,119,1,54,4,189,6,194,8,105,10,122,11,10,12,242,11,91,11,31,10,108,8,78,6,220,3,22,1,34,254,12,251,255,247,13,245,90,242,214,239,163,237,178,235,14,234,208,232,247,231,135,231,129,231,217,231,160,232,179,233,35,235,195,
236,158,238,136,240,136,242,124,244,82,246,239,247,87,249,123,250,81,251,235,251,60,252,81,252,41,252,214,251,76,251,165,250,213,249,240,248,237,247,236,246,224,245,220,244,250,243,50,243,148,242,32,242,223,241,200,241,240,241,61,242,168,242,31,243,178,
243,73,244,233,244,150,245,47,246,186,246,42,247,141,247,193,247,211,247,176,247,75,247,171,246,212,245,199,244,165,243,116,242,69,241,28,240,28,239,65,238,163,237,66,237,55,237,104,237,238,237,201,238,239,239,122,241,114,243,183,245,81,248,49,251,83,
254,174,1,53,5,205,8,101,12,225,15,55,19,70,22,28,25,150,27,186,29,131,31,233,32,220,33,100,34,116,34,10,34,44,33,208,31,245,29,163,27,245,24,246,21,188,18,96,15,192,11,8,8,64,4,104,0,162,252,253,248,127,245,51,242,52,239,122,236,5,234,5,232,108,230,
36,229,69,228,180,227,78,227,57,227,87,227,169,227,47,228,236,228,182,229,159,230,186,231,226,232,50,234,163,235,35,237,175,238,130,240,133,242,201,244,107,247,33,250,41,253,128,255,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,
111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,
115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,
32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,
105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,
101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Release_Initial_Loud_wav = (const char*) temp_binary_data_9;

//================== Sustain Loud.wav ==================
static const unsigned char temp_binary_data_10[] =
{ 82,73,70,70,110,11,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,182,9,0,0,190,0,125,2,58,4,230,5,148,7,45,9,193,10,62,12,166,13,250,14,62,16,86,17,95,18,75,19,23,20,198,20,110,21,231,21,77,22,148,22,197,
22,190,22,178,22,131,22,50,22,198,21,56,21,131,20,186,19,217,18,221,17,214,16,194,15,166,14,131,13,97,12,59,11,31,10,4,9,244,7,236,6,251,5,29,5,76,4,162,3,30,3,170,2,85,2,38,2,27,2,39,2,95,2,178,2,23,3,148,3,34,4,187,4,83,5,9,6,167,6,90,7,250,7,163,8,
57,9,214,9,98,10,228,10,108,11,240,11,97,12,230,12,78,13,173,13,18,14,100,14,164,14,204,14,226,14,221,14,206,14,180,14,121,14,41,14,210,13,89,13,206,12,48,12,126,11,177,10,190,9,165,8,123,7,59,6,219,4,110,3,234,1,89,0,176,254,20,253,104,251,193,249,22,
248,94,246,180,244,23,243,130,241,249,239,141,238,36,237,201,235,133,234,66,233,13,232,230,230,188,229,129,228,99,227,55,226,253,224,212,223,167,222,115,221,82,220,58,219,6,218,238,216,206,215,172,214,158,213,154,212,151,211,178,210,224,209,16,209,106,
208,229,207,114,207,34,207,11,207,235,206,255,206,80,207,191,207,82,208,30,209,9,210,37,211,143,212,21,214,205,215,197,217,240,219,60,222,213,224,157,227,128,230,156,233,233,236,69,240,222,243,151,247,73,251,36,255,19,3,244,6,238,10,242,14,225,18,219,
22,211,26,167,30,95,34,14,38,127,41,191,44,231,47,199,50,103,53,229,55,17,58,15,60,218,61,117,63,192,64,238,65,222,66,133,67,4,68,57,68,56,68,254,67,132,67,204,66,249,65,248,64,181,63,80,62,208,60,29,59,89,57,128,55,131,53,143,51,136,49,118,47,80,45,
67,43,31,41,10,39,236,36,217,34,186,32,181,30,157,28,162,26,174,24,197,22,212,20,6,19,54,17,105,15,160,13,231,11,29,10,106,8,179,6,250,4,66,3,143,1,202,255,21,254,82,252,149,250,221,248,57,247,153,245,24,244,169,242,75,241,16,240,4,239,14,238,44,237,
101,236,191,235,43,235,175,234,70,234,253,233,215,233,180,233,176,233,168,233,181,233,198,233,235,233,248,233,14,234,25,234,39,234,34,234,38,234,33,234,22,234,13,234,248,233,238,233,232,233,235,233,230,233,247,233,1,234,27,234,62,234,100,234,154,234,
220,234,55,235,146,235,8,236,128,236,249,236,123,237,18,238,171,238,81,239,7,240,185,240,114,241,46,242,233,242,169,243,99,244,27,245,195,245,110,246,5,247,141,247,23,248,153,248,7,249,120,249,219,249,53,250,142,250,226,250,32,251,84,251,140,251,179,
251,228,251,29,252,65,252,95,252,109,252,112,252,97,252,67,252,20,252,210,251,131,251,28,251,156,250,15,250,125,249,227,248,63,248,154,247,223,246,50,246,117,245,175,244,244,243,63,243,137,242,220,241,57,241,161,240,15,240,159,239,75,239,22,239,5,239,
255,238,15,239,73,239,148,239,2,240,151,240,70,241,14,242,251,242,250,243,26,245,95,246,207,247,80,249,246,250,168,252,103,254,59,0,30,2,244,3,210,5,161,7,101,9,20,11,184,12,44,14,148,15,229,16,23,18,42,19,38,20,246,20,159,21,50,22,170,22,240,22,46,23,
70,23,70,23,38,23,231,22,141,22,22,22,132,21,215,20,15,20,56,19,70,18,61,17,55,16,23,15,1,14,228,12,191,11,155,10,114,9,85,8,60,7,56,6,79,5,121,4,193,3,36,3,163,2,63,2,11,2,221,1,232,1,5,2,75,2,155,2,5,3,126,3,252,3,146,4,43,5,206,5,112,6,14,7,167,7,
80,8,234,8,132,9,22,10,169,10,50,11,174,11,38,12,149,12,248,12,95,13,167,13,222,13,3,14,15,14,5,14,247,13,204,13,141,13,59,13,209,12,84,12,202,11,44,11,109,10,153,9,168,8,162,7,121,6,84,5,252,3,165,2,53,1,189,255,55,254,173,252,28,251,129,249,241,247,
85,246,186,244,51,243,174,241,57,240,211,238,118,237,37,236,236,234,176,233,137,232,109,231,102,230,86,229,87,228,72,227,73,226,75,225,73,224,68,223,66,222,62,221,39,220,36,219,26,218,5,217,2,216,6,215,1,214,18,213,49,212,95,211,167,210,16,210,143,209,
45,209,238,208,196,208,203,208,2,209,91,209,221,209,150,210,103,211,112,212,175,213,22,215,166,216,131,218,131,220,184,222,38,225,190,227,126,230,118,233,161,236,227,239,85,243,221,246,126,250,65,254,22,2,227,5,196,9,175,13,139,17,99,21,66,25,243,28,
166,32,56,36,184,39,11,43,70,46,65,49,15,52,175,54,16,57,57,59,58,61,247,62,112,64,189,65,198,66,128,67,16,68,84,68,81,68,23,68,166,67,247,66,33,66,41,65,243,63,162,62,44,61,141,59,211,57,6,56,33,54,49,52,57,50,47,48,25,46,23,44,251,41,238,39,221,37,
201,35,184,33,173,31,161,29,158,27,174,25,193,23,215,21,250,19,30,18,70,16,127,14,192,12,0,11,69,9,134,7,198,5,3,4,65,2,125,0,184,254,242,252,22,251,76,249,141,247,209,245,42,244,145,242,25,241,179,239,114,238,55,237,37,236,48,235,77,234,138,233,236,
232,108,232,4,232,186,231,140,231,116,231,130,231,149,231,204,231,5,232,72,232,131,232,188,232,254,232,46,233,106,233,137,233,180,233,213,233,249,233,14,234,41,234,69,234,99,234,138,234,198,234,248,234,46,235,99,235,150,235,208,235,25,236,88,236,171,
236,248,236,69,237,159,237,16,238,121,238,245,238,139,239,29,240,195,240,115,241,44,242,224,242,153,243,67,244,227,244,131,245,17,246,155,246,26,247,142,247,236,247,89,248,184,248,16,249,102,249,178,249,233,249,35,250,101,250,155,250,221,250,38,251,106,
251,157,251,221,251,1,252,44,252,71,252,64,252,59,252,25,252,225,251,143,251,45,251,191,250,59,250,183,249,34,249,114,248,207,247,37,247,117,246,209,245,44,245,126,244,216,243,57,243,163,242,31,242,170,241,67,241,243,240,191,240,147,240,133,240,144,240,
182,240,245,240,100,241,222,241,104,242,35,243,239,243,220,244,245,245,28,247,105,248,210,249,94,251,248,252,172,254,107,0,43,2,251,3,203,5,137,7,61,9,217,10,106,12,225,13,78,15,160,16,202,17,221,18,187,19,127,20,38,21,174,21,20,22,100,22,154,22,167,
22,163,22,117,22,50,22,208,21,89,21,183,20,253,19,43,19,52,18,53,17,33,16,17,15,238,13,185,12,140,11,96,10,72,9,50,8,49,7,73,6,114,5,175,4,251,3,108,3,0,3,176,2,141,2,122,2,137,2,182,2,251,2,84,3,186,3,57,4,193,4,86,5,249,5,149,6,59,7,218,7,124,8,26,
9,180,9,71,10,219,10,113,11,241,11,108,12,245,12,117,13,235,13,95,14,185,14,251,14,50,15,82,15,92,15,89,15,47,15,248,14,157,14,57,14,179,13,31,13,112,12,153,11,169,10,164,9,127,8,68,7,250,5,129,4,5,3,118,1,221,255,53,254,141,252,217,250,25,249,96,247,
170,245,251,243,97,242,203,240,83,239,244,237,147,236,73,235,31,234,252,232,239,231,235,230,249,229,3,229,27,228,48,227,71,226,100,225,124,224,126,223,131,222,136,221,124,220,124,219,121,218,112,217,110,216,105,215,100,214,103,213,129,212,149,211,202,
210,14,210,104,209,209,208,120,208,30,208,4,208,13,208,70,208,154,208,46,209,225,209,196,210,234,211,51,213,171,214,110,216,95,218,134,220,237,222,135,225,77,228,85,231,144,234,235,237,129,241,43,245,227,248,184,252,180,0,157,4,158,8,159,12,156,16,152,
20,149,24,118,28,63,32,255,35,136,39,235,42,50,46,46,49,248,51,153,54,249,56,31,59,35,61,225,62,91,64,182,65,206,66,151,67,45,68,129,68,143,68,111,68,18,68,110,67,164,66,172,65,106,64,17,63,140,61,225,59,30,58,86,56,89,54,88,52,85,50,59,48,41,46,23,44,
249,41,223,39,203,37,183,35,146,33,140,31,123,29,114,27,115,25,130,23,152,21,194,19,247,17,33,16,109,14,181,12,6,11,102,9,194,7,14,6,99,4,187,2,255,0,74,255,150,253,211,251,17,250,93,248,153,246,239,244,77,243,196,241,83,240,252,238,183,237,154,236,169,
235,221,234,47,234,163,233,50,233,216,232,172,232,150,232,151,232,181,232,216,232,3,233,56,233,104,233,162,233,230,233,34,234,82,234,111,234,138,234,154,234,177,234,192,234,193,234,210,234,222,234,230,234,1,235,24,235,45,235,78,235,105,235,142,235,170,
235,206,235,247,235,42,236,100,236,165,236,246,236,95,237,196,237,58,238,204,238,98,239,18,240,200,240,130,241,67,242,2,243,190,243,111,244,27,245,196,245,95,246,244,246,112,247,230,247,79,248,163,248,252,248,83,249,154,249,224,249,26,250,83,250,143,
250,212,250,18,251,77,251,146,251,205,251,10,252,66,252,108,252,123,252,122,252,94,252,32,252,214,251,112,251,5,251,127,250,246,249,99,249,187,248,16,248,105,247,194,246,28,246,115,245,195,244,30,244,115,243,210,242,62,242,183,241,56,241,205,240,117,
240,46,240,0,240,233,239,253,239,46,240,128,240,231,240,124,241,30,242,242,242,225,243,245,244,39,246,120,247,236,248,116,250,27,252,207,253,157,255,109,1,67,3,32,5,241,6,172,8,103,10,10,12,154,13,8,15,96,16,147,17,166,18,149,19,98,20,8,21,151,21,6,22,
95,22,149,22,173,22,169,22,143,22,86,22,7,22,152,21,16,21,106,20,160,19,191,18,194,17,186,16,154,15,108,14,54,13,7,12,216,10,186,9,166,8,161,7,179,6,214,5,19,5,109,4,238,3,134,3,56,3,28,3,10,3,29,3,74,3,142,3,223,3,79,4,201,4,77,5,213,5,111,6,255,6,154,
7,55,8,204,8,102,9,1,10,142,10,18,11,141,11,255,11,107,12,228,12,66,13,165,13,243,13,56,14,103,14,146,14,162,14,157,14,125,14,73,14,255,13,168,13,68,13,198,12,43,12,118,11,168,10,204,9,218,8,211,7,178,6,114,5,26,4,174,2,52,1,159,255,5,254,95,252,174,
250,255,248,88,247,170,245,18,244,126,242,246,240,125,239,31,238,196,236,116,235,75,234,49,233,38,232,50,231,65,230,93,229,131,228,164,227,201,226,241,225,15,225,21,224,39,223,47,222,31,221,35,220,40,219,34,218,37,217,39,216,35,215,52,214,78,213,113,
212,168,211,251,210,66,210,181,209,78,209,236,208,183,208,178,208,210,208,14,209,156,209,56,210,13,211,41,212,107,213,224,214,152,216,148,218,164,220,12,223,148,225,86,228,108,231,151,234,251,237,104,241,51,245,192,248,192,252,76,73,83,84,190,0,0,0,73,
78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,
108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,
0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,
32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,
69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,
49,48,48,0,0,0 };

const char* Sustain_Loud_wav = (const char*) temp_binary_data_10;

//================== Halfway Attack Quiet.wav ==================
static const unsigned char temp_binary_data_11[] =
{ 82,73,70,70,70,9,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,142,7,0,0,49,0,72,1,109,2,127,3,164,4,176,5,194,6,187,7,186,8,161,9,135,10,86,11,29,12,205,12,113,13,5,14,140,14,11,15,114,15,205,15,25,16,84,
16,137,16,179,16,204,16,222,16,224,16,220,16,209,16,190,16,159,16,127,16,83,16,38,16,244,15,188,15,133,15,72,15,7,15,198,14,127,14,59,14,238,13,162,13,82,13,3,13,168,12,80,12,245,11,158,11,61,11,224,10,120,10,25,10,179,9,78,9,233,8,128,8,34,8,183,7,89,
7,238,6,147,6,42,6,202,5,100,5,7,5,161,4,67,4,220,3,127,3,24,3,188,2,91,2,247,1,151,1,55,1,210,0,111,0,18,0,175,255,76,255,228,254,131,254,26,254,185,253,72,253,224,252,109,252,4,252,149,251,37,251,188,250,79,250,235,249,124,249,33,249,183,248,98,248,
7,248,185,247,110,247,42,247,238,246,182,246,132,246,98,246,59,246,40,246,20,246,8,246,7,246,8,246,16,246,30,246,56,246,88,246,123,246,173,246,222,246,29,247,96,247,168,247,246,247,69,248,161,248,242,248,85,249,174,249,12,250,109,250,204,250,47,251,138,
251,237,251,68,252,164,252,0,253,86,253,173,253,253,253,74,254,147,254,220,254,27,255,78,255,130,255,162,255,192,255,220,255,221,255,220,255,203,255,174,255,135,255,89,255,24,255,207,254,119,254,30,254,178,253,67,253,205,252,70,252,192,251,45,251,151,
250,1,250,109,249,206,248,57,248,161,247,11,247,131,246,252,245,123,245,255,244,142,244,46,244,200,243,139,243,65,243,28,243,247,242,231,242,226,242,240,242,12,243,50,243,111,243,186,243,15,244,124,244,241,244,112,245,6,246,162,246,78,247,1,248,196,248,
140,249,93,250,69,251,31,252,20,253,2,254,0,255,247,255,0,1,249,1,6,3,2,4,8,5,250,5,252,6,225,7,209,8,177,9,139,10,84,11,20,12,204,12,114,13,13,14,154,14,26,15,144,15,247,15,85,16,166,16,234,16,31,17,85,17,119,17,153,17,168,17,186,17,185,17,190,17,177,
17,165,17,138,17,111,17,72,17,26,17,231,16,172,16,104,16,36,16,212,15,122,15,37,15,188,14,89,14,224,13,115,13,244,12,122,12,241,11,107,11,224,10,84,10,193,9,46,9,159,8,9,8,115,7,222,6,75,6,180,5,36,5,139,4,252,3,109,3,223,2,84,2,199,1,71,1,196,0,75,0,
207,255,93,255,241,254,128,254,29,254,185,253,91,253,0,253,169,252,85,252,255,251,182,251,101,251,29,251,215,250,148,250,79,250,17,250,209,249,153,249,95,249,41,249,243,248,189,248,142,248,87,248,42,248,252,247,206,247,168,247,127,247,94,247,55,247,32,
247,0,247,238,246,219,246,208,246,195,246,200,246,197,246,211,246,231,246,254,246,37,247,88,247,137,247,205,247,10,248,92,248,170,248,4,249,97,249,188,249,39,250,144,250,248,250,98,251,208,251,57,252,171,252,20,253,130,253,236,253,81,254,175,254,13,255,
100,255,179,255,251,255,63,0,118,0,165,0,204,0,225,0,238,0,243,0,227,0,207,0,167,0,118,0,52,0,233,255,148,255,38,255,188,254,56,254,174,253,34,253,133,252,226,251,58,251,142,250,208,249,25,249,97,248,160,247,234,246,52,246,125,245,205,244,37,244,137,
243,243,242,113,242,244,241,131,241,44,241,218,240,159,240,126,240,97,240,92,240,105,240,142,240,195,240,17,241,125,241,239,241,127,242,37,243,221,243,175,244,150,245,125,246,136,247,148,248,173,249,216,250,3,252,58,253,108,254,181,255,241,0,48,2,119,
3,171,4,231,5,24,7,67,8,95,9,115,10,121,11,112,12,89,13,51,14,248,14,174,15,88,16,229,16,107,17,223,17,58,18,147,18,213,18,11,19,52,19,87,19,102,19,109,19,102,19,88,19,63,19,29,19,239,18,183,18,119,18,43,18,219,17,127,17,43,17,183,16,89,16,216,15,107,
15,228,14,102,14,220,13,78,13,197,12,43,12,158,11,7,11,111,10,221,9,71,9,180,8,45,8,162,7,29,7,155,6,29,6,168,5,47,5,201,4,90,4,251,3,154,3,65,3,231,2,146,2,67,2,235,1,165,1,75,1,0,1,173,0,89,0,8,0,182,255,97,255,15,255,184,254,99,254,9,254,177,253,90,
253,251,252,163,252,70,252,240,251,151,251,63,251,231,250,146,250,55,250,225,249,138,249,54,249,226,248,151,248,67,248,250,247,173,247,106,247,40,247,236,246,179,246,127,246,85,246,43,246,11,246,242,245,221,245,213,245,209,245,218,245,232,245,255,245,
40,246,83,246,149,246,214,246,36,247,123,247,217,247,60,248,161,248,18,249,131,249,244,249,106,250,227,250,90,251,217,251,80,252,196,252,61,253,176,253,30,254,131,254,231,254,59,255,138,255,215,255,18,0,69,0,115,0,141,0,160,0,166,0,157,0,129,0,95,0,47,
0,232,255,157,255,57,255,207,254,86,254,211,253,67,253,172,252,9,252,93,251,170,250,251,249,65,249,138,248,207,247,23,247,97,246,181,245,4,245,92,244,195,243,48,243,162,242,48,242,189,241,95,241,18,241,210,240,170,240,146,240,146,240,155,240,190,240,
244,240,61,241,160,241,24,242,155,242,57,243,234,243,170,244,128,245,102,246,82,247,77,248,95,249,110,250,150,251,188,252,240,253,28,255,85,0,139,1,187,2,246,3,30,5,66,6,94,7,112,8,112,9,108,10,86,11,43,12,248,12,180,13,91,14,248,14,121,15,241,15,81,
16,180,16,239,16,54,17,90,17,133,17,155,17,174,17,180,17,177,17,171,17,152,17,133,17,103,17,69,17,29,17,245,16,195,16,144,16,85,16,24,16,212,15,145,15,74,15,252,14,172,14,81,14,249,13,150,13,56,13,206,12,99,12,248,11,135,11,24,11,164,10,56,10,196,9,88,
9,223,8,118,8,1,8,152,7,42,7,195,6,94,6,245,5,149,5,53,5,211,4,119,4,27,4,192,3,102,3,5,3,167,2,75,2,234,1,148,1,43,1,208,0,107,0,8,0,166,255,65,255,217,254,115,254,9,254,163,253,56,253,208,252,97,252,248,251,130,251,29,251,175,250,66,250,215,249,106,
249,254,248,160,248,58,248,226,247,140,247,53,247,235,246,165,246,100,246,44,246,252,245,211,245,163,245,142,245,109,245,98,245,82,245,87,245,86,245,103,245,123,245,153,245,190,245,238,245,35,246,94,246,165,246,240,246,58,247,151,247,236,247,71,248,168,
248,12,249,111,249,213,249,68,250,162,250,23,251,122,251,230,251,83,252,187,252,27,253,119,253,215,253,34,254,116,254,187,254,254,254,47,255,89,255,120,255,139,255,151,255,151,255,135,255,107,255,68,255,14,255,210,254,137,254,48,254,218,253,109,253,1,
253,136,252,14,252,128,251,251,250,104,250,216,249,65,249,176,248,27,248,134,247,243,246,102,246,216,245,85,245,213,244,93,244,247,243,151,243,73,243,9,243,211,242,168,242,157,242,146,242,164,242,193,242,247,242,58,243,150,243,252,243,119,244,8,245,165,
245,86,246,18,247,229,247,182,248,158,249,144,250,136,251,136,252,146,253,154,254,168,255,186,0,195,1,206,2,217,3,220,4,218,5,211,6,196,7,166,8,137,9,96,10,42,11,241,11,168,12,83,13,248,13,138,14,22,15,151,15,9,16,114,16,203,16,37,17,103,17,166,17,214,
17,254,17,29,18,52,18,62,18,63,18,62,18,44,18,31,18,254,17,222,17,169,17,122,17,53,17,247,16,166,16,88,16,246,15,159,15,55,15,208,14,96,14,234,13,111,13,248,12,122,12,250,11,129,11,255,10,128,10,252,9,128,9,252,8,123,8,246,7,117,7,244,6,120,6,238,5,119,
5,246,4,123,4,8,4,139,3,28,3,165,2,53,2,198,1,86,1,240,0,131,0,29,0,187,255,83,255,248,254,147,254,56,254,214,253,123,253,28,253,189,252,101,252,11,252,176,251,86,251,249,250,158,250,66,250,227,249,128,249,32,249,190,248,92,248,251,247,154,247,58,247,
216,246,129,246,30,246,200,245,113,245,26,245,207,244,135,244,73,244,17,244,231,243,188,243,165,243,156,243,150,243,164,243,184,243,220,243,16,244,79,244,155,244,243,244,85,245,190,245,50,246,176,246,49,247,186,247,74,248,215,248,114,249,6,250,168,250,
59,251,225,251,119,252,17,253,168,253,61,254,193,254,69,255,205,255,5,0,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,
82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,
89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,
0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,
98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,
49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Halfway_Attack_Quiet_wav = (const char*) temp_binary_data_11;

//================== Attack Initial Quiet.wav ==================
static const unsigned char temp_binary_data_12[] =
{ 82,73,70,70,164,11,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,236,9,0,0,49,0,116,0,185,0,10,1,81,1,168,1,254,1,87,2,183,2,16,3,117,3,207,3,54,4,140,4,234,4,60,5,140,5,205,5,12,6,60,6,113,6,148,6,186,6,
205,6,225,6,231,6,233,6,227,6,223,6,207,6,188,6,165,6,128,6,96,6,54,6,2,6,206,5,154,5,94,5,33,5,227,4,164,4,101,4,35,4,233,3,168,3,110,3,51,3,248,2,193,2,135,2,88,2,33,2,246,1,205,1,162,1,130,1,94,1,72,1,41,1,27,1,2,1,241,0,222,0,207,0,191,0,176,0,165,
0,148,0,136,0,126,0,108,0,95,0,82,0,59,0,38,0,18,0,247,255,228,255,197,255,177,255,150,255,125,255,98,255,70,255,48,255,16,255,242,254,205,254,172,254,136,254,105,254,71,254,31,254,1,254,211,253,181,253,140,253,114,253,71,253,43,253,16,253,241,252,221,
252,192,252,175,252,151,252,134,252,122,252,109,252,102,252,96,252,91,252,86,252,89,252,91,252,98,252,105,252,116,252,125,252,138,252,146,252,158,252,173,252,179,252,196,252,203,252,217,252,224,252,236,252,240,252,248,252,249,252,251,252,1,253,254,252,
255,252,252,252,255,252,247,252,247,252,241,252,235,252,224,252,216,252,199,252,180,252,157,252,130,252,111,252,79,252,60,252,33,252,10,252,250,251,226,251,206,251,190,251,163,251,141,251,115,251,94,251,71,251,49,251,31,251,14,251,3,251,252,250,244,250,
242,250,241,250,241,250,247,250,2,251,12,251,27,251,46,251,62,251,88,251,104,251,140,251,159,251,194,251,221,251,254,251,37,252,66,252,110,252,143,252,191,252,231,252,27,253,75,253,132,253,191,253,2,254,63,254,140,254,209,254,31,255,113,255,192,255,27,
0,112,0,215,0,49,1,165,1,11,2,135,2,245,2,119,3,229,3,103,4,224,4,97,5,216,5,91,6,214,6,81,7,205,7,66,8,175,8,33,9,126,9,225,9,45,10,125,10,184,10,246,10,35,11,70,11,99,11,120,11,124,11,130,11,116,11,103,11,67,11,37,11,237,10,182,10,114,10,40,10,212,
9,127,9,34,9,187,8,90,8,239,7,137,7,29,7,188,6,80,6,240,5,135,5,40,5,195,4,108,4,15,4,191,3,106,3,27,3,206,2,132,2,65,2,0,2,199,1,132,1,79,1,15,1,215,0,157,0,110,0,57,0,2,0,211,255,153,255,108,255,58,255,12,255,218,254,173,254,125,254,86,254,41,254,4,
254,217,253,178,253,146,253,111,253,82,253,56,253,26,253,5,253,232,252,211,252,189,252,168,252,145,252,133,252,111,252,100,252,83,252,70,252,60,252,54,252,56,252,58,252,65,252,77,252,90,252,106,252,122,252,138,252,154,252,177,252,188,252,209,252,223,
252,241,252,255,252,12,253,33,253,40,253,60,253,72,253,83,253,99,253,102,253,116,253,122,253,127,253,130,253,130,253,131,253,128,253,122,253,113,253,100,253,81,253,72,253,53,253,35,253,25,253,3,253,249,252,236,252,225,252,214,252,204,252,194,252,185,
252,171,252,162,252,143,252,130,252,112,252,100,252,84,252,67,252,52,252,30,252,10,252,247,251,221,251,197,251,168,251,139,251,103,251,71,251,32,251,249,250,204,250,167,250,123,250,85,250,45,250,11,250,227,249,203,249,175,249,153,249,137,249,124,249,
120,249,117,249,121,249,128,249,138,249,157,249,176,249,195,249,229,249,253,249,34,250,77,250,118,250,177,250,230,250,40,251,106,251,182,251,10,252,99,252,188,252,34,253,132,253,236,253,95,254,209,254,81,255,203,255,81,0,213,0,96,1,239,1,122,2,16,3,157,
3,51,4,195,4,85,5,228,5,115,6,254,6,134,7,15,8,137,8,9,9,115,9,224,9,61,10,145,10,227,10,35,11,98,11,143,11,182,11,207,11,230,11,230,11,229,11,221,11,200,11,174,11,137,11,94,11,42,11,243,10,175,10,113,10,27,10,216,9,119,9,42,9,201,8,115,8,23,8,187,7,
100,7,13,7,182,6,105,6,18,6,202,5,120,5,47,5,229,4,157,4,85,4,21,4,201,3,145,3,80,3,25,3,219,2,170,2,107,2,60,2,2,2,203,1,148,1,87,1,31,1,226,0,167,0,102,0,42,0,240,255,177,255,116,255,51,255,242,254,183,254,121,254,59,254,2,254,195,253,145,253,75,253,
26,253,223,252,169,252,118,252,73,252,19,252,237,251,193,251,159,251,128,251,104,251,79,251,61,251,48,251,36,251,30,251,30,251,30,251,36,251,52,251,61,251,88,251,105,251,133,251,158,251,191,251,218,251,253,251,35,252,71,252,103,252,144,252,167,252,203,
252,226,252,0,253,20,253,48,253,69,253,92,253,113,253,132,253,150,253,164,253,178,253,186,253,196,253,208,253,210,253,221,253,222,253,230,253,229,253,234,253,236,253,236,253,239,253,235,253,230,253,227,253,215,253,210,253,194,253,179,253,159,253,141,
253,118,253,91,253,65,253,30,253,247,252,212,252,167,252,127,252,82,252,34,252,236,251,189,251,133,251,77,251,26,251,229,250,178,250,131,250,83,250,30,250,248,249,211,249,174,249,149,249,125,249,111,249,88,249,89,249,75,249,80,249,85,249,91,249,109,249,
124,249,157,249,179,249,220,249,1,250,46,250,102,250,161,250,225,250,40,251,118,251,197,251,27,252,125,252,215,252,67,253,162,253,21,254,131,254,250,254,114,255,234,255,108,0,233,0,109,1,245,1,122,2,7,3,141,3,22,4,155,4,25,5,152,5,6,6,124,6,226,6,75,
7,166,7,3,8,79,8,160,8,225,8,32,9,87,9,143,9,183,9,225,9,6,10,34,10,64,10,80,10,96,10,101,10,106,10,94,10,88,10,75,10,52,10,30,10,254,9,220,9,179,9,138,9,92,9,44,9,253,8,201,8,149,8,93,8,39,8,233,7,179,7,110,7,54,7,239,6,187,6,119,6,65,6,255,5,188,5,
134,5,66,5,4,5,196,4,126,4,58,4,250,3,175,3,107,3,27,3,208,2,129,2,46,2,229,1,142,1,68,1,243,0,163,0,75,0,2,0,170,255,98,255,7,255,190,254,103,254,30,254,200,253,124,253,38,253,217,252,140,252,64,252,249,251,180,251,116,251,64,251,11,251,227,250,190,
250,160,250,136,250,118,250,110,250,102,250,108,250,117,250,129,250,155,250,176,250,214,250,251,250,38,251,85,251,139,251,189,251,245,251,45,252,104,252,160,252,221,252,24,253,85,253,137,253,191,253,239,253,34,254,76,254,123,254,161,254,192,254,225,254,
243,254,12,255,20,255,35,255,38,255,35,255,36,255,26,255,20,255,8,255,251,254,227,254,210,254,182,254,160,254,130,254,105,254,75,254,48,254,18,254,238,253,211,253,179,253,146,253,116,253,79,253,42,253,6,253,222,252,184,252,149,252,112,252,84,252,47,252,
29,252,253,251,227,251,201,251,172,251,143,251,121,251,101,251,71,251,52,251,22,251,0,251,233,250,205,250,180,250,161,250,127,250,106,250,70,250,47,250,8,250,237,249,203,249,174,249,147,249,126,249,105,249,92,249,90,249,89,249,102,249,115,249,140,249,
165,249,202,249,235,249,24,250,67,250,123,250,176,250,245,250,59,251,134,251,220,251,53,252,150,252,0,253,104,253,228,253,87,254,223,254,90,255,227,255,106,0,246,0,125,1,11,2,145,2,20,3,159,3,23,4,150,4,14,5,128,5,243,5,94,6,202,6,38,7,143,7,235,7,77,
8,161,8,249,8,66,9,143,9,206,9,18,10,72,10,132,10,172,10,218,10,251,10,26,11,45,11,69,11,74,11,89,11,82,11,80,11,63,11,48,11,24,11,243,10,212,10,159,10,109,10,44,10,234,9,159,9,79,9,253,8,167,8,77,8,250,7,156,7,67,7,234,6,134,6,50,6,210,5,119,5,26,5,
182,4,85,4,244,3,147,3,49,3,203,2,110,2,7,2,174,1,80,1,251,0,163,0,82,0,4,0,182,255,116,255,41,255,230,254,162,254,96,254,33,254,229,253,169,253,114,253,61,253,7,253,209,252,167,252,120,252,81,252,42,252,4,252,225,251,194,251,169,251,135,251,115,251,
91,251,77,251,65,251,62,251,60,251,60,251,71,251,77,251,98,251,116,251,139,251,168,251,196,251,237,251,13,252,60,252,99,252,144,252,188,252,235,252,22,253,74,253,111,253,162,253,197,253,243,253,25,254,66,254,105,254,139,254,171,254,200,254,225,254,249,
254,11,255,22,255,32,255,33,255,35,255,28,255,16,255,7,255,241,254,218,254,187,254,160,254,120,254,87,254,44,254,11,254,216,253,176,253,131,253,86,253,49,253,13,253,228,252,196,252,159,252,130,252,104,252,79,252,63,252,42,252,23,252,7,252,245,251,231,
251,219,251,196,251,187,251,161,251,142,251,121,251,95,251,65,251,36,251,0,251,218,250,180,250,137,250,94,250,49,250,7,250,207,249,167,249,115,249,75,249,36,249,254,248,219,248,197,248,172,248,160,248,138,248,134,248,124,248,124,248,131,248,139,248,162,
248,182,248,218,248,253,248,49,249,109,249,172,249,2,250,86,250,187,250,31,251,148,251,253,251,123,252,253,252,134,253,10,254,156,254,42,255,189,255,84,0,227,0,127,1,17,2,168,2,59,3,208,3,97,4,240,4,126,5,255,5,137,6,253,6,127,7,232,7,87,8,178,8,16,9,
90,9,168,9,235,9,37,10,97,10,137,10,187,10,226,10,6,11,38,11,61,11,81,11,92,11,104,11,104,11,96,11,90,11,65,11,48,11,17,11,239,10,199,10,156,10,109,10,62,10,12,10,216,9,158,9,104,9,43,9,235,8,176,8,109,8,41,8,232,7,155,7,84,7,8,7,188,6,108,6,23,6,192,
5,103,5,17,5,182,4,94,4,255,3,165,3,71,3,238,2,145,2,58,2,222,1,135,1,39,1,217,0,123,0,45,0,214,255,138,255,59,255,239,254,170,254,105,254,41,254,245,253,183,253,136,253,80,253,38,253,244,252,203,252,163,252,126,252,91,252,60,252,26,252,7,252,234,251,
222,251,202,251,195,251,180,251,178,251,174,251,171,251,178,251,187,251,194,251,211,251,228,251,249,251,14,252,37,252,62,252,92,252,125,252,154,252,188,252,217,252,246,252,17,253,49,253,82,253,110,253,148,253,169,253,199,253,221,253,243,253,12,254,20,
254,42,254,41,254,52,254,52,254,53,254,51,254,45,254,38,254,29,254,14,254,5,254,244,253,229,253,206,253,186,253,164,253,138,253,117,253,96,253,73,253,56,253,37,253,23,253,9,253,255,252,243,252,228,252,221,252,204,252,201,252,192,252,182,252,171,252,163,
252,147,252,136,252,121,252,105,252,78,252,52,252,15,252,234,251,191,251,145,251,92,251,43,251,247,250,189,250,131,250,73,250,11,250,210,249,148,249,87,249,29,249,235,248,178,248,137,248,90,248,53,248,23,248,0,248,236,247,225,247,223,247,236,247,242,
247,16,248,45,248,83,248,133,248,186,248,250,248,62,249,143,249,227,249,67,250,171,250,21,251,142,251,9,252,132,252,15,253,152,253,46,254,186,254,90,255,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,
119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,
121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,
102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,
48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,
104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Attack_Initial_Quiet_wav = (const char*) temp_binary_data_12;

//================== Decay Quiet.wav ==================
static const unsigned char temp_binary_data_13[] =
{ 82,73,70,70,52,10,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,124,8,0,0,30,0,81,0,117,0,152,0,174,0,179,0,176,0,162,0,132,0,90,0,43,0,228,255,150,255,53,255,203,254,81,254,210,253,71,253,174,252,13,252,
102,251,174,250,3,250,81,249,147,248,225,247,44,247,113,246,202,245,34,245,135,244,242,243,114,243,242,242,138,242,51,242,243,241,194,241,164,241,148,241,151,241,184,241,238,241,59,242,161,242,27,243,167,243,87,244,20,245,235,245,207,246,204,247,209,
248,238,249,28,251,72,252,142,253,212,254,37,0,111,1,207,2,26,4,114,5,188,6,253,7,49,9,90,10,118,11,127,12,128,13,106,14,61,15,1,16,180,16,73,17,210,17,69,18,156,18,237,18,34,19,73,19,89,19,99,19,87,19,65,19,32,19,230,18,179,18,105,18,26,18,189,17,99,
17,250,16,143,16,42,16,183,15,77,15,220,14,109,14,247,13,136,13,24,13,162,12,56,12,192,11,82,11,223,10,113,10,255,9,149,9,39,9,184,8,75,8,228,7,126,7,16,7,178,6,73,6,233,5,136,5,42,5,204,4,111,4,24,4,184,3,100,3,5,3,170,2,83,2,243,1,153,1,57,1,217,0,
114,0,20,0,173,255,73,255,223,254,121,254,12,254,157,253,52,253,193,252,90,252,239,251,131,251,23,251,172,250,69,250,228,249,129,249,36,249,201,248,116,248,32,248,209,247,130,247,64,247,252,246,196,246,142,246,91,246,53,246,16,246,242,245,220,245,199,
245,190,245,177,245,176,245,186,245,195,245,214,245,239,245,11,246,49,246,93,246,140,246,195,246,246,246,61,247,119,247,196,247,17,248,90,248,178,248,4,249,102,249,187,249,30,250,121,250,214,250,56,251,157,251,253,251,98,252,197,252,32,253,131,253,220,
253,56,254,136,254,221,254,24,255,100,255,147,255,198,255,230,255,11,0,20,0,34,0,26,0,18,0,247,255,218,255,165,255,112,255,43,255,217,254,125,254,22,254,164,253,37,253,162,252,22,252,127,251,236,250,76,250,174,249,16,249,117,248,208,247,55,247,157,246,
18,246,136,245,21,245,155,244,61,244,224,243,154,243,93,243,57,243,29,243,19,243,34,243,60,243,111,243,180,243,15,244,118,244,252,244,147,245,63,246,250,246,205,247,167,248,151,249,148,250,155,251,174,252,203,253,235,254,18,0,70,1,109,2,161,3,206,4,248,
5,18,7,45,8,56,9,51,10,42,11,10,12,229,12,170,13,99,14,255,14,149,15,19,16,131,16,226,16,51,17,106,17,157,17,188,17,205,17,215,17,210,17,188,17,167,17,125,17,88,17,29,17,236,16,168,16,98,16,27,16,206,15,121,15,37,15,206,14,116,14,29,14,188,13,91,13,248,
12,146,12,47,12,192,11,95,11,233,10,130,10,17,10,160,9,48,9,188,8,75,8,217,7,110,7,247,6,143,6,27,6,180,5,74,5,225,4,129,4,28,4,198,3,101,3,10,3,178,2,83,2,248,1,153,1,61,1,222,0,132,0,33,0,198,255,99,255,1,255,162,254,59,254,220,253,115,253,19,253,172,
252,75,252,232,251,133,251,33,251,198,250,98,250,9,250,169,249,85,249,255,248,173,248,94,248,17,248,203,247,138,247,68,247,13,247,215,246,168,246,131,246,96,246,67,246,49,246,31,246,21,246,18,246,15,246,24,246,37,246,54,246,81,246,112,246,148,246,189,
246,229,246,21,247,73,247,128,247,189,247,248,247,57,248,126,248,191,248,13,249,84,249,160,249,240,249,59,250,148,250,223,250,57,251,141,251,224,251,54,252,139,252,219,252,49,253,126,253,197,253,26,254,84,254,151,254,203,254,255,254,42,255,75,255,109,
255,118,255,132,255,136,255,121,255,110,255,76,255,42,255,244,254,188,254,117,254,34,254,202,253,100,253,241,252,127,252,5,252,126,251,1,251,114,250,232,249,88,249,208,248,69,248,195,247,66,247,196,246,81,246,233,245,136,245,49,245,234,244,166,244,122,
244,86,244,77,244,70,244,101,244,132,244,190,244,7,245,103,245,215,245,97,246,249,246,160,247,88,248,41,249,250,249,233,250,219,251,220,252,229,253,251,254,13,0,51,1,81,2,121,3,157,4,192,5,214,6,235,7,246,8,249,9,235,10,216,11,178,12,122,13,57,14,228,
14,121,15,6,16,119,16,222,16,51,17,123,17,176,17,215,17,240,17,249,17,245,17,234,17,205,17,170,17,121,17,69,17,253,16,186,16,98,16,16,16,179,15,83,15,234,14,134,14,23,14,172,13,56,13,207,12,89,12,232,11,117,11,2,11,144,10,28,10,171,9,50,9,198,8,84,8,
232,7,126,7,22,7,175,6,72,6,227,5,132,5,33,5,202,4,103,4,19,4,185,3,99,3,12,3,182,2,92,2,8,2,172,1,85,1,252,0,159,0,70,0,237,255,143,255,52,255,210,254,120,254,17,254,182,253,82,253,241,252,145,252,46,252,208,251,114,251,17,251,183,250,86,250,254,249,
163,249,81,249,251,248,163,248,86,248,4,248,187,247,117,247,45,247,241,246,181,246,130,246,84,246,46,246,12,246,241,245,218,245,203,245,193,245,195,245,199,245,209,245,227,245,251,245,24,246,60,246,102,246,147,246,201,246,3,247,62,247,128,247,200,247,
18,248,98,248,173,248,5,249,85,249,179,249,7,250,99,250,192,250,26,251,119,251,217,251,55,252,147,252,243,252,81,253,163,253,4,254,78,254,163,254,234,254,46,255,107,255,153,255,202,255,228,255,0,0,12,0,13,0,8,0,254,255,226,255,185,255,140,255,80,255,
4,255,188,254,86,254,240,253,125,253,4,253,121,252,250,251,101,251,217,250,61,250,176,249,15,249,132,248,241,247,104,247,227,246,101,246,237,245,132,245,38,245,204,244,138,244,77,244,41,244,10,244,9,244,19,244,48,244,103,244,172,244,9,245,123,245,255,
245,154,246,70,247,11,248,209,248,184,249,161,250,155,251,160,252,180,253,192,254,226,255,254,0,39,2,76,3,114,4,151,5,172,6,195,7,206,8,200,9,196,10,166,11,125,12,78,13,4,14,176,14,74,15,207,15,71,16,171,16,4,17,71,17,125,17,163,17,182,17,188,17,185,
17,167,17,138,17,96,17,47,17,239,16,180,16,94,16,22,16,189,15,100,15,6,15,165,14,65,14,224,13,115,13,22,13,170,12,71,12,223,11,117,11,18,11,165,10,64,10,215,9,111,9,12,9,163,8,72,8,222,7,128,7,32,7,192,6,103,6,4,6,168,5,74,5,245,4,153,4,62,4,236,3,138,
3,55,3,214,2,127,2,31,2,197,1,102,1,7,1,175,0,71,0,240,255,135,255,42,255,193,254,93,254,248,253,143,253,45,253,195,252,94,252,249,251,151,251,53,251,214,250,120,250,28,250,196,249,108,249,22,249,198,248,116,248,39,248,222,247,154,247,89,247,26,247,228,
246,179,246,137,246,100,246,68,246,47,246,26,246,16,246,10,246,13,246,17,246,32,246,45,246,69,246,100,246,134,246,176,246,222,246,19,247,74,247,136,247,199,247,15,248,83,248,163,248,232,248,59,249,141,249,220,249,46,250,134,250,213,250,42,251,127,251,
208,251,38,252,117,252,203,252,19,253,100,253,170,253,240,253,54,254,114,254,166,254,222,254,11,255,43,255,70,255,89,255,98,255,96,255,94,255,81,255,48,255,25,255,228,254,180,254,119,254,47,254,220,253,138,253,37,253,194,252,84,252,220,251,100,251,229,
250,107,250,230,249,101,249,229,248,101,248,233,247,118,247,1,247,155,246,60,246,219,245,143,245,72,245,13,245,221,244,198,244,171,244,180,244,192,244,233,244,23,245,101,245,188,245,42,246,169,246,67,247,222,247,157,248,91,249,49,250,20,251,2,252,247,
252,245,253,2,255,10,0,32,1,52,2,76,3,93,4,117,5,120,6,133,7,129,8,113,9,88,10,52,11,0,12,192,12,115,13,25,14,167,14,49,15,164,15,7,16,95,16,164,16,220,16,4,17,37,17,43,17,51,17,36,17,20,17,243,16,204,16,155,16,94,16,38,16,221,15,147,15,67,15,243,14,
155,14,65,14,226,13,128,13,32,13,192,12,86,12,244,11,136,11,31,11,182,10,71,10,226,9,115,9,13,9,159,8,55,8,204,7,99,7,252,6,142,6,40,6,186,5,82,5,232,4,132,4,31,4,185,3,95,3,252,2,159,2,62,2,225,1,135,1,43,1,206,0,120,0,26,0,199,255,103,255,15,255,181,
254,92,254,2,254,169,253,82,253,248,252,159,252,72,252,245,251,158,251,73,251,242,250,161,250,80,250,254,249,184,249,103,249,31,249,211,248,141,248,71,248,11,248,201,247,149,247,94,247,49,247,8,247,230,246,201,246,177,246,161,246,153,246,145,246,143,
246,154,246,154,246,177,246,193,246,219,246,254,246,34,247,74,247,126,247,172,247,236,247,35,248,106,248,172,248,240,248,60,249,131,249,205,249,29,250,109,250,185,250,14,251,92,251,174,251,252,251,81,252,154,252,234,252,56,253,129,253,201,253,21,254,
76,254,144,254,186,254,237,254,19,255,51,255,70,255,78,255,93,255,81,255,78,255,58,255,30,255,249,254,205,254,152,254,82,254,19,254,182,253,97,253,250,252,148,252,35,252,174,251,54,251,182,250,57,250,185,249,58,249,185,248,67,248,198,247,88,247,235,246,
135,246,34,246,214,245,131,245,69,245,19,245,232,244,206,244,195,244,204,244,215,244,7,245,51,245,129,245,219,245,72,246,203,246,95,247,3,248,174,248,122,249,71,250,37,251,12,252,2,253,250,253,4,255,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,
0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,
0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,
46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,
110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,
99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Decay_Quiet_wav = (const char*) temp_binary_data_13;

//================== Release Quiet.wav ==================
static const unsigned char temp_binary_data_14[] =
{ 82,73,70,70,178,7,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,250,5,0,0,95,0,144,1,191,2,210,3,230,4,213,5,203,6,150,7,97,8,21,9,192,9,84,10,226,10,93,11,205,11,47,12,133,12,204,12,18,13,68,13,122,13,154,
13,186,13,208,13,223,13,245,13,0,14,11,14,29,14,36,14,51,14,56,14,56,14,59,14,54,14,48,14,40,14,32,14,20,14,10,14,253,13,240,13,223,13,205,13,181,13,155,13,128,13,91,13,54,13,15,13,221,12,177,12,118,12,65,12,5,12,199,11,136,11,63,11,252,10,168,10,88,
10,255,9,164,9,62,9,219,8,108,8,245,7,130,7,5,7,130,6,3,6,118,5,233,4,92,4,199,3,50,3,153,2,1,2,100,1,202,0,47,0,145,255,241,254,90,254,185,253,35,253,134,252,233,251,78,251,177,250,22,250,121,249,232,248,74,248,195,247,45,247,173,246,26,246,159,245,
21,245,150,244,23,244,154,243,32,243,168,242,52,242,198,241,97,241,13,241,186,240,122,240,66,240,17,240,246,239,229,239,224,239,236,239,2,240,42,240,98,240,179,240,19,241,139,241,26,242,179,242,99,243,44,244,248,244,225,245,205,246,201,247,201,248,220,
249,239,250,15,252,54,253,93,254,130,255,175,0,215,1,249,2,25,4,43,5,44,6,35,7,6,8,206,8,137,9,43,10,176,10,25,11,117,11,167,11,196,11,196,11,161,11,90,11,255,10,124,10,222,9,42,9,83,8,103,7,104,6,87,5,43,4,249,2,179,1,97,0,5,255,172,253,68,252,230,250,
148,249,56,248,246,246,193,245,151,244,141,243,143,242,177,241,225,240,65,240,170,239,61,239,239,238,195,238,183,238,203,238,251,238,73,239,187,239,75,240,243,240,181,241,142,242,109,243,107,244,112,245,128,246,153,247,178,248,210,249,232,250,11,252,
28,253,50,254,58,255,62,0,40,1,31,2,241,2,196,3,124,4,51,5,205,5,100,6,228,6,92,7,200,7,43,8,126,8,215,8,27,9,104,9,158,9,217,9,2,10,49,10,81,10,114,10,136,10,162,10,181,10,206,10,226,10,252,10,19,11,45,11,60,11,84,11,95,11,114,11,126,11,141,11,156,11,
168,11,181,11,189,11,200,11,205,11,215,11,219,11,223,11,223,11,229,11,221,11,217,11,200,11,192,11,167,11,143,11,117,11,78,11,44,11,254,10,206,10,149,10,90,10,16,10,193,9,110,9,13,9,175,8,68,8,215,7,97,7,239,6,113,6,242,5,112,5,235,4,96,4,213,3,73,3,181,
2,39,2,149,1,6,1,122,0,228,255,90,255,196,254,65,254,173,253,37,253,151,252,11,252,122,251,236,250,92,250,209,249,71,249,189,248,46,248,162,247,22,247,134,246,253,245,111,245,220,244,88,244,198,243,71,243,202,242,83,242,227,241,131,241,42,241,227,240,
166,240,121,240,84,240,64,240,60,240,69,240,97,240,145,240,197,240,22,241,119,241,235,241,121,242,20,243,201,243,140,244,103,245,73,246,62,247,66,248,74,249,94,250,129,251,169,252,201,253,253,254,45,0,85,1,132,2,168,3,196,4,216,5,218,6,202,7,165,8,118,
9,31,10,184,10,61,11,153,11,228,11,15,12,27,12,14,12,227,11,152,11,44,11,173,10,10,10,74,9,123,8,146,7,148,6,136,5,102,4,51,3,253,1,192,0,113,255,47,254,231,252,160,251,103,250,54,249,15,248,1,247,2,246,26,245,66,244,143,243,240,242,108,242,17,242,199,
241,157,241,149,241,157,241,205,241,23,242,123,242,241,242,131,243,44,244,229,244,171,245,133,246,92,247,61,248,48,249,18,250,9,251,237,251,211,252,175,253,133,254,87,255,22,0,211,0,125,1,27,2,177,2,52,3,170,3,22,4,112,4,193,4,9,5,67,5,120,5,167,5,208,
5,243,5,15,6,47,6,62,6,83,6,92,6,107,6,115,6,128,6,137,6,154,6,170,6,186,6,200,6,220,6,240,6,4,7,26,7,40,7,74,7,85,7,125,7,145,7,183,7,206,7,239,7,10,8,42,8,71,8,99,8,129,8,164,8,193,8,219,8,241,8,10,9,28,9,48,9,65,9,82,9,89,9,100,9,93,9,95,9,84,9,76,
9,52,9,30,9,248,8,210,8,160,8,105,8,44,8,234,7,160,7,83,7,2,7,175,6,83,6,247,5,154,5,53,5,218,4,115,4,14,4,171,3,69,3,225,2,122,2,25,2,171,1,72,1,219,0,107,0,247,255,130,255,4,255,131,254,253,253,120,253,225,252,89,252,191,251,33,251,130,250,217,249,
45,249,128,248,208,247,26,247,109,246,183,245,11,245,95,244,192,243,38,243,163,242,35,242,183,241,81,241,12,241,199,240,169,240,144,240,139,240,158,240,203,240,6,241,94,241,205,241,70,242,226,242,141,243,78,244,32,245,0,246,247,246,232,247,252,248,5,
250,33,251,60,252,87,253,117,254,147,255,168,0,186,1,197,2,198,3,179,4,158,5,110,6,39,7,208,7,94,8,213,8,45,9,114,9,147,9,154,9,148,9,101,9,33,9,201,8,84,8,201,7,48,7,123,6,181,5,231,4,4,4,23,3,34,2,38,1,34,0,46,255,51,254,63,253,78,252,112,251,149,250,
205,249,22,249,110,248,222,247,104,247,2,247,183,246,133,246,103,246,97,246,116,246,165,246,226,246,62,247,167,247,36,248,183,248,88,249,4,250,185,250,123,251,50,252,255,252,189,253,129,254,61,255,240,255,166,0,67,1,229,1,105,2,239,2,97,3,196,3,28,4,
91,4,142,4,171,4,186,4,187,4,170,4,146,4,105,4,62,4,255,3,206,3,130,3,68,3,250,2,185,2,110,2,45,2,236,1,179,1,124,1,80,1,40,1,8,1,241,0,228,0,220,0,219,0,228,0,245,0,9,1,46,1,83,1,134,1,187,1,250,1,56,2,124,2,202,2,17,3,109,3,187,3,30,4,119,4,221,4,58,
5,164,5,254,5,105,6,192,6,32,7,121,7,208,7,45,8,120,8,201,8,16,9,78,9,136,9,182,9,216,9,245,9,3,10,10,10,3,10,243,9,219,9,182,9,139,9,88,9,30,9,222,8,150,8,76,8,2,8,170,7,82,7,245,6,148,6,39,6,193,5,74,5,222,4,99,4,236,3,106,3,240,2,96,2,218,1,61,1,173,
0,7,0,97,255,177,254,244,253,60,253,119,252,177,251,229,250,16,250,63,249,101,248,153,247,193,246,238,245,36,245,89,244,157,243,237,242,66,242,167,241,31,241,161,240,55,240,229,239,169,239,125,239,108,239,113,239,132,239,186,239,3,240,97,240,223,240,
107,241,25,242,202,242,161,243,122,244,109,245,109,246,119,247,142,248,172,249,205,250,238,251,24,253,52,254,73,255,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,
117,110,100,115,32,108,105,107,101,0,73,65,82,84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,
109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,
41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,
58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,
68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Release_Quiet_wav = (const char*) temp_binary_data_14;

//================== Sustain Quiet.wav ==================
static const unsigned char temp_binary_data_15[] =
{ 82,73,70,70,74,9,0,0,87,65,86,69,102,109,116,32,16,0,0,0,1,0,1,0,128,187,0,0,0,119,1,0,2,0,16,0,100,97,116,97,146,7,0,0,207,0,225,1,231,2,246,3,247,4,2,6,255,6,246,7,230,8,192,9,164,10,103,11,45,12,218,12,130,13,17,14,157,14,25,15,126,15,222,15,48,16,
108,16,157,16,194,16,213,16,222,16,218,16,197,16,174,16,139,16,94,16,44,16,243,15,180,15,111,15,41,15,220,14,140,14,60,14,233,13,153,13,67,13,233,12,140,12,48,12,212,11,115,11,21,11,179,10,86,10,243,9,149,9,49,9,208,8,118,8,15,8,180,7,74,7,243,6,132,
6,41,6,189,5,96,5,249,4,149,4,53,4,206,3,105,3,3,3,154,2,59,2,208,1,109,1,1,1,151,0,47,0,197,255,88,255,239,254,129,254,16,254,164,253,49,253,203,252,89,252,246,251,133,251,38,251,187,250,92,250,253,249,159,249,71,249,234,248,155,248,60,248,241,247,154,
247,81,247,2,247,195,246,134,246,73,246,28,246,236,245,201,245,175,245,152,245,142,245,134,245,134,245,145,245,156,245,171,245,198,245,227,245,11,246,50,246,105,246,160,246,225,246,40,247,112,247,199,247,23,248,117,248,208,248,45,249,146,249,238,249,
88,250,186,250,35,251,128,251,235,251,69,252,174,252,8,253,106,253,195,253,27,254,114,254,194,254,15,255,83,255,142,255,196,255,238,255,16,0,52,0,61,0,71,0,71,0,59,0,44,0,13,0,234,255,183,255,127,255,62,255,239,254,155,254,61,254,209,253,99,253,234,252,
109,252,235,251,105,251,218,250,82,250,192,249,52,249,171,248,40,248,173,247,44,247,187,246,81,246,236,245,158,245,74,245,16,245,223,244,183,244,161,244,154,244,169,244,190,244,234,244,39,245,113,245,211,245,72,246,201,246,98,247,3,248,183,248,119,249,
69,250,30,251,253,251,242,252,217,253,225,254,215,255,229,0,225,1,243,2,236,3,249,4,238,5,236,6,214,7,197,8,160,9,118,10,66,11,254,11,172,12,78,13,230,13,110,14,225,14,81,15,168,15,249,15,50,16,102,16,132,16,156,16,158,16,157,16,141,16,116,16,79,16,45,
16,247,15,198,15,136,15,80,15,3,15,191,14,112,14,38,14,219,13,139,13,59,13,231,12,151,12,59,12,231,11,134,11,43,11,207,10,114,10,20,10,181,9,87,9,242,8,146,8,47,8,202,7,100,7,0,7,151,6,46,6,196,5,91,5,237,4,135,4,28,4,181,3,78,3,229,2,126,2,26,2,182,
1,81,1,231,0,127,0,23,0,170,255,64,255,209,254,105,254,245,253,131,253,23,253,166,252,53,252,206,251,93,251,245,250,136,250,33,250,185,249,87,249,242,248,149,248,52,248,224,247,129,247,53,247,231,246,159,246,92,246,33,246,236,245,196,245,160,245,132,
245,114,245,104,245,98,245,104,245,115,245,134,245,154,245,193,245,227,245,19,246,73,246,130,246,198,246,20,247,95,247,190,247,23,248,120,248,224,248,68,249,182,249,28,250,143,250,253,250,106,251,214,251,70,252,168,252,21,253,115,253,209,253,50,254,132,
254,219,254,36,255,107,255,170,255,227,255,20,0,58,0,87,0,116,0,123,0,129,0,125,0,114,0,95,0,64,0,30,0,234,255,187,255,124,255,52,255,233,254,144,254,44,254,198,253,88,253,223,252,98,252,224,251,94,251,214,250,79,250,192,249,61,249,181,248,53,248,181,
247,69,247,206,246,99,246,4,246,175,245,96,245,38,245,237,244,193,244,168,244,148,244,152,244,165,244,197,244,239,244,40,245,125,245,211,245,65,246,190,246,72,247,224,247,144,248,63,249,12,250,221,250,183,251,160,252,135,253,128,254,120,255,129,0,131,
1,139,2,150,3,154,4,160,5,160,6,151,7,135,8,111,9,78,10,29,11,224,11,154,12,69,13,218,13,110,14,219,14,75,15,166,15,238,15,51,16,94,16,129,16,144,16,152,16,146,16,130,16,105,16,72,16,25,16,232,15,176,15,113,15,50,15,235,14,164,14,82,14,12,14,179,13,111,
13,21,13,201,12,110,12,28,12,195,11,106,11,15,11,179,10,86,10,252,9,154,9,66,9,224,8,126,8,34,8,188,7,93,7,247,6,147,6,47,6,199,5,102,5,252,4,160,4,53,4,214,3,109,3,13,3,169,2,67,2,225,1,119,1,19,1,168,0,65,0,217,255,109,255,0,255,147,254,32,254,178,
253,68,253,216,252,108,252,2,252,157,251,48,251,207,250,106,250,7,250,164,249,73,249,229,248,143,248,55,248,226,247,141,247,71,247,249,246,188,246,126,246,77,246,22,246,243,245,210,245,185,245,175,245,165,245,166,245,175,245,190,245,213,245,240,245,23,
246,65,246,114,246,173,246,229,246,51,247,118,247,204,247,30,248,122,248,217,248,57,249,162,249,4,250,106,250,213,250,54,251,157,251,255,251,99,252,184,252,26,253,106,253,197,253,15,254,99,254,164,254,235,254,45,255,103,255,154,255,201,255,234,255,9,
0,34,0,51,0,54,0,63,0,51,0,33,0,18,0,239,255,202,255,153,255,91,255,26,255,202,254,118,254,18,254,169,253,52,253,185,252,58,252,183,251,43,251,163,250,25,250,141,249,4,249,126,248,250,247,124,247,10,247,150,246,49,246,220,245,130,245,62,245,3,245,212,
244,177,244,157,244,155,244,158,244,190,244,227,244,29,245,103,245,195,245,43,246,172,246,57,247,211,247,126,248,57,249,252,249,211,250,175,251,156,252,138,253,136,254,134,255,133,0,152,1,155,2,171,3,173,4,181,5,172,6,167,7,150,8,119,9,83,10,33,11,217,
11,148,12,51,13,200,13,79,14,201,14,44,15,141,15,214,15,26,16,73,16,113,16,130,16,145,16,145,16,130,16,109,16,73,16,33,16,241,15,187,15,124,15,57,15,238,14,171,14,87,14,11,14,187,13,104,13,23,13,194,12,108,12,21,12,188,11,104,11,12,11,184,10,93,10,6,
10,171,9,87,9,252,8,169,8,74,8,248,7,151,7,69,7,232,6,136,6,51,6,210,5,116,5,23,5,180,4,84,4,241,3,143,3,47,3,197,2,96,2,245,1,136,1,27,1,169,0,59,0,202,255,89,255,223,254,109,254,247,253,133,253,12,253,157,252,42,252,186,251,75,251,224,250,114,250,12,
250,165,249,61,249,221,248,126,248,31,248,207,247,109,247,28,247,210,246,137,246,71,246,12,246,215,245,167,245,137,245,103,245,82,245,72,245,65,245,72,245,77,245,96,245,118,245,147,245,187,245,228,245,23,246,87,246,146,246,223,246,44,247,133,247,216,
247,65,248,161,248,11,249,115,249,227,249,76,250,187,250,44,251,143,251,2,252,101,252,206,252,55,253,153,253,248,253,83,254,175,254,247,254,74,255,139,255,209,255,0,0,55,0,91,0,123,0,153,0,162,0,172,0,169,0,158,0,134,0,105,0,63,0,6,0,211,255,136,255,
57,255,219,254,120,254,4,254,148,253,19,253,141,252,0,252,113,251,220,250,77,250,189,249,44,249,157,248,20,248,140,247,15,247,150,246,44,246,194,245,107,245,25,245,209,244,162,244,112,244,87,244,72,244,75,244,93,244,131,244,181,244,246,244,77,245,175,
245,39,246,170,246,75,247,231,247,162,248,100,249,54,250,16,251,254,251,232,252,228,253,230,254,236,255,239,0,4,2,11,3,22,4,25,5,32,6,18,7,16,8,244,8,215,9,176,10,118,11,48,12,220,12,121,13,3,14,133,14,242,14,87,15,165,15,237,15,32,16,72,16,102,16,119,
16,123,16,117,16,102,16,71,16,47,16,1,16,218,15,165,15,117,15,49,15,253,14,178,14,112,14,36,14,226,13,148,13,74,13,251,12,175,12,87,12,10,12,174,11,93,11,0,11,173,10,83,10,247,9,155,9,64,9,227,8,128,8,35,8,192,7,93,7,247,6,143,6,35,6,196,5,85,5,231,4,
131,4,19,4,171,3,61,3,206,2,98,2,234,1,126,1,7,1,147,0,31,0,164,255,55,255,181,254,71,254,202,253,93,253,224,252,115,252,255,251,149,251,36,251,188,250,75,250,230,249,126,249,25,249,178,248,85,248,247,247,159,247,70,247,243,246,173,246,97,246,40,246,
235,245,192,245,149,245,112,245,90,245,69,245,60,245,53,245,62,245,68,245,90,245,115,245,144,245,189,245,237,245,32,246,95,246,166,246,240,246,63,247,157,247,242,247,89,248,190,248,40,249,150,249,7,250,117,250,231,250,88,251,208,251,54,252,176,252,28,
253,141,253,239,253,92,254,181,254,18,255,108,255,173,255,10,0,31,0,76,73,83,84,190,0,0,0,73,78,70,79,73,78,65,77,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,0,73,65,82,
84,26,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,0,0,73,67,77,84,44,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,
109,71,115,84,71,114,49,73,0,73,67,82,68,10,0,0,0,50,48,49,57,48,53,50,49,0,0,73,83,70,84,34,0,0,0,76,97,118,102,53,56,46,55,54,46,49,48,48,32,40,108,105,98,115,110,100,102,105,108,101,45,49,46,48,46,51,49,41,0,105,100,51,32,198,0,0,0,73,68,51,3,0,0,
0,0,1,59,84,73,84,50,0,0,0,32,0,0,0,69,117,112,104,111,110,105,117,109,32,45,32,119,104,97,116,32,105,116,32,115,111,117,110,100,115,32,108,105,107,101,67,79,77,77,0,0,0,48,0,0,0,0,0,0,0,104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,
98,101,46,99,111,109,47,119,97,116,99,104,63,118,61,115,49,89,109,71,115,84,71,114,49,73,84,80,69,49,0,0,0,25,0,0,0,82,111,99,104,100,97,108,101,32,66,111,114,111,117,103,104,32,67,111,117,110,99,105,108,84,68,82,67,0,0,0,9,0,0,0,50,48,49,57,48,53,50,
49,84,88,88,88,0,0,0,23,0,0,0,83,111,102,116,119,97,114,101,0,76,97,118,102,53,56,46,55,54,46,49,48,48,0,0,0 };

const char* Sustain_Quiet_wav = (const char*) temp_binary_data_15;

//================== CabinetEmulation.cpp ==================
static const unsigned char temp_binary_data_16[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    CabinetEmulation.cpp\r\n"
"    Created: 17 May 2025 6:51:21pm\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"CabinetEmulation.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"CabinetEmulation::CabinetEmulation()\r\n"
"{\r\n"
"    // In your constructor, you should add any child components, and\r\n"
"    // initialise any special settings that your component needs.\r\n"
"\r\n"
"}\r\n"
"\r\n"
"CabinetEmulation::~CabinetEmulation()\r\n"
"{\r\n"
"}\r\n"
"\r\n"
"void CabinetEmulation::paint (juce::Graphics& g)\r\n"
"{\r\n"
"    /* This demo code just fills the component's background and\r\n"
"       draws some placeholder text to get you started.\r\n"
"\r\n"
"       You should replace everything in this method with your own\r\n"
"       drawing code..\r\n"
"    */\r\n"
"\r\n"
"    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background\r\n"
"\r\n"
"    g.setColour (juce::Colours::grey);\r\n"
"    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component\r\n"
"\r\n"
"    g.setColour (juce::Colours::white);\r\n"
"    g.setFont (juce::FontOptions (14.0f));\r\n"
"    g.drawText (\"CabinetEmulation\", getLocalBounds(),\r\n"
"                juce::Justification::centred, true);   // draw some placeholder text\r\n"
"}\r\n"
"\r\n"
"void CabinetEmulation::resized()\r\n"
"{\r\n"
"    // This method is where you should set the bounds of any child\r\n"
"    // components that your component contains..\r\n"
"\r\n"
"}\r\n";

const char* CabinetEmulation_cpp = (const char*) temp_binary_data_16;

//================== CabinetEmulation.h ==================
static const unsigned char temp_binary_data_17[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    CabinetEmulation.h\r\n"
"    Created: 17 May 2025 6:51:21pm\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#pragma once\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"\r\n"
"//==============================================================================\r\n"
"/*\r\n"
"*/\r\n"
"class CabinetEmulation  : public juce::Component\r\n"
"{\r\n"
"public:\r\n"
"    CabinetEmulation();\r\n"
"    ~CabinetEmulation() override;\r\n"
"\r\n"
"    void paint (juce::Graphics&) override;\r\n"
"    void resized() override;\r\n"
"\r\n"
"private:\r\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabinetEmulation)\r\n"
"};\r\n";

const char* CabinetEmulation_h = (const char*) temp_binary_data_17;

//================== GramoMain.cpp ==================
static const unsigned char temp_binary_data_18[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    GramoMain.cpp\r\n"
"    Created: 13 May 2025 11:10:55am\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"GramoMain.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"GramoMain::GramoMain()\r\n"
"{\r\n"
"\t// In your constructor, you should add any child components, and\r\n"
"\t// initialise any special settings that your component needs.\r\n"
"\r\n"
"\tinitaliseGramoVoice();\r\n"
"}\r\n"
"\r\n"
"void GramoMain::initaliseGramoVoice()\r\n"
"{\r\n"
"\tconstexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.\r\n"
"\r\n"
"\tsetupStylusParams(TEXT_BOX_SIZE);\r\n"
"\tsetupSoundboxParams(TEXT_BOX_SIZE);\r\n"
"\tsetupHornParams(TEXT_BOX_SIZE);\r\n"
"\r\n"
"\tgramoStylus; // Initialise the stylus emulation\r\n"
"\tgramoSoundbox; // Initialise the soundbox emulation\r\n"
"\tgramoHorn; // Initialise the horn emulation\r\n"
"\r\n"
"\t//std::string GramoSuite = \"../Source/UI/GramoSuite.fbx\";\r\n"
"}\r\n"
"\r\n"
"GramoMain::~GramoMain()\r\n"
"{\r\n"
"}\r\n"
"\r\n"
"void GramoMain::prepareToPlay(int samplesPerBlockExpected, double sampleRate)\r\n"
"{\r\n"
"\t// Use this method as the place to do any pre-playback\r\n"
"\t// initialisation that you need..\r\n"
"\tgramoStylus.prepareToPlay(samplesPerBlockExpected, sampleRate);\r\n"
"\tgramoSoundbox.prepareToPlay(samplesPerBlockExpected, sampleRate);\r\n"
"\tgramoHorn.prepareToPlay(samplesPerBlockExpected, sampleRate);\r\n"
"}\r\n"
"\r\n"
"void GramoMain::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)\r\n"
"{\r\n"
"\r\n"
"\t// Process the audio data through the components\r\n"
"\tgramoStylus.getNextAudioBlock(bufferToFill);\r\n"
"\tgramoSoundbox.getNextAudioBlock(bufferToFill);\r\n"
"\tgramoHorn.getNextAudioBlock(bufferToFill);\r\n"
"}\r\n"
"\r\n"
"void GramoMain::releaseResources()\r\n"
"{\r\n"
"\t// When playback stops, you can use this as an opportunity\r\n"
"\t// to free up any spare memory, etc.\r\n"
"\tgramoStylus.releaseResources();\r\n"
"\tgramoSoundbox.releaseResources();\r\n"
"\tgramoHorn.releaseResources();\r\n"
"}\r\n"
"\r\n"
"void GramoMain::paint(juce::Graphics& g)\r\n"
"{\r\n"
"    setupSections();\r\n"
"\tdrawUiText(g);\r\n"
"}\r\n"
"\r\n"
"void GramoMain::setupSections()\r\n"
"{\r\n"
"    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.\r\n"
"\tpictureSection = r.removeFromBottom(200); // Allocates the picture section.\r\n"
"    \r\n"
"    juce::Rectangle<int> interfaceSection = r; // Remaining area for the interface.\r\n"
"    int sectionHeight = interfaceSection.getHeight() / 4; // Divides the interface into four sections.\r\n"
"    constexpr int textSectionWidth = 40; // Width for the text labels.\r\n"
"\r\n"
"\tstylusUiComponent(interfaceSection, sectionHeight, textSectionWidth); // Sets up the stylus UI sections.\r\n"
"\tsoundboxUiComponent(interfaceSection, sectionHeight, textSectionWidth); // Sets up the soundbox UI sections.\r\n"
"    hornUiComponent(interfaceSection, sectionHeight, textSectionWidth); // Sets up the horn UI sections.\r\n"
"}\r\n"
"\r\n"
"void GramoMain::drawUiText(juce::Graphics& g)\r\n"
"{\r\n"
"\tg.setFont(18.0f); // Sets the font size for the text.\r\n"
"\tg.drawFittedText(\"STYLUS_PRESSURE\", stylusPressureTextSection, juce::Justification::left, 1); // Draws the text for the stylus pressure section.\r\n"
"\tg.drawFittedText(\"VINYL_FILTER_FREQ\", vinylFilterFreqTextSection, juce::Justification::left, 1); // Draws the text for the vinyl filter frequency section.\r\n"
"\tg.drawFittedText(\"PITCH_SHIFT\", pitchShiftTextSection, juce::Justification::left, 1); // Draws the text for the pitch shift section.\r\n"
"\r\n"
"\tg.drawFittedText(\"SOUNDBOX_PRESSURE\", soundboxPressureTextSection, juce::Justification::left, 1); // Draws the text for the soundbox pressure section.\r\n"
"\tg.drawFittedText(\"NOISE_GAIN\", noiseGainTextSection, juce::Justification::left, 1); // Draws the text for the noise gain section.\r\n"
"\tg.drawFittedText(\"VIBRATO_DEPTH\", vibratoDepthTextSection, juce::Justification::left, 1); // Draws the text for the vibrato depth section.\r\n"
"\tg.drawFittedText(\"VIBRATO_FREQ\", vibratoRateTextSection, juce::Justification::left, 1); // Draws the text for the vibrato frequency section.\r\n"
"\tg.drawFittedText(\"VIBRATO_GAIN\", vibratoGainTextSection, juce::Justification::left, 1); // Draws the text for the vibrato gain section.\r\n"
"\tg.drawFittedText(\"VIBRATO_MIX\", vibratoMixTextSection, juce::Justification::left, 1); // Draws the text for the vibrato mix section.\r\n"
"\r\n"
"\tg.drawFittedText(\"HORN_STIFFNESS\", hornStiffnessTextSection, juce::Justification::left, 1); // Draws the text for the horn stiffness section.\r\n"
"\tg.drawFittedText(\"HORN_DIAMETER\", hornDiameterTextSection, juce::Justification::left, 1); // Draws the text for the horn diameter section.\r\n"
"\tg.drawFittedText(\"HORN_LENGTH\", hornLengthTextSection, juce::Justification::left, 1); // Draws the text for the horn length section.\r\n"
"}\r\n"
"\r\n"
"\r\n"
"void GramoMain::stylusUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth)\r\n"
"{\r\n"
"    stylusPressureSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    stylusPressureTextSection = stylusPressureSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    vinylFilterFreqSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    vinylFilterFreqTextSection = vinylFilterFreqSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    pitchShiftSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    pitchShiftTextSection = pitchShiftSection.removeFromRight(textSectionWidth);\r\n"
"}\r\n"
"\r\n"
"void GramoMain::soundboxUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth)\r\n"
"{\r\n"
"    soundboxPressureSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    soundboxPressureTextSection = soundboxPressureSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    noiseGainSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    noiseGainTextSection = noiseGainSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    vibratoDepthSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    vibratoDepthTextSection = vibratoDepthSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    vibratoRateSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    vibratoRateTextSection = vibratoRateSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    vibratoGainSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    vibratoGainTextSection = vibratoGainSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    vibratoMixSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    vibratoMixTextSection = vibratoMixSection.removeFromRight(textSectionWidth);\r\n"
"}\r\n"
"\r\n"
"void GramoMain::hornUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth)\r\n"
"{\r\n"
"    // Allocates sections for sliders and their labels.\r\n"
"    hornStiffnessSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    hornStiffnessTextSection = hornStiffnessSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    hornDiameterSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    hornDiameterTextSection = hornDiameterSection.removeFromRight(textSectionWidth);\r\n"
"\r\n"
"    hornLengthSection = interfaceSection.removeFromTop(sectionHeight);\r\n"
"    hornLengthTextSection = hornLengthSection.removeFromRight(textSectionWidth);\r\n"
"}\r\n"
"\r\n"
"void GramoMain::setupStylusParams(const int TEXT_BOX_SIZE)\r\n"
"{\r\n"
"\t// Set up for the stylus parameters\r\n"
"\tstylusPressureParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tstylusPressureParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tstylusPressureParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(stylusPressureParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\tvinylFilterFreqParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tvinylFilterFreqParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tvinylFilterFreqParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(vinylFilterFreqParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\tpitchShiftParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tpitchShiftParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tpitchShiftParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(pitchShiftParam); // Makes the slider visible in the editor.\r\n"
"}\r\n"
"\r\n"
"void GramoMain::setupHornParams(const int TEXT_BOX_SIZE)\r\n"
"{\r\n"
"\t// Set up for the horn parameters\t\r\n"
"\thornStiffnessParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\thornStiffnessParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\thornStiffnessParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(hornStiffnessParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\thornDiameterParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\thornDiameterParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\thornDiameterParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(hornDiameterParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\thornLengthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\thornLengthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\thornLengthParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(hornLengthParam); // Makes the slider visible in the editor.\r\n"
"}\r\n"
"\r\n"
"void GramoMain::setupSoundboxParams(const int TEXT_BOX_SIZE)\r\n"
"{\r\n"
"\t// Set up for the soundbox parameters\r\n"
"\tsoundboxPressureParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tsoundboxPressureParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tsoundboxPressureParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(soundboxPressureParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\tnoiseGainParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tnoiseGainParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tnoiseGainParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(noiseGainParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\tvibratoDepthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tvibratoDepthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tvibratoDepthParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(vibratoDepthParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\tvibratoRateParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tvibratoRateParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tvibratoRateParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(vibratoRateParam); // Makes the slider visible in the editor.\r\n"
"\r\n"
"\tvibratoGainParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\r\n"
"\tvibratoGainParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\r\n"
"\tvibratoGainParam.setRange(0.0f, 1.0f); // Sets the range of the slider.\r\n"
"\taddAndMakeVisible(vibratoGainParam); // Makes the slider visible in the editor.\r\n"
"}\r\n"
"\r\n"
"void GramoMain::resized()\r\n"
"{\r\n"
"    // This method is called when the component is resized.\r\n"
"    // Use this to lay out any child components that you want to add.\r\n"
"\r\n"
"    setupSections();\r\n"
"}\r\n"
"\r\n"
"void GramoMain::sliderValueChanged(juce::Slider* slider)\r\n"
"{\r\n"
"\trepaint();\r\n"
"}";

const char* GramoMain_cpp = (const char*) temp_binary_data_18;

//================== GramoMain.h ==================
static const unsigned char temp_binary_data_19[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    GramoMain.h\r\n"
"    Created: 13 May 2025 11:10:55am\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#pragma once\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"StylusEmulation.h\"\r\n"
"#include \"HornEmulation.h\"\r\n"
"#include \"SoundboxEmulation.h\"\r\n"
"#include \"../Source/PluginProcessor.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"/*\r\n"
"*/\r\n"
"class GramoMain : public juce::Component, juce::AudioSource, juce::Slider::Listener\r\n"
"{\r\n"
"public:\r\n"
"    GramoMain();\r\n"
"    void initaliseGramoVoice();\r\n"
"    void setupStylusParams(const int TEXT_BOX_SIZE);\r\n"
"    void setupSoundboxParams(const int TEXT_BOX_SIZE);\r\n"
"    void setupHornParams(const int TEXT_BOX_SIZE);\r\n"
"    ~GramoMain() override;\r\n"
"\r\n"
"    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;\r\n"
"    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;\r\n"
"    void releaseResources() override;\r\n"
"\r\n"
"\tvoid paint(juce::Graphics& g) override; // Paints the editor's GUI components.\r\n"
"    void drawUiText(juce::Graphics& g);\r\n"
"    void resized() override; // Handles resizing and layout of GUI components.\r\n"
"\r\n"
"    juce::Rectangle<int> pictureSection; // Rectangle for the picture section of the GUI.\r\n"
"\r\n"
"    // Type alias for a unique pointer to a SliderAttachment.\r\n"
"    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;\r\n"
"\r\n"
"    // Horn parameters\r\n"
"    juce::Slider hornStiffnessParam; // Slider for controlling the stiffness of the gramophone's brass horn.\r\n"
"    SliderAttatchmentPtr hornStiffnessAttach; // Attachment to link the horn stiffness slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider hornDiameterParam; // Slider for controlling the diameter of the gramophone's brass horn.\r\n"
"    SliderAttatchmentPtr hornDiameterAttach; // Attachment to link the horn diameter slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider hornLengthParam; // Slider for controlling the length of the gramophone's brass horn.\r\n"
"    SliderAttatchmentPtr hornLengthAttach; // Attachment to link the horn length slider to the parameter tree.\r\n"
"\r\n"
"    // Soundbox parameters\r\n"
"    juce::Slider soundboxPressureParam; // Slider for controlling the soundbox pressure.\r\n"
"    SliderAttatchmentPtr soundboxPressureAttach; // Attachment to link the soundbox pressure slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider noiseGainParam; // Slider for controlling the noise gain in the soundbox.\r\n"
"    SliderAttatchmentPtr noiseGainAttach; // Attachment to link the noise gain slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider vibratoDepthParam; // Slider for controlling the depth of the vibrato effect.\r\n"
"    SliderAttatchmentPtr vibratoDepthAttach; // Attachment to link the vibrato depth slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider vibratoRateParam; // Slider for controlling the vibrato frequency.\r\n"
"    SliderAttatchmentPtr vibratoRateAttach; // Attachment to link the vibrato frequency slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider vibratoGainParam; // Slider for controlling the vibrato gain.\r\n"
"    SliderAttatchmentPtr vibratoGainAttach; // Attachment to link the vibrato gain slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider vibratoMixParam; // Slider for controlling the vibrato mix.\r\n"
"    SliderAttatchmentPtr vibratoMixAttach; // Attachment to link the vibrato mix slider to the parameter tree.\r\n"
"\r\n"
"    // Stylus parameters\r\n"
"    juce::Slider stylusPressureParam; // Slider for controlling the pressure of the stylus on the record.\r\n"
"    SliderAttatchmentPtr stylusPressureAttach; // Attachment to link the stylus pressure slider to the parameter tree.\r\n"
"\r\n"
"    juce::Slider vinylFilterFreqParam; // Slider for controlling the vinyl filter frequency.\r\n"
"    SliderAttatchmentPtr vinylFilterFreqAttach; // Attachment to link the vinyl filter frequency slider to the parameter tree.\r\n"
"\r\n"
"    // Global parameters\r\n"
"    juce::Slider pitchShiftParam; // Slider for controlling the pitch shift.\r\n"
"    SliderAttatchmentPtr pitchShiftAttach; // Attachment to link the pitch shift slider to the parameter tree.\r\n"
"\r\n"
"private:\r\n"
"\r\n"
"    void sliderValueChanged(juce::Slider* slider) override; // Callback for when a slider's value changes.\r\n"
"\tvoid setupSections(); // Sets up the layout and sections of the GUI.\r\n"
"\r\n"
"    void stylusUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth);\r\n"
"    void soundboxUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth);\r\n"
"    void hornUiComponent(juce::Rectangle<int>& interfaceSection, int sectionHeight, const int textSectionWidth);\r\n"
"\r\n"
"    \r\n"
"    // Rectangles defining sections of the GUI layout.\r\n"
"\r\n"
"\t// Rectangles for the interface horn sections.\r\n"
"\tjuce::Rectangle<int> hornStiffnessSection; // Rectangle for the horn stiffness section of the GUI.\r\n"
"\tjuce::Rectangle<int> hornStiffnessTextSection; // Rectangle for the text label of the horn stiffness section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> hornDiameterSection; // Rectangle for the horn diameter section of the GUI.\r\n"
"\tjuce::Rectangle<int> hornDiameterTextSection; // Rectangle for the text label of the horn diameter section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> hornLengthSection; // Rectangle for the horn length section of the GUI.\r\n"
"\tjuce::Rectangle<int> hornLengthTextSection; // Rectangle for the text label of the horn length section.\r\n"
"\r\n"
"\t// Rectangles for the interface soundbox sections.\r\n"
"\tjuce::Rectangle<int> soundboxPressureSection; // Rectangle for the soundbox pressure section of the GUI.\r\n"
"\tjuce::Rectangle<int> soundboxPressureTextSection; // Rectangle for the text label of the soundbox pressure section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> noiseGainSection; // Rectangle for the noise gain section of the GUI.\r\n"
"\tjuce::Rectangle<int> noiseGainTextSection; // Rectangle for the text label of the noise gain section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> vibratoDepthSection; // Rectangle for the vibrato depth section of the GUI.\r\n"
"\tjuce::Rectangle<int> vibratoDepthTextSection; // Rectangle for the text label of the vibrato depth section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> vibratoRateSection; // Rectangle for the vibrato frequency section of the GUI.\r\n"
"\tjuce::Rectangle<int> vibratoRateTextSection; // Rectangle for the text label of the vibrato frequency section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> vibratoGainSection; // Rectangle for the vibrato gain section of the GUI.\r\n"
"\tjuce::Rectangle<int> vibratoGainTextSection; // Rectangle for the text label of the vibrato gain section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> vibratoMixSection; // Rectangle for the vibrato mix section of the GUI.\r\n"
"\tjuce::Rectangle<int> vibratoMixTextSection; // Rectangle for the text label of the vibrato mix section.\r\n"
"\r\n"
"\t// Rectangles for the interface stylus sections.\r\n"
"\tjuce::Rectangle<int> stylusPressureSection; // Rectangle for the stylus pressure section of the GUI.\r\n"
"\tjuce::Rectangle<int> stylusPressureTextSection; // Rectangle for the text label of the stylus pressure section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> vinylFilterFreqSection; // Rectangle for the vinyl filter frequency section of the GUI.\r\n"
"\tjuce::Rectangle<int> vinylFilterFreqTextSection; // Rectangle for the text label of the vinyl filter frequency section.\r\n"
"\r\n"
"\tjuce::Rectangle<int> pitchShiftSection; // Rectangle for the pitch shift section of the GUI.\r\n"
"\tjuce::Rectangle<int> pitchShiftTextSection; // Rectangle for the text label of the pitch shift section.\r\n"
"\r\n"
"    StylusEmulation gramoStylus;\r\n"
"\tHornEmulation gramoHorn;\r\n"
"    SoundboxEmulation gramoSoundbox;\r\n"
"\r\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GramoMain)\r\n"
"};";

const char* GramoMain_h = (const char*) temp_binary_data_19;

//================== HornEmulation.cpp ==================
static const unsigned char temp_binary_data_20[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    HornEmulation.cpp\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"HornEmulation.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"HornEmulation::HornEmulation()\r\n"
"{\r\n"
"    // In your constructor, you should add any child components, and\r\n"
"    // initialise any special settings that your component needs.\r\n"
"\r\n"
"\t// ADSR setup\r\n"
"\tadsr.setTarget(1.0);\r\n"
"\tadsr.setAttackRate(0.02);\r\n"
"\tadsr.setDecayRate(0.2);\r\n"
"\tadsr.setSustainLevel(0.9);\r\n"
"\tadsr.setReleaseRate(0.1);\r\n"
"\r\n"
"\t// Initialise member variables to avoid warning C26495\r\n"
"\tpitchShiftTarget = 0.0f;\r\n"
"\tmaxDelay = 0.0f;\r\n"
"\tdelayLength = 0;\r\n"
"\treadPtr = 0;\r\n"
"\twritePtr = 0;\r\n"
"\toutputGain = 1.0f;\r\n"
"\tinputGain = 0.5f;\r\n"
"\tfrequency = 440.0f;  // Default A4, will be overridden\r\n"
"\r\n"
"\t// Initialise RMS tracking\r\n"
"\trmsLevel = 0.0f;\r\n"
"\trmsAlpha = 0.99f;  // Smoothing factor (adjust as needed)\r\n"
"}\r\n"
"\r\n"
"HornEmulation::WaveguideSynthesis::WaveguideSynthesis()\r\n"
"{\r\n"
"\t// In your constructor, you should add any child components, and\r\n"
"\t// initialise any special settings that your component needs.\r\n"
"\r\n"
"\treader = nullptr;\r\n"
"\taudioFormatManager.registerBasicFormats(); // Register basic audio formats\r\n"
"\tsetupBodyResonances(); // Initialise body resonances\r\n"
"}\r\n"
"\r\n"
"HornEmulation::~HornEmulation()\r\n"
"{\r\n"
"\t// Destructor for waveguide synthesis\r\n"
"\tadsr.setTarget(10.0); // Set target to 10.0 to avoid any abrupt changes\r\n"
"\tadsr.setAttackRate(0.1); // Set attack rate to 0.2 to simulate sound passing through the horn\r\n"
"\tadsr.setDecayRate(0.0); //\tNo decay\r\n"
"\tadsr.setSustainLevel(10.0);\r\n"
"\tadsr.setReleaseRate(0.1); // To simulate post-audio brass vibrations\r\n"
"}\r\n"
"\r\n"
"\r\n"
"HornEmulation::WaveguideSynthesis::~WaveguideSynthesis()\r\n"
"{\r\n"
"\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::WaveguideSynthesis::prepareToPlay(int samplesPerBlockExpected, double sampleRate)\r\n"
"{\r\n"
"\thandleImpulseResponse(sampleRate, samplesPerBlockExpected); // Handle the impulse response\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)\r\n"
"{\r\n"
"\tpitchShiftTarget = 0.0f;\r\n"
"\r\n"
"\t// Calculate delay buffer length based on lowest frequency\r\n"
"\tmaxDelay = sampleRate / lowestFrequency + 1;\r\n"
"\tdelayLength = maxDelay;\r\n"
"\r\n"
"\t// Initialise delay line\r\n"
"\tfor (int i = 0; i < 2048; i++)\r\n"
"\t\tdelayLine[i] = 0.0f;\r\n"
"\r\n"
"\treadPtr = 0;\r\n"
"\twritePtr = delayLength;\r\n"
"\r\n"
"\toutputGain = 1.0f;\r\n"
"\tinputGain = 0.5f;\r\n"
"\r\n"
"\tfreqSetup(); // Set the frequency of the brass synthesis\r\n"
"\r\n"
"\tStk::setSampleRate(sampleRate);\r\n"
"\r\n"
"\t// Convolution setup\r\n"
"\tjuce::dsp::ProcessSpec specConvolution;\r\n"
"\tspecConvolution.sampleRate = sampleRate;\r\n"
"\tspecConvolution.maximumBlockSize = samplesPerBlockExpected;\r\n"
"\tspecConvolution.numChannels = 1;\r\n"
"\r\n"
"\tfor (int i = 0; i <= 10; i++) convolution[i].prepare(specConvolution); // Prepare the convolution processor\r\n"
"\r\n"
"\twaveguideSynthesis.prepareToPlay(samplesPerBlockExpected, sampleRate); // Initialise the waveguide synthesis\r\n"
"\r\n"
"\tfor (int i = 0; i < 11; ++i) // Load impulses responses into convolution method\r\n"
"\t{\r\n"
"\t\twaveguideSynthesis.reader = waveguideSynthesis.audioFormatManager.createReaderFor(waveguideSynthesis.irFiles[i]);\r\n"
"\r\n"
"\t\tif (waveguideSynthesis.reader != nullptr)\r\n"
"\t\t{\r\n"
"\t\t\twaveguideSynthesis.iRs[i].setSize(1, static_cast<int>(waveguideSynthesis.reader->lengthInSamples));\r\n"
"\t\t\twaveguideSynthesis.reader->read(&waveguideSynthesis.iRs[i], 0, static_cast<int>(waveguideSynthesis.reader->lengthInSamples), 0, true, true);\r\n"
"\r\n"
"\t\t\tconvolution[i].loadImpulseResponse(\r\n"
"\t\t\t\tstd::move(waveguideSynthesis.iRs[i]),\r\n"
"\t\t\t\twaveguideSynthesis.reader->sampleRate,\r\n"
"\t\t\t\tjuce::dsp::Convolution::Stereo::no,\r\n"
"\t\t\t\tjuce::dsp::Convolution::Trim::no,\r\n"
"\t\t\t\tjuce::dsp::Convolution::Normalise::yes);\r\n"
"\r\n"
"\t\t\tdelete waveguideSynthesis.reader;\r\n"
"\t\t\twaveguideSynthesis.reader = nullptr;\r\n"
"\t\t}\r\n"
"\t}\r\n"
"}\r\n"
"\r\n"
"stk::StkFloat HornEmulation::tick(unsigned int channel)\r\n"
"{\r\n"
"\tfloat input = gramoStylus.getFilterOutput(); // Get the input from the stylus\r\n"
"\r\n"
"\tfloat output = brassHorn.tick(); // Mix with waveguide synthesis output\r\n"
"\r\n"
"\toutput *= adsr.tick(); // Mix with waveguide synthesis output\r\n"
"\r\n"
"\treturn output;\r\n"
"}\r\n"
"\r\n"
"stk::StkFrames& HornEmulation::tick(stk::StkFrames& frames, unsigned int channel) {\r\n"
"\t// Process each sample in the frame\r\n"
"\tfor (unsigned int i = 0; i < frames.frames(); i++) {\r\n"
"\t\tframes(i, channel) = tick();\r\n"
"\t}\r\n"
"\treturn frames;\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::WaveguideSynthesis::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)\r\n"
"{\r\n"
"\t// This function is called by the host to fill the output buffer with audio data.\r\n"
"\tbufferToFill.clearActiveBufferRegion(); // Clear the buffer region\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)\r\n"
"{\r\n"
"\tfloat incomingAmplitude = 0.0f;\r\n"
"\tint sampleCount = 0;\r\n"
"\r\n"
"\t// This function is called by the host to fill the output buffer with audio data.\r\n"
"\tfor (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {\r\n"
"\t\tfloat* channelData = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);\r\n"
"\r\n"
"\t\tfor (int sample = 0; sample < bufferToFill.numSamples; ++sample) {\r\n"
"\t\t\t// Get input from the buffer\r\n"
"\t\t\tfloat inputSample = channelData[sample];\r\n"
"\r\n"
"\t\t\t// Process the stylus (which acts as the excitation, like lips in brass)\r\n"
"\t\t\tgramoStylus.processPressureDifference(inputSample);\r\n"
"\r\n"
"\t\t\tfloat stylusOutput = gramoStylus.getFilterOutput();\r\n"
"\r\n"
"\t\t\tbrassHorn.noteOn(frequency, stylusOutput); // This is conceptual - you'd need to adapt\r\n"
"\r\n"
"\t\t\t// Use the STK tick method to get the processed sample\r\n"
"\t\t\tfloat outputSample = brassHorn.tick();\r\n"
"\r\n"
"\t\t\tchannelData[sample] = outputSample;\r\n"
"\r\n"
"\t\t\tincomingAmplitude = pow(channelData[sample], 2.0f);\r\n"
"\t\t\tsampleCount++;\r\n"
"\t\t}\r\n"
"\t}\r\n"
"\r\n"
"\trmsLevel = sqrt(incomingAmplitude / sampleCount); // Calculate RMS level\r\n"
"\trmsLevel = (rmsAlpha * rmsLevel) + (1.0f - rmsAlpha) * incomingAmplitude; // Apply smoothing\r\n"
"\r\n"
"\tincomingAmplitude += brassHorn.lastOut();\r\n"
"\r\n"
"\t// Determine which convolution to use\r\n"
"\tint convIndex = selectConvolutionIndex(incomingAmplitude, adsr.tick());\r\n"
"\r\n"
"\t// Process through the selected convolution\r\n"
"\tauto block = juce::dsp::AudioBlock<float>(*bufferToFill.buffer);\r\n"
"\tauto context = juce::dsp::ProcessContextReplacing<float>(block);\r\n"
"\tconvolution[convIndex].process(context);\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::WaveguideSynthesis::releaseResources()\r\n"
"{\r\n"
"\t// When playback stops, you can use this as an opportunity\r\n"
"\t// to free up any spare memory, etc.\r\n"
"\tfor (int i = 0; i <= 10; ++i) iRs[i].setSize(0, 0);\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::releaseResources()\r\n"
"{\r\n"
"\t// When playback stops, you can use this as an opportunity\r\n"
"\t// to free up any spare memory, etc.\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) {\r\n"
"    // Your implementation here\r\n"
"    // e.g., brassHorn.noteOn(frequency, amplitude);\r\n"
"\r\n"
"\tfrequency = freqSetup(); // Set the frequency of the brass synthesis\r\n"
"\tbrassHorn.startBlowing(amplitude, 0.1);\r\n"
"\tadsr.keyOn();\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::noteOff(stk::StkFloat amplitude) {\r\n"
"\tbrassHorn.setFrequency(freqSetup()); // Set the frequency of the brass synthesis\r\n"
"\tbrassHorn.stopBlowing(amplitude);\r\n"
"\tadsr.keyOff(); // Release the ADSR envelope\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::WaveguideSynthesis::setupBodyResonances()\r\n"
"{\r\n"
"\t// Configure a body resonance filter (BP filter)\r\n"
"\tstk::BiQuad bodyFilter;\r\n"
"\tfloat bodyFrequency = 500.0f; // Resonant frequency in Hz\r\n"
"\tfloat bodyQfactor = 1.5f; // Q factor for the body resonance filter\r\n"
"\tbodyFilter.setResonance(bodyFrequency, bodyQfactor, true); // Set the resonance filter\r\n"
"}\r\n"
"\r\n"
"float HornEmulation::freqSetup()\r\n"
"{\r\n"
"\tconstexpr float brassYoungModulus = 10.0e10f; // Young's modulus for brass in Pascals\r\n"
"\tconstexpr float airDensity = 1.2f; // Density of air in kg/m^3\r\n"
"\tconstexpr float soundSpeed = 343.0f; // Speed of sound in air in m/s\r\n"
"\r\n"
"\tfloat hornDiameter = 0.25f; // Diameter of the horn\r\n"
"\tfloat hornLength = 0.75;\r\n"
"\tfloat hornWallThickness = 0.04f; // Wall thickness of the horn\r\n"
"\r\n"
"\tfloat hornStiffness = (brassYoungModulus * hornWallThickness) /\r\n"
"\t\t(hornDiameter * hornLength); // Simplified stiffness model for a thin-walled brass tube\r\n"
"\r\n"
"\t// Calculate timbre modifier based on geometry\r\n"
"\tfloat wavelength = 2.f * 0.25; // Wavelength of the sound wave\r\n"
"\tfloat freq = soundSpeed / wavelength; // Frequency of the sound wave\r\n"
"\r\n"
"\t// Calculate a timbre modifier proportional to horn stiffness and geometry\r\n"
"\tfloat timbreModifier = hornDiameter / (hornStiffness * hornLength); // Timbre modifier based on horn parameters\r\n"
"\tfloat effectiveFreq = (freq * timbreModifier) + pitchShiftTarget; // Effective frequency based on the horn parameters\r\n"
"\treturn effectiveFreq;\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::WaveguideSynthesis::handleImpulseResponse(double sampleRate, int samplesPerBlock)\r\n"
"{\r\n"
"\taudioFormatManager.registerBasicFormats();\r\n"
"\r\n"
"\treader = nullptr;\r\n"
"\r\n"
"\tirFiles[0] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Initial Stage/Attack Initial Quiet.wav\");\r\n"
"\tirFiles[1] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Initial Stage/Attack Initial Loud.wav\");\r\n"
"\tirFiles[2] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Attack/Halfway Stage/Halfway Attack Quiet.wav\");\r\n"
"\tirFiles[3] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Attack/Halfway Stage/Halfway Attack Loud.wav\");\r\n"
"\tirFiles[4] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Decay/Decay Quiet.wav\");\r\n"
"\tirFiles[5] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Decay/Decay Loud.wav\");\r\n"
"\tirFiles[6] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Sustain/Sustain Quiet.wav\");\r\n"
"\tirFiles[7] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Sustain/Sustain Loud.wav\");\r\n"
"\tirFiles[8] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Quiet/Release/Release Quiet.wav\");\r\n"
"\tirFiles[9] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Initial Stage/Release Initial Loud.wav\");\r\n"
"\tirFiles[10] = juce::File(\"../Source/Audio/Impulse Response Captures/Euphonium/Loud/Release/Halfway Stage/Halfway Release Loud.wav\");\r\n"
"}\r\n"
"\r\n"
"void HornEmulation::setPitchShift(float position)\r\n"
"{\r\n"
"\tpitchShiftTarget = position * 100.0f; // Convert slide position to pitch shift\r\n"
"\r\n"
"\t// Update the frequency if the brass instrument is active\r\n"
"\t// Check if ADSR is in a non-idle state (states 0-3 are active states)\r\n"
"\tint adsrState = adsr.getState();\r\n"
"\tif (adsrState >= 0 && adsrState <= 3) {\r\n"
"\t\t// Update frequency - using the current frequency plus the pitch shift\r\n"
"\t\t// Assuming 'frequency' is the current base frequency\r\n"
"\t\tbrassHorn.setFrequency(frequency + pitchShiftTarget);\r\n"
"\t}\r\n"
"}\r\n"
"\r\n"
"int HornEmulation::selectConvolutionIndex(float amplitude, float adsrValue)\r\n"
"{\r\n"
"\t// Determine if we're using \"loud\" or \"quiet\" IRs\r\n"
"\tconst float LoudnessThresh = 0.3f; // Threshold for loudness\r\n"
"\tbool isLoud = amplitude > 0.6f;\r\n"
"\r\n"
"\t// Get the current ADSR state (STK uses integers 0-4 for its states)\r\n"
"\tint state = adsr.getState();\r\n"
"\r\n"
"\t// Default to the first IR\r\n"
"\tint convolutionIndex = 0;\r\n"
"\r\n"
"\t// STK ADSR states are often: \r\n"
"\t// 0 = ATTACK\r\n"
"\t// 1 = DECAY\r\n"
"\t// 2 = SUSTAIN\r\n"
"\t// 3 = RELEASE\r\n"
"\t// 4 = IDLE\r\n"
"\r\n"
"\tswitch (state) {\r\n"
"\tcase 0: // ATTACK\r\n"
"\t\t// For attack, we have initial and halfway IRs for both loud and quiet\r\n"
"\t\tif (adsrValue < 0.5f) {\r\n"
"\t\t\t// Initial stage of attack\r\n"
"\t\t\tconvolutionIndex = isLoud ? 1 : 0;  // Index 1 = loud initial attack, 0 = quiet initial attack\r\n"
"\t\t}\r\n"
"\t\telse {\r\n"
"\t\t\t// Halfway stage of attack\r\n"
"\t\t\tconvolutionIndex = isLoud ? 3 : 2;  // Index 3 = loud halfway attack, 2 = quiet halfway attack\r\n"
"\t\t}\r\n"
"\t\tbreak;\r\n"
"\r\n"
"\tcase 1: // DECAY\r\n"
"\t\t// For decay, we have separate IRs for loud and quiet\r\n"
"\t\tconvolutionIndex = isLoud ? 5 : 4;  // Index 5 = loud decay, 4 = quiet decay\r\n"
"\t\tbreak;\r\n"
"\r\n"
"\tcase 2: // SUSTAIN\r\n"
"\t\t// For sustain, we have separate IRs for loud and quiet\r\n"
"\t\tconvolutionIndex = isLoud ? 7 : 6;  // Index 7 = loud sustain, 6 = quiet sustain\r\n"
"\t\tbreak;\r\n"
"\r\n"
"\tcase 3: // RELEASE\r\n"
"\t\t// For release, we have quiet, and loud with initial and halfway stages\r\n"
"\t\tif (isLoud) {\r\n"
"\t\t\tif (adsrValue > 0.5f) {\r\n"
"\t\t\t\tconvolutionIndex = 9;  // Loud initial release\r\n"
"\t\t\t}\r\n"
"\t\t\telse {\r\n"
"\t\t\t\tconvolutionIndex = 10; // Loud halfway release\r\n"
"\t\t\t}\r\n"
"\t\t}\r\n"
"\t\telse {\r\n"
"\t\t\tconvolutionIndex = 8;      // Quiet release\r\n"
"\t\t}\r\n"
"\t\tbreak;\r\n"
"\r\n"
"\tdefault: // IDLE or other state\r\n"
"\t\tconvolutionIndex = 0; // Default to first IR\r\n"
"\t\tbreak;\r\n"
"\t}\r\n"
"\r\n"
"\treturn convolutionIndex;\r\n"
"}\r\n";

const char* HornEmulation_cpp = (const char*) temp_binary_data_20;

//================== HornEmulation.h ==================
static const unsigned char temp_binary_data_21[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    HornEmulation.h\r\n"
"    Created: 17 May 2025 6:50:39pm\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#pragma once\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"StylusEmulation.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"/*\r\n"
"*/\r\n"
"class HornEmulation : public juce::Component, public stk::Instrmnt, public juce::AudioSource\r\n"
"{\r\n"
"public:\r\n"
"\r\n"
"    HornEmulation();\r\n"
"    ~HornEmulation() override;\r\n"
"\r\n"
"    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;\r\n"
"    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;\r\n"
"    void releaseResources() override;\r\n"
"\r\n"
"\t// Stk pure virtual methods\r\n"
"    void noteOn(stk::StkFloat frequency, stk::StkFloat amplitude) override;\r\n"
"    void noteOff(stk::StkFloat amplitude) override;\r\n"
"    stk::StkFloat tick(unsigned int channel = 0) override;\r\n"
"    stk::StkFrames& tick(stk::StkFrames& frames, unsigned int channel = 0) override;\r\n"
"\r\n"
"    int selectConvolutionIndex(float amplitude, float adsrValue);\r\n"
"    float freqSetup();\r\n"
"    void setPitchShift(float position);\r\n"
"\r\n"
"    stk::ADSR adsr;\r\n"
"\r\n"
"    // Brass synthesis variables\r\n"
"    stk::Brass brassHorn;\r\n"
"    float frequency;\r\n"
"\r\n"
"    float rmsLevel;\r\n"
"    float rmsAlpha;\r\n"
"\r\n"
"\r\n"
"    class WaveguideSynthesis : public juce::Component, juce::AudioSource\r\n"
"    {\r\n"
"    public:\r\n"
"\r\n"
"        WaveguideSynthesis();\r\n"
"        ~WaveguideSynthesis() override;\r\n"
"\r\n"
"\t\tvoid prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;\r\n"
"        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;\r\n"
"        void releaseResources() override;\r\n"
"\r\n"
"        void setupBodyResonances();\r\n"
"        void handleImpulseResponse(double sampleRate, int samplesPerBlock);\r\n"
"\r\n"
"        juce::AudioFormatReader* reader;\r\n"
"        juce::AudioFormatManager audioFormatManager;\r\n"
"        juce::AudioBuffer<float> iRs[11];\r\n"
"        juce::File irFiles[11];\r\n"
"\r\n"
"    private:\r\n"
"\r\n"
"\r\n"
"        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveguideSynthesis)\r\n"
"    };\r\n"
"\r\n"
"private:\r\n"
"\r\n"
"    float pitchShiftTarget;\r\n"
"    float maxDelay;\r\n"
"\r\n"
"    stk::Delay delayLine[2048];\r\n"
"    int delayLength;\r\n"
"    int readPtr;\r\n"
"    int writePtr;\r\n"
"\r\n"
"    float outputGain;\r\n"
"    float inputGain;\r\n"
"\r\n"
"    float lowestFrequency = 8.0f;\r\n"
"\r\n"
"    StylusEmulation gramoStylus;\r\n"
"\tWaveguideSynthesis waveguideSynthesis;\r\n"
"\r\n"
"    juce::dsp::Convolution convolution[11];\r\n"
"\r\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HornEmulation)\r\n"
"};\r\n"
"\r\n";

const char* HornEmulation_h = (const char*) temp_binary_data_21;

//================== SoundboxEmulation.cpp ==================
static const unsigned char temp_binary_data_22[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    SoundboxEmulation.cpp\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"SoundboxEmulation.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"SoundboxEmulation::SoundboxEmulation()\r\n"
"{\r\n"
"    // In your constructor, you should add any child components, and\r\n"
"    // initialise any special settings that your component needs.\r\n"
"\r\n"
"    vibratoFrequency = 5.925f;\r\n"
"    vibratoGain = 0.1f;\r\n"
"    vibratoPhase = 0.0f;\r\n"
"\r\n"
"    maxPressure = 0.05f;\r\n"
"    soundboxPressure = 0.0f;\r\n"
"    soundboxGain = 0.0f;\r\n"
"    noiseGain = 0.2f;\r\n"
"}\r\n"
"\r\n"
"SoundboxEmulation::~SoundboxEmulation()\r\n"
"{\r\n"
"}\r\n"
"\r\n"
"void SoundboxEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)\r\n"
"{\r\n"
"    vibratoEffect = configureVibrato(sampleRate);\r\n"
"}\r\n"
"\r\n"
"void SoundboxEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)\r\n"
"{\r\n"
"\t// This function is called by the host to fill the output buffer with audio data.\r\n"
"\r\n"
"    //vibratoMix = bufferToFill.buffer->\r\n"
"\r\n"
"        // Update breath pressure\r\n"
"    if (soundboxPressure < soundboxGain)\r\n"
"        soundboxPressure += 0.001f;\r\n"
"    if (soundboxPressure > soundboxGain)\r\n"
"        soundboxPressure = soundboxGain;\r\n"
"}\r\n"
"\r\n"
"void SoundboxEmulation::releaseResources()\r\n"
"{\r\n"
"\t// When playback stops, you can use this as an opportunity\r\n"
"\t// to free up any spare memory, etc.\r\n"
"\r\n"
"    vibratoPhase = 0.0f;\r\n"
"\r\n"
"\tsoundboxPressure = 0.0f;\r\n"
"}\r\n"
"\r\n"
"void SoundboxEmulation::startAirShift(float amplitude, float rate)\r\n"
"{\r\n"
"    soundboxGain = amplitude * maxPressure;\r\n"
"}\r\n"
"\r\n"
"float SoundboxEmulation::configureVibrato(double sampleRate)\r\n"
"{\r\n"
"    vibratoPhase += vibratoFrequency / sampleRate;\r\n"
"    if (vibratoPhase >= 1.0f) vibratoPhase -= 1.0f;\r\n"
"    return vibratoGain * std::sin(2.0f * std::numbers::pi * vibratoPhase);\r\n"
"}\r\n"
"\r\n"
"float SoundboxEmulation::generateNoise() const\r\n"
"{\r\n"
"    return noiseGain * (2.0f * rand() / static_cast<float>(RAND_MAX) - 1.0f);\r\n"
"}\r\n";

const char* SoundboxEmulation_cpp = (const char*) temp_binary_data_22;

//================== SoundboxEmulation.h ==================
static const unsigned char temp_binary_data_23[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    SoundboxEmulation.h\r\n"
"    Created: 18 May 2025 12:17:28pm\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#pragma once\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include <numbers>\r\n"
"\r\n"
"//==============================================================================\r\n"
"/*\r\n"
"*/\r\n"
"class SoundboxEmulation : public juce::Component, public juce::AudioSource\r\n"
"{\r\n"
"public:\r\n"
"    SoundboxEmulation();\r\n"
"    ~SoundboxEmulation() override;\r\n"
"\r\n"
"\tvoid prepareToPlay(int samplesPerBlockExpected, double sampleRate);\r\n"
"\tvoid getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);\r\n"
"\tvoid releaseResources() override;\r\n"
"\r\n"
"    float configureVibrato(double sampleRate);\r\n"
"\r\n"
"    void startAirShift(float amplitude, float rate = 0.1f);\r\n"
"\r\n"
"    float getsoundboxPressure() const { return soundboxPressure; }\r\n"
"    float generateNoise() const;\r\n"
"\r\n"
"    float getMaxPressure() const { return maxPressure; }\r\n"
"\r\n"
"private:\r\n"
"\r\n"
"    // soundbox air parameters\r\n"
"    float soundboxPressure;\r\n"
"    float soundboxGain;\r\n"
"    float soundboxTarget;\r\n"
"    float maxPressure;\r\n"
"\r\n"
"    float noiseGain;\r\n"
"\r\n"
"    float vibratoFrequency;\r\n"
"    float vibratoGain;\r\n"
"    float vibratoPhase;\r\n"
"    float vibratoEffect;\r\n"
"\tfloat vibratoMix;\r\n"
"\r\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundboxEmulation)\r\n"
"};\r\n";

const char* SoundboxEmulation_h = (const char*) temp_binary_data_23;

//================== StylusEmulation.cpp ==================
static const unsigned char temp_binary_data_24[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    StylusEmulation.cpp\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"#include \"StylusEmulation.h\"\r\n"
"\r\n"
"//==============================================================================\r\n"
"StylusEmulation::StylusEmulation()\r\n"
"{\r\n"
"    // In your constructor, you should add any child components, and\r\n"
"    // initialise any special settings that your component needs.\r\n"
"\r\n"
"    vinylTarget = 0.0f;\r\n"
"    stylusOutput = 0.0f;\r\n"
"    stylusFilterState[0] = 0.0f;\r\n"
"    stylusFilterState[1] = 0.0f;\r\n"
"}\r\n"
"\r\n"
"StylusEmulation::~StylusEmulation()\r\n"
"{\r\n"
"}\r\n"
"\r\n"
"void StylusEmulation::prepareToPlay(int samplesPerBlockExpected, double sampleRate)\r\n"
"{\r\n"
"}\r\n"
"\r\n"
"void StylusEmulation::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)\r\n"
"{\r\n"
"    // This function is called by the host to fill the output buffer with audio data.\r\n"
"}\r\n"
"\r\n"
"void StylusEmulation::releaseResources()\r\n"
"{\r\n"
"    // When playback stops, you can use this as an opportunity\r\n"
"    // to free up any spare memory, etc.\r\n"
"\r\n"
"\tfor (int i = 0; i <= 2; i++) stylusFilterState[1] = 0.0f;\r\n"
"}\r\n"
"\r\n"
"void StylusEmulation::paint (juce::Graphics& g)\r\n"
"{\r\n"
"\r\n"
"}\r\n"
"\r\n"
"void StylusEmulation::resized()\r\n"
"{\r\n"
"    // This method is where you should set the bounds of any child\r\n"
"    // components that your component contains...\r\n"
"}\r\n"
"\r\n"
"void StylusEmulation::processPressureDifference(float pressureDiff)\r\n"
"{\r\n"
"    float filterOutput = 0.7f * stylusFilterState[0] + 0.3f * pressureDiff;\r\n"
"    stylusFilterState[0] = filterOutput;\r\n"
"    stylusFilterState[1] = pressureDiff;\r\n"
"}";

const char* StylusEmulation_cpp = (const char*) temp_binary_data_24;

//================== StylusEmulation.h ==================
static const unsigned char temp_binary_data_25[] =
"/*\r\n"
"  ==============================================================================\r\n"
"\r\n"
"    StylusEmulation.h\r\n"
"    Created: 17 May 2025 6:50:05pm\r\n"
"    Author:  monty\r\n"
"\r\n"
"  ==============================================================================\r\n"
"*/\r\n"
"\r\n"
"#pragma once\r\n"
"\r\n"
"#include <JuceHeader.h>\r\n"
"\r\n"
"//==============================================================================\r\n"
"/*\r\n"
"*/\r\n"
"class StylusEmulation  : public juce::Component, public juce::AudioSource\r\n"
"{\r\n"
"public:\r\n"
"\r\n"
"    StylusEmulation();\r\n"
"    ~StylusEmulation() override;\r\n"
"\r\n"
"\tvoid prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;\r\n"
"\tvoid getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;\r\n"
"    void releaseResources() override;\r\n"
"\r\n"
"    void paint (juce::Graphics&) override;\r\n"
"    void resized() override;\r\n"
"\r\n"
"    void setVinyFilter(float frequency);\r\n"
"    void processPressureDifference(float pressureDiff);\r\n"
"    float getFilterOutput() const { return stylusFilterState[0]; }\r\n"
"\r\n"
"\r\n"
"private:\r\n"
"\r\n"
"    float vinylTarget;\r\n"
"    float stylusOutput;\r\n"
"    float stylusFilterState[2];\r\n"
"\r\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StylusEmulation)\r\n"
"};\r\n";

const char* StylusEmulation_h = (const char*) temp_binary_data_25;

//================== InfoButton.cpp ==================
static const unsigned char temp_binary_data_26[] =
"#include \"InfoButton.h\"\n"
"\n"
"InfoButton::InfoButton (juce::Colour colour)\n"
"{\n"
"    button.setButtonText (\"i\");\n"
"    button.addListener (this);\n"
"\n"
"    info_text.setColour (juce::Label::backgroundColourId, colour);\n"
"    info_text.setColour (juce::Label::outlineColourId, juce::Colours::white);\n"
"    info_text.setColour (juce::Label::textColourId, juce::Colours::lightgrey);\n"
"    info_text.setJustificationType (juce::Justification::centredLeft);\n"
"    info_text.setBorderSize (juce::BorderSize<int> (20, 70, 20, 70));\n"
"\n"
"    std::string info_string = \"\";\n"
"    info_string += ProjectInfo::companyName + std::string (\" \") + ProjectInfo::projectName + std::string (\" version \") + ProjectInfo::versionString + std::string (\"\\n\\n\");\n"
"    info_string += std::string (\"by Montague Whishaw\\n\\n\");\n"
"    info_string += std::string (\"Check out my other projects at https://github.com/MontagueWh\");\n"
"\n"
"    info_text.setText (info_string, juce::dontSendNotification);\n"
"}\n"
"\n"
"InfoButton::~InfoButton() {}\n"
"\n"
"void InfoButton::addToEditor (juce::AudioProcessorEditor* editor)\n"
"{\n"
"    editor->addAndMakeVisible (info_text);\n"
"    info_text.setVisible (false);\n"
"    editor->addAndMakeVisible (button);\n"
"}\n"
"\n"
"void InfoButton::buttonStateChanged (juce::Button* b)\n"
"{\n"
"    if (b == &button)\n"
"    {\n"
"        if (button.isOver())\n"
"        {\n"
"            info_text.setVisible (true);\n"
"        }\n"
"        else\n"
"        {\n"
"            info_text.setVisible (false);\n"
"        }\n"
"    }\n"
"}\n"
"\n"
"void InfoButton::buttonClicked (juce::Button* button)\n"
"{\n"
"}\n";

const char* InfoButton_cpp = (const char*) temp_binary_data_26;

//================== InfoButton.h ==================
static const unsigned char temp_binary_data_27[] =
"#pragma once\n"
"\n"
"#include <JuceHeader.h>\n"
"\n"
"// Use the info button class by\n"
"// 1) Create an InfoButton object\n"
"// 2) Make the button visible by  using the function addToEditor(this) from PluginEditor class\n"
"// 3) In resized() function set boundry of the public data members button and info_text\n"
"class InfoButton : public juce::Button::Listener\n"
"{\n"
"public:\n"
"    explicit InfoButton (juce::Colour colour);\n"
"    ~InfoButton();\n"
"    void addToEditor (juce::AudioProcessorEditor* editor);\n"
"    void buttonStateChanged (juce::Button* b) override;\n"
"    void buttonClicked (juce::Button* button) override;\n"
"    juce::TextButton button;\n"
"    juce::Label info_text;\n"
"};\n";

const char* InfoButton_h = (const char*) temp_binary_data_27;

//================== PluginProcessor.cpp ==================
static const unsigned char temp_binary_data_28[] =
"/*\n"
"  ==============================================================================\n"
"\n"
"    This file contains the basic framework code for a JUCE plugin processor.\n"
"\n"
"  ==============================================================================\n"
"*/\n"
"\n"
"#include \"PluginProcessor.h\" // Includes the header file for the plugin processor class.\n"
"#include \"PluginEditor.h\"    // Includes the header file for the plugin editor class.\n"
"\n"
"constexpr float BP_FREQ = 2950.0f; // Defines a constant for the band-pass filter frequency.\n"
"\n"
"//==============================================================================\n"
"// Constructor for the plugin processor class.\n"
"VirtualGramoAudioProcessor::VirtualGramoAudioProcessor()\n"
"#ifndef JucePlugin_PreferredChannelConfigurations\n"
"    : AudioProcessor(BusesProperties() // Initialises the audio processor with bus properties.\n"
"#if ! JucePlugin_IsMidiEffect\n"
"#if ! JucePlugin_IsSynth\n"
"        .withInput(\"Input\", juce::AudioChannelSet::discreteChannels(MAX_CHANNELS), true) // Adds the number of input busses\n"
"#endif\n"
"        .withOutput(\"Output\", juce::AudioChannelSet::discreteChannels(MAX_CHANNELS), true) // Adds the number of output busses\n"
"#endif\n"
"    ),\n"
"    apvts(*this, nullptr, \"Parameters\", createParameters()) // Initialises the AudioProcessorValueTreeState for parameter management.\n"
"#endif\n"
"{\n"
"\tgramoVoice.initaliseGramoVoice(); // Initialises the GramoVoice component.\n"
"}\n"
"\n"
"VirtualGramoAudioProcessor::~VirtualGramoAudioProcessor()\n"
"{\n"
"    // Destructor for the plugin processor class. Cleans up resources if necessary.\n"
"}\n"
"\n"
"//==============================================================================\n"
"// Returns the name of the plugin.\n"
"const juce::String VirtualGramoAudioProcessor::getName() const\n"
"{\n"
"    return JucePlugin_Name; // Uses the name defined in the JUCE plugin configuration.\n"
"}\n"
"\n"
"// Determines if the plugin accepts MIDI input.\n"
"bool VirtualGramoAudioProcessor::acceptsMidi() const\n"
"{\n"
"#if JucePlugin_WantsMidiInput\n"
"    return true; // Returns true if the plugin is configured to accept MIDI input.\n"
"#else\n"
"    return false; // Returns false otherwise.\n"
"#endif\n"
"}\n"
"\n"
"// Determines if the plugin produces MIDI output.\n"
"bool VirtualGramoAudioProcessor::producesMidi() const\n"
"{\n"
"#if JucePlugin_ProducesMidiOutput\n"
"    return true; // Returns true if the plugin is configured to produce MIDI output.\n"
"#else\n"
"    return false; // Returns false otherwise.\n"
"#endif\n"
"}\n"
"\n"
"// Determines if the plugin is a MIDI effect.\n"
"bool VirtualGramoAudioProcessor::isMidiEffect() const\n"
"{\n"
"#if JucePlugin_IsMidiEffect\n"
"    return true; // Returns true if the plugin is a MIDI effect.\n"
"#else\n"
"    return false; // Returns false otherwise.\n"
"#endif\n"
"}\n"
"\n"
"// Returns the tail length of the plugin in seconds.\n"
"double VirtualGramoAudioProcessor::getTailLengthSeconds() const\n"
"{\n"
"    return 0.0; // No tail length is defined for this plugin.\n"
"}\n"
"\n"
"// Returns the number of programs (presets) available in the plugin.\n"
"int VirtualGramoAudioProcessor::getNumPrograms()\n"
"{\n"
"    return 1; // At least one program is required, even if not implemented.\n"
"}\n"
"\n"
"// Returns the index of the current program.\n"
"int VirtualGramoAudioProcessor::getCurrentProgram()\n"
"{\n"
"    return 0; // Only one program is available, so the index is always 0.\n"
"}\n"
"\n"
"// Sets the current program (not implemented in this plugin).\n"
"void VirtualGramoAudioProcessor::setCurrentProgram(int /*index*/)\n"
"{\n"
"}\n"
"\n"
"// Returns the name of the program at the given index (not implemented).\n"
"const juce::String VirtualGramoAudioProcessor::getProgramName(int /*index*/)\n"
"{\n"
"    return {}; // Returns an empty string.\n"
"}\n"
"\n"
"// Changes the name of the program at the given index (not implemented).\n"
"void VirtualGramoAudioProcessor::changeProgramName(int /*index*/, const juce::String& /*newName*/)\n"
"{\n"
"}\n"
"\n"
"//==============================================================================\n"
"// Prepares the plugin for playback by initialising DSP components.\n"
"void VirtualGramoAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)\n"
"{\n"
"    // Sets up the processing specification for DSP components.\n"
"    juce::dsp::ProcessSpec spec = { sampleRate, static_cast<juce::uint32>(samplesPerBlock),\n"
"                                    static_cast<juce::uint32>(getMainBusNumOutputChannels()) };\n"
"\n"
"    PrepareAdditionalEffects(spec, sampleRate);\n"
"\n"
"\tgramoVoice.prepareToPlay(sampleRate, samplesPerBlock); // Prepares the GramoMain for playback.\n"
"}\n"
"\n"
"// Releases resources when playback stops.\n"
"void VirtualGramoAudioProcessor::releaseResources()\n"
"{\n"
"    // Frees up any resources or memory used during playback.\n"
"\n"
"\tgramoVoice.releaseResources(); // Releases resources for the GramoMain.\n"
"}\n"
"\n"
"#ifndef JucePlugin_PreferredChannelConfigurations\n"
"// Checks if the given bus layout is supported by the plugin.\n"
"bool VirtualGramoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const\n"
"{\n"
"#if JucePlugin_IsMidiEffect\n"
"    juce::ignoreUnused(layouts);\n"
"    return true; // MIDI effects support all layouts.\n"
"#else\n"
"    // Allow any valid output channel configuration\n"
"    const auto& outputSet = layouts.getMainOutputChannelSet();\n"
"\n"
"    // Ensure the layout is valid and not empty\n"
"    if (outputSet.isDisabled())\n"
"        return false;\n"
"\n"
"    // Ensures the input layout matches the output layout for non-synth plugins.\n"
"#if ! JucePlugin_IsSynth\n"
"    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())\n"
"        return false;\n"
"#endif\n"
"\n"
"    return true; // Layout is supported.\n"
"#endif\n"
"}\n"
"#endif\n"
"\n"
"// Processes audio and MIDI data for each block of samples.\n"
"void VirtualGramoAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)\n"
"{\n"
"    juce::ScopedNoDenormals noDenormals; // Ensures denormalized numbers are handled correctly.\n"
"    auto totalNumInputChannels = getTotalNumInputChannels(); // Gets the number of input channels.\n"
"    auto totalNumOutputChannels = getTotalNumOutputChannels(); // Gets the number of output channels.\n"
"\n"
"    mix.pushDrySamples(buffer); // Pushes the dry signal into the mix processor.\n"
"\n"
"    // Process the audio data through gramophone components.\n"
"    juce::AudioSourceChannelInfo info(&buffer, 0, buffer.getNumSamples()); // Creates an AudioSourceChannelInfo object for the buffer.\n"
"    gramoVoice.getNextAudioBlock(info); // Process the audio data through the GramoMain.\n"
"\n"
"    // Processes each sample in the buffer.\n"
"    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)\n"
"    {\n"
"        for (int channel = 0; channel < totalNumInputChannels; ++channel)\n"
"        {            \n"
"            ProcessCompressionAndTone(buffer, channel, sample);\n"
"        }\n"
"    }\n"
"\n"
"    // Wraps the buffer in an AudioBlock for further processing.\n"
"    auto block = juce::dsp::AudioBlock<float>(buffer);\n"
"    auto contextToUse = juce::dsp::ProcessContextReplacing<float>(block);\n"
"\n"
"    ProcessChorusEffect(contextToUse);\n"
"\n"
"    // Configures and applies the wet/dry mix.\n"
"    mix.setWetMixProportion(1.0f - apvts.getRawParameterValue(\"MIX\")->load());\n"
"    mix.mixWetSamples(block);\n"
"}\n"
"\n"
"//==============================================================================\n"
"// Indicates whether the plugin has an editor.\n"
"bool VirtualGramoAudioProcessor::hasEditor() const\n"
"{\n"
"    return true; // Returns true to indicate the plugin has a GUI editor.\n"
"}\n"
"\n"
"// Creates and returns the plugin editor.\n"
"juce::AudioProcessorEditor* VirtualGramoAudioProcessor::createEditor()\n"
"{\n"
"    return new VirtualGramoAudioProcessorEditor(*this); // Creates an instance of the editor.\n"
"}\n"
"\n"
"//==============================================================================\n"
"// Saves the plugin's state to a memory block.\n"
"void VirtualGramoAudioProcessor::getStateInformation(juce::MemoryBlock& destData)\n"
"{\n"
"    auto state = apvts.copyState(); // Copies the current state of the parameters.\n"
"    std::unique_ptr<juce::XmlElement> xml(state.createXml()); // Converts the state to XML.\n"
"    copyXmlToBinary(*xml, destData); // Saves the XML to the memory block.\n"
"}\n"
"\n"
"// Restores the plugin's state from a memory block.\n"
"void VirtualGramoAudioProcessor::setStateInformation(const void* data, int sizeInBytes)\n"
"{\n"
"    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes)); // Reads XML from the memory block.\n"
"\n"
"    if (xmlState.get() != nullptr)\n"
"        if (xmlState->hasTagName(apvts.state.getType())) // Checks if the XML tag matches the parameter tree type.\n"
"            apvts.replaceState(juce::ValueTree::fromXml(*xmlState)); // Restores the state from the XML.\n"
"}\n"
"\n"
"// Creates and returns the parameter layout for the plugin.\n"
"juce::AudioProcessorValueTreeState::ParameterLayout VirtualGramoAudioProcessor::createParameters()\n"
"{\n"
"    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters; // Stores the parameters.\n"
"\n"
"    createGramophoneParams(parameters);\n"
"\n"
"    // Adds parameters for compression, vibrato, tone, and mix.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"COMPRESS\", \"Compress\", 0.04f, 0.45f, 0.1f));\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VIBRATO\", \"Vibrato\", 0.0f, 0.33f, 0.01f));\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VIBRATO_RATE\", \"Rate\", 0.5f, 4.0f, 2.0f));\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"TONE\", \"Tone\", 320.1f, 4700.0f, 2000.0f));\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"MIX\", \"Mix\", 0.0f, 0.5f, 0.0f));\n"
"    return { parameters.begin(), parameters.end() }; // Returns the parameter layout.\n"
"}\n"
"\n"
"void VirtualGramoAudioProcessor::createGramophoneParams(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& parameters)\n"
"{\n"
"    // Adds parameters for vinyl sub-component\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"STYLUS_PRESSURE\", \"Stylus Pressure\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for stylus pressure.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VINYL_FILTER_FREQ\", \"Vinyl Filter Frequency\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for vinyl filter frequency.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"PITCH_SHIFT\", \"Pitch Shift\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for pitch shift.\n"
"\n"
"    // Adds parameters for soundbox sub-component\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"SOUNDBOX_PRESSURE\", \"Soundbox Pressure\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for soundbox pressure.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"NOISE_GAIN\", \"Noise Gain\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for noise gain.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VIBRATO_DEPTH\", \"Vibrato Depth\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for vibrato depth.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VIBRATO_RATE\", \"Vibrato Rate\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for vibrato rate.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VIBRATO_GAIN\", \"Vibrato Gain\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for vibrato gain.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"VIBRATO_MIX\", \"Vibrato Mix\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for vibrato mix.\n"
"\n"
"    // Adds parameters for horn sub-component\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"HORN_STIFFNESS\", \"Horn Stiffness\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for horn stiffness.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"HORN_DIAMETER\", \"Horn Diameter\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for horn diameter.\n"
"    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(\"HORN_LENGTH\", \"Horn Length\", 0.0f, 1.0f, 0.5f)); // Adds a parameter for horn length.\n"
"}\n"
"\n"
"//==============================================================================\n"
"// Factory function to create a new instance of the plugin.\n"
"juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()\n"
"{\n"
"    return new VirtualGramoAudioProcessor(); // Creates and returns a new instance of the processor.\n"
"}\n"
"\n"
"void VirtualGramoAudioProcessor::PrepareAdditionalEffects(juce::dsp::ProcessSpec& spec, double sampleRate)\n"
"{\n"
"    filterCount = getTotalNumOutputChannels(); // Sets the number of filters to the number of output channels.\n"
"    filters.resize(filterCount); // Resizes the filter vector to match the number of channels.\n"
"\n"
"    chorus.prepare(spec); // Prepares the chorus effect with the processing spec.\n"
"    mix.prepare(spec);    // Prepares the wet/dry mix processor.\n"
"\n"
"    // Retrieves the initial frequency value from the parameter tree.\n"
"    float frequency = apvts.getRawParameterValue(\"TONE\")->load();\n"
"\n"
"    // Prepares and configures the band-pass filters for each channel.\n"
"    for (int i = 0; i < filterCount; ++i)\n"
"    {\n"
"        filters[i].prepare(spec); // Prepares each filter with the processing spec.\n"
"        filters[i].coefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, frequency, 6.0f); // Sets the filter coefficients.\n"
"    }\n"
"}\n"
"\n"
"\n"
"void VirtualGramoAudioProcessor::ProcessChorusEffect(juce::dsp::ProcessContextReplacing<float>& contextToUse)\n"
"{\n"
"    // Configures and processes the chorus effect.\n"
"    chorus.setRate(apvts.getRawParameterValue(\"VIBRATO_RATE\")->load());\n"
"    chorus.setDepth(apvts.getRawParameterValue(\"VIBRATO\")->load());\n"
"    chorus.setCentreDelay(1.0f);\n"
"    chorus.setFeedback(0.0f);\n"
"    chorus.setMix(1.0f);\n"
"    chorus.process(contextToUse);\n"
"}\n"
"\n"
"void VirtualGramoAudioProcessor::ProcessCompressionAndTone(juce::AudioSampleBuffer& buffer, int channel, int sample)\n"
"{\n"
"    // Retrieves parameter values for compression and tone.\n"
"    float threshold = apvts.getRawParameterValue(\"COMPRESS\")->load();\n"
"    float frequency = apvts.getRawParameterValue(\"TONE\")->load();\n"
"\n"
"    // Apply compression\n"
"    float in = buffer.getReadPointer(channel)[sample];\n"
"    if (in >= threshold)\n"
"        buffer.getWritePointer(channel)[sample] = (in / 4) + (3 * threshold / 4);\n"
"    else if (in <= -threshold)\n"
"        buffer.getWritePointer(channel)[sample] = (in / 4) - (3 * threshold / 4);\n"
"\n"
"    // Applies makeup gain to the signal.\n"
"    *buffer.getWritePointer(channel, sample) *= 5.0f - (11.0f * threshold * threshold);\n"
"\n"
"    // Applies a band-pass filter to the signal for each channel\n"
"    for (int i = 0; i < filterCount; ++i)\n"
"    {\n"
"        filters[i].coefficients = *juce::dsp::IIR::Coefficients<float>::makeBandPass(getSampleRate(), frequency, 2.7f);\n"
"        buffer.getWritePointer(channel)[sample] = filters[i].processSample(buffer.getReadPointer(channel)[sample]);\n"
"    }\n"
"}";

const char* PluginProcessor_cpp = (const char*) temp_binary_data_28;

//================== PluginProcessor.h ==================
static const unsigned char temp_binary_data_29[] =
"/*\n"
"  ==============================================================================\n"
"\n"
"    This file contains the basic framework code for a JUCE plugin processor.\n"
"\n"
"  ==============================================================================\n"
"*/\n"
"\n"
"#pragma once // Ensures the file is included only once during compilation.\n"
"\n"
"#include <JuceHeader.h> // Includes the JUCE framework header file.\n"
"#include \"Data/GramoMain.h\"\n"
"\n"
"static const int MAX_CHANNELS = 64;\n"
"\n"
"//==============================================================================\n"
"/**\n"
" * The main audio processor class for the plugin.\n"
" * Inherits from juce::AudioProcessor and implements its virtual methods.\n"
" */\n"
"class VirtualGramoAudioProcessor : public juce::AudioProcessor\n"
"{\n"
"public:\n"
"\n"
"    //==============================================================================\n"
"    VirtualGramoAudioProcessor(); // Constructor for the audio processor.\n"
"    ~VirtualGramoAudioProcessor() override; // Destructor for the audio processor.\n"
"\n"
"    //==============================================================================\n"
"    void prepareToPlay(double sampleRate, int samplesPerBlock) override; // Prepares the processor for playback by initialising resources\n"
"    \n"
"    void releaseResources() override; // Releases resources when playback stops.\n"
"\n"
"#ifndef JucePlugin_PreferredChannelConfigurations\n"
"    bool isBusesLayoutSupported(const BusesLayout& layouts) const override; // Checks if the given bus layout is supported by the plugin\n"
"#endif\n"
"    \n"
"    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override; // Processes audio and MIDI data for each block of samples\n"
"\n"
"    //==============================================================================\n"
"    juce::AudioProcessorEditor* createEditor() override; // Creates and returns the plugin editor (GUI)\n"
"\n"
"    bool hasEditor() const override; // Indicates whether the plugin has an editor (GUI)\n"
"\n"
"    //==============================================================================\n"
"    const juce::String getName() const override; // Returns the name of the plugin\n"
"    \n"
"    bool acceptsMidi() const override; // Determines if the plugin accepts MIDI input\n"
"\tbool producesMidi() const override; // Determines if the plugin produces MIDI output\n"
"    bool isMidiEffect() const override; // Determines if the plugin is a MIDI effect\n"
"\n"
"    double getTailLengthSeconds() const override; // Returns the tail length of the plugin in seconds\n"
"\n"
"    //==============================================================================\n"
"    int getNumPrograms() override; // Returns the number of programs (presets) available in the plugin\n"
"    int getCurrentProgram() override; // Returns the index of the current program\n"
"    void setCurrentProgram(int index) override; // Sets the current program (preset) by index.\n"
"\n"
"    const juce::String getProgramName(int index) override; // Returns the name of the program (preset) at the given index\n"
"    void changeProgramName(int index, const juce::String& newName) override; // Changes the name of the program (preset) at the given index\n"
"\n"
"    //==============================================================================\n"
"    void getStateInformation(juce::MemoryBlock& destData) override; // Saves the plugin's state to a memory block\n"
"\n"
"    void setStateInformation(const void* data, int sizeInBytes) override; // Restores the plugin's state from a memory block\n"
"\n"
"    juce::AudioProcessorValueTreeState apvts; // Manages the plugin's parameters using a value tree state.\n"
"\n"
"\n"
"    void PrepareAdditionalEffects(juce::dsp::ProcessSpec& spec, double sampleRate);\n"
"    void ProcessChorusEffect(juce::dsp::ProcessContextReplacing<float>& contextToUse);\n"
"    void ProcessCompressionAndTone(juce::AudioSampleBuffer& buffer, int channel, int sample);\n"
"\n"
"    GramoMain& gramoVoice; // Instance of the GramoMain class for audio processing.\n"
"\n"
"private:\n"
"\n"
"\t//==============================================================================\n"
"    // Creates and returns the parameter layout for the plugin.\n"
"    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();\n"
"\n"
"    void createGramophoneParams(std::vector<std::unique_ptr<juce::RangedAudioParameter>>& parameters);\n"
"\n"
"    // DSP components used in the plugin.\n"
"    juce::dsp::Chorus<float> chorus; // Chorus effect processor.\n"
"    int filterCount;\n"
"    std::vector<juce::dsp::IIR::Filter<float>> filters;\n"
"    juce::dsp::DryWetMixer<float> mix; // Wet/dry mix processor.\n"
"\n"
"    //==============================================================================\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualGramoAudioProcessor)\n"
"        // Macro to prevent copying and enable leak detection for the class.\n"
"};";

const char* PluginProcessor_h = (const char*) temp_binary_data_29;

//================== PluginEditor.cpp ==================
static const unsigned char temp_binary_data_30[] =
"/*\n"
"  ==============================================================================\n"
"\n"
"    This file contains the basic framework code for a JUCE plugin editor.\n"
"\n"
"  ==============================================================================\n"
"*/\n"
"\n"
"#include \"PluginEditor.h\" // Includes the header file for the plugin editor.\n"
"#include \"PluginProcessor.h\" // Includes the header file for the plugin processor.\n"
"\n"
"\n"
"constexpr float LINE_THICKNESS = 4.0f; // Defines the thickness of lines drawn in the editor.\n"
"\n"
"//==============================================================================\n"
"// Constructor for the plugin editor.\n"
"VirtualGramoAudioProcessorEditor::VirtualGramoAudioProcessorEditor(VirtualGramoAudioProcessor& p)\n"
"   : AudioProcessorEditor(&p), audioProcessor(p), gramoVoice(p.gramoVoice), info_button_(juce::Colours::darkgrey)\n"
"{\n"
"    constexpr int TEXT_BOX_SIZE = 25; // Defines the size of the text box for sliders.\n"
"\n"
"    additionalEffectsParamsSetup(TEXT_BOX_SIZE);\n"
"    wetDryParamSetup(TEXT_BOX_SIZE);\n"
"    gramoParamSetup();\n"
"\n"
"    // Adds the info button to the editor.\n"
"    info_button_.addToEditor(this);\n"
"\n"
"\t//addAndMakeVisible(gramoModelLoader); // Adds the model loader to the editor.\n"
"\n"
"    setSize(1500, 1500); // Sets the initial size of the editor window.\n"
"\tsetResizable(true, true);\n"
"}\n"
"\n"
"void VirtualGramoAudioProcessorEditor::gramoParamSetup()\n"
"{\n"
"    gramoVoice.initaliseGramoVoice(); // Initialise the gramophone component.\n"
"\n"
"    // Sets up the stylus parameters.\n"
"    gramoVoice.stylusPressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"STYLUS_PRESSURE\", gramoVoice.stylusPressureParam); // Attach the stylus pressure slider to the parameter tree.\n"
"    gramoVoice.vinylFilterFreqAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VINYL_FILTER_FREQ\", gramoVoice.vinylFilterFreqParam); // Attach the vinyl filter frequency slider to the parameter "
"tree.\n"
"    gramoVoice.pitchShiftAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"PITCH_SHIFT\", gramoVoice.pitchShiftParam); // Attach the pitch shift slider to the parameter tree.\n"
"\n"
"    // Sets up the soundbox parameters.\n"
"    gramoVoice.soundboxPressureAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"SOUNDBOX_PRESSURE\", gramoVoice.soundboxPressureParam); // Attach the soundbox pressure slider to the parameter tre"
"e.\n"
"    gramoVoice.noiseGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"NOISE_GAIN\", gramoVoice.noiseGainParam); // Attach the noise gain slider to the parameter tree.\n"
"    gramoVoice.vibratoDepthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VIBRATO_DEPTH\", gramoVoice.vibratoDepthParam); // Attach the vibrato depth slider to the parameter tree.\n"
"    gramoVoice.vibratoRateAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VIBRATO_RATE\", gramoVoice.vibratoRateParam); // Attach the vibrato frequency slider to the parameter tree.\n"
"    gramoVoice.vibratoGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VIBRATO_GAIN\", gramoVoice.vibratoGainParam); // Attach the vibrato gain slider to the parameter tree.\n"
"    gramoVoice.vibratoMixAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VIBRATO_MIX\", gramoVoice.vibratoMixParam); // Attach the vibrato mix slider to the parameter tree.\n"
"\n"
"    // Sets up the horn parameters.\n"
"    gramoVoice.hornStiffnessAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"HORN_STIFFNESS\", gramoVoice.hornStiffnessParam); // Attach the horn stiffness slider to the parameter tree.\n"
"    gramoVoice.hornDiameterAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"HORN_DIAMETER\", gramoVoice.hornDiameterParam); // Attach the horn diameter slider to the parameter tree.\n"
"    gramoVoice.hornLengthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"HORN_LENGTH\", gramoVoice.hornLengthParam); // Attach the horn length slider to the parameter tree.\n"
"\n"
"\taddAndMakeVisible(gramoVoice); // Makes the GramoVoice component visible in the editor.\n"
"}\n"
"\n"
"// Destructor for the plugin editor.\n"
"VirtualGramoAudioProcessorEditor::~VirtualGramoAudioProcessorEditor()\n"
"{\n"
"}\n"
"\n"
"//==============================================================================\n"
"// Paints the editor's GUI components.\n"
"void VirtualGramoAudioProcessorEditor::paint(juce::Graphics& g)\n"
"{\n"
"    // (Our component is opaque, so we must completely fill the background with a solid colour)\n"
"    g.fillAll(juce::Colours::beige);\n"
"\n"
"    g.setColour(juce::Colour(0xff123456));\n"
"    g.setFont(40.0f);\n"
"    g.drawFittedText(\"Virtual Gramophone\", getLocalBounds(), juce::Justification::centredTop, 1);\n"
"\n"
"    setupSections();\n"
"\n"
"    g.setFont(18.0f);\n"
"    g.drawFittedText(\"TONE\", toneTextSection, juce::Justification::left, 1);\n"
"    g.drawFittedText(\"VIBE\", vibratoTextSection, juce::Justification::left, 1);\n"
"    g.drawFittedText(\"DRY\", wetDryTextSection, juce::Justification::left, 1);\n"
"\n"
"\tgramoVoice.paint(g); // Calls the paint method of the GramoVoice instance to draw its components.\n"
"}\n"
"\n"
"// Converts a slider's value to an alpha (transparency) value.\n"
"float VirtualGramoAudioProcessorEditor::sliderToAplhaValue(juce::Slider& slider)\n"
"{\n"
"    double range = (slider.getMaximum() - slider.getMinimum());\n"
"    return static_cast<float>((slider.getValue() - slider.getMinimum()) / range);\n"
"}\n"
"\n"
"// Handles resizing and layout of GUI components.\n"
"void VirtualGramoAudioProcessorEditor::resized()\n"
"{\n"
"    info_button_.button.setBounds(getWidth() - 35, 10, 20, 20); // Positions the info button.\n"
"    info_button_.info_text.setBounds(30, 50, getWidth() - 60, getHeight() - 100); // Positions the info text.\n"
"    setupSections(); // Updates the layout sections.\n"
"    compressThreshParam.setBounds(compressSection); // Positions the compression slider.\n"
"    toneParam.setBounds(toneSection); // Positions the tone slider.\n"
"    vibratoDepthParam.setBounds(vibratoDepthSection); // Positions the vibrato slider.\n"
"    vibratoRateParam.setBounds(vibratoRateSection); // Positions the vibrato rate slider.\n"
"    wetDryParam.setBounds(wetDrySection); // Positions the mix slider.\n"
"\n"
"\tgramoVoice.resized(); // Calls the resized method of the GramoVoice instance to update its layout.\n"
"}\n"
"\n"
"// Sets up the layout sections for the GUI.\n"
"void VirtualGramoAudioProcessorEditor::setupSections()\n"
"{\n"
"    juce::Rectangle<int> r = getLocalBounds(); // Gets the bounds of the editor.\n"
"    topSection = r.removeFromTop(50); // Allocates the top section.\n"
"\n"
"    juce::Rectangle<int> interfaceSection = r; // Remaining area for the interface.\n"
"    int sectionHeight = interfaceSection.getHeight() / 4; // Divides the interface into four sections.\n"
"    constexpr int textSectionWidth = 40; // Width for the text labels.\n"
"\n"
"    // Allocates sections for sliders and their labels.\n"
"    compressSection = interfaceSection.removeFromTop(sectionHeight);\n"
"    compressTextSection = compressSection.removeFromLeft(textSectionWidth);\n"
"\n"
"\ttoneSection = interfaceSection.removeFromTop(sectionHeight);\n"
"\ttoneTextSection = toneSection.removeFromLeft(textSectionWidth);\n"
"\n"
"\tvibratoDepthSection = interfaceSection.removeFromTop(sectionHeight);\n"
"    vibratoRateSection = interfaceSection.removeFromTop(sectionHeight);\n"
"\tvibratoTextSection = vibratoDepthSection.removeFromLeft(textSectionWidth);\n"
"\n"
"    wetDrySection = interfaceSection;\n"
"    wetDrySection = interfaceSection.removeFromTop(textSectionWidth);\n"
"}\n"
"\n"
"void VirtualGramoAudioProcessorEditor::additionalEffectsParamsSetup(const int TEXT_BOX_SIZE)\n"
"{\n"
"    // Sets up the compression slider.\n"
"    compressThreshParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); // Rotary slider style.\n"
"    compressThreshParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE); // No text box for the slider.\n"
"    compressThreshParam.addListener(this); // Adds this editor as a listener for slider changes.\n"
"    addAndMakeVisible(compressThreshParam); // Makes the slider visible in the editor.\n"
"\n"
"    // Links the compression slider to the \"COMPRESS\" parameter in the processor's parameter tree.\n"
"    compressThreshAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"COMPRESS\", compressThreshParam);\n"
"\n"
"    // Sets up the tone slider.\n"
"    toneParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);\n"
"    toneParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);\n"
"    toneParam.addListener(this);\n"
"    addAndMakeVisible(toneParam);\n"
"    toneAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"TONE\", toneParam);\n"
"\n"
"    // Sets up the vibrato slider.\n"
"    vibratoDepthParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);\n"
"    vibratoDepthParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);\n"
"    vibratoDepthParam.addListener(this);\n"
"    addAndMakeVisible(vibratoDepthParam);\n"
"    vibratoDepthAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VIBRATO_DEPTH\", vibratoDepthParam);\n"
"\n"
"    // Sets up the vibrato rate slider.\n"
"    vibratoRateParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);\n"
"    vibratoRateParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);\n"
"    vibratoRateParam.addListener(this);\n"
"    addAndMakeVisible(vibratoRateParam);\n"
"    vibratoRateAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"VIBRATO_RATE\", vibratoRateParam);\n"
"}\n"
"void VirtualGramoAudioProcessorEditor::wetDryParamSetup(const int TEXT_BOX_SIZE)\n"
"{\n"
"    // Sets up the mix slider.\n"
"    wetDryParam.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);\n"
"    wetDryParam.setTextBoxStyle(juce::Slider::NoTextBox, true, TEXT_BOX_SIZE, TEXT_BOX_SIZE);\n"
"    wetDryParam.addListener(this);\n"
"    addAndMakeVisible(wetDryParam);\n"
"    wetDryAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, \"MIX\", wetDryParam);\n"
"}\n"
"\n"
"// Callback for when a slider's value changes.\n"
"void VirtualGramoAudioProcessorEditor::sliderValueChanged(juce::Slider* /*slider*/)\n"
"{\n"
"    repaint(); // Repaints the editor to reflect the updated slider value.\n"
"}";

const char* PluginEditor_cpp = (const char*) temp_binary_data_30;

//================== PluginEditor.h ==================
static const unsigned char temp_binary_data_31[] =
"/*\n"
"  ==============================================================================\n"
"\n"
"    This file contains the basic framework code for a JUCE plugin editor.\n"
"\n"
"  ==============================================================================\n"
"*/\n"
"\n"
"#pragma once // Ensures the file is included only once during compilation.\n"
"\n"
"#include \"PluginProcessor.h\" // Includes the header file for the plugin processor.\n"
"#include \"UI/InfoButton.h\"      // Includes the header file for the InfoButton class.\n"
"#include <JuceHeader.h>      // Includes the JUCE framework header file.\n"
"//#include <../Source/UI/GramoModelLoader.h>\n"
"#include \"Data/GramoMain.h\"\n"
"\n"
"\n"
"//==============================================================================\n"
"/**\n"
" * The main editor class for the plugin.\n"
" * Inherits from juce::AudioProcessorEditor and juce::Slider::Listener.\n"
" * Handles the GUI and user interactions for the plugin.\n"
" */\n"
"class VirtualGramoAudioProcessorEditor : public juce::AudioProcessorEditor,\n"
"    public juce::Slider::Listener\n"
"{\n"
"public:\n"
"    explicit VirtualGramoAudioProcessorEditor(VirtualGramoAudioProcessor&); // Constructor that takes a reference to the audio processor.\n"
"    void gramoParamSetup();\n"
"    void wetDryParamSetup(const int TEXT_BOX_SIZE);\n"
"    void additionalEffectsParamsSetup(const int TEXT_BOX_SIZE);\n"
"    ~VirtualGramoAudioProcessorEditor() override; // Destructor for the editor.\n"
"\n"
"    //==============================================================================\n"
"    void paint(juce::Graphics&) override; // Paints the editor's GUI components.\n"
"    void resized() override; // Handles resizing and layout of GUI components.\n"
"\n"
"\n"
"private:\n"
"    float sliderToAplhaValue(juce::Slider& slider); // Converts a slider's value to an alpha (transparency) value.\n"
"    void setupSections(); // Sets up the layout and sections of the GUI.\n"
"    void sliderValueChanged(juce::Slider* slider) override; // Callback for when a slider's value changes.\n"
"\n"
"    InfoButton info_button_; // Custom button for displaying information about the plugin.\n"
"\n"
"    // Type alias for a unique pointer to a SliderAttachment.\n"
"    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttatchmentPtr;\n"
"\n"
"    // Sliders for controlling various parameters of the plugin.\n"
"    juce::Slider compressThreshParam; // Slider for controlling the compression parameter.\n"
"    SliderAttatchmentPtr compressThreshAttach; // Attachment to link the compress slider to the parameter tree.\n"
"\n"
"    juce::Slider toneParam; // Slider for controlling the tone parameter.\n"
"    SliderAttatchmentPtr toneAttach; // Attachment to link the tone slider to the parameter tree.\n"
"\n"
"    juce::Slider vibratoDepthParam; // Slider for controlling the vibrato depth parameter.\n"
"    SliderAttatchmentPtr vibratoDepthAttach; // Attachment to link the vibrato slider to the parameter tree.\n"
"\n"
"    juce::Slider vibratoRateParam; // Slider for controlling the vibrato rate parameter.\n"
"    SliderAttatchmentPtr vibratoRateAttach; // Attachment to link the vibrato rate slider to the parameter tree.\n"
"\n"
"    juce::Slider wetDryParam; // Slider for controlling the wet/dry mix parameter.\n"
"    SliderAttatchmentPtr wetDryAttach; // Attachment to link the mix slider to the parameter tree.\n"
"\n"
"    // Rectangles defining sections of the GUI layout.\n"
"    juce::Rectangle<int> topSection; // Rectangle for the top section of the GUI.\n"
"\n"
"    juce::Rectangle<int> compressSection; // Rectangle for the compression slider section.\n"
"    juce::Rectangle<int> toneSection; // Rectangle for the tone slider section.\n"
"    juce::Rectangle<int> vibratoDepthSection; // Rectangle for the vibrato slider section.\n"
"    juce::Rectangle<int> vibratoRateSection; // Rectangle for the vibrato rate slider section.\n"
"    juce::Rectangle<int> wetDrySection; // Rectangle for the mix slider section.\n"
"\n"
"    juce::Rectangle<int> compressTextSection; // Rectangle for the compression text label section.\n"
"    juce::Rectangle<int> toneTextSection; // Rectangle for the tone text label section.\n"
"    juce::Rectangle<int> vibratoTextSection; // Rectangle for the vibrato text label section.\n"
"    juce::Rectangle<int> wetDryTextSection; // Rectangle for the mix text label section.\n"
"\n"
"    VirtualGramoAudioProcessor& audioProcessor; // Reference to the audio processor instance.\n"
"\tGramoMain& gramoVoice; // Reference to the GramoMain instance for audio processing.\n"
"\n"
"    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualGramoAudioProcessorEditor)\n"
"        // Macro to prevent copying and enable leak detection for the class.\n"
"};\n";

const char* PluginEditor_h = (const char*) temp_binary_data_31;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xf71599ce:  numBytes = 8109; return camera_h;
        case 0xae3b69db:  numBytes = 31287; return Importer_hpp;
        case 0xbfc55a96:  numBytes = 38946; return mesh_h;
        case 0x021c65f8:  numBytes = 33714; return postprocess_h;
        case 0x721f3175:  numBytes = 17564; return scene_h;
        case 0xcbf5e813:  numBytes = 3346; return Halfway_Attack_Loud_wav;
        case 0xc6d6dc51:  numBytes = 3746; return Attack_Initial_Loud_wav;
        case 0x8d13a3a4:  numBytes = 3342; return Decay_Loud_wav;
        case 0x1358521a:  numBytes = 2034; return Halfway_Release_Loud_wav;
        case 0x3c66c4b2:  numBytes = 1178; return Release_Initial_Loud_wav;
        case 0x4aa5f75b:  numBytes = 2934; return Sustain_Loud_wav;
        case 0x8f6bb94d:  numBytes = 2382; return Halfway_Attack_Quiet_wav;
        case 0xf0a94ccf:  numBytes = 2988; return Attack_Initial_Quiet_wav;
        case 0xf2056fdc:  numBytes = 2620; return Decay_Quiet_wav;
        case 0xdcdd4be9:  numBytes = 1978; return Release_Quiet_wav;
        case 0xe6bd9305:  numBytes = 2386; return Sustain_Quiet_wav;
        case 0xfcab5fa2:  numBytes = 1540; return CabinetEmulation_cpp;
        case 0x6d375227:  numBytes = 674; return CabinetEmulation_h;
        case 0x4e6a0f15:  numBytes = 12109; return GramoMain_cpp;
        case 0xf5b1425a:  numBytes = 7658; return GramoMain_h;
        case 0xf0869617:  numBytes = 12538; return HornEmulation_cpp;
        case 0x4be7a1dc:  numBytes = 2606; return HornEmulation_h;
        case 0x0e1b9dde:  numBytes = 2081; return SoundboxEmulation_cpp;
        case 0xdcd9ef63:  numBytes = 1401; return SoundboxEmulation_h;
        case 0xf393d128:  numBytes = 1659; return StylusEmulation_cpp;
        case 0x287a6d2d:  numBytes = 1159; return StylusEmulation_h;
        case 0x10b27a84:  numBytes = 1468; return InfoButton_cpp;
        case 0x8cabbd89:  numBytes = 643; return InfoButton_h;
        case 0x687677e3:  numBytes = 14421; return PluginProcessor_cpp;
        case 0xe1bd86a8:  numBytes = 4692; return PluginProcessor_h;
        case 0xd36ebf84:  numBytes = 10667; return PluginEditor_cpp;
        case 0xebb54289:  numBytes = 4511; return PluginEditor_h;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "camera_h",
    "Importer_hpp",
    "mesh_h",
    "postprocess_h",
    "scene_h",
    "Halfway_Attack_Loud_wav",
    "Attack_Initial_Loud_wav",
    "Decay_Loud_wav",
    "Halfway_Release_Loud_wav",
    "Release_Initial_Loud_wav",
    "Sustain_Loud_wav",
    "Halfway_Attack_Quiet_wav",
    "Attack_Initial_Quiet_wav",
    "Decay_Quiet_wav",
    "Release_Quiet_wav",
    "Sustain_Quiet_wav",
    "CabinetEmulation_cpp",
    "CabinetEmulation_h",
    "GramoMain_cpp",
    "GramoMain_h",
    "HornEmulation_cpp",
    "HornEmulation_h",
    "SoundboxEmulation_cpp",
    "SoundboxEmulation_h",
    "StylusEmulation_cpp",
    "StylusEmulation_h",
    "InfoButton_cpp",
    "InfoButton_h",
    "PluginProcessor_cpp",
    "PluginProcessor_h",
    "PluginEditor_cpp",
    "PluginEditor_h"
};

const char* originalFilenames[] =
{
    "camera.h",
    "Importer.hpp",
    "mesh.h",
    "postprocess.h",
    "scene.h",
    "Halfway Attack Loud.wav",
    "Attack Initial Loud.wav",
    "Decay Loud.wav",
    "Halfway Release Loud.wav",
    "Release Initial Loud.wav",
    "Sustain Loud.wav",
    "Halfway Attack Quiet.wav",
    "Attack Initial Quiet.wav",
    "Decay Quiet.wav",
    "Release Quiet.wav",
    "Sustain Quiet.wav",
    "CabinetEmulation.cpp",
    "CabinetEmulation.h",
    "GramoMain.cpp",
    "GramoMain.h",
    "HornEmulation.cpp",
    "HornEmulation.h",
    "SoundboxEmulation.cpp",
    "SoundboxEmulation.h",
    "StylusEmulation.cpp",
    "StylusEmulation.h",
    "InfoButton.cpp",
    "InfoButton.h",
    "PluginProcessor.cpp",
    "PluginProcessor.h",
    "PluginEditor.cpp",
    "PluginEditor.h"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}

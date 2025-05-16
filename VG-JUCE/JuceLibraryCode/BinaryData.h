/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Halfway_Attack_Loud_wav;
    const int            Halfway_Attack_Loud_wavSize = 3346;

    extern const char*   Attack_Initial_Loud_wav;
    const int            Attack_Initial_Loud_wavSize = 3746;

    extern const char*   Decay_Loud_wav;
    const int            Decay_Loud_wavSize = 3342;

    extern const char*   Halfway_Release_Loud_wav;
    const int            Halfway_Release_Loud_wavSize = 2034;

    extern const char*   Release_Initial_Loud_wav;
    const int            Release_Initial_Loud_wavSize = 1178;

    extern const char*   Sustain_Loud_wav;
    const int            Sustain_Loud_wavSize = 2934;

    extern const char*   Halfway_Attack_Quiet_wav;
    const int            Halfway_Attack_Quiet_wavSize = 2382;

    extern const char*   Attack_Initial_Quiet_wav;
    const int            Attack_Initial_Quiet_wavSize = 2988;

    extern const char*   Decay_Quiet_wav;
    const int            Decay_Quiet_wavSize = 2620;

    extern const char*   Release_Quiet_wav;
    const int            Release_Quiet_wavSize = 1978;

    extern const char*   Sustain_Quiet_wav;
    const int            Sustain_Quiet_wavSize = 2386;

    extern const char*   GramoVoice_cpp;
    const int            GramoVoice_cppSize = 6778;

    extern const char*   GramoVoice_h;
    const int            GramoVoice_hSize = 3208;

    extern const char*   GramoModelLoader_cpp;
    const int            GramoModelLoader_cppSize = 7228;

    extern const char*   GramoModelLoader_h;
    const int            GramoModelLoader_hSize = 2921;

    extern const char*   GramoSuite_fbx;
    const int            GramoSuite_fbxSize = 22266768;

    extern const char*   InfoButton_cpp;
    const int            InfoButton_cppSize = 1468;

    extern const char*   InfoButton_h;
    const int            InfoButton_hSize = 643;

    extern const char*   PluginProcessor_cpp;
    const int            PluginProcessor_cppSize = 11846;

    extern const char*   PluginProcessor_h;
    const int            PluginProcessor_hSize = 4658;

    extern const char*   PluginEditor_cpp;
    const int            PluginEditor_cppSize = 9390;

    extern const char*   PluginEditor_h;
    const int            PluginEditor_hSize = 5864;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 22;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}

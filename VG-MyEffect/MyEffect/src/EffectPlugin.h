//
//  EffectPlugin.h
//  MyEffect Plugin Header File
//
//  Used to declare objects and data structures used by the plugin.
//

#pragma once

#include "apdi/Plugin.h"
#include "apdi/Helpers.h"
using namespace APDI;

#include "EffectExtra.h"

const float STYLUS_MASS = 0.000001f; // kilograms
const float STYLUS_DAMPING_COEFFICIENT = 0.005f; // damping coefficient
const float STIFFNESS_COEFFICIENT = 1000.f; // Springiness of the stylus's suspension
const float STYLUS_TO_VINYL_COEFFICIENT = 0.02f; // Friction between stylus and vinyl
const float STYLUS_ACCELERATION_FACTOR = 9.81f; // Acceleration due to gravity in m/s^2
const float STYLUS_MASS_TO_FORCE_FACTOR = STYLUS_ACCELERATION_FACTOR / 1000.f; // Convert grams to force in Newtons

class MyEffect : public APDI::Effect
{
public:
    MyEffect(const Parameters& parameters, const Presets& presets); // constructor (initialise variables, etc.)
    ~MyEffect();                                                    // destructor (clean up, free memory, etc.)

    void setSampleRate(float sampleRate) { stk::Stk::setSampleRate(sampleRate); }
    float getSampleRate() const { return stk::Stk::sampleRate(); };

    //void stylusAndVinylEmulate(float fDiameterCoeff, float rpmCoeff, float trackingForceCoeff, float wobbleCoeff, float fTremoloDepth, float fTremoloRate, float fTremoloOnsetWobble, float sampleRate);

    void process(const float** inputBuffers, float** outputBuffers, int numSamples);

    void presetLoaded(int iPresetNum, const char* sPresetName);
    void optionChanged(int iOptionMenu, int iItem);
    void buttonPressed(int iButton);

private:
    // Declare shared member variables here

    //void calculateVariables(float diameter, float trackingForce, float RPM, float attack, float decay, float sustain, float release);
    //float fStylusFreq;

    //Dynamics dynamics;
    WowAndFlutter wowAndFlutter;
};

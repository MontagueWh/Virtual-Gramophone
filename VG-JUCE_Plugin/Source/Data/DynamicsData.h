/*
  ==============================================================================

    DynamicsData.h
    Created: 9 Jul 2025 10:18:22pm
    Author:  monty

  ==============================================================================
*/

#pragma once

#include <cmath>

class Dynamics
{
public:

    Dynamics() : iMeasuredLength(0), iMeasuredItems(0), fMax(0.f), fMaxOld(0) {}

    float fAmplitude = 0.f; // Current amplitude of the inputBuffer signal

    float peakDetector(float input, float sampleRate)
    {
        fAmplitude = fabs(input); // Get the absolute value of the inputBuffer signal

        iMeasuredLength = (int)(0.02 * sampleRate); // Calculate the length of the measurement window

        if (fAmplitude > fMax) fMax = fAmplitude; // Update the maximum amplitude if the current amplitude is greater

        iMeasuredItems++; // Increment the number of measured items

        float fOutput = 0;

        if (iMeasuredItems == iMeasuredLength)
        {
            fOutput = fMax; // Output the maximum amplitude after the measurement window is complete
            fMax = iMeasuredItems = 0; // Reset the maximum amplitude and measured items count
        }

        return fOutput; // Return the fTremOutput value
    }

private:
    int iMeasuredLength, iMeasuredItems;
    float fMax, fMaxOld;
};
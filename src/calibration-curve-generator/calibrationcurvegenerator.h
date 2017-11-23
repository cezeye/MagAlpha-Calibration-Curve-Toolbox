/****************************************************************************
 * MIT License
 *
 * Copyright (c) 2017 Mathieu Kaelin for Monolithic Power Systems
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ****************************************************************************/
#ifndef CALIBRATIONCURVEGENERATOR_H
#define CALIBRATIONCURVEGENERATOR_H

#if defined __cplusplus
extern "C" {
#endif

/**
 * @file calibrationcurvegenerator.h
 * @author Mathieu Kaelin
 * @date 2017/11/21
 * @brief Functions to extract the harmoncis from the measured data.
 *
 * @see https://www.monolithicpower.com/
 * @see http://sensors.monolithicpower.com/
 */


/**
 * @brief Extract the harmonics from the measured angle values.
 *
 * compute the 4th first harmonics of the angle error based on the reference
 * angle (@p referenceAngleInDegree[]) and the measured sensor output in degree
 * (@p measuredAngleInDegree[]).
 * The results are provided through pointer input parameters (@p pH1, @p pH2
 * @p pH3, @p pH4, @p pPhi1, @p pPhi2, @p pPhi3 and @p pPhi4). This function also
 * provide the computed angle error in degree through @p angleErrorArrayInDegree[]
 * array.
 *
 * See below a function call example:
 * @code{.c}
 * //input paramaters
 * const unsigned int sizeAngleArray = 200;
 * float referenceAngleInDegree[sizeAngleArray];    //fill with ref angle
 * float measuredAngleInDegree[sizeAngleArray];     //fill with sensor angle
 *
 * //output parameters
 * float angleErrorArrayInDegree[sizeAngleArray];
 * float h1;
 * float h2;
 * float h3;
 * float h4;
 * float phi1;
 * float phi2;
 * float phi3;
 * float phi4;
 * extractAngleErrorHarmonics(  referenceAngleInDegree,
 *                              measuredAngleInDegree,
 *                              angleErrorArrayInDegree,
 *                              sizeAngleArray,
 *                              &h1,
 *                              &h2,
 *                              &h3,
 *                              &h4,
 *                              &phi1,
 *                              &phi2,
 *                              &phi3,
 *                              &phi4);
 * @endcode
 * @param referenceAngleInDegree[] Input array with the refereance angle set on the calibration setup.
 * @param measuredAngleInDegree[] Input array with the angle in degree measured by the sensor.
 * @param angleErrorArrayInDegree[] Output array with the computed angle error in degree.
 * @param sizeAngleArray size of the array provided to this function.
 * @param pH1 Pointer to H1 harmonic amplitude.
 * @param pH2 Pointer to H2 harmonic amplitude.
 * @param pH3 Pointer to H3 harmonic amplitude.
 * @param pH4 Pointer to H4 harmonic amplitude.
 * @param pPhi1 Pointer to Phi1 harmonic phase.
 * @param pPhi2 Pointer to Phi2 harmonic phase.
 * @param pPhi3 Pointer to Phi3 harmonic phase.
 * @param pPhi4 Pointer to Phi4 harmonic phase.
 * @return always return 0.
 */
unsigned char extractAngleErrorHarmonics(   float referenceAngleInDegree[],
                                            float measuredAngleInDegree[],
                                            float angleErrorArrayInDegree[],
                                            const unsigned int sizeAngleArray,
                                            float *pH1,
                                            float *pH2,
                                            float *pH3,
                                            float *pH4,
                                            float *pPhi1,
                                            float *pPhi2,
                                            float *pPhi3,
                                            float *pPhi4);


/**
 * @brief Generate the fitted curve
 *
 * of measured data based on the harmonics parameters
 * computed with the #extractAngleErrorHarmonics
 *
 * Generate the fitted curve of the input @p measuredAngleInDegree[] by using
 * the harmonics parameters @p pH1 - @p pH4 and @p pPhi1 - @p pPhi4 which have
 * been computed on #extractAngleErrorHarmonics.
 * The fitted curve (in degree) is provided through @p angleFittingArrayInDegree[]
 * array.
 * See below a function call example:
 * @code{.c}
 * //input paramaters
 * const unsigned int sizeAngleArray = 200;
 * float measuredAngleInDegree[sizeAngleArray]; //fill with sensor angle
 * //from extractAngleErrorHarmonics function
 * float h1;
 * float h2;
 * float h3;
 * float h4;
 * float phi1;
 * float phi2;
 * float phi3;
 * float phi4;
 * //output parameters
 * float angleFittingArray[sizeAngleArray];
 * getFittedCurve( measuredAngleInDegree, angleFittingArray, sizeAngleArray,
 *                 &h1, &h2, &h3, &h4, &phi1, &phi2, &phi3, &phi4);
 * @endcode
 * @param measuredAngleInDegree[] Input array with the angle in degree measured by the sensor.
 * @param angleFittingArrayInDegree[] Output array with the fitted curve of the angle error in degree.
 * @param sizeAngleArray size of the array provided to this function.
 * @param pH1 Pointer to H1 harmonic amplitude.
 * @param pH2 Pointer to H2 harmonic amplitude.
 * @param pH3 Pointer to H3 harmonic amplitude.
 * @param pH4 Pointer to H4 harmonic amplitude.
 * @param pPhi1 Pointer to Phi1 harmonic phase.
 * @param pPhi2 Pointer to Phi2 harmonic phase.
 * @param pPhi3 Pointer to Phi3 harmonic phase.
 * @param pPhi4 Pointer to Phi4 harmonic phase.
 * @return always return 0.
 */
unsigned char getFittedCurve(   float measuredAngleInDegree[],
                                float angleFittingArrayInDegree[],
                                const unsigned int sizeAngleArray,
                                float *pH1,
                                float *pH2,
                                float *pH3,
                                float *pH4,
                                float *pPhi1,
                                float *pPhi2,
                                float *pPhi3,
                                float *pPhi4);


/**
 * @brief Compute the harmonics parameters.
 *
 * Private function only used inside #extractAngleErrorHarmonics
 */
unsigned char getHarmonics(float angleErrorArrayInDegree[],
                           const unsigned int sizeAngleArray,
                           unsigned int harmonicOrder,
                           float *pHarmonicAmplitude,
                           float *pHarmonicPhase);


/**
 * @brief Compute the modula the same way MatLab does.
 *
 * Private function only used inside #extractAngleErrorHarmonics
 */
float modulo(float x, float y);

#if defined __cplusplus
}
#endif

#endif // CALIBRATIONCURVEGENERATOR_H

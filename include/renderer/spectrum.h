/** ! 
 * Header file for renderer spectrum
 * 
 * @file renderer/spectrum.h
 * 
 * @author Jacob Smith
 */

// Include guard
#pragma once

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <renderer/rtypedef.h>

// Enumeration definitions
enum spectrum_e 
{
    SPECTRUM_INVALID          = 0,
    SPECTRUM_CONSTANT         = 1,
    SPECTRUM_DENSELY_SAMPLED  = 2,
    SPECTRUM_PIECEWISE_LINEAR = 3,
    SPECTRUM_RGB_ALBEDO       = 4,
    SPECTRUM_RGB_UNBOUNDED    = 5,
    SPECTRUM_RGB_ILLUMINANT   = 6,
    SPECTRUM_BLACKBODY        = 7
};

// Type definitions
typedef int (*fn_spectrum_lambda)(const spectrum *const p_spectrum, float *p_lambda );
typedef int (*fn_spectrum_max_value)(const spectrum *const p_spectrum, float *p_lambda );

// Structure definitions
struct spectrum_s
{
    enum spectrum_e type;

    union 
    {
        struct
        {
            float constant;
        } constant;
        
        struct
        {
            /* data */
        } densely_sampled;
        
        struct
        {
            /* data */
        } piecewise_linear;
        
        struct
        {
            /* data */
        } rgb_albedo;
        
        struct
        {
            /* data */
        } rgb_unbounded;
        
        struct
        {
            /* data */
        } rgb_illuminant;
        
        struct
        {
            /* data */
        } blackbody;
        
        
    };
    
    fn_spectrum_lambda    pfn_lambda;
    fn_spectrum_max_value pfn_max;
};

// Function declarations

/** !
 * Construct a constant spectrum from a wavelength
 * 
 * @param p_spectrum return
 * @param constant   the constant wavelength
 * 
 * @return 1 on success, 0 on error
 */
int spectrum_constant_construct ( spectrum *const p_spectrum, const float constant );

/** !
 * Get the wavelength of a constant spectrum
 * 
 * @note this is the same as
 * 
 * @param p_spectrum the spectrum
 * @param p_lambda   return
 * 
 * @return 1 on success, 0 on error
 */
int spectrum_constant_lambda ( const spectrum *const p_spectrum, float *p_lambda );


#include <renderer/spectrum.h>

int spectrum_constant_construct ( spectrum *const p_spectrum, const float constant )
{
    
    // Argument check
    if ( p_spectrum == (void *) 0 ) goto no_spectrum;

    // Initialized data
    spectrum _spectrum = { 0 };

    // Populate the spectrum struct
    _spectrum = (spectrum)
    {
        .type     = SPECTRUM_CONSTANT,
        .pfn_lambda = &spectrum_constant_lambda,
        .pfn_max    = &spectrum_constant_lambda,
        .constant = 
        {
            .constant = constant
        }
    };

    // Return the struct to the caller
    memcpy(p_spectrum, &_spectrum, sizeof(spectrum));

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_spectrum:
                #ifndef NDEBUG
                    log_error("[renderer] [spectrum] Null pointer provided for oaraneter \"p_spectrum\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int spectrum_constant_lambda ( const spectrum *const p_spectrum, float *p_lambda )
{

    // Argument check
    if ( p_spectrum == (void *) 0 ) goto no_spectrum;
    if ( p_lambda   == (void *) 0 ) goto no_lambda;

    // Return the wavelength to the caller
    *p_lambda = p_spectrum->constant.constant;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_spectrum:
                #ifndef NDEBUG
                    log_error("[renderer] [spectrum] Null pointer provided for oaraneter \"p_spectrum\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_lambda:
                #ifndef NDEBUG
                    log_error("[renderer] [spectrum] Null pointer provided for oaraneter \"p_lambda\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}


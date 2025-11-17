#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (OPEN_LOOP,"ramfuncs")
struct duty_cycle OPEN_LOOP(double eta)
{
    struct duty_cycle etas;
    static int cont=0;

    if (cont==1600){cont=0;}
    etas.eta_a=sin(cont*0.015707963267948966)*eta;
    etas.eta_b=sin(cont*0.015707963267948966-2.094395102393195492)*eta;
    etas.eta_c=sin(cont*0.015707963267948966+2.094395102393195492)*eta;
    cont++;
/*
    // Saturation
    if (etas.eta_a > 0.95) {etas.eta_a = 0.95;}
    if (etas.eta_a < -0.95) {etas.eta_a = -0.95;}
    if (etas.eta_b > 0.95) {etas.eta_b = 0.95;}
    if (etas.eta_b < -0.95) {etas.eta_b = -0.95;}
    if (etas.eta_c > 0.95) {etas.eta_c = 0.95;}
    if (etas.eta_c < -0.95) {etas.eta_c = -0.95;}
*/
    // Return structure
    return etas;
}

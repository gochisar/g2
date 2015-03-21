/*
 * coolant.h - coolant driver
 * This file is part of the TinyG project
 *
 * Copyright (c) 2015 Alden S. Hart, Jr.
 *
 * This file ("the software") is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2 as published by the
 * Free Software Foundation. You should have received a copy of the GNU General Public
 * License, version 2 along with the software.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, you may use this file as part of a software library without
 * restriction. Specifically, if other files instantiate templates or use macros or
 * inline functions from this file, or you compile this file and link it with  other
 * files to produce an executable, this file does not by itself cause the resulting
 * executable to be covered by the GNU General Public License. This exception does not
 * however invalidate any other reasons why the executable file might be covered by the
 * GNU General Public License.
 *
 * THE SOFTWARE IS DISTRIBUTED IN THE HOPE THAT IT WILL BE USEFUL, BUT WITHOUT ANY
 * WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef COOLANT_H_ONCE
#define COOLANT_H_ONCE

typedef enum {				        // spindle state settings (See hardware.h for bit settings)
    COOLANT_OFF = 0,
    COOLANT_ON,
} cmCoolantState;

typedef enum {
    COOLANT_ACTIVE_LOW = 0,
    COOLANT_ACTIVE_HIGH
} cmCoolantPolarity;

typedef enum {
    COOLANT_NORMAL = 0,
    COOLANT_PAUSE,
} cmCoolantPause;

/*
 * Coolant control structure
 */

typedef struct cmCoolatSingleton {

    cmCoolantPause pause_on_hold;       // set to COOLANT_PAUSE to pause coolant on feedhold

    cmCoolantPolarity mist_polarity;    // 0=active low, 1=active high
	cmCoolantState mist_state;          // COOLANT_ON = mist on (M7), COOLANT_OFF = off (M9)
    cmCoolantPause mist_pause;          // pause state - applies to above states

    cmCoolantPolarity flood_polarity;   // 0=active low, 1=active high
	cmCoolantState flood_state;         // COOLANT_ON = flood on (M8), COOLANT_OFF = off (M9)
    cmCoolantPause flood_pause;         // pause state - applies to above states

} cmCoolantSingleton_t;
extern cmCoolantSingleton_t coolant;

/*
 * Global Scope Functions
 */

void coolant_init();
void coolant_reset();

stat_t cm_mist_coolant_control(uint8_t mist_state); 			// M7
stat_t cm_flood_coolant_control(uint8_t flood_state);			// M8, M9
void cm_coolant_off_immediate(void);

/*--- text_mode support functions ---*/

#ifdef __TEXT_MODE

    void cm_print_cph(nvObj_t *nv);     // coolant pause on hold
    void cm_print_cpm(nvObj_t *nv);     // coolant polarity mist
    void cm_print_cpf(nvObj_t *nv);     // coolant polarity flood
    void cm_print_cm(nvObj_t *nv);     // report mist coolant state
    void cm_print_cf(nvObj_t *nv);     // report flood coolant state

#else

    #define cm_print_cph tx_print_stub
    #define cm_print_cpm tx_print_stub
    #define cm_print_cpf tx_print_stub
    #define cm_print_cm tx_print_stub
    #define cm_print_cf tx_print_stub

#endif // __TEXT_MODE

#endif	// End of include guard: COOLANT_H_ONCE

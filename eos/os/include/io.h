/*
 * io.h
 *
 * Created: 8/31/2015 9:23:50 PM
 *  Author: Mihai
 */ 


#ifndef IO_H_
#define IO_H_
#include "io_driver.h"
/************************************************************************/
/* \defgroup io															*/
/* Interface exposed to applications								    */
/* @{                                                                   */
/************************************************************************/

/************************************************************************/
/* write                                                                */
/* \param[in] BYTE desc IO descriptor                                   */
/* \param[in] P_UBYTE addr address                                      */
/* \param[in] UDWORD data data                                          */
/* \param[out] void                                                     */
/************************************************************************/
_PUBLIC inline void write(BYTE desc,volatile P_UBYTE addr,UDWORD data)
{
	(*ops[desc].op.io_write)(addr,data);		
}

/************************************************************************/
/* read                                                                 */
/* \param[in] BYTE desc IO descriptor                                   */
/* \param[in] P_UBYTE addr address                                      */
/* \param[in] UBYTE no_of_blocks no of bytes to be read                 */
/* \param[out] UDWORD read data                                         */
/************************************************************************/
_PUBLIC inline UDWORD read(BYTE desc,volatile P_UBYTE addr,UBYTE no_of_blocks)
{
	return (*ops[desc].op.io_read)(addr,no_of_blocks);
}

/************************************************************************/
/* seek                                                                 */
/* \param[in] BYTE desc IO descriptor                                   */
/* \param[in] UDWORD off_ offset                                        */
/* \param[in] E_Seek_Location loc seek type                             */
/* \param[out] WORD offset or -1                                        */
/************************************************************************/
_PUBLIC inline WORD seek(BYTE desc,UDWORD off_,E_Seek_Location loc)
{
	return ((ops[desc].op.dt==EEP_DRIVER)?((*ops[desc].op.special_fct.io_seek)(off_,loc)):-1);
}


_PUBLIC inline BYTE configure(BYTE desc,UBYTE dir,UBYTE pld,UBYTE ev)
{
	return ((ops[desc].op.dt==GPIO_DRIVER)?((*ops[desc].op.special_fct.io_conf)(dir,pld,ev)):-1);
	
}

/************************************************************************/
/* @} //end of app_register                                             */
/************************************************************************/

#endif /* IO_H_ */
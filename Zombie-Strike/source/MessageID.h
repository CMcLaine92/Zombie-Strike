/***************************************************************
|	File:		MessageID.h
|	Author:		Jason Bloomfield
|	Course:		N/A
|	Purpose:	MessageID enum declares the message enumerators
***************************************************************/

#ifndef MESSAGEID_H
#define MESSAGEID_H


/**************************************************************/
// MessageID enum
//	- enumerated list of message identifiers
enum class MessageID 
{ 
	MSG_UNKNOWN,
	MSG_DESTROY_OBJECT,
	MSG_CREATE_PSTL_BLT,
	MSG_CREATE_SHTGN_BLT,
	MSG_CREATE_ASSRFLE_BLT,
	MSG_CREATE_SNPR_BLT,
	MSG_CREATE_PUKE,
	MSG_CREATE_FLAME,
	MSG_CREATE_NADE,
	MSG_CREATE_SLOW_ZOMBIE,
	MSG_CREATE_FAST_ZOMBIE,
	MSG_CREATE_FAT_ZOMBIE,
	MSG_CREATE_EXPLODING_ZOMBIE,
	MSG_CREATE_TANK_ZOMBIE,
	MSG_CREATE_TURRET,
	MSG_CREATE_BLOOD,
	MSG_CREATE_TURRET_BLT,

};


#endif //MESSAGEID_H
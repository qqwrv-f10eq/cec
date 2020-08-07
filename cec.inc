
#if defined _inc_CEC_INCLUDE
	#undef _inc_CEC_INCLUDE
#endif

#if defined _CEC_INCLUDE_included
	#endinput
#endif
#define _CEC_INCLUDE_included


native CE_Convert(const input[], output[]);
native CE_Convert_Dialog(const input[], output[], style = 0);
native CE_CountTag(const input[]);
native CE_CountVowel(const input[]);

stock CE_SendClientMessage(playerid, color, const text[])
{
	#if defined _IO_included
	if (isPlayerAndroid(playerid) != 0) {
		return SendClientMessage(playerid, color, text);
	}
	#endif
	static str[144];
	str[0] = '\0';
	CE_Convert(text, str);
	return SendClientMessage(playerid, color, str);
}

stock CE_SendClientMessageToAll(color, const text[])
{
	static str[144];
	str[0] = '\0';
	CE_Convert(text, str);
	SendClientMessageToAll(color, str);
	return 1;
}

stock CE_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[]) {	
	#if defined _IO_included
	if (isPlayerAndroid(playerid) != 0) {
		return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
	}
	#endif
	static captionOutput[256], infoOutput[4096];
	captionOutput[0] = '\0';
	infoOutput[0] = '\0';
	CE_Convert_Dialog(caption, captionOutput, DIALOG_STYLE_MSGBOX);
	CE_Convert_Dialog(info, infoOutput, style);
	return ShowPlayerDialog(playerid, dialogid, style, captionOutput, infoOutput, button1, button2);
}	


stock Text3D:CE_Create3DTextLabel(const text[], color, Float:X, Float:Y, Float:Z, Float:DrawDistance, virtualworld = -1, testLOS = 0) {	
	static str[4096];
	str[0] = '\0';
	CE_Convert(text, str);
	new Text3D:ce_3dtextid = Create3DTextLabel(str, color, X, Y, Z, DrawDistance, virtualworld, testLOS);	
	return ce_3dtextid;
}

stock CE_Update3DTextLabelText(Text3D:id, color, const text[]) {
	static str[4096];
	str[0] = '\0';
	CE_Convert(text, str);
	Update3DTextLabelText(id, color, str);
}

#if defined _streamer_included
	#if defined CreateDynamic3DTextLabel
		stock STREAMER_TAG_3D_TEXT_LABEL:CE_CreateDynamic3DTextLabel(const text[], color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = -1, priority = 0)	
		{
			static str[4096];
			str[0] = '\0';
			CE_Convert(text, str);	
			new  STREAMER_TAG_3D_TEXT_LABEL:ce_3dtextid = CreateDynamic3DTextLabel(str, color, x, y, z, drawdistance, attachedplayer, attachedvehicle, testlos, worldid, interiorid, playerid, streamdistance, areaid, priority);	
			return ce_3dtextid;	
		}
	#endif
	#if defined UpdateDynamic3DTextLabelText
		stock CE_UpdateDynamic3DTextLabelText(STREAMER_TAG_3D_TEXT_LABEL:id, color, const text[])
		{	
			static str[4096];
			str[0] = '\0';
			CE_Convert(text, str);	
			UpdateDynamic3DTextLabelText(id, color, str);		
		}
	#endif
#endif

#if defined cec_auto	

	#if defined _streamer_included

		#if defined CreateDynamic3DTextLabel
			#if defined _ALS_CreateDyn3DTextLabel
				#undef CreateDynamic3DTextLabel
			#else	
				#define _ALS_CreateDyn3DTextLabel
			#endif
			#define CreateDynamic3DTextLabel CE_CreateDynamic3DTextLabel
		#endif

		#if defined UpdateDynamic3DTextLabelText
			#if defined _ALS_UpdateDyn3DTextLabelText
				#undef UpdateDynamic3DTextLabelText
			#else	
				#define _ALS_UpdateDyn3DTextLabelText
			#endif		
			#define UpdateDynamic3DTextLabelText CE_UpdateDynamic3DTextLabelText
		#endif
	#endif

	#if defined _ALS_Create3DTextLabel
		#undef Create3DTextLabel	
	#else	
		#define _ALS_Create3DTextLabel
	#endif	
	#define Create3DTextLabel CE_Create3DTextLabel

	#if defined _ALS_Update3DTextLabelText
		#undef Update3DTextLabelText	
	#else	
		#define _ALS_Update3DTextLabelText
	#endif	
	#define Update3DTextLabelText CE_Update3DTextLabelText

	#if defined _ALS_ShowPlayerDialog	
		#undef ShowPlayerDialog	
	#else	
		#define _ALS_ShowPlayerDialog	
	#endif	

	#define ShowPlayerDialog CE_ShowPlayerDialog	

	#if defined _ALS_SendClientMessage	
		#undef SendClientMessage	
	#else	
		#define _ALS_SendClientMessage	
	#endif	
	#define SendClientMessage CE_SendClientMessage


	#if defined _ALS_SendClientMessageToAll
		#undef SendClientMessageToAll
	#else	
		#define _ALS_SendClientMessageToAll
	#endif	
	#define SendClientMessageToAll CE_SendClientMessageToAll

 #endif
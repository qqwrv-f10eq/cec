/*

░█▀▀█ ▒█░▄▀ ▀▀█▀▀ ░█▀▀█ ▒█░▒█ 
▒█▄▄█ ▒█▀▄░ ░▒█░░ ▒█▄▄█ ▒█▀▀█ 
▒█░▒█ ▒█░▒█ ░▒█░░ ▒█░▒█ ▒█░▒█

 * Copyright (c) 2021, Aktah */

#if defined _CEC_INCLUDE_included
	#endinput
#endif
#define _CEC_INCLUDE_included

#if !defined PAWNRAKNET_INC_
	#error "Please include Pawn.RakNet"
#endif

#define	RPC_Create3DTextLabel	36
#define	RPC_DialogBox			61
#define	RPC_SendClientMessage	93

native CE_Convert(const input[], output[]);
native CE_Convert_Dialog(const input[], output[], style = 0);
native CE_CountTag(const input[]);
native CE_CountVowel(const input[]);

enum E_TEXT_STRUCT
{
	e_wLabelId,
	e_dwColor,
	Float:e_fPosX,
	Float:e_fPosY,
	Float:e_fPosZ,
	Float:e_fDrawDistance,
	e_byteTestLOS,
	e_playerId,
	e_vehicleId,
	e_szText[4096]
};

enum PR_Chat
{
	dwColor,
	szLength,
	szMessage[144]
};

enum E_DIALOG_STRUCT
{
	e_wDialogID, 			// UINT16
	e_bDialogStyle, 		// UINT8
	e_bTitleLength, 		// UINT8
	e_szTitle[64], 			// char
	e_bButton1Len, 			// UINT8
	e_szButton1[61],		// char
	e_bButton2Len, 			// UINT8
	e_szButton2[64], 		// char
	e_szInfo[4096]
};

#if defined _inc_y_hooks || defined _INC_y_hooks
	hook OnOutcomingRPC(playerid, rpcid, BitStream:bs)
#else
	public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
#endif
	{
		if(rpcid == RPC_SendClientMessage)
		{	
			#if defined _IO_included
			if(playerid != -1 && isPlayerAndroid(playerid) != 0)
				return 1;
			#endif

			static rpcData[PR_Chat];

			BS_ReadUint32(bs, rpcData[dwColor]);
			BS_ReadUint32(bs, rpcData[szLength]);
			BS_ReadString(bs, rpcData[szMessage], rpcData[szLength]);

			static str[144];
			str[0] = '\0';
			CE_Convert(rpcData[szMessage], str);
		
			BS_Reset(bs);

			BS_WriteUint32(bs, rpcData[dwColor]);
			BS_WriteUint32(bs, rpcData[szLength]);
			BS_WriteString(bs, str);

			PR_SendRPC(bs, playerid, rpcid);

			BS_ResetReadPointer(bs);
			BS_ResetWritePointer(bs);
			return 0;
		}
		else if(rpcid == RPC_DialogBox)
		{
			#if defined _IO_included
			if(playerid != -1 && isPlayerAndroid(playerid) != 0)
				return 1;
			#endif

			static dataDialog[E_DIALOG_STRUCT];
			BS_ReadValue(
		        bs,
		        PR_UINT16,  dataDialog[e_wDialogID],
				PR_UINT8, dataDialog[e_bDialogStyle],
				PR_UINT8, dataDialog[e_bTitleLength],
				PR_STRING, dataDialog[e_szTitle], dataDialog[e_bTitleLength],
				PR_UINT8, dataDialog[e_bButton1Len],
				PR_STRING, dataDialog[e_szButton1], dataDialog[e_bButton1Len],
				PR_UINT8, dataDialog[e_bButton2Len],
				PR_STRING, dataDialog[e_szButton2], dataDialog[e_bButton2Len],
				PR_CSTRING, dataDialog[e_szInfo], sizeof(dataDialog[e_szInfo])
		    );

			BS_Reset(bs);

			static captionOutput[256], infoOutput[4096];
			captionOutput[0] = '\0';
			infoOutput[0] = '\0';

			CE_Convert_Dialog(dataDialog[e_szTitle], captionOutput, DIALOG_STYLE_MSGBOX);
			CE_Convert_Dialog(dataDialog[e_szInfo], infoOutput, dataDialog[e_bDialogStyle]);

			BS_WriteValue(
			    bs,
			    PR_UINT16, dataDialog[e_wDialogID],
				PR_UINT8, dataDialog[e_bDialogStyle],
				PR_UINT8, dataDialog[e_bTitleLength],
				PR_STRING, captionOutput,
				PR_UINT8, dataDialog[e_bButton1Len],
				PR_STRING, dataDialog[e_szButton1], 
				PR_UINT8, dataDialog[e_bButton2Len],
				PR_STRING, dataDialog[e_szButton2], 
				PR_CSTRING, infoOutput
			);

			PR_SendRPC(bs, playerid, rpcid);

			BS_ResetReadPointer(bs);
			BS_ResetWritePointer(bs);
			return 0;
		}
		else if(rpcid == RPC_Create3DTextLabel)
		{
			#if defined _IO_included
			if(playerid != -1 && isPlayerAndroid(playerid) != 0)
				return 1;
			#endif

			static textData[E_TEXT_STRUCT];

			BS_ReadUint16(bs, textData[e_wLabelId]);
			BS_ReadUint32(bs, textData[e_dwColor]);
			BS_ReadFloat(bs,textData[e_fPosX]);
			BS_ReadFloat(bs,textData[e_fPosY]);
			BS_ReadFloat(bs,textData[e_fPosZ]);
			BS_ReadFloat(bs, textData[e_fDrawDistance]);
			BS_ReadUint8(bs, textData[e_byteTestLOS]);
			BS_ReadUint16(bs, textData[e_playerId]);
			BS_ReadUint16(bs, textData[e_vehicleId]);
			BS_ReadCompressedString(bs, textData[e_szText], sizeof(textData[e_szText]));

			static str[4096];
			str[0] = '\0';
			CE_Convert(textData[e_szText], str);

			BS_Reset(bs);

			BS_WriteUint16(bs, textData[e_wLabelId]);
			BS_WriteUint32(bs, textData[e_dwColor]);
			BS_WriteFloat(bs,textData[e_fPosX]);
			BS_WriteFloat(bs,textData[e_fPosY]);
			BS_WriteFloat(bs,textData[e_fPosZ]);
			BS_WriteFloat(bs, textData[e_fDrawDistance]);
			BS_WriteUint8(bs, textData[e_byteTestLOS]);
			BS_WriteUint16(bs, textData[e_playerId]);
			BS_WriteUint16(bs, textData[e_vehicleId]);
			BS_WriteCompressedString(bs, str);

			PR_SendRPC(bs, playerid, rpcid);

			BS_ResetReadPointer(bs);
			BS_ResetWritePointer(bs);
			return 0;
		}
		#if defined INCLUDE_OnOutcomingRPC
			return INCLUDE_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
		#else
			return 1;
		#endif
	}
#if !defined _inc_y_hooks && !defined _INC_y_hooks
	#if defined _ALS_OnOutcomingRPC
		#undef OnOutcomingRPC
	#else
		#define _ALS_OnOutcomingRPC
	#endif
	#define OnOutcomingRPC INCLUDE_OnOutcomingRPC
	#if defined INCLUDE_OnOutcomingRPC
		forward INCLUDE_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
	#endif
#endif

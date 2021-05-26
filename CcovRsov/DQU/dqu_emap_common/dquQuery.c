/************************************************************************
* �ļ���    ��  dsuQuery.c
* ��Ȩ˵��  ��  �������ؿƼ����޹�˾
* �汾��  	��  1.0
* ����ʱ��	��	2009.09.26
* ����  		������	
* ��������	��	dsu��ѯ�����ļ�  
* ʹ��ע��	�� 
* �޸ļ�¼	��	
************************************************************************/
#ifdef ZCAPP_VXWORKS_CODECONTROL
#include <vxWorks.h>
#endif /*End of ZCAPP_VXWORKS_CODECONTROL*/

#include "dquQuery.h"
#include "dquQueryExp.h"
#include "dquCbtcType.h"

static DSU_EMAP_STRU *qds_dsuEmapStru=NULL;
static DSU_STC_LIMIT_LINKIDX_STRU *qds_dsuLimitStcLinkIdx=NULL;

/*���õ�ǰ����Դ*/
UINT8 dquSetCurrentQueryDataSource(DSU_EMAP_STRU *pDsuEmapStru,DSU_STC_LIMIT_LINKIDX_STRU *pDsuLimitStcLinkIdx)
{
	UINT8 chReturnValue=0;             /*���ں�������ֵ*/
	UINT8 CbtcVersionType=0;

	CbtcVersionType = GetCbtcSysType();

	if (DQU_CBTC_FAO == CbtcVersionType)
	{
		if (NULL!=pDsuEmapStru)
		{
			qds_dsuEmapStru=pDsuEmapStru;
			chReturnValue=1;
		}
		else
		{
			chReturnValue=0;
		}
	} 
	else
	{
		if ((NULL!=pDsuEmapStru) && (NULL!=pDsuLimitStcLinkIdx))
		{
			qds_dsuEmapStru=pDsuEmapStru;
			qds_dsuLimitStcLinkIdx=pDsuLimitStcLinkIdx;
			chReturnValue=1;
		}
		else
		{
			chReturnValue=0;
		}
	}
	return chReturnValue;
}
/*
* ���������� �������з�����Ϣ�Լ�����״̬��Ϣ����ѯ�õ���ǰlink�����з��������link��
* ��������� UINT16 LinkId, ��ǰLink���
*            UCHAR Direction, ��ǰ����
*            UCHAR PointNum,  ������Ϣ����������
*            const POINT_STRU *pPointStru, ������Ϣ
* ��������� UINT16 *pLinkId����ǰLink������Link���
* ����ֵ��   1,��ѯ�ɹ�
*            0,��ѯʧ��,����������Ч������ʧ��
*		      	 0xFF,��·�յ㣬δ�ҵ�����
*             
*/
UINT8 dsuGetAdjacentLinkID(UINT16 LinkId, UCHAR Direction, UCHAR PointNum,const DQU_POINT_STATUS_STRU *pPointStru,UINT16 *pLinkId)
{
	return dsuGetAdjacentLinkIDExp(qds_dsuEmapStru,LinkId,Direction,PointNum,pPointStru,pLinkId);
}


/*
* ���������� ���ܺ��������ݵ�ǰλ�ã���λ���Լ�����ĵ�����Ϣ���õ���λ��.
���һ���㼴��ǰLnk��㣬������һ��Link�յ㣬�����뵱ǰ��pLODStru�����Link Id����
* ��������� const LOD_STRU * pLODStru, ��ǰλ��
*            INT32 Displacement,        λ�ƣ��з��ţ��������Ϊ����ʾ����ȡ��
*            UCHAR PointNum,            ��������
*            const POINT_STRU * pPointStru,  ������Ϣ
* ��������� LOD_STRU *pNewLODStru       ��λ��
* ����ֵ��   1,�ɹ�
*            0,ʧ��
*/
UCHAR dsuLODCalcu(const LOD_STRU *pLODStru, INT32 Displacement, UCHAR PointNum, const DQU_POINT_STATUS_STRU *pPointStru, LOD_STRU *pNewLODStru) 
{
	return dsuLODCalcuExp(qds_dsuEmapStru,pLODStru,Displacement, PointNum,pPointStru,pNewLODStru);
}

/*
*���ʽӿ�
* ���������� ��A��B����λ�õõ�����λ�ơ�
* ��������� const LOD_STRU * pLODAStru, A��λ��
*            const LOD_STRU * pLODBStru, B��λ��
*            UINT8 PointNum,             ��������
*            const POINT_STRU * pPointStru, ������Ϣ�ṹ��
* ��������� INT32 *Displacement��       ABλ�ƣ����з����������ű�ʾ����            
* ����ֵ��   1,�ɹ�
*            0,ʧ��
* ʹ��ע�⣺�Ͽ���෿��Ŀ:����B�ķ�����ң�ABλ����LinkB����Ϊ���գ�
            ������ͨ��Ŀ�������߼�����仯�㣬�㷨��Ϊ����A�ķ�����ң�ABλ����LinkA����Ϊ���ա�
* author:qxt 20170811
*/
UINT8 dsuDispCalcuByLOC(const LOD_STRU *pLODAStru, const LOD_STRU *pLODBStru, 
	UINT8 PointNum, const DQU_POINT_STATUS_STRU *pPointStru, INT32 *Displacement)
{
	return dsuDispCalcuByLOCExp(qds_dsuEmapStru, pLODAStru, pLODBStru,PointNum,pPointStru,Displacement);
}


/*
* �������ܣ�	�˺����Ĺ����ǲ�ѯ����λ�ü������link���С�
* ****************************************************************************************************
*        1          2              3                4                    5              6
*       -----��---------*--��--------------��--------------------��-------*-----��------------
*                       S                                                 E
*        ͼ����  ����Link�˵㡣*����ѯ�����λ�á�1��2��3...Linkʾ����
*        ��ͼ��ʾ��Link3��4Ϊ��������
*        �˴�������pLODEndStru���������ң�
*        S����pLODEndStru->Dir������ң��ҵ�E�򷵻سɹ����Ҳ����򷵻�ʧ�ܡ�
* ****************************************************************************************************
* ��ڲ�����	const LOD_STRU * pLODStartStru,	ʼ��λ��
*               const LOD_STRU * pLODEndStru	�ն�λ��
*               const UINT8 PointNum			������Ŀ 
*               const POINT_STRU * pPointStru	������Ϣ
* ���ڲ�����	UINT16 wLinkID[DSU_MAX_LINK_BETWEEN]				Link��������
*               UINT16 *wLinkNumber                             Link����
* ����ֵ��   	0,  ��ѯʧ��
*               1,  ��ѯ�ɹ�                                                             
* ʹ��ע�⣺    Ŀǰ������û�а������˵�Link Id��
*               ����Ҫ��������֮������γ����򣬷��򷵻�0
*/

UINT8 dsuGetLinkBtwLoc(const LOD_STRU *pLODStartStru, const LOD_STRU *pLODEndStru,
	UINT8 PointNum,const DQU_POINT_STATUS_STRU *pPointStru, 
	UINT16 wLinkID[DSU_MAX_LINK_BETWEEN], UINT16 *wLinkNumber)
{
	return dsuGetLinkBtwLocExp(qds_dsuEmapStru,pLODStartStru,pLODEndStru,PointNum,pPointStru,wLinkID,wLinkNumber);	
}


/*
* �������ܣ� �˺����Ĺ����ǽ��жϵ�ǰλ���Ƿ���ָ������Χ�ڡ�
* ****************************************************************************************************
*
*       --------------*--------------------*---------------------*-----------------
*                     S                    C                     E
*  �Ͽ���෿��Ŀ�� �����㷨Ϊ������λ��DisplacementSC��DisplacementCE���������λ�Ʒ�����ͬ��˵��C��SE������
*  ������ͨ��Ŀ�������߼�����仯�㣩��   �����㷨Ϊ������λ��DisplacementCS��DisplacementCE���������λ�Ʒ��Ų���ͬ��˵��C��SE������
* ****************************************************************************************************
* ��ڲ����� const LOD_STRU * pLODStartStru,	����ʼ��λ��
*            const LOD_STRU * pLODEndStru,	�����ն�λ��
*            const UINT8 PointNum,			������Ŀ 
*            const POINT_STRU * pPointStru,	������Ϣ
*			 const LOD_STRU * pCurrentLODStru,��ǰλ��
* ���ڲ����� UINT8 *pLocInArea         1,��ָ������
*                                     0,����ָ������
* ����ֵ��   0����ѯʧ��
*            1����ѯ�ɹ�
* ʹ��ע�⣺1.�ڵ�ǰλ��������˵�λ��ʱ����ʱ�����¹����жϣ�
*             1) ��ǰλ����������㣬��Ϊ�õ����ڱ�����
*             2) ��ǰλ���������յ㣬��Ϊ�õ㲻���ڱ�����
*             3) 3���غϷ����������ڡ�
*           2.��������ҵ�������յ㶼�������ڣ����Ե������α�����������ʼ�����ն�λ�ã�ֻҪ���ε�����һ���������ڣ�˵���ڵ���ʼ�����ն��γɵı�������
*           3.���SE���򲻴��ڣ���������0ʧ�ܡ����SC,����SE�����ڣ���������1�ɹ������ǵ�C����������
*           4.�෿�ͺϿ���Ŀ��ʼ��λ�ú��ն�λ�ô���ķ����豣֤һ��
*             ������ͨ����֤ʼ��λ�õķ�����ȷ���ɡ�
*/
UINT8 dsuCheckLocInArea(const LOD_STRU * pLODStartStru, const LOD_STRU *pLODEndStru,
	UINT8 PointNum, const DQU_POINT_STATUS_STRU *pPointStru, 
	const LOD_STRU *pCurrentLODStru,UINT8 *pLocInArea)
{
	return dsuCheckLocInAreaExp(qds_dsuEmapStru,pLODStartStru,pLODEndStru,PointNum,pPointStru,pCurrentLODStru,pLocInArea);
}

/************************************************************************

�������ܣ�	�˺����Ĺ���������link��ID��Ϣ��ѯlink�ĳ�����Ϣ
��ڲ�����	const UINT16 wLinkID		link��ID	
���ڲ�����	��
����ֵ��	UINT32 dwLinkLength	��ѯʧ��: 0xffffffff; ��ѯ�ɹ�: ���ز��ҵ���link����                                                                
************************************************************************/
/*���ܺ�������ѯlink����*/
UINT32 LinkLength(UINT16 wLinkID)
{
	return LinkLengthExp(qds_dsuEmapStru,wLinkID);
}

/*
* �������ܣ� �˺����Ĺ����ǽ��жϵ�ǰλ���Ƿ���ָ������Χ�ڡ�
�˺����Ĺ�����CheckLocInArea��������ġ�CheckLocInArea�Է���û��Ҫ�󣬼��������漰�ķ�������ȷ�ġ�
��CheckLocInAreaQuickҪ���StartLOD�ܹ�����EndLOD��
* ****************************************************************************************************
*
*       --------------*--------------------*---------------------*-----------------
*                     S                    C                     E
*       �����㷨Ϊ�������жϵ�ǰλ���������S��E�Ƿ���ͬһLink�ϣ�
*       �����ͬһLink�ϣ����ݷ����λ���ж��Ƿ��������ڣ��������ͬһLink���ж�CLinkId�Ƿ���SE֮���ĳһLinkId��ͬ
*       ��������֮���Link���Ա������������Զ��ڶ�ε��ñ�������ѯ�Ƿ��������ڵĺ���Ч�ʺ��а���
*
* ****************************************************************************************************
* ��ڲ����� const LOD_STRU * pLODStartStru,	����ʼ��λ��
*            const LOD_STRU * pLODEndStru,	�����ն�λ��
* ���ڲ�����	UINT16 wLinkID[DSU_MAX_LINK_BETWEEN]				Link��������
*               UINT16 *wLinkNumber                             Link����
*			 const LOD_STRU * pCurrentLODStru,��ǰλ��
* ���ڲ����� UINT8 *pLocInArea         1,��ָ������
*                                     0,����ָ������
* ����ֵ��   0����ѯʧ��
*            1����ѯ�ɹ�
* ʹ��ע�⣺1.�ڵ�ǰλ��������˵�λ��ʱ����ʱ�����¹����жϣ�
*             1) ��ǰλ����������㣬��Ϊ�õ����ڱ�����
*             2) ��ǰλ���������յ㣬��Ϊ�õ㲻���ڱ�����
*             3) 3���غϷ����������ڡ�
*           2.��������ҵ�������յ㶼�������ڣ����Ե������α�����������ʼ�����ն�λ�ã�ֻҪ���ε�����һ���������ڣ�˵���ڵ���ʼ�����ն��γɵı�������
*           3.���SE���򲻴��ڣ���������0ʧ�ܡ����SC,����SE�����ڣ���������1�ɹ������ǵ�C����������
*/
UINT8 dsuCheckLocInAreaQuick(const LOD_STRU * pLODStartStru, const LOD_STRU * pLODEndStru,
	UINT16 wLinkNumber,UINT16 wLinkID[DSU_MAX_LINK_BETWEEN],
	const LOD_STRU * pCurrentLODStru,UINT8 *pLocInArea)
{
	return dsuCheckLocInAreaQuickExp(qds_dsuEmapStru,pLODStartStru,pLODEndStru,wLinkNumber,wLinkID,pCurrentLODStru,pLocInArea);
}

/*
* �������ܣ� �˺����Ĺ������жϵ�ǰλ���Ƿ���ָ������Χ�ڣ��˺����Ƕ�dsuCheckLocInAreaQuick
��һ�����䡣���ڽ���ǰ����ȡ�����ټ����Ƿ��������ڡ�
* ��ڲ����� const LOD_STRU * pLODStartStru,	����ʼ��λ��
*            const LOD_STRU * pLODEndStru,	�����ն�λ��
* ���ڲ����� UINT16 wLinkID[DSU_MAX_LINK_BETWEEN]				Link��������
*            UINT16 *wLinkNumber                             Link����
*			 const LOD_STRU * pCurrentLODStru,��ǰλ��
*            UINT8 *pLocInArea         1,��ָ������
*                                     0,����ָ������
* ����ֵ��   0����ѯʧ��
*            1����ѯ�ɹ�
*/
UINT8 dsuCheckLocInAreaQuick2(const LOD_STRU * pLODStartStru, const LOD_STRU * pLODEndStru,
	UINT16 wLinkNumber,UINT16 wLinkID[DSU_MAX_LINK_BETWEEN],
	const LOD_STRU * pCurrentLODStru,UINT8 *pLocInArea)
{
	return dsuCheckLocInAreaQuickExp2( qds_dsuEmapStru,pLODStartStru,pLODEndStru,wLinkNumber,wLinkID,pCurrentLODStru,pLocInArea);
}

/*****************************����Ϊ�¶�ƽ�������������Ҫ�õ��ĺ���**************************/
/************************************************************************

�������ܣ�	�˺����Ĺ����ǲ�ѯ��ǰGarde������Grade
��ڲ�����	const UINT16 wCurrentGradeID	��ǰ�¶ȱ��
const UCHAR chDirection			�������з���
const UCHAR PointNum			MA��Χ�ڵ�����Ŀ
const DQU_POINT_STATUS_STRU * pPointStru	MA��Χ�ڵ�����Ϣ		
���ڲ�����	��
����ֵ��	UINT16 wFindGradeID	��ѯʧ��: 0xffff; ��ѯ�ɹ�: �������ڵ��¶�ID                                                              
************************************************************************/
/*���ܺ���,��ѯ��ǰGarde������Grade*/
UINT16 FindAdjacentGradeID(const UINT16 wCurrentGradeID, const UCHAR chDirection, const UCHAR PointNum,
	const DQU_POINT_STATUS_STRU * pPointStru)
{
	return FindAdjacentGradeIDExp(qds_dsuEmapStru,wCurrentGradeID,chDirection,PointNum,pPointStru);
}
/*
*�������ܣ���ѯĳ�������¶�ID
*���������UINT16 linkId,UINT32 offset�������
*���������UINT16 GradeID�����¶�ID
*����ֵ��  0����ִ��ʧ�ܣ�1�ɹ�
*/
UINT8 dsuGetGradeIdbyLoc(const UINT16 linkId,const UINT32 offset,UINT16* GradeID)
{
	return dsuGetGradeIdbyLocExp(qds_dsuEmapStru,linkId,offset,GradeID);
}
/*************
*�������ܣ�����ĳ���¶�ƽ������¶�ֵ
*���������Point �����¶ȵ�
*��������� 
*����ֵ��  0����ִ��ʧ�� 1 �����¶ȵ�һ�� 2 �����¶ȵ�2�� 3 �����¶ȵ�3��
****************/
UINT8 dsuCalculateGradeValue(UINT16 LinkId,UINT32 ofst,FLOAT32* GradeVal)
{
	return dsuCalculateGradeValueExp(qds_dsuEmapStru,LinkId,ofst,GradeVal); 
}

/*************
*�������ܣ�����ĳ�¶�ƽ���󣬷ֳɵļ������ֵķֽ�������ľ���
*���������gradeId �¶�ID
*���������UINT32* endPointDistance UINT32* startPointDistance
*����ֵ��  0����ִ��ʧ��   1�ɹ�
��ע��     �������Ҫƽ������ĵ㣬��Ϊ��Чֵffffffff  ����ֵΪ1
****************/
UINT8 dsuDividPointDistanceFromOrigin(UINT16 GradeId,UINT16 linkId,UINT32* endPointDistance,UINT32* startPointDistance)
{
	return dsuDividPointDistanceFromOriginExp(qds_dsuEmapStru,GradeId,linkId,endPointDistance,startPointDistance);
}

/*************
*�������ܣ������¶���ĳһ�㼰�¶�id������õ�����¶����ľ���
*���������gradeId �¶�ID
UINT16 linkId UINT32 Ofst
*���������UINT32 *length  ����

*����ֵ��  0����ִ��ʧ��   1�ɹ�  
****************/
UINT8 dsuGetDistanceFromOrigin(UINT16 GradeId,UINT16 linkId,UINT32 Ofst,UINT32* length)
{
	return dsuGetDistanceFromOriginExp(qds_dsuEmapStru,GradeId,linkId,Ofst,length);	
}

/************************************************************************

�������ܣ�	�˺����Ĺ����ǲ�ѯ��������λ�ü������¶ȡ�������ѯ�����
�յ㷶Χ�����е���·�¶ȣ�����������¶ȣ�������£����涨
����Ϊ��������Ϊ���������Ĺ��ܼ�Ϊ������Χ���¶ȵ���Сֵ��
������������¶ȵ�ǧ������

��ڲ�����	const LOD_STRU * pLODStartStru		��ѯ���λ�úͷ���ʵ��Ϊ�г���βλ�úͷ���
const LOD_STRU * pLODEndStru		��ѯ�յ�λ�úͷ���
const UCHAR PointNum				MA�еĵ�������
const POINT_STRU * pPointStru		������Ϣ�ṹ��
���ڲ�����	FLOAT64 * Gradient					�г���β��MA�յ㷶Χ������¶ȵ�ǧ����������Ϊ��������Ϊ����
����ֵ��	UCHAR bReturnValue					 	
0����ѯʧ�ܣ�
1����ѯ��ȷ��
ע���ڼ���Ĺ����У��õ����ֵ������ֵǰ����/10�Ĳ�������˷���
���¶�ֵΪǧ��ֵ                                                     
************************************************************************/
/*14 ��λ�ü�����¶Ȳ�ѯ*/
UCHAR dsuGradientGet(const LOD_STRU * pLODStartStru, const LOD_STRU * pLODEndStru,
	const UCHAR PointNum, const DQU_POINT_STATUS_STRU * pPointStru, FLOAT32 * Gradient)
{
	return dsuGradientGetExp(qds_dsuEmapStru,pLODStartStru,pLODEndStru,PointNum,pPointStru,Gradient);
}

/*
�������ܣ��жϺ�һ�¶ȵ��¶�ֵ���ǰһ���¶ȵ��¶�ֵ�����ӣ����仯���Ǽ��� 
���������UINT16 fistGradeID,UINT16 secondGradeID
���������GradeTrend �¶� 
1�� ����  
2�� ����
0�� ���仯
����ֵ��0ʧ�� 1�ɹ�
*/
UINT8 dquGradeTrend(UINT16 fistGradeID,UINT16 secondGradeID,UINT8 *GradeTrend)
{
	return dquGradeTrendExp(qds_dsuEmapStru,fistGradeID,secondGradeID,GradeTrend);
}

/*
�������ܣ���ȡǰ����¶�
���������UINT16 linkId,��ǰlink
���������gradeFrnt �¶� 
Null��  ��·�յ��ǰ���¶�Ϊͳһ�¶�  
��Null��ǰ���¶����¶ȱ��пɲ�
����ֵ��0ʧ�� 1�ɹ� 2��·�յ�
*/
UINT8 dsuGetGradeFrnt(UINT16 linkId, DSU_GRADE_STRU** gradeFrnt)
{
	return dsuGetGradeFrntExp(qds_dsuEmapStru,linkId,gradeFrnt); 
}

/*
�������ܣ���ȡ������¶�
���������UINT16 linkId,��ǰlink
���������gradeRear �¶� 
Null��  ��·�յ������¶�Ϊͳһ�¶�  
��Null�������¶����¶ȱ��пɲ�
����ֵ��0ʧ�� 1�ɹ� 2��·�յ�
*/
UINT8 dsuGetGradeRear(UINT16 linkId, DSU_GRADE_STRU** gradeRear)
{
	return dsuGetGradeRearExp(qds_dsuEmapStru,linkId,gradeRear); 
}

/**
�������ܣ���ȡ��ǰLINK�ľ�̬���ٸ���
���������
@linkId����ǰlink
�����������
����ֵ����̬���ٸ���
*/
UINT8 GetStcLmtSpdCntByLnkId(const UINT16 linkId)
{
	return GetStcLmtSpdCntByLnkIdExp(qds_dsuEmapStru,qds_dsuLimitStcLinkIdx,linkId);
}

/**
�������ܣ���ȡ�ƶ�LINK�ĵ�ָ���±�ľ�̬��ʱ���ٵĶ���ָ��
���������
@linkId����ǰLink���
@idx����ӦLink�ĵڼ������٣��±�ȡֵ��Χ0-9
����ֵ��
@NULL����ȡʧ�� 
@�ǿգ���Ӧ���ٽṹ��ָ��
*/
DSU_STATIC_RES_SPEED_STRU *GetStcLmtSpdInfoByLnkId(const UINT16 linkId,const UINT8 idx)
{
	return GetStcLmtSpdInfoByLnkIdExp(qds_dsuEmapStru,qds_dsuLimitStcLinkIdx,linkId,idx);
}


/*
�������ܣ����࿪����תΪ�������
���������multiPointId �࿪�������
          multiPointState �࿪����״̬

���������wVirtualPointIds ��ֺ����������� 
          wVirtualPointStates ��ֺ��������״̬
����ֵ������ֵ����ֺ������������, 0ʧ��  

�����㷨���࿪������������������� Nλ��R1λ��L1λ��R2λ��L2λ
            ����Ӧ�������е������� 0��  1��   2��   3��   4
		    ����Ӧ�Ķ࿪����״̬�� 1��  2��   3��   4��   5
		   ��˵� ����=�࿪����״̬multiPointState-1 ʱ������Ӧ�������������ԭֵ�������������״̬ȡ������λ<=>��λ��

ע�������������������wVirtualPointIds��״̬wVirtualPointStates��������Ч���������״̬����Ϊ3����
         
		               / L                                      / L
		              /                                        /
		             /                                        /       101                
		-|------------------------         ===��   ---|------/----------------- N      
		   1         \           N                          102       \
		              \                                                \
					   \                                                \
		              R                                                 R
		           ͼ1.ʵ����������                            ͼ2.���ⵥ������

		   ��ͼ1ʵ����������1��״̬Ϊ3ʱ���Ƴ�ͼ2���ⵥ������ΪLλ����ʱ101Ϊ��Ч�����������״̬Ϊ3������ֵ��������Ϊ2������
		   wVirtualPointIds[0]=102;
		   wVirtualPointStates[0]=2;
		   wVirtualPointIds[1]=101;
		   wVirtualPointStates[1]=3;
author:������Ŀ add by qxt 20170622
*/
UINT8 ConvertToVirtualSwitches(const UINT16 multiPointId,const UINT8 multiPointState,UINT16 wVirtualPointIds[MAX_VIRTUAL_SWITCH_NUM],UINT8 wVirtualPointStates[MAX_VIRTUAL_SWITCH_NUM])
{
     return ConvertToVirtualSwitchesExp(qds_dsuEmapStru,multiPointId,multiPointState,wVirtualPointIds, wVirtualPointStates);
}

/*
�������ܣ����������תΪ�࿪����
���������wVirtualPointIds[] ���������� 
          wVirtualPointStates[] �������״̬
		  wVirtualPointNum    �����������
���������multiPointId ��Ӧ�࿪�������
          multiPointState ��Ӧ�࿪����״̬
����ֵ��0ʧ�� 1�ɹ�

ע�������������������wVirtualPointIds��״̬wVirtualPointStates��������Ч���������������Ҫ���롣��
           
		 		      /L                                                 L
		             /                                                /
		            /                                                /
		           /                                                /
		---|------/-----------\------ N      =====>        ------------------ N
		          1          2 \                                    \
							    \                                    \
		                          R                                      R
		         ͼ1.���ⵥ������                             ͼ2.ʵ����������
		 
		 ��ͼ1����������1��״̬Ϊ2ʱ���Ƴ�ͼ2�࿪������״̬ΪLλ����ʱͼһ�������2Ϊ��Ч�ģ����������������Ϊ���£�
         wVirtualPointIds[0]=1;
		 wVirtualPointStates[0]=2;
         wVirtualPointNum=1;
author:������Ŀ add by qxt 20170622
*/
UINT8 ConvertToMultiSwitch(const UINT16 wVirtualPointIds[MAX_VIRTUAL_SWITCH_NUM],const UINT8 wVirtualPointStates[MAX_VIRTUAL_SWITCH_NUM],const UINT8 wVirtualPointNum,UINT16 *multiPointId,UINT8 *multiPointState)
{
      return ConvertToMultiSwitchExp(qds_dsuEmapStru,wVirtualPointIds, wVirtualPointStates,  wVirtualPointNum,multiPointId,multiPointState);
}
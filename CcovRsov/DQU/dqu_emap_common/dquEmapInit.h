/************************************************************************
*
* �ļ���   ��  dquEmapInit.h
* ��Ȩ˵�� ��  �������ؿƼ����޹�˾
* �汾��   ��  1.0
* ����ʱ�� ��  
* ����     ��  ������
* �������� ��  ���ӵ�ͼ��ʼ������  
* ʹ��ע�� �� 
* �޸ļ�¼ ��  
*
************************************************************************/
#ifndef  DQU_EMAP_INIT_H
#define  DQU_EMAP_INIT_H

#include "string.h"
#include "Convert.h"
#include "dfsDataRead.h"
#include "dsuVar.h"
#include "dquStructInit.h"
#include "dquQueryExp.h"
#include "dquDataTypeDefine.h"
#include "CommonMemory.h"

#define  INIT_ERR_NUM   100	/*���ݻ�����ͨ���ݽṹV15.0.0���ӱ�������Ҫ����ֵ������50��Ϊ100�����ں�����չ��modify by sds 20181116*/

extern UINT8  initErrNo[INIT_ERR_NUM];      /*�����ݳ�ʼ��ʧ�ܹ��Ϻ�����*/
#define DEBUG_GET_DATA_FAIL    0x01  /*��ȡ����ʧ��*/
#define DEBUG_DATA_LENTH_FAIL  0x02  /*���ݳ�������*/
#define DEBUG_CALC_FAIL        0x04  /*������̴���*/

#define DQU_EMAP_VER1	66	/*��Ʒ���*/
#define DQU_EMAP_VER2	17	/*����ģ����*/
#define DQU_EMAP_VER3	0	/*����ģ�����汾���*/
#define DQU_EMAP_VER4	0	/*����ģ���Ӱ汾���*/

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************
*�������ܣ����ӵ�ͼģ��汾�Ż�ȡ
*����˵����������ϵͳ���ò�ѯ�����汾�ţ���ֹ���ɴ���
*��ڲ�������
*���ڲ�������
*����ֵ��UINT32��ʾ�İ汾��
*********************************************/
UINT32 GetDquEmapVersion();

/*��ʼ�����ӵ�ͼ*/
UINT8 dfsEmapInit (CHAR * FSName);

/************************************************************
*�������ܣ����ù���ͣ�������ԵĹ�����Ϣ������������򲻽��й���
*����˵����
*		filterAttr:����������Ϣ
*����ֵ����
*�޸ļ�¼��add by sds 2019-10-22
*************************************************************/
void SetFilterStopPointAttr(UINT32 filterAttr);

/****************************************
*�������ܣ���ʼ�����ӵ�ͼ��չ�ӿ�
*����˵����pDataBuf,�������ݿ飬
*	   dsuEmapStru,�ⲿʵ����ӵ�ͼ�洢�ṹ��ָ�룬
*	   dsuLimitStcLinkIdx,�ⲿʵ�徲̬����link�ṹ��ָ�룬
*	   mode,����ģʽ��1�ϵ�һ�μ��أ�2����ʱ��δ���
*	   timeSlice��ִ�е�ʱ��Ƭ����λ�����룩
*����ֵ��  0ʧ�ܣ�1�ɹ���2�ֲ�����δ���
*****************************************/
UINT8 dfsEmapInitExp(UINT8 * pDataBuf,DSU_EMAP_STRU *dsuEmapStru,DSU_STC_LIMIT_LINKIDX_STRU *dsuLimitStcLinkIdx,UINT8 mode,UINT16 timeSlice);


/*���ӵ�ͼ��ʼ����ϣ�ִ�е��ӵ�ͼ�ڲ�������������������*/
UINT8 dfsEmapInitFinally();

/************************************************************
*�������ܣ������������������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*
		�������νṹ����������
						
			UINT16  wOrgnRelatPointId;					���������������������
			UINT16  wOrgnMainAxleSgmtId;					��������������Ӷ�λ�������α��
			UINT16  wOrgnSideAxleSgmtId;					��������������ӷ�λ�������α��
			UINT16  wTmnlRelatPointId;					���������յ�����������
			UINT16  wTmnlMainAxleSgmtId;					���������յ����Ӷ�λ�������α��
			UINT16  wTmnlSideAxleSgmtId;					���������յ����ӷ�λ�������α��
			UINT16  wRelatAxleSgmtNum;					��������������Ŀ
			UINT16  wRelatAxleSgmtId[3];					�����������α��
			UINT16  wManageZC;							����ZC������
			UINT16  wManagePhysicalCI;					��������CI������
			UINT32 dwOrgnLinkOfst;							�������linkƫ����
			UINT32 dwTmnlLinkOfst;							�յ�����linkƫ����
			UINT16  wMiddleLinkId;							���������м����link���
************************************/
UINT8 AxleSgmtStru();

/************************************************************
*�������ܣ������߼�����������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*   UINT16  wMiddleLinkId;						�߼������м����link���
	UINT16  wMainOrgnLogicSgmtId;				��������������ǰ���߼����εı��
	UINT16  wMainTmnlLogicSgmtId;				�������������ں����߼����εı��
************************************/
UINT8 LogicSgmtStru();

/*********************************************
*�������ܣ���·�����ݽṹ
*����˵������
*����ֵ��0��ʧ�ܣ�1���ɹ�
	UINT16  wIncludeAxleSgmtNum;				��·�����ļ���������Ŀ
	UINT16  wIncludeAxleSgmtId[8];				�����ļ������α��
	UINT16  wAxleSgmtLockStatus[8];				�����ļ�����������״̬
	
	UINT16  wObsNum;							��·�����ϰ�����Ŀ
	UINT16  wObsType[8];							�ϰ�������
	UINT16  wObsID[8];								�ϰ���ID
	UINT16	wObsNeedLockStatus[8];					�ϰ�����Ҫ����״̬
*********************************************/
UINT8 RouteStru();

/*********************************************
*�������ܣ���ɱ�������������
*����˵������
*����ֵ��0��ʧ�ܣ�1���ɹ�
*********************************************/
UINT8 ProtectLink();

/*********************************************
*�������ܣ������¶�
*����˵������
*����ֵ��0��ʧ�ܣ�1���ɹ�
*********************************************/
UINT8 Grade();

/*********************************************
*�������ܣ�����Ĭ���г����б�����
*����˵������
*����ֵ��0��ʧ�ܣ�1���ɹ�
*********************************************/
UINT8 DefaultRouteStru();

/*********************************************
*�������ܣ����ݽӽ�����ID����ȡ�ӽ����ΰ����ĵ�����״̬
*����˵����
       ���������AccessLinkId �ӽ�����ID
	   ���������RelatePointNum ��������
	             RelatePointId[] ����ID
				 RelatePointSta[] ����״̬
*����ֵ �� 0 ʧ�ܣ�1�ɹ�
*********************************************/
UINT8 GetPointInfoFromAccessLink(UINT16 AccessLinkId,UINT16 Dirction,UINT16 * RelatePointNum,UINT16  RelatePointId[],UINT16 RelatePointSta[]);

/**************************************
�������ܣ�����link���л�ü������α������
���������linkId �����׵�ַ��LinkNum link����
���������AxleSgmtId �������α�������ַ
          AxleSgmtNum ���鳤��
����ֵ��0ʧ�ܣ�1�ɹ�
***************************************/
UINT8 GetAxleSemtIdFromLinkId(UINT16* linkId,UINT16 LinkNum,UINT16 *AxleSgmtId,UINT16 * AxleSgmtNum);

/*********************************************
*�������ܣ����ݽ�·link���У������ϰ�����Ϣ
*����˵������
*����ֵ��0��ʧ�ܣ�1���ɹ�
*********************************************/
UINT8 GetObstacleFromRoute(DSU_ROUTE_STRU*  pRouteStru);

/*********************************************
*�������ܣ�����ͣ������Ϣ
*����˵������
*����ֵ��0��ʧ�ܣ�1���ɹ�
*********************************************/
UINT8 CalculateStopPoint();

/**********************************************
�������ܣ���ʼ��[ռλ��������]:ֻ����������������ռλ���������ݱ���������������������һ��
���������pDataAddr:�������׵�ַ
		  dataSize:�����ֽڳ���
		  rowCount:����������
�����������
����ֵ: 1 �ɹ�
�޸ļ�¼��add by sds 2019-10-22
**********************************************/
UINT8 initNop(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[link����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initLink(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initPoint(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[�źŻ�����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initSignal(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[Ӧ��������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initBalise(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[����������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initAxle(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[����������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initScreen(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[����ͣ����ť����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initEmergStop(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ͣ����������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initStation(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ͣ��������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initStopPoint(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[������������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initAxleSgmt(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[�߼���������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initLogicSgmt(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��·����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initRoute(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[������������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initProtectLink(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��ʽ�ӽ�����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initBLOCAccessLink(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[CBTC�ӽ�����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initCBTCAccessLink(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[�¶���Ϣ����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initGrade(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��̬������Ϣ]:��������
���������pDataAddr:�������׵�ַ
		  dataSize:�����ֽڳ���
		  rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initStaticResSpeed(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[Ĭ���г�����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initDefaultRout(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[վ����Ӫ��]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initRunLevel(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[�˳�CBTC����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initExitRoute(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��CBTC����]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initTrainLine(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[�Զ��۷�]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initAR(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ZC����������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initZCComZone(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[CI��Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initCI(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ATS��Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initATS(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ͳһ������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initConResSpeed(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ͳһ�¶���Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initConGrade(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ZC�ֽ����Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initZCDividPoint(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[����������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initPhysicalSgmt(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��ʽ��������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initBlocTrgArea(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[CBTC��������]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initCbtcTrgArea(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[վ̨]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initPlatForm(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[������·]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initComeGoRoute(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initFloodGate(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[SPKS������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initSpksButton(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initDepotGate(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initTunnel(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[ZC��Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initZC(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[�࿪��������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initMultiPoint(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[����������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initPowerlessZone(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**********************************************
�������ܣ���ʼ��[��������Ϣ]:��������
���������pDataAddr:�������׵�ַ
dataSize:�����ֽڳ���
rowCount:����������
�����������
����ֵ:2������,1�ɹ�,0ʧ��
**********************************************/
UINT8 initCarStop(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/*********************************************
�������ܣ���ʼ������ͣ��������Ϣ ����������
���������UINT8 *pDataAddr, �����ڴ��ַ
		  UINT32 DataSize,  ���ݱ��������ֽ���
          UINT16 rowCount,  ���ݱ�����������
�����������
����ֵ�� 2δ�����꣬1�ɹ���0ʧ��
��ע�����ݻ�����ͨ���ݽṹV18.0.0���ӣ�add by sds 20200211
*********************************************/
UINT8 initAdjtStation(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/**************************************************************************
* ��������:		��ʼ��PSC��
* �������:		UINT8 *pDataAddr, �����ڴ��ַ
				UINT32 DataSize,  ���ݱ��������ֽ���
				UINT16 rowCount,  ���ݱ�����������
* �����������:	��
* �������:		��
* ȫ�ֱ���:		
* ����ֵ:		2δ�����꣬1�ɹ���0ʧ��
8 �޸ļ�¼:
* 1�����ݻ�����ͨ���ݽṹV20.0.0���ӣ�add by sds 2020-8-18
**************************************************************************/
UINT8 initPSC(UINT8 *pDataAddr, UINT32 dataSize, UINT16 rowCount);

/***
�������ܣ���ȡ������
�����������
���������errRecord���������飬errRecordLen���鳤��
����ֵ��1�ɹ�
***/
UINT8 dquGetErrNo(UINT8* errRecord,UINT32 * errRecordLen);

/************************************************
�������ܣ���̬������Ϣ��Ӧ�Ĳ�����LinkΪ�����ı��У�
		  �����Ż���ѯ��ǰLINK�����������ʹ�á�
���������
@linkId:��ǰ��̬���ٱ�������Ŷ�Ӧ����LINK��ţ���pCurrentStaticResSpeedStru->wLinkId
@limitStcSpdId:��ǰ��̬���ٱ�������ţ���pCurrentStaticResSpeedStru->wId
�����������
����ֵ��1�ɹ� 0ʧ��
************************************************/
UINT8 InsertToLimitStcLinkIdx(UINT16 linkId,UINT16 limitStcSpdId);

/*
�������ܣ����ݵ������Ͷ࿪��������ȡ����ʵ�����
����˵������
����ֵ��1�ɹ��� 0ʧ��
author:������Ŀ qxt 20170626
*/
UINT8 GetPhyiscalSwitches();

/*
�������ܣ�����Link�������豸���ӳ���ϵ
����˵������
����ֵ��1�ɹ��� 0ʧ��
author: qxt 20170816
*/
UINT8 GetDeviceInfoInLink();

/*************************************************
�������ܣ�����Link���¶ȼ��ӳ���ϵ
		  �¶�ID�����¶���������Ӧ�Ĳ�����LinkΪ�����ı��У�
		  �����Ż���ѯ��ǰLINK����¶�������
����˵������
����ֵ��2��ʾ��ǰû�д����꣬��Ҫ�ٴε��ô˺����� 1��ʾ�ɹ��� 0��ʾʧ��
author: lmy 20180122
*************************************************/
UINT8 GetGradeInfoCrossLink();

/*
�������ܣ�����SPKS������Link����
����˵������
����ֵ��2��ʾ��ǰû�д����꣬��Ҫ�ٴε��ô˺����� 1��ʾ�ɹ��� 0��ʾʧ��
author: qxt 20180716
*/
UINT8 CalcSPKSIncLinks();

#ifdef __cplusplus
}
#endif
#endif 
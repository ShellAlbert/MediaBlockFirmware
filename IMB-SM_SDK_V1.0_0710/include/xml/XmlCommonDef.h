#ifndef C_XML_COMMON_DEF
#define C_XML_COMMON_DEF
typedef enum 
{
	XML_ERR_SUCCESS,						//�ɹ�
	XML_ERR_FAIL_TO_INIT_PLATFORM,			//��ʼ��ʧ��
	XML_ERR_FAIL_TO_LOAD_GRAMMER_FILE,		//�����﷨�ļ�ʧ��(schema,DTD)
	XML_ERR_OUT_OF_MEMORY,					//�ڴ�ľ�
	XML_ERR_DOM_ERROR,						//����XML�ļ�����
	XML_ERR_UNKNOWN_ERROR,					//δ֪����
	XML_ERR_TRY_TO_MODIFY_READONLY_NODE,	//��ͼ�޸�ֻ���ڵ�
	XML_ERR_INVALID_NODE,					//ʹ�÷Ƿ��ڵ�
	XML_ERR_NODE_NOT_FOUND,					//�ڵ�δ�ҵ�
	XML_ERR_INVALID_NODE_NAME,				//�ڵ������Ϸ�
}XmlErrNo;

#endif

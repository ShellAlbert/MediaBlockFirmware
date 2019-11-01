#ifndef C_XML_COMMON_DEF
#define C_XML_COMMON_DEF
typedef enum 
{
	XML_ERR_SUCCESS,						//成功
	XML_ERR_FAIL_TO_INIT_PLATFORM,			//初始化失败
	XML_ERR_FAIL_TO_LOAD_GRAMMER_FILE,		//加载语法文件失败(schema,DTD)
	XML_ERR_OUT_OF_MEMORY,					//内存耗尽
	XML_ERR_DOM_ERROR,						//解析XML文件出错
	XML_ERR_UNKNOWN_ERROR,					//未知错误
	XML_ERR_TRY_TO_MODIFY_READONLY_NODE,	//试图修改只读节点
	XML_ERR_INVALID_NODE,					//使用非法节点
	XML_ERR_NODE_NOT_FOUND,					//节点未找到
	XML_ERR_INVALID_NODE_NAME,				//节点名不合法
}XmlErrNo;

#endif

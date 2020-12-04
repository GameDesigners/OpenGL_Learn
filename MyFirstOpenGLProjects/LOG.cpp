#include "LOG.h"

/// <summary>
/// 获取当前硬件可声明的顶点属性数量
/// </summary>
/// <returns></returns>
int LOG::GetIntegerv()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	return nrAttributes;
}
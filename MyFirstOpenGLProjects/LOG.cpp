#include "LOG.h"

/// <summary>
/// ��ȡ��ǰӲ���������Ķ�����������
/// </summary>
/// <returns></returns>
int LOG::GetIntegerv()
{
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	return nrAttributes;
}
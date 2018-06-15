
// ��ɫ�壺���ڵļ��������32λ���Ǹ��ߣ�����ͼ�����ݿ������ɫ24λ���ģ�
// ��ÿ�����ؾ���24bit��ʾ��ÿ8bit��ʾRGB��ɫ�е�һɫ������ǰ�ļ������������
// �ϲͼ����1λ��4λ��8λ����BITMAPINFOHEADER�е�biBitCount����24����ʱ��
// �����RGBɫ�ʾ���Ҫ��ɫ�壬��ɫ�弴ʹ��ͼ��������ʹ�õ�һ����ɫ��Ӧ��RGB
// ��ɫ�У�����ͼ�������е�����ֵ����һ������ֵ������������ֵ���������ֵ��Ӧ
// �ĵ�ɫ���е�ֵ����ɫ����һ�����飬������ÿ��Ԫ�ؾ���һ��rgb��ɫ������8λͼ��
// ���ɱ��256����ɫ����ɫ��Ĵ�С����256
// ��ɫ��������ÿ��Ԫ�ص����ݽṹ���£�

//typedef struct tagRGBQUAD
//{
//	BYTE rgbBlue;
//	BYTE rgbGreen;
//	BYTE rgbRed;
//	BYTE rgbReserved;
//}RGBQUAD;
//
//typedef RGBQUAD FAR* LPRGBQUAD;

// ͼ�����ݶ���1λͼ��1��������1bit�洢������24λͼ��1��������24bit�洢��
// λͼ�ļ��������Ǵ��¶��ϣ�������Ҵ洢�ġ�����˵����ȡ��ʱ�����ȶ�������
// ͼ�����·������أ�����ȡ����ͼ�����Ϸ���ͼ��

/**
 * ��˵����C++ʵ��λͼ�ļ��Ķ�ȡ��洢
*/

#ifndef _MY_BITMAP_H_
#define _MY_BITMAP_H_

#include <Windows.h>

class CBitMap
{
public:
	CBitMap();
	~CBitMap();
protected:
	BITMAPFILEHEADER fileHeader;		// λͼ�ļ�ͷ
	BITMAPINFOHEADER infoHeader;		// λͼ��Ϣͷ
public:
	int m_width_p;						// λͼ���(���ؼ���)
	int m_height_p;						// λͼ�߶�
	int m_nBitCount;					// λ��
	unsigned char *databuf;				// ʵ��ͼ������
	LPRGBQUAD colorTable;				// ��ɫ��(��ɫ��)
	bool Read(char *fileName);			// ��ȡλͼ�ļ�
	bool Write(char *fileName);			// ������д��λͼ�ļ���
};

#endif // _MY_BITMAP_H_
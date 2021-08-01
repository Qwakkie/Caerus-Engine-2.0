#include "BinaryReader.h"


#include <fstream>
#include <string>
#include <Windows.h>


BinaryReader::BinaryReader(void):
	m_Exists(false),
	m_pReader(nullptr)
{
}

BinaryReader::~BinaryReader(void)
{
	Close();
}

void BinaryReader::Open(std::string binaryFile)
{
	Close();

	auto temp = new std::ifstream();
	temp->open(binaryFile, std::ios::in| std::ios::binary);
	if(temp->is_open())
	{
		m_pReader = temp;
		m_Exists = true;
	}
	else
	{
		Close();
	}
}

void BinaryReader::Close()
{
	delete m_pReader;
	m_pReader = nullptr;
	m_Exists = false;
}

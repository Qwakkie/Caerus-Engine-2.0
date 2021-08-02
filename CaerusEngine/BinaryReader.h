#pragma once
#include <istream>
#include <string>
#include <Windows.h>

class BinaryReader
{
public:
	BinaryReader(void);
	~BinaryReader(void);


	template<class T>
	T Read()
	{
		T value;
		m_pReader->read((char*)&value, sizeof(T));
		if (m_pReader->eof())
			m_Exists = false;
		return value;
	}

	bool Exists() const { return m_Exists; }

	void Open(std::string binaryFile);
	void Close();

private: 

	bool m_Exists;
	std::istream* m_pReader;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	BinaryReader(const BinaryReader& yRef);									
	BinaryReader& operator=(const BinaryReader& yRef);
};


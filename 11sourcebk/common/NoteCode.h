//---------------------------------------------------------------------------

#ifndef NoteCodeH
#define NoteCodeH

#include <vcl.h>
#include <ADODB.hpp>

//---------------------------------------------------------------------------
class NoteCode
{
public:
	NoteCode(const TDateTime& dt, int storage, int id);
	NoteCode(int year, int month, int day, int storage, int id);
	NoteCode(String code);
	String AsString();
	static NoteCode StringToNoteCode(String code);
	static String BuildCode(TADOQuery* pQuery, const TDateTime& dt, int storage, const String& table, const String& field);
	int GetID();

private:
	int m_year;
	int m_month;
	int m_day;
	int m_storage;
	int m_id;
};



#endif

//---------------------------------------------------------------------------


#pragma hdrstop

#include "NoteCode.h"

//---------------------------------------------------------------------------

NoteCode::NoteCode(const TDateTime& dt, int storage, int id)
{
	unsigned short year, month, day;
	dt.DecodeDate(&year, &month, &day);
	m_year = year;
	m_month = month;
	m_day = day;
	m_storage = storage;
	m_id = id;
}

NoteCode::NoteCode(int year, int month, int day, int storage, int id)
	:m_year(year)
	,m_month(month)
	,m_day(day)
	,m_storage(storage)
	,m_id(id)
{
}

NoteCode::NoteCode(String code)
{
	m_storage = code.SubString(1, 2).ToInt();
	m_year = code.SubString(3, 2).ToInt();
	m_month = code.SubString(7, 2).ToInt();
	m_day = code.SubString(9, 2).ToInt();
	m_id = code.SubString(11, 5).ToInt();
}

NoteCode NoteCode::StringToNoteCode(String code)
{
    return NoteCode(code);
}

String NoteCode::AsString()
{
	String ret;
	TVarRec args[] = {m_storage, m_year, m_month, m_day, m_id};
	ret = ret.Format("%.2d%.4d%.2d%.2d%.5d", args, 5);
	return ret;
}

int NoteCode::GetID()
{
    return m_id;
}

String NoteCode::BuildCode(TADOQuery* pQuery, const TDateTime& dt, int storage, const String& table, const String& field)
{
	String code, codemin, codemax;
	String base = dt.FormatString("yyyymmdd");
	codemin = Format("%0.2d%s%0.5d", ARRAYOFCONST((storage, base.c_str(), 0)));
	codemax = Format("%0.2d%s%0.5d", ARRAYOFCONST((storage, base.c_str(), 99999)));
	String sql = Format("select max(%s) as code from %s where %s>=%s and %s<=%s",
    	ARRAYOFCONST((field.c_str(), table.c_str(), field.c_str(), codemin.c_str(), field.c_str(), codemax.c_str())));
	pQuery->Close();
	pQuery->SQL->Clear();
	pQuery->SQL->Add(sql);
	pQuery->Open();
	if (pQuery->RecordCount >= 1)
	{
		pQuery->Last();
		String last = pQuery->FieldByName("code")->AsString;
		if (last == "")
		{
			code = codemin;
		}
		else
		{
			int  id = last.SubString(11, 5).ToInt() ;
			id++;
			code = Format("%s%0.5d", ARRAYOFCONST((codemin.SubString(0, 10).c_str(), id)));
		}
	}
	else
	{
        code = codemin;
    }
	pQuery->Close();
	return code;
}

#pragma package(smart_init)

/*
	CVSNT Generic API
    Copyright (C) 2005 Tony Hoyle and March-Hare Software Ltd

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef DB2RECORDSET__H
#define DB2RECORDSET__H

#include <vector>

class CDb2Connection;

class CDb2Field : public CSqlField
{
	friend class CDb2Recordset;
public:
	CDb2Field();
	virtual ~CDb2Field();

	virtual operator int();
	virtual operator long();
	virtual operator unsigned();
	virtual operator unsigned long();
#if defined(_WIN32) || defined(_WIN64)
	virtual operator __int64();
#else
	virtual operator long long();
#endif
	virtual operator const char *();
	virtual operator const wchar_t *();

protected:
	HSTMT hStmt;
	cvs::wstring name;
	SQLSMALLINT type,ctype;
	SQLUINTEGER size;
	SQLSMALLINT decimal;
	SQLSMALLINT null;
	SQLINTEGER fldlen,datalen;
	void *data;
	SQLSMALLINT field;
	cvs::wstring tmpwstr;
	cvs::string tmpstr;
};


class CDb2Recordset : public CSqlRecordset
{
	friend class CDb2Connection;
public:
	CDb2Recordset();
	virtual ~CDb2Recordset();

	virtual bool Close();
	virtual bool Closed() const;
	virtual bool Eof() const;
	virtual bool Next();
	virtual CSqlField* operator[](size_t item) const;
	virtual CSqlField* operator[](int item) const;
	virtual CSqlField* operator[](const char *item) const;

protected:
	HSTMT m_hStmt;
	bool m_bEof;
	SQLSMALLINT m_num_fields;
	std::vector<CDb2Field> m_sqlfields;
	CDb2Connection *m_parent;

	bool Init(CDb2Connection *parent, HSTMT hStmt, const char *command);
	void GetStmtError();
};

#endif



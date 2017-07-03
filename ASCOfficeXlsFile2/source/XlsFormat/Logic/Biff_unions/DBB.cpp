﻿/*
 * (c) Copyright Ascensio System SIA 2010-2017
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "DBB.h"

#include "../Biff_records/SXDBB.h"
#include "SXOPER.h"

namespace XLS
{

DBB::DBB()
{
	fShortIitms = false;
}

DBB::~DBB()
{
}

BaseObjectPtr DBB::clone()
{
	return BaseObjectPtr(new DBB(*this));
}

// DBB = [SXDBB] *SXOPER
const bool DBB::loadContent(BinProcessor& proc)
{
	if(proc.optional<SXDBB>())
	{
		m_SXDBB = elements_.back();
		elements_.pop_back();
	}
	int count = proc.repeated<SXOPER>(0, 0);
	while(count--)
	{
		m_arSXOPER.push_back(elements_.front());	elements_.pop_front();
	}

	if (!m_SXDBB && m_arSXOPER.empty())
		return false;

	return true;
}
int DBB::serialize(std::wostream & strm)
{
	SXDBB* dbb = dynamic_cast<SXDBB*>(m_SXDBB.get());

	if (!dbb && m_arSXOPER.empty()) return 0;

	CP_XML_WRITER(strm)
	{
		CP_XML_NODE(L"r")
		{ 		
			if (m_arSXOPER.empty() == false)
			{
				for (size_t i = 0; i < m_arSXOPER.size(); i++)
				{
					m_arSXOPER[i]->serialize(CP_XML_STREAM());
				}
			}
			else
			{
				if (fShortIitms == false)
				{
					for (size_t i = 0; i < dbb->size; i++)
					{
						CP_XML_NODE(L"x")
						{		
							CP_XML_ATTR(L"v", dbb->blob[i]);
						}
					}
				}
				else
				{
					unsigned short * values = (unsigned short *)dbb->blob.get();
					for (size_t i = 0; i < dbb->size / 2; i++)
					{
						CP_XML_NODE(L"x")
						{		
							CP_XML_ATTR(L"v", values[i]);
						}
					}
				}
			}
		}
	}
	return 0;
}
} // namespace XLS


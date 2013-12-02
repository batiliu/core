#include "precompiled_cpodf.h"

#include "office_presentation.h"

#include <boost/foreach.hpp>

#include <cpdoccore/xml/xmlchar.h>
#include <cpdoccore/xml/serialize.h>
#include <cpdoccore/xml/attributes.h>

#include "serialize_elements.h"

namespace cpdoccore { 
namespace odf {

// office:presentation
//////////////////////////////////////////////////////////////////////////////////////////////////
const wchar_t * office_presentation::ns = L"office";
const wchar_t * office_presentation::name = L"presentation";

void office_presentation::add_child_element( xml::sax * Reader, const ::std::wstring & Ns, const ::std::wstring & Name)
{
    CP_CREATE_ELEMENT(content_);
}

void office_presentation::add_text(const std::wstring & Text)
{
    // TODO : error
}

void office_presentation::add_attributes( const xml::attributes_wc_ptr & Attributes )
{
}

void office_presentation::docx_convert(oox::docx_conversion_context & Context)
{
    Context.start_office_text();
	_CP_LOG(info) << L"[info][docx] process spreadsheet (" << content_.size() << L" elmements)" << std::endl;
	BOOST_FOREACH(const office_element_ptr & elm, content_)
    {
        elm->docx_convert(Context);
    }
    Context.end_office_text();
}

void office_presentation::xlsx_convert(oox::xlsx_conversion_context & Context)
{
    Context.start_office_spreadsheet(this);
    _CP_LOG(info) << L"[info][xlsx] process spreadsheet (" << content_.size() << L" elmements)" << std::endl;
    BOOST_FOREACH(const office_element_ptr & elm, content_)
    {
        elm->xlsx_convert(Context);
    }
    Context.end_office_spreadsheet();
}
void office_presentation::pptx_convert(oox::pptx_conversion_context & Context)
{
    Context.start_office_presentation();
    _CP_LOG(info) << L"[info][pptx] process presentationt (" << content_.size() << L" elmements)" << std::endl;
    BOOST_FOREACH(const office_element_ptr & elm, content_)
    {
        elm->pptx_convert(Context);
    }
    Context.end_office_presentation();
}

}
}

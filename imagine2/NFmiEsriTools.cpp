#include "NFmiEsriTools.h"
#include "NFmiEsriShape.h"
#include "NFmiStringTools.h"
#include <list>
#include <stdexcept>

using namespace std;

namespace Imagine
{
namespace NFmiEsriTools
{
namespace
{
// Compare two values with the given comparison operator
template <typename T>
bool compare_values(const T& value, const string& comparison, const T& limit)
{
  if (comparison == "==" || comparison == "=")
    return value == limit;
  if (comparison == "<>")
    return value != limit;
  if (comparison == "<")
    return value < limit;
  if (comparison == ">")
    return value > limit;
  if (comparison == "<=")
    return value <= limit;
  if (comparison == ">=")
    return value >= limit;
  return false;
}

// Test whether the field value of the element satisfies the condition
bool element_matches(const NFmiEsriElement& element,
                     const string& fieldname,
                     NFmiEsriAttributeType atype,
                     const string& fieldcomparison,
                     const string& svalue,
                     int ivalue,
                     double dvalue)
{
  if (atype == kFmiEsriString)
    return compare_values(element.GetString(fieldname), fieldcomparison, svalue);
  if (atype == kFmiEsriInteger)
    return compare_values(element.GetInteger(fieldname), fieldcomparison, ivalue);
  return compare_values(element.GetDouble(fieldname), fieldcomparison, dvalue);
}
}  // namespace

// ----------------------------------------------------------------------
/*!
 * \brief Filter a shape based on a condition of form NAME<op>VALUE
 */
// ----------------------------------------------------------------------

NFmiEsriShape* filter(const NFmiEsriShape& theShape, const std::string& theCondition)
{
  // Parse the relevant option

  list<string> comparisons;
  comparisons.emplace_back("==");
  comparisons.emplace_back("<=");
  comparisons.emplace_back(">=");
  comparisons.emplace_back("<>");
  comparisons.emplace_back("<");
  comparisons.emplace_back(">");
  comparisons.emplace_back("=");

  string fieldname;
  string fieldvalue;
  string fieldcomparison;
  list<string> words;

  for (list<string>::const_iterator it = comparisons.begin(); it != comparisons.end(); ++it)
  {
    string::size_type pos = theCondition.find(*it);
    if (pos != string::npos)
    {
      fieldcomparison = *it;
      fieldname = theCondition.substr(0, pos);
      fieldvalue = theCondition.substr(pos + it->size());
      break;
    }
  }

  if (fieldcomparison.empty())
    throw runtime_error("Unable to parse comparison option");

  // Fetch the attribute name

  const NFmiEsriAttributeName* name = theShape.AttributeName(fieldname);
  if (name == nullptr)
    throw runtime_error("The shape does not have a field named '" + fieldname + "'");
  // Preparse the desired field value

  const NFmiEsriAttributeType atype = name->Type();

  string svalue;
  int ivalue = 0;
  double dvalue = 0;

  switch (atype)
  {
    case kFmiEsriString:
      svalue = fieldvalue;
      break;
    case kFmiEsriInteger:
      ivalue = NFmiStringTools::Convert<int>(fieldvalue);
      break;
    case kFmiEsriDouble:
      dvalue = NFmiStringTools::Convert<double>(fieldvalue);
      break;
    default:
      throw runtime_error("The field '" + fieldname + "' is of unknown type");
  }

  NFmiEsriShape* shape = new NFmiEsriShape(theShape.Type());

  for (NFmiEsriShape::attributes_type::const_iterator ait = theShape.Attributes().begin();
       ait != theShape.Attributes().end();
       ++ait)
  {
    shape->Add(new NFmiEsriAttributeName(**ait));
  }

  for (NFmiEsriShape::const_iterator it = theShape.Elements().begin();
       it != theShape.Elements().end();
       ++it)
  {
    // Skip empty elements
    if (*it == nullptr)
      continue;

    // Check if the value is correct

    bool ok = element_matches(**it, fieldname, atype, fieldcomparison, svalue, ivalue, dvalue);

    if (!ok)
      continue;

    NFmiEsriElement* tmp = (*it)->Clone();
    shape->Add(tmp);
  }

  return shape;
}

}  // namespace NFmiEsriTools
}  // namespace Imagine

/*
 * BoostJSON.h
 *
 *  Created on: Dec 5, 2015
 *      Author: fred

The MIT License (MIT)

Copyright (c) 2015 Frederick S. Ziegler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

#ifndef BOOSTJSON_H_
#define BOOSTJSON_H_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>
#include <string>
#include <boost/regex.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using namespace std;

namespace BoostJSONDemo
{

// Definitions taken from http://www.json.org/
// TJSONValueType defines the value types allowed as an element in an array or
// as the value portion of a string-value pair in an object.
enum TJSONValueType
{
   kJSONTrueType,
   kJSONFalseType,
   kJSONNullType,
   kJSONNumberType,
   kJSONStringType,
   kJSONObjectType,
   kJSONArrayType,
   kUNKNOWNJSONValueType,
};

typedef pair<TJSONValueType, string> TTJSONValueTypeStrPair;
typedef map<TJSONValueType, string> TTJSONValueTypeStrMap;
typedef pair<TJSONValueType, boost::regex> TTJSONValueTypeRegexPair;
typedef map<TJSONValueType, boost::regex> TTJSONValueTypeRegexMap;
// TObjType defines the fundamental entities used by JSON.
enum TObjType
{
   kObject,
   kArray,
   kValue,
   kStrValuePair,
   kUNKNOWNObjType,
};

typedef pair<TObjType, string> TTObjTypeStrPair;
typedef map<TObjType, string> TTObjTypeStrMap;

class BoostJSON
{
public:
   BoostJSON();
   virtual ~BoostJSON();

   // INPUT/OUPUT
   // LoadJSONFile() loads the file jsonFileName
   void LoadJSONFile(const string& jsonFileName);
   // CoutCode() populates outStr with a three letter code that shows if
   // itr->first, itr->second.data, and itr->second, respectively, are
   // populated ('S') or empty('E').
   void CoutCode(ptree::const_iterator itr, string& outStr) const;
   // CoutTypeStr() outputs the type of itr.
   void CoutTypeStr(ptree::const_iterator itr) const;
   // Dump() outputs the JSON structure under pt, indented by cnt.
   void Dump(const ptree& pt, int cnt) const;
   // Dump() outputs the entire loaded JSON structure.
   void Dump() const;
   // getPt() returns the internal Boost ptree.
   const ptree& getPt() const;

   // INFORMATIONAL
   // GetObjectType() returns the object type of itr.
   TObjType GetObjectType(ptree::const_iterator &itr) const;
   // GetValueType() returns the value type of itr.
   TJSONValueType GetValueType(ptree::const_iterator &itr) const;
   // GetValueType() returns the value type of valStr.
   TJSONValueType GetValueType(const string& valStr) const;
   // GetValueTypeStr() returns the string name for type.
   const string& GetValueTypeStr(TJSONValueType type) const;
   // GetChildCount() returns the number of direct children under itr.
   size_t GetChildCount(ptree::const_iterator &itr) const;
   // IsObject() returns true iff itr points to an object.
   // An object has a name, an unnamed tree, and the first child element is an
   // object or string-value pair.
   bool IsObject(ptree::const_iterator &itr) const;
   // IsArray() returns true iff itr points to an element in an array.
   // An array has a name, an unnamed tree, and the first child element is a
   // value.
   bool IsArray(ptree::const_iterator &itr) const;
   // IsValue() returns true iff itr points to a value.
   // A value has no name and a named, empty tree.
   bool IsValue(ptree::const_iterator &itr) const;
   // IsStrValuePair() returns true iff itr points to a string-value pair.
   // A string-value pair has a name and a named, empty tree.
   bool IsStrValuePair(ptree::const_iterator &itr) const;

private:
   // Not implemented
   BoostJSON(BoostJSON&);
   BoostJSON& operator=(BoostJSON&);
   bool operator==(BoostJSON&);
   bool operator!=(BoostJSON&);

   ptree m_pt;
   static TTJSONValueTypeStrMap  ms_valTypeStrMap;
   static TTJSONValueTypeRegexMap  ms_valTypeRegexStrMap;
   static TTObjTypeStrMap        ms_objTypeStrMap;
};

}

#endif /* BOOSTJSON_H_ */

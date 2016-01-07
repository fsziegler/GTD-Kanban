/*
 * BoostJSON.cpp
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

#include "BoostJSON.h"

namespace BoostJSONDemo
{

TTJSONValueTypeStrMap   BoostJSON::ms_valTypeStrMap;
const string            kUNKNOWNJSONValueTypeStr("UNKNOWNValueType");
TTJSONValueTypeRegexMap BoostJSON::ms_valTypeRegexStrMap;
TTObjTypeStrMap         BoostJSON::ms_objTypeStrMap;
const string            kUNKNOWNJSONObjTypeStr("UNKNOWNObjType");

BoostJSON::BoostJSON()
{
   if (0 == ms_valTypeStrMap.size())
   {
      ms_valTypeStrMap.insert(TTJSONValueTypeStrPair(kJSONTrueType, "true"));
      ms_valTypeStrMap.insert(TTJSONValueTypeStrPair(kJSONFalseType, "false"));
      ms_valTypeStrMap.insert(TTJSONValueTypeStrPair(kJSONNullType, "null"));
      ms_valTypeStrMap.insert(
            TTJSONValueTypeStrPair(kJSONNumberType, "number"));
      ms_valTypeStrMap.insert(
            TTJSONValueTypeStrPair(kJSONStringType, "string"));
      ms_valTypeStrMap.insert(
            TTJSONValueTypeStrPair(kJSONObjectType, "object"));
      ms_valTypeStrMap.insert(TTJSONValueTypeStrPair(kJSONArrayType, "array"));
      ms_valTypeStrMap.insert(
            TTJSONValueTypeStrPair(kUNKNOWNJSONValueType,
                  kUNKNOWNJSONValueTypeStr));

      ms_valTypeRegexStrMap.insert(
            TTJSONValueTypeRegexPair(kJSONTrueType, boost::regex("true")));
      ms_valTypeRegexStrMap.insert(
            TTJSONValueTypeRegexPair(kJSONFalseType, boost::regex("false")));
      ms_valTypeRegexStrMap.insert(
            TTJSONValueTypeRegexPair(kJSONNullType, boost::regex("null")));
      ms_valTypeRegexStrMap.insert(
            TTJSONValueTypeRegexPair(kJSONNumberType,
                  boost::regex("[0-9\\+\\-\\.eE]+")));
      ms_valTypeRegexStrMap.insert(
            TTJSONValueTypeRegexPair(kJSONStringType,
                  boost::regex("[[:alnum:][:punct:][:space:]]+")));

      ms_objTypeStrMap.insert(TTObjTypeStrPair(kObject, "Object"));
      ms_objTypeStrMap.insert(TTObjTypeStrPair(kArray, "Array"));
      ms_objTypeStrMap.insert(TTObjTypeStrPair(kValue, "Value"));
      ms_objTypeStrMap.insert(TTObjTypeStrPair(kStrValuePair, "ValuePair"));
      ms_objTypeStrMap.insert(
            TTObjTypeStrPair(kUNKNOWNObjType, kUNKNOWNJSONObjTypeStr));
   }
}

BoostJSON::~BoostJSON()
{
}

void BoostJSON::LoadJSONFile(const string& jsonFileName)
{
   try
   {
      read_json(jsonFileName.c_str(), m_pt);
   }
   catch(exception& ex)
   {
      cout << "Exception " << ex.what() << " thrown trying to open JSON file "
            << jsonFileName << endl;
   }
   catch(...)
   {
      cout << "Unknown exception thrown trying to open JSON file "
            << jsonFileName << endl;
   }
}

void Indent(int cnt)
{
   for(int i=0; cnt>i; ++i)
   {
      cout << "  ";
   }
}

void BoostJSON::CoutCode(ptree::const_iterator itr, string& outStr) const
{
   outStr.clear();
   outStr.append(0 < itr->first.size() ? "[S" : "[E");
   outStr.append(0 < itr->second.data().size() ? "S" : "E");
   outStr.append(0 < itr->second.size() ? "S] " : "E] ");
}

void BoostJSON::CoutTypeStr(ptree::const_iterator itr) const
{
   ptree::const_iterator itrCpy(itr);
   switch(GetObjectType(itrCpy))
   {
   case kObject:
      cout << "{object} ";
      break;
   case kArray:
      cout << "{array object} ";
      break;
   case kValue:
      cout << "{";
      cout << GetValueTypeStr(GetValueType(itrCpy));
      cout << "} ";
      break;
   case kStrValuePair:
      cout << "{";
      cout << GetValueTypeStr(GetValueType(itrCpy->second.data()));
      cout << "} ";
      break;
   case kUNKNOWNObjType:
   default:
      cout << "{unknown} ";
      break;
   }
}

void BoostJSON::Dump(const ptree& pt, int cnt) const
{
   static const string EmptyStr("[empty]");
   string outStr;
   for (ptree::const_iterator itr = pt.begin(); pt.end() != itr; ++itr)
   {
      CoutCode(itr, outStr);
      Indent(cnt);
      if(0 < itr->first.size())
      {
         cout << outStr << itr->first;
         switch(GetObjectType(itr))
         {
         case kObject:
            cout << "{object}";
            break;
         case kArray:
            cout << "{array}";
            break;
         default:
            cout << "{string}";
            break;
         }
      }
      else
      {
         cout << outStr << EmptyStr;
      }
      cout << " : ";
      if(0 < GetChildCount(itr))
      {
         cout << endl;
         Dump(itr->second, cnt+1);
      }
      else
      {
         cout
               << (0 < itr->second.data().size() ? itr->second.data() : EmptyStr);
         ptree::const_iterator itrCpy(itr);
         CoutTypeStr(itrCpy);
         cout << endl;
      }
   }
}

void BoostJSON::Dump() const
{
   Dump(m_pt, 0);
}

const ptree& BoostJSON::getPt() const
{
   return m_pt;
}

/*
            Second
   First    data()   Children Case
   -------+--------+--------+-------
   empty  | empty  | empty  | DNE
   empty  | empty  | exist  | DNE
   empty  | string | empty  | value (in array)
   empty  | string | exist  | DNE
   string | empty  | empty  | object (empty)
   string | empty  | exist  | object
   string | string | empty  | string:value pair
   string | string | exist  | DNE
*/
TObjType BoostJSON::GetObjectType(ptree::const_iterator &itr) const
{
   bool first(0 < itr->first.size());
   bool childName(0 < itr->second.data().size());
   bool children(0 < itr->second.size());
   if(!first && childName && !children)
   {
      return kValue;
   }
   if (first && !childName)
   {
      if(children)
      {
         ptree::const_iterator objItr(itr->second.begin());
         switch(GetObjectType(objItr))
         {
         case kObject:
         case kStrValuePair:
            return kObject;
         case kValue:
            return kArray;
         default:
            break;
         }
      }
      else
      {
         return kObject;
      }
   }
   if(first && childName && !children)
   {
     return kStrValuePair;
   }
   return kUNKNOWNObjType;
}

TJSONValueType BoostJSON::GetValueType(const string& valStr) const
{
   for (int i = kJSONTrueType; kJSONObjectType != i;
         ++i)
   {
      const TJSONValueType valType((TJSONValueType) i);
      auto itr = ms_valTypeRegexStrMap.find(valType);
      if ((ms_valTypeRegexStrMap.end() != itr)
            && (boost::regex_match(valStr, (*itr).second)))
      {
         return valType;
      }
   }
   return kUNKNOWNJSONValueType;
}

TJSONValueType BoostJSON::GetValueType(ptree::const_iterator& itr) const
{
   TObjType objType(GetObjectType(itr));
   switch(objType)
   {
   case kObject:
      return kJSONObjectType;
   case kArray:
      return kJSONArrayType;
   case kValue:
   {
      return GetValueType(itr->second.data());
   }
   case kStrValuePair:
      return kJSONStringType; // assumes "string" in "string/value" pair
   default:
      break;
   }
   return kUNKNOWNJSONValueType;
}

const string& BoostJSON::GetValueTypeStr(TJSONValueType type) const
{
   if(ms_valTypeStrMap.end() != ms_valTypeStrMap.find(type))
   {
      return (*ms_valTypeStrMap.find(type)).second;
   }
   return kUNKNOWNJSONValueTypeStr;
}

size_t BoostJSON::GetChildCount(ptree::const_iterator& itr) const
{
   return (*itr).second.size();
}

bool BoostJSON::IsObject(ptree::const_iterator& itr) const
{
   return (kJSONObjectType == GetValueType(itr));
}

bool BoostJSON::IsArray(ptree::const_iterator& itr) const
{
   return (kJSONArrayType == GetValueType(itr));
}

bool BoostJSON::IsValue(ptree::const_iterator& itr) const
{
   return (kValue == GetObjectType(itr));
}

bool BoostJSON::IsStrValuePair(ptree::const_iterator &itr) const
{
   return (kStrValuePair == GetObjectType(itr));
}

}

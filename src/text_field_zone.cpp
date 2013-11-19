/*    This file is part of synoptic
      The aim of this software is to provide synoptic reprenstation
      utilities
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include "text_field_zone.h"

namespace synoptic
{
  //----------------------------------------------------------------------------
  void text_field_zone::init(void)
  {
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type(' ',0x0));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('!',0x10101010001000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('"',0x24480000000000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('#',0x127f247e480000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('$',0x18201824180400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('%',0x2052240812250200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('&',0xc101a241a00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('\'',0x10100000000000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('(',0x810202020201008));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type(')',0x2010080808081020));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('*',0x103810280000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('+',0x10107c101000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type(',',0x8081000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('-',0x3c000000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('.',0x80000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('/',0x2040810204000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('0',0x1c222222221c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('1',0x18280808083e00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('2',0x7c023e40403e00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('3',0x7c023c02027c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('4',0xc10287e080800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('5',0x7e407c02027c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('6',0x3e407c42423c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('7',0x7e020404080800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('8',0x3c423c42423c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('9',0x3c42423e023c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type(':',0x101000101000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type(';',0x80008081000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('<',0x618204020180600));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('=',0x7e007e000000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('>',0x6018040204186000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('?',0x3c422408000800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('@',0x3c425a5c403e00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('A',0x3c42427e424200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('B',0x7c427c42427c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('C',0x3c404040403c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('D',0x7c424242427c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('E',0x7e404078407e00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('F',0x7e407c40404000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('G',0x3e40404e423c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('H',0x22223e22222200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('I',0x7c101010107c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('J',0x7e080808087000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('K',0x42445860584600));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('L',0x40404040407c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('M',0x42665a42424200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('N',0x4262524a464200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('O',0x3c424242423c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('P',0x7c42427c404000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('Q',0x3844544c443a00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('R',0x7c42427c444200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('S',0x3e403c02027c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('T',0x7c101010101000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('U',0x42424242423c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('V',0x42422424241800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('W',0x4141222a2a1400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('X',0x42241818244200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('Y',0x42241810204000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('Z',0x7e020c30407e00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('[',0x38202020203800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('\\',0x40201008040200));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type(']',0x38080808083800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('^',0x10280000000000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('_',0x7c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('`',0x4020000000000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('a',0x3048483400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('b',0x20203824241800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('c',0x1c20201c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('d',0x404142c241c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('e',0x182438201c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('f',0xc10101c101000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('g',0x344838083000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('h',0x60202038242400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('i',0x80008080800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('j',0x40e0202020c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('k',0x10101418141400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('l',0x30101010107c00));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('m',0x78545400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('n',0x18141400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('o',0x1824241800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('p',0x182438202000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('q',0x18241c040400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('r',0x6c3020202000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('s',0x1c2018043800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('t',0x20382020202000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('u',0x4848483400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('v',0x4428281000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('w',0x412a2a1400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('x',0x442810284400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('y',0x2418081000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('z',0x3808103800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('{',0x408081008080400));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('|',0x8080808080800));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('}',0x2010100810102000));
    m_chars.insert(std::map<uint8_t,uint64_t>::value_type('~',0x205a040000));
   
  }

  std::map<uint8_t,uint64_t> text_field_zone::m_chars;
}

//EOF

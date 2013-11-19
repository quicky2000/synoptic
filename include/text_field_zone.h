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
#ifndef TEXT_FIELD_ZONE_H
#define TEXT_FIELD_ZONE_H

#include "zone.h"
#include "quicky_exception.h"
#include <map>
#include <string>
#include <sstream>

namespace synoptic
{
  class text_field_zone: public zone
  {
  public:
    inline text_field_zone(zone_owner_if &,
                           const uint32_t &);
    inline void set_text(const std::string & p_text);
    inline void set_text(const uint64_t & p_nb);
    inline void set_text(const double & p_nb);
  private:
    inline void internal_paint(const uint8_t & p_char,const uint32_t & p_pos);
    inline void internal_paint(void);
    static void init(void);
    const uint32_t m_nb_char;
    std::string m_text;
    std::string m_previous_text;
    static std::map<uint8_t,uint64_t> m_chars;
  };
  //----------------------------------------------------------------------------
  text_field_zone::text_field_zone(zone_owner_if & p_owner,
                                   const uint32_t & p_nb_char):
    zone(p_owner,8 * p_nb_char,8),
    m_nb_char(p_nb_char),
    m_text(p_nb_char,' ')
      {
        if(!m_chars.size())
          {
            init();
          }
      }
    //----------------------------------------------------------------------------
    void text_field_zone::internal_paint(void)
    {
      for(uint32_t l_index = 0 ; l_index < m_text.size() ; ++l_index)
        {
	  if(m_text[l_index] != m_previous_text[l_index])
	    {
	      internal_paint(m_text[l_index],l_index);
	    }
        }
      m_previous_text = m_text;
    }

    //----------------------------------------------------------------------------
    void text_field_zone::set_text(const std::string & p_text)
    {
      if(p_text.size() > m_nb_char)
        {
          std::stringstream l_stream ;
          l_stream << "Text \"" << p_text << "\" is too long compared to field width : " << m_nb_char ;
          throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
        }
      m_text = p_text;
      if(m_text.size() < m_nb_char) m_text += std::string(m_nb_char - m_text.size(),' ');
    }

    //----------------------------------------------------------------------------
    void text_field_zone::set_text(const uint64_t & p_nb)
      {
	std::stringstream l_stream ;
	l_stream << p_nb;
	set_text(l_stream.str());
      }

    //----------------------------------------------------------------------------
    void text_field_zone::set_text(const double & p_nb)
      {
	std::stringstream l_stream ;
	l_stream << p_nb;
	set_text(l_stream.str());
      }

    //----------------------------------------------------------------------------
    void text_field_zone::internal_paint(const uint8_t & p_char,const uint32_t & p_pos)
    {
      std::map<uint8_t,uint64_t>::const_iterator l_iter = m_chars.find(p_char);
      if(m_chars.end() == l_iter)
        {
          std::stringstream l_stream ;
          l_stream << "Char \"" << p_char << "\" has no graphical representation" ;
          throw quicky_exception::quicky_runtime_exception(l_stream.str(),__LINE__,__FILE__);
        }
      uint64_t l_coded_value = l_iter->second;
      uint32_t l_char_color = get_owner().get_color_code(255,255,255);
      uint32_t l_background_color = get_owner().get_color_code(0,0,0);
      for(uint32_t l_y = 0 ; l_y < 8 ; ++l_y)
        {
          for(uint32_t l_x = 0 ; l_x < 8 ; ++l_x)
            {
              if(l_coded_value & 0x1)
                {
                  set_pixel(7 - l_x + 8 * p_pos,7 - l_y,l_char_color);
                }
	      else
		{
                  set_pixel(7 - l_x + 8 * p_pos,7 - l_y,l_background_color);
		}
              l_coded_value = l_coded_value >> 1;
            }
        }
    }
}

#endif // TEXT_FIELD_ZONE_H
//EOF

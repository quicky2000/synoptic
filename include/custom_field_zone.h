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
#ifndef CUSTOM_FIELD_ZONE_H
#define CUSTOM_FIELD_ZONE_H

#include "display_zone.h"
#include "quicky_exception.h"
#include <map>
#include <inttypes.h>

namespace synoptic
{
  class custom_field_zone:public display_zone
  {
  public:
    inline custom_field_zone(zone_owner_if &,
			     const std::string & p_name,
			     const uint32_t & p_width,
			     const uint32_t & p_height);
    inline void set_content(const uint32_t & p_content);
    inline void set_char_color(const uint32_t & p_r,
                               const uint32_t & p_g,
                               const uint32_t & p_b);
    inline void set_background_color(const uint32_t & p_r,
                                     const uint32_t & p_g,
                                     const uint32_t & p_b);
    inline void set_char_color(const uint32_t & p_color_code);
    inline void set_background_color(const uint32_t & p_color_code);
  private:
    virtual const uint64_t & get_content_representation(const uint32_t & p_content)=0;
    // virtual method inherited from zone
    inline void internal_paint(void);
    //end of virtual method inherited from zone
    uint32_t m_content;
    uint32_t m_char_color;
    uint32_t m_background_color;
  };

  //----------------------------------------------------------------------------
  custom_field_zone::custom_field_zone(zone_owner_if & p_owner,
				       const std::string & p_name,
				       const uint32_t & p_width,
				       const uint32_t & p_height):
    display_zone(p_owner,p_name,p_width,p_height),
    m_content(0),
    m_char_color(p_owner.get_color_code(255,255,255)),
    m_background_color(p_owner.get_color_code(0,0,0))
      {
      }

  //----------------------------------------------------------------------------
    void custom_field_zone::set_char_color(const uint32_t & p_r,
                        const uint32_t & p_g,
                        const uint32_t & p_b)
    {
      m_char_color = get_owner().get_color_code(p_r,p_g,p_b);
    }
  //----------------------------------------------------------------------------
    void custom_field_zone::set_background_color(const uint32_t & p_r,
                              const uint32_t & p_g,
                              const uint32_t & p_b)
    {
      m_background_color = get_owner().get_color_code(p_r,p_g,p_b);
    }

    //----------------------------------------------------------------------------
    void custom_field_zone::set_char_color(const uint32_t & p_color_code)
    {
      m_char_color = p_color_code;
    }
    //----------------------------------------------------------------------------
    void custom_field_zone::set_background_color(const uint32_t & p_color_code)
    {
      m_background_color = p_color_code;
    }

    //----------------------------------------------------------------------------
    void custom_field_zone::internal_paint(void)
    {
      uint64_t l_content_representation = get_content_representation(m_content);
    
      for(uint32_t l_y = 0 ; l_y < get_height() ; ++l_y)
        {
          for(uint32_t l_x = 0 ; l_x < get_width() ; ++l_x)
            {
              if(l_content_representation & 0x1)
                {
                  set_pixel(get_width() - 1 - l_x,get_height() - 1 - l_y,m_char_color);
                }
	      else
		{
                  set_pixel(get_width() - 1 - l_x,get_height() - 1 - l_y,m_background_color);
		}
              l_content_representation = l_content_representation >> 1;
            }
        }
    }

    //----------------------------------------------------------------------------
    void custom_field_zone::set_content(const uint32_t & p_content)
    {
      m_content = p_content;
    }
}

#endif // CUSTOM_FIELD_ZONE_H
//EOF
